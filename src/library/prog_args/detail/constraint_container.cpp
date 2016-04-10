
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
/// See documentation of class celma::prog_args::ConstraintContainer.


// module header file include
#include "celma/prog_args/detail/constraint_container.hpp"


// C++ Standard Library includes
#include <algorithm>
#include <stdexcept>


// project includes
#include "celma/common/tokenizer.hpp"


using namespace std;


namespace celma { namespace prog_args { namespace detail {


// module definitions
ConstraintContainer*  ConstraintContainer::mpCurrentConstraints = nullptr;



/// Constructor.
/// @since  0.2, 10.04.2016
ConstraintContainer::ConstraintContainer():
   mConstraints()
{
} // end ConstraintContainer::ConstraintContainer



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

   common::Tokenizer  tok( arg_spec, ';');


   for (auto it : tok)
   {
      // don't add the same constraint twice
      const Data                      search( it);
      const DataCont::const_iterator  dataIt = find( mConstraints.begin(),
                                                     mConstraints.end(),
                                                     search);
      if ((dataIt == mConstraints.end()) || (dataIt->mConstraint != constraint_type))
      {
         mConstraints.push_back( Data( it, constraint_type, created_by));
      } // end if
   } // end for

} // end ConstraintContainer::addConstraint



/// Must be called for each argument from the command line that was
/// identified.<br>
/// Internally checks if there is a constraint for this argument.
/// @param[in]  argSpec  The argument (short or long) that was identified
///                      from the command line.
/// @since  0.2, 10.04.2016
void ConstraintContainer::argumentIdentified( const string& argSpec)
{

   if (mConstraints.empty())
      return;

   const Data  search( argSpec);
   auto        it = mConstraints.begin();

   while ((it = find( it, mConstraints.end(), search)) != mConstraints.end())
   {
      if (it->mConstraint == cRequired)
      {
         it = mConstraints.erase( it);
      } else if (it->mConstraint == cExcluded)
      {
         throw runtime_error( "Argument '" + it->spec() + "' is excluded by '" +
                              it->mOrigin + "'");
      } // end if
   } // end while

} // end ConstraintContainer::argumentIdentified



/// Checks if there are open constraints in the list.
/// @since  0.2, 10.04.2016
void ConstraintContainer::checkRequired()
{

   for (size_t i = 0; i < mConstraints.size(); ++i)
   {
      const Data&  currentConstraint = mConstraints[ i];
      if (currentConstraint.mConstraint == cRequired)
      {
         
         throw runtime_error( string( "Argument '").append( currentConstraint.spec()).
                              append( "' required by '").
                              append( currentConstraint.mOrigin).
                              append( "' is missing"));
      } // end if
   } // end for

} // end ConstraintContainer::checkRequired



/// Constructor.
/// @param[in]  arg_spec  The argument specification, short and/or long
///                       argument.
/// @param[in]  c         The type of the constraint.
/// @param[in]  origin    The origin (== argument) of this constraint.
/// @since  0.2, 10.04.2016
ConstraintContainer::Data::Data( const string& arg_spec, Constraint c,
                                 const string& origin):
   mArgKeys( arg_spec),
   mConstraint( c),
   mOrigin( origin)
{
} // end ConstraintContainer::Data::Data



/// Returns if either the short or long argument match.
/// @param[in]  other  The other object to compare against.
/// @return  \c true if the short or long argument match.
/// @since  0.2, 10.04.2016
bool ConstraintContainer::Data::operator ==( const ConstraintContainer::Data& other) const
{

   return mArgKeys == other.mArgKeys;
} // end ConstraintContainer::Data::operator ==



/// Returns the argument specification as set on the constructor (rebuilt,
/// actually).
/// @return  The complete argument specification.
/// @since  0.2, 10.04.2016
string ConstraintContainer::Data::spec() const
{

   return mArgKeys.str();
} // end ConstraintContainer::Data::spec



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF constraint_container.cpp  =========================

