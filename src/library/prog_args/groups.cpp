
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::Groups.


// module header file include
#include "celma/prog_args/groups.hpp"


// C++ Standard Library includes
#include <sstream>
#include <stdexcept>


// project includes
#include "celma/prog_args/detail/eval_arguments_error_exit.hpp"
#include "celma/prog_args/i_usage_text.hpp"


namespace celma { namespace prog_args {


using std::endl;
using std::runtime_error;
using std::string;



/// Returns the argument handler for the specified group name.<br>
/// If the argument handler does not exist yet, a new handler object will be
/// created. If the handler object exists already, it must be a 'plain'
/// handler object, not a value handler.<br>
/// The output streams will be passed as specified when calling instance()
/// for this group object, and the flags parameter will be a combination of
/// this object's flag and the flags passed in \a this_handler_flags.
///
/// @param[in]  grpName             The symbolic name of this handler, used
///                                 for identification and printing the
///                                 usage.
/// @param[in]  this_handler_flags  Set of flags to pass to the constructor
///                                 of the handler object if a new one is
///                                 created.
/// @param[in]  txt1                Optional pointer to the object to provide
///                                 additional text for the usage.
/// @param[in]  txt2                Optional pointer to the object to provide
///                                 additional text for the usage.
/// @since  0.13.0, 05.02.2017  (renamed/merged, added parameters)
/// @since  0.2, 10.04.2016
Groups::SharedArgHndl Groups::getArgHandler( const string& grpName,
                                             int this_handler_flags,
                                             IUsageText* txt1,
                                             IUsageText* txt2)
{

   if (grpName.empty())
      throw runtime_error( "Empty named not allowed for an argument group!");

   /// check that this symbolic group name is used already
   for (auto const& stored_group : mArgGroups)
   {
      if (stored_group.mName == grpName)
      {
         if (stored_group.mpArgHandler->isValueHandler())
            throw runtime_error( "Handler named '" + grpName + "' is a value handler!");
         return stored_group.mpArgHandler;
      } // end if
   } // end for

   auto new_handler = std::make_shared< Handler>( mOutput, mErrorOutput,
                                                  mHandlerFlags | this_handler_flags,
                                                  txt1, txt2);

   new_handler->setUsageParams( mpUsageParams);
   mArgGroups.push_back( Storage( grpName, new_handler));

   // pass the argument 'list argument groups' only to the first Handler object
   if (mHandlerFlags & Handler::hfListArgGroups)
      mHandlerFlags -= Handler::hfListArgGroups;

   return new_handler;
} // Groups::getArgHandler



/// Returns the argument value handler for the specified group name.<br>
/// If the argument handler does not exist yet, a new value handler object
/// will be created. If the handler object exists already, it must a value
/// handler object, not a 'plain' handler.<br>
/// The output streams will be passed as specified when calling instance()
/// for this group object, and the flags parameter will be a combination of
/// this object's flag and the flags passed in \a this_handler_flags.
/// @param[in]  grpName             The symbolic name of this value handler,
///                                 used for identification and printing the
///                                 usage.
/// @param[in]  this_handler_flags  Set of flags to pass to the constructor
///                                 of the value handler object if a new one
///                                 is created.
/// @param[in]  txt1                Optional pointer to the object to provide
///                                 additional text for the usage.
/// @param[in]  txt2                Optional pointer to the object to provide
///                                 additional text for the usage.
/// @since  0.14.0, 09.02.2017
Groups::SharedArgHndl Groups::getArgValueHandler( const string& grpName,
                                                  int this_handler_flags,
                                                  IUsageText* txt1,
                                                  IUsageText* txt2)
{

   if (grpName.empty())
      throw runtime_error( "Empty named not allowed for an argument group!");

   /// check that this symbolic group name is used already
   for (auto & stored_group : mArgGroups)
   {
      if (stored_group.mName == grpName)
      {
         if (!stored_group.mpArgHandler->isValueHandler())
            throw runtime_error( "Handler named '" + grpName + "' is not a value handler!");
         return stored_group.mpArgHandler;
      } // end if
   } // end for

   auto new_handler = std::make_shared< ValueHandler>( mOutput, mErrorOutput,
                                                       mHandlerFlags | this_handler_flags,
                                                       txt1, txt2);

   new_handler->setUsageParams( mpUsageParams);
   mArgGroups.push_back( Storage( grpName, new_handler));

   // pass the argument 'list argument groups' only to the first Handler object
   if (mHandlerFlags & Handler::hfListArgGroups)
      mHandlerFlags -= Handler::hfListArgGroups;

   return new_handler;
} // Groups::getArgValueHandler



/// Iterates over the list of arguments and passes the elemnts to the
/// internally stored argument handlers.<br>
/// After all arguments were processed successfully, the function checks for
/// missing, mandatory arguments.
/// @param[in]  argc    Number of arguments passed to the process.
/// @param[in]  argv[]  List of argument strings.
/// @since  0.2, 10.04.2016
void Groups::evalArguments( int argc, char* argv[]) noexcept( false)
{

   detail::ArgListParser  alp( argc, argv);


   if (mArgGroups.empty())
      throw runtime_error( "No argument handlers defined!");

   mEvaluating = true;

   for (auto ai = alp.begin(); ai != alp.end(); ++ai)
   {
      auto  result = Handler::ArgResult::unknown;
      for (auto & stored_group : mArgGroups)
      {
         result = stored_group.mpArgHandler->evalSingleArgument( ai, alp.end());
         if (result != Handler::ArgResult::unknown)
            break;   // for
      } // end for

      if (result == Handler::ArgResult::unknown)
      {
         if (ai->mElementType == detail::ArgListElement::Type::value)
            throw runtime_error( "Unknown argument '" + ai->mValue + "'");
         if ((ai->mElementType == detail::ArgListElement::Type::singleCharArg)
             || (ai->mElementType == detail::ArgListElement::Type::control))
            throw runtime_error( "Unknown argument '" + string( 1, ai->mArgChar)
                                    + "'");
         throw runtime_error( "Unknown argument '" + ai->mArgString + "'");
      } // end if
   } // end for

   for (auto const& stored_group : mArgGroups)
   {
      stored_group.mpArgHandler->checkMissingMandatoryCardinality();
   } // end for

} // Groups::evalArguments



/// Same as evalArguments(). Difference is that this method catches
/// exceptions, reports them on \c stderr and then exits the program.<br>
/// In other words: If the function returns, all argument requirements and
/// constraints were met.
/// @param[in]  argc
///    Number of arguments passed to the process.
/// @param[in]  argv
///    List of argument strings.
/// @param[in]  prefix
///    Prefix text to print before the error message.<br>
///    The prefix may be an empty string. If not, add a space at the end as
///    separator to the following text.
/// @since
///    1.8.0, 03.07.2018
void Groups::evalArgumentsErrorExit( int argc, char* argv[],
   const std::string& prefix)
{

   detail::evalArgumentsErrorExit( *this, mErrorOutput, argc, argv, prefix);

} // Groups::evalArgumentsErrorExit



/// After calling evalArguments(), prints the list of arguments that were
/// used and the values that were set.
///
/// @param[in]  contents_set
///    Set of flags that specify the contents of the summary to print.
/// @param[out]  os
///    The stream to write the summary to.
/// @since  1.8.0, 03.07.2018
void Groups::printSummary( sumoptset_t contents_set, std::ostream& os) const
{

   os << "Argument summary:" << std::endl;

   std::ostringstream  oss;

   for (auto const& argh : mArgGroups)
   {
      argh.mpArgHandler->printSummary( contents_set, oss, false, nullptr);
   } // end for

   if (oss.str().empty())
      os << "   No arguments used/values set." << std::endl;
   else
      os << oss.str();

} // Groups::printSummary



/// Needed for testing purposes, but may be used in 'normal' programs too:
/// Removes a previously added argument handler object.
/// @param[in]  grpName  The symbolic name of the argument handler to remove.
/// @since  0.2, 10.04.2016
void Groups::removeArgHandler( const string& grpName)
{

   for (auto ahi = mArgGroups.begin(); ahi != mArgGroups.end(); ++ahi)
   {
      if (ahi->mName == grpName)
      {
         mArgGroups.erase( ahi);
         break;   // for
      } // end if
   } // end for

} // Groups::removeArgHandler



/// Needed for testing purposes, but may be used in 'normal' programs too:
/// Removes all previously added argument handler objects.
/// @since  0.13.0, 05.02.2017
void Groups::removeAllArgHandler()
{

   mArgGroups.clear();

} // Groups::removeAllArgHandler



/// Checks if the specified argument is already used by one of the argument
/// handlers.
/// @param[in]  argChar  The argument character to check.
/// @return  \c true if the argument is already in use.
/// @since  0.2, 10.04.2016
bool Groups::argumentExists( char argChar) const
{

   for (auto const& stored_group : mArgGroups)
   {
      if (stored_group.mpArgHandler->argumentExists( argChar))
         return true;
   } // end for

   return false;
} // Groups::argumentExists



/// Checks if the specified argument is already used by one of the argument
/// handlers.
/// @param[in]  argString  The argument string to check.
/// @return  \c true if the argument is already in use.
/// @since  0.2, 10.04.2016
bool Groups::argumentExists( const string& argString) const
{

   for (auto const& stored_group : mArgGroups)
   {
      if (stored_group.mpArgHandler->argumentExists( argString))
         return true;
   } // end for

   return false;
} // Groups::argumentExists



/// Displays the usage combined from all argument handlers.
/// @param[in]  txt1  Pointer to the text to display before or after the
///                   list of arguments.
/// @param[in]  txt2  Pointer to the text to display after the list of
///                   arguments.
/// @since  0.2, 10.04.2016
void Groups::displayUsage( IUsageText* txt1, IUsageText* txt2) const
{

   if ((txt1 != nullptr) && (txt1->usagePos() == Handler::UsagePos::beforeArgs))
      mOutput << txt1 << endl << endl;

   mOutput << "Usage:" << endl << endl;

   for (auto & stored_group : mArgGroups)
   {
      stored_group.mpArgHandler->mDescription.setLineLength( mUsageLineLength);
      stored_group.mpArgHandler->mDescription.setCaption( "Mandatory:",
                                                            "Optional:");

      mOutput << stored_group.mName << endl
              << *(stored_group.mpArgHandler) << endl
              << endl;
   } // end for

   if ((txt1 != nullptr) && (txt1->usagePos() == Handler::UsagePos::afterArgs))
      mOutput << txt1 << endl << endl;
   else if ((txt2 != nullptr) && (txt2->usagePos() == Handler::UsagePos::afterArgs))
      mOutput << txt2 << endl << endl;

   ::exit( EXIT_SUCCESS);

} // Groups::displayUsage



/// When argument groups are used, it is necessary to check that the same
/// argument is only used in one of the handlers.<br>
/// This is achieved by setting the Handler::hfInGroup flag for each handler
/// that is created. Then, when an argument is added to the handler, it calls
/// this method.<br>
/// Here, since we don't know which argument was the new one, compare each
/// argument of the handler with all arguments of all the other handlers.<br>
/// One special point is to mention: When a new Handler object is created,
/// and a standard argument is set by this handler, this will call this
/// method, but then the new Handler object is not yet in the internal object
/// list.
/// @param[in]  mod_handler  The argument Handler object to which a new
///                          argument was added.
/// @since  0.13.0, 05.02.2017
void Groups::crossCheckArguments( Handler* mod_handler) const
{

   string  own_name;


   for (auto const& stored_group : mArgGroups)
   {
      if (stored_group.mpArgHandler.get() == mod_handler)
      {
         own_name = stored_group.mName;
         break;   // for
      } // end if
   } // end for

   if (own_name.empty())
      own_name = "<current handler>";

   for (auto & stored_group : mArgGroups)
   {
      // don't have the handler compare against itself
      if (stored_group.mpArgHandler.get() == mod_handler)
         continue; // for

      mod_handler->crossCheckArguments( own_name, stored_group.mName,
                                        *stored_group.mpArgHandler);
   } // end for

} // Groups::crossCheckArguments



/// Lists the names of the argument groups.
/// @since  013.1, 07.02.2017
void Groups::listArgGroups()
{

   mOutput << "list of known argument groups:" << endl;

   for (auto const& stored_group : mArgGroups)
   {
      mOutput << "- " << stored_group.mName << endl;
   } // end for

} // Groups::listArgGroups



/// Constructor.
///
/// @param[in]  flag_set  Set of the flags to pass to all handler objects.
/// @since  1.8.0, 11.07.2018
Groups::Groups( int flag_set):
   Groups( std::cout, std::cerr, flag_set)
{
} // Groups::Groups



/// Constructor.
///
/// @param[in]  os
///    The stream to write normal output to.
/// @param[in]  error_os
///    The stream to write error output to.
/// @param[in]  flag_set
///    Set of the flags to pass to all handler objects.
/// @since  0.13.0, 05.02.2017  (added parameters)
/// @since  0.2, 10.04.2016
Groups::Groups( std::ostream& os, std::ostream& error_os, int flag_set):
   mOutput( os),
   mErrorOutput( error_os),
   mHandlerFlags( (flag_set & Groups2HandlerFlags) | Handler::hfInGroup),
   mArgGroups(),
   mUsageLineLength( detail::ArgumentDesc::DefaultLineLength),
   mpUsageParams( new detail::UsageParams())
{
} // Groups::Groups



} // namespace prog_args
} // namespace celma


// =====  END OF groups.cpp  =====

