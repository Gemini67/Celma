
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
/// See documentation of class celma::prog_args::detail::ConstraintRequires.


// module header file include
#include "celma/prog_args/detail/constraint_requires.hpp"


// C/OS lib includes
#include <cassert>


// project includes
#include "celma/prog_args/detail/constraint_container.hpp"


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor, stores the argument specification of the other, requried
/// argument.
/// @param[in]  reqArgSpec  The argument specification of the required
///                         argument.
/// @since  0.2, 10.04.2016
ConstraintRequires::ConstraintRequires( const string& reqArgSpec):
   mRequiredArgSpec( reqArgSpec)
{
} // end ConstraintRequires::ConstraintRequires



/// Adds the 'required' constraint to the current argument handler.
/// @param[in]  sourceArg  The argument that sets this constraint.
/// @since  0.2, 10.04.2016
void ConstraintRequires::executeConstraint( const std::string& sourceArg)
{

   assert( ConstraintContainer::mpCurrentConstraints != nullptr);

   ConstraintContainer::mpCurrentConstraints->
      addConstraint( ConstraintContainer::cRequired, mRequiredArgSpec, sourceArg);

} // end ConstraintRequires::executeConstraint



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF constraint_requires.cpp  =========================

