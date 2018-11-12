
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
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
/// @since  0.15.0, 17.07.2017  (use type ArgumentKey instead of string for
///                             arguments)
/// @since  0.2, 10.04.2016
class TypedArgCallableValue: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  fun    The function to call when the argument is set on the
   ///                    command line.
   /// @param[in]  fname  The name of the function to call.
   /// @since  0.16.0, 10.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArgCallableValue( ArgHandlerCallableValue fun,
                          const std::string& fname);

   /// Returns "callable-value".
   /// @return  The string "callable-value".
   /// @since  1.14.0, 28.09.2018
   virtual const std::string varTypeName() const override;

   /// Returns if the function was called or not.
   /// @return  \c true if function was called, \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override;

   /// Prints "callable" since there is no value to print.
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since
   ///    1.8.0, 05.07.2018
   virtual void printValue( std::ostream& os, bool print_type) const override;

   /// Allows to set the value mode to 'optional' (or required, but that is
   /// already the default).
   /// @param[in]  vm  The new value mode to set.
   /// @return  Pointer to this object.
   /// @since  0.13.2, 18.02.2017
   virtual TypedArgBase* setValueMode( ValueMode vm) noexcept( false) override;

   /// Callables with values may also accept multiple, separate values.
   /// @return  Pointer to this object.
   /// @since  0.2, 10.04.2016
   virtual TypedArgBase* setTakesMultiValue() override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Executes the specified function.
   /// @param[in]  value  The value to pass to the function.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value) override;

   /// Reference of the destination variable to store the value in.
   ArgHandlerCallableValue  mFun;
   /// Flag set when the function is called.
   bool                     mWasCalled = false;

}; // TypedArgCallableValue


// inlined methods
// ===============


inline TypedArgCallableValue::TypedArgCallableValue( ArgHandlerCallableValue fun,
                                                     const std::string& fname):
   TypedArgBase( fname, ValueMode::required, false),
   mFun( fun)
{
} // TypedArgCallableValue::TypedArgCallableValue


inline const std::string TypedArgCallableValue::varTypeName() const
{
   return "callable-value";
} // TypedArgCallableValue::varTypeName


inline bool TypedArgCallableValue::hasValue() const
{
   return mWasCalled;
} // TypedArgCallableValue::hasValue


inline void TypedArgCallableValue::printValue( std::ostream& os, bool) const
{
   os << "[callable(value)]";
} // TypedArgCallableValue::printValue


inline TypedArgBase* TypedArgCallableValue::setValueMode( ValueMode vm) noexcept( false)
{
   if ((vm == ValueMode::none) || (vm == ValueMode::unknown))
      throw std::invalid_argument( std::string( "may not set value mode '") +
                                   valueMode2str( vm) + "' on variable '" +
                                   mVarName + "'");
   mValueMode = vm;
   return this;
} // TypedArgCallableValue::setValueMode


inline TypedArgBase* TypedArgCallableValue::setTakesMultiValue()
{
   mTakeMultipleValues = true;
   return this;
} // TypedArgCallableValue::setTakesMultiValue


inline void TypedArgCallableValue::dump( std::ostream& os) const
{
   os << "calls function/method '" << mVarName << "'." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArgCallableValue::dump


inline void TypedArgCallableValue::assign( const std::string& value)
{
   mFun( value);
   mWasCalled = true;
} // TypedArgCallableValue::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_VALUE_HPP


// =====  END OF typed_arg_callable_value.hpp  =====

