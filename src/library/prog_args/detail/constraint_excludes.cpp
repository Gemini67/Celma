
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
/// See documentation of class celma::prog_args::detail::ConstraintExcludes.


// module headerfile include
#include "celma/prog_args/detail/constraint_excludes.hpp"


// OS/C lib includes
#include <cassert>


// C++ Standard Library includes
#include <sstream>


// project includes
#include "celma/prog_args/detail/constraint_container.hpp"


namespace celma::prog_args::detail {



/// Constructor, stores the argument specification of the other, forbidden
/// argument(s).
///
/// @param[in]  container
///    Pointer to the container to which the argument will be added.
/// @param[in]  reqArgSpec
///    The argument specification of the forbidden argument(s).
/// @since  1.47.0, 05.12.2021
///    (parameter \a container added)
/// @since  0.2, 10.04.2016
ConstraintExcludes::ConstraintExcludes( ConstraintContainer* container,
   const std::string& reqArgSpec):
      IArgConstraint( "excludes", reqArgSpec, container)
{
} // ConstraintExcludes::ConstraintExcludes



/// Adds the 'exludes' constraint to the current argument handler.
///
/// @param[in]  key  The argument that sets this constraint.
/// @since  0.2, 10.04.2016
void ConstraintExcludes::executeConstraint( const ArgumentKey& key)
{

   mpConstraintsContainer->
      addConstraint( ConstraintContainer::Constraint::excluded,
                     mConstraints, format::toString( key));

} // ConstraintExcludes::executeConstraint



/// Returns a text description of the constraint.
///
/// @return  A string with the text description of the constraint.
/// @since  0.16.0, 15.08.2017
std::string ConstraintExcludes::toString() const
{

   std::ostringstream  oss;


   oss << "excludes (" << mConstraints << ")";

   return oss.str();
} // ConstraintExcludes::toString



} // namespace celma::prog_args::detail


// =====  END OF constraint_excludes.cpp  =====

