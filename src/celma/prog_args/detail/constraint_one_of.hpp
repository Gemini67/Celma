
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
/// See documentation of class celma::prog_args::detail::ConstraintOneOf.


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ONE_OF_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ONE_OF_HPP


#include <string>
#include "celma/prog_args/detail/i_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Constraint: Exactly one of the specified arguments must be used.
/// @since  0.2, 10.04.2016
class ConstraintOneOf: public IConstraint
{
public:
   /// Constructor.
   /// @param[in]  reqArgSpec  The list of arguments of which one must be used.
   /// @since  0.2, 10.04.2016
   explicit ConstraintOneOf( const std::string& reqArgSpec);
   
   /// Called when an argument was identified. If the argument is one of those
   /// in the specified list, check if it is the first of these arguments that
   /// is used, i.e. #mUsedArgument is empty.
   /// @param[in]  sourceArg  The argument that was used/identified.
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const std::string& sourceArg);

   /// Required for global constraints to make sure that the argument list
   /// contains both the short and long argument.
   /// @return  The list of argument as passed in the constructor.
   /// @since  0.2, 10.04.2016
   virtual std::string& argumentList();

   /// Called after the argument list was validated.
   /// @since  0.2, 10.04.2016
   virtual void validated();

   /// Called after all arguments were evaluated. Checks that one of the
   /// specified arguments was actually used, i.e. #mUsedArgument may not be
   /// empty.
   /// @since  0.2, 10.04.2016
   virtual void checkEndCondition() const;

private:
   /// The argument specifications of the arguments.<br>
   /// Non-const because non-complete argument specifications may be expanded.
   std::string  mArgSpecList;
   /// Contains the argument that was actually used on the command line.<br>
   /// Used to determine if an argument was used, may be used and for error
   /// reporting.
   std::string  mUsedArgument;

}; // ConstraintOneOf


} // namespace detail


// helper function
// ===============


/// Helper function to easily add a 'one of' constraint.<br>
/// Usage:  argument_handler_object.addConstraint( one_of( "..."));
/// @param[in]  argSpec  The argument specifications of the selection of
///                      arguments of which one must be used.
/// @return  The newly created constraint object.
/// @since  0.2, 10.04.2016
inline detail::IConstraint* one_of( const std::string& argSpec)
{
   return new detail::ConstraintOneOf( argSpec);
} // end one_of


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ONE_OF_HPP


// =========================  END OF constraint_one_of.hpp  =========================

