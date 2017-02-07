
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


#ifndef CELMA_PROG_ARGS_HANDLER_HPP
#define CELMA_PROG_ARGS_HANDLER_HPP


#include <functional>
#include <ostream>
#include <string>
#include <vector>

#include "celma/common/check_assign.hpp"
#include "celma/common/range_dest.hpp"

#include "celma/prog_args/detail/arg_list_parser.hpp"
#include "celma/prog_args/detail/argument_container.hpp"
#include "celma/prog_args/detail/argument_desc.hpp"
#include "celma/prog_args/detail/constraint_container.hpp"
#include "celma/prog_args/detail/typed_arg_callable.hpp"
#include "celma/prog_args/detail/typed_arg_callable_value.hpp"
#include "celma/prog_args/detail/typed_arg.hpp"
#include "celma/prog_args/detail/typed_arg_pair.hpp"
#include "celma/prog_args/detail/typed_arg_range.hpp"
#include "celma/prog_args/detail/typed_arg_sub_group.hpp"


namespace celma { namespace prog_args {


class IUsageText;
class Groups;


/// Class to store all command line argument descriptions as well as the
/// destination variables to store the values in.<br>
/// To set up an argument handler, simply follow these steps:
/// - Create object, specify the HandleFlags to get the desired behaviour.
/// - For each argument, call addArgument() with the strings that specify the
///   short and/or long arguments, the destination variable to store the value
///   in when the argument is used (using the macro DEST_VAR()) plus a description
///   of the argument and its value (for the usage).<br>
///   The short (character) and long argument format are order independent in
///   the argument string.
///   Example:  <code>addArgument( "s,silent", DEST_VAR( mRunSilent), "Set to suppress output");</code>
/// - For free (i.e. positional) arguments, simply pass an empty string for the arguments:<br>
///   Example:  <code>addArgument( "", DEST_VAR( mHostname), "The name of the host to connect to");</code>
/// - For each argument, you can specify if it requires a value or not.<br>
///   Internally, the following defaults are applied:
///   - Arguments used to set a boolean variable don't accept a value.
///   - All other arguments require a value.
///   .
///   To change this 'value mode', call the function setValueMode() with the
///   desired value.<br>
///   Example: <code>addArgument( "v,verbose-level", DEST_VAR( mRunSilent), "Specifies the verbose level, if set without value default is 'low'")->setValueMode( vmOptional);</code>
/// - Additionally you can use the following modifiers for each argument to
///   further specify the handling of the argument and its value:
///   - setIsMandatory(): specifies that this argument is mandatory
///   - addCheck(): Allows to add a value check. Possible checks are
///     - lower: Lower limit for values to accept (inclusive).
///     - upper: Upper limit for values to accept (exclusive).
///     - range: Range of values for scalar types to accept.
///     - values: List of values to accept.
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
///   .
///   It is possible to add multiple checks to the same argument. In this case,
///   a value must be accepted by all checks. The checks are executed in the
///   order in which they were added.<br>
///   Example:  <code>addArgument( "f,factor>", DEST_VAR( myFactor), "Factor")->addCheck( range( 1.0, 100.0));</code>
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
/// @todo  Arguments that means: Everything that follows should not be treated
///        as real program arguments anymore.<br>
///        Example (here: first argument without a -):
///           cmd [options ...] \<servername\> \<cmd\> [args ...]
///        All following arguments are stored in the string provided with this
///        parameter.
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
/// @todo  For destination type vector: Add flag/feature that the contents of
///        the vector should be cleared before the first value from the command
///        line is assigned.
///        Idea: vector is filled with default value(s), if the argument is
///        used the default should be replaced by the new values.
/// @todo  Clean up the interface by removing all special addArgument()s for
///        free values and
///        a) simply document the case that an empty string should be passed
///        b) and/or provide a constant 'free_value' (or so) that can be used.
/// @todo  Instead of having containers with short and/or the long argument as
///        key, and multiple places to split an argument specification string
///        into short and long string: Call ArgSpec, takes the string as
///        parameter, stores it internally and splits it into short and/or long
///        argument, finally can be used for comparison etc.
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
/// @todo  Add test-feature: Process all arguments, print all errors.
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
   typedef std::function< void()>  HandlerFunc;

   /// List of flags to control the behaviour of this class:
   enum HandleFlags
   {
      /// Allows the argument '-h' to print the usage of the program.
      hfHelpShort     = 0x01,
      /// Allows the argument '--help' to print the usage of the program.
      hfHelpLong      = hfHelpShort << 1,
      /// Specifies to read arguments from the optional program arguments file
      /// before parsing the command line arguments.<br>
      /// File: $HOME/.progargs/\<progfilename\>.pa
      hfReadProgArg   = hfHelpLong  << 1,
      /// Produces verbose output when a value is assigned to a variable.
      hfVerboseArgs   = hfReadProgArg << 1,
      /// Specifies that hidden arguments should be printed too in the usage.
      hfUsageHidden   = hfVerboseArgs << 1,
      /// Allows the argument '--print-hidden' to print the hidden arguments in
      /// the usage.
      hfArgHidden     = hfUsageHidden << 1,
      /// Adds the argument '--list-arg-vars' which, when used, prints the list
      /// of arguments and the names of the destination variables and their
      /// values.
      hfListArgVar    = hfArgHidden << 1,
      /// Special flag originally for testing: Don't exit after printing the
      /// usage.
      hfUsageCont     = hfListArgVar << 1,
      /// Activates the argument '--endvalues' that is used to signal the end of
      /// a separate value list.
      hfEndValues     = hfUsageCont << 1,
      /// Activates the argument '--list-arg-groups' which lists the names of
      /// all known argument groups.<br>
      /// If argument groups are used, set this argument when creating the
      /// Groups singleton object.
      hfListArgGroups = hfEndValues << 1,
      /// This flag is set by the Groups class when it creates a Handler object.
      /// Don't use otherwise!
      hfInGroup       = hfListArgGroups << 1
   }; // HandleFlags

   /// List of possible positions for the additional output 
   enum class UsagePos
   {
      unused,       //!< Initialization value.
      beforeArgs,   //!< Position before the list of arguments.
      afterArgs     //!< Position after the list of arguments.
   }; // UsagePos

   /// Make the type 'ValueMode' available through this class too.
   typedef detail::TypedArgBase::ValueMode  ValueMode;

   /// Set of all help arguments.
   static const int  AllHelp = hfHelpShort | hfHelpLong;
   /// Set of available standard/commonly used arguments.
   static const int  AllFlags = hfHelpShort | hfHelpLong | hfReadProgArg;
   /// Flags for testing/debugging the module itself.
   static const int  DebugFlags = hfVerboseArgs | hfListArgVar;
   /// Complete set of all available arguments.
   static const int  FullFlagSet = hfHelpShort | hfHelpLong | hfReadProgArg |
                                   hfVerboseArgs | hfUsageHidden | hfArgHidden |
                                   hfListArgVar | hfUsageCont;

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
   explicit Handler( int flagSet = hfHelpShort | hfHelpLong,
                     IUsageText* txt1 = nullptr,
                     IUsageText* txt2 = nullptr);

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
            IUsageText* txt2 = nullptr);

   /// Destructor, deletes dynamically allocated objects.
   /// @since  0.2, 10.04.2016
   ~Handler();

   /// Adds a single-value argument.
   /// @tparam  T  The native type of the variable to store the value in.
   /// @param[in]  arg_spec  The arguments on the command line for this argument.
   /// @param[in]  dest      The variable to store the value in.
   /// @param[in]  vname     The name of the variable to store the value in.<br>
   ///                       Used for error reporting.
   /// @param[in]  desc      The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   template< typename T>
      detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                         T& dest,
                                         const std::string vname,
                                         const std::string& desc);

   /// Adds a single-value argument where an additional value is set on a
   /// second variable when the parameter is used.
   /// @tparam  T1  The native type of the variable to store the argument value in.
   /// @tparam  T2  The native type of the second variable.
   /// @param[in]  arg_spec  The arguments on the command line for this argument.
   /// @param[in]  dest1     The variable to store the argument value in.
   /// @param[in]  vname1    The name of the variable to store the argument value
   ///                       in.<br>
   ///                       Used for error reporting.
   /// @param[in]  dest2     The variable to store the given value in.
   /// @param[in]  vname2    The name of the variable to store the given value in.
   /// @param[in]  value2    The value to store in the second variable.
   /// @param[in]  desc      The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   template< typename T1, typename T2>
      detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                         T1& dest1, const std::string vname1,
                                         T2& dest2, const std::string vname2,
                                         const T2& value2,
                                         const std::string& desc);

   /// Adds a free, single-value argument.
   /// @tparam  T  The native type of the variable to store the value in.
   /// @param[in]  dest   The variable to store the value in.
   /// @param[in]  vname  The name of the variable to store the value in.<br>
   ///                    Used for error reporting.
   /// @param[in]  desc   The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   template< typename T>
      detail::TypedArgBase* addArgument( T& dest,
                                         const std::string vname,
                                         const std::string& desc);

   /// Adds a multi-value argument that supports a range definition string for
   /// the values.
   /// @tparam  T  The native type of the variable to store the value(s) in.
   /// @tparam  C  The type of the container used to store the values in.
   /// @param[in]  arg_spec  The arguments on the command line for this argument.
   /// @param[in]  dest      The variable to store the value(s) in.
   /// @param[in]  vname     The name of the variable to store the value in.<br>
   ///                       Used for error reporting.
   /// @param[in]  desc      The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   template< typename T, typename C>
      detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                         const common::RangeDest< T, C>& dest,
                                         const std::string vname,
                                         const std::string& desc);

   /// Adds a free, multi-value argument that supports a range definition string
   /// for the values.
   /// @tparam  T  The native type of the variable to store the value(s) in.
   /// @tparam  C  The type of the container used to store the values in.
   /// @param[in]  dest   The variable to store the value(s) in.
   /// @param[in]  vname  The name of the variable to store the value in.<br>
   ///                    Used for error reporting.
   /// @param[in]  desc   The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   template< typename T, typename C>
      detail::TypedArgBase* addArgument( const common::RangeDest< T, C>& dest,
                                         const std::string vname,
                                         const std::string& desc);

   /// Adds an argument handler function that is called when an argument that
   /// does not accept any value is set.
   /// @param[in]  arg_spec  The arguments on the command line for this argument.
   /// @param[in]  fun       The function to call for this argument.<br>
   ///                       Use the macros DEST_FUNCTION or DEST_METHOD to
   ///                       easily set up the correct call.
   /// @param[in]  fname     The name of the function to call.<br>
   ///                       Used for error reporting.
   /// @param[in]  desc      The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                      detail::ArgHandlerCallable fun,
                                      const std::string fname,
                                      const std::string& desc);

   /// Adds an argument handler function that is called when an argument that
   /// may accept or requires a parameter is set.<br>
   /// Due to ambiguity problems there is no addArgument() version for using a
   /// free value for a callable. But you can achieve this easily by passing an
   /// empty string ("") as \a arg_spec.
   /// @param[in]  arg_spec     The arguments on the command line for this
   ///                          argument.
   /// @param[in]  fun          The function to call for this argument.<br>
   ///                          This function must take an std::string as
   ///                          parameter.<br>
   ///                          Use the macros DEST_FUNCTION_VALUE or
   ///                          DEST_METHOD_VALUE to easily set up the correct
   ///                          call.
   /// @param[in]  fname        The name of the function to call.<br>
   ///                          Used for error reporting.
   /// @param[in]  takes_value  Dummy parameter used to distinguish from the
   ///                          non-value variant.
   /// @param[in]  desc         The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                      detail::ArgHandlerCallableValue fun,
                                      const std::string fname,
                                      bool takes_value,
                                      const std::string& desc);

   /// Adds a sub-group.<br>
   /// Note: Theoretically we could pass the object by reference, but then the
   /// compiler cannot distinguish anymore between this function and the variant
   /// to add an argument resulting in a function call.
   /// @param[in]  arg_spec  The arguments on the command line to enter/start
   ///                       the sub-group.
   /// @param[in]  subGroup  The object to handle the sub-group arguments.
   /// @param[in]  desc      The description of this sub-group argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgument( const std::string& arg_spec,
                                      Handler* subGroup,
                                      const std::string& desc);

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
   detail::TypedArgBase* addHelpArgument( const std::string& arg_spec,
                                          const std::string& desc,
                                          IUsageText* txt1 = nullptr,
                                          IUsageText* txt2 = nullptr);

   /// Adds an argument that takes the path/filename of an argument file as
   /// parameter.
   /// @param[in]  arg_spec  The arguments on the command line for specifying the
   ///                       file with the arguments.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgumentFile( const std::string& arg_spec);

   /// Adds an argument that activates printing of hidden arguments in the usage.<br>
   /// Same as setting the flag #hfArgHidden, but allows to specify the
   /// argument.
   /// @param[in]  arg_spec  The argument(s) on the command line for activating
   ///                       printing the hidden arguments.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* addArgumentPrintHidden( const std::string& arg_spec);

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

   /// Adds an argument with a custom destination type.
   /// @tparam  C  The custom class used to handle variables of the custom
   ///             destination type. This class must be derived from the class
   ///             TypedArgBase.
   /// @tparam  T  The custom type of the destination variable to handle.
   /// @param[in]  arg_spec  The arguments on the command line for this argument.
   /// @param[in]  dest      The variable to store the value(s) in.
   /// @param[in]  vname     The name of the variable to store the value in.<br>
   ///                       Used for error reporting.
   /// @param[in]  desc      The description of this argument.
   /// @return  The object managing this argument, may be used to apply further
   ///          settings.
   /// @since  0.2, 10.04.2016
   template< typename C, typename T>
      detail::TypedArgBase* addCustomArgument( const std::string& arg_spec,
                                               T& dest,
                                               const std::string vname,
                                               const std::string& desc);

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

protected:
	/// Class needs access to internals.
   friend class Groups;

   /// Function call result for evalSingleArgument():
   enum class ArgResult
   {
      unknown,   //!< Unknown argument for this instance (try with next).
      consumed   //!< Argument handled by this instance, proceed with next
                 //!< argument.
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

   /// Checks and sets the maximum argument length, needed to format the usage.
   /// @param[in,out]  maxArgLen  Maximum argument length as needed so far, may
   ///                            be increased if this class contains longer
   ///                            arguments.
   /// @since  0.2, 10.04.2016
   void checkMaxArgLen( size_t& maxArgLen) const;

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

   /// Prints the usage of this class.
   /// @param[out]  os  The stream to print to.
   /// @param[in]   ah  The object to print the data of.
   /// @return  The stream.
   /// @since  0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, const Handler& ah);

private:
   /// Type of the container to store the global constrainst in.
   typedef std::vector< detail::IConstraint*>  ConstraintCont;

   /// Don't allow copying.
   Handler( const Handler&) = delete;
   /// Don't allow assignments.
   Handler& operator =( const Handler&) = delete;

   /// Function to print the usage of a program (when requested through the
   /// arguments). The additional parameters allow to print additional
   /// information.
   /// @param[in]  txt1  Pointer to the object that prints the first text.
   /// @param[in]  txt2  Pointer to the object that prints the second text.
   /// @since  0.2, 10.04.2016
   void usage( IUsageText* txt1, IUsageText* txt2);

   /// Sets the flag that this object is used as sub-group handler.
   /// @since  0.2, 10.04.2016
   void setIsSubGroupHandler();

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
      ArgResult processArg( const T& arg, const std::string& argString,
                            detail::ArgListParser::const_iterator& ai,
                            const detail::ArgListParser::const_iterator& end)
                          noexcept( false);

   /// Tries to open the file with the program's name and read the arguments
   /// from this file.
   /// @param[in]  arg0  The (path and) name of the program file.
   /// @since  0.2, 10.04.2016
   void readEvalFileArguments( const char* arg0);

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

   /// Called to mark the end of a value list: Sets mpLastArg to NULL.
   /// @since  0.2, 10.04.2016
   void endValueList();

   /// Iterates over the arguments and evaluates them.
   /// @param[in]  alp  The parser object used to access the arguments.
   /// @since  0.2, 10.04.2016
   void iterateArguments( detail::ArgListParser& alp) noexcept( false);

   /// Standard procedure for adding an argument handling object.
   /// @param[in]  ah_obj    Pointer to the object that handles the argument.
   /// @param[in]  arg_spec  The specification of the argument.
   /// @param[in]  desc      The description of the argument.
   /// @return  Pointer to the passed argument handling object.
   /// @since  0.2, 10.04.2016
   detail::TypedArgBase* internAddArgument( detail::TypedArgBase* ah_obj,
                                            const std::string& arg_spec,
                                            const std::string& desc);

   /// Checks each argument in the list if it is a valid/known argument.<br>
   /// If the argument specification in the list does not match the original
   /// specification of the argument (short and/or long), it is replaced in the
   /// \a constraint_arg_list.
   /// @param[in]  constraint_arg_list  .
   /// @return  .
   /// @since  0.2, 10.04.2016
   bool validArguments( std::string& constraint_arg_list) const;

   /// When an argument was identified, passes the argument specification to all
   /// global constraint objects to check if a constraint is violated.
   /// @param[in]  arg_spec  The argument specification.
   /// @since  0.2, 10.04.2016
   void executeGlobalConstraints( const std::string& arg_spec);

   /// After all arguments were processed, call this method to iterate over all
   /// global constraints to check e.g. if a required argument is missing.
   /// @since  0.2, 10.04.2016
   void checkGlobalConstraints() const;

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
   void handleIdentifiedArg( detail::TypedArgBase* hdl,
                             const std::string& arg_spec,
                             const std::string& value = "");

   /// Stream to write output to.
   std::ostream&                mOutput;
   /// Stream to write error output to.
   std::ostream&                mErrorOutput;
   /// Set when the flag #hfReadProgArg was passed to the constructor. Then the
   /// default program arguments file is read before the command line arguments
   /// are evaluated.
   const bool                   mReadProgramArguments;
   /// Set when the flag #hfVerboseArgs was passed to the constructor. Produces
   /// verbose output when a value is assigned to a variable.
   const bool                   mVerbose;
   /// Set when the flag #hfUsageHidden was passed to the constructor. Specifies
   /// if hidden arguments should be printed in the usage or not.
   bool                         mPrintHidden;
   /// Set when the flag #hfUsageCont was passed to the constructor. Specifies
   /// that the program flow should continue after printing the usage.
   const bool                   mUsageContinues;
   /// Set when the usage was printed.<br>
   /// Needed together with the flag #mUsageContinues to bypass end-of-arguments
   /// checks so that evalArgument() can return.
   bool                         mUsagePrinted = false;
   /// The (top-level) arguments known by this class.
   detail::ArgumentContainer    mArguments;
   /// Argument sub-groups.
   detail::ArgumentContainer    mSubGroupArgs;
   /// Storage for the arguments and their descriptions.
   detail::ArgumentDesc         mDescription;
   /// Function called for an opening bracket '('.
   HandlerFunc                  mpOpeningBracketHdlr;
   /// Function called for a closing bracket ')'.
   HandlerFunc                  mpClosingBracketHdlr;
   /// Function called for an exclamation mark '!'.
   HandlerFunc                  mpExclamationMarkHdlr;
   /// Set when this object is used as argument handler for a sub-group.
   bool                         mIsSubGroupHandler = false;
   /// The current constraints, dynamically created through the arguments that
   /// were processed so far.
   detail::ConstraintContainer  mConstraints;
   /// Global constraints, i.e. constraints that affect multiple arguments
   /// and/or are not triggered by a specific argument.
   ConstraintCont               mGlobalConstraints;

   /// Pointer to the last argument handler that was used. Needed for
   /// processing multiple, separate values.
   detail::TypedArgBase*        mpLastArg = nullptr;
   /// Reading arguments from a file should not influence the cardinality
   /// checks, i.e. it should be possible to overwrite a value from a file
   /// without triggering a 'too many values' exception.
   bool                         mReadingArgumentFile = false;
   /// Flag, set when this argument handler object was created by a Groups
   /// object.
   bool                         mUsedByGroup;

}; // Handler


// macros
// ======


/// Macro used to pass the destination variable and its name.
/// @param  n  The destination variable.
/// @since  0.2, 10.04.2016
#define DEST_VAR( n)  n, #n

/// Macro used to pass a destination variable that accepts a range string as
/// value.
/// @param  n  The destination variable.
/// @param  t  The value type of the destination variable.
/// @param  c  The type of the container/the destination variable.
/// @todo  Try to change this (and the class RangeDest?) so that the type of
///        the destination variable (container type) does not need to be
///        set separately.
/// @since  0.2, 10.04.2016
#define DEST_RANGE( n, t, c)  celma::common::RangeDest< t, c < t > >( n), #n

/// Macro used to pass a destination variable that accepts a range string as
/// value.
/// @param  n  The destination variable.
/// @param  s  The size of the bitset.
/// @since  0.2, 10.04.2016
#define DEST_BITSET( n, s)  celma::common::RangeDest< size_t, std::bitset< s> >( n), #n

/// Use this define to pass a function that takes no value as argument handler.
/// @param[in]  f  The name of the function.
/// @since  0.2, 10.04.2016
#define  DEST_FUNCTION( f)  std::bind( &f), #f

/// Use this define to pass a function that accepts a value as argument handler.
/// @param[in]  f  The name of the function.
/// @since  0.2, 10.04.2016
#define  DEST_FUNCTION_VALUE( f)  std::bind( &f, std::placeholders::_1), #f, true

/// Use this define to pass a method (class member function) of the current
/// object, that takes no value, as argument handler.
/// @param[in]  c  The name of the class.
/// @param[in]  m  The name of the method.
/// @since  0.13.1, 07.02.2017
#define  DEST_MEMBER_METHOD( c, m)  std::bind( & c :: m, this), #c "::" #m

/// Use this define to pass a method (class member function) that takes no value
/// as argument handler.
/// @param[in]  c  The name of the class.
/// @param[in]  m  The name of the method.
/// @param[in]  o  The object to call the method for.
/// @since  0.2, 10.04.2016
#define  DEST_METHOD( c, m, o)  std::bind( & c :: m, &o), #c "::" #m

/// Use this define to pass a method (class member function) of the current
/// object, that accepts a value, as argument handler.
/// @param[in]  c  The name of the class.
/// @param[in]  m  The name of the method.
/// @since  0.13.1, 07.02.2017
#define  DEST_MEMBER_METHOD_VALUE( c, m)  std::bind( & c :: m, this, std::placeholders::_1), #c "::" #m, true


/// Use this define to pass a method (class member function) that accepts a
/// value as argument handler.
/// @param[in]  c  The name of the class.
/// @param[in]  m  The name of the method.
/// @param[in]  o  The object to call the method for.
/// @since  0.2, 10.04.2016
#define  DEST_METHOD_VALUE( c, m, o)  std::bind( & c :: m, &o, std::placeholders::_1), #c "::" #m, true


// inlined methods
// ===============


template< typename T>
   detail::TypedArgBase*
      Handler::addArgument( const std::string& arg_spec,
                            T& dest,
                            const std::string vname,
                            const std::string& desc)
{
   detail::TypedArgBase*  arg_hdl = new detail::TypedArg< T>( arg_spec, dest, vname);
   return internAddArgument( arg_hdl, arg_spec, desc);
} // Handler::addArgument


template< typename T1, typename T2>
   detail::TypedArgBase*
      Handler::addArgument( const std::string& arg_spec,
                            T1& dest1,
                            const std::string vname1,
                            T2& dest2,
                            const std::string vname2,
                            const T2& value2,
                            const std::string& desc)
{
   detail::TypedArgBase*  arg_hdl =
      new detail::TypedArgPair< T1, T2>( arg_spec, dest1, vname1, dest2, vname2,
                                         value2);
   return internAddArgument( arg_hdl, arg_spec, desc);
} // Handler::addArgument


template< typename T>
   detail::TypedArgBase*
      Handler::addArgument( T& dest, const std::string vname,
                            const std::string& desc)
{
   detail::TypedArgBase*  arg_hdl = new detail::TypedArg< T>( "-", dest, vname);
   return internAddArgument( arg_hdl, "", desc);
} // Handler::addArgument


template< typename T, typename C>
   detail::TypedArgBase*
      Handler::addArgument( const std::string& arg_spec,
                            const common::RangeDest< T, C>& dest,
                            const std::string vname,
                            const std::string& desc)
{
   detail::TypedArgBase*  arg_hdl = new detail::TypedArgRange< T, C>( arg_spec, dest, vname);
   return internAddArgument( arg_hdl, arg_spec, desc);
} // Handler::addArgument


template< typename T, typename C>
   detail::TypedArgBase*
      Handler::addArgument( const common::RangeDest< T, C>& dest,
                            const std::string vname,
                            const std::string& desc)
{
   detail::TypedArgBase*  arg_hdl = new detail::TypedArgRange< T, C>( "-", dest, vname);
   return internAddArgument( arg_hdl, "", desc);
} // Handler::addArgument


inline detail::TypedArgBase*
   Handler::addArgument( const std::string& arg_spec,
                         detail::ArgHandlerCallable fun,
                         const std::string fname,
                         const std::string& desc)
{
   detail::TypedArgBase*  arg_hdl = new detail::TypedArgCallable( arg_spec, fun, fname);
   return internAddArgument( arg_hdl, arg_spec, desc);
} // Handler::addArgument


inline detail::TypedArgBase*
   Handler::addArgument( const std::string& arg_spec,
                         detail::ArgHandlerCallableValue fun,
                         const std::string fname,
                         bool,
                         const std::string& desc)
{
   detail::TypedArgBase*  arg_hdl = new detail::TypedArgCallableValue( arg_spec, fun, fname);
   return internAddArgument( arg_hdl, arg_spec, desc);
} // Handler::addArgument


inline detail::TypedArgBase*
   Handler::addArgument( const std::string& arg_spec, Handler* subGroup,
                         const std::string& desc)
{
   if (subGroup == nullptr)
      throw std::runtime_error( "Sub-group object pointer is NULL");
   subGroup->setIsSubGroupHandler();
   detail::TypedArgBase*  arg_hdl = new detail::TypedArgSubGroup( arg_spec, subGroup);
   mSubGroupArgs.addArgument( arg_hdl, arg_spec);
   mDescription.addArgument( arg_spec, desc, arg_hdl);
   return arg_hdl;
} // Handler::addArgument


template< typename C, typename T>
   detail::TypedArgBase*
      Handler::addCustomArgument( const std::string& arg_spec,
                                  T& dest,
                                  const std::string vname,
                                  const std::string& desc)
{
   detail::TypedArgBase*  arg_hdl = new C( arg_spec, dest, vname);
   return internAddArgument( arg_hdl, arg_spec, desc);
} // Handler::addCustomArgument


inline void Handler::setUsageLineLength( int useLen)
{
   mDescription.setLineLength( useLen);
   mSubGroupArgs.setUsageLineLength( useLen);
} // Handler::setUsageLineLength


inline void Handler::setIsSubGroupHandler()
{
   mIsSubGroupHandler = true;
} // Handler::setIsSubGroupHandler


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_HANDLER_HPP


// ===========================  END OF handler.hpp  ===========================

