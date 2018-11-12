
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
/// See documentation of class celma::prog_args::detail::ConstraintRequires.


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_REQUIRES_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_REQUIRES_HPP


#include <string>
#include "celma/prog_args/detail/i_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Constraint: Argument requires another argument to be used.
/// @since  0.15.0, 05.07.2017  (use Storage<> internally, pass argument keys as
///                             ArgumentKey objects)
/// @since  0.2, 10.04.2016
class ConstraintRequires: public IConstraint
{
public:
   /// Constructor, stores the argument specification of the other, requried
   /// argument.
   /// @param[in]  reqArgSpec  The argument specification of the required
   ///                         argument.
   /// @since  0.2, 10.04.2016
   explicit ConstraintRequires( const std::string& reqArgSpec);
   
   /// Adds the 'required' constraint to the current argument handler.
   /// @param[in]  key  The argument that sets this constraint.
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const ArgumentKey& key) override;

   /// Returns a text description of the constraint.
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   virtual std::string toString() const override;

private:
   /// The argument specification of the other, required argument.
   const std::string  mRequiredArgSpec;

}; // ConstraintRequires


} // namespace detail


// helper function
// ===============


/// Helper function to easily add a 'requires' constraint.<br>
/// Usage:  addArgument( ...)->addConstraint( requires( "..."));
/// @param[in]  argSpec  The argument specification of the other, required
///                      argument.
/// @return  The newly created constraint object.
/// @since  0.2, 10.04.2016
inline detail::IConstraint* requires( const std::string& argSpec)
{
   return new detail::ConstraintRequires( argSpec);
} // requires


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_REQUIRES_HPP


// =====================  END OF constraint_requires.hpp  =====================

