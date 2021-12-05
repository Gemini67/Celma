
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


// module header file include
#include "celma/prog_args/detail/constraint_requires.hpp"


// C/OS lib includes
#include <cassert>


// project includes
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/constraint_container.hpp"


namespace celma::prog_args::detail {



/// Constructor, stores the argument specification of the other, required
/// argument.
///
/// @param[in]  container
///    Pointer to the container to which the argument will be added.
/// @param[in]  reqArgSpec
///    The argument specification of the required argument.
/// @since  1.47.0, 05.12.2021
///    (parameter \a container added)
/// @since  0.2, 10.04.2016
ConstraintRequires::ConstraintRequires( ConstraintContainer* container,
   const std::string& reqArgSpec):
      IArgConstraint( "requires", reqArgSpec, container)
{
} // ConstraintRequires::ConstraintRequires



/// Adds the 'required' constraint to the current argument handler.
///
/// @param[in]  key  The argument that sets this constraint.
/// @since  0.2, 10.04.2016
void ConstraintRequires::executeConstraint( const ArgumentKey& key)
{

   mpConstraintsContainer->addConstraint(
      ConstraintContainer::Constraint::required,
      mConstraints, format::toString( key));

} // ConstraintRequires::executeConstraint



/// Returns a text description of the constraint.
///
/// @return  A string with the text description of the constraint.
/// @since  0.16.0, 15.08.2017
std::string ConstraintRequires::toString() const
{

   std::ostringstream  oss;

   oss << "Requires " << mConstraints;

   return oss.str();
} // ConstraintRequires::toString



} // namespace celma::prog_args::detail


// =====  END OF constraint_requires.cpp  =====

