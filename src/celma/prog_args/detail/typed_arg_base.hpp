
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
/// See documentation of class celma::prog_args::detail::TypedArgBase.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_BASE_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_BASE_HPP


#include <iosfwd>
#include <string>
#include <vector>
#include "celma/prog_args/detail/argument_key.hpp"
#include "celma/prog_args/detail/i_check.hpp"
#include "celma/prog_args/detail/i_arg_constraint.hpp"
#include "celma/prog_args/detail/i_format.hpp"
#include "celma/prog_args/detail/i_cardinality.hpp"

// the specific checks are not actually needed here, but they are included
// anyway for convenience of the user
#include "celma/prog_args/detail/check_file_modification.hpp"
#include "celma/prog_args/detail/check_file_size.hpp"
#include "celma/prog_args/detail/check_file_suffix.hpp"
#include "celma/prog_args/detail/check_is_absolute_path.hpp"
#include "celma/prog_args/detail/check_is_directory.hpp"
#include "celma/prog_args/detail/check_is_file.hpp"
#include "celma/prog_args/detail/check_lower.hpp"
#include "celma/prog_args/detail/check_max_length.hpp"
#include "celma/prog_args/detail/check_min_length.hpp"
#include "celma/prog_args/detail/check_parent_directory_exists.hpp"
#include "celma/prog_args/detail/check_pattern.hpp"
#include "celma/prog_args/detail/check_range.hpp"
#include "celma/prog_args/detail/check_upper.hpp"
#include "celma/prog_args/detail/check_values.hpp"

// also the specific formatters are not actually needed here, but they are also
// included anyway for convenience of the user
#include "celma/prog_args/detail/format_anycase.hpp"
#include "celma/prog_args/detail/format_lowercase.hpp"
#include "celma/prog_args/detail/format_uppercase.hpp"

// and also the specific cardinality checks are not actually needed here, but
// they are also included anyway for convenience of the user
#include "celma/prog_args/detail/cardinality_exact.hpp"
#include "celma/prog_args/detail/cardinality_max.hpp"
#include "celma/prog_args/detail/cardinality_range.hpp"

// last but not least, for the same reason include all argument constraints here
#include "celma/prog_args/detail/constraint_excludes.hpp"
#include "celma/prog_args/detail/constraint_requires.hpp"


namespace celma::prog_args::detail {


/// Base class for storing type-specific handlers type-neutrally.<br>
/// Some functionality is provided by this base class already:
/// - Value mode: Defines, if the argument needs, accepts or doesn't use a
///   value.
/// - The name of the destination variable (for output purposes).
/// - If an argument is mandary or not.
/// - For an argument that accepts multiple values, if it even accepts multiple,
///   separate values on the command line.
/// - The list of value check functions for this argument.
/// - The list of formatting functions for this argument.
/// - If the argument's default value should be printed in the usage.
/// - If an argument is hidden or not.
/// - Pointer to the cardinality check object, called every time before assign()
///   is called.
/// .
/// The class provides two insertion operators:<br>
/// - The first, public one takes a pointer to an object. This variant is used
///   to call the virtual method dump() which can be overloaded by derived
///   classes.
/// - The second, protected one takes a const reference as parameter. This
///   variant is used to print the values of the features/flags handled by this
///   base class.
/// .
/// @since
///    0.15.0, 13.07.2017  (use type ArgumentKey instead of string for arguments)
/// @since
///    0.2, 10.04.2016
class TypedArgBase
{
public:
   /// List of possible settings if a value is needed for an argument:
   enum class ValueMode
   {
      none,       //!< The argument does not accept a value.<br>
                  //!< This is the default for boolean arguments.
      optional,   //!< The value is optional.
      required,   //!< The argument must have a value.<br>
                  //!< This is the default for all other arguments.
      command     //!< An argument with this value mode signals that this and
                  //!< all the following arguments and values are not anymore
                  //!< relevant for this object, but should be assigned as
                  //!< complete argument string to the value of the argument and
                  //!< will then be handled by another tool/command.
   }; // ValueMode

   /// Returns the text for the enum.
   /// @param[in]  vm
   ///    The value to return the text for.
   /// @return
   ///    The text for the value mode.
   /// @since
   ///    0.13.2, 18.02.2017
   static constexpr const char* valueMode2str( ValueMode vm);

   /// Copying is not allowed.
   TypedArgBase( const TypedArgBase&) = delete;

   /// Destructor, frees dynamically allocated memory.
   /// @since
   ///    0.2, 10.04.2016
   virtual ~TypedArgBase();

   /// Set the argument key.
   /// @param[in]  key
   ///    The complete argument specification with short and/or long argument.
   /// @since
   ///    0.16.0, 09.11.2017
   void setKey( const ArgumentKey& key);

   /// Assigns a value.<br>
   /// Checks if the argument is deprecated, or if a cardinality constraint is
   /// violated.<br>
   /// If not and the flag \a inverted is set, checks if the argument supports
   /// inverted logic.<br>
   /// Finally the virtual method assign() is called to actually assign the
   /// value, and afterwards activateConstraints() is called to activate the
   /// constraints (sic!) triggered by this argument.
   ///
   /// @param[in]  ignore_cardinality
   ///    Specifies if the cardinality of calls/value assignments should be
   ///    ignored.
   /// @param[in]  value
   ///    The value to assign, in string format.
   /// @param[in]  inverted
   ///    Is set when the argument was preceeded by an exclamation mark which
   ///    means that the logic of the argument should be inverted.
   /// @throw  std::runtime_error
   ///    if the function is deprecated, or when the flag \a inverted is set and
   ///    the value type dopes not support inversion.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  1.6.0, 29.06.2018
   ///    (renamed from calledAssign)
   /// @since  0.2, 10.04.2016
   void assignValue( bool ignore_cardinality, const std::string& value,
      bool inverted) noexcept( false);

   /// Should return if the argument was used/parameter was set.
   /// @return
   ///    \c true if the argument was used and therefore the parameter set.
   /// @since
   ///    0.2, 10.04.2016
   virtual bool hasValue() const = 0;

   /// Prints the current value of the destination variable.<br>
   /// Does not check any flags, if a value has been set etc., simply prints the
   /// value.
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since
   ///    1.8.0, 04.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const = 0;

   /// Returns the argument key(s) specified for this argument.
   /// @return
   ///    The short and/or long argument specified for this argument.
   /// @since
   ///    0.15.0, 13.07.2017  (renamed from argSpec())
   /// @since
   ///    0.2, 10.04.2016
   const ArgumentKey& key() const;

   /// For bitset destinations and boolean within a check-assign: Unset the bits
   /// instead of setting them.<br>
   /// Throws an exception here, must be implemented by the partial
   /// specialisation for type \c std::bitset.
   ///
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* unsetFlag() noexcept( false);

   /// Specifies that the argument is mandatory (required). By default, all
   /// arguments are optional.<br>
   /// Virtual because some arguments don't make sense to be mandatory
   /// (specially boolean flags), so the specialisation for bool can override
   /// the method.
   /// @return
   ///    Pointer to this object.
   /// @since
   ///    0.2, 10.04.2016
   virtual TypedArgBase* setIsMandatory() noexcept( false);

   /// Returns if this argument is mandatory (required) or not.
   /// @return
   ///    \c true if the argument is mandatory.
   /// @since
   ///    0.2, 10.04.2016
   bool isMandatory() const;

   /// Sets the flag if the default value of the destination variable should be
   /// printed in the usage or not.
   ///
   /// @param[in]  doPrint  \c true = do print the default value.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setPrintDefault( bool doPrint);

   /// Returns if the default value of the destination variable should be
   /// printed in the usage.
   ///
   /// @return  \c true if the default value should be printed.
   /// @since  0.2, 10.04.2016
   bool printDefault() const;

   /// If printing the default value in the usage is enabled, this function can
   /// be used to specify the unit of the value. This will be displayed behind
   /// the value in the usage.
   ///
   /// @param[in]  unit  The unit of the value to display in the usage.
   /// @throw  std::logic_error if printing the default value is disabled.
   /// @since  1.35.0, 09.02.2020
   void setValueUnit( const std::string& unit) noexcept( false);

   /// Returns the specified value unit string.
   ///
   /// @return  The value unit string if specified, an empty string otherwise.
   /// @since  1.35.0, 09.02.2020
   const std::string& valueUnit() const;

   /// Specifies that this argument is hidden.
   /// @return
   ///    Pointer to this object.
   /// @since
   ///    0.2, 10.04.2016
   TypedArgBase* setIsHidden();

   /// Returns if this argument is hidden.
   /// @return
   ///    \c true if this argument is hidden.
   /// @since
   ///    0.2, 10.04.2016
   bool isHidden() const;

   /// Overwrites the 'value mode' which specifies if a value is needed for this
   /// argument or not.<br>
   /// Here in the base class, the only value mode that can be set is
   /// 'required'.
   ///
   /// @param[in]  vm  The new value mode.
   /// @return  Pointer to this object.
   /// @throw  std::invalid_argument If the given value mode is not 'required'.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setValueMode( ValueMode vm) noexcept( false);

   /// Returns the value mode of this argument.
   /// @return
   ///    The value mode of this argument.
   /// @since
   ///    0.2, 10.04.2016
   ValueMode valueMode() const;

   /// Normally, all values for an argument must be passed as one logical unit,
   /// e.g. a comma-separated list.<br>
   /// When this feature is activated, it is possible to pass multiple, separate
   /// values to one argument. Activating this feature is only possible on data
   /// types that can handle multiple values.<br>
   /// Internally, the feature works like this: If a free value is found in the
   /// argument list, check if the last used argument has this feature enabled.
   /// If so, pass the value to this argument, otherwise treat the value as free
   /// free value.<br>
   /// In order to end the value list and make the next value in the argument
   /// list a free value, use the argument '--endvalues' after the last value.
   /// @return
   ///    Pointer to this object.
   /// @throw
   ///    std::runtime_error when called on a type that cannot handle multiple
   ///    values.
   /// @since
   ///    0.2, 10.04.2016
   virtual TypedArgBase* setTakesMultiValue() noexcept( false);

   /// Returns if this arguments should accept multiple, separate values on the
   /// command line.
   /// @return
   ///    \c true if this argument accepts multiple, separate values.
   /// @since
   ///    0.2, 10.04.2016
   bool takesMultiValue() const;

   /// Adds a value formatter: The value from the argument list (command line)
   /// is formatted before it is checked and/or stored.
   /// Use this function for destination types that can store only one value, or
   /// values of one type.
   ///
   /// @param[in]  f
   ///    Pointer to the formatter to add, is deleted when it could not be
   ///    stored.
   /// @return  Pointer to this object.
   /// @throw
   ///    std::logic_error when called for an argument that does not accept
   ///    values.
   /// @throw
   ///    std::invalid_argument when the given object pointer is NULL.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* addFormat( IFormat* f) noexcept( false);

   /// Adds a value formatter for the value at the given position: The value
   /// from the argument list (command line) is formatted before it is checked
   /// and/or stored.
   /// Use this function for destination types that can store multiple values
   /// with the same or even with different types.<br>
   /// Here in the base class always throws, must be overloaded for types that
   /// support multiple values.
   ///
   /// @param[in]  val_idx
   ///    The index of the value to apply the format to.<br>
   ///    A value of -1 means that the format should be applied to all values,
   ///    index 0 means the first value etc.
   /// @param[in]  f
   ///    Pointer to the formatter to add, is deleted when it could not be
   ///    stored.
   /// @return  Pointer to this object.
   /// @throw
   ///    std::logic_error when called for an argument that does not accept
   ///    multiple values.
   /// @since  1.32.0, 25.04.2019
   virtual TypedArgBase* addFormatPos( int val_idx, IFormat* f) noexcept( false);

   /// Defines a formatter for the key of containers with key-value pairs.
   ///
   /// @param[in]  f  Ignored here.
   /// @return  Never in this base class.
   /// @throw  std::logic_error when executed in the base class.
   /// @since  1.41.0, 18.02.2020
   virtual TypedArgBase* addFormatKey( IFormat* f) noexcept( false);

   /// Defines a formatter for the values of containers with key-value pairs.
   /// 
   /// @param[in]  f  Ignored here.
   /// @return  Never in this base class.
   /// @throw  std::logic_error when executed in the base class.
   /// @since  1.41.0, 18.02.2020
   virtual TypedArgBase* addFormatValue( IFormat* f) noexcept( false);

   /// Calls all formatter methods defined for this argument. The formatter
   /// methods should throw an exception when a formatting failed.
   ///
   /// @param[in,out]  val
   ///    The value to format, may be modified by the defined formatters.
   /// @param[in]      value_idx
   ///    The index of the value to format, -1 to call the single/general
   ///    formatter.
   /// @since
   ///    0.2, 10.04.2016
   void format( std::string& val, int value_idx = -1) const;

   /// Adds a value check.
   ///
   /// @param[in]  c
   ///    Pointer to the object that checks the value, is deleted when it could
   ///    not be stored.
   /// @return  Pointer to this object.
   /// @throw
   ///    std::logic_error when called for an argument that does not accept
   ///    values.
   /// @throw  std::invalid_argument when the given object pointer is NULL.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* addCheck( ICheck* c);

   /// Special feature for destination variable type level counter:<br>
   /// Allow mixing of increment and assignment on the command line.
   ///
   /// @since  1.11.0, 20.08.2018
   virtual TypedArgBase* setAllowMixIncSet() noexcept( false);

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   ///
   /// @param[in]  sep  The character to use to split a list. Ignored here.
   /// @return  Never returns.
   /// @throw  std::invalid_argument when called in this base class.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setListSep( char sep) noexcept( false);

   /// Is overwritten by types that support key-value pairs.
   /// Here: Throws.
   ///
   /// @param[in]  separators
   ///    Specifies the separator(s) for pairs. Ignored here
   /// @return  Never returns here.
   /// @throw  std::invalid_argument when called in this base class.
   /// @since   1.41.0, 13.02.2020
   virtual TypedArgBase* setPairFormat( const std::string& separators)
      noexcept( false);

   /// Special feature for destination variable type vector:<br>
   /// Clear the contents of the vector before assigning the value(s) from the
   /// command line. If the feature is off (the default), the value(s from the
   /// command line are appended.<br>
   /// Use this feature if some default value(s) have been assigned to the
   /// destination vector that should be overwritten by the argument's values.
   /// Throws when called for other destination types.
   /// @since
   ///    1.2.0, 28.12.2017
   virtual TypedArgBase* setClearBeforeAssign() noexcept( false);

   /// Special feature for destination variable type vector:<br>
   /// Sort the contents of the vector.
   /// @since
   ///    1.9.0, 04.08.2018
   virtual TypedArgBase* setSortData() noexcept( false);

   /// Special feature for destination variable type vector:<br>
   /// Make sure only unique values are stored in the vector.
   ///
   /// @param[in]  duplicates_are_errors
   ///    Set this flag if duplicate values should be treated as errors,
   ///    otherwise they will be silently discarded.
   /// @since
   ///    1.9.0, 04.08.2018
   virtual TypedArgBase* setUniqueData( bool duplicates_are_errors = false)
      noexcept( false);

   /// Calls all check methods defined for this argument. The check methods
   /// throw an exception when a check failed, so: No exception, value can be
   /// stored.
   /// @param[in]  val
   ///    The value to check in string format.
   /// @since
   ///    0.2, 10.04.2016
   void check( const std::string& val) const;

   /// Returns if the argument has a check specified.
   /// @return
   ///    \c true if the argument has a check specified.
   /// @since
   ///    0.16.0, 12.08.2017
   bool hasCheck() const;

   /// Returns a text description of the check specified for this argument.
   /// @return
   ///    A string with the description of the check.
   /// @since
   ///    0.16.0, 12.08.2017
   std::string checkStr() const;

   /// Returns a text description of the formats specified for this argument.
   ///
   /// @return  A string with the description of the formatters.
   /// @since  1.33.0, 05.11.2019
   std::string formatStr() const;

   /// Specifies the cardinality check to perform on this type before assignment
   /// of a new value.<br>
   /// For most types, cardinality is set to 'maximum(1)', meaning that at most
   /// one (1) value may be assigned to this variable. Exception: vectors.<br>
   /// If your parameter (type) allows more values or requires a specific number
   /// of values, set the corresponding cardinality.<br>
   /// Only one cardinality check is possible, so setting a new check object
   /// deletes any previously existing check/object.
   /// @param[in]  c
   ///    The object that handles the cardinality checks, NULL means no
   ///    cardinality checks.
   /// @return
   ///    Pointer to this object.
   /// @since
   ///    0.2, 10.04.2016
   virtual TypedArgBase* setCardinality( ICardinality* c = nullptr);

   /// After all arguments were processed, checks if the cardinality
   /// requirement (e.g. minimum number of values) was met.
   /// @since
   ///    0.2, 10.04.2016
   void checkCardinality();

   /// Returns a text description of the cardinality specified for this argument.
   ///
   /// @return  A string with the description of the cardinality.
   /// @since  1.14.0, 02.10.2018
   std::string cardinalityStr() const;

   /// Allows to change the "original value check" mode. This is only applicable
   /// to typed arg value objects.
   /// @param[in]  yesNo
   ///    Set to \c false for turning the value check off.
   /// @return
   ///    Pointer to this object.
   /// @since
   ///    1.1.0, 16.11.2017
   virtual TypedArgBase* checkOriginalValue( bool yesNo) noexcept( false);

   /// Marks an argument as deprecated.
   /// @return
   ///    Pointer to this object.
   /// @since
   ///    1.6.0, 30.04.2018
   virtual TypedArgBase* setIsDeprecated() noexcept( false);

   /// Returns if the argument is marked as deprecated.
   /// @return
   ///    \c true if the argument is marked as deprecated.
   /// @since
   ///    1.6.0, 30.04.2018
   bool isDeprecated() const;

   /// Marks an argument as replaced by another argument.
   /// @return
   ///    Pointer to this object.
   /// @since
   ///    1.6.0, 03.07.2018
   virtual TypedArgBase* setReplacedBy( const std::string& new_arg_key)
      noexcept( false);

   /// Returns if the argument is marked as "replaced by another argument".
   /// @return
   ///    \c true if the argument is marked as replaced.
   /// @since
   ///    1.6.0, 02.07.2018
   bool isReplaced() const;

   /// Returns the value stored in the "replaced by" property (without checking
   /// e.g. if the "is deprecated" flag is set).
   /// @return
   ///    The value stored in "replaced by".
   /// @since
   ///    1.6.0, 03.07.2018
   const std::string& replacedBy() const;

   /// Marks an argument that inverted logic is supported, i.e. the argument may
   /// be proceeded by an exclamation mark.<br>
   /// By default this is not allowed/supported.
   ///
   /// @return  Pointer to this object.
   /// @throw  invalid argument.
   /// @since  1.27.0, 28.05.2019
   virtual TypedArgBase* allowsInversion() noexcept( false);

/*
   /// Adds a value conversion: The value from the argument list (command line)
   /// is converted before it is checked and/or stored.
   /// @param[in]  c
   ///    Pointer to the conversion to add.
   /// @return
   ///    Pointer to this object.
   /// @since
   ///    0.2, 10.04.2016
   TypedArgBase* addConversion( ConversionBase* c);

   /// Calls all conversion methods defined for this argument. The conversion
   /// methods should throw an exception when a conversion failed.
   /// @param[in,out]  val
   ///    The value to convert.
   /// @since
   ///    0.2, 10.04.2016
   void convert( std::string& val) const;
*/

   /// Returns the name of the destination variable in which the values are
   /// stored.
   /// @return
   ///    The name of the destination variable.
   /// @since
   ///    0.2, 10.04.2016
   const std::string& varName() const;

   /// Returns the type of the destination variable as string.
   ///
   /// @return  String with the type of the destination variable.
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const = 0;

   /// Should add the value of the destination variable to the string when
   /// called.<br>
   /// Throws an exception when called for the base class.
   /// @param[out]  dest
   ///    The string to append the default value to.
   /// @since
   ///    0.2, 10.04.2016
   virtual void defaultValue( std::string& dest) const noexcept( false);

   /// Adds a constraint to this argument. The constraint is only evaluated when
   /// the argument is actually used.
   ///
   /// @param[in]  iac
   ///    Pointer to the contraint object to add to this argument.
   /// @return
   ///    Pointer to this object.
   /// @since
   ///    0.2, 10.04.2016
   virtual TypedArgBase* addConstraint( IArgConstraint* iac) noexcept( false);

   /// Returns if the argument has a constraint specified.
   /// @return
   ///    \c true if the argument has a constraint specified.
   /// @since
   ///    0.16.0, 15.08.2017
   bool hasConstraint() const;

   /// Returns if the values in the objects intersect.
   /// In the base class: Throws always.
   ///
   /// @return  Here: Nothing, always throws.
   /// @throw  std::invalid_argument in the base class.
   /// @since   1.34.1, 12.01.2020
   virtual bool hasIntersection( TypedArgBase* arg) const noexcept( false);

   /// Returns the result of the comparison of the values in this and the other
   /// object.
   /// Here in the base class: ALways throws.
   ///
   /// @param[in]  arg
   ///    Pointer to the other object with the value to compare against.<br>
   ///    Here: Ignored.
   /// @return  Nothing, always throws.
   /// @throw  std::invalid_argument in the base class.
   /// @since  1.34.1, 14.01.2020
   virtual int compareValue( const TypedArgBase* arg) const noexcept( false);

   /// Returns a text description of the constraint specified for this argument.
   /// @return
   ///    A string with the description of the constraint.
   /// @since
   ///    0.16.0, 15.08.2017
   std::string constraintStr() const;

   /// Prints all properties of a destination variable.
   ///
   /// @param[in]  os  The stream to print to.
   /// @since  1.33.0, 01.11.2019  (moved here from handler class)
   void printProperties( std::ostream& os) const;

   /// Assignment is not allowed.
   TypedArgBase& operator =( const TypedArgBase&) = delete;

   /// Called for printing an argument and its destination variable.<br>
   /// Calls dump() which can be overloaded by derived classes.
   /// @param[out]  os
   ///    The stream to write to.
   /// @param[in]   tab
   ///    Pointer to the object to print.
   /// @return
   ///    The stream as passed in.
   /// @since
   ///    0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, const TypedArgBase* tab);

protected:
   /// Constructor.
   /// @param[in]  vname
   ///    The name of the destination variable to store the value in.
   /// @param[in]  vm
   ///    The value mode to set for this argument.
   /// @param[in]  printDef
   ///    Specifies if the default value of the destination variable should be
   ///    printed in the usage or not.
   /// @since
   ///    1.5.0, 20.06.2018  (not public anymore)
   /// @since
   ///    0.16.0, 09.11.2017
   TypedArgBase( const std::string& vname, ValueMode vm, bool printDef);

   /// Prints the values of the settings/flags managed by this class (except the
   /// name of the destination variable).
   /// @param[out]  os
   ///    The stream to print to.
   /// @param[in]   tab
   ///    The object to print.
   /// @return
   ///    The stream as passed in.
   /// @since
   ///    0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, const TypedArgBase& tab);

   /// Should be called by the assign() methods in the derived classes:<br>
   /// Handle all the constraints defined for this object.
   /// @since
   ///    0.2, 10.04.2016
   void activateConstraints();

   /// Finally adds the given formatter to the container of formatters.
   ///
   /// @param[in]  val_idx
   ///    The index of the value to apply the format on, plus 1.
   /// @param[in]  f
   ///    Pointer to the formatter object to store.
   /// @return  This object.
   /// @throw
   ///    std::logic_error when called for an argument that does not accept
   ///    values.
   /// @throw
   ///    std::invalid_argument when the given object pointer is NULL.
   /// @since  1.32.0, 25.04.2019
   TypedArgBase* internAddFormat( int val_idx, IFormat* f) noexcept( false);

   /// Storage type for formatters for one value type/position.
   using value_format_cont_t = std::vector< std::unique_ptr< IFormat>>;
   /// Storage type for all formatters for multiple value types/positions.
   using format_cont_t = std::vector< value_format_cont_t>;

   /// The complete argument specification: short and/or long argument.
   ArgumentKey                     mKey;
   /// Contains the name of the variable in which the value(s) are stored.
   const std::string               mVarName;
   /// The value mode of this argument, set depending on the type of the
   /// destination variable.
   ValueMode                       mValueMode;
   /// Set if this argument is mandatory, not set by default.
   bool                            mIsMandatory = false;
   /// Set if this argument can handle multiple, separate values in the
   /// argument list.
   bool                            mTakeMultipleValues = false;
   /// Set if the destination variable for this argument already contains the
   /// default value which may be printed in the usage.
   bool                            mPrintDefault;
   /// Set if this argument should be hidden = not printed in the usage.
   bool                            mIsHidden = false;
   /// Set to activate the comparison of the destination variable with its
   /// original value before a new value is assigned.<br>
   /// This may be used by the typed arg value class to detect multiple
   /// assignments to the same destination variable.
   bool                            mCheckOrigValue = false;
   /// Set if an argument is deprecated. Issues an error message
   /// "argument is deprecated" instead of "unknown argument".
   bool                            mIsDeprecated = false;
   /// Set when the argument supports logic inversion by a preceeding
   /// exclamation makr.
   bool                            mAllowsInverting = false;
   /// The key of the argument that replaced this argument.
   std::string                     mReplacedBy;
   /// When set: the unit string to display in the usage.
   std::string                     mUnitString;
   /// Stores all the checks (objects) defined for this argument.
   std::vector< ICheck*>           mChecks;
   /// Stores all the formatters (objects) defined for this argument.<br>
   /// Index 0 is used for formatters for single-value destinations and for
   /// formatters that apply to all positions of a multi-value destination.<br>
   /// Index 1 is then used for values at position 0 of the destination etc.
   format_cont_t                   mFormats;
   /// Pointer to the object that manages the cardinality check.
   std::unique_ptr< ICardinality>  mpCardinality;
   /// Stores the constraints defined for this argument.
   std::vector< IArgConstraint*>   mConstraints;

private:
   /// Creates a list of the name of the formatters set for a specific index.
   ///
   /// @param[in]  os
   ///    The stream to write to.
   /// @param[in]  formatters
   ///    The container with the formatters for a specific index.
   /// @since  1.33.0, 05.11.2019
   static void formatStr( std::ostream& os,
      const value_format_cont_t& formatters);

   /// Should assign a value to the specified destination variable.<br>
   /// Value parameter is obviously always passed, if the destination type
   /// doesn't accept values or supports usage without value(s), the string is/
   /// may be empty.<br>
   /// Also the inverted parameter is always present, but it may only be set
   /// when the argument does support logic inversion. In all other cases the
   /// value need not be checked.
   ///
   /// @param[in]  value
   ///    The value to assign in string format.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value, bool inverted) = 0;

   /// Used for printing an argument and its destination variable.<br>
   /// This function should be overloaded by derived classes.
   /// @param[out]  os
   ///    The stream to print to.
   /// @since
   ///    0.2, 10.04.2016
   virtual void dump( std::ostream& os) const;

   /// Returns the number of formatters added for this argument.
   ///
   /// @return  The number of formatters that have been added.
   /// @since  1.32.0, 19.08.2019
   size_t numFormats() const;

}; // TypedArgBase


/// Prints the value of the enum in readable form.
/// @param[out]  os
///    The stream to print to.
/// @param[in]   vm
///    The enum value to print.
/// @return
///    The stream as passed in.
/// @since
///    0.2, 10.04.2016
std::ostream& operator <<( std::ostream& os, TypedArgBase::ValueMode vm);


// inlined methods
// ===============


constexpr const char* TypedArgBase::valueMode2str( ValueMode vm)
{
   switch (vm)
   {
   default:
   case ValueMode::none:      return "none";
   case ValueMode::optional:  return "optional";
   case ValueMode::required:  return "required";
   case ValueMode::command:   return "command";
   } // end switch
} // TypedArgBase::valueMode2str


inline const ArgumentKey& TypedArgBase::key() const
{
   return mKey;
} // TypedArgBase::key


inline TypedArgBase* TypedArgBase::setIsMandatory()
{
   if (mIsDeprecated)
      throw std::logic_error( "deprecated argument for variable '" + mVarName
         + "' cannot be set 'mandatory'");
   mIsMandatory = true;
   return this;
} // TypedArgBase::setIsMandatory


inline TypedArgBase* TypedArgBase::unsetFlag() noexcept( false)
{
   throw std::logic_error( "calling unsetFlag() not allowed for variable '" +
                           mVarName + "'");
} // TypedArgBase::unsetFlag


inline TypedArgBase* TypedArgBase::setPrintDefault( bool doPrint)
{
   mPrintDefault = doPrint;
   return this;
} // TypedArgBase::setPrintDefault


inline bool TypedArgBase::isMandatory() const
{
   return mIsMandatory;
} // TypedArgBase::isMandatory


inline bool TypedArgBase::printDefault() const
{
   return mPrintDefault;
} // TypedArgBase::printDefault


inline void TypedArgBase::setValueUnit( const std::string& unit)
   noexcept( false)
{
   if (!mPrintDefault)
      throw std::logic_error( "unit string can only be set when printing the "
         "default value is enabled");
   mUnitString = unit;
} // TypedArgBase::setValueUnit


inline const std::string& TypedArgBase::valueUnit() const
{
   return mUnitString;
} // TypedArgBase::valueUnit


inline TypedArgBase* TypedArgBase::setIsHidden()
{
   mIsHidden = true;
   return this;
} // TypedArgBase::setIsHidden


inline bool TypedArgBase::isHidden() const
{
   return mIsHidden;
} // TypedArgBase::isHidden


inline TypedArgBase::ValueMode TypedArgBase::valueMode() const
{
   return mValueMode;
} // TypedArgBase::valueMode


inline TypedArgBase* TypedArgBase::setTakesMultiValue() noexcept( false)
{
   throw std::invalid_argument( "setting 'take multiple values' not allowed "
                                "for variable '" + mVarName + "'");
} // TypedArgBase::setTakesMultiValue


inline bool TypedArgBase::takesMultiValue() const
{
   return mTakeMultipleValues;
} // TypedArgBase::takesMultiValue


inline TypedArgBase* TypedArgBase::setAllowMixIncSet() noexcept( false)
{
   throw std::invalid_argument( "setting \"allow mixing increment and setter\" "
      "not allowed for variable '" + mVarName + "'");
} // TypedArgBase::setAllowMixIncSet


inline TypedArgBase* TypedArgBase::setListSep( char /* sep */)
{
   throw std::invalid_argument( "setting list separator not allowed for "
                                "variable '" + mVarName + "'");
} // TypedArgBase::setListSep


inline TypedArgBase* TypedArgBase::setPairFormat( const std::string&)
   noexcept( false)
{
   throw std::invalid_argument( "setting pair separator not allowed for "
                                "variable '" + mVarName + "'");
} // TypedArgBase::setPairFormat


inline TypedArgBase* TypedArgBase::setClearBeforeAssign()
{
   throw std::invalid_argument( "setting 'clear before assign' is not allowed "
                                "for variable '" + mVarName + "'");
} // TypedArgBase::setClearBeforeAssign


inline TypedArgBase* TypedArgBase::setSortData()
{
   throw std::invalid_argument( "setting 'sort data' is not allowed for "
      "variable '" + mVarName + "'");
} // TypedArgBase::setSortData


inline TypedArgBase* TypedArgBase::setUniqueData( bool)
{
   throw std::invalid_argument( "setting 'unique data' is not allowed for "
      "variable '" + mVarName + "'");
} // TypedArgBase::setUniqueData


inline bool TypedArgBase::hasCheck() const
{
   return !mChecks.empty();
} // TypedArgBase::hasCheck


inline bool TypedArgBase::isDeprecated() const
{
   return mIsDeprecated;
} // TypedArgBase::isDeprecated


inline bool TypedArgBase::isReplaced() const
{
   return mIsDeprecated && !mReplacedBy.empty();
} // TypedArgBase::isReplaced


inline const std::string& TypedArgBase::replacedBy() const
{
   return mReplacedBy;
} // TypedArgBase::replacedBy


inline TypedArgBase* TypedArgBase::allowsInversion()
{
   throw std::invalid_argument( "setting 'allows inversion' not allowed for "
                                "variable '" + mVarName + "'");
} // TypedArgBase::allowsInversion


inline bool TypedArgBase::hasConstraint() const
{
   return !mConstraints.empty();
} // TypedArgBase::hasConstraint


inline const std::string& TypedArgBase::varName() const
{
   return mVarName;
} // TypedArgBase::varName


inline void TypedArgBase::defaultValue( std::string& /* dest */) const
   noexcept( false)
{
   throw std::runtime_error( "default value not available from base class for "
                             "variable '" + mVarName + "'");
} // TypedArgBase::defaultValue


} // namespace celma::prog_args::detail


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_BASE_HPP


// =====  END OF typed_arg_base.hpp  =====

