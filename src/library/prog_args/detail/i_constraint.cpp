
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
/// See documentation of class celma::prog_args::detail::IConstraint.


// module header file include
#include "celma/prog_args/detail/i_constraint.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/common/tokenizer.hpp"
#include "celma/prog_args/detail/argument_key.hpp"


namespace celma { namespace prog_args { namespace detail {


using std::runtime_error;


/// Needed on global constraints: The list of arguments for which the
/// constraint is defined.
/// @return  The list arguments affected by the constraint.
/// @since  0.2, 10.04.2016
std::string& IConstraint::argumentList()
{

   throw runtime_error( "should not be called");
} // IConstraint::argumentList



/// Called after the argument list in a global constraint was validated.
/// @since  0.2, 10.04.2016
void IConstraint::validated()
{

   throw runtime_error( "should not be called");
} // IConstraint::validated



/// Needed on global constraints: Called when all arguments were evaluated,
/// has to check if the constraint was fulfilled.
/// @since  0.2, 10.04.2016
void IConstraint::checkEndCondition() const
{

   throw runtime_error( "should not be called");
} // IConstraint::checkEndCondition



/// Checks if the argument specified in \a arg_spec is one of the argument(s)
/// specified in the \a constraint_arg_list.<br>
/// This method is used by global constraints derived from this base class,
/// because their executeConstraint() method is called for each argument
/// found on the command line.
/// @param[in]  constraint_arg_list  The list of argument(s) for which the
///                                  constraint is defined.
/// @param[in]  key                  The specification of the argument just
///                                  found in the argument string.
/// @return  \c true if the specified argument is in the list of constrained
///          arguments.
/// @since  0.15.0, 18.07.2017  (use ArgumentKey as parameter type)
/// @since  0.2, 10.04.2016
bool IConstraint::isConstraintArgument( const std::string& constraint_arg_list,
                                        const ArgumentKey& key)
{

   common::Tokenizer  tok( constraint_arg_list, ';');


   for (auto const& it : tok)
   {
      if (ArgumentKey( it) == key)
         return true;
   } // end for

   return false;
} // IConstraint::isConstraintArgument



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF i_constraint.cpp  =========================

