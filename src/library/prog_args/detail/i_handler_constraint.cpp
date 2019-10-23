
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
/// See documentation of class celma::prog_args::detail::IHandlerConstraint.


// module headerfile include
#include "celma/prog_args/detail/i_handler_constraint.hpp"


// project includes
#include "celma/common/tokenizer.hpp"
#include "celma/prog_args/detail/argument_key.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Checks if the argument specified in \a arg_spec is one of the argument(s)
/// specified in the \a constraint_arg_list.
/// This method is used by global constraints derived from this base class,
/// because their executeConstraint() method is called for each argument
/// found on the command line.
///
/// @param[in]  constraint_arg_list
///    The list of argument(s) for which the constraint is defined.
/// @param[in]  key
///    The specification of the argument just found in the argument string.
/// @return
///    \c true if the specified argument is in the list of constrained
///    arguments.
/// @since  0.15.0, 18.07.2017
///    (use ArgumentKey as parameter type)
/// @since  0.2, 10.04.2016
bool IHandlerConstraint::isConstraintArgument( const std::string& constraint_arg_list,
   const ArgumentKey& key)
{

   common::Tokenizer  tok( constraint_arg_list, ';');


   for (auto const& it : tok)
   {
      if (ArgumentKey( it) == key)
         return true;
   } // end for

   return false;
} // IHandlerConstraint::isConstraintArgument



/// Constructor.
///
/// @param[in]  constraint_name
///    The name of the constraint for error messages.
/// @param[in]  arg_spec
///    The list of arguments affected by the constraint.<br>
///    Must already be checked by the calling function (not empty, no invalid
///    arguments).
/// @since
///    1.23.0, 04.04.2019
IHandlerConstraint::IHandlerConstraint( const std::string& constraint_name,
   const std::string& arg_spec):
      mConstraintName( constraint_name),
      mArgSpecList( arg_spec)
{
} // IHandlerConstraint::IHandlerConstraint



/// Helper function needed to distinguish between a "normal" constraint and a
/// value constraint.
/// Since the interface for value constraints is derived from this class, it
/// is possible to pass a value contraint to the interface that expects
/// "normal" constraints. So, instead of traing to force the user to use the
/// correct interface, we provide only one method in the handler class and
/// check there internally which type of constraint we are dealing with.
///
/// @return  Always \c false here.
/// @since  x.y.z, 23.10.2019
bool IHandlerConstraint::isValueConstraint() const
{

   return false;
} // IHandlerConstraint::isValueConstraint



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF i_handler_constraint.cpp  =====

