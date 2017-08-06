
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
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


using std::runtime_error;
using std::string;


namespace celma { namespace prog_args { namespace detail {



/// Constructor, does a basic validation of the argument list.
/// @param[in]  reqArgSpec    The list of arguments that must be used.
/// @since  0.2, 10.04.2016
ConstraintAllOf::ConstraintAllOf( const string& reqArgSpec):
   mArgSpecList( reqArgSpec),
   mRemainingArguments()
{

   if (mArgSpecList.empty())
      throw runtime_error( "Constraint 'all of' cannot be created with an empty "
                           "list of arguments");

   if (mArgSpecList.find( ';') == string::npos)
      throw runtime_error( "List of needed arguments for constraint 'all of' "
                           "must contain at least two arguments separated by ';'");

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

   if (mRemainingArguments.empty())
      throw runtime_error( "Argument '" + format::toString( key)
                           + "' was already used");

   auto  argpos = mRemainingArguments.find( key);

   if (argpos == mRemainingArguments.end())
      throw runtime_error( "Argument '" + format::toString( key)
                           + "' was already used");

   mRemainingArguments.erase( argpos);

} // ConstraintAllOf::executeConstraint



/// Returns the list of arguments that must be used.
/// @return  The list of arguments as passed to the constructor.
/// @since  0.2, 10.04.2016
string& ConstraintAllOf::argumentList()
{

   return mArgSpecList;
} // ConstraintAllOf::argumentList



/// Called after the argument list in a global constraint was validated.
/// @since  0.2, 10.04.2016
void ConstraintAllOf::validated()
{

   common::Tokenizer  tok( mArgSpecList, ';');


   mRemainingArguments.insert( tok.begin(), tok.end(), nullptr);

} // ConstraintAllOf::validated



/// Checks if all of the specified arguments were used, i.e.: if the string
/// \a #mRemainingArguments is empty.
/// @since  0.2, 10.04.2016
void ConstraintAllOf::checkEndCondition() const
{

   if (!mRemainingArguments.empty())
   {
      string  remaining;
      for (auto const& arg : mRemainingArguments)
      {
         if (!remaining.empty())
            remaining.append( ", ");
         remaining.append( format::toString( arg.key()));
      } // end for

      throw runtime_error( "Argument(s) '" + remaining + "' required but missing");
   } // end if

} // ConstraintAllOf::checkEndCondition



} // namespace detail
} // namespace prog_args
} // namespace celma


// ======================  END OF constraint_all_of.cpp  ======================

