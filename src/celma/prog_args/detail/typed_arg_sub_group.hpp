
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
/// @since  0.15.0, 17.07.2017  (use type ArgumentKey instead of string for
///                             arguments)
/// @since  0.2, 10.04.2016
class TypedArgSubGroup: public TypedArgBase
{
public:
   /// Constructor.
   /// @param[in]  key     The complete argument specification with short and/or
   ///                     long argument.
   /// @param[in]  ah_obj  The argument handler object.
   /// @since  0.2, 10.04.2016
   TypedArgSubGroup( const ArgumentKey& key, Handler& ah_obj);

   /// Empty, virtual default destructor.
   ///
   /// @since  1.32.0, 27.08.2019
   virtual ~TypedArgSubGroup() = default;

   /// Returns "subgroup".
   ///
   /// @return  Constant string "subgroup".
   /// @since  1.14.0, 28.09.2018
   const std::string varTypeName() const override;

   /// Required by framework, does nothing except setting the #mWasCalled flag.
   /// @since  0.2, 10.04.2016
   void assign( const std::string& /* value */, bool /* inverted */) override;

   /// Returns if the function was called or not.
   /// @return  \c true if function was called, \c false otherwise.
   /// @since  0.2, 10.04.2016
   bool hasValue() const override;

   /// Should not be called. Prints the text "subgroup".
   /// @param[in]  os
   ///    The stream to print the value to.
   /// @param[in]  print_type
   ///    Specifies if the type of the destination variable should be printed
   ///    too.
   /// @since
   ///    1.8.0, 05.07.2018
   void printValue( std::ostream& os, bool print_type) const override;

   /// Returns the argument handler object.
   /// @return  The object stored internally.
   /// @since  0.2, 10.04.2016
   Handler* obj() const;

private:
   /// The argument handler object.
   Handler&  mArgHandler;
   /// Flag set when the function is called.
   bool      mWasCalled;

}; // TypedArgSubGroup


// inlined methods
// ===============


inline bool TypedArgSubGroup::hasValue() const
{
   return mWasCalled;
} // TypedArgSubGroup::hasValue


inline void TypedArgSubGroup::printValue( std::ostream&, bool) const
{
   // will never be called
} // TypedArgSubGroup::printValue


inline Handler* TypedArgSubGroup::obj() const
{
   return &mArgHandler;
} // TypedArgSubGroup::obj


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_TYPED_ARG_SUB_GROUP_HPP


// =====  END OF typed_arg_sub_group.hpp  =====

