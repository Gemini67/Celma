
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
/// See documentation of class celma::prog_args::Handler.


#ifndef CELMA_PROG_ARGS_HANDLER_HPP
#define CELMA_PROG_ARGS_HANDLER_HPP


#include <functional>
#include <iosfwd>
#include <string>
#include <vector>

#include "celma/prog_args/detail/arg_list_parser.hpp"
#include "celma/prog_args/detail/argument_container.hpp"
#include "celma/prog_args/detail/argument_desc.hpp"
#include "celma/prog_args/detail/argument_key.hpp"
#include "celma/prog_args/detail/constraint_container.hpp"
#include "celma/prog_args/summary_options.hpp"


namespace celma { namespace prog_args {


class IUsageText;
class Groups;
class ValueHandler;


/// Class to store all command line argument, their descriptions as well as the
/// destination variables to store the values in.<br>
/// To set up an argument handler, simply follow these steps:
/// - Create object, specify the HandleFlags to get the desired behaviour.
/// - For each argument, call addArgument() with the parameters that specify
///   - the short and/or long argument keys;
///   - the handler for the destination variable to store the value in when the
///     argument is used;
///   - the name of the destination variable;
///   - plus a description of the argument and its value (for the usage).
///   .
///   The short (character) and long argument format are order independent in
///   the argument string.<br>
///   The object to handle the destination variable is created using a function
///   of the template family celma::prg_args::destination().<br>
///   Use one of the \c DEST_... macros to easily create the second and third
///   parameter of the function, the destination variable object plus the name
///   of the destination variable.<br>
///   Example:  <code>addArgument( "s,silent", DEST_VAR( mRunSilent), "Set to suppress output");</code>
/// - For free (i.e. positional) arguments, simply pass a string with just a
///   dash as 'argument key':<br>
///   Example:  <code>addArgument( "-", DEST_VAR( mHostname), "The name of the host to connect to");</code>
/// - For each argument, you can specify if it requires a value or not.<br>
///   Internally, the following defaults are applied:
///   - Arguments used to set a boolean variable don't accept a value.
///   - All other arguments require a value.
///   .
///   To change this 'value mode', call the function setValueMode() with the
///   desired value.<br>
///   Example: <code>addArgument( "v,verbose-level", DEST_VAR( mRunSilent),
///                               "Specifies the verbose level, if set without "
///                               "value default is 'low'")
///                             ->setValueMode( vmOptional);</code>
/// - The value mode can also be used to flag a parameter that means:
///   The remaining command line arguments are not for this program/
///   application.<br>
///   Use the vakue mode 'command' for this.<br>
///   If such an argument is used, the remaining argument string is passed as
///   value to its destination variable.
/// - Additionally you can use the following modifiers for each argument to
///   further specify the handling of the argument and its value:
///   - setIsMandatory(): specifies that this argument is mandatory
///   - addCheck(): Allows to add a value check. Possible checks are
///     - lower: Lower limit for values to accept (inclusive).
///     - upper: Upper limit for values to accept (exclusive).
///     - range: Range of values for scalar types to accept.
///     - values: List of values to accept.
///     - pattern: Compares values from the command line against a regular
///       expression pattern.
///     - is file: Value must be the (path and) file name of an existing regular
///       file.
///     - is directory: Value must be the path and name of an existing
///       directory.
///     - is absolute path: The value must be an absolute path.
///     - parent directory exists: The parent directory of the given path/file
///       name must exist (the file itself not).
///     .
///     It is possible to add multiple checks to the same argument. In this case,
///     a value must be accepted by all checks. The checks are executed in the
///     order in which they were added.<br>
///     Example:  <code>addArgument( "f,factor>", DEST_VAR( myFactor), "Factor")->addCheck( range( 1.0, 100.0));</code>
///   - usetFlag(): For destination variable type boolean: Instead of setting the
///     variable to \c true when the argument is used, set it to \c false.
///   - setPrintDefault(): Specifies if the default value (of the destination
///     variable) should be printed in the usage.
///   - setIsHidden(): Can be used to make an argument a hidden argument, i.e.
///     it will not be listed in the usage.
///   - setTakesMultiValue(): For destination types vector and callables: The
///     destination type is able to process multiple, separate values.
///   - addFormat(): Adds a format converter, can be used e.g. to convert
///     symbolic names into integer values.
///   - setListSep(): For destination type vector, allows to specify the list
///     separator character by which a list of values is split.
///   - setCardinality(): Allows to change or delete the cardinality check that
///     is applied to this argument.
///   - checkOriginalValue(): For value arguments, i.e. 'flag' arguments where
///     the value to set on the destination variable is part of the argument
///     itself, multiple changes to the same destination variable are prevented
///     by checking the original value before changing it. Set
///     checkOriginalValue() to \c false to allow multiple changes.
///   - setIsDeprecated(): When an argument is no longer available, you may want
///     to give the user this information instead of just saying "unknown
///     argument". So, just mark an argument as deprecated, then it will no
///     longer appear in the usage, and if the argument is used on the command
///     line, the proper error message is printed.<br>
///     If the argument was mandatory before, remove this flag. Setting a
///     deprecated argument to mandatory, or vice versa, will throw in
///     addArgument().
///   - setReplacedBy(): When an argument is replaced by another, you may want
///     to give the user this information instead of just saying "unknown
///     argument". So, just mark an argument as "replaced by", then it will no
///     longer appear in the usage, and if the argument is used on the command
///     line, the proper error message is printed.<br>
///     Internally the argument is handled like a deprecated argument, so
///     features related to deprecated arguments apply to replaced arguments
///     too.<br>
///     If the argument was mandatory before, remove this flag. Setting a
///     deprecated argument to mandatory, or vice versa, will throw in
///     addArgument().
///   - setAllowMixIncSet(): For destination type level counter, allows to mix
///     arguments that increment the value or assign a new value.
///   .
/// - Finally, when all arguments were specified, call evalArguments() to
///   actually evaluate the command line arguments.
/// - You can use this class to print a list of the arguments and their
///   descriptions with usage(). The arguments are printed in the order in which
///   they were added.
/// - You can extend arguments with your own checks. Simply implement a class
///   which implements the CheckBase interface, and pass an object of this class
///   to addCheck().
/// - In order to support other data types, you just need to implement a
///   conversion function which reads the value from a istream and stores it in
///   a variable of the corresponding type.<br>
///   Example interface: <code>istream& operator >>( istream& source, <type>& dest);</code>
///
/// When used together with the Application() template, use this class as base
/// class of your application main class, then evalArguments() is called
/// automatically. The arguments must be specified in the constructor of your
/// class then.
///
/// Please refer to the documentation for a complete description of all
/// features.
///
/// @todo  Don't use special member variables for control character handlers,
///        implement them as 'starting characters' in a general way, so that
///        afterwards also e.g. +\<argument\> is possible.
/// @todo  When using sub-groups, it should be possible to change the text
///        displayed for the h/help arguments.
/// @todo  It should be possible to specify the pre- and post-usage text for
///        sub-groups.
/// @todo  Also display checks like range, value-lists etc. in the usage.
/// @todo  Add handling for an argument like '--end-sub-group' which causes
///        the processing in a sub-group to end and continue in the calling
///        object.<br>
///        This could be used to make sure that an argument is handled by the
///        main object and not in the sub-group.
/// @todo  Additional flag for Handler: Sort arguments for usage.
/// @todo  Due to the fact that addArgument() does not return the Handler
///        object but the newly created TypedArg... object, it is not possible
///        to use function call chaining like boost::program_options does.<br>
///        To achieve something similar, the insertion operator could be
///        overloaded for the class Handler, allowing for a syntax like<br>
///        Handler  ah;<br>
///        ah << Argument( ...)->setIsMandatory()-> ...<br>
///           << Argument( ...)-> ...
/// @todo  Argument constraints: Value relations.
///        Support constraints like 'value of argument x must be less than value
///        of argument y', e.g. start time < end time.
/// @todo  Change the logic of addCheck(): If multiple checks are added, a value
///        is accepted if it matches at least one of these checks.
///        Since lower and upper bound are already combined in the range check,
///        I currently see no other need to specify two different checks that
///        should be and'ed.
/// @todo  To make usage of program arguments easier:
///        Argument that means "write all the following arguments into the
///        program arguments file", e.g. "--create-prog-args [<filename>]"
/// @todo  Due to the fact that the range handling already produces values with
///        the destination type, the existing check() methods cannot be applied
///        (they expect a string parameter). Is it necessary/possible to fix
///        this?
/// @todo  Add new range check that allows to specify a range string for the
///        allowed values. Maybe need to rename the existing range check. Or
///        simply replace it?
///        Problem: The new range check would then also produce values with the
///        destination type already ...
/// @todo  Maybe we want 'hidden argument groups'? Maybe this is not really
///        necessary, check what happens on a group where all arguments are
///        marked as hidden.
/// @todo  Pass the verbose flag to the assign methods and then print the
///        verbose output there. This will cover all cases and also allows e.g.
///        to print the second assignment if a pair is used.
/// @todo  Flag and/or argument that changes the processing: Process all
///        arguments and throw/exit at the end only. This would help to detect
///        multiple errors in the argument string.
/// @todo  Add support for arguments with +/- logic?<br>
///        Boolean flags with - would set the flag to \c false, with + it would
///        be set to \c true.<br>
///        What with other types? Maybe it would make sense to specify two
///        different handlers, one for - and one for +? Or one handler with two
///        different destinations, one for - and one for +?<b>
///        If +/- is distinguished on short arguments, what about long
///        arguments?
/// @todo  Refactor typed arg for std::vector so that any std container can be
///        used.
/// @todo  Similar solution that allows to use an std container with key/value
///        pairs.
/// @todo  Check comments of constraints classes (all_of).
///        All of: Use as dynamic constraint? Otherwise, all the arguments could
///        simply be mandatory.
/// @todo  Add feature to specify the behaviour when the same argument is used
///        multiple times (and cardinality is 1):<br>
///        Error/Exception (as is), store the first value (ignore additional
///        calls), store the last value.
/// @todo  Use different exit codes from evalArgumentErrorExit(), depending on
///        the type of the exception that was called.
/// @todo  Add pre- and post-argument list help texts also to argument handlers
///        used in a group?
/// @todo  Path created from parameter and ProjectPath as destination variable?
///
/// @since  0.2, 10.04.2016
class Handler
{
public:
   /// Type of the (storage handler of the) functions to call for control
   /// characters.
   using HandlerFunc = std::function< void()>;

   /// List of flags to control the behaviour of this class:
   enum HandleFlags
   {
      /// Allows the argument '-h' to print the usage of the program.
      hfHelpShort       = 0x01,
      /// Allows the argument '--help' to print the usage of the program.
      hfHelpLong        = hfHelpShort << 1,
      /// Allows the argument "--help-arg=<arg>" to get the usage of one
      /// specific argument.
      hfHelpArg         = hfHelpLong << 1,
      /// Allows the argument "--help-arg-full=<arg>" to get the usage of one
      /// specific argument, plus a description of all properties of the
      /// argument and its destination variable.
      hfHelpArgFull     = hfHelpArg << 1,
      /// Specifies to read arguments from the optional program arguments file
      /// before parsing the command line arguments.<br>
      /// File: $HOME/.progargs/\<progfilename\>.pa
      hfReadProgArg     = hfHelpArgFull  << 1,
      /// Set this when additional program arguments should be read from an
      /// environment variable. Default name of the environment variable is the
      /// name of the program file in uppercase letters.
      hfEnvVarArgs = hfReadProgArg << 1,
      /// Produces verbose output when a value is assigned to a variable.
      hfVerboseArgs     = hfEnvVarArgs << 1,
      /// Specifies that hidden arguments should be printed too in the usage.
      hfUsageHidden     = hfVerboseArgs << 1,
      /// Allows the argument '--print-hidden' to print the hidden arguments in
      /// the usage.
      hfArgHidden       = hfUsageHidden << 1,
      /// Specifies that deprecated arguments should be printed too in the usage.
      hfUsageDeprecated =  hfArgHidden << 1,
      /// Allows the argument '--print-deprecated' to print the deprecated
      /// arguments in he usage.
      hfArgDeprecated   = hfUsageDeprecated << 1,
      /// Only print the arguments with their short argument in the usage.
      hfUsageShort      = hfArgDeprecated << 1,
      /// Only print the arguments with their long argument in the usage.
      hfUsageLong       = hfUsageShort << 1,
      /// Adds the argument '--list-arg-vars' which, when used, prints the list
      /// of arguments and the names of the destination variables and their
      /// values.
      hfListArgVar      = hfUsageLong << 1,
      /// Special flag originally for testing: Don't exit after printing the
      /// usage.
      hfUsageCont       = hfListArgVar << 1,
      /// Activates the argument '--endvalues' that is used to signal the end of
      /// a separate value list.
      hfEndValues       = hfUsageCont << 1,
      /// Activates the argument '--list-arg-groups' which lists the names of
      /// all known argument groups.<br>
      /// If argument groups are used, set this argument when creating the
      /// Groups singleton object.
      hfListArgGroups   = hfEndValues << 1,
      /// This flag is set by the Groups class when it creates a Handler object.
      /// Don't use otherwise!
      hfInGroup         = hfListArgGroups << 1
   }; // HandleFlags

   /// List of possible positions for the additional output.
   enum class UsagePos
   {
      unused,       //!< Initialization value.
      beforeArgs,   //!< Position before the list of arguments.
      afterArgs     //!< Position after the list of arguments.
   }; // UsagePos

   /// List of possible settings for printing the usage:
   enum class UsageContents
   {
      all,         //!< Default: Display all arguments with their short and/or
                   //!< long argument keys.
      shortOnly,   //!< Display only those arguments with a short key.
      longOnly     //!< Display only those arguments with a long key.
   }; // UsageContents

   /// Make the type 'ValueMode' available through this class too.
   using ValueMode = detail::TypedArgBase::ValueMode;

   /// Set of all help arguments.
   static const int  AllHelp = hfHelpShort | hfHelpLong | hfHelpArg;
   /// Set of available standard/commonly used arguments.
   static const int  AllFlags = hfHelpShort | hfHelpLong | hfReadProgArg;
   /// Flags for testing/debugging the module itself.
   static const int  DebugFlags = hfVerboseArgs | hfListArgVar;
   /// Complete set of all available arguments.
   static const int  FullFlagSet = hfHelpShort | hfHelpLong | hfHelpArg
                                   | hfReadProgArg | hfEnvVarArgs | hfVerboseArgs
                                   | hfUsageHidden | hfArgHidden | hfListArgVar
                                   | hfUsageCont;

   /// (Default) Constructor.
   /// @param[in]  flagSet  The set of flags. See enum HandleFlags for a list of
   ///                      possible values.
   /// @param[in]  txt1     Optional pointer to the object to provide additional
   ///                      text for the usage.
   /// @param[in]  txt2     Optional pointer to the object to provide additional
   ///                      text for the usage.
   /// @since  0.3, 04.06.2016  (same interface, now implemented as delegating
   ///                           constructor)
   /// @since  0.2, 10.04.2016
   explicit Handler( int flagSet = hfHelpShort | hfHelpLong,
                     IUsageText* txt1 = nullptr,
                     IUsageText* txt2 = nullptr) noexcept( false);

   /// Constructor that allows to specify the output streams to write to.
   /// @param[in]  os        The stream to write normal output to.
   /// @param[in]  error_os  The stream to write error output to.
   /// @param[in]  flag_set  The set of flags. See enum HandleFlags for a list
   ///                       of possible values.
   /// @param[in]  txt1      Optional pointer to the object to provide
   ///                       additional text for the usage.
   /// @param[in]  txt2      Optional pointer to the object to provide
   ///                       additional text for the usage.
   /// @since  0.3, 04.06.2016  (added parameters for output streams)
   /// @since  0.2, 10.04.2016
   Handler( std::ostream& os, std::ostream& error_os,
            int flag_set = hfHelpShort | hfHelpLong,
            IUsageText* txt1 = nullptr,
            IUsageText* txt2 = nullptr) noexcept( false);

   /// Constructor to be used by a sub-group. Copies some settings from the main
   /// argument handler object.<br>
   /// It is possible to create a sub-group argument handler using one of the
   /// other constructors, but then the settings are of course not copied.<br>
   /// The following flags are ignored, the settings are taken from the main
   /// argument handler:<br>
   /// #hfReadProgArg, #hfVerboseArgs, #hfUsageHidden, #hfUsageShort,
   /// #hfUsageLong and #hfUsageCont.
   /// @param[in]  main_ah   The main argument handler to copy the settings
   ///                       from.
   /// @param[in]  flag_set  The set of flags. See enum HandleFlags for a list
   ///                       of possible values.
   /// @param[in]  txt1      Optional pointer to the object to provide
   ///                       additional text for the usage.
   /// @param[in]  txt2      Optional pointer to the object to provide
   ///                       additional text for the usage.
   /// @since  1.1.0, 04.12.2017
   Handler( Handler& main_ah, int flag_set, IUsageText* txt1 = nullptr,
            IUsageText* txt2 = nullptr) noexcept( false);

   /// Don't allow copying.
   Handler( const Handler&) = delete;
   /// Don't allow assignments.
   Handler& operator =( const Handler&) = delete;

   /// Destructor, deletes dynamically allocated objects.
   /// @since  0.2, 10.04.2016
   ~Handler();

   /// Activates the check for program arguments in an environment variable,
   /// plus allows to specify the name of the environment variable o use.<br>
   /// The default is the name of the program file, all in uppercase letters.
   ///
   /// @param[in]  env_var_name  Optional, the name of the environment variable.
   /// @since  x.y.z, 01.04.2019
   void checkEnvVarArgs( std::string env_var_name = "");

   /// Adds an argument with short and/or long arguments.<br>
   /// For positional arguments, i.e. arguments not preceeded by a an argument
   /// character/name, specify "-" as \a arg_spec.
   /// @param[in]  arg_spec  The arguments on the command line for this argument.
   /// @param[in]  dest      The object that handles the type-specific stuff.<br>
   ///                       Use the celma::prog_args::destination() template
   ///                       functions to obtain the correct object.
   /// @param[in]  desc      The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.16.0, 09.11.2017
   detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                      detail::TypedArgBase* dest,
                                      const std::string& desc);

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
   detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                      Handler& subGroup,
                                      const std::string& desc);

   /// Adds an argument that behaves like the -h/--help arguments. Use this if
   /// the help argument should e.g. be in another language.<br>
   /// The standard help arguments may still be set in the constructor, then
   /// both arguments can be used to get the usage displayed.
   ///
   /// @param[in]  arg_spec
   ///    The arguments on the command line for the help feature.
   /// @param[in]  desc
   ///    The description of this argument.
   /// @param[in]  txt1
   ///    Optional pointer to the object to provide additional text for the
   ///    usage.
   /// @param[in]  txt2
   ///    Optional pointer to the object to provide additional text for the
   ///    usage.
   /// @return
   ///    The object managing the argument, may be used to apply further
   ///    settings (normally not necessary).
   /// @since  0.10, 22.12.2016
   detail::TypedArgBase* addHelpArgument( const std::string& arg_spec,
                                          const std::string& desc,
                                          IUsageText* txt1 = nullptr,
                                          IUsageText* txt2 = nullptr);

   /// Adds an argument that takes the path/filename of an argument file as
   /// parameter.<br>
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
   detail::TypedArgBase* addArgumentFile( const std::string& arg_spec);

   /// Adds an argument that activates printing of hidden arguments in the
   /// usage.<br>
   /// Same as setting the flag #hfArgHidden, but allows to specify the
   /// argument and its description.
   /// @param[in]  arg_spec  The argument(s) on the command line for activating
   ///                       printing the hidden arguments.
   /// @param[in]  desc      Optional text for the description of the argument
   ///                       in the usage. If not set, the default description
   ///                       is used.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  1.1.0, 06.12.2017  (adapted to using usage parameters object)
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgumentPrintHidden( const std::string& arg_spec,
      const char* desc = nullptr);

   /// Adds an argument that activates printing of usage with arguments with
   /// short argument key only.
   /// @param[in]  arg_spec  The argument(s) on the command line for activating
   ///                       printing the usage with short arguments only.
   /// @param[in]  desc      Optional text for the description of the argument
   ///                       in the usage. If not set, the default description
   ///                       is used.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  1.1.0, 25.09.2017
   detail::TypedArgBase* addArgumentUsageShort( const std::string& arg_spec,
      const char* desc = nullptr);

   /// Adds an argument that activates printing of usage with arguments with
   /// long argument key only.
   /// @param[in]  arg_spec  The argument(s) on the command line for activating
   ///                       printing the usage with long arguments only.
   /// @param[in]  desc      Optional text for the description of the argument
   ///                       in the usage. If not set, the default description
   ///                       is used.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  1.1.0, 25.09.2017
   detail::TypedArgBase* addArgumentUsageLong( const std::string& arg_spec,
      const char* desc = nullptr);

   /// Adds an argument that prints the list of arguments, their destination
   /// variables and their values.<br>
   /// Same as setting the flag #hfListArgVar, but allows to specify the
   /// argument.
   /// @param[in]  arg_spec  The argument(s) on the command line for printing the
   ///                       arguments and their destination variables.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgumentListArgVars( const std::string& arg_spec);

   /// Adds an argument that prints the list of argument groups.<br>
   /// Same as setting the flag #hfListArgGroups, but allows to specify the
   /// argument.
   /// @param[in]  arg_spec  The argument(s) on the command line for printing the
   ///                       argument groups.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.13.1, 07.02.2017
   detail::TypedArgBase* addArgumentListArgGroups( const std::string& arg_spec);

   /// Adds an argument that can be used to mark the end of multiple, separate
   /// value list.
   /// @param[in]  arg_spec  The argument(s) on the command line for marking the
   ///                       end of a separate value list.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgumentEndValues( const std::string& arg_spec);

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
   detail::TypedArgBase* addArgumentHelpArgument( const std::string& arg_spec,
      bool full = false);

   /// Specifies the callback function for a control argument.<br>
   /// If no handler is defined for a control character, it is treated as error
   /// when found in an argument list.
   /// @param[in]  ctrlChar  The control character to specify the handler for.
   /// @param[in]  hf        The handler to call when the control character is
   ///                       detected on the argument list.
   /// @since  0.2, 10.04.2016
   void addControlHandler( char ctrlChar, HandlerFunc hf) noexcept( false);

   /// Specifies the line length to use when printing the usage.
   /// @param[in]  useLen  The new line length to use.<br>
   ///                     The value must be in the range 60 <= useLen < 240.
   /// @since  0.2, 10.04.2016
   void setUsageLineLength( int useLen);

   /// Re-sets the usage parameters to use for displaying the usage.
   /// @param[in]  usage_params  Shared object to share for the usage parameters.
   /// @since  1.1.0, 04.12.2017
   void setUsageParams( detail::shared_usage_params_t& usage_params);

   /// Adds a constraint to the argument handler itself that affects multiple
   /// arguments.<br>
   /// The arguments specified in the constraint must already be defined.
   /// @param[in]  ic  Pointer to the object that handles the constraint.
   /// @since  0.2, 10.04.2016
   void addConstraint( detail::IConstraint* ic) noexcept( false);

   /// Iterates over the list of arguments and their values and stores the
   /// values in the corresponding destination variables.<br>
   /// The function also checks for missing, mandatory arguments, arguments
   /// wrongly used without a value etc. If an invalid value is passed for an
   /// argument, or if a mandatory argument is missing etc., an exception is
   /// thrown.
   /// @param[in]  argc    Number of arguments passed to the process.
   /// @param[in]  argv[]  List of argument strings.
   /// @throw  Exception as described above.
   /// @since  0.2, 10.04.2016
   void evalArguments( int argc, char* argv[]) noexcept( false);

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
   void evalArgumentsErrorExit( int argc, char* argv[],
                                const std::string& prefix);

   /// After calling evalArguments(), prints the list of arguments that were
   /// used and the values that were set.
   ///
   /// @param[in]  contents_set
   ///    Set of flags that specify the contents of the summary to print.
   /// @param[out]  os
   ///    The stream to write the summary to.
   /// @since 1.8.0, 25.07.2018 (version with less parameters)
   void printSummary( sumoptset_t contents_set = sumoptset_t(), std::ostream& os = std::cout);

   /// Same as before, but only the output stream to write to can/must be
   /// specified.
   ///
   /// @param[out]  os  The stream to write the summary to.
   /// @since 1.8.0, 26.07.2018 (version with even less parameters)
   void printSummary( std::ostream&);

   /// Helps to determine if an object is a 'plain' Handler object or a
   /// ValueHandler object.
   /// @return  Always \c false for objects of this class.
   /// @since  0.14.0, 21.02.2017
   virtual bool isValueHandler() const;

   /// Returns this object if it is a ValueHandler object, otherwise throws.
   /// @return  \c this object if it is a ValueHandler object, for objects of
   ///          the base class Handler throws.
   /// @since  0.14.0, 15.03.2017
   virtual ValueHandler* getValueHandlerObj() noexcept( false);

   /// Returns pointer to the base type of the object that handles the specified
   /// argument.
   /// @param[in]  arg_spec  The short and/or long arguments keys.
   /// @return  Pointer to the object handling the specified argument.
   /// @since  0.14.0, 16.03.2017
   detail::TypedArgBase* getArgHandler( const std::string& arg_spec)
      noexcept( false);

protected:
	/// Classes need access to internals.
   friend class detail::ArgumentContainer;
   friend class Groups;

   /// Function call result for evalSingleArgument():
   enum class ArgResult
   {
      unknown,    //!< Unknown argument for this instance (try with next).
      consumed,   //!< Argument handled by this instance, proceed with next
                  //!< argument.
      last        //!< Found an argument with value mode "command".
   };

   // functions needed by the Groups class

   /// Compares the arguments defined in this object with those in \a otherAH
   /// and throws an exception if duplicates are detected.
   /// @param[in]  ownName    The symbolic name of this objects arguments.
   /// @param[in]  otherName  The symbolic name of the the other objects
   ///                        arguments.
   /// @param[in]  otherAH    The other object to check the argument list
   ///                        against.
   /// @since  0.2, 10.04.2016
   void crossCheckArguments( const std::string ownName,
                             const std::string& otherName,
                             const Handler& otherAH) const noexcept( false);

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
   ArgResult evalSingleArgument( detail::ArgListParser::const_iterator& ai,
                                 const detail::ArgListParser::const_iterator& end);

   /// Checks if all mandatory arguments were set, and the cardinality
   /// requirements were met.
   /// @since  0.2, 10.04.2016
   void checkMissingMandatoryCardinality() const;

   /// Checks if the specified argument is already used.
   /// @param[in]  argChar  The argument character to check.
   /// @return  \c true if the argument is already in use.
   /// @since  0.2, 10.04.2016
   bool argumentExists( char argChar) const;

   /// Checks if the specified argument is already used.
   /// @param[in]  argString  The argument string to check.
   /// @return  \c true if the argument is already in use.
   /// @since  0.2, 10.04.2016
   bool argumentExists( const std::string& argString) const;

   /// After calling evalArguments(), prints the list of arguments that were
   /// used and the values that were set.
   ///
   /// @param[in]  contents_set
   ///    Set of flags that specify the contents of the summary to print.
   /// @param[out]  os
   ///    The stream to write the summary to.
   /// @param[in]   standalone
   ///    If set, prints a title and a line if no arguments were found,
   ///    otherwise only prints the list of arguments used (or nothing).
   /// @param[in]   arg_prefix
   ///    Specifies the prefix for the arguments of this handler. Used when the
   ///    argument handler handles the arguments of a sub-group.
   /// @since 1.8.0, 03.07.2018
   void printSummary( sumoptset_t contents_set, std::ostream& os,
      bool standalone, const char* arg_prefix) const;

   /// Prints the usage of this class.
   /// @param[out]  os  The stream to print to.
   /// @param[in]   ah  The object to print the data of.
   /// @return  The stream.
   /// @since  0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, const Handler& ah);

private:
   /// The argument key to use to handle positional arguments.
   static const detail::ArgumentKey  mPosKey;

   /// Type of the container to store the global constrainst in.
   using ConstraintCont = std::vector< detail::IConstraint*>;

   /// Called by the constructors to evaluate the set of flags given.
   ///
   /// @param[in]  flag_set
   ///    The set of flags to set.
   /// @param[in]  txt1
   ///    Optional pointer to the object to provide additional text for the
   ///    usage.
   /// @param[in]  txt2
   ///    Optional pointer to the object to provide additional text for the
   ///    usage.
   /// @since
   ///    1.11.0, 16.02.2018
   void handleStartFlags( int flag_set, IUsageText* txt1, IUsageText* txt2)
      noexcept( false);

   /// Function to print the usage of a program (when requested through the
   /// arguments). The additional parameters allow to print additional
   /// information.
   ///
   /// @param[in]  txt1
   ///    Pointer to the object that prints the first text.
   /// @param[in]  txt2
   ///    Pointer to the object that prints the second text.
   /// @since  0.2, 10.04.2016
   void usage( IUsageText* txt1, IUsageText* txt2) noexcept( false);

   /// Sets the flag that this object is used as sub-group handler.
   /// @since  0.2, 10.04.2016
   void setIsSubGroupHandler();

   /// Finally: Handle an identified argument from the command line.
   /// @param[in]      key  The argument (character/short or long).
   /// @param[in,out]  ai   The iterator pointing to the current argument.<br>
   ///                      May be increased here (for values or argument
   ///                      groups).
   /// @param[in]      end  Iterator pointing to the end of the argument list.
   /// @return  Result of handling the current argument.
   /// @since  0.15.0, 17.07.2017  (only ArgumentKey as parameter, no template
   ///                             anymore)
   /// @since  0.2, 10.04.2016
   ArgResult processArg( const detail::ArgumentKey& key,
                         detail::ArgListParser::const_iterator& ai,
                         const detail::ArgListParser::const_iterator& end)
                       noexcept( false);

   /// Tries to open the file with the program's name and read the arguments
   /// from this file.
   /// @param[in]  arg0  The (path and) name of the program file.
   /// @since  0.2, 10.04.2016
   void readEvalFileArguments( const char* arg0);

   /// If no environment variable name is given, the name of the program file is
   /// used. Then check if an environment variable with this name exists and is
   /// not empty. If so the evaluate the program arguments from the variable.
   ///
   /// @param[in]  arg0  The (path and) name of the program file.
   /// @since  x.y.z, 01.04.2019
   void checkReadEnvVarArgs( const char* arg0);

   /// Function to read arguments from a file.
   /// @param[in]  pathFilename   The (path and) file name to read from.
   /// @param[in]  reportMissing  If set, the file should exist, an exception is
   ///                            thrown if the file could not be read.
   /// @since  0.2, 10.04.2016
   void readArgumentFile( const std::string& pathFilename, bool reportMissing);

   /// Prints the list of arguments and their destination variables.
   /// @since  0.2, 10.04.2016
   void listArgVars();

   /// Prints the list of argument groups.
   /// @since  0.13.1, 07.02.2017
   void listArgGroups();

   /// Called to mark the end of a value list: Sets #mpLastArg to NULL.
   ///
   /// @since  0.2, 10.04.2016
   void endValueList();

   /// Searches if the given argment key belongs to a known argument, and if so
   /// prints its usage.<br>
   /// If the argument key is unknown, an error message is printed.<br>
   /// At the end, the function calls exit(), unless "usage continues" is set.
   ///
   /// @param[in]  help_arg_key
   ///    The key of the argument to print the usage of.
   /// @param[in]  full
   ///    If set, also prints information about the argument and its destination
   ///    variable.
   /// @since  1.14.0, 25.09.2018
   void helpArgument( const std::string& help_arg_key, bool full);

   /// Iterates over the arguments and evaluates them.
   /// @param[in]  alp  The parser object used to access the arguments.
   /// @since  0.2, 10.04.2016
   void iterateArguments( detail::ArgListParser& alp) noexcept( false);

   /// Standard procedure for adding an argument handling object.
   /// @param[in]  ah_obj  Pointer to the object that handles the argument.
   /// @param[in]  key     The argument key: short and/or long argument.
   /// @param[in]  desc    The description of the argument.
   /// @return  Pointer to the passed argument handling object.
   /// @since  0.15.0, 13.07.2017  (take ArgumentKey instead of string)
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* internAddArgument( detail::TypedArgBase* ah_obj,
                                            const detail::ArgumentKey& key,
                                            const std::string& desc);

   /// Checks each argument in the list if it is a valid/known argument.<br>
   /// If the argument specification in the list does not match the original
   /// specification of the argument (short and/or long), it is replaced in the
   /// \a constraint_arg_list.
   /// @param[in]  constraint_arg_list  The list of arguments to check.
   /// @return  \c true if all arguments in the list are valid.
   /// @since  0.2, 10.04.2016
   bool validArguments( std::string& constraint_arg_list) const;

   /// Checks if the provided argument specification contains an invalid
   /// combination, i.e. a short and a long argument that are already used on
   /// two different, existing arguments.
   /// @param[in]  key  The argument specification to test.
   /// @return  \c true if the given combination is invalid.
   /// @since  0.15.0, 06.08.2017
   bool invalidCombination( const detail::ArgumentKey& key) const
      noexcept( false);

   /// When an argument was identified, passes the argument specification to all
   /// global constraint objects to check if a constraint is violated.
   /// @param[in]  key  The argument specification.
   /// @since  0.2, 10.04.2016
   void executeGlobalConstraints( const detail::ArgumentKey& key);

   /// After all arguments were processed, call this method to iterate over all
   /// global constraints to check e.g. if a required argument is missing.
   /// @since  0.2, 10.04.2016
   void checkGlobalConstraints() const;

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
   void handleIdentifiedArg( detail::TypedArgBase* hdl,
                             const detail::ArgumentKey& key,
                             const std::string& value = "");

   /// Stream to write output to.
   std::ostream&                  mOutput;
   /// Stream to write error output to.
   std::ostream&                  mErrorOutput;
   /// Set when the flag #hfReadProgArg was passed to the constructor. Then the
   /// default program arguments file is read before the command line arguments
   /// are evaluated.
   const bool                     mReadProgramArguments;
   /// Set when the flag #hfVerboseArgs was passed to the constructor. Produces
   /// verbose output when a value is assigned to a variable.
   const bool                     mVerbose;
   /// Set when the flag #hfUsageCont was passed to the constructor. Specifies
   /// that the program flow should continue after printing the usage.
   const bool                     mUsageContinues;
   /// Set when the usage was printed.<br>
   /// Needed together with the flag #mUsageContinues to bypass end-of-arguments
   /// checks so that evalArgument() can return.
   bool                           mUsagePrinted = false;
   /// Defines the contents of the usage.
   detail::shared_usage_params_t  mpUsageParams;
   /// The (top-level) arguments known by this class.
   detail::ArgumentContainer      mArguments;
   /// Argument sub-groups.
   detail::ArgumentContainer      mSubGroupArgs;
   /// Storage for the arguments and their descriptions.
   detail::ArgumentDesc           mDescription;
   /// Function called for an opening bracket '('.
   HandlerFunc                    mpOpeningBracketHdlr;
   /// Function called for a closing bracket ')'.
   HandlerFunc                    mpClosingBracketHdlr;
   /// Function called for an exclamation mark '!'.
   HandlerFunc                    mpExclamationMarkHdlr;
   /// Set when this object is used as argument handler for a sub-group.
   bool                           mIsSubGroupHandler = false;
   /// The current constraints, dynamically created through the arguments that
   /// were processed so far.
   detail::ConstraintContainer    mConstraints;
   /// Global constraints, i.e. constraints that affect multiple arguments
   /// and/or are not triggered by a specific argument.
   ConstraintCont                 mGlobalConstraints;
   /// Set when the flag #hfEnvVarArgs is passed to the constructor, or when
   /// checkEnvVarArgs() is called: Checks for additional program arguments in
   /// the given environment variable.
   bool                           mCheckEnvVar = false;
   /// Contains the name of the environment variable to check for additional
   /// program arguments. By default, the name of the program file is used, all
   /// in uppercase letters.
   std::string                    mEnvVarName;

   /// Pointer to the last argument handler that was used. Needed for
   /// processing multiple, separate values.
   detail::TypedArgBase*          mpLastArg = nullptr;

   /// List of values/flags for the different read mode.<br>
   /// The flags for "reading from file" and "processing environment variable"
   /// may be set in parallel.
   enum ReadMode
   {
      commandLine,   //!< Normal evaluation of command line arguments.
      file,          //!< Flag/Bit set when evaluating an argument file.
      envVar         //!< Flag/Bit set when evaluating an environment variable.
   };

   /// Reading arguments from a file or an environment variable should not
   /// influence the cardinality checks, i.e. it should be possible to overwrite
   /// a value from a file without triggering a 'too many values' exception.<br>
   /// Since arguments from the environment variable could trigger reading an
   /// argument file, these two states must be managd separately.
   uint8_t                        mReadMode = ReadMode::commandLine;
   /// Flag, set when this argument handler object was created by a Groups
   /// object.
   bool                           mUsedByGroup;

}; // Handler


// inlined methods
// ===============


inline detail::TypedArgBase*
   Handler::addArgument( const std::string& arg_spec,
                         detail::TypedArgBase* dest,
                         const std::string& desc)
{
   const detail::ArgumentKey  key( arg_spec);
   dest->setKey( key);
   return internAddArgument( dest, key, desc);
} // Handler::addArgument


inline void Handler::setUsageLineLength( int useLen)
{
   mDescription.setLineLength( useLen);
   mSubGroupArgs.setUsageLineLength( useLen);
} // Handler::setUsageLineLength


inline void Handler::setUsageParams( detail::shared_usage_params_t& usage_params)
{
   mpUsageParams = usage_params;
} // Handler::setUsageParams


inline void Handler::setIsSubGroupHandler()
{
   mIsSubGroupHandler = true;
} // Handler::setIsSubGroupHandler


inline void Handler::printSummary( sumoptset_t contents_set, std::ostream& os)
{
   printSummary( contents_set, os, true, nullptr);
} // Handler::printSummary


inline void Handler::printSummary( std::ostream& os)
{
   printSummary( sumoptset_t(), os, true, nullptr);
} // Handler::printSummary


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_HANDLER_HPP


// =====  END OF handler.hpp  =====

