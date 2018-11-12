
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::ConstraintAnyOf.


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ANY_OF_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ANY_OF_HPP


#include <string>
#include "celma/prog_args/detail/i_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Constraint: None or just one of the specified arguments may be used.
/// @since  0.15.0, 19.07.2017  (use ArgumentKey type to handle keys)
/// @since  0.2, 10.04.2016
class ConstraintAnyOf: public IConstraint
{
public:
   /// Constructor.
   /// @param[in]  reqArgSpec  The list of arguments of which at most one may be
   ///                         used.
   /// @since  0.2, 10.04.2016
   explicit ConstraintAnyOf( const std::string& reqArgSpec);
   
   /// Called when an argument was identified. If the argument is one of those
   /// in the specified list, check if it is the first of these arguments that
   /// is used, i.e. #mUsedArgument is empty.
   /// @param[in]  key  The argument that was used/identified.
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const ArgumentKey& key) override;

   /// Required for global constraints to make sure that the argument list
   /// contains both the short and long argument.
   /// @return  The list of argument as passed in the constructor.
   /// @since  0.2, 10.04.2016
   virtual std::string& argumentList() override;

   /// Called after the argument list was validated.
   /// @since  0.2, 10.04.2016
   virtual void validated() override;

   /// Called after all arguments were evaluated. No check done here, but the
   /// method from the base class must be overwritten.
   /// @since  0.2, 10.04.2016
   virtual void checkEndCondition() const override;

   /// Returns a text description of the constraint.
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   virtual std::string toString() const override;

private:
   /// The argument specifications of the arguments.<br>
   /// Non-const because non-complete argument specifications may be expanded.
   std::string  mArgSpecList;
   /// Contains the argument that was actually used on the command line.<br>
   /// Used to determine if an argument was used, may be used and for error
   /// reporting.
   std::string  mUsedArgument;

}; // ConstraintAnyOf


} // namespace detail


// helper function
// ===============


/// Helper function to easily add a 'one of' constraint.<br>
/// Usage:  argument_handler_object.addConstraint( one_of( "..."));
/// @param[in]  argSpec  The argument specifications of the selection of
///                      arguments of which one must be used.
/// @return  The newly created constraint object.
/// @since  0.2, 10.04.2016
inline detail::IConstraint* any_of( const std::string& argSpec)
{
   return new detail::ConstraintAnyOf( argSpec);
} // any_of


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ANY_OF_HPP


// ======================  END OF constraint_any_of.hpp  ======================

