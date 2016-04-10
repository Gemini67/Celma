
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


// module header file include
#include "celma/prog_args/detail/constraint_excludes.hpp"


// C/OS lib includes
#include <cassert>


// project includes
#include "celma/prog_args/detail/constraint_container.hpp"


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor, stores the argument specification of the other, forbidden
/// argument(s).
/// @param[in]  reqArgSpec  The argument specification of the forbidden
///                         argument(s).
/// @since  0.2, 10.04.2016
ConstraintExcludes::ConstraintExcludes( const string& reqArgSpec):
   mExcludedArgSpec( reqArgSpec)
{
} // end ConstraintExcludes::ConstraintExcludes



/// Adds the 'exludes' constraint to the current argument handler.
/// @param[in]  sourceArg  The argument that sets this constraint.
/// @since  0.2, 10.04.2016
void ConstraintExcludes::executeConstraint( const std::string& sourceArg)
{

   assert( ConstraintContainer::mpCurrentConstraints != nullptr);

   ConstraintContainer::mpCurrentConstraints->
      addConstraint( ConstraintContainer::cExcluded, mExcludedArgSpec, sourceArg);

} // end ConstraintExcludes::executeConstraint



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF constraint_excludes.cpp  =========================

