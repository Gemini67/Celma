
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
/// See documentation of class celma::prog_args::detail::ConstraintExcludes.


// module header file include
#include "celma/prog_args/detail/constraint_excludes.hpp"


// C/OS lib includes
#include <cassert>


// project includes
#include "celma/prog_args/detail/constraint_container.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor, stores the argument specification of the other, forbidden
/// argument(s).
/// @param[in]  reqArgSpec  The argument specification of the forbidden
///                         argument(s).
/// @since  0.2, 10.04.2016
ConstraintExcludes::ConstraintExcludes( const std::string& reqArgSpec):
   mExcludedArgSpec( reqArgSpec)
{
} // ConstraintExcludes::ConstraintExcludes



/// Adds the 'exludes' constraint to the current argument handler.
/// @param[in]  key  The argument that sets this constraint.
/// @since  0.2, 10.04.2016
void ConstraintExcludes::executeConstraint( const ArgumentKey& key)
{

   assert( ConstraintContainer::mpCurrentConstraints != nullptr);

   ConstraintContainer::mpCurrentConstraints->
      addConstraint( ConstraintContainer::Constraint::excluded,
                     mExcludedArgSpec, format::toString( key));

} // ConstraintExcludes::executeConstraint



/// Returns a text description of the constraint.
/// @return  A string with the text description of the constraint.
/// @since  0.16.0, 15.08.2017
std::string ConstraintExcludes::toString() const
{

   std::ostringstream  oss;

   oss << "Excludes ( " << mExcludedArgSpec << ")";

   return oss.str();
} // ConstraintExcludes::toString



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====================  END OF constraint_excludes.cpp  =====================

