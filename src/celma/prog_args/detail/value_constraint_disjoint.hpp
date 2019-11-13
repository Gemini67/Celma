
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class
/// celma::prog_args::detail::ValueConstraintDisjoint<>.


#ifndef CELMA_PROG_ARGS_DETAIL_VALUE_CONSTRAINT_DISJOINT_HPP
#define CELMA_PROG_ARGS_DETAIL_VALUE_CONSTRAINT_DISJOINT_HPP


#include <sstream>
#include <stdexcept>
#include <string>
#include "celma/common/has_intersection.hpp"
#include "celma/common/type_name.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/i_handler_value_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Constraint: The values of the given argument destinations, of type
/// container,  must be different.
///
/// @tparam  C1
///    The type of the container of the first argument to check.
/// @tparam  C2
///    The type of the container of the second argument to check.
/// @since  1.33.0, 30.10.2019
template< typename C1, typename C2> class ValueConstraintDisjoint:
   public IHandlerValueConstraint
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
   virtual ~ValueConstraintDisjoint() = default;

   /// Checks that not more than two arguments are added for this constraint,
   /// then calls the method of the base class to actually store the argument.
   ///
   /// @param[in]  handler  Pointer to the argument handler object.
   /// @since  1.33.0, 31.10.2019
   virtual void storeArgumentHandler( TypedArgBase* handler) noexcept( false)
      override;

   /// Empty here, all the work is done in checkEndCondition().
   ///
   /// @param[in]  key  Ignored.
   /// @since  1.33.0, 30.10.2019
   virtual void executeConstraint( const ArgumentKey& key) override;

   /// Does nothing here.
   ///
   /// @since  1.33.0, 30.10.2019
   virtual void validated() override;

   /// Checks all the values of the two containers, they must not intersect.
   ///
   /// @throw
   ///    std::runtime_error when the same value is found in two different
   ///    arguments.
   /// @since  1.33.0, 30.10.2019
   virtual void checkEndCondition() const noexcept( false) override;

   /// Checks if the type set for the constraint matches one of the types of the
   /// destination variables.
   ///
   /// @param[in]  var_type_name
   ///    The name of the type of the arguments destination variable.
   /// @return
   ///    \c true if the type of the destination variable and the type set for
   ///    one of the the destination variables match.
   /// @since  1.33.0, 31.10.2019
   virtual bool matchesVarType( const std::string& var_type_name) const override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  1.33.0, 30.10.2019
   virtual std::string toString() const override;

}; // ValueConstraintDisjoint< C1, C2>


// inlined methods
// ===============


template< typename C1, typename C2>
   ValueConstraintDisjoint< C1, C2>::ValueConstraintDisjoint(
      const std::string& reqArgSpec):
         IHandlerValueConstraint( "disjoint", reqArgSpec)
{
} // ValueConstraintDisjoint< C1, C2>::ValueConstraintDisjoint


template< typename C1, typename C2>
   void ValueConstraintDisjoint< C1, C2>::storeArgumentHandler(
      TypedArgBase* handler)
{
   if (mArgHandlers.size() == 2)
      throw std::invalid_argument( "constraint 'disjoint' can handle only two "
         "arguments");
   IHandlerValueConstraint::storeArgumentHandler( handler);
} // ValueConstraintDisjoint< C1, C2>::storeArgumentHandler

template< typename C1, typename C2>
   void ValueConstraintDisjoint< C1, C2>::executeConstraint( const ArgumentKey&)
{
} // ValueConstraintDisjoint< C1, C2>::executeConstraint


template< typename C1, typename C2>
   void ValueConstraintDisjoint< C1, C2>::validated()
{
} // ValueConstraintDisjoint< C1, C2>::validated


template< typename C1, typename C2>
   void ValueConstraintDisjoint< C1, C2>::checkEndCondition() const
{

   TypedArgBase*  arg1 = mArgHandlers[ 0];
   TypedArgBase*  arg2 = mArgHandlers[ 1];

   if (!arg1->hasValue() || !arg2->hasValue())
      return;

   C1  cont1;
   C2  cont2;

   static_cast< TypedArg< C1>*>( arg1)->getValue( cont1);
   static_cast< TypedArg< C2>*>( arg2)->getValue( cont2);

   if (common::hasIntersection( cont1, cont2))
      throw std::runtime_error( "containers of variable '" + arg1->varName()
         + "' from argument '" + format::toString( arg1->key())
         + "' and variable '" + arg2->varName() +"' from argument '"
         + format::toString( arg2->key()) + "' intersect in at least one value,"
              " must be disjoint");

} // ValueConstraintDisjoint< C1, C2>::checkEndCondition


template< typename C1, typename C2>
   bool ValueConstraintDisjoint< C1, C2>::matchesVarType(
      const std::string& var_type_name) const
{
   return (var_type_name == type< C1>::name())
      || (var_type_name == type< C2>::name());
} // ValueConstraintDisjoint< C1, C2>::matchesVarType


template< typename C1, typename C2>
   std::string ValueConstraintDisjoint< C1, C2>::toString() const
{

   std::ostringstream  oss;

   oss << "disjoint_containers( " << mArgSpecList << ")";

   return oss.str();
} // ValueConstraintDisjoint< C1, C2>::toString


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
template< typename C1>
   detail::IHandlerValueConstraint* disjoint( const std::string& argSpec)
{
   return new detail::ValueConstraintDisjoint< C1, C1>( argSpec);
} // disjoint


/// Helper function to easily add a 'disjoint' value constraint.
/// Usage:  argument_handler_object.addValueConstraint( disjoint< std::vector< int>, std::set< int>( "..."));
///
/// @param[in]  argSpec
///    The list of arguments (argument keys) of which the values must be
///    different.
/// @return  The newly created constraint object.
/// @since  1.33.0, 30.10.2019
template< typename C1, typename C2>
   detail::IHandlerValueConstraint* disjoint( const std::string& argSpec)
{
   return new detail::ValueConstraintDisjoint< C1, C2>( argSpec);
} // disjoint


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_VALUE_CONSTRAINT_DISJOINT_HPP


// =====  END OF value_constraint_disjoint.hpp  =====

