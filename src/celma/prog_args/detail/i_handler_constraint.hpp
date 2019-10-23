
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


#ifndef CELMA_PROG_ARGS_DETAIL_I_HANDLER_CONSTRAINT_HPP
#define CELMA_PROG_ARGS_DETAIL_I_HANDLER_CONSTRAINT_HPP


#include <iosfwd>
#include <string>


namespace celma { namespace prog_args { namespace detail {


class ArgumentKey;


/// Base class for constraints which affect multiple arguments and are stored/
/// handled in the argument handler itself.
///
/// @since  1.24.2, 23.10.2018
///    (arg list returned from here, some methods now pure virtual)
/// @since  1.22.1, 25.10.2018
///    (moved from IConstraint, special version for handler arguments)
/// @since  0.2, 10.04.2016
class IHandlerConstraint
{
public:
   /// Empty, virtual destructor required for base classes.
   ///
   /// @since  0.2, 10.04.2016
   virtual ~IHandlerConstraint() = default;

   /// Called when an argument was identified and the corresponding handler
   /// called.
   ///
   /// @param[in]  key  The argument to execute the constraint with.
   /// @since  0.15.0, 18.07.2017
   ///    (use ArgumentKey as parameter type)
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const ArgumentKey& key) = 0;

   /// The list of arguments for which the constraint is defined.
   ///
   /// @return  The list arguments affected by the constraint.
   /// @since  0.2, 10.04.2016
   std::string& argumentList();

   /// Called after the argument list in a global constraint was validated.
   ///
   /// @since  1.24.2, 23.04.2019
   ///    (now pure virtual here)
   /// @since  0.2, 10.04.2016
   virtual void validated() = 0;

   /// Called when all arguments were evaluated, has to check if the constraint
   /// was fulfilled.
   ///
   /// @since  1.24.2, 23.04.2019
   ///    (now pure virtual here)
   /// @since  0.2, 10.04.2016
   virtual void checkEndCondition() const = 0;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   virtual std::string toString() const = 0;

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
   virtual bool isValueConstraint() const;

protected:
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
   static bool isConstraintArgument( const std::string& constraint_arg_list,
                                     const ArgumentKey& key);

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
   IHandlerConstraint( const std::string& constraint_name,
      const std::string& arg_spec);

   /// The name of the constraint for error messages.
   const std::string  mConstraintName;
   /// The argument specifications of the arguments.<br>
   /// Non-const because non-complete argument specifications may be expanded.
   std::string        mArgSpecList;

}; // IHandlerConstraint


// inlined methods
// ===============


inline std::string& IHandlerConstraint::argumentList()
{
   return mArgSpecList;
} // IHandlerConstraint::argumentList


inline std::ostream& operator <<( std::ostream& os, IHandlerConstraint* pc)
{
   return os << pc->toString();
} // operator <<


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_I_HANDLER_CONSTRAINT_HPP


// =====  END OF i_handler_constraint.hpp  =====

