
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


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ONE_OF_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ONE_OF_HPP


#include <string>
#include "celma/prog_args/detail/i_handler_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Constraint: Exactly one of the specified arguments must be used.
///
/// @since  0.15.0, 05.07.2017
///    (use Storage<> internally, pass argument keys as ArgumentKey objects)
/// @since  0.2, 10.04.2016
class ConstraintOneOf: public IHandlerConstraint
{
public:
   /// Constructor.
   ///
   /// @param[in]  reqArgSpec  The list of arguments of which one must be used.
   /// @since  0.2, 10.04.2016
   explicit ConstraintOneOf( const std::string& reqArgSpec);
   
   // Default destructor is fine.
   virtual ~ConstraintOneOf() = default;

   /// Called when an argument was identified. If the argument is one of those
   /// in the specified list, check if it is the first of these arguments that
   /// is used, i.e. #mUsedArgument is empty.
   ///
   /// @param[in]  key  The argument that was used/identified.
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const ArgumentKey& key) override;

   /// Called after the argument list was validated.
   ///
   /// @since  0.2, 10.04.2016
   virtual void validated() override;

   /// Called after all arguments were evaluated. Checks that one of the
   /// specified arguments was actually used, i.e. #mUsedArgument may not be
   /// empty.
   ///
   /// @since  0.2, 10.04.2016
   virtual void checkEndCondition() const override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   virtual std::string toString() const override;

private:
   /// Contains the argument that was actually used on the command line.<br>
   /// Used to determine if an argument was used, may be used and for error
   /// reporting.
   std::string  mUsedArgument;

}; // ConstraintOneOf


} // namespace detail


// helper function
// ===============


/// Helper function to easily add a 'one of' constraint.<br>
/// Usage:  argument_handler_object.addConstraint( one_of( "..."));
///
/// @param[in]  argSpec
///    The argument specifications of the selection of arguments of which one
///    must be used.
/// @return  The newly created constraint object.
/// @since  0.2, 10.04.2016
inline detail::IHandlerConstraint* one_of( const std::string& argSpec)
{
   return new detail::ConstraintOneOf( argSpec);
} // one_of


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ONE_OF_HPP


// =====  END OF constraint_one_of.hpp  =====

