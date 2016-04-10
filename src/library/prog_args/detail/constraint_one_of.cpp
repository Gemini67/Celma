
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
/// See documentation of class celma::prog_args::detail::ConstraintOneOf.


// module header file include
#include "celma/prog_args/detail/constraint_one_of.hpp"


// C++ Standard Library includes
#include <stdexcept>


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
/// @param[in]  reqArgSpec  The list of arguments of which one must be used.
/// @since  0.2, 10.04.2016
ConstraintOneOf::ConstraintOneOf( const string& reqArgSpec):
   mArgSpecList( reqArgSpec),
   mUsedArgument()
{
} // end ConstraintOneOf::ConstraintOneOf



/// Called when an argument was identified. If the argument is one of those
/// in the specified list, check if it is the first of these arguments that
/// is used, i.e. #mUsedArgument is empty.
/// @param[in]  sourceArg  The argument that was used/identified.
/// @since  0.2, 10.04.2016
void ConstraintOneOf::executeConstraint( const string& sourceArg)
{

   // it may be any argument
   if (!isConstraintArgument( mArgSpecList, sourceArg))
      return;

   // is it the first argument that was actually used?
   if (!mUsedArgument.empty())
      throw runtime_error( string( "Argument '").append( sourceArg).
                           append( "' cannot be used since '").
                           append( mUsedArgument).append( "' was already used"));

   // store the first argument used
   mUsedArgument = sourceArg;

} // end ConstraintOneOf::executeConstraint



/// Required for global constraints to make sure that the argument list
/// contains both the short and long argument.
/// @return  The list of argument as passed in the constructor.
/// @since  0.2, 10.04.2016
string& ConstraintOneOf::argumentList()
{

   return mArgSpecList;
} // end ConstraintOneOf::argumentList



/// Called after the argument list in a global constraint was validated.
/// @since  0.2, 10.04.2016
void ConstraintOneOf::validated()
{
} // end ConstraintOneOf::validated



/// Called after all arguments were evaluated. Checks that one of the
/// specified arguments was actually used, i.e. #mUsedArgument may not be
/// empty.
/// @since  0.2, 10.04.2016
void ConstraintOneOf::checkEndCondition() const
{

   if (mUsedArgument.empty())
      throw runtime_error( "None of the arguments '" + mArgSpecList + "' was used");

} // end ConstraintOneOf::checkEndCondition



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF constraint_one_of.cpp  =========================

