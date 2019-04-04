
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


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ALL_OF_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ALL_OF_HPP


#include <memory>
#include <string>
#include "celma/prog_args/detail/argument_key.hpp"
#include "celma/prog_args/detail/i_handler_constraint.hpp"
#include "celma/prog_args/detail/storage.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Global constraint: All of the specified arguments must be used.
///
/// @since  0.15.0, 19.07.2017
///    (use ArgumentKey type to handle keys)
/// @since  0.2, 10.04.2016
class ConstraintAllOf: public IHandlerConstraint
{
public:
   /// Constructor, does a basic validation of the argument list.
   ///
   /// @param[in]  reqArgSpec  The list of arguments that must be used.
   /// @throws
   ///    "invalid argument" if the string is empty or does not contain at least
   ///    two arguments.
   /// @since  0.2, 10.04.2016
   explicit ConstraintAllOf( const std::string& reqArgSpec) noexcept( false);

   // Default destructor is fine.
   virtual ~ConstraintAllOf() = default;

   /// Called when any argument was identified. Procedure:
   /// - Check if the argument is one of the arguments for which the constraint
   ///   is defined.
   /// - If so, verify that this argument was not already used before and then
   ///   remove it from the list of remaining arguments.
   ///
   /// @param[in]  key  The current argument that was identified.
   /// @since  0.2, 10.04.2016
   virtual void executeConstraint( const ArgumentKey& key) override;

   /// Returns the list of arguments that must be used.
   ///
   /// @return  The list of arguments as passed to the constructor.
   /// @since  0.2, 10.04.2016
   virtual std::string& argumentList() override;

   /// Called after the argument list was validated.
   ///
   /// @since  0.2, 10.04.2016
   virtual void validated() override;

   /// Checks if all of the specified arguments were used, i.e.: if the string
   /// \a #mRemainingArguments is empty.
   ///
   /// @since  0.2, 10.04.2016
   virtual void checkEndCondition() const override;

   /// Returns a text description of the constraint.
   ///
   /// @return  A string with the text description of the constraint.
   /// @since  0.16.0, 15.08.2017
   virtual std::string toString() const override;

private:
   /// Container for the keys, only keys needed.
   using key_cont_t = Storage< std::nullptr_t>;

   /// The argument specifications of the arguments.<br>
   /// Non-const because non-complete argument specifications may be expanded.
   std::string  mArgSpecList;
   /// When validated() is called, the arguments from #mArgSpecList are copied
   /// here. Afterwards, executeConstraint() will delete the used argument from
   /// it
   key_cont_t   mRemainingArguments;

}; // ConstraintAllOf


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
inline detail::IHandlerConstraint* all_of( const std::string& argSpec)
{
   return new detail::ConstraintAllOf( argSpec);
} // all_of


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_ALL_OF_HPP


// =====  END OF constraint_all_of.hpp  =====

