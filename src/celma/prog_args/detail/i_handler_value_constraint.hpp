
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
/// See documentation of class
/// celma::prog_args::detail::IHandlerValueConstraint.


#ifndef CELMA_PROG_ARGS_DETAIL_I_HANDLER_VALUE_CONSTRAINT_HPP
#define CELMA_PROG_ARGS_DETAIL_I_HANDLER_VALUE_CONSTRAINT_HPP


#include <iosfwd>
#include <string>
#include <vector>
#include "celma/prog_args/detail/i_handler_constraint.hpp"


namespace celma { namespace prog_args { namespace detail {


class TypedArgBase;


/// Base class for constraints which affect multiple arguments and are stored/
/// handled in the argument handler itself.
/// This class is an extension of the
/// celma::prog_args::detail::IHandlerConstraint interface, which is used by
/// constraints that compare the value(s) of arguments. For this, the
/// constraints need access to the argument handler objects.
///
/// @since  x.y.z, 22.10.2019
class IHandlerValueConstraint: public IHandlerConstraint
{
public:
   /// Empty, virtual destructor required for base classes.
   ///
   /// @since  x.y.z, 22.10.2019
   virtual ~IHandlerValueConstraint() = default;

   /// Returns \c true.
   ///
   /// @return  Always \c true.
   /// @since  x.y.z, 23.10.2019
   virtual bool isValueConstraint() const override;

   /// Returns the type set for the constraint as string.
   ///
   /// @return  String with the type of the destination variable.
   /// @since  x.y.z, 23.10.2019
   virtual const std::string varTypeName() const = 0;

   /// Stores the pointer to the handler object for one of the arguments in the
   /// argument list.
   /// These objects are needed by the actual constraint implementations to
   /// compare the values.
   ///
   /// @param[in]  handler  Pointer to the argument handler object.
   /// @since  x.y.z, 22.10.2019
   void storeArgumentHandler( TypedArgBase* handler);

   /// Returns the number of arguments (argument handler objects) stored
   /// internally.
   /// This is needed to make sure that at least two arguments have been defined
   /// for the constraint.
   ///
   /// @return
   ///    Number of arguments (argument handler objects) are stored internally.
   /// @since  x.y.z, 23.10.2019
   size_t numArguments() const;

protected:
   /// Constructor.
   ///
   /// @param[in]  constraint_name
   ///    The name of the constraint for error messages.
   /// @param[in]  arg_spec
   ///    The list of arguments affected by the constraint.<br>
   ///    Must already be checked by the calling function (not empty, no invalid
   ///    arguments).
   /// @since  x.y.z, 22.10.2019
   IHandlerValueConstraint( const std::string& constraint_name,
      const std::string& arg_spec);

   /// Type of the container used to store the pointers to the argument handler
   /// objects.
   using storage_t = std::vector< TypedArgBase*>;

   /// The argument handler objects needed to check the constraint.
   storage_t  mArgHandlers;

}; // IHandlerValueConstraint


// inlined methods
// ===============


inline size_t IHandlerValueConstraint::numArguments() const
{
   return mArgHandlers.size();
} // IHandlerValueConstraint::numArguments


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_I_HANDLER_VALUE_CONSTRAINT_HPP


// =====  END OF i_handler_value_constraint.hpp  =====

