
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
/// See documentation of template celma::prog_args::detail::TypedArgCallableValue.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_VALUE_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_VALUE_HPP


#include <iostream>
#include <string>
#include "celma/prog_args/detail/arg_handler_callable.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Helper class to store a function that serves as argument handler.
/// @since  0.2, 10.04.2016
class TypedArgCallableValue: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  fun       The function to call when the argument is set on
   ///                       the command line.
   /// @param[in]  fname     The name of the function to call.
   /// @since  0.2, 10.04.2016
   TypedArgCallableValue( const std::string& arg_spec,
                          ArgHandlerCallableValue fun,
                          const std::string& fname);

   /// Returns if the function was called or not.
   /// @return  \c true if function was called, \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const;

   /// Callables with values may also accept multiple, separate values.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setTakesMultiValue();

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const;

private:
   /// Executes the specified function.
   /// @param[in]  value  The value to pass to the function.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value);

   /// Reference of the destination variable to store the value in.
   ArgHandlerCallableValue  mFun;
   /// Flag set when the function is called.
   bool                     mWasCalled;

}; // TypedArgCallableValue


// inlined methods
// ===============


inline TypedArgCallableValue::TypedArgCallableValue( const std::string& arg_spec,
                                                     ArgHandlerCallableValue fun,
                                                     const std::string& fname):
   TypedArgBase( arg_spec, fname, vmRequired, false),
   mFun( fun),
   mWasCalled( false)
{
} // end TypedArgCallableValue::TypedArgCallableValue


inline bool TypedArgCallableValue::hasValue() const
{
   return mWasCalled;
} // end TypedArgCallableValue::hasValue


inline TypedArgBase* TypedArgCallableValue::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // end TypedArgCallableValue::setTakesMultiValue


inline void TypedArgCallableValue::dump( std::ostream& os) const
{
   os << "calls function/method '" << mVarName << "'." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // end TypedArgCallableValue::dump


inline void TypedArgCallableValue::assign( const std::string& value)
{
   mFun( value);
   mWasCalled = true;
} // end TypedArgCallableValue::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_VALUE_HPP


// =========================  END OF typed_arg_callable.hpp  =========================

