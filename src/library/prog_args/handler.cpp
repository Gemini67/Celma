
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
/// See documentation of class celma::prog_args::Handler.


// module header file include
#include "celma/prog_args/handler.hpp"


// C++ Standard Library includes
#include <fstream>
#include <iostream>
#include <iomanip>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/common/clear_container.hpp"
#include "celma/common/reset_at_exit.hpp"
#include "celma/common/scoped_value.hpp"
#include "celma/common/tokenizer.hpp"
#include "celma/prog_args/groups.hpp"
#include "celma/prog_args/i_usage_text.hpp"


namespace celma { namespace prog_args {


using std::endl;
using std::exception;
using std::invalid_argument;
using std::logic_error;
using std::overflow_error;
using std::range_error;
using std::runtime_error;
using std::string;
using std::underflow_error;



/// Constructor.
/// @param[in]  flagSet  The set of flags. See enum HandleFlags for a list of
///                      possible values.
/// @param[in]  txt1     Optional pointer to the object to provide additional
///                      text for the usage.
/// @param[in]  txt2     Optional pointer to the object to provide additional
///                      text for the usage.
/// @since  0.3, 04.06.2016  (same interface, now implemented as delegating
///                           constructor)
/// @since  0.2, 10.04.2016
Handler::Handler( int flagSet, IUsageText* txt1, IUsageText* txt2):
   Handler( std::cout, std::cerr, flagSet, txt1, txt2)
{
} // Handler::Handler



/// Constructor that allows to specify the output streams to write to.
/// @param[in]  os        The stream to write normal out to.
/// @param[in]  error_os  The stream to write error output to.
/// @param[in]  flag_set  The set of flags. See enum HandleFlags for a list
///                       of possible values.
/// @param[in]  txt1      Optional pointer to the object to provide
///                       additional text for the usage.
/// @param[in]  txt2      Optional pointer to the object to provide
///                       additional text for the usage.
/// @since  0.3, 04.06.2016  (added parameters for output streams)
/// @since  0.2, 10.04.2016
Handler::Handler( std::ostream& os, std::ostream& error_os,
                  int flag_set, IUsageText* txt1, IUsageText* txt2):
   mOutput( os),
   mErrorOutput( error_os),
   mReadProgramArguments( (flag_set & hfReadProgArg) != 0),
   mVerbose( (flag_set & hfVerboseArgs) != 0),
   mPrintHidden( (flag_set & hfUsageHidden) != 0),
   mUsageContinues( (flag_set & hfUsageCont) != 0),
   mUsagePrinted( false),
   mpOpeningBracketHdlr(),
   mpClosingBracketHdlr(),
   mpExclamationMarkHdlr(),
   mIsSubGroupHandler( false),
   mConstraints(),
   mpLastArg( nullptr),
   mReadingArgumentFile( false)
{

   string  args;


   if ((flag_set & hfHelpShort) && (flag_set & hfHelpLong))
      args = "h,help";
   else if (flag_set & hfHelpShort)
      args = "h";
   else if (flag_set & hfHelpLong)
      args = "help";

   if (!args.empty())
      addArgument( args, detail::ArgHandlerCallable( std::bind( &Handler::usage, this, txt1, txt2)),
                   "Handler::usage",
                   "Prints the program usage");

   if (flag_set & hfArgHidden)
      addArgumentPrintHidden( "print-hidden");

   if (flag_set & hfListArgVar)
      addArgumentListArgVars( "list-arg-vars");

   if (flag_set & hfEndValues)
      addArgumentEndValues( "endvalues");

} // Handler::Handler



/// Destructor, deletes dynamically allocated objects.
/// @since  0.2, 10.04.2016
Handler::~Handler()
{

   common::Vector::clear( mGlobalConstraints);

} // Handler::~Handler



/// Adds an argument that behaves like the -h/--help arguments. Use this if
/// the help argument should e.g. be in another language.<br>
/// The standard help arguments may still be set in the constructor, then
/// both arguments can be used to get the usage displayed.
/// @param[in]  arg_spec  The arguments on the command line for the help
///                       feature.
/// @param[in]  desc      The description of this argument.
/// @param[in]  txt1      Optional pointer to the object to provide
///                       additional text for the usage.
/// @param[in]  txt2      Optional pointer to the object to provide
///                       additional text for the usage.
/// @return  The object managing the argument, may be used to apply further
///          settings (normally not necessary).
/// @since  0.10, 22.12.2016
detail::TypedArgBase* Handler::addHelpArgument( const string& arg_spec,
                                                const string& desc,
                                                IUsageText* txt1,
                                                IUsageText* txt2)
{

   return addArgument( arg_spec,
                       detail::ArgHandlerCallable(
                          std::bind( &Handler::usage, this, txt1, txt2)
                       ),
                       "Handler::usage",
                       desc);
} // Handler::addHelpArgument



/// Adds an argument that takes the path/filename of an argument file as
/// parameter.
/// @param[in]  arg_spec  The arguments on the command line for specifying the
///                       file with the arguments.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::addArgumentFile( const string& arg_spec)
{

   detail::TypedArgBase*  arg_hdl = new detail::TypedArgCallableValue( arg_spec,
                                                                       std::bind( &Handler::readArgumentFile,
                                                                                  this, std::placeholders::_1, true),
                                                                       "Handler::readArgumentFile");


   return internAddArgument( arg_hdl, arg_spec,
                             "Specifies the (path and) file name of the "
                             "file with the program arguments to read.");
} // Handler::addArgumentFile



/// Adds an argument that activates printing of hidden arguments in the usage.
/// @param[in]  arg_spec  The argument(s) on the command line for activating
///                       printing the hidden arguments.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::addArgumentPrintHidden( const string& arg_spec)
{

   detail::TypedArgBase*  arg_hdl = new detail::TypedArg< bool>( arg_spec, DEST_VAR( mPrintHidden));


   return internAddArgument( arg_hdl, arg_spec,
                             "Also print hidden arguments in the usage.");
} // Handler::addArgumentPrintHidden



/// Adds an argument that prints the list of arguments, their destination
/// variables and their values.<br>
/// Same as setting the flag #hfListArgVar, but allows to specify the
/// argument.
/// @param[in]  arg_spec  The argument(s) on the command line for printing the
///                       arguments and their destination variables.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::addArgumentListArgVars( const string& arg_spec)
{

   detail::TypedArgBase*  arg_hdl = new detail::TypedArgCallable( arg_spec, DEST_METHOD( Handler, listArgVars, *this));


   arg_hdl->setCardinality();
   return internAddArgument( arg_hdl, arg_spec,
                             "Prints the list of arguments and their destination "
                             "variables.");
} // Handler::addArgumentListArgVars



/// Adds an argument that can be used to mark the end of multiple, separate
/// value list.
/// @param[in]  arg_spec  The argument(s) on the command line for marking the
///                       end of a separate value list.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::addArgumentEndValues( const string& arg_spec)
{

   detail::TypedArgBase*  arg_hdl = new detail::TypedArgCallable( arg_spec, DEST_METHOD( Handler, endValueList, *this));


   arg_hdl->setCardinality();
   return internAddArgument( arg_hdl, arg_spec,
                             "Marks the end of a multiple, separate value list.");
} // Handler::addArgumentEndValues



/// Specifies the callback function for a control argument.<br>
/// If no handler is defined for a control character, it is treated as error
/// when found in an argument list.
/// @param[in]  ctrlChar  The control character to specify the handler for.
/// @param[in]  hf        The handler to call when the control character is
///                       detected on the argument list.
/// @since  0.2, 10.04.2016
void Handler::addControlHandler( char ctrlChar, HandlerFunc hf) noexcept( false)
{

   switch (ctrlChar)
   {
   case '(':  mpOpeningBracketHdlr  = hf;  break;
   case ')':  mpClosingBracketHdlr  = hf;  break;
   case '!':  mpExclamationMarkHdlr = hf;  break;
   default:
      throw runtime_error( "Invalid control character '" + string( 1, ctrlChar)
                           + "' specified!");
   } // end switch

} // Handler::addControlHandler



/// Adds a constraint to the argument handler itself that affects multiple
/// arguments.<br>
/// The arguments specified in the constraint must already be defined.
/// @param[in]  ic  Pointer to the object that handles the constraint.
/// @since  0.2, 10.04.2016
void Handler::addConstraint( detail::IConstraint* ic) noexcept( false)
{

   if (ic->argumentList().empty())
      throw runtime_error( "may not specify constraint with empty argument list");

   if (!validArguments( ic->argumentList()))
      throw runtime_error( "constraint contains invalid argument(s)");

   // in case the argument list was updated through validArguments(), the
   // constraints may need to be notified about the new content
   ic->validated();

   mGlobalConstraints.push_back( ic);

} // Handler::addConstraint



/// Iterates over the list of arguments and their values and stores the
/// values in the corresponding destination variables.<br>
/// The function also checks for missing, mandatory arguments, arguments
/// wrongly used without a value etc. If an invalid value is passed for an
/// argument, or if a mandatory argument is missing etc., an exception is
/// thrown.
/// @param[in]  argc    Number of arguments passed to the process.
/// @param[in]  argv[]  List of argument strings.
/// @since  0.2, 10.04.2016
void Handler::evalArguments( int argc, char* argv[]) noexcept( false)
{

   // first (try to) read the arguments from the file
   if (mReadProgramArguments)
   {
      readEvalFileArguments( argv[ 0]);
   } // end if

   // make sure that mpLastArg is reset at the end, in case the same object is
   // used multiple times
   const common::ResetAtExit< detail::TypedArgBase*>  rae( mpLastArg, nullptr);

   // now for the command line arguments
   detail::ArgListParser  alp( argc, argv);

   iterateArguments( alp);

   // if the usage was printed, and we still get here, we don't need to perform
   // the final checks
   if (!mUsagePrinted)
   {
      // phew, we're done. check for missing mandatory arguments
      mArguments.checkMandatoryCardinality();
      mSubGroupArgs.checkMandatoryCardinality();

      // check for missing required arguments through constraints
      mConstraints.checkRequired();

      // and check for global constraints not met
      checkGlobalConstraints();
   } // end if

} // Handler::evalArguments



/// Same as evalArguments(). Difference is that this method catches
/// exceptions, reports them on stderr and then exits the program.<br>
/// In other words: If the function returns, all argument requirements and
/// constraints were met.
/// @param[in]  argc    Number of arguments passed to the process.
/// @param[in]  argv    List of argument strings.
/// @param[in]  prefix  Prefix text to print before the error message.<br>
///                     The prefix may be an empty string. If not, add a
///                     space at the end as separator to the following text.
/// @since  0.2, 10.04.2016
void Handler::evalArgumentsErrorExit( int argc, char* argv[],
                                      const string& prefix)
{

   try
   {

      evalArguments( argc, argv);
      return;   // return here, easier error exit below

   } catch (const invalid_argument& ia)
   {
      mErrorOutput << prefix << "Caught 'invalid argument' exception: " << ia.what() << "!" << endl;
   } catch (const logic_error& le)
   {
      mErrorOutput << prefix << "Caught 'logic error' exception: " << le.what() << "!" << endl;
   } catch (const overflow_error& oe)
   {
      mErrorOutput << prefix << "Caught 'overflow' exception: " << oe.what() << "!" << endl;
   } catch (const range_error& re)
   {
      mErrorOutput << prefix << "Caught 'range error' exception: " << re.what() << "!" << endl;
   } catch (const underflow_error& ue)
   {
      mErrorOutput << prefix << "Caught 'underflow' exception: " << ue.what() << "!" << endl;
   } catch (const runtime_error& rte)
   {
      mErrorOutput << prefix << "Caught 'runtime error' exception: " << rte.what() << "!" << endl;
   } catch (const exception& e)
   {
      mErrorOutput << prefix << "Caught unspecific std::exception: " << e.what() << "!" << endl;
   } catch (...)
   {
      mErrorOutput << prefix << "Caught unknown exception!" << endl;
   } // end try

   exit( EXIT_FAILURE);
} // Handler::evalArgumentsErrorExit



/// Compares the arguments defined in this object with those in \a otherAH
/// and throws an exception if duplicates are detected.
/// @param[in]  ownName    The symbolic name of this objects arguments.
/// @param[in]  otherName  The symbolic name of the the other objects
///                        arguments.
/// @param[in]  otherAH    The other object to check the argument list
///                        against.
/// @since  0.2, 10.04.2016
void Handler::crossCheckArguments( const string ownName,
                                   const string& otherName,
                                   const Handler& otherAH) const
{

   // check that no application argument is used by two both argument handlers
   mArguments.checkArgMix(    ownName, otherName, otherAH.mArguments);
   mArguments.checkArgMix(    ownName, otherName, otherAH.mSubGroupArgs);
   mSubGroupArgs.checkArgMix( ownName, otherName, otherAH.mArguments);
   mSubGroupArgs.checkArgMix( ownName, otherName, otherAH.mSubGroupArgs);

   // finally, check that there are no control character handlers set in both
   // argument handlers
   if (mpOpeningBracketHdlr && otherAH.mpOpeningBracketHdlr)
      throw runtime_error( "Control argument handler for '(' from group '" +
                           otherName + "' is already used by '" + ownName +
                           "'");
   if (mpClosingBracketHdlr && otherAH.mpClosingBracketHdlr)
      throw runtime_error( "Control argument handler for ')' from group '" +
                           otherName + "' is already used by '" + ownName +
                           "'");
   if (mpExclamationMarkHdlr && otherAH.mpExclamationMarkHdlr)
      throw runtime_error( "Control argument handler for '!' from group '" +
                           otherName + "' is already used by '" + ownName +
                           "'");

} // Handler::crossCheckArguments



/// The handling of single character arguments and argument strings/names is
/// of course completely the same, except for the argument and its type.<br>
/// So, this template handles both types of arguments. Needed only in the
/// implementation, so the template definition is in the source file too.
/// @tparam  T  The type of the argument (character or string).
/// @param[in]      arg        The argument (character/short or long).
/// @param[in]      argString  The argument character or string always in
///                            string format.
/// @param[in,out]  ai         The iterator pointing to the current argument.
///                            May be increased here (for values or argument
///                            groups).
/// @param[in]      end        Iterator pointing to the end of the argument
///                            list.
/// @return  Result of handling the current argument.
/// @since  0.2, 10.04.2016
template< typename T>
   Handler::ArgResult Handler::processArg( const T& arg,
                                           const string& argString,
                                           detail::ArgListParser::const_iterator& ai,
                                           const detail::ArgListParser::const_iterator& end)
{

   auto  p_arg_hdl = mSubGroupArgs.findArg( arg);


   if (p_arg_hdl != nullptr)
   {
      handleIdentifiedArg( p_arg_hdl, argString);

      auto  subArgHandler = static_cast< detail::TypedArgSubGroup*>( p_arg_hdl)->obj();
      ++ai;

      // we may only advance the main iterator if the argument is (still)
      // handled by the sub-argument
      detail::ArgListParser::const_iterator  subAI( ai);
      while ((subAI != end) &&
             (subArgHandler->evalSingleArgument( subAI, end) == ArgResult::consumed))
      {
         ai = subAI;
         ++subAI;
      } // end while

      mpLastArg = nullptr;
      return ArgResult::consumed;
   } // end if

   mpLastArg = p_arg_hdl = mArguments.findArg( arg);
   if (p_arg_hdl == nullptr)
      return ArgResult::unknown;

   // an argument that we know
   if (p_arg_hdl->valueMode() == detail::TypedArgBase::ValueMode::unknown)
      throw runtime_error( "Value mode not set for argument '" + argString + "'");

   if (p_arg_hdl->valueMode() == detail::TypedArgBase::ValueMode::none)
   {
      // no value needed
      handleIdentifiedArg( p_arg_hdl, argString);
      return ArgResult::consumed;
   } // end if

   // check if the next element in the list is a value
   detail::ArgListParser::const_iterator  ait2( ai);
   ait2.remArgStrAsVal();
   ++ait2;

   if ((p_arg_hdl->valueMode() == detail::TypedArgBase::ValueMode::required) &&
       ((ait2 == end) || (ait2->mElementType != detail::ArgListElement::etValue)))
      throw invalid_argument( "Argument '" + argString + "' requires value(s)");

   if (((ait2 == end) || (ait2->mElementType != detail::ArgListElement::etValue)) &&
       (p_arg_hdl->valueMode() == detail::TypedArgBase::ValueMode::unknown))
   {
      handleIdentifiedArg( p_arg_hdl, argString);
   } else if ((ait2 != end) && (ait2->mElementType == detail::ArgListElement::etValue))
   {
      // first process the argument, *then* assign ait2 to ai
      // reason: arg and argString are references of ai->, so if we change ai
      // the references are still on the old value(s)
      handleIdentifiedArg( p_arg_hdl, argString, ait2->mValue);
      ai = ait2;
   } else
   {
      handleIdentifiedArg( p_arg_hdl, argString);
   } // end if

   return ArgResult::consumed;
} // Handler::processArg



/// Handles one argument.<br>
/// Since this function is called from multiple sources, it must not throw an
/// exception when e.g. an unknown argument is found. Exceptions may only be
/// thrown if e.g. a known argument misses its value. Otherwise, in most
/// cases \a ArgResult::unknown should be returned and the error handling
/// left to the calling function.
/// @param[in]  ai   Iterator that points to the argument to handle.<br>
///                  If the argument requires a value, the iterator is
///                  incremented, so it will point to the next argument when
///                  incremented again.
/// @param[in]  end  Iterator pointing to the end of the argument list.<br>
///                  Needed to check if a value is available.
/// @return  Result of handling this argument.
/// @since  0.2, 10.04.2016
Handler::ArgResult
   Handler::evalSingleArgument( detail::ArgListParser::const_iterator& ai,
                                const detail::ArgListParser::const_iterator& end)
{

   switch (ai->mElementType)
   {
   case detail::ArgListElement::etValue:
      if ((mpLastArg != nullptr) && mpLastArg->takesMultiValue())
      {
         mpLastArg->calledAssign( mReadingArgumentFile, ai->mValue);
         return ArgResult::consumed;
      } else if (detail::TypedArgBase* hdl = mArguments.findArg( '-'))
      {
         handleIdentifiedArg( hdl, string( "-"), ai->mValue);
         return ArgResult::consumed;
      } // end if
      break;

   case detail::ArgListElement::etSingleCharArg:
      return processArg( ai->mArgChar, string( 1, ai->mArgChar), ai, end);

   case detail::ArgListElement::etStringArg:
      return processArg( ai->mArgString, ai->mArgString, ai, end);

   case detail::ArgListElement::etControl:
      if (ai->mArgChar == '(')
      {
         if (!mpOpeningBracketHdlr)
            return ArgResult::unknown;
         mpOpeningBracketHdlr();
      } else if (ai->mArgChar == ')')
      {
         if (!mpClosingBracketHdlr)
            return ArgResult::unknown;
         mpClosingBracketHdlr();
      } else
      {
         if (!mpExclamationMarkHdlr)
            return ArgResult::unknown;
         mpExclamationMarkHdlr();
      } // end if

      return ArgResult::consumed;

   default:
      throw invalid_argument( "Got invalid element in argument list");

   } // end switch

   return ArgResult::unknown;
} // Handler::evalSingleArgument



/// Checks if all mandatory arguments were set, and the cardinality
/// requirements were met.
/// @since  0.2, 10.04.2016
void Handler::checkMissingMandatoryCardinality() const
{

   mArguments.checkMandatoryCardinality();
   mSubGroupArgs.checkMandatoryCardinality();

} // Handler::checkMissingMandatoryCardinality



/// Checks and sets the maximum argument length, needed to format the usage.
/// @param[in,out]  maxArgLen  Maximum argument length as needed so far, may
///                            be increased if this class contains longer
///                            arguments.
/// @since  0.2, 10.04.2016
void Handler::checkMaxArgLen( size_t& maxArgLen) const
{

   size_t  myArgLength = 0;


   myArgLength = std::max( myArgLength, mDescription.maxArgLen());
   maxArgLen   = std::max( myArgLength, maxArgLen);

} // Handler::checkMaxArgLen



/// Checks if the specified argument is already used.
/// @param[in]  argChar  The argument character to check.
/// @return  \c true if the argument is already in use.
/// @since  0.2, 10.04.2016
bool Handler::argumentExists( char argChar) const
{

   return mArguments.findArg( argChar) != nullptr;
} // Handler::argumentExists



/// Checks if the specified argument is already used.
/// @param[in]  argString  The argument string to check.
/// @return  \c true if the argument is already in use.
/// @since  0.2, 10.04.2016
bool Handler::argumentExists( const string& argString) const
{

   return mArguments.findArg( argString) != nullptr;
} // Handler::argumentExists



/// Tries to open the file with the program's name and read the arguments
/// from this file.
/// @param[in]  arg0  The (path and) name of the program file.
/// @since  0.2, 10.04.2016
void Handler::readEvalFileArguments( const char* arg0)
{

   const char*  progNameOnly = basename( arg0);
   const char*  homeDir = getenv( "HOME");


   if (homeDir == nullptr)
      return;

   // try to open the file as $HOME/.progargs/<progname>.pa
   string  absPath( homeDir);
   absPath.append( "/.progargs/").append( progNameOnly).append( ".pa");

   readArgumentFile( absPath, false);

} // Handler::readEvalFileArguments



/// Function to read arguments from a file.
/// @param[in]  pathFilename   The (path and) file name to read from.
/// @param[in]  reportMissing  If set, the file should exist, an exception is
///                            thrown if the file could not be read.
/// @since  0.2, 10.04.2016
void Handler::readArgumentFile( const string& pathFilename, bool reportMissing)
{

   std::ifstream  progArgs( pathFilename.c_str());


   if (!progArgs || !progArgs.is_open())
   {
      if (reportMissing)
         throw runtime_error( "could not open file '" + pathFilename + "'");
      return;
   } // end if

   const common::ResetAtExit< bool>  rae( mReadingArgumentFile, false);
   mReadingArgumentFile = true;

   // now read the lines with arguments and process them
   string  line;
   while (!std::getline( progArgs, line).eof())
   {
      if (line.empty() || (line[ 0] == '#'))
         continue;   // while

      appl::ArgString2Array  as2a( line, nullptr);
      detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);

      iterateArguments( alp);
   } // end while

   progArgs.close();

} // Handler::readArgumentFile



/// Prints the list of arguments and their destination variables.
/// @since  0.2, 10.04.2016
void Handler::listArgVars()
{

   mOutput << mArguments << endl;

   if (!mSubGroupArgs.empty())
      mOutput << mSubGroupArgs << endl;

} // Handler::listArgVars



/// Called to mark the end of a value list: Sets mpLastArg to NULL.
/// @since  0.2, 10.04.2016
void Handler::endValueList()
{

   mpLastArg = nullptr;

} // Handler::endValueList



/// Iterates over the arguments and evaluates them.
/// @param[in]  alp  The parser object used to access the arguments.
/// @since  0.2, 10.04.2016
void Handler::iterateArguments( detail::ArgListParser& alp) noexcept( false)
{

   /// make me the current argument handler
   const common::ScopedValue< detail::ConstraintContainer*>
      makeMeCurrent( detail::ConstraintContainer::mpCurrentConstraints,
                     &mConstraints);


   for (auto ai = alp.begin(); ai != alp.end(); ++ai)
   {
      auto const  result = evalSingleArgument( ai, alp.end());
      if (result == ArgResult::unknown)
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

} // Handler::iterateArguments



/// Prints the usage of this class.
/// @param[out]  os  The stream to print to.
/// @param[in]   ah  The object to print the data of.
/// @return  The stream.
/// @since  0.2, 10.04.2016
std::ostream& operator <<( std::ostream& os, const Handler& ah)
{
   return os << ah.mDescription;
} // operator <<



/// Function to print the usage of a program (when requested through the
/// arguments). The additional parameters allow to print additional
/// information.
/// @param[in]  txt1  Pointer to the object that prints the first text.
/// @param[in]  txt2  Pointer to the object that prints the second text.
/// @since  0.2, 10.04.2016
void Handler::usage( IUsageText* txt1, IUsageText* txt2)
{

   if (Groups::instance().evaluatedByArgGroups() && !mIsSubGroupHandler)
       Groups::instance().displayUsage( txt1, txt2);

   // the second parameter/object can only be used if the first is used too
   // in other words: usage( NULL, myObj) is invalid
   assert( (txt2 == nullptr) || (txt1 != nullptr));
   // if both parameters/objects are used, their position must different
   assert( (txt1 == nullptr) || (txt2 == nullptr) ||
           (txt1->usagePos() != txt2->usagePos()));

   if ((txt1 != nullptr) && (txt1->usagePos() == UsagePos::beforeArgs))
      mOutput << txt1 << endl << endl;

   size_t  stdArgLength = 0;

   mDescription.setMinArgLen( stdArgLength);

   mOutput << "Usage:" << endl;

   mDescription.setPrintHidden( mPrintHidden);
   mOutput << mDescription << endl;

   if ((txt1 != nullptr) && (txt1->usagePos() == UsagePos::afterArgs))
      mOutput << txt1 << endl << endl;
   else if ((txt2 != nullptr) && (txt2->usagePos() == UsagePos::afterArgs))
      mOutput << txt2 << endl << endl;

   if (!mUsageContinues)
      ::exit( EXIT_SUCCESS);

   mUsagePrinted = true;

} // Handler::usage



/// Standard procedure for adding an argument handling object.
/// @param[in]  ah_obj    Pointer to the object that handles the argument.
/// @param[in]  arg_spec  The specification of the argument.
/// @param[in]  desc      The description of the argument.
/// @return  Pointer to the passed argument handling object.
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::internAddArgument( detail::TypedArgBase* ah_obj,
                                                  const string& arg_spec,
                                                  const string& desc)
{

   mArguments.addArgument( ah_obj, arg_spec);
   mDescription.addArgument( arg_spec, desc, ah_obj);

   return ah_obj;
} // Handler::internAddArgument



/// Checks each argument in the list if it is a valid/known argument.<br>
/// If the argument specification in the list does not match the original
/// specification of the argument (short and/or long), it is replaced in the
/// \a constraint_arg_list.
/// @param[in]  constraint_arg_list  .
/// @return  .
/// @since  0.2, 10.04.2016
bool Handler::validArguments( string& constraint_arg_list) const
{

   common::Tokenizer  tok( constraint_arg_list, ';');
   string             new_constraint_arg_list;


   for (auto const& it : tok)
   {
      const auto  comma_pos = it.find( ',');
      string      current_arg;
      if (comma_pos == string::npos)
      {
         detail::TypedArgBase*  arg = nullptr;
         if (it.length() == 1)
         {
            // only a short argument
            arg = mArguments.findArg( it[ 0]);
         } else
         {
            // only a long argument
            arg = mArguments.findArg( it);
         } // end if

         // found the handler for this argument?
         if (arg == nullptr)
            return false;

         // argument is valid but may use both short and long format
         current_arg = arg->argSpec();
      } else
      {
         // both short and long argument
         const string           first(  it, 0, comma_pos);
         const string           second( it, comma_pos + 1, string::npos);
         detail::TypedArgBase*  arg_short = nullptr;
         detail::TypedArgBase*  arg_long  = nullptr;

         if (first.length() == 1)
         {
            arg_short = mArguments.findArg( first[ 0]);
            arg_long  = mArguments.findArg( second);
         } else
         {
            arg_short = mArguments.findArg( second[ 0]);
            arg_long  = mArguments.findArg( first);
         } // end if

         // found both the short and long argument?
         if ((arg_short == nullptr) || (arg_long == nullptr))
            return false;

         // do the short and long format (from the constraint string) really
         // belong to the same handler?
         if (arg_short != arg_long)
            throw runtime_error( "argument short/long mismatch");

         current_arg = arg_short->argSpec();
      } // end if

      // argument from the list is valid
      if (!new_constraint_arg_list.empty())
         new_constraint_arg_list.append( ";");
      new_constraint_arg_list.append( current_arg);
   } // end for

   // when we get here, all the arguments in the constraint string were valid
   // maybe one or more argument specification was expanded, take the new string
   constraint_arg_list = new_constraint_arg_list;

   return true;
} // Handler::validArguments



/// When an argument was identified, passes the argument specification to all
/// global constraint objects to check if a constraint is violated.
/// @param[in]  arg_spec  The argument specification.
/// @since  0.2, 10.04.2016
void Handler::executeGlobalConstraints( const string& arg_spec)
{

   for (auto & current_constraint : mGlobalConstraints)
   {
      current_constraint->executeConstraint( arg_spec);
   } // end for

} // Handler::executeGlobalConstraints



/// After all arguments were processed, call this method to iterate over all
/// global constraints to check e.g. if a required argument is missing.
/// @since  0.2, 10.04.2016
void Handler::checkGlobalConstraints() const
{

   for (auto cit : mGlobalConstraints)
   {
      cit->checkEndCondition();
   } // end for

} // Handler::checkGlobalConstraints



/// Called when a valid argument was identified. Performs the actions that
/// are common to all arguments:
/// - Check argument constraints.
/// - Check global constraints.
/// - Produce verbose output if required.
/// - Finally call calledAssign() for this argument.
///
/// @param[in]  hdl       Pointer to the object that handles this argument.
/// @param[in]  arg_spec  The argument specification.
/// @param[in]  value     The value for the argument, empty string if not set.
/// @since  0.2, 10.04.2016
void Handler::handleIdentifiedArg( detail::TypedArgBase* hdl,
                                   const string& arg_spec,
                                   const string& value)
{

   mConstraints.argumentIdentified( arg_spec);
   executeGlobalConstraints( hdl->argSpec());

   if (mVerbose)
   {
      if (value.empty())
         mOutput << hdl->varName() << ": is set" << endl;
      else
         mOutput << hdl->varName() << ": value '" << value << "' is assigned" << endl;
   } // end if

   hdl->calledAssign( mReadingArgumentFile, value);

} // Handler::handleIdentifiedArg



} // namespace prog_args
} // namespace celma


// ===========================  END OF handler.cpp  ===========================

