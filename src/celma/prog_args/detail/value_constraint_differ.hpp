
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
/// See documentation of class celma::prog_args::detail::ValueConstraintDiffer.


#ifndef CELMA_PROG_ARGS_DETAIL_VALUE_CONSTRAINT_DIFFER_HPP
#define CELMA_PROG_ARGS_DETAIL_VALUE_CONSTRAINT_DIFFER_HPP


#include <sstream>
#include <stdexcept>
#include <string>
#include "celma/common/type_name.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args/detail/i_handler_value_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Constraint: The values of the given arguments must be different.
///
/// @tparam  T  The type of the values of the arguments to check.
/// @since  1.31.0, 22.10.2019
class ValueConstraintDiffer: public IHandlerValueConstraint
{
public:
   /// Constructor.
   ///
   /// @param[in]  reqArgSpec
   ///    The list of arguments of which the values must be different.
   /// @throw
   ///    std::invalid_argument if the string is empty or does not contain at
   ///    least two arguments.
   /// @since  1.31.0, 22.10.2019
   explicit ValueConstraintDiffer( const std::string& reqArgSpec) noexcept( false);
   
   // Default destructor is fine.
   ~ValueConstraintDiffer() override = default;

   /// Empty here, all the work is done in checkEndCondition().
   ///
   /// @param[in]  key  Ignored.
   /// @since  1.31.0, 22.10.2019
   void executeConstraint( const ArgumentKey& key) override;

   /// Does nothing here.
   ///
   /// @since  1.31.0, 22.10.2019
   void validated() override;

   /// Iterates over all the defined arguments and compares the values set for
   /// these arguments, they must all be different.
   ///
   /// @throw
   ///    std::runtime_error when the same value is found in two different
   ///    arguments.
   /// @since  1.31.0, 22.10.2019
   void checkEndCondition() const noexcept( false) override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  1.31.0, 22.10.2019
   std::string toString() const override;

}; // ValueConstraintDiffer


// inlined methods
// ===============


inline ValueConstraintDiffer::ValueConstraintDiffer( const std::string& reqArgSpec):
   IHandlerValueConstraint( "differ", reqArgSpec)
{
} // ValueConstraintDiffer::ValueConstraintDiffer


inline void ValueConstraintDiffer::executeConstraint( const ArgumentKey&)
{
} // ValueConstraintDiffer::executeConstraint


inline void ValueConstraintDiffer::validated()
{
} // ValueConstraintDiffer::validated


inline void ValueConstraintDiffer::checkEndCondition() const
{

   for (auto const& arg1 : mArgHandlers)
   {
      if (!arg1->hasValue())
         continue;

      for (auto const& arg2 : mArgHandlers)
      {
         if ((arg1 != arg2) && arg2->hasValue()
             && (arg1->compareValue( arg2) == 0))
         {
            throw std::runtime_error( "variable '" + arg1->varName()
               + "' from argument '" + format::toString( arg1->key())
               + "' and variable '" + arg2->varName() +"' from argument '"
               + format::toString( arg2->key()) + "' contain the same "
               "value, must be different");
         } // end if
      } // end for
   } // end for

} // ValueConstraintDiffer::checkEndCondition


inline std::string ValueConstraintDiffer::toString() const
{

   std::ostringstream  oss;

   oss << "different_values( " << mArgSpecList << ")";

   return oss.str();
} // ValueConstraintDiffer::toString


} // namespace detail


// helper function
// ===============


/// Helper function to easily add a 'differ' value constraint.<br>
/// Usage:  argument_handler_object.addValueConstraint( differ< std::string>( "..."));
///
/// @param[in]  argSpec
///    The list of arguments (argument keys) of which the values must be
///    different.
/// @return  The newly created constraint object.
/// @since  1.31.0, 22.10.2019
inline detail::IHandlerValueConstraint* differ( const std::string& argSpec)
{
   return new detail::ValueConstraintDiffer( argSpec);
} // differ


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_VALUE_CONSTRAINT_DIFFER_HPP


// =====  END OF value_constraint_differ.hpp  =====

