
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
/// See documentation of class celma::prog_args::detail::TypedArgSubGroup.


// module header file include
#include "celma/prog_args/detail/typed_arg_sub_group.hpp"


// project includes
#include "celma/prog_args/handler.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @param[in]  arg_spec  The complete argument specification with short and/
///                       or long argument.
/// @param[in]  ah_obj    The argument handler object.
/// @since  0.2, 10.04.2016
TypedArgSubGroup::TypedArgSubGroup( const ArgumentKey& key,
                                    Handler& ah_obj):
   TypedArgBase( "sub-group", ValueMode::none, false),
   mArgHandler( ah_obj),
   mWasCalled( false)
{

   setKey( key);
   // a sub-group can hold multiple arguments, so it should be possible to call
   // it multiple times
   mpCardinality.reset();

} // TypedArgSubGroup::TypedArgSubGroup



/// Returns "subgroup".
///
/// @return  Constant string "subgroup".
/// @since  1.14.0, 28.09.2018
const std::string TypedArgSubGroup::varTypeName() const
{

   return "subgroup";
} // TypedArgSubGroup::varTypeName



/// Required by framework, does nothing except setting the #mWasCalled flag.
/// @since  0.2, 10.04.2016
void TypedArgSubGroup::assign( const std::string& /* value */)
{

   mWasCalled = true;

} // TypedArgSubGroup::assign



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF typed_arg_sub_group.cpp  =====

