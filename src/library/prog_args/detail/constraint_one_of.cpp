
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
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


// project includes
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/argument_key.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
///
/// @param[in]  reqArgSpec  The list of arguments of which one must be used.
/// @since  0.2, 10.04.2016
ConstraintOneOf::ConstraintOneOf( const std::string& reqArgSpec):
   IHandlerConstraint( "one of", reqArgSpec),
   mUsedArgument()
{
} // ConstraintOneOf::ConstraintOneOf



/// Called when an argument was identified. If the argument is one of those
/// in the specified list, check if it is the first of these arguments that
/// is used, i.e. #mUsedArgument is empty.
///
/// @param[in]  key  The argument that was used/identified.
/// @since  0.2, 10.04.2016
void ConstraintOneOf::executeConstraint( const ArgumentKey& key)
{

   // it may be any argument
   if (!isConstraintArgument( mArgSpecList, key))
      return;

   // is it the first argument that was actually used?
   if (!mUsedArgument.empty())
      throw std::runtime_error( "Argument '" + format::toString( key)
                                + "' cannot be used since '" + mUsedArgument
                                + "' was already used");

   // store the first argument used
   mUsedArgument = format::toString( key);

} // ConstraintOneOf::executeConstraint



/// Required for global constraints to make sure that the argument list
/// contains both the short and long argument.
///
/// @return  The list of argument as passed in the constructor.
/// @since  0.2, 10.04.2016
std::string& ConstraintOneOf::argumentList()
{

   return mArgSpecList;
} // ConstraintOneOf::argumentList



/// Called after the argument list in a global constraint was validated.
/// @since  0.2, 10.04.2016
void ConstraintOneOf::validated()
{
} // ConstraintOneOf::validated



/// Called after all arguments were evaluated. Checks that one of the
/// specified arguments was actually used, i.e. #mUsedArgument may not be
/// empty.
///
/// @since  0.2, 10.04.2016
void ConstraintOneOf::checkEndCondition() const
{

   if (mUsedArgument.empty())
      throw std::runtime_error( "None of the arguments '" + mArgSpecList
                                + "' was used");

} // ConstraintOneOf::checkEndCondition



/// Returns a text description of the constraint.
///
/// @return  A string with the text description of the constraint.
/// @since  0.16.0, 15.08.2017
std::string ConstraintOneOf::toString() const
{

   std::ostringstream  oss;

   oss << "One of ( " << mArgSpecList << ")";

   return oss.str();
} // ConstraintOneOf::toString



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF constraint_one_of.cpp  =====

