
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class
/// celma::prog_args::detail::IHandlerValueConstraint.


// module headerfile include
#include "celma/prog_args/detail/i_handler_value_constraint.hpp"


// project includes
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Returns \c true.
///
/// @return  Always \c true.
/// @since  x.y.z, 23.10.2019
bool IHandlerValueConstraint::isValueConstraint() const
{

   return true;
} // IHandlerValueConstraint::isValueConstraint



/// Stores the pointer to the handler object for one of the arguments in the
/// argument list.
/// These objects are needed by the actual constraint implementations to
/// compare the values.
///
/// @param[in]  handler  Pointer to the argument handler object.
/// @since  x.y.z, 22.10.2019
void IHandlerValueConstraint::storeArgumentHandler( TypedArgBase* handler)
{

   mArgHandlers.push_back( handler);

} // IHandlerValueConstraint::storeArgumentHandler



/// Constructor.
///
/// @param[in]  constraint_name
///    The name of the constraint for error messages.
/// @param[in]  arg_spec
///    The list of arguments affected by the constraint.<br>
///    Must already be checked by the calling function (not empty, no invalid
///    arguments).
/// @since  x.y.z, 22.10.2019
IHandlerValueConstraint::IHandlerValueConstraint(
   const std::string& constraint_name,
   const std::string& arg_spec):
      IHandlerConstraint( constraint_name, arg_spec),
      mArgHandlers()
{
} // IHandlerValueConstraint::IHandlerValueConstraint



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF i_handler_value_constraint.cpp  =====

