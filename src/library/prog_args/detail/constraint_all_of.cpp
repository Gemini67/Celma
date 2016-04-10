
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
/// See documentation of class celma::prog_args::detail::ConstraintAllOf.


// module header file include
#include "celma/prog_args/detail/constraint_all_of.hpp"


// C++ Standard Library includes
#include <stdexcept>


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Constructor, does a basic validation of the argument list.
/// @param[in]  reqArgSpec    The list of arguments that must be used.
/// @since  0.2, 10.04.2016
ConstraintAllOf::ConstraintAllOf( const string& reqArgSpec):
   mArgSpecList( reqArgSpec),
   mRemainingArguments( "uninitialized")
{

   if (mArgSpecList.empty())
      throw runtime_error( "Constraint 'all of' cannot be created with an empty "
                           "list of arguments");

   if (mArgSpecList.find( ';') == string::npos)
      throw runtime_error( "List of needed arguments for constraint 'all of' "
                           "must contain at least two arguments separated by ';'");

} // end ConstraintAllOf::ConstraintAllOf



/// Called when any argument was identified. Procedure:
/// - Check if the argument is one of the arguments for which the constraint
///   is defined.
/// - If so, verify that this argument was not already used before and then
///   remove it from the list of remaining arguments.
///
/// @param[in]  sourceArg  The current argument that was identified.
/// @since  0.2, 10.04.2016
void ConstraintAllOf::executeConstraint( const string& sourceArg)
{

   if (!isConstraintArgument( mArgSpecList, sourceArg))
      return;

   if (mRemainingArguments.empty())
      throw runtime_error( "Argument '" + sourceArg + "' was already used");

   const string::size_type  argpos = mRemainingArguments.find( sourceArg);

   if (argpos == string::npos)
      throw runtime_error( "Argument '" + sourceArg + "' was already used");

   mRemainingArguments.erase( argpos, sourceArg.length() + 1);

} // end ConstraintAllOf::executeConstraint



/// Returns the list of arguments that must be used.
/// @return  The list of arguments as passed to the constructor.
/// @since  0.2, 10.04.2016
string& ConstraintAllOf::argumentList()
{

   return mArgSpecList;
} // end ConstraintAllOf::argumentList



/// Called after the argument list in a global constraint was validated.
/// @since  0.2, 10.04.2016
void ConstraintAllOf::validated()
{

   mRemainingArguments = mArgSpecList;

} // end ConstraintAllOf::validated



/// Checks if all of the specified arguments were used, i.e.: if the string
/// \a #mRemainingArguments is empty.
/// @since  0.2, 10.04.2016
void ConstraintAllOf::checkEndCondition() const
{

   if (!mRemainingArguments.empty())
      throw runtime_error( "Argument(s) '" + mRemainingArguments +
                           "' required but missing");

} // end ConstraintAllOf::checkEndCondition



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF constraint_all_of.cpp  =========================

