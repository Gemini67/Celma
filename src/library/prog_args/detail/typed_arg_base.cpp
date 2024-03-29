
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::TypedArgBase.


// module headerfile include
#include "celma/prog_args/detail/typed_arg_base.hpp"


// C++ Standard Library includes
#include <iostream>


// Boost includes
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/container/clear_container.hpp"
#include "celma/format/to_string.hpp"


namespace celma::prog_args::detail {


using std::ostream;
using std::string;



/// Destructor, frees dynamically allocated memory.
/// @since
///    0.2, 10.04.2016
TypedArgBase::~TypedArgBase()
{

   container::Vector::clear( mChecks);
   container::Vector::clear( mConstraints);

} // TypedArgBase::~TypedArgBase



/// Set the argument key.
/// @param[in]  key
///    The complete argument specification with short and/or long argument.
/// @since
///    0.16.0, 09.11.2017
void TypedArgBase::setKey( const ArgumentKey& key)
{

   mKey = key;

} // TypedArgBase::setKey



/// Stores the pointer to the constraint container to use for checking/adding
/// constraints.
///
/// @param[in]  container
///    Pointer to the constraints container to store.
/// @since  1.47.0, 05.12.2021
/// @throws  std::invalid_argument
///    when the given pointer is NULL.
void TypedArgBase::setConstraintsContainer( ConstraintContainer* container)
   noexcept( false)
{

   if (container == nullptr)
      throw std::invalid_argument( "Need to set a valid constraints container "
         "object");

   mpConstraintsContainer = container;

} // TypedArgBase::setConstraintsContainer



/// Overwrites the 'value mode' which specifies if a value is needed for this
/// argument or not.<br>
/// Here in the base class, the only value mode that can be set is
/// 'required'.
///
/// @param[in]  vm  The new value mode.
/// @return  Pointer to this object.
/// @throw  std::invalid_argument If the given value mode is not 'required'.
/// @since  0.2, 10.04.2016
TypedArgBase* TypedArgBase::setValueMode( ValueMode vm)
{

   if (vm == mValueMode)
      return this;

   if (vm != ValueMode::required)
      throw std::invalid_argument( std::string( "may not set value mode '") +
                                   valueMode2str( vm) + "' on variable '" +
                                   mVarName + "'");

   mValueMode = vm;
   return this;
} // TypedArgBase::setValueMode



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
void TypedArgBase::assignValue( bool ignore_cardinality, const string& value,
   bool inverted)
{

   if (mIsDeprecated)
   {
      if (mReplacedBy.empty())
         throw std::runtime_error( "argument '" + format::toString( mKey)
            + "' is deprecated");
      else
         throw std::runtime_error( "argument '" + format::toString( mKey)
            + "' has been replaced by '" + mReplacedBy + "'");
   } // end if

   if (!ignore_cardinality && mpCardinality)
      mpCardinality->gotValue();

   if (inverted && !mAllowsInverting)
      throw std::runtime_error( "argument '" + format::toString( mKey)
            + "' does not support invertion");

   assign( value, inverted);
   activateConstraints();

} // TypedArgBase::assignValue



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
TypedArgBase* TypedArgBase::addFormat( IFormat* f)
{

   return internAddFormat( 0, f);
} // TypedArgBase::addFormat



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
TypedArgBase* TypedArgBase::addFormatPos( int, IFormat* f)
{

   delete f;

   throw std::logic_error( "Variable '" + mVarName + "' does not store multiple"
      " values, use addFormat() without index paramater");

   return nullptr;
} // TypedArgBase::addFormatPos



/// Defines a formatter for the key of containers with key-value pairs.
///
/// @param[in]  f  Ignored here.
/// @return  Never in this base class.
/// @throw  std::logic_error when executed in the base class.
/// @since  1.41.0, 18.02.2020
TypedArgBase* TypedArgBase::addFormatKey( IFormat* f)
{

   delete f;

   throw std::logic_error( "Variable '" + mVarName + "' does not support "
      "different key/value formatters");

   return nullptr;
} // TypedArgBase::addFormatKey



/// Defines a formatter for the values of containers with key-value pairs.
/// 
/// @param[in]  f  Ignored here.
/// @return  Never in this base class.
/// @throw  std::logic_error when executed in the base class.
/// @since  1.41.0, 18.02.2020
TypedArgBase* TypedArgBase::addFormatValue( IFormat* f)
{

   delete f;

   throw std::logic_error( "Variable '" + mVarName + "' does not support "
      "different key/value formatters");

   return nullptr;
}



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
void TypedArgBase::format( string& val, int value_idx) const
{

   // since the format container is only filled when at least one formatter was
   // added, a value index greater than the size of the container is not
   // necessarily an error, it only means that no formatter was defined for the
   // given value (position)
   // since we cannot check (easily) if the given index is too high, we also
   // omit the check if the index is too low
   // we just check the range to make sure we don't access a non-existing
   // element
   if ((-1 <= value_idx) && (value_idx + 1 < static_cast< int>( mFormats.size())))
   {
      for (auto const& stored_format : mFormats[ value_idx + 1])
      {
         stored_format->formatValue( val);
      } // end for
   } // end if

} // TypedArgBase::format



/// Adds a value check.
///
/// @param[in]  c
///    Pointer to the object that checks the value, is deleted when it could
///    not be stored.
/// @return  Pointer to this object.
/// @throw
///    std::logic_error" when called for an argument that does not accept
///    values.
///    std::invalid_argument when the given object pointer is NULL.
/// @since
///    0.2, 10.04.2016
TypedArgBase* TypedArgBase::addCheck( ICheck* c)
{

   if (mValueMode == ValueMode::none)
   {
      delete c;
      throw std::logic_error( "calling addCheck() not allowed for variable '"
         + mVarName + "' (because it doesn't accept values)");
   } // end if

   if (c == nullptr)
      throw std::invalid_argument( "must provide valid object for value checks "
         "on variable '" + mVarName + "'");

   for (auto const& check_iter : mChecks)
   {
      if (!check_iter->combinationAllowed( c))
         throw std::logic_error( "two checks of the same kind are not allowed");
   } // end for

   mChecks.push_back( c);

   return this;
} // TypedArgBase::addCheck



/// Calls all check methods defined for this argument. The check methods
/// throw an exception when a check failed, so: No exception, value can be
/// stored.
/// @param[in]  val
///    The value to check in string format.
/// @since
///    0.2, 10.04.2016
void TypedArgBase::check( const string& val) const
{

   for (auto const& stored_checks : mChecks)
   {
      stored_checks->checkValue( val);
   } // end for

} // TypedArgBase::check


/// Returns a text description of the check specified for this argument.
/// @return
///    A string with the description of the check.
/// @since
///    0.16.0, 12.08.2017
string TypedArgBase::checkStr() const
{

   if (mChecks.empty())
      return "-";

   return format::toString( mChecks.begin(), mChecks.end());
} // TypedArgBase::checkStr



/// Returns a text description of the formats specified for this argument.
///
/// @return  A string with the description of the formatters.
/// @since  1.33.0, 05.11.2019
string TypedArgBase::formatStr() const
{

   if (mFormats.empty())
      return "-";

   std::ostringstream  oss;

   if (mFormats[ 0].size() > 0)
   {
      oss << "all: ";
      formatStr( oss, mFormats[ 0]);
   } // end if

   for (int i = 1; i < static_cast< int>( mFormats.size()); ++i)
   {
      if (mFormats[ i].empty())
         continue; // for

      if (!oss.str().empty())
         oss << "; ";
      oss << "idx " << i - 1 << ": ";
      formatStr( oss, mFormats[ i]);
   } // end for

   return oss.str();
} // TypedArgBase::formatStr



/// Returns a text description of the constraint specified for this argument.
/// @return
///    A string with the description of the constraint.
/// @since
///    0.16.0, 15.08.2017
string TypedArgBase::constraintStr() const
{

   if (mConstraints.empty())
      return "-";

   return format::toString( mConstraints.begin(), mConstraints.end());
} // TypedArgBase::constraintStr



/// Adds a constraint to this argument. The constraint is only evaluated when
/// the argument is actually used.
///
/// @param[in]  fun
///    Function to call to get the constraint object.
/// @return
///    Pointer to this object.
/// @throws  std::invalid_argument
///    when the given function is invalid, or the constraints container has
///    not been set yet.
/// @since  1.47.0, 05.12.2021
///    (parameter is now a function object)
/// @since  0.2, 10.04.2016
TypedArgBase* TypedArgBase::addConstraint(
      std::function< detail::IArgConstraint*( ConstraintContainer*)> fun)
      noexcept( false)
{

   if (mpConstraintsContainer == nullptr)
      throw std::invalid_argument( "constraints container has not been defined "
         "yet");
   if (!fun)
      throw std::invalid_argument( "function is invalid");

   mConstraints.push_back( fun( mpConstraintsContainer));

   return this;
} // TypedArgBase::addConstraint



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
TypedArgBase* TypedArgBase::setCardinality( ICardinality* c)
{

   // check if c == nullptr should not be necessary
   mpCardinality.reset( c);

   return this;
} // TypedArgBase::setCardinality



/// After all arguments were processed, checks if the cardinality
/// requirement (e.g. minimum number of values) was met.
/// @since
///    0.2, 10.04.2016
void TypedArgBase::checkCardinality()
{

   if (mpCardinality)
      mpCardinality->check();

} // TypedArgBase::checkCardinality



/// Returns a text description of the cardinality specified for this argument.
///
/// @return  A string with the description of the cardinality.
/// @since  1.14.0, 02.10.2018
string TypedArgBase::cardinalityStr() const
{

   return mpCardinality ? mpCardinality->cardinalityStr() : string( "none");
} // TypedArgBase::cardinalityStr



/// Allows to change the "original value check" mode. This is only applicable
/// to typed arg value objects.
/// @param[in]  yesNo
///    Set to \c false for turning the value check off.
/// @return
///    Pointer to this object.
/// @since
///    1.1.0, 16.11.2017
TypedArgBase* TypedArgBase::checkOriginalValue( bool)
{

   throw std::invalid_argument( "may not change 'check original value' "
      "mode on variable '" + mVarName + "'");

} // TypedArgBase::checkOriginalValue



/// Marks an argument as deprecated.
/// @return
///    Pointer to this object.
/// @since
///    1.6.0, 30.04.2018
TypedArgBase* TypedArgBase::setIsDeprecated()
{

   if (mIsMandatory)
      throw std::logic_error( "mandatory argument for variable '" + mVarName
         + "' cannot be set 'deprecated'");

   mIsDeprecated = true;
   return this;
} // TypedArgBase::setIsDeprecated



/// Marks an argument as replaced by another argument.
/// @return
///    Pointer to this object.
/// @since
///    1.6.0, 03.07.2018
TypedArgBase* TypedArgBase::setReplacedBy( const std::string& new_arg_key)
{

   if (mIsMandatory)
      throw std::logic_error( "mandatory argument for variable '" + mVarName
         + "' cannot be set 'replaced by'");

   mIsDeprecated = true;
   mReplacedBy = new_arg_key;

   return this;
} // TypedArgBase::setReplacedBy



/// Used for printing an argument and its destination variable.<br>
/// This function should be overloaded by derived classes.
/// @param[out]  os
///    The stream to print to.
/// @since
///    0.2, 10.04.2016
void TypedArgBase::dump( std::ostream& os) const
{

   os << "sets value on '" << mVarName << "'.";

} // TypedArgBase::dump



/// Should be called by the assign() methods in the derived classes:<br>
/// Handle all the constraints defined for this object.
/// @since
///    0.2, 10.04.2016
void TypedArgBase::activateConstraints()
{

   for (auto & curr_constraint : mConstraints)
   {
      curr_constraint->executeConstraint( mKey);
   } // end for

} // TypedArgBase::activateConstraints



/// Returns if the values in the objects intersect.
/// In the base class: Throws always.
///
/// @return  Here: Nothing, always throws.
/// @throw  std::invalid_argument in the base class.
/// @since   1.34.1, 12.01.2020
bool TypedArgBase::hasIntersection( TypedArgBase*) const noexcept( false)
{

   throw std::invalid_argument( "hasIntersection() may not be used with variable"
      " '" + mVarName + "'");

   return false;
} // TypedArgBase::hasIntersection



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
int TypedArgBase::compareValue( const TypedArgBase*) const noexcept( false)
{

   throw std::invalid_argument( "compareValue() may not be used with variable"
      " '" + mVarName + "'");

   return false;
} // TypedArgBase::compareValue



/// Prints all properties of a destination variable.
///
/// @param[in]  os  The stream to print to.
/// @since  1.33.0, 01.11.2019  (moved here from handler class)
void TypedArgBase::printProperties( std::ostream& os) const
{

   os << "Properties:\n"
      << "   destination variable name:  " << mVarName << '\n'
      << "   destination variable type:  " << varTypeName() << '\n'
      << "   is mandatory:               " << std::boolalpha << mIsMandatory
      << '\n'
      << "   value mode:                 " << mValueMode << '\n'
      << "   cardinality:                " << cardinalityStr() << '\n'
      << "   checks:                     " << checkStr() << '\n'
      << "   check original value:       " << mCheckOrigValue << '\n'
      << "   formats:                    " << formatStr() << '\n'
      << "   constraints:                " << constraintStr() << '\n'
      << "   is hidden:                  " << mIsHidden  << '\n'
      << "   takes multiple values:      " << mTakeMultipleValues << '\n'
      << "   allows inverting:           " << mAllowsInverting << '\n'
      << "   is deprecated:              " << mIsDeprecated << '\n'
      << "   is replaced:                " << isReplaced() << '\n';

   if (!mReplacedBy.empty())
      os << "   replaced by:                " << mReplacedBy << '\n';

   os << std::endl;

} // TypedArgBase::printProperties



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
ostream& operator <<( ostream& os, const TypedArgBase* tab)
{

   tab->dump( os);

   return os;
} // operator <<



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
TypedArgBase::TypedArgBase( const std::string& vname, ValueMode vm,
                            bool printDef):
   mKey( "-"),
   mVarName( vname),
   mValueMode( vm),
   mPrintDefault( printDef),
   mReplacedBy(),
   mUnitString(),
   mChecks(),
   mFormats(),
   mpCardinality( new CardinalityMax( 1)),
   mConstraints()
{
} // TypedArgBase::TypedArgBase



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
TypedArgBase* TypedArgBase::internAddFormat( int val_idx, IFormat* f)
{

   if (mValueMode == ValueMode::none)
   {
      delete f;
      throw std::logic_error( "calling addFormat() not allowed for variable '"
         + mVarName + "' that doesn't accept values");
   } // end if

   if (f == nullptr)
      throw std::invalid_argument( "must provide valid object for formatting on"
         " variable '" + mVarName + "'");

   if (static_cast< int>( mFormats.size()) <= val_idx)
      mFormats.resize( val_idx + 10);

   mFormats[ val_idx].emplace_back( f);

   return this;
} // TypedArgBase::internAddFormat



/// Creates a list of the name of the formatters set for a specific index.
///
/// @param[in]  os
///    The stream to write to.
/// @param[in]  formatters
///    The container with the formatters for a specific index.
/// @since  1.33.0, 05.11.2019
void TypedArgBase::formatStr( std::ostream& os,
   const value_format_cont_t& formatters)
{

   bool  first = true;

   for (auto const& formatter : formatters)
   {
      if (!first)
         os << ", ";
      os << formatter->desc();
      first = false;
   } // end for

} // TypedArgBase::formatStr



/// Returns the number of formatters added for this argument.
///
/// @return  The number of formatters that have been added.
/// @since  1.32.0, 19.08.2019
size_t TypedArgBase::numFormats() const
{

   size_t  result = 0;


   for (auto const& val_format : mFormats)
   {
      result += val_format.size();
   } // end for

   return result;
} // TypedArgBase::numFormats



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
ostream& operator <<( ostream& os, const TypedArgBase& tab)
{

   std::string  deprecated_str;


   if (tab.mIsDeprecated)
   {
      if (tab.mReplacedBy.empty())
         deprecated_str = "deprecated, ";
      else
         deprecated_str = "replaced by "
            + format::toString( tab.mReplacedBy) + ", ";
   } // end if

   os << "value " << tab.mValueMode << ", "
      << (tab.mIsMandatory ? "mandatory, " : "optional, ")
      << (tab.takesMultiValue() ? "takes" : "does not take") << " multiple&separate values, "
      << (tab.mPrintDefault ? "" : "don't ") << "print dflt, "
      << (tab.mIsHidden ? "hidden, " : "")
      << deprecated_str
      << (tab.mChecks.empty() ? "no" : boost::lexical_cast< string>( tab.mChecks.size()))
      << " checks, "
      << (tab.mFormats.empty() ? "no" : boost::lexical_cast< string>( tab.numFormats()))
      << " formats.";

   return os;
} // operator <<



/// Prints the value of the enum in readable form.
/// @param[out]  os
///    The stream to print to.
/// @param[in]   vm
///    The enum value to print.
/// @return
///    The stream as passed in.
/// @since
///    0.2, 10.04.2016
ostream& operator <<( ostream& os, TypedArgBase::ValueMode vm)
{

   os << "'" << TypedArgBase::valueMode2str( vm)
      << "' (" << static_cast< int>( vm) << ")";

   return os;
} // operator <<



} // namespace celma::prog_args::detail


// =====  END OF typed_arg_base.cpp  =====

