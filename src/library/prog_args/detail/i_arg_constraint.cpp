
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



/// Constructor, verifies the constraint string.
///
/// @param[in]  name
///    The name of the constraint for error messages.
/// @param[in]  constraint
///    The string with the (list of) constraint(s).
/// @throw  std::invalid_argument when the given constraint string is empty.
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

