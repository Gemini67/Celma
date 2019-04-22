
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
/// See documentation of class celma::prog_args::detail::ConstraintAnyOf.


// module header file include
#include "celma/prog_args/detail/constraint_any_of.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/argument_key.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor.
///
/// @param[in]  reqArgSpec
///    The list of arguments of which at most one may be used.
/// @throws
///    "invalid argument" if the string is empty or does not contain at least
///    two arguments.
/// @since  0.2, 10.04.2016
ConstraintAnyOf::ConstraintAnyOf( const std::string& reqArgSpec):
   IHandlerConstraint( "any of", reqArgSpec),
   mUsedArgument()
{
} // ConstraintAnyOf::ConstraintAnyOf



/// Called when an argument was identified. If the argument is one of those
/// in the specified list, check if it is the first of these arguments that
/// is used, i.e. #mUsedArgument is empty.
///
/// @param[in]  key  The argument that was used/identified.
/// @since  1.1, 01.03.2016
void ConstraintAnyOf::executeConstraint( const ArgumentKey& key)
{

   if (!isConstraintArgument( mArgSpecList, key))
      return;

   if (!mUsedArgument.empty())
      throw std::runtime_error( "Argument '" + format::toString( key)
                                + "' cannot be used since '" + mUsedArgument
                                + "' was already used");

   mUsedArgument = format::toString( key);

} // ConstraintAnyOf::executeConstraint



/// Required for global constraints to make sure that the argument list
/// contains both the short and long argument.
///
/// @return  The list of argument as passed in the constructor.
/// @since  0.2, 10.04.2016
std::string& ConstraintAnyOf::argumentList()
{

   return mArgSpecList;
} // ConstraintAnyOf::argumentList



/// Called after the argument list in a global constraint was validated.
///
/// @since  0.2, 10.04.2016
void ConstraintAnyOf::validated()
{
} // ConstraintAnyOf::validated



/// Called after all arguments were evaluated. No check done here, but the
/// method from the base class must be overwritten.
///
/// @since  0.2, 10.04.2016
void ConstraintAnyOf::checkEndCondition() const
{
} // ConstraintAnyOf::checkEndCondition



/// Returns a text description of the constraint.
///
/// @return  A string with the text description of the constraint.
/// @since  0.16.0, 15.08.2017
std::string ConstraintAnyOf::toString() const
{

   std::ostringstream  oss;

   oss << "Any of ( " << mArgSpecList << ")";

   return oss.str();
} // ConstraintAnyOf::toString



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF constraint_any_of.cpp  =====

