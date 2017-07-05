
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
/// See documentation of class celma::prog_args::detail::ConstraintContainer.


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_CONTAINER_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_CONTAINER_HPP


#include <string>
#include <vector>
#include "celma/prog_args/detail/argument_key.hpp"
#include "celma/prog_args/detail/storage.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Handles the argument constraints:<br>
/// - Runtime required arguments<br>
///   Use case: Argument 'a' requires argument(s) 'b', 'c' etc.<br>
///   Set as: Constraint on argument 'a'.<br>
///   Handling:<br>
///   - When argument 'a' is used, add constraint to the list.
///   - When argument 'b' is used, remove it from the list.
///   - After evaluation arguments, check that the list is empty.
/// .
/// @todo  Using a global variable to provide access to the current object of
///        this class is of course not thread-safe. Need to find a better
///        solution.
/// @todo  Enum class.
/// @since  0.2, 10.04.2016
class ConstraintContainer
{
public:
   /// List of supported constraints:
   enum class Constraint
   {
      unknown,    //!< Initialisation value.
      required,   //!< Required argument(s).
      excluded,   //!< Excluded (forbidden) argument(s).
      allOf,      //!< If one of a group of arguments is used, all arguments of
                  //!< this group must be used.
      anyOf,      //!< Any argument of a group of arguments may be used, but at
                  //!< least one of them.
      oneOf       //!< Exactly one argument of a group of argumnts must be used.
   };

   /// Sometimes need acceess to the current constraint container from other
   /// classes/methods. This member variable points to it.
   static ConstraintContainer*  mpCurrentConstraints;

   /// Constructor.
   /// @since  x.y.z, 26.06.2017
   ConstraintContainer();

   /// Default destructor is just fine.
   ~ConstraintContainer() = default;

   /// Adds an argument specific constraint.
   /// @param[in]  constraint_type  The type of the constraint to add.
   /// @param[in]  arg_spec         The (list of) argument specifications, both
   ///                              short and/or long argument must be set.
   /// @param[in]  created_by       The argument that set this constraint.
   /// @since  0.2, 10.04.2016
   void addConstraint( Constraint constraint_type,
                       const std::string& arg_spec,
                       const std::string& created_by);

   /// Adds a global constraint that affects multiple arguments in the current
   /// argument handler.
   /// @param[in]  constraint_type  The type of the constraint to add.
   /// @param[in]  arg_spec         The (list of) argument specifications, both
   ///                              short and/or long argument must be set.
   /// @since  0.2, 10.04.2016
   void addConstraint( Constraint constraint_type,
                       const std::string& arg_spec);

   /// Must be called for each argument from the command line that was
   /// identified.<br>
   /// Internally checks if there is a constraint for this argument.
   /// @param[in]  argSpec  The argument (short or long) that was identified
   ///                      from the command line.
   /// @since  0.2, 10.04.2016
   void argumentIdentified( const std::string& argSpec);

   /// Checks if there are open constraints in the list.
   /// @since  0.2, 10.04.2016
   void checkRequired();

protected:
   /// Helper class to store a (list of) argument(s).
   /// @since  0.2, 10.04.2016
   class Data
   {
   public:
      /// Constructor.
      /// @param[in]  c       The type of the constraint.
      /// @param[in]  origin  The origin (== argument) of this constraint.
      /// @since  0.2, 10.04.2016
      explicit Data( Constraint c = Constraint::unknown,
                     const std::string& origin = "");

      /// The type of the constraint.
      Constraint   mConstraint;
      /// The argument that set this constraint. Used for error reporting only.
      std::string  mOrigin;

   }; // ConstraintContainer::Data

   /// The container with the current constraints.
   Storage< Data>  mConstraints;

}; // ConstraintContainer


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_CONTAINER_HPP


// =====================  END OF constraint_container.hpp  =====================

