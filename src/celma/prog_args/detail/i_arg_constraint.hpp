
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


#ifndef CELMA_PROG_ARGS_DETAIL_I_ARG_CONSTRAINT_HPP
#define CELMA_PROG_ARGS_DETAIL_I_ARG_CONSTRAINT_HPP


#include <iosfwd>
#include <string>


namespace celma { namespace prog_args { namespace detail {


class ArgumentKey;


/// Base class for constraints depending on a specific argument, dynamically
/// activated if the argument is used.
///
/// @since  1.22.1, 25.10.2018
///    (moved from IConstraint, special version for argument-specific constraints)
/// @since  0.2, 10.04.2016
class IArgConstraint
{
public:
   /// Empty, virtual destructor required for base classes.
   ///
   /// @since  0.2, 10.04.2016
   virtual ~IArgConstraint() = default;

   /// Called when an argument was identified and the corresponding handler
   /// called.
   ///
   /// @param[in]  key  The argument to execute the constraint with.
   /// @since  0.15.0, 18.07.2017
   ///    (use ArgumentKey as parameter type)
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const ArgumentKey& key) = 0;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   virtual std::string toString() const = 0;

protected:
   /// Constructor, verifies the constraint string.
   ///
   /// @param[in]  name
   ///    The name of the constraint for error messages.
   /// @param[in]  constraint
   ///    The string with the (list of) constraint(s).
   /// @throw  std::invalid_argument when the given constraint string is empty.
   /// @since  1.23.0, 05.04.2019
   IArgConstraint( const std::string name, const std::string constraint)
      noexcept( false);

   /// The name of the constraint.
   const std::string  mName;
   /// The (list of) constrained arguments.
   const std::string  mConstraints;

}; // IArgConstraint


// inlined methods
// ===============


inline std::ostream& operator <<( std::ostream& os, IArgConstraint* pc)
{

   return os << pc->toString();
} // operator <<


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_I_ARG_CONSTRAINT_HPP


// =====  END OF i_arg_constraint.hpp  =====

