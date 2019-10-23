
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
/// See documentation of class celma::prog_args::ConstraintContainer.


// module header file include
#include "celma/prog_args/detail/constraint_container.hpp"


// C++ Standard Library includes
#include <algorithm>
#include <stdexcept>


// project includes
#include "celma/common/tokenizer.hpp"
#include "celma/format/to_string.hpp"


namespace celma { namespace prog_args { namespace detail {


using std::string;


// module definitions
ConstraintContainer*  ConstraintContainer::mpCurrentConstraints = nullptr;



/// Constructor.
/// @since  0.15.0, 26.06.2017
ConstraintContainer::ConstraintContainer():
   mConstraints( true)
{
} // ConstraintContainer::ConstraintContainer



/// Adds a (list of) required argument(s).
/// @param[in]  constraint_type  The type of the constraint to add.
/// @param[in]  arg_spec         The (list of) argument specifications, both
///                              short and/or long argument must be set.
/// @param[in]  created_by       The argument that set this constraint.
/// @since  0.2, 10.04.2016
void ConstraintContainer::addConstraint( Constraint constraint_type,
                                         const string& arg_spec,
                                         const string& created_by)
{

   common::Tokenizer  tokenizer( arg_spec, ';');


   for (auto const& token : tokenizer)
   {
      // don't add the same constraint twice
      const ArgumentKey  search( token);
      auto               dataIt = mConstraints.find( search);

      if ((dataIt == mConstraints.end())
          || (dataIt->data().mConstraint != constraint_type))
      {
         mConstraints.addArgument( Data( constraint_type, created_by), search);
      } // end if
   } // end for

} // ConstraintContainer::addConstraint



/// Must be called for each argument from the command line that was
/// identified.<br>
/// Internally checks if there is a constraint for this argument.
/// @param[in]  key  The argument (short or long) that was identified from
///                  the command line.
/// @since  0.2, 10.04.2016
void ConstraintContainer::argumentIdentified( const ArgumentKey& key)
{

   if (mConstraints.empty())
      return;

   auto  it = mConstraints.cbegin();

   while ((it = std::find( it, mConstraints.cend(), key)) != mConstraints.cend())
   {
      if (it->data().mConstraint == Constraint::required)
      {
         it = mConstraints.erase( it);
      } else if (it->data().mConstraint == Constraint::excluded)
      {
         throw std::runtime_error( "Argument '" + format::toString( key)
                                   + "' is excluded by '" + it->data().mOrigin
                                   + "'");
      } // end if
   } // end while

} // ConstraintContainer::argumentIdentified



/// Checks if there are open constraints in the list.
/// @since  0.2, 10.04.2016
void ConstraintContainer::checkRequired()
{

   for (auto const& current_constraint : mConstraints)
   {
      if (current_constraint.data().mConstraint == Constraint::required)
      {
         
         throw std::runtime_error(
            string( "Argument '").
                  append( format::toString( current_constraint.key())).
                  append( "' required by '").
                  append( current_constraint.data().mOrigin).
                  append( "' is missing"));
      } // end if
   } // end for

} // ConstraintContainer::checkRequired



/// Constructor.
/// @param[in]  arg_spec  The argument specification, short and/or long
///                       argument.
/// @param[in]  c         The type of the constraint.
/// @param[in]  origin    The origin (== argument) of this constraint.
/// @since  0.2, 10.04.2016
ConstraintContainer::Data::Data( Constraint c, const string& origin):
   mConstraint( c),
   mOrigin( origin)
{
} // ConstraintContainer::Data::Data



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF constraint_container.cpp  =====

