
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
/// See documentation of class celma::prog_args::detail::ConstraintAllOf.


// module header file include
#include "celma/prog_args/detail/constraint_all_of.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/common/tokenizer.hpp"
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor, does a basic validation of the argument list.
///
/// @param[in]  reqArgSpec  The list of arguments that must be used.
/// @since  0.2, 10.04.2016
ConstraintAllOf::ConstraintAllOf( const std::string& reqArgSpec):
   IHandlerConstraint( "all of", reqArgSpec),
   mRemainingArguments()
{
} // ConstraintAllOf::ConstraintAllOf



/// Called when any argument was identified. Procedure:
/// - Check if the argument is one of the arguments for which the constraint
///   is defined.
/// - If so, verify that this argument was not already used before and then
///   remove it from the list of remaining arguments.
///
/// @param[in]  key  The current argument that was identified.
/// @since  0.2, 10.04.2016
void ConstraintAllOf::executeConstraint( const ArgumentKey& key)
{

   if (!isConstraintArgument( mArgSpecList, key))
      return;

   // don't have to check for multiple calls:
   // - normally not allowed anyway
   // - if allowed and it happens: so what?
   auto  argpos = mRemainingArguments.find( key);

   if (argpos != mRemainingArguments.end())
      mRemainingArguments.erase( argpos);

} // ConstraintAllOf::executeConstraint



/// Called after the argument list in a global constraint was validated.
///
/// @since  0.2, 10.04.2016
void ConstraintAllOf::validated()
{

   common::Tokenizer  tok( mArgSpecList, ';');


   mRemainingArguments.insert( tok.begin(), tok.end(), nullptr);

} // ConstraintAllOf::validated



/// Checks if all of the specified arguments were used, i.e.: if the string
/// \a #mRemainingArguments is empty.
///
/// @since  0.2, 10.04.2016
void ConstraintAllOf::checkEndCondition() const
{

   if (!mRemainingArguments.empty())
   {
      std::string  remaining;
      for (auto const& arg : mRemainingArguments)
      {
         if (!remaining.empty())
            remaining.append( ", ");
         remaining.append( format::toString( arg.key()));
      } // end for

      throw std::runtime_error( "Argument(s) '" + remaining
         + "' required but missing");
   } // end if

} // ConstraintAllOf::checkEndCondition



/// Returns a text description of the constraint.
///
/// @return  A string with the text description of the constraint.
/// @since  0.16.0, 15.08.2017
std::string ConstraintAllOf::toString() const
{

   std::ostringstream  oss;

   oss << "All of ( " << mArgSpecList << ")";

   return oss.str();
} // ConstraintAllOf::toString



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF constraint_all_of.cpp  =====

