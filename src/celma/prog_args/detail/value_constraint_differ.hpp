
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
/// @since  x.y.z, 22.10.2019
template< typename T> class ValueConstraintDiffer:
   public IHandlerValueConstraint
{
public:
   /// Constructor.
   ///
   /// @param[in]  reqArgSpec
   ///    The list of arguments of which the values must be different.
   /// @throws
   ///    "invalid argument" if the string is empty or does not contain at least
   ///    two arguments.
   /// @since  x.y.z, 22.10.2019
   explicit ValueConstraintDiffer( const std::string& reqArgSpec) noexcept( false);
   
   // Default destructor is fine.
   virtual ~ValueConstraintDiffer() = default;

   /// Empty here, all the work is done in checkEndCondition().
   ///
   /// @param[in]  key  Ignored.
   /// @since  x.y.z, 22.10.2019
   virtual void executeConstraint( const ArgumentKey& key) override;

   /// Does nothing here.
   ///
   /// @since  x.y.z, 22.10.2019
   virtual void validated() override;

   /// Iterates over all the defined arguments and compares the values set for
   /// these arguments, they must all be different.
   ///
   /// @throw
   ///    std::runtime_error when the same value is found in two different
   ///    arguments.
   /// @since  x.y.z, 22.10.2019
   virtual void checkEndCondition() const noexcept( false) override;

   /// Returns the type set for the constraint as string.
   ///
   /// @return  String with the type of the destination variable.
   /// @since  x.y.z, 23.10.2019
   virtual const std::string varTypeName() const override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  x.y.z, 22.10.2019
   virtual std::string toString() const override;

}; // ValueConstraintDiffer


// inlined methods
// ===============


template< typename T>
   ValueConstraintDiffer< T>::ValueConstraintDiffer( const std::string& reqArgSpec):
      IHandlerValueConstraint( "differ", reqArgSpec)
{
} // ValueConstraintDiffer< T>::ValueConstraintDiffer


template< typename T>
   void ValueConstraintDiffer< T>::executeConstraint( const ArgumentKey&)
{
} // ValueConstraintDiffer< T>::executeConstraint


template< typename T> void ValueConstraintDiffer< T>::validated()
{
} // ValueConstraintDiffer< T>::validated


template< typename T> void ValueConstraintDiffer< T>::checkEndCondition() const
{

   for (auto const& arg1 : mArgHandlers)
   {
      if (!arg1->hasValue())
         continue;

      T  value1;
      static_cast< TypedArg< T>*>( arg1)->getValue( value1);

      for (auto const& arg2 : mArgHandlers)
      {
         if (arg2->hasValue() && (arg1 != arg2))
         {
            T  value2;
            static_cast< TypedArg< T>*>( arg2)->getValue( value2);

            if (value1 == value2)
               throw std::runtime_error( "variable '" + arg1->varName()
                  + "' from argument '" + format::toString( arg1->key())
                  + "' and variable '" + arg2->varName() +"' from argument '"
                  + format::toString( arg2->key()) + "' contain the same "
                  "value, must be different");
         } // end if
      } // end for
   } // end for

} // ValueConstraintDiffer< T>::checkEndCondition


template< typename T>
   const std::string ValueConstraintDiffer< T>::varTypeName() const
{
   return type< T>::name();
} // ValueConstraintDiffer< T>::varTypeName


template< typename T> std::string ValueConstraintDiffer< T>::toString() const
{

   std::ostringstream  oss;

   oss << "different_values( " << mArgSpecList << ")";

   return oss.str();
} // ValueConstraintDiffer< T>::toString


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
/// @since  x.y.z, 22.10.2019
template< typename T>
   detail::IHandlerValueConstraint* differ( const std::string& argSpec)
{
   return new detail::ValueConstraintDiffer< T>( argSpec);
} // differ


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_VALUE_CONSTRAINT_DIFFER_HPP


// =====  END OF value_constraint_differ.hpp  =====

