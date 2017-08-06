
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
/// See documentation of class celma::prog_args::detail::TypedArgBase.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_BASE_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_BASE_HPP


#include <iosfwd>
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "celma/prog_args/detail/argument_key.hpp"
#include "celma/prog_args/detail/i_check.hpp"
#include "celma/prog_args/detail/i_constraint.hpp"
#include "celma/prog_args/detail/i_format.hpp"
#include "celma/prog_args/detail/i_cardinality.hpp"

// the specific checks are not actually needed here, but they are included
// anyway for convenience of the user
#include "celma/prog_args/detail/check_lower.hpp"
#include "celma/prog_args/detail/check_upper.hpp"
#include "celma/prog_args/detail/check_range.hpp"
#include "celma/prog_args/detail/check_values.hpp"

// also the specific formatters are not actually needed here, but they are also
// included anyway for convenience of the user
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


namespace celma { namespace prog_args { namespace detail {


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
///
/// The class provides two insertion operators:<br>
/// - The first, public one takes a pointer to an object. This variant is used
///   to call the virtual method dump() which can be overloaded by derived
///   classes.
/// - The second, protected one takes a const reference as parameter. This
///   variant is used to print the values of the features/flags handled by this
///   base class.
///
/// @since  x.y.z, 13.07.2017  (use type ArgumentKey instead of string for
///                             arguments)
/// @since  0.2, 10.04.2016
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
      command,    //!< An argumewnt with this value mode signals that this and
                  //!< all the following arguments and values are not anymore
                  //!< relevant for this object, but should be assigned as
                  //!< complete argument string to the value of the argument and
                  //!< will then be handled by another tool/command.
      unknown     //!< We don't know if the argument actually needs a value or
                  //!< not (used for arguments that result in a function call).
                  //!< But this is only used as an initialisation value, once
                  //!< the arguments are evaluated each argument must have a
                  //!< defined value mode.
   }; // ValueMode

   /// Returns the text for the enum.
   /// @param[in]  vm  The value to return the text for.
   /// @return  The text for the value mode.
   /// @since  0.13.2, 18.02.2017
   static constexpr const char* valueMode2str( ValueMode vm);

   /// Constructor.
   /// @param[in]  key       The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  vname     The name of the destination variable to store the
   ///                       value in.
   /// @param[in]  vm        The value mode to set for this argument.
   /// @param[in]  printDef  Specifies if the default value of the destination
   ///                       variable should be printed in the usage or not.
   /// @since  0.2, 10.04.2016
   TypedArgBase( const ArgumentKey& key, const std::string& vname,
                 ValueMode vm, bool printDef);

   /// Destructor, frees dynamically allocated memory.
   /// @since  0.2, 10.04.2016
   virtual ~TypedArgBase();

   /// Assigns a value.
   /// @param[in]  ignore_cardinality  Specifies if the cardinality of calls/
   ///                                 value assignments should be ignored.
   /// @param[in]  value               The value to assign, in string format.
   /// @since  0.2, 10.04.2016
   void calledAssign( bool ignore_cardinality, const std::string& value = "");

   /// Should return if the argument was used/parameter was set.
   /// @return  \c true if the argument was used and therefore the parameter set,
   ///          \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const = 0;

   /// Returns the argument key(s) specified for this argument.
   /// @return  The short and/or long argument specified for this argument.
   /// @since  x.y.z, 13.07.2017  (renamed from argSpec())
   /// @since  0.2, 10.04.2016
   const ArgumentKey& key() const;

   /// For boolean arguments: Unset the flag (set to \c false) instead of
   /// setting it (the default).<br>
   /// Throws an exception here, must be implemented by the partial
   /// specialisation for type \c bool.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* unsetFlag() noexcept( false);

   /// Specifies that the argument is mandatory (required). By default, all
   /// arguments are optional.<br>
   /// Virtual because some arguments don't make sense to be mandatory
   /// (specially boolean flags), so the specialisation for bool can override
   /// the method.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setIsMandatory();

   /// Returns if this argument is mandatory (required) or not.
   /// @return  \c true if the argument is mandatory, \c false otherwise.
   /// @since  0.2, 10.04.2016
   bool isMandatory() const;

   /// Sets the flag if the default value of the destination variable should be
   /// printed in the usage or not.
   /// @param[in]  doPrint  \c true = do print the default value, \c false = don't.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setPrintDefault( bool doPrint);

   /// Returns if the default value of the destination variable should be
   /// printed in the usage.
   /// @return  \c true if the default value should be printed, \c false otherwise.
   /// @since  0.2, 10.04.2016
   bool printDefault() const;

   /// Specifies that this argument is hidden.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   TypedArgBase* setIsHidden();

   /// Returns if this argument is hidden.
   /// @return  \c true if this argument is hidden.
   /// @since  0.2, 10.04.2016
   bool isHidden() const;

   /// Overwrites the 'value mode' which specifies if a value is needed for this
   /// argument or not.<br>
   /// Here in the base class, the only value mode that can be set is
   /// 'required'.
   /// @param[in]  vm  The new value mode.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setValueMode( ValueMode vm) noexcept( false);

   /// Returns the value mode of this argument.
   /// @return  The value mode of this argument.
   /// @since  0.2, 10.04.2016
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
   /// @return  Pointer to this object.
   /// @throws  runtime_error when called on a type that cannot handle multiple
   ///          values.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setTakesMultiValue() noexcept( false);

   /// Returns if this arguments should accept multiple, separate values on the
   /// command line.
   /// @return  \c true if this argument accepts multiple, separate values.
   /// @since  0.2, 10.04.2016
   bool takesMultiValue() const;

   /// Adds a value formatter: The value from the argument list (command line)
   /// is formatted before it is checked and/or stored.<br>
   /// Throws when called for an argument that does not accept values.
   /// @param[in]  f  Pointer to the formatter to add.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* addFormat( IFormat* f) noexcept( false);

   /// Calls all formatter methods defined for this argument. The formatter
   /// methods should throw an exception when a formatting failed.
   /// @param[in,out]  val  The value to format.
   /// @since  0.2, 10.04.2016
   void format( std::string& val) const;

   /// Adds a value check.<br>
   /// Throws when called for an argument that does not accept values.
   /// @param[in]  c  Pointer to the object that checks the value.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* addCheck( ICheck* c);

   /// Specifies the list separator character to use for splitting lists of
   /// values.
   /// @param[in]  sep  The character to use to split a list.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setListSep( char sep) noexcept( false);

   /// Calls all check methods defined for this argument. The check methods
   /// throw an exception when a check failed, so: No exception, value can be
   /// stored.
   /// @param[in]  val  The value to check in string format.
   /// @since  0.2, 10.04.2016
   void check( const std::string& val) const;

   /// Specifies the cardinality check to perform on this type before assignment
   /// of a new value.<br>
   /// For most types, cardinality is set to 'maximum(1)', meaning that at most
   /// one (1) value may be assigned to this variable. Exception: vectors.<br>
   /// If your parameter (type) allows more values or requires a specific number
   /// of values, set the corresponding cardinality.<br>
   /// Only one cardinality check is possible, so setting a new check object
   /// deletes any previously existing check/object.
   /// @param[in]  c  The object that handles the cardinality checks, NULL means
   ///                no cardinality checks.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setCardinality( ICardinality* c = nullptr);

   /// After all arguments were processed, checks if the cardinality
   /// requirement (e.g. minimum number of values) was met.
   /// @since  0.2, 10.04.2016
   void checkCardinality();

/*
   /// Adds a value conversion: The value from the argument list (command line)
   /// is converted before it is checked and/or stored.
   /// @param[in]  c  Pointer to the conversion to add.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   TypedArgBase* addConversion( ConversionBase* c);

   /// Calls all conversion methods defined for this argument. The conversion
   /// methods should throw an exception when a conversion failed.
   /// @param[in,out]  val  The value to convert.
   /// @since  0.2, 10.04.2016
   void convert( std::string& val) const;
*/

   /// Returns the name of the destination variable in which the values are
   /// stored.
   /// @return  The name of the destination variable.
   /// @since  0.2, 10.04.2016
   const std::string& varName() const;

   /// Should add the value of the destination variable to the string when
   /// called.<br>
   /// Throws an exception when called for the base class.
   /// @param[in]  dest  The string to append the default value to.
   /// @since  0.2, 10.04.2016
   virtual void defaultValue( std::string& dest) const noexcept( false);

   /// Adds a constraint to this argument. The constraint is only evaluated when
   /// the argument is actually used.
   /// @param[in]  ic  Pointer to the contraint object to add to this argument.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* addConstraint( IConstraint* ic);

   /// Called for printing an argument and its destination variable.<br>
   /// Calls dump() which can be overloaded by derived classes.
   /// @param[out]  os   The stream to write to.
   /// @param[in]   tab  Pointer to the object to print.
   /// @return  The stream as passed in.
   /// @since  0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, const TypedArgBase* tab);

protected:
   /// Prints the values of the settings/flags managed by this class (except the
   /// name of the destination variable).
   /// @param[out]  os   The stream to print to.
   /// @param[in]   tab  The object to print.
   /// @return  The stream as passed in.
   /// @since  0.2, 10.04.2016
   friend std::ostream& operator <<( std::ostream& os, const TypedArgBase& tab);

   /// Should be called by the assign() methods in the derived classes:<br>
   /// Handle all the constraints defined for this object.
   /// @since  0.2, 10.04.2016
   void activateConstraints();

   /// The complete argument specification: short and/or long argument.
   const ArgumentKey                 mKey;
   /// Contains the name of the variable in which the value(s) are stored.
   const std::string                 mVarName;
   /// The value mode of this argument, set depending on the type of the
   /// destination variable.
   ValueMode                         mValueMode;
   /// Set if this argument is mandatory, not set by default.
   bool                              mIsMandatory;
   /// Set if this argument can handle multiple, separate values in the
   /// argument list.
   bool                              mTakeMultipleValues;
   /// Set if the destination variable for this argument already contains the
   /// default value which may be printed in the usage.
   bool                              mPrintDefault;
   /// Set if this argument should be hidden = not printed in the usage.
   bool                              mIsHidden;
   /// Stores all the checks (objects) defined for this argument.
   std::vector< ICheck*>             mChecks;
   /// Stores all the formatters (objects) defined for this argument.
   std::vector< IFormat*>            mFormats;
   /// Pointer to the object that manages the cardinality check.
   boost::scoped_ptr< ICardinality>  mpCardinality;
   /// Stores the constraints defined for this argument.
   std::vector< IConstraint*>        mConstraints;

private:
   /// Should assign a value to the specified destination variable.
   /// @param[in]  value  The value to assign in string format.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value = "") = 0;

   /// Used for printing an argument and its destination variable.<br>
   /// This function should be overloaded by derived classes.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const;

}; // TypedArgBase


/// Prints the value of the enum in readable form.
/// @param[out]  os  The stream to print to.
/// @param[in]   vm  The enum value to print.
/// @return  The stream as passed in.
/// @since  0.2, 10.04.2016
std::ostream& operator <<( std::ostream& os, TypedArgBase::ValueMode vm);


// inlined methods
// ===============


constexpr const char* TypedArgBase::valueMode2str( ValueMode vm)
{
   switch (vm)
   {
   case ValueMode::none:      return "none";
   case ValueMode::optional:  return "optional";
   case ValueMode::required:  return "required";
   case ValueMode::command:   return "command";
   default:                   return "unknown";
   } // end switch
} // TypedArgBase::valueMode2str


inline const ArgumentKey& TypedArgBase::key() const
{
   return mKey;
} // TypedArgBase::key


inline TypedArgBase* TypedArgBase::setIsMandatory()
{
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


inline TypedArgBase* TypedArgBase::setListSep( char /* sep */) noexcept( false)
{
   throw std::invalid_argument( "setting list separator not allowed for "
                                "variable '" + mVarName + "'");
} // TypedArgBase::setListSep


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


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_BASE_HPP


// ========================  END OF typed_arg_base.hpp  ========================

