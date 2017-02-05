
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::Groups.


// module header file include
#include "celma/prog_args/groups.hpp"


// project includes
#include "celma/prog_args/handler.hpp"
#include "celma/prog_args/i_usage_text.hpp"


namespace celma { namespace prog_args {


using std::cout;
using std::endl;
using std::runtime_error;
using std::string;



/// Returns the argument handler for the specified group name.<br>
/// If the argument handler does not exist yet, a new handler object will be
/// created. The output streams will be passed as specified when calling
/// instance() for this group object, and the flags parameter will be a
/// combination of this object's flag and the flags passed in
/// \a this_handler_flags.
/// @param[in]  grpName             The symbolic name of this handler, used
///                                 for identification and printing the
///                                 usage.
/// @param[in]  this_handler_flags  Set of flags to pass to the constructor
///                                 of the handler object if a new one is
///                                 created.
/// @param[in]  ah       The argument handler to add.
/// @since  0.2, 10.04.2016
Groups::SharedArgHndl Groups::getArgHandler( const string& grpName,
                                             int this_handler_flags,
                                             IUsageText* txt1,
                                             IUsageText* txt2)
{

   if (grpName.empty())
   {
      throw runtime_error( "Empty named not allowed for an argument group!");
   } // end if

   /// check that this symbolic group name is used already
   for (auto const& stored_group : mArgGroups)
   {
      if (stored_group.mName == grpName)
         return stored_group.mpArgHandler;
   } // end for

   auto new_handler = std::make_shared< Handler>( mOutput, mErrorOutput,
                                                  mHandlerFlags | this_handler_flags,
                                                  txt1, txt2);

   mArgGroups.push_back( Storage( grpName, new_handler));

   return new_handler;
} // Groups::getArgHandler



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
         if (ai->mElementType == detail::ArgListElement::etValue)
            throw runtime_error( "Unknown argument '" + ai->mValue + "'");
         if ((ai->mElementType == detail::ArgListElement::etSingleCharArg) ||
             (ai->mElementType == detail::ArgListElement::etControl))
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

   size_t  maxArgLen = 0;


   for (auto const& stored_group : mArgGroups)
   {
      stored_group.mpArgHandler->checkMaxArgLen( maxArgLen);
   } // end for

   if ((txt1 != nullptr) && (txt1->usagePos() == Handler::UsagePos::beforeArgs))
      cout << txt1 << endl << endl;

   cout << "Usage:" << endl << endl;

   for (auto & stored_group : mArgGroups)
   {
      stored_group.mpArgHandler->mDescription.setMinArgLen( maxArgLen);
      stored_group.mpArgHandler->mDescription.setLineLength( mUsageLineLength);
      stored_group.mpArgHandler->mDescription.setCaption( "Mandatory:",
                                                            "Optional:");

      cout << stored_group.mName << endl
           << *(stored_group.mpArgHandler) << endl
           << endl;
   } // end for

   if ((txt1 != nullptr) && (txt1->usagePos() == Handler::UsagePos::afterArgs))
      cout << txt1 << endl << endl;
   else if ((txt2 != nullptr) && (txt2->usagePos() == Handler::UsagePos::afterArgs))
      cout << txt2 << endl << endl;

   exit( EXIT_SUCCESS);

} // Groups::displayUsage



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



/// Constructor.
/// @param[in]  os        The stream to write normal output to.
/// @param[in]  error_os  The stream to write error output to.
/// @param[in]  flag_set  Set of the flags to pass to all handler objects.
/// @since  0.13.0, 05.02.2017  (added parameters)
/// @since  0.2, 10.04.2016
Groups::Groups( std::ostream& os, std::ostream& error_os, int flag_set):
   mOutput( os),
   mErrorOutput( error_os),
   mHandlerFlags( flag_set | Handler::hfInGroup),
   mArgGroups(),
   mEvaluating( false),
   mUsageLineLength( detail::ArgumentDesc::DefaultLineLength)
{
} // Groups::Groups



} // namespace prog_args
} // namespace celma


// ============================  END OF groups.cpp  ============================

