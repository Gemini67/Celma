
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
/// See documentation of class celma::prog_args::detail::ConstraintExcludes.


#pragma once


#include <string>
#include "celma/prog_args/detail/i_arg_constraint.hpp"


namespace celma::prog_args { namespace detail {


/// Constraint: Argument forbids to use some other argument(s).
///
/// @since  0.15.0, 05.07.2017
///    (use Storage<> internally, pass argument keys as ArgumentKey objects)
/// @since  0.2, 10.04.2016
class ConstraintExcludes final : public IArgConstraint
{
public:
   /// Constructor, stores the argument specification of the other, forbidden
   /// argument(s).
   ///
   /// @param[in]  reqArgSpec
   ///    The argument specification of the forbidden argument(s).
   /// @since  0.2, 10.04.2016
   explicit ConstraintExcludes( const std::string& reqArgSpec);

   /// Empty, virtual destructor.
   ///
   /// @since  1.14.0, 02.10.2018
   ~ConstraintExcludes() override = default;
   
   /// Adds the 'exludes' constraint to the current argument handler.
   ///
   /// @param[in]  key  The argument that sets this constraint.
   /// @since  0.2, 10.04.2016
   void executeConstraint( const ArgumentKey& key) override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   std::string toString() const override;

}; // ConstraintExcludes


} // namespace detail


// helper function
// ===============


/// Helper function to easily add an 'excludes' constraint.<br>
/// Usage:  addArgument( ...)->addConstraint( excludes( "..."));
///
/// @param[in]  argSpec
///    The argument specification of the other, forbidden argument.
/// @return  The newly created constraint object.
/// @since  0.2, 10.04.2016
inline detail::IArgConstraint* excludes( const std::string& argSpec)
{
   return new detail::ConstraintExcludes( argSpec);
} // excludes


} // namespace celma::prog_args


// =====  END OF constraint_excludes.hpp  =====

