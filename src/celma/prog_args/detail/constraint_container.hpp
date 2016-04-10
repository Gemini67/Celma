
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
/// See documentation of class celma::prog_args::detail::ConstraintContainer.


#ifndef CELMA_PROG_ARGS_DETAIL_CONSTRAINT_CONTAINER_HPP
#define CELMA_PROG_ARGS_DETAIL_CONSTRAINT_CONTAINER_HPP


#include <string>
#include <vector>
#include "celma/prog_args/detail/argument_key.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Handles the argument constraints:<br>
/// - Runtime required arguments<br>
///   Use case: Argument 'a' requires argument(s) 'b', 'c' etc.<br>
///   Set as: Constraint on argument 'a'.<br>
///   Handling:<br>
///   - When argument 'a' is used, add constraint to the list.
///   - When argument 'b' is used, remove it from the list.
///   - After evaluation arguments, check that the list is empty.
///
/// @since  0.2, 10.04.2016
class ConstraintContainer
{
public:
   /// List of supported constraints:
   enum Constraint
   {
      cUnknown,    //!< Initialisation value.
      cRequired,   //!< Required argument(s).
      cExcluded,   //!< Excluded (forbidden) argument(s).
      cAllOf,
      cAnyOf,
      cOneOf
   };

   /// Sometimes need acceess to the current constraint container from other
   /// classes/methods. This member variable points to it.
   static ConstraintContainer*  mpCurrentConstraints;

   /// Constructor.
   /// @since  0.2, 10.04.2016
   ConstraintContainer();

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

private:
   /// Helper class to store a (list of) argument(s).
   /// @since  0.2, 10.04.2016
   class Data
   {
   public:
      /// Constructor.
      /// @param[in]  arg_spec  The argument specification, short and/or long
      ///                       argument.
      /// @param[in]  c         The type of the constraint.
      /// @param[in]  origin    The origin (== argument) of this constraint.
      /// @since  0.2, 10.04.2016
      explicit Data( const std::string& arg_spec, Constraint c = cUnknown,
                     const std::string& origin = "");

      /// Returns if either the short or long argument match.
      /// @param[in]  other  The other object to compare against.
      /// @return  \c true if the short or long argument match.
      /// @since  0.2, 10.04.2016
      bool operator ==( const Data& other) const;

      /// Returns the argument specification as set on the constructor (rebuilt,
      /// actually).
      /// @return  The complete argument specification.
      /// @since  0.2, 10.04.2016
      std::string spec() const;

      /// The short (char) argument.
      ArgumentKey  mArgKeys;
      /// The type of the constraint.
      Constraint   mConstraint;
      /// The argument that set this constraint. Used for error reporting only.
      std::string  mOrigin;

   }; // ConstraintContainer::Data

   /// The type of the container in which the data is stored.
   typedef std::vector< Data>  DataCont;

   /// The container with the current constraints.
   DataCont  mConstraints;

}; // ConstraintContainer


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_CONSTRAINT_CONTAINER_HPP


// =========================  END OF constraint_container.hpp  =========================

