
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
/// See documentation of class celma::prog_args::detail::ConstraintAllOf.


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ALL_OF_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ALL_OF_HPP


#include <string>
#include "celma/prog_args/detail/i_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Global constraint: All of the specified arguments must be used.
/// @since  0.2, 10.04.2016
class ConstraintAllOf: public IConstraint
{
public:
   /// Constructor, does a basic validation of the argument list.
   /// @param[in]  reqArgSpec    The list of arguments that must be used.
   /// @since  0.2, 10.04.2016
   explicit ConstraintAllOf( const std::string& reqArgSpec);
   
   /// Called when any argument was identified. Procedure:
   /// - Check if the argument is one of the arguments for which the constraint
   ///   is defined.
   /// - If so, verify that this argument was not already used before and then
   ///   remove it from the list of remaining arguments.
   ///
   /// @param[in]  sourceArg  The current argument that was identified.
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const std::string& sourceArg);

   /// Returns the list of arguments that must be used.
   /// @return  The list of arguments as passed to the constructor.
   /// @since  0.2, 10.04.2016
   virtual std::string& argumentList();

   /// Called after the argument list was validated.
   /// @since  0.2, 10.04.2016
   virtual void validated();

   /// Checks if all of the specified arguments were used, i.e.: if the string
   /// \a #mRemainingArguments is empty.
   /// @since  0.2, 10.04.2016
   virtual void checkEndCondition() const;

private:
   /// The argument specifications of the arguments.<br>
   /// Non-const because non-complete argument specifications may be expanded.
   std::string  mArgSpecList;
   /// Contains the argument that was actually used on the command line.<br>
   /// Used to determine if an argument was used, may be used and for error
   /// reporting.
   std::string  mRemainingArguments;

}; // ConstraintAllOf


} // namespace detail


// helper function
// ===============


/// Helper function to easily add a 'one of' constraint.<br>
/// Usage:  argument_handler_object.addConstraint( one_of( "..."));
/// @param[in]  argSpec  The argument specifications of the selection of
///                      arguments of which one must be used.
/// @return  The newly created constraint object.
/// @since  0.2, 10.04.2016
inline detail::IConstraint* all_of( const std::string& argSpec)
{
   return new detail::ConstraintAllOf( argSpec);
} // end all_of


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ALL_OF_HPP


// =========================  END OF constraint_all_of.hpp  =========================

