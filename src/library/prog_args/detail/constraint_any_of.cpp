
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
/// See documentation of class celma::prog_args::detail::ConstraintAnyOf.


// module header file include
#include "celma/prog_args/detail/constraint_any_of.hpp"


// C++ Standard Library includes
#include <stdexcept>


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @param[in]  reqArgSpec  The list of arguments of which at most one may be
///                         used.
/// @since  1.1, 01.03.2016
ConstraintAnyOf::ConstraintAnyOf( const string& reqArgSpec):
   mArgSpecList( reqArgSpec),
   mUsedArgument()
{
} // end ConstraintAnyOf::ConstraintAnyOf



/// Called when an argument was identified. If the argument is one of those
/// in the specified list, check if it is the first of these arguments that
/// is used, i.e. #mUsedArgument is empty.
/// @param[in]  sourceArg  The argument that was used/identified.
/// @since  1.1, 01.03.2016
void ConstraintAnyOf::executeConstraint( const string& sourceArg)
{

   if (!isConstraintArgument( mArgSpecList, sourceArg))
      return;

   if (!mUsedArgument.empty())
      throw runtime_error( "Argument '" + sourceArg + "' cannot be used since '" +
                           mUsedArgument + "' was already used");

   mUsedArgument = sourceArg;

} // end ConstraintAnyOf::executeConstraint



/// Required for global constraints to make sure that the argument list
/// contains both the short and long argument.
/// @return  The list of argument as passed in the constructor.
/// @since  0.2, 10.04.2016
string& ConstraintAnyOf::argumentList()
{

   return mArgSpecList;
} // end ConstraintAnyOf::argumentList



/// Called after the argument list in a global constraint was validated.
/// @since  0.2, 10.04.2016
void ConstraintAnyOf::validated()
{
} // end ConstraintAnyOf::validated



/// Called after all arguments were evaluated. No check done here, but the
/// method from the base class must be overwritten.
/// @since  0.2, 10.04.2016
void ConstraintAnyOf::checkEndCondition() const
{
} // end ConstraintAnyOf::checkEndCondition



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF constraint_any_of.cpp  =========================

