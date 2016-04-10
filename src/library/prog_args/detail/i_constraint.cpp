
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
/// See documentation of class celma::prog_args::detail::IConstraint.


// module header file include
#include "celma/prog_args/detail/i_constraint.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/common/tokenizer.hpp"


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Needed on global constraints: The list of arguments for which the
/// constraint is defined.
/// @return  The list arguments affected by the constraint.
/// @since  0.2, 10.04.2016
string& IConstraint::argumentList()
{

   throw std::runtime_error( "should not be called");
} // end IConstraint::argumentList



/// Called after the argument list in a global constraint was validated.
/// @since  0.2, 10.04.2016
void IConstraint::validated()
{

   throw std::runtime_error( "should not be called");
} // end IConstraint::validated



/// Needed on global constraints: Called when all arguments were evaluated,
/// has to check if the constraint was fulfilled.
/// @since  0.2, 10.04.2016
void IConstraint::checkEndCondition() const
{

   throw std::runtime_error( "should not be called");
} // end IConstraint::checkEndCondition



/// Checks if the argument specified in \a arg_spec is one of the argument(s)
/// specified in the \a constraint_arg_list.<br>
/// This method is used by global constraints derived from this base class,
/// because their executeConstraint() method is called for each argument
/// found on the command line.
/// @param[in]  constraint_arg_list  The list of argument(s) for which the
///                                  constraint is defined.
/// @param[in]  arg_spec             The specification of the argument just
///                                  found in the argument string.
/// @return  \c true if the specified argument is in the list of constrained
///          arguments.
/// @since  0.2, 10.04.2016
bool IConstraint::isConstraintArgument( const string& constraint_arg_list,
                                        const string& arg_spec)
{

   common::Tokenizer  tok( constraint_arg_list, ';');


   for (auto it : tok)
   {
      if (it == arg_spec)
         return true;
   } // end for

   return false;
} // end IConstraint::isConstraintArgument



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF i_constraint.cpp  =========================

