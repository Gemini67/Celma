
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template celma::prog_args::detail::TypedArgValue.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_VALUE_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_VALUE_HPP


#include <cstring>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "celma/common/check_assign.hpp"
#include "celma/common/tokenizer.hpp"
#include "celma/common/type_name.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/cardinality_max.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


// Template TypedArgValue
// ======================


/// Helper class to handle a 'value' argument: Only the argument needs to be
/// set on the command line, the value to set is specified on the argument.<br>
/// Use this when multiple arguments are used to set different values in the
/// same destination variable.
/// By default is checked that the original value of the destination variable is
/// modified only once. To allow multiple changes, i.e. the last argument that
/// modifies the value wins, set checkOriginalValue() to \c false.
/// @tparam  T  The type of the value.
/// @since  1.1.0, 25.09.2017
template< typename T> class TypedArgValue: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  dest   The destination variable to store the value in.
   /// @param[in]  vname  The name of the destination variable to store the
   ///                    value in.
   /// @param[in]  value  The value to set.
   /// @since  1.1.0, 25.09.2017
   TypedArgValue( T& dest, const std::string& vname, const T& value);

   /// Returns if the destination has a value set.<br>
   /// Of course this applies only when the value through the current object.
   /// @return  \c true if the destination variable contains a value.
   /// @since  1.1.0, 25.09.2017
   virtual bool hasValue() const override;

   /// This type doesn't allow to change the value mode: Throws always.
   /// @param[in]  vm  Ignored.
   /// @return  Pointer to this object.
   /// @throw  std::logic_error.
   /// @since  1.1.0, 25.09.2017
   virtual TypedArgBase* setValueMode( ValueMode vm) noexcept( false) override;

   /// Adds the value of the destination variable to the string.
   /// @param[out]  dest  The string to append the default value to.
   /// @since  1.1.0, 25.09.2017
   virtual void defaultValue( std::string& dest) const override;

   /// Allows to change the "original value check" mode.
   /// @param[in]  yesNo  Set to \c false for turning the value check off.
   /// @return  Pointer to this object.
   /// @since  1.1.0, 16.11.2017
   virtual TypedArgBase* checkOriginalValue( bool yesNo) noexcept( false)
      override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  1.1.0, 25.09.2017
   virtual void dump( std::ostream& os) const override;

private:
   /// Stores the value in the destination variable.
   /// @param[in]  value  Ignored.
   /// @since  1.1.0, 25.09.2017
   virtual void assign( const std::string& value) override;

   /// Reference of the destination variable to store the value in.
   T&       mDestVar;
   /// The value to set when the argument is used.
   const T  mValue;
   /// The original value of the destination variable when the object was
   /// created. Used to detect multiple assignments to the same destination
   /// variable through multiple arguments.
   const T  mOrigValue;
   /// Flag, set when the argument was found/the value is set.
   bool     mHasValueSet = false;

}; // TypedArgValue< T>


// inlined methods
// ===============


template< typename T>
   TypedArgValue< T>::TypedArgValue( T& dest, const std::string& vname,
                                     const T& value):
      TypedArgBase( vname, ValueMode::none, true),
      mDestVar( dest),
      mValue( value),
      mOrigValue( dest)
{
   mCheckOrigValue = true;
   mpCardinality.reset( new CardinalityMax( 1));
} // TypedArgValue< T>::TypedArgValue


template< typename T> bool TypedArgValue< T>::hasValue() const
{
   return mHasValueSet;
} // TypedArgValue< T>::hasValue


template< typename T>
   TypedArgBase* TypedArgValue< T>::setValueMode( ValueMode) noexcept( false)
{
   throw std::logic_error( "cannot change the value mode on variable '"
                           + mVarName + "'");
} // TypedArgValue< T>::setValueMode


template< typename T> void TypedArgValue< T>::defaultValue( std::string&) const
{
} // TypedArgValue< T>::defaultValue


template< typename T>
   TypedArgBase* TypedArgValue< T>::checkOriginalValue( bool yesNo)
{
   mCheckOrigValue = yesNo;
   return this;
} // TypedArgValue::checkOriginalValue


template< typename T> void TypedArgValue< T>::dump( std::ostream& os) const
{
   os << "value type '" << type< T>::name() << "', destination '"
      << mVarName << "', set-value '" << mValue << "', ";
   if (mHasValueSet)
      os << "value = " << mDestVar << "." << std::endl;
   else 
      os << "value not set." << std::endl;
   os << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArgValue< T>::dump


template< typename T> void TypedArgValue< T>::assign( const std::string&)
{
   if (mCheckOrigValue && (mDestVar != mOrigValue))
      throw std::runtime_error( "destination variable '" + mVarName
         + "' has already been set to '" + format::toString( mDestVar) + "'");
   mDestVar = mValue;
   mHasValueSet = true;
} // TypedArgValue< T>::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_VALUE_HPP


// =======================  END OF typed_arg_value.hpp  =======================

