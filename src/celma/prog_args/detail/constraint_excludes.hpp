
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
/// See documentation of class celma::prog_args::detail::ConstraintExcludes.


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_EXCLUDES_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_EXCLUDES_HPP


#include <string>
#include "celma/prog_args/detail/i_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Constraint: Argument forbids to use some other argument(s).
/// @since  0.2, 10.04.2016
class ConstraintExcludes: public IConstraint
{
public:
   /// Constructor, stores the argument specification of the other, forbidden
   /// argument(s).
   /// @param[in]  reqArgSpec  The argument specification of the forbidden
   ///                         argument(s).
   /// @since  0.2, 10.04.2016
   explicit ConstraintExcludes( const std::string& reqArgSpec);
   
   /// Adds the 'exludes' constraint to the current argument handler.
   /// @param[in]  sourceArg  The argument that sets this constraint.
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const std::string& sourceArg) override;

private:
   /// The argument specification of the other, forbidden argument(s).
   const std::string  mExcludedArgSpec;

}; // ConstraintExcludes


} // namespace detail


// helper function
// ===============


/// Helper function to easily add an 'excludes' constraint.<br>
/// Usage:  addArgument( ...)->addConstraint( excludes( "..."));
/// @param[in]  argSpec  The argument specification of the other, forbidden
///                      argument.
/// @return  The newly created constraint object.
/// @since  0.2, 10.04.2016
inline detail::IConstraint* excludes( const std::string& argSpec)
{
   return new detail::ConstraintExcludes( argSpec);
} // end excludes


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_EXCLUDES_HPP


// =====================  END OF constraint_excludes.hpp  =====================

