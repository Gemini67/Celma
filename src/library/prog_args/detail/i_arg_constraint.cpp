
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
/// See documentation of class celma::prog_args::detail::IArgConstraint.


// module header file include
#include "celma/prog_args/detail/i_arg_constraint.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/common/tokenizer.hpp"
#include "celma/prog_args/detail/argument_key.hpp"


namespace celma { namespace prog_args { namespace detail {


using std::runtime_error;



/// Checks if the argument specified in \a arg_spec is one of the argument(s)
/// specified in the \a constraint_arg_list.<br>
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
bool IArgConstraint::isConstraintArgument( const std::string& constraint_arg_list,
   const ArgumentKey& key)
{

   common::Tokenizer  tok( constraint_arg_list, ';');


   for (auto const& it : tok)
   {
      if (ArgumentKey( it) == key)
         return true;
   } // end for

   return false;
} // IArgConstraint::isConstraintArgument



/// Constructor, verifies the constraint string.
///
/// @param[in]  name
///    The name of the constraint for error messages.
/// @param[in]  constraint
///    The string with the (list of) constraint(s).
/// @throws  "invalid argument" when the given constraint string is empty.
/// @since  1.23.0, 05.04.2019
IArgConstraint::IArgConstraint( const std::string name,
   const std::string constraint):
      mName( name),
      mConstraints( constraint)
{

   if (constraint.empty())
      throw std::invalid_argument( "Constraint string for constraint '" + mName
         + "' may not be empty");
   
} // IArgConstraint::IArgConstraint



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF i_arg_constraint.cpp  =====

