
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class
/// celma::prog_args::detail::ValueConstraintDisjoint<>.


#pragma once


#include <sstream>
#include <stdexcept>
#include <string>
#include "celma/common/type_name.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/i_handler_value_constraint.hpp"


namespace celma::prog_args { namespace detail {


/// Constraint: The values of the given argument destinations, of type
/// container,  must be different.
///
/// @since  1.33.0, 30.10.2019
class ValueConstraintDisjoint final : public IHandlerValueConstraint
{
public:
   /// Constructor.
   ///
   /// @param[in]  reqArgSpec
   ///    The keys of the two arguments of which the values must be different.
   /// @throw
   ///    std::invalid_argument if the string is empty or does not contain
   ///    exactly two arguments.
   /// @since  1.33.0, 30.10.2019
   explicit ValueConstraintDisjoint( const std::string& reqArgSpec)
      noexcept( false);
   
   // Default destructor is fine.
   ~ValueConstraintDisjoint() override = default;

   /// Checks that not more than two arguments are added for this constraint,
   /// then calls the method of the base class to actually store the argument.
   ///
   /// @param[in]  handler  Pointer to the argument handler object.
   /// @since  1.33.0, 31.10.2019
   void storeArgumentHandler( TypedArgBase* handler) noexcept( false) override;

   /// Empty here, all the work is done in checkEndCondition().
   ///
   /// @param[in]  key  Ignored.
   /// @since  1.33.0, 30.10.2019
   void executeConstraint( const ArgumentKey& key) override;

   /// Does nothing here.
   ///
   /// @since  1.33.0, 30.10.2019
   void validated() override;

   /// Checks all the values of the two containers, they must not intersect.
   ///
   /// @throw
   ///    std::runtime_error when the same value is found in two different
   ///    arguments.
   /// @since  1.33.0, 30.10.2019
   void checkEndCondition() const noexcept( false) override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  1.33.0, 30.10.2019
   std::string toString() const override;

}; // ValueConstraintDisjoint


// inlined methods
// ===============


inline ValueConstraintDisjoint::ValueConstraintDisjoint(
   const std::string& reqArgSpec):
      IHandlerValueConstraint( "disjoint", reqArgSpec)
{
} // ValueConstraintDisjoint::ValueConstraintDisjoint


inline
   void ValueConstraintDisjoint::storeArgumentHandler( TypedArgBase* handler)
{
   if (mArgHandlers.size() == 2)
      throw std::invalid_argument( "constraint 'disjoint' can handle only two "
         "arguments");
   IHandlerValueConstraint::storeArgumentHandler( handler);
} // ValueConstraintDisjoint::storeArgumentHandler

inline
   void ValueConstraintDisjoint::executeConstraint( const ArgumentKey&)
{
} // ValueConstraintDisjoint::executeConstraint


inline void ValueConstraintDisjoint::validated()
{
} // ValueConstraintDisjoint::validated


inline void ValueConstraintDisjoint::checkEndCondition() const
{

   TypedArgBase*  arg1 = mArgHandlers[ 0];
   TypedArgBase*  arg2 = mArgHandlers[ 1];

   if (!arg1->hasValue() || !arg2->hasValue())
      return;

   if (arg1->hasIntersection( arg2))
      throw std::runtime_error( "containers of variable '" + arg1->varName()
         + "' from argument '" + format::toString( arg1->key())
         + "' and variable '" + arg2->varName() +"' from argument '"
         + format::toString( arg2->key()) + "' intersect in at least one value,"
              " must be disjoint");

} // ValueConstraintDisjoint::checkEndCondition


inline std::string ValueConstraintDisjoint::toString() const
{

   std::ostringstream  oss;

   oss << "disjoint_containers( " << mArgSpecList << ")";

   return oss.str();
} // ValueConstraintDisjoint::toString


} // namespace detail


// helper function
// ===============


/// Helper function to easily add a 'disjoint' value constraint.
/// Usage:  argument_handler_object.addValueConstraint( disjoint< std::vector< int>>( "..."));
///
/// @param[in]  argSpec
///    The list of arguments (argument keys) of which the values must be
///    different.
/// @return  The newly created constraint object.
/// @since  1.33.0, 30.10.2019
[[nodiscard]] inline detail::IHandlerValueConstraint*
   disjoint( const std::string& argSpec)
{
   return new detail::ValueConstraintDisjoint( argSpec);
} // disjoint


} // namespace celma::prog_args


// =====  END OF value_constraint_disjoint.hpp  =====

