
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::ConstraintRequires.


#pragma once


#include <string>
#include "celma/prog_args/detail/i_arg_constraint.hpp"


namespace celma::prog_args { namespace detail {


/// Constraint: Argument requires another argument to be used.
///
/// @since  0.15.0, 05.07.2017
///    (use Storage<> internally, pass argument keys as ArgumentKey objects)
/// @since  0.2, 10.04.2016
class ConstraintRequires final : public IArgConstraint
{
public:
   /// Constructor, stores the argument specification of the other, requried
   /// argument.
   ///
   /// @param[in]  container
   ///    Pointer to the container to which the argument will be added.
   /// @param[in]  reqArgSpec
   ///    The argument specification of the required argument.
   /// @since  1.47.0, 05.12.2021
   ///    (parameter \a container added)
   /// @since  0.2, 10.04.2016
   ConstraintRequires( ConstraintContainer* container,
      const std::string& reqArgSpec);

   /// Empty, virtual destructor.
   ///
   /// @since  1.23.0, 05.04.2019
   ~ConstraintRequires() override = default;

   /// Adds the 'required' constraint to the current argument handler.
   ///
   /// @param[in]  key  The argument that sets this constraint.
   /// @since  0.2, 10.04.2016
   void executeConstraint( const ArgumentKey& key) override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   std::string toString() const override;

}; // ConstraintRequires


} // namespace detail


// helper function
// ===============


/// Helper function to easily add a 'requires' constraint.<br>
/// Usage:  addArgument( ...)->addConstraint( requiresArg( "..."));
///
/// @param[in]  argSpec
///    The argument specification of the other, required argument.
/// @return
///    Lambda that will create the constraints object with additional parameters.
/// @since  1.47.0, 05.12.2021
///    (now returns a lambda)
/// @since  1.43.0, 09.02.2021
///    (name changed from requires() due to conflict with new C++ standard 20)
/// @since  0.2, 10.04.2016
[[nodiscard]] inline auto requiresArg( const std::string& argSpec)
{
   return [=]( detail::ConstraintContainer* container)
   {
      return new detail::ConstraintRequires( container, argSpec);
   };
} // requiresArg


} // namespace celma::prog_args


// =====  END OF constraint_requires.hpp  =====

