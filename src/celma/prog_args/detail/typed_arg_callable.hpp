
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
/// See documentation of template celma::prog_args::detail::TypedArgCallable.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_HPP


#include <iostream>
#include <string>
#include "celma/prog_args/detail/arg_handler_callable.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Helper class to store a function that serves as argument handler.
/// @since  0.15.0, 17.07.2017  (use type ArgumentKey instead of string for
///                             arguments)
/// @since  0.2, 10.04.2016
class TypedArgCallable: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  fun    The function to call when the argument is set on the
   ///                    command line.
   /// @param[in]  fname  The name of the function to call.
   /// @since  0.16.0, 10.11.2017  (removed key parameter)
   /// @since  0.2, 10.04.2016
   TypedArgCallable( ArgHandlerCallable fun, const std::string& fname);

   /// Returns "callable" as type name.
   /// @return  The string "callable".
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

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Executes the specified function.
   ///
   /// @param[in]  value
   ///    Ignored.
   /// @param[in]  inverted
   ///    Set when the argument supports inversion and when the argument was 
   ///    preceeded preceeded by an exclamation mark.
   /// @since  1.27.0, 24.05.2019
   ///    (added parameter inverted)
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value, bool inverted) override;

   /// Reference of the destination variable to store the value in.
   ArgHandlerCallable  mFun;
   /// Flag set when the function is called.
   bool                mWasCalled = false;

}; // TypedArgCallable


// inlined methods
// ===============


inline TypedArgCallable::TypedArgCallable( ArgHandlerCallable fun,
                                           const std::string& fname):
   TypedArgBase( fname, ValueMode::none, false),
   mFun( fun)
{
} // TypedArgCallable::TypedArgCallable


inline const std::string TypedArgCallable::varTypeName() const
{
   return "callable";
} // TypedArgCallable::varTypeName


inline bool TypedArgCallable::hasValue() const
{
   return mWasCalled;
} // TypedArgCallable::hasValue


inline void TypedArgCallable::printValue( std::ostream& os, bool) const
{
   os << "[callable]";
} // TypedArgCallable::printValue


inline void TypedArgCallable::dump( std::ostream& os) const
{
   os << "calls function/method '" << mVarName << "'." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArgCallable::dump


inline void TypedArgCallable::assign( const std::string&, bool inverted)
{
   mFun( inverted);
   mWasCalled = true;
} // TypedArgCallable::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_HPP


// =====  END OF typed_arg_callable.hpp  =====

