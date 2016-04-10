
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
/// See documentation of class celma::prog_args::detail::TypedArgSubGroup.


#ifndef CELMA_PROG_ARGS_DETAIL_TYPED_ARG_SUB_GROUP_HPP
#define CELMA_PROG_ARGS_DETAIL_TYPED_ARG_SUB_GROUP_HPP


#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args {


// forward declaration
class Handler;


namespace detail {


/// Helper class to store an argument handler object that handles a sub-group of
/// arguments.
/// @since  0.2, 10.04.2016
class TypedArgSubGroup: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  arg_spec  The complete argument specification with short and/
   ///                       or long argument.
   /// @param[in]  ah_obj    The argument handler object.
   /// @since  0.2, 10.04.2016
   TypedArgSubGroup( const std::string& arg_spec, Handler* ah_obj);

   /// Required by framework, does nothing except setting the #mWasCalled flag.
   /// @since  0.2, 10.04.2016
   virtual void assign( const std::string& /* value */);

   /// Returns if the function was called or not.
   /// @return  \c true if function was called, \c false otherwise.
   /// @since  0.2, 10.04.2016
   virtual bool hasValue() const;

   /// Returns the argument handler object.
   /// @return  The object stored internally.
   /// @since  0.2, 10.04.2016
   Handler* obj() const;

private:
   /// The argument handler object.
   Handler*  mpArgHandler;
   /// Flag set when the function is called.
   bool      mWasCalled;

}; // TypedArgSubGroup


// inlined methods
// ===============


inline bool TypedArgSubGroup::hasValue() const
{
   return mWasCalled;
} // end TypedArgSubGroup::hasValue


inline Handler* TypedArgSubGroup::obj() const
{
   return mpArgHandler;
} // end TypedArgSubGroup::obj


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_SUB_GROUP_HPP


// =========================  END OF typed_arg_sub_group.hpp  =========================

