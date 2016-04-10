
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
/// See documentation of class celma::prog_args::detail::TypedArgBase.


// module header file include
#include "celma/prog_args/detail/typed_arg_base.hpp"


// C++ Standard Library includes
#include <iostream>


// Boost includes
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/common/clear_container.hpp"


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @param[in]  arg_spec  The complete argument specification with short and/
///                       or long argument.
/// @param[in]  vname     The name of the destination variable to store the
///                       value in.
/// @param[in]  vm        The value mode to set for this argument.
/// @param[in]  printDef  Specifies if the default value of the destination
///                       variable should be printed in the usage or not.
/// @since  0.2, 10.04.2016
TypedArgBase::TypedArgBase( const std::string& arg_spec, const string& vname,
                            ValueMode vm, bool printDef):
   mArgSpec( arg_spec),
   mVarName( vname),
   mValueMode( vm),
   mIsMandatory( false),
   mTakeMultipleValues( false),
   mPrintDefault( printDef),
   mIsHidden( false),
   mChecks(),
   mFormats(),
   mpCardinality( new CardinalityMax( 1)),
   mConstraints()
{
} // end TypedArgBase::TypedArgBase



/// Destructor, frees dynamically allocated memory.
/// @since  0.2, 10.04.2016
TypedArgBase::~TypedArgBase()
{

   common::Vector::clear( mChecks);
   common::Vector::clear( mFormats);
   common::Vector::clear( mConstraints);

} // end TypedArgBase::~TypedArgBase



/// Assigns a value.
/// @param[in]  ignore_cardinality  Specifies if the cardinality of calls/
///                                 value assignments should be ignored.
/// @param[in]  value               The value to assign, in string format.
/// @since  0.2, 10.04.2016
void TypedArgBase::calledAssign( bool ignore_cardinality, const string& value)
{

   if (!ignore_cardinality && (mpCardinality.get() != nullptr))
      mpCardinality->gotValue();

   assign( value);
   activateConstraints();

} // end TypedArgBase::calledAssign



/// Adds a value formatter: The value from the argument list (command line)
/// is formatted before it is checked and/or stored.
/// @param[in]  f  Pointer to the formatter to add.
/// @return  Pointer to this object.
/// @since  0.2, 10.04.2016
TypedArgBase* TypedArgBase::addFormat( IFormat* f)
{

   if (mValueMode == vmNone)
      throw logic_error( "calling addFormat() not allowed for variable '" +
                           mVarName + "' (because it doesn't accept values)");

   if (f == nullptr)
      throw logic_error( "must provide valid object for formatting on variable '" +
                         mVarName + "'");

   mFormats.push_back( f);

   return this;
} // TypedArgBase::addFormat



/// Calls all formatter methods defined for this argument. The formatter
/// methods should throw an exception when a formatting failed.
/// @param[in,out]  val  The value to format.
/// @since  0.2, 10.04.2016
void TypedArgBase::format( string& val) const
{

   for (size_t i = 0; i < mFormats.size(); ++i)
   {
      mFormats[ i]->formatValue( val);
   } // end for

} // end TypedArgBase::format



/// Adds a value check.
/// @param[in]  c  Pointer to the object that checks the value.
/// @return  Pointer to this object.
/// @since  0.2, 10.04.2016
TypedArgBase* TypedArgBase::addCheck( ICheck* c)
{

   if (mValueMode == vmNone)
      throw logic_error( "calling addCheck() not allowed for variable '" +
                         mVarName + "' (because it doesn't accept values)");

   if (c == nullptr)
      throw logic_error( "must provide valid object for value checks on variable '" +
                         mVarName + "'");

   mChecks.push_back( c);

   return this;
} // TypedArgBase::addCheck



/// Calls all check methods defined for this argument. The check methods
/// throw an exception when a check failed, so: No exception, value can be
/// stored.
/// @param[in]  val  The value to check in string format.
/// @since  0.2, 10.04.2016
void TypedArgBase::check( const string& val) const
{

   for (size_t i = 0; i < mChecks.size(); ++i)
   {
      mChecks[ i]->checkValue( val);
   } // end for

} // end TypedArgBase::check



/// Adds a constraint to this argument. The constraint is only evaluated when
/// the argument is actually used.
/// @param[in]  ic  Pointer to the contraint object to add to this argument.
/// @return  Pointer to this object.
/// @since  0.2, 10.04.2016
TypedArgBase* TypedArgBase::addConstraint( IConstraint* ic)
{

   mConstraints.push_back( ic);

   return this;
} // end TypedArgBase::addConstraint



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
TypedArgBase* TypedArgBase::setCardinality( ICardinality* c)
{

   // check if c == nullptr should not be necessary
   mpCardinality.reset( c);

   return this;
} // end TypedArgBase::setCardinality



/// After all arguments were processed, checks if the cardinality
/// requirement (e.g. minimum number of values) was met.
/// @since  0.2, 10.04.2016
void TypedArgBase::checkCardinality()
{

   if (mpCardinality.get() != nullptr)
      mpCardinality->check();

} // end TypedArgBase::checkCardinality



/// Used for printing an argument and its destination variable.<br>
/// This function should be overloaded by derived classes.
/// @param[out]  os  The stream to print to.
/// @since  0.2, 10.04.2016
void TypedArgBase::dump( std::ostream& os) const
{

   os << "sets value on '" << mVarName << "'.";

} // end TypedArgBase::dump



/// Should be called by the assign() methods in the derived classes:<br>
/// Handle all the constraints defined for this object.
/// @since  0.2, 10.04.2016
void TypedArgBase::activateConstraints()
{

   for (size_t i = 0; i < mConstraints.size(); ++i)
   {
      mConstraints[ i]->executeConstraint( mArgSpec);
   } // end for

} // end TypedArgBase::activateConstraints


/// Called for printing an argument and its destination variable.<br>
/// Calls dump() which can be overloaded by derived classes.
/// @param[out]  os   The stream to write to.
/// @param[in]   tab  Pointer to the object to print.
/// @return  The stream as passed in.
/// @since  0.2, 10.04.2016
ostream& operator <<( ostream& os, const TypedArgBase* tab)
{

   tab->dump( os);

   return os;
} // end operator <<



/// Prints the values of the settings/flags managed by this class (except the
/// name of the destination variable).
/// @param[out]  os   The stream to print to.
/// @param[in]   tab  The object to print.
/// @return  The stream as passed in.
/// @since  0.2, 10.04.2016
ostream& operator <<( ostream& os, const TypedArgBase& tab)
{

   os << "value " << tab.mValueMode << ", "
      << (tab.mIsMandatory ? "mandatory, " : "optional, ")
      << (tab.takesMultiValue() ? "takes" : "does not take") << " multiple&separate values, "
      << (tab.mPrintDefault ? "" : "don't ") << "print dflt, "
      << (tab.mIsHidden ? "hidden, " : "visible, ")
      << (tab.mChecks.empty() ? "no" : boost::lexical_cast< string>( tab.mChecks.size()))
      << " checks, "
      << (tab.mFormats.empty() ? "no" : boost::lexical_cast< string>( tab.mFormats.size()))
      << " formats";

   return os;
} // end operator <<



/// Prints the value of the enum in readable form.
/// @param[out]  os  The stream to print to.
/// @param[in]   vm  The enum value to print.
/// @return  The stream as passed in.
/// @since  0.2, 10.04.2016
ostream& operator <<( ostream& os, TypedArgBase::ValueMode vm)
{

   switch (vm)
   {
   case TypedArgBase::vmNone:      os << "'no value'";  break;
   case TypedArgBase::vmOptional:  os << "'optional'";  break;
   case TypedArgBase::vmRequired:  os << "'required'";  break;
   default:                        os << "'unknown'";   break;
   } // end switch

   os << " (" << static_cast< int>( vm) << ")";

   return os;
} // end operator <<



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF typed_arg_base.cpp  =========================
