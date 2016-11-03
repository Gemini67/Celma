
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
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
#include <iostream>


// project includes
#include "celma/prog_args/handler.hpp"
#include "celma/prog_args/i_usage_text.hpp"


namespace celma { namespace prog_args {


using std::cout;
using std::endl;
using std::invalid_argument;
using std::runtime_error;
using std::string;


/// Adds an argument handler to the internal list.<br>
/// All arguments that this handler supports should already be set, so the
/// class can check that there are no duplicates.
/// @param[in]  grpName  The symbolic name of this handler, used for
///                      identification and printing the usage.
/// @param[in]  ah       The argument handler to add.
/// @since  0.2, 10.04.2016
void Groups::addArgHandler( const string& grpName, SharedArgHndl ah) noexcept( false)
{

   if (ah.get() == nullptr)
   {
      throw runtime_error( "Handler for name '" + grpName + "' is NULL");
   } // end if

   /// check that this symbolic name is not used already
   for (auto const& stored_group : mArgGroups)
   {
      if (stored_group.mName == grpName)
         throw runtime_error( "Group name '" + grpName + "' is already in use!");
   } // end for

   /// Make sure that the new group does not contain any argument(s) that are
   /// already used by an existing group
   for (auto const& stored_group : mArgGroups)
   {
      stored_group.mpArgHandler->crossCheckArguments( stored_group.mName,
                                                      grpName, *ah);
   } // end for

   mArgGroups.push_back( Storage( grpName, ah));

} // Groups::addArgHandler



/// Returns the handler stored with the given symbolic name.
/// @param[in]  grpName  The name of the handler.
/// @return  Pointer to the handler object, NULL if no object with this name
///          was found.
/// @since  0.2, 10.04.2016
Groups::SharedArgHndl Groups::getHandler( const string& grpName) const
{

   for (auto const& stored_group : mArgGroups)
   {
      if (stored_group.mName == grpName)
         return stored_group.mpArgHandler;
   } // end for

   return SharedArgHndl();
} // Groups::getHandler



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
      auto  result = Handler::arUnknown;
      for (auto & stored_group : mArgGroups)
      {
         result = stored_group.mpArgHandler->evalSingleArgument( ai, alp.end());
         if (result != Handler::arUnknown)
            break;   // for
      } // end for

      if (result == Handler::arUnknown)
      {
         if (ai->mElementType == detail::ArgListElement::etValue)
            throw invalid_argument( "Unknown argument '" + ai->mValue + "'");
         if ((ai->mElementType == detail::ArgListElement::etSingleCharArg) ||
             (ai->mElementType == detail::ArgListElement::etControl))
            throw invalid_argument( "Unknown argument '" + string( 1, ai->mArgChar)
                                    + "'");
         throw invalid_argument( "Unknown argument '" + ai->mArgString + "'");
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



/// Constructor.
/// @since  0.2, 10.04.2016
Groups::Groups():
   mArgGroups(),
   mEvaluating( false),
   mUsageLineLength( detail::ArgumentDesc::DefaultLineLength)
{
} // Groups::Groups



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



} // namespace prog_args
} // namespace celma


// ============================  END OF groups.cpp  ============================

