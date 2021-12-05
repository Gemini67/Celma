
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


// module headerfile include
#include "celma/prog_args/detail/i_arg_constraint.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/common/tokenizer.hpp"
#include "celma/prog_args/detail/argument_key.hpp"


namespace celma::prog_args::detail {



/// Constructor, verifies the constraint string.
///
/// @param[in]  name
///    The name of the constraint for error messages.
/// @param[in]  constraint
///    The string with the (list of) constraint(s).
/// @param[in]  container
///    Pointer to the container in the corresponding argument handler.
/// @throw
///    std::invalid_argument when the given constraint string is empty, or
///    when the container pointer is NULL.
/// @since  1.47.0, 05.12.2021
///    (added parameter container)
/// @since  1.23.0, 05.04.2019
IArgConstraint::IArgConstraint( const std::string name,
   const std::string constraint, ConstraintContainer* container):
      mName( name),
      mConstraints( constraint),
      mpConstraintsContainer( container)
{

   if (constraint.empty())
      throw std::invalid_argument( "Constraint string for constraint '" + mName
         + "' may not be empty");
   if (mpConstraintsContainer == nullptr)
      throw std::invalid_argument( "Constraint container pointer may not be "
         "NULL");
   
} // IArgConstraint::IArgConstraint



} // namespace celma::prog_args::detail


// =====  END OF i_arg_constraint.cpp  =====

