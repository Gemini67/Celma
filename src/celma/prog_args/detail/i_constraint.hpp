
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
/// See documentation of class celma::prog_args::detail::IConstraint.


#ifndef CELMA_PROG_ARGS_DETAIL_I_CONSTRAINT_HPP
#define CELMA_PROG_ARGS_DETAIL_I_CONSTRAINT_HPP


#include <string>


namespace celma { namespace prog_args { namespace detail {


/// Base class for constraints.<br>
/// Actually this base class is used for two different types of constraints:
/// - Constraints depending on a specific argument, dynamically activated if
///   the argument is used.
/// - So-called 'global constraint's which affect multiple arguments and are
///   stored/handled in the argument handler itself.
/// @since  0.2, 10.04.2016
class IConstraint
{
public:
   /// Empty, virtual destructor required for base classes.
   /// @since  0.2, 10.04.2016
   virtual ~IConstraint() { }

   /// Called when an argument was identified and the corresponding handler
   /// called.
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const std::string& sourceArg) = 0;

   /// Needed on global constraints: The list of arguments for which the
   /// constraint is defined.
   /// @return  The list arguments affected by the constraint.
   /// @since  0.2, 10.04.2016
   virtual std::string& argumentList();

   /// Called after the argument list in a global constraint was validated.
   /// @since  0.2, 10.04.2016
   virtual void validated();

   /// Needed on global constraints: Called when all arguments were evaluated,
   /// has to check if the constraint was fulfilled.
   /// @since  0.2, 10.04.2016
   virtual void checkEndCondition() const;

protected:
   /// Checks if the argument specified in \a arg_spec is one of the argument(s)
   /// specified in the \a constraint_arg_list.<br>
   /// This method is used by global constraints derived from this base class,
   /// because their executeConstraint() method is called for each argument
   /// found on the command line.
   /// @param[in]  constraint_arg_list  The list of argument(s) for which the
   ///                                  constraint is defined.
   /// @param[in]  arg_spec             The specification of the argument just
   ///                                  found in the argument string.
   /// @return  \c true if the specified argument is in the list of constrained
   ///          arguments.
   /// @since  0.2, 10.04.2016
   static bool isConstraintArgument( const std::string& constraint_arg_list,
                                     const std::string& arg_spec);

}; // IConstraint


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_I_CONSTRAINT_HPP


// =========================  END OF i_constraint.hpp  =========================
