
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::ConstraintAnyOf.


#pragma once


#include <string>
#include "celma/prog_args/detail/i_handler_constraint.hpp"


namespace celma::prog_args { namespace detail {


/// Constraint: None or just one of the specified arguments may be used.
///
/// @since  0.15.0, 19.07.2017  (use ArgumentKey type to handle keys)
/// @since  0.2, 10.04.2016
class ConstraintAnyOf final : public IHandlerConstraint
{
public:
   /// Constructor.
   ///
   /// @param[in]  reqArgSpec
   ///    The list of arguments of which at most one may be used.
   /// @since  0.2, 10.04.2016
   explicit ConstraintAnyOf( const std::string& reqArgSpec);

   // Default destructor is fine.
   ~ConstraintAnyOf() override = default;

   /// Called when an argument was identified. If the argument is one of those
   /// in the specified list, check if it is the first of these arguments that
   /// is used, i.e. #mUsedArgument is empty.
   ///
   /// @param[in]  key  The argument that was used/identified.
   /// @since  0.2, 10.04.2016
   void executeConstraint( const ArgumentKey& key) override;

   /// Called after the argument list was validated.
   ///
   /// @since  0.2, 10.04.2016
   void validated() override;

   /// Called after all arguments were evaluated. No check done here, but the
   /// method from the base class must be overwritten.
   ///
   /// @since  0.2, 10.04.2016
   void checkEndCondition() const override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   std::string toString() const override;

private:
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
///
/// @param[in]  argSpec
///    The argument specifications of the selection of arguments of which one
///    must be used.
/// @return  The newly created constraint object.
/// @since  0.2, 10.04.2016
[[nodiscard]] inline detail::IHandlerConstraint* any_of( const std::string& argSpec)
{
   return new detail::ConstraintAnyOf( argSpec);
} // any_of


} // namespace celma::prog_args


// =====  END OF constraint_any_of.hpp  =====

