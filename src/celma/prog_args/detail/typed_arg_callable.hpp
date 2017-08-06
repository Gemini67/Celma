
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
/// See documentation of template celma::prog_args::detail::TypedArgCallable.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_HPP


#include <iostream>
#include <string>
#include "celma/prog_args/detail/arg_handler_callable.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Helper class to store a function that serves as argument handler.
/// @since  x.y.z, 17.07.2017  (use type ArgumentKey instead of string for
///                             arguments)
/// @since  0.2, 10.04.2016
class TypedArgCallable: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  key    The complete argument specification with short and/or
   ///                    long argument.
   /// @param[in]  fun    The function to call when the argument is set on the
   ///                    command line.
   /// @param[in]  fname  The name of the function to call.
   /// @since  0.2, 10.04.2016
   TypedArgCallable( const ArgumentKey& key, ArgHandlerCallable fun,
                     const std::string& fname);

   /// Returns if the function was called or not.
   /// @return  \c true if function was called, \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const override;

protected:
   /// Used for printing an argument and its destination variable.
   /// @param[out]  os  The stream to print to.
   /// @since  0.2, 10.04.2016
   virtual void dump( std::ostream& os) const override;

private:
   /// Executes the specified function.
   /// @param[in]  value  Ignored.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& value) override;

   /// Reference of the destination variable to store the value in.
   ArgHandlerCallable  mFun;
   /// Flag set when the function is called.
   bool                mWasCalled;

}; // TypedArgCallable


// inlined methods
// ===============


inline TypedArgCallable::TypedArgCallable( const ArgumentKey& key,
                                           ArgHandlerCallable fun,
                                           const std::string& fname):
   TypedArgBase( key, fname, ValueMode::none, false),
   mFun( fun),
   mWasCalled( false)
{
} // TypedArgCallable::TypedArgCallable


inline bool TypedArgCallable::hasValue() const
{
   return mWasCalled;
} // TypedArgCallable::hasValue


inline void TypedArgCallable::dump( std::ostream& os) const
{
   os << "calls function/method '" << mVarName << "'." << std::endl
      << "   " << static_cast< const TypedArgBase&>( *this);
} // TypedArgCallable::dump


inline void TypedArgCallable::assign( const std::string&)
{
   mFun();
   mWasCalled = true;
} // TypedArgCallable::assign


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_CALLABLE_HPP


// ======================  END OF typed_arg_callable.hpp  ======================

