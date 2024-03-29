
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::Handler.


// module headerfile include
#include "celma/prog_args/handler.hpp"


// OS/C lib includes
#include <cstdlib>
#include <cstring>
#include <libgen.h>


// C++ Standard Library includes
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <vector>


// Boost library includes
#include <boost/algorithm/string.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/common/contains.hpp"
#include "celma/common/reset_at_exit.hpp"
#include "celma/common/scoped_value.hpp"
#include "celma/common/tokenizer.hpp"
#include "celma/container/clear_container.hpp"
#include "celma/format/text_block.hpp"
#include "celma/prog_args/destination.hpp"
#include "celma/prog_args/detail/eval_arguments_error_exit.hpp"
#include "celma/prog_args/detail/i_handler_value_constraint.hpp"
#include "celma/prog_args/detail/typed_arg_sub_group.hpp"
#include "celma/prog_args/groups.hpp"
#include "celma/prog_args/i_usage_text.hpp"


namespace celma::prog_args {


using std::endl;
using std::exception;
using std::invalid_argument;
using std::logic_error;
using std::overflow_error;
using std::out_of_range;
using std::runtime_error;
using std::string;
using std::underflow_error;


// module definitions
const detail::ArgumentKey  Handler::mPosKey( "-");


/// Constructor.
///
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
///
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
   mUsageContinues( (flag_set & hfUsageCont) != 0),
   mpUsageParams( new detail::UsageParams()),
   mArguments( (flag_set & hfNoAbbr) == 0),
   mSubGroupArgs( (flag_set & hfNoAbbr) == 0, true),
   mDescription( mpUsageParams),
   mpOpeningBracketHdlr(),
   mpClosingBracketHdlr(),
   mConstraints(),
   mGlobalConstraints(),
   mCheckEnvVar( (flag_set & hfEnvVarArgs) != 0),
   mEnvVarName(),
   mUsedByGroup( (flag_set & hfInGroup) != 0)
{

   handleStartFlags( flag_set, txt1, txt2);

   if (flag_set & hfUsageHidden)
      mpUsageParams->setPrintHidden();

   if (flag_set & hfArgHidden)
      mpUsageParams->addArgumentPrintHidden( *this, "print-hidden");

} // Handler::Handler



/// Constructor to be used by a sub-group. Copies some settings from the main
/// argument handler object.
/// It is possible to create a sub-group argument handler using one of the
/// other constructors, but then the settings are of course not copied.<br>
/// The following flags are ignored, the settings are taken from the main
/// argument handler:<br>
/// #hfReadProgArg, #hfVerboseArgs, #hfUsageHidden, #hfUsageShort,
/// #hfUsageLong and #hfUsageCont.
///
/// @param[in]  main_ah   The main argument handler to copy the settings
///                       from.
/// @param[in]  flag_set  The set of flags. See enum HandleFlags for a list
///                       of possible values.
/// @param[in]  txt1      Optional pointer to the object to provide
///                       additional text for the usage.
/// @param[in]  txt2      Optional pointer to the object to provide
///                       additional text for the usage.
/// @since  1.1.0, 04.12.2017
Handler::Handler( Handler& main_ah, int flag_set, IUsageText* txt1,
                  IUsageText* txt2):
   mOutput( main_ah.mOutput),
   mErrorOutput( main_ah.mErrorOutput),
   mReadProgramArguments( false),
   mVerbose( main_ah.mVerbose),
   mUsageContinues( main_ah.mUsageContinues),
   mpUsageParams( main_ah.mpUsageParams),
   mArguments( (flag_set & hfNoAbbr) == 0),
   mSubGroupArgs( (flag_set & hfNoAbbr) == 0),
   mDescription( mpUsageParams),
   mpOpeningBracketHdlr(),
   mpClosingBracketHdlr(),
   mConstraints(),
   mGlobalConstraints(),
   mCheckEnvVar(),
   mEnvVarName(),
   mUsedByGroup( (flag_set & hfInGroup) != 0)
{

   handleStartFlags( flag_set, txt1, txt2);

} // Handler::Handler



/// Destructor, deletes dynamically allocated objects.
///
/// @since  0.2, 10.04.2016
Handler::~Handler()
{

   container::Vector::clear( mGlobalConstraints);

} // Handler::~Handler



/// Activates the check for program arguments in an environment variable,
/// plus allows to specify the name of the environment variable to use.
/// The default is the name of the program file, all in uppercase letters.
///
/// @param[in]  env_var_name  Optional, the name of the environment variable.
/// @since  1.22.0, 01.04.2019
void Handler::checkEnvVarArgs( std::string env_var_name)
{

   mCheckEnvVar = true;
   mEnvVarName  = env_var_name;

} // Handler::checkEnvVarArgs



/// Adds a sub-group.
///
/// @param[in]  arg_spec
///    The arguments on the command line to enter/start the sub-group.
/// @param[in]  subGroup
///    The object to handle the sub-group arguments.
/// @param[in]  desc
///    The description of this sub-group argument.
/// @return
///    The object managing this argument, may be used to apply further
///    settings.
/// @since  0.2, 10.04.2016
detail::TypedArgBase*
   Handler::addArgument( const string& arg_spec, Handler& subGroup,
                         const string& desc)
{

   subGroup.setIsSubGroupHandler();

   const detail::ArgumentKey  key( arg_spec);
   auto  arg_hdl = new detail::TypedArgSubGroup( key, subGroup);

   arg_hdl->setKey( key);
   arg_hdl->setConstraintsContainer( &mConstraints);

   mSubGroupArgs.addArgument( arg_hdl, key);
   mDescription.addArgument( desc, arg_hdl);

   return arg_hdl;
} // Handler::addArgument



/// Adds an argument that behaves like the -h/--help arguments. Use this if
/// the help argument should e.g. be in another language.
/// The standard help arguments may still be set in the constructor, then
/// both arguments can be used to get the usage displayed.
///
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
      new detail::TypedArgCallable( [=]( bool) { usage( txt1, txt2); },
         "Handler::usage"),
      desc);
} // Handler::addHelpArgument



/// Adds an argument that takes the path/filename of an argument file as
/// parameter.
/// When the flag #hfReadProgArg is passed to the constructor, the program
/// arguments file with the predefined name is always read if it exists.<br>
/// With this method it is possible to specify an argument with which the
/// (path and) name of the arguments file can be specified. Only if this
/// given argument is then used on the command line, the argument file is
/// read.
///
/// @param[in]  arg_spec
///    The arguments on the command line for specifying the file with the
///    arguments.
/// @return
///    The object managing this argument, may be used to apply further
///    settings.
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::addArgumentFile( const string& arg_spec)
{

   static const string        desc( "Specifies the (path and) file name of the "
                                    "file with the program arguments to read.");
   const detail::ArgumentKey  key( arg_spec);

   auto  arg_hdl = new detail::TypedArgCallableValue(
      [&](auto const& filename, bool)
      {
         this->readArgumentFile( filename, true);
      },
      "Handler::readArgumentFile");


   return internAddArgument( arg_hdl, key, desc);
} // Handler::addArgumentFile



/// Adds an argument that activates printing of hidden arguments in the
/// usage.
/// Same as setting the flag #hfArgHidden, but allows to specify the
/// argument and its description.
///
/// @param[in]  arg_spec  The argument(s) on the command line for activating
///                       printing the hidden arguments.
/// @param[in]  desc      Optional text for the description of the argument
///                       in the usage. If not set, the default description
///                       is used.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  1.1.0, 06.12.2017  (adapted to using usage parameters object)
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::addArgumentPrintHidden( const string& arg_spec,
   const char* desc)
{

   return mpUsageParams->addArgumentPrintHidden( *this, arg_spec, desc);
} // Handler::addArgumentPrintHidden



/// Adds an argument that activates printing of usage with arguments with
/// short argument key only.
///
/// @param[in]  arg_spec  The argument(s) on the command line for activating
///                       printing the usage with short arguments only.
/// @param[in]  desc      Optional text for the description of the argument
///                       in the usage. If not set, the default description
///                       is used.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  1.1.0, 25.09.2017
detail::TypedArgBase*
   Handler::addArgumentUsageShort( const std::string& arg_spec,
      const char* desc)
{

   return mpUsageParams->addArgumentUsageShort( *this, arg_spec, desc);
} // Handler::addArgumentUsageShort



/// Adds an argument that activates printing of usage with arguments with
/// long argument key only.
///
/// @param[in]  arg_spec  The argument(s) on the command line for activating
///                       printing the usage with long arguments only.
/// @param[in]  desc      Optional text for the description of the argument
///                       in the usage. If not set, the default description
///                       is used.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  1.1.0, 25.09.2017
detail::TypedArgBase*
   Handler::addArgumentUsageLong( const std::string& arg_spec,
      const char* desc)
{

   return mpUsageParams->addArgumentUsageLong( *this, arg_spec, desc);
} // Handler::addArgumentUsageLong



/// Adds an argument that prints the list of arguments, their destination
/// variables and their values.
/// Same as setting the flag #hfListArgVar, but allows to specify the
/// argument.
///
/// @param[in]  arg_spec  The argument(s) on the command line for printing the
///                       arguments and their destination variables.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::addArgumentListArgVars( const string& arg_spec)
{

   static const string  desc( "Prints the list of arguments and their destination "
                              "variables.");
   const detail::ArgumentKey  key( arg_spec);

   auto  arg_hdl = new detail::TypedArgCallable(
      [&]( bool) { this->listArgVars(); }, "Handler::listArgVars");


   arg_hdl->setCardinality();

   return internAddArgument( arg_hdl, key, desc);
} // Handler::addArgumentListArgVars



/// Adds an argument that prints the list of argument groups.
/// Same as setting the flag #hfListArgGroups, but allows to specify the
/// argument.
///
/// @param[in]  arg_spec  The argument(s) on the command line for printing the
///                       argument groups.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.13.1, 07.02.2017
detail::TypedArgBase* Handler::addArgumentListArgGroups( const string& arg_spec)
{

   static const string  desc( "Prints the list of argument groups.");

   if (!mUsedByGroup)
      throw invalid_argument( "Standard argument 'list argument groups' can"
                              " only be set when argument groups are used!");

   const detail::ArgumentKey  key( arg_spec);

   auto  arg_hdl = new detail::TypedArgCallable(
      [&]( bool) { this->listArgGroups(); }, desc);


   arg_hdl->setCardinality();

   return internAddArgument( arg_hdl, key, desc);
} // Handler::addArgumentListArgGroups



/// Adds an argument that can be used to mark the end of multiple, separate
/// value list.
///
/// @param[in]  arg_spec  The argument(s) on the command line for marking the
///                       end of a separate value list.
/// @return  The object managing this argument, may be used to apply further
///          settings.
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::addArgumentEndValues( const string& arg_spec)
{

   static const string  desc( "Marks the end of a multiple, separate value list.");

   const detail::ArgumentKey  key( arg_spec);
   detail::TypedArgBase*      arg_hdl
      = new detail::TypedArgCallable( [&]( bool)
      {
         this->endValueList();
      }, desc);


   arg_hdl->setCardinality();

   return internAddArgument( arg_hdl, key, desc);
} // Handler::addArgumentEndValues



/// Adds an argument that can be used to get the usage for exactly one
/// argument.
///
/// @param[in]  arg_spec
///    The argument(s) on the command line to request the usage for an
///    argument.
/// @param[in]  full
///    Set this flag if the argument should invoke the function to print the
///    usage and a complee description of the argument and its destination
///    variable.
/// @return
///    The object managing this argument, may be used to apply further
///    settings.
/// @since
///    1.14.0, 25.09.2018
detail::TypedArgBase* Handler::addArgumentHelpArgument( const string& arg_spec,
   bool full)
{

   static const string  desc( "Prints the usage for the given argument.");

   const detail::ArgumentKey  key( arg_spec);
   detail::TypedArgBase*      arg_hdl
      = new detail::TypedArgCallableValue(
         [&, full=full]( auto const& help_arg_key, bool)
         {
            this->helpArgument( help_arg_key, full);
         }, desc);


   return internAddArgument( arg_hdl, key, desc);
} // Handler::addArgumentHelpArgument



/// Specifies the callback functions for handling brackets on the command
/// line.
///
/// @param[in]  open_bracket
///    The handler to call when an opening round bracket is detected on the
///    command line.
/// @param[in]  closing_bracket
///    The handler to call when a closing round bracket is detected in the
///    argument list.
/// @since  1.27.0, 28.05.2019
///    (renamed from addControlHandler)
/// @since  0.2, 10.04.2016
void Handler::addBracketHandler( HandlerFunc open_bracket,
      HandlerFunc closing_bracket)
{

   mpOpeningBracketHdlr = open_bracket;
   mpClosingBracketHdlr = closing_bracket;

   // these are not really new argument handlers, but the cross-check function
   // verifies them too
   if (mUsedByGroup)
      Groups::instance().crossCheckArguments( this);

} // Handler::addBracketHandler



/// Adds a (value) constraint to the argument handler itself that affects
/// multiple arguments.
/// The arguments specified in the constraint must already be defined.
///
/// @param[in]  ihc
///    Pointer to the object that handles the constraint. Is deleted when an
///    error occurs.
/// @throw
///    std::invalid_argument if a NULL pointer is passed, or the argument
///    list contains invalid arguments.
/// @since  0.2, 10.04.2016
void Handler::addConstraint( detail::IHandlerConstraint* ihc)
{

   if (ihc == nullptr)
      throw invalid_argument( "invalid NULL pointer passed");

   if (ihc->isValueConstraint())
   {
      auto  ihvc = static_cast< detail::IHandlerValueConstraint*>( ihc);
      if (!validValueArguments( ihvc))
      {
         delete ihc;
         throw invalid_argument( "constraint contains invalid argument(s)");
      } // end if
   } else if (!validArguments( ihc->argumentList()))
   {
      delete ihc;
      throw invalid_argument( "constraint contains invalid argument(s)");
   } // end if

   // in case the argument list was updated through validArguments(), the
   // constraints may need to be notified about the new content
   ihc->validated();

   mGlobalConstraints.push_back( ihc);

} // Handler::addConstraint



/// Iterates over the list of arguments and their values and stores the
/// values in the corresponding destination variables.
/// The function also checks for missing, mandatory arguments, arguments
/// wrongly used without a value etc. If an invalid value is passed for an
/// argument, or if a mandatory argument is missing etc., an exception is
/// thrown.
///
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

   if (mCheckEnvVar)
   {
      checkReadEnvVarArgs( argv[ 0]);
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
/// exceptions, reports them on \c stderr and then exits the program.
/// In other words: If the function returns, all argument requirements and
/// constraints were met.
///
/// @param[in]  argc    Number of arguments passed to the process.
/// @param[in]  argv    List of argument strings.
/// @param[in]  prefix  Prefix text to print before the error message.<br>
///                     The prefix may be an empty string. If not, add a
///                     space at the end as separator to the following text.
/// @since  0.2, 10.04.2016
void Handler::evalArgumentsErrorExit( int argc, char* argv[],
   const string& prefix)
{

   detail::evalArgumentsErrorExit( *this, mErrorOutput, argc, argv, prefix);

} // Handler::evalArgumentsErrorExit



/// After calling evalArguments(), prints the list of arguments that were
/// used and the values that were set.
///
/// @param[in]  contents_set
///    Set of flags that specify the contents of the summary to print.
/// @param[out]  os
///    The stream to write the summary to.
/// @param[in]   standalone
///    If set, prints a title and a line if no arguments were found,
///    otherwise only prints the list of arguments used.
/// @param[in]   arg_prefix
///    Specifies the prefix for the arguments of this handler. Used when the
///    argument handler handles the arguments of a sub-group.
/// @since 1.8.0, 03.07.2018
void Handler::printSummary( sumoptset_t contents_set, std::ostream& os,
   bool standalone, const char* arg_prefix) const
{

   if (standalone)
      os << "Argument summary:" << std::endl;

   // collect the summary in a stream, so we can check if anything was found
   std::ostringstream  oss;

   mArguments.printSummary( contents_set, oss, arg_prefix);
   mSubGroupArgs.printSummary( contents_set, oss, arg_prefix);

   if (oss.str().empty())
   {
      if (standalone)
         os << "   No arguments used/values set." << std::endl;
   } else
   {
      os << oss.str();
   } // end if

} // Handler::printSummary



/// Helps to determine if an object is a 'plain' Handler object or a
/// ValueHandler object.
///
/// @return  Always \c false for objects of this class.
/// @since  0.14.0, 21.02.2017
bool Handler::isValueHandler() const
{
   return false;
} // Handler::isValueHandler



/// Returns this object if it is a ValueHandler object, otherwise throws.
///
/// @return  \c this object if it is a ValueHandler object, for objects of
///          the base class Handler throws.
/// @since  0.14.0, 15.03.2017
ValueHandler* Handler::getValueHandlerObj()
{
   throw runtime_error( "this is a plain handler, not a handler value");
} // Handler::getValueHandlerObj



/// Returns pointer to the base type of the object that handles the specified
/// argument.
///
/// @param[in]  arg_spec  The short and/or long arguments keys.
/// @return  Pointer to the object handling the specified argument.
/// @since  0.14.0, 16.03.2017
detail::TypedArgBase* Handler::getArgHandler( const string& arg_spec)
                                            noexcept( false)
{

   return mArguments.findArg( detail::ArgumentKey( arg_spec));
} // Handler::getArgHandler



/// Compares the arguments defined in this object with those in \a otherAH
/// and throws an exception if duplicates are detected.
///
/// @param[in]  ownName
///    The symbolic name of this objects arguments.
/// @param[in]  otherName
///    The symbolic name of the the other objects arguments.
/// @param[in]  otherAH
///    The other object to check the argument list against.
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
   // since open and close handlers are always set together, we need to check
   // only one
   if (mpOpeningBracketHdlr && otherAH.mpOpeningBracketHdlr)
      throw invalid_argument( "Control argument handler for '()' from group '" +
                              otherName + "' is already used by '" + ownName +
                              "'");

} // Handler::crossCheckArguments



/// Finally: Handle an identified argument from the command line.
///
/// @param[in]      key  The argument (character/short or long).
/// @param[in,out]  ai   The iterator pointing to the current argument.<br>
///                      May be increased here (for values or argument
///                      groups).
/// @param[in]      end  Iterator pointing to the end of the argument list.
/// @return  Result of handling the current argument.
/// @throws  celma::prog_args::argument_error if a value is missing for an
///          argument.
/// @since  0.15.0, 17.07.2017  (only ArgumentKey as parameter, no template
///                             anymore)
/// @since  0.2, 10.04.2016
Handler::ArgResult
   Handler::processArg( const detail::ArgumentKey& key,
                        detail::ArgListParser::const_iterator& ai,
                        const detail::ArgListParser::const_iterator& end)
                       noexcept( false)
{

   auto  p_arg_hdl = mSubGroupArgs.findArg( key);


   if (p_arg_hdl != nullptr)
   {
      handleIdentifiedArg( p_arg_hdl, key);

      auto  subArgHandler = static_cast< detail::TypedArgSubGroup*>( p_arg_hdl)->obj();
      ++ai;

      // we may only advance the main iterator if the argument is (still)
      // handled by the sub-argument
      auto  subAI( ai);
      while ((subAI != end)
             && (subArgHandler->evalSingleArgument( subAI, end) == ArgResult::consumed))
      {
         ai = subAI++;
      } // end while

      mpLastArg = nullptr;
      return ArgResult::consumed;
   } // end if

   mpLastArg = p_arg_hdl = mArguments.findArg( key);
   if (p_arg_hdl == nullptr)
      return ArgResult::unknown;

   if (p_arg_hdl->valueMode() == ValueMode::none)
   {
      // no value needed
      handleIdentifiedArg( p_arg_hdl, key);
      return ArgResult::consumed;
   } // end if

   if (p_arg_hdl->valueMode() == ValueMode::command)
   {
      // found last argument/value for me, rest for another object/tool
      handleIdentifiedArg( p_arg_hdl, key, ai.argsAsString( false));
      return ArgResult::last;
   } // end if

   // check if the next element in the list is a value
   auto  ait2( ai);
   // if the value mode of this argument is optional, we don't allow values to
   // directly follow the argument, because then we cannot distinguish if it's
   // a value or the next argument
   if (p_arg_hdl->valueMode() == ValueMode::required)
      ait2.remArgStrAsVal();
   ++ait2;

   if ((ait2 == end)
       || (ait2->mElementType != detail::ArgListElement::Type::value))
   {
      // no next value
      if (p_arg_hdl->valueMode() == ValueMode::optional)
         handleIdentifiedArg( p_arg_hdl, key);
      else
         throw argument_error( "Argument '" + format::toString( key)
                               + "' requires value(s)");
   } else
   {
      // have a next value, and value mode can only be 'optional' or 'required'
      // first process the argument, *then* assign ait2 to ai
      // reason: arg and arg_string are references of ai->, so if we change ai
      // the references are still on the old value(s)
      handleIdentifiedArg( p_arg_hdl, key, ait2->mValue);
      ai = ait2;
   } // end if

   return ArgResult::consumed;
} // Handler::processArg



/// Handles one argument.
/// Since this function is called from multiple sources, it must not throw an
/// exception when e.g. an unknown argument is found. Exceptions may only be
/// thrown if e.g. a known argument misses its value. Otherwise, in most
/// cases \a ArgResult::unknown should be returned and the error handling
/// left to the calling function.
///
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
   default:
   case detail::ArgListElement::Type::value:
      if ((mpLastArg != nullptr) && mpLastArg->takesMultiValue())
      {
         mpLastArg->assignValue( mReadMode != ReadMode::commandLine, ai->mValue,
            mInverted);
         return ArgResult::consumed;
      } // end if
      if (detail::TypedArgBase* hdl = mArguments.findArg( mPosKey))
      {
         if (hdl->valueMode() == ValueMode::command)
         {
            // this and the following arguments/values are not for me
            handleIdentifiedArg( hdl, mPosKey, ai.argsAsString());
            return ArgResult::last;
         } // end if

         handleIdentifiedArg( hdl, mPosKey, ai->mValue);
         return ArgResult::consumed;
      } // end if
      break;

   case detail::ArgListElement::Type::singleCharArg:
      return processArg( detail::ArgumentKey( ai->mArgChar), ai, end);

   case detail::ArgListElement::Type::stringArg:
      return processArg( detail::ArgumentKey( ai->mArgString), ai, end);

   case detail::ArgListElement::Type::control:
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
         mInverted = true;
      } // end if

      return ArgResult::consumed;
   } // end switch

   return ArgResult::unknown;
} // Handler::evalSingleArgument



/// Checks if all mandatory arguments were set, and the cardinality
/// requirements were met.
///
/// @since  0.2, 10.04.2016
void Handler::checkMissingMandatoryCardinality() const
{

   mArguments.checkMandatoryCardinality();
   mSubGroupArgs.checkMandatoryCardinality();

} // Handler::checkMissingMandatoryCardinality



/// Checks if the specified argument is already used.
///
/// @param[in]  argChar  The argument character to check.
/// @return  \c true if the argument is already in use.
/// @since  0.2, 10.04.2016
bool Handler::argumentExists( char argChar) const
{

   return mArguments.findArg( detail::ArgumentKey( argChar)) != nullptr;
} // Handler::argumentExists



/// Checks if the specified argument is already used.
///
/// @param[in]  argString  The argument string to check.
/// @return  \c true if the argument is already in use.
/// @since  0.2, 10.04.2016
bool Handler::argumentExists( const string& argString) const
{

   return mArguments.findArg( detail::ArgumentKey( argString)) != nullptr;
} // Handler::argumentExists



/// Tries to open the file with the program's name and read the arguments
/// from this file.
///
/// @param[in]  arg0  The (path and) name of the program file.
/// @since  0.2, 10.04.2016
void Handler::readEvalFileArguments( const char* arg0)
{

   assert( (mReadMode & ReadMode::file) == 0);

   // have to copy the path since basename() may want to modify it
   std::unique_ptr< char>  copy( new char[ ::strlen( arg0)]);

   ::strcpy( copy.get(), arg0);

   const char*  progNameOnly = ::basename( copy.get());
   const char*  homeDir = ::getenv( "HOME");

   if (homeDir == nullptr)
      return;

   // try to open the file as $HOME/.progargs/<progname>.pa
   string  absPath( homeDir);
   absPath.append( "/.progargs/").append( progNameOnly).append( ".pa");

   readArgumentFile( absPath, false);

} // Handler::readEvalFileArguments



/// If no environment variable name is given, the name of the program file is
/// used. Then check if an environment variable with this name exists and is
/// not empty. If so the evaluate the program arguments from the variable.
///
/// @param[in]  arg0  The (path and) name of the program file.
/// @since  1.22.0, 01.04.2019
void Handler::checkReadEnvVarArgs( const char* arg0)
{

   assert( (mReadMode & ReadMode::envVar) == 0);

   if (mEnvVarName.empty())
   {
      std::unique_ptr< char>  copy( new char[ ::strlen( arg0)]);

      ::strcpy( copy.get(), arg0);
      mEnvVarName = ::basename( copy.get());
      boost::to_upper( mEnvVarName);
   } // end if

   const char*  arg_env = ::getenv( mEnvVarName.c_str());

   if ((arg_env == nullptr) || (arg_env[ 0] == '\0'))
      return;

   const common::ScopedFlag< uint8_t>  sf( mReadMode, ReadMode::envVar);
   auto const                          as2a = appl::make_arg_array( arg_env,
      nullptr);
   detail::ArgListParser               alp( as2a.mArgC, as2a.mpArgV);

   iterateArguments( alp);

} // Handler::checkReadEnvVarArgs



/// Function to read arguments from a file.
///
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

   const common::ScopedFlag< uint8_t>  sf( mReadMode, ReadMode::file);

   // now read the lines with arguments and process them
   string  line;
   while (!std::getline( progArgs, line).eof())
   {
      if (line.empty() || (line[ 0] == '#'))
         continue;   // while

      auto const             as2a = appl::make_arg_array( line, nullptr);
      detail::ArgListParser  alp( as2a.mArgC, as2a.mpArgV);

      iterateArguments( alp);
   } // end while

   progArgs.close();

} // Handler::readArgumentFile



/// Prints the list of arguments and their destination variables.
///
/// @since  0.2, 10.04.2016
void Handler::listArgVars()
{

   mOutput << mArguments << endl;

   if (!mSubGroupArgs.empty())
      mOutput << mSubGroupArgs << endl;

} // Handler::listArgVars



/// Prints the list of argument groups.
///
/// @since  0.13.1, 07.02.2017
void Handler::listArgGroups()
{

   Groups::instance().listArgGroups();

} // Handler::listArgGroups



/// Called to mark the end of a value list: Sets #mpLastArg to NULL.
///
/// @since  0.2, 10.04.2016
void Handler::endValueList()
{

   mpLastArg = nullptr;

} // Handler::endValueList



/// Searches if the given argment key belongs to a known argument, and if so
/// prints its usage.
/// If the argument key is unknown, an error message is printed.<br>
/// At the end, the function calls exit(), unless "usage continues" is set.
///
/// @param[in]  help_arg_key
///    The key of the argument to print the usage of.
/// @param[in]  full
///    If set, also prints information about the argument and its destination
///    variable.
/// @since  1.14.0, 25.09.2018
void Handler::helpArgument( const string& help_arg_key, bool full)
{

   auto const  slash_pos = help_arg_key.find( "/");

   if (slash_pos != string::npos)
   {
      const detail::ArgumentKey  key( help_arg_key.substr( 0, slash_pos));
      auto                       p_arg_hdl = mSubGroupArgs.findArg( key);

      if (p_arg_hdl != nullptr)
      {
         static_cast< detail::TypedArgSubGroup*>( p_arg_hdl)->obj()->
            helpArgument( help_arg_key.substr( slash_pos + 1), full);
         return;
      } // end if

      mErrorOutput << "*** ERROR: Sub-group argument '" << help_arg_key
         << "' is unknown!" << std::endl;

      mUsagePrinted = true;

      if (!mUsageContinues)
        ::exit( EXIT_SUCCESS);
      return;
   } // end if

   const detail::ArgumentKey  key( help_arg_key);
   auto                       p_arg_hdl = mArguments.findArg( key);

   if (p_arg_hdl == nullptr)
   {
      p_arg_hdl = mSubGroupArgs.findArg( key);
   } // end if

   if (p_arg_hdl != nullptr)
   {
      mOutput << "Argument '" << key << "', usage:" << std::endl;

      auto const  desc = mDescription.getArgDesc( key);
      format::TextBlock  tb( 3, 80, true);
      tb.format(  mOutput, desc);

      mOutput << std::endl;

      if (full)
      {
         p_arg_hdl->printProperties( mOutput);
      } // end if
   } else
   {
      mErrorOutput << "*** ERROR: Argument '" << help_arg_key << "' is unknown!"
         << std::endl;
   } // end if

   mUsagePrinted = true;

   if (!mUsageContinues)
      ::exit( EXIT_SUCCESS);

} // Handler::helpArgument



/// Iterates over the arguments and evaluates them.
///
/// @param[in]  alp  The parser object used to access the arguments.
/// @throws  std::invalid_argument when an unknown argument is found.
/// @since  0.2, 10.04.2016
void Handler::iterateArguments( detail::ArgListParser& alp) noexcept( false)
{

   for (auto ai = alp.begin(); ai != alp.end(); ++ai)
   {
      auto const  result = evalSingleArgument( ai, alp.end());
      if (result == ArgResult::unknown)
      {
         if (ai->mElementType == detail::ArgListElement::Type::value)
            throw invalid_argument( "Unknown argument '" + ai->mValue + "'");
         if ((ai->mElementType == detail::ArgListElement::Type::singleCharArg)
             || (ai->mElementType == detail::ArgListElement::Type::control))
            throw invalid_argument( "Unknown argument '" + string( 1, ai->mArgChar)
                                    + "'");
         throw invalid_argument( "Unknown argument '" + ai->mArgString + "'");
      } // end if

      if (result == ArgResult::last)
         break;   // for
   } // end for

} // Handler::iterateArguments



/// Prints the usage of this class.
///
/// @param[out]  os  The stream to print to.
/// @param[in]   ah  The object to print the data of.
/// @return  The stream.
/// @since  0.2, 10.04.2016
std::ostream& operator <<( std::ostream& os, const Handler& ah)
{
   return os << ah.mDescription;
} // operator <<



/// Called by the constructors to evaluate the set of flags given.
///
/// @param[in]  flag_set
///    The set of flags to set.
/// @param[in]  txt1
///    Optional pointer to the object that provides additional text for the
///    usage.
/// @param[in]  txt2
///    Optional pointer to the object that provides additional text for the
///    usage.
/// @since
///    1.11.0, 16.02.2018
void Handler::handleStartFlags( int flag_set, IUsageText* txt1,
   IUsageText* txt2)
{

   string  args;


   if ((flag_set & hfHelpShort) && (flag_set & hfHelpLong))
      args = "h,help";
   else if (flag_set & hfHelpShort)
      args = "h";
   else if (flag_set & hfHelpLong)
      args = "help";

   if ((txt1 == nullptr) && (txt2 != nullptr))
      throw invalid_argument( "Use first usage text argument to specify a "
         "single usage text");
   if ((txt1 != nullptr) && (txt2 != nullptr))
   {
      if (txt1->usagePos() == txt2->usagePos())
         throw invalid_argument( "Cannot have two usage texts with the same "
            "position");
      if ((txt1->usagePos() == UsagePos::afterArgs)
          && (txt2->usagePos() == UsagePos::beforeArgs))
         throw invalid_argument( "Invalid order of usage texts (after/before)");
   } // end if

   if (!args.empty())
      addArgument( args, new detail::TypedArgCallable(
         [=]( bool) { usage( txt1, txt2); }, "Handler::usage"),
         "Prints the program usage.");

   if (flag_set & hfHelpArg)
      addArgumentHelpArgument( "help-arg");

   if (flag_set & hfHelpArgFull)
      addArgumentHelpArgument( "help-arg-full", true);

   if (flag_set & hfUsageDeprecated)
      mpUsageParams->setPrintDeprecated();

   if (flag_set & hfArgDeprecated)
      mpUsageParams->addArgumentPrintDeprecated( *this, "print-deprecated");

   if (flag_set & hfUsageShort)
      mpUsageParams->addArgumentUsageShort( *this, "help-short");

   if (flag_set & hfUsageLong)
      mpUsageParams->addArgumentUsageLong( *this, "help-long");

   if (flag_set & hfListArgVar)
      addArgumentListArgVars( "list-arg-vars");

   if (flag_set & hfListArgGroups)
      addArgumentListArgGroups( "list-arg-groups");

   if (flag_set & hfEndValues)
      addArgumentEndValues( "endvalues");

} // Handler::handleStartFlags



/// Function to print the usage of a program (when requested through the
/// arguments). The additional parameters allow to print additional
/// information.
///
/// @param[in]  txt1
///    Pointer to the object that prints the first text.
/// @param[in]  txt2
///    Pointer to the object that prints the second text.
/// @since  0.2, 10.04.2016
void Handler::usage( IUsageText* txt1, IUsageText* txt2)
{

   if (Groups::instance().evaluatedByArgGroups() && !mIsSubGroupHandler)
   {
      Groups::instance().displayUsage( txt1, txt2);
      mUsagePrinted = true;
      return;
   } // end if

   if ((txt1 != nullptr) && (txt1->usagePos() == UsagePos::beforeArgs))
      mOutput << txt1 << endl << endl;

   mOutput << "Usage:" << endl
           << mDescription << endl;

   if ((txt1 != nullptr) && (txt1->usagePos() == UsagePos::afterArgs))
      mOutput << txt1 << endl << endl;
   else if ((txt2 != nullptr) && (txt2->usagePos() == UsagePos::afterArgs))
      mOutput << txt2 << endl << endl;

   if (!mUsageContinues)
      ::exit( EXIT_SUCCESS);

   mUsagePrinted = true;

} // Handler::usage



/// Standard procedure for adding an argument handling object.
///
/// @param[in]  ah_obj  Pointer to the object that handles the argument.
/// @param[in]  key     The argument key: short and/or long argument.
/// @param[in]  desc    The description of the argument.
/// @return  Pointer to the passed argument handling object.
/// @since  0.15.0, 13.07.2017  (take ArgumentKey instead of string)
/// @since  0.2, 10.04.2016
detail::TypedArgBase* Handler::internAddArgument( detail::TypedArgBase* ah_obj,
                                                  const detail::ArgumentKey& key,
                                                  const string& desc)
{

   ah_obj->setKey( key);
   ah_obj->setConstraintsContainer( &mConstraints);

   mArguments.addArgument( ah_obj, key);
   mDescription.addArgument( desc, ah_obj);

   if (mUsedByGroup)
      Groups::instance().crossCheckArguments( this);

   return ah_obj;
} // Handler::internAddArgument



/// Checks each argument in the list if it is a valid/known argument.
/// If the argument specification in the list does not match the original
/// specification of the argument (short and/or long), it is replaced in the
/// \a constraint_arg_list.
///
/// @param[in]  constraint_arg_list  The list of arguments to check.
/// @return  \c true if all arguments in the list are valid.
/// @throw
///    std::invalid_argument if the given string is empty, contains an
///    invalid argument key or invalid combination of short and long keys,
///    contains less than 2 arguments or the same argument more than once.
/// @since  0.2, 10.04.2016
bool Handler::validArguments( string& constraint_arg_list) const
{

   if (constraint_arg_list.empty())
      throw invalid_argument( "constraints cannot be created with an empty list"
         " of arguments");

   common::Tokenizer     tok( constraint_arg_list, ';');
   string                new_constraint_arg_list;
   std::vector< string>  used_argument;

   for (auto const& it : tok)
   {
      const detail::ArgumentKey  key( it);
      if (detail::TypedArgBase* arg = mArguments.findArg( key))
      {
         if (invalidCombination( key))
            throw invalid_argument( "Combination '" + it + "' is invalid");

         const string  key_str( format::toString( arg->key()));

         if (common::contains( used_argument, key_str))
            throw invalid_argument( "same argument key '" + key_str
               + "' is used twice in argument list");

         // argument from the list is valid
         if (!new_constraint_arg_list.empty())
            new_constraint_arg_list.append( ";");
         new_constraint_arg_list.append( key_str);

         used_argument.push_back( key_str);
      } else
      {
         return false;
      } // end if
   } // end for

   // when we get here, all the arguments in the constraint string were valid
   // maybe one or more argument specification was expanded, take the new string
   constraint_arg_list = new_constraint_arg_list;

   return true;
} // Handler::validArguments



/// Checks each argument in the list of the constraint if it is a valid/known
/// argument.
/// The (pointer to the) argument handlers are also stored in the constraint
/// object, they are needed later to check the constraint.<br>
/// If the argument specification in the list does not match the original
/// specification of the argument (short and/or long), it is replaced in the
/// \a constraint_arg_list.
///
/// @param[in]  ihc  Pointer to the value constraint constraint object.
/// @return  \c true if all arguments in the list are valid.
/// @throw
///    std::invalid_argument if the given string is empty, contains an
///    invalid argument key or invalid combination of short and long keys,
///    contains less than 2 arguments or the same argument more than once.
/// @since  1.31.0, 22.10.2019
bool Handler::validValueArguments( detail::IHandlerValueConstraint* ihc) const
{

   auto &  constraint_arg_list = ihc->argumentList();

   if (constraint_arg_list.empty())
      throw invalid_argument( "constraints cannot be created with an empty list"
         " of arguments");

   common::Tokenizer     tok( constraint_arg_list, ';');
   string                new_constraint_arg_list;
   std::vector< string>  used_argument;

   for (auto const& it : tok)
   {
      const detail::ArgumentKey  key( it);
      if (detail::TypedArgBase* arg = mArguments.findArg( key))
      {
         if (invalidCombination( key))
            throw invalid_argument( "Combination '" + it + "' is invalid");

         if (!ihc->matchesVarType( arg->varTypeName()))
            throw invalid_argument( "arguments listed for constraint have "
               "different types");

         // argument from the list is valid
         const string  key_str( format::toString( arg->key()));

         if (common::contains( used_argument, key_str))
            throw invalid_argument( "same argument key '" + key_str
               + "' is used twice in argument list");

         if (!new_constraint_arg_list.empty())
            new_constraint_arg_list.append( ";");
         new_constraint_arg_list.append( key_str);

         ihc->storeArgumentHandler( arg);

         used_argument.push_back( key_str);
      } else
      {
         return false;
      } // end if
   } // end for

   if (ihc->numArguments() < 2)
      throw invalid_argument( "need at least 2 arguments for a value "
         "constraint");

   // when we get here, all the arguments in the constraint string were valid
   // maybe one or more argument specification was expanded, take the new string
   constraint_arg_list = new_constraint_arg_list;

   return true;
} // Handler::validValueArguments



/// Checks if the provided argument specification contains an invalid
/// combination, i.e. a short and a long argument that are already used on
/// two different, existing arguments.
///
/// @param[in]  key  The argument specification to test.
/// @return  \c true if the given combination is invalid.
/// @since  0.15.0, 06.08.2017
bool Handler::invalidCombination( const detail::ArgumentKey& key) const
{

   // if the argument is provided with short and long argument:
   // search for both separately to make sure there is no mismatch
   detail::TypedArgBase*  short_arg = nullptr;
   detail::TypedArgBase*  long_arg = nullptr;


   if (key.hasCharArg())
   {
      if ((short_arg = mArguments.findArg( detail::ArgumentKey( key.argChar()))) == nullptr)
         throw runtime_error( "unknown argument '" + string( 1, key.argChar())
                              + "'");
   } // end if

   if (key.hasStringArg())
   {
      if ((long_arg = mArguments.findArg( detail::ArgumentKey( key.argString()))) == nullptr)
         throw runtime_error( "unknown argument '" + key.argString() + "'");
   } // end if

   return (short_arg != nullptr) && (long_arg != nullptr)
          && (short_arg != long_arg);
} // Handler::invalidCombination



/// When an argument was identified, passes the argument specification to all
/// global constraint objects to check if a constraint is violated.
///
/// @param[in]  key  The argument specification.
/// @since  0.2, 10.04.2016
void Handler::executeGlobalConstraints( const detail::ArgumentKey& key)
{

   for (auto & current_constraint : mGlobalConstraints)
   {
      current_constraint->executeConstraint( key);
   } // end for

} // Handler::executeGlobalConstraints



/// After all arguments were processed, call this method to iterate over all
/// global constraints to check e.g. if a required argument is missing.
///
/// @since  0.2, 10.04.2016
void Handler::checkGlobalConstraints() const
{

   for (auto const& cit : mGlobalConstraints)
   {
      cit->checkEndCondition();
   } // end for

} // Handler::checkGlobalConstraints



/// Called when a valid argument was identified. Performs the actions that
/// are common to all arguments:
/// - Check argument constraints.
/// - Check global constraints.
/// - Produce verbose output if required.
/// - Finally call assignValue() for this argument.
///
/// @param[in]  hdl    Pointer to the object that handles this argument.
/// @param[in]  key    The short and/or long argument keys.
/// @param[in]  value  The value for the argument, empty string if not set.
/// @since  0.2, 10.04.2016
void Handler::handleIdentifiedArg( detail::TypedArgBase* hdl,
                                   const detail::ArgumentKey& key,
                                   const string& value)
{

   mConstraints.argumentIdentified( key);
   executeGlobalConstraints( hdl->key());

   if (mVerbose)
   {
      if (value.empty())
         mOutput << hdl->varName() << ": is set" << endl;
      else
         mOutput << hdl->varName() << ": value '" << value << "' is assigned"
                 << endl;
   } // end if

   hdl->assignValue( mReadMode != 0, value, mInverted);

   mInverted = false;

} // Handler::handleIdentifiedArg



} // namespace celma::prog_args


// =====  END OF handler.cpp  =====

