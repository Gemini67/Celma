
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
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


namespace celma { namespace prog_args { namespace detail {



/// Constructor, stores the argument specification of the other, requried
/// argument.
///
/// @param[in]  reqArgSpec
///    The argument specification of the required argument.
/// @since  0.2, 10.04.2016
ConstraintRequires::ConstraintRequires( const std::string& reqArgSpec):
   mRequiredArgSpec( reqArgSpec)
{
} // ConstraintRequires::ConstraintRequires



/// Adds the 'required' constraint to the current argument handler.
///
/// @param[in]  key  The argument that sets this constraint.
/// @since  0.2, 10.04.2016
void ConstraintRequires::executeConstraint( const ArgumentKey& key)
{

   assert( ConstraintContainer::mpCurrentConstraints != nullptr);

   ConstraintContainer::mpCurrentConstraints->
      addConstraint( ConstraintContainer::Constraint::required,
                     mRequiredArgSpec, format::toString( key));

} // ConstraintRequires::executeConstraint



/// Returns a text description of the constraint.
///
/// @return  A string with the text description of the constraint.
/// @since  0.16.0, 15.08.2017
std::string ConstraintRequires::toString() const
{

   std::ostringstream  oss;

   oss << "Requires " << mRequiredArgSpec;

   return oss.str();
} // ConstraintRequires::toString



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF constraint_requires.cpp  =====

