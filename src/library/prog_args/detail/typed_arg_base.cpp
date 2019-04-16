
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
/// See documentation of class celma::prog_args::detail::TypedArgBase.


// module header file include
#include "celma/prog_args/detail/typed_arg_base.hpp"


// C++ Standard Library includes
#include <iostream>


// Boost includes
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/common/clear_container.hpp"
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {


using std::ostream;
using std::string;


/// Destructor, frees dynamically allocated memory.
/// @since
///    0.2, 10.04.2016
TypedArgBase::~TypedArgBase()
{

   common::Vector::clear( mChecks);
   common::Vector::clear( mFormats);
   common::Vector::clear( mConstraints);

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



/// Overwrites the 'value mode' which specifies if a value is needed for this
/// argument or not.<br>
/// Here in the base class, the only value mode that can be set is
/// 'required'.
/// @param[in]  vm
///    The new value mode.
/// @return
///    Pointer to this object.
/// @since
///    0.2, 10.04.2016
TypedArgBase* TypedArgBase::setValueMode( ValueMode vm) noexcept( false)
{

   if (vm != ValueMode::required)
      throw std::invalid_argument( std::string( "may not set value mode '") +
                                   valueMode2str( vm) + "' on variable '" +
                                   mVarName + "'");

   mValueMode = vm;
   return this;
} // TypedArgBase::setValueMode



/// Assigns a value.<br>
/// Checks if the argument is deprecated, or if a cardinality constraint is
/// violated. If not, the virtual method assign() is called to actually
/// assign the value, and finally activateConstraints() is called to activate
/// the contrainst (sic!) triggered by this argument.
///
/// @param[in]  ignore_cardinality
///    Specifies if the cardinality of calls/value assignments should be
///    ignored.
/// @param[in]  value
///    The value to assign, in string format.
/// @since
///    1.6.0, 29.06.2018  (renamed from calledAssign)
/// @since
///    0.2, 10.04.2016
void TypedArgBase::assignValue( bool ignore_cardinality, const string& value)
{

   if (mIsDeprecated)
   {
      if (mReplacedBy.empty())
         throw std::runtime_error( "argument '" + format::toString( mKey)
            + "' is deprecated!");
      else
         throw std::runtime_error( "argument '" + format::toString( mKey)
            + "' has been replaced by '" + mReplacedBy + "'!");
   } // end if

   if (!ignore_cardinality && mpCardinality)
      mpCardinality->gotValue();

   assign( value);
   activateConstraints();

} // TypedArgBase::assignValue



/// Adds a value formatter: The value from the argument list (command line)
/// is formatted before it is checked and/or stored.
///
/// @param[in]  f
///    Pointer to the formatter to add, is deleted when it could not be
///    stored.
/// @return  Pointer to this object.
///    - "logic error" when called for an argument that does not accept
///      values.
///    - "invalid argument" when the given object pointer is NULL.
/// @since
///    0.2, 10.04.2016
TypedArgBase* TypedArgBase::addFormat( IFormat* f) noexcept( false)
{

   if (mValueMode == ValueMode::none)
   {
      delete f;
      throw std::logic_error( "calling addFormat() not allowed for variable '"
         + mVarName + "' (because it doesn't accept values)");
   } // end if

   if (f == nullptr)
      throw std::invalid_argument( "must provide valid object for formatting on"
         " variable '" + mVarName + "'");

   mFormats.push_back( f);

   return this;
} // TypedArgBase::addFormat



/// Calls all formatter methods defined for this argument. The formatter
/// methods should throw an exception when a formatting failed.
/// @param[in,out]  val
///    The value to format.
/// @since
///    0.2, 10.04.2016
void TypedArgBase::format( string& val) const
{

   for (auto const& stored_format : mFormats)
   {
      stored_format->formatValue( val);
   } // end for

} // TypedArgBase::format



/// Adds a value check.
///
/// @param[in]  c
///    Pointer to the object that checks the value, is deleted when it could
///    not be stored.
/// @return  Pointer to this object.
/// @throws
///    - "logic error" when called for an argument that does not accept
///      values.
///    - "invalid argument" when the given object pointer is NULL.
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
/// @param[in]  iac
///    Pointer to the contraint object to add to this argument.
/// @return
///    Pointer to this object.
/// @since
///    0.2, 10.04.2016
TypedArgBase* TypedArgBase::addConstraint( IArgConstraint* iac)
{

   if (iac == nullptr)
      throw std::invalid_argument( "invalid NULL pointer added as constraint");

   mConstraints.push_back( iac);

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
   mChecks(),
   mFormats(),
   mpCardinality( new CardinalityMax( 1)),
   mConstraints()
{
} // TypedArgBase::TypedArgBase



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
         deprecated_str = "replaced by '"
            + format::toString( tab.mReplacedBy) + "', ";
   } // end if

   os << "value " << tab.mValueMode << ", "
      << (tab.mIsMandatory ? "mandatory, " : "optional, ")
      << (tab.takesMultiValue() ? "takes" : "does not take") << " multiple&separate values, "
      << (tab.mPrintDefault ? "" : "don't ") << "print dflt, "
      << (tab.mIsHidden ? "hidden, " : "")
      << deprecated_str
      << (tab.mChecks.empty() ? "no" : boost::lexical_cast< string>( tab.mChecks.size()))
      << " checks, "
      << (tab.mFormats.empty() ? "no" : boost::lexical_cast< string>( tab.mFormats.size()))
      << " formats";

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



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF typed_arg_base.cpp  =====

