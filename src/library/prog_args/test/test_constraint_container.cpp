
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module ConstraintContainer, using the Boost.Test
**    module.
**
--*/


// module to test header file include
#include "celma/prog_args/detail/constraint_container.hpp"


// OS/C lib includes


// C++ Standard Library includes
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE ConstraintContainerTest
#include <boost/test/unit_test.hpp>


// project includes


using celma::prog_args::detail::ConstraintContainer;
using std::runtime_error;


// module definitions


namespace {


class ConstraintAccess: public ConstraintContainer
{
public:
   /// 
   /// @return  .
   /// @since  x.y.z, 27.06.2017
   size_t size() const
   {
      return mConstraints.size();
   }
};


} // namespace


/// Check that an constraint container does nothing.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( empty_constraints)
{

   ConstraintContainer  constraints;


   BOOST_REQUIRE_NO_THROW( constraints.argumentIdentified( "a"));
   BOOST_REQUIRE_NO_THROW( constraints.checkRequired());

} // empty_constraints



/// Duplicate argument(s) in the list should be silently discarded.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_constraint)
{

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "a;b;a", "s");
      BOOST_REQUIRE_EQUAL( constraints.size(), 2);
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "n,name;b;n", "s");
      BOOST_REQUIRE_EQUAL( constraints.size(), 2);
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "n,name;b;name", "s");
      BOOST_REQUIRE_EQUAL( constraints.size(), 2);
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "n,name;b;n,name", "s");
      BOOST_REQUIRE_EQUAL( constraints.size(), 2);
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "n;b;n,name", "s");
      BOOST_REQUIRE_EQUAL( constraints.size(), 2);
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "name;b;n,name", "s");
      BOOST_REQUIRE_EQUAL( constraints.size(), 2);
   } // end scope

} // duplicate_constraint



/// Add a 'requires' constraint.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_requires_constraint)
{

   // argument with 'required' constraint added, not found

   {
      ConstraintContainer  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "o", "i,input");

      BOOST_REQUIRE_THROW( constraints.checkRequired(), runtime_error);
   } // end scope

   {
      ConstraintContainer  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "output", "i,input");

      BOOST_REQUIRE_THROW( constraints.checkRequired(), runtime_error);
   } // end scope

   {
      ConstraintContainer  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "o,output", "i,input");

      BOOST_REQUIRE_THROW( constraints.checkRequired(), runtime_error);
   } // end scope

   // argument with 'required' constraint added, found

   {
      ConstraintContainer  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "o", "i,input");
      constraints.argumentIdentified( "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      ConstraintContainer  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required, 
                                 "output", "i,input");
      constraints.argumentIdentified( "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      ConstraintContainer  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "o,output", "i,input");
      constraints.argumentIdentified( "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

} // one_requires_constraint



/// Add an 'excludes' constraint.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_excludes_constraint)
{

   // argument with 'exclude' constraint added, not used

   {
      ConstraintContainer  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "o", "i,input");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "output", "i,input");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "o,output", "i,input");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   
   // argument with 'excluded' constraint added, found

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "o", "i,input");
      BOOST_REQUIRE_THROW( constraints.argumentIdentified( "o,output"),
                           runtime_error);

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "output", "i,input");
      BOOST_REQUIRE_THROW( constraints.argumentIdentified( "o,output"),
                           runtime_error);

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "o,output", "i,input");
      BOOST_REQUIRE_THROW( constraints.argumentIdentified( "o,output"),
                           runtime_error);

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

} // one_excludes_constraint



/// Add different combinations of constraints.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( combinations)
{

   // arguments with 'exclude' and 'required' constraint added, required not used

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "o", "i,input");
      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "p", "o,output");

      // required argument not found
      BOOST_REQUIRE_THROW( constraints.checkRequired(), runtime_error);
   } // end scope

   // arguments with 'exclude' and 'required' constraint added, required used

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "o", "i,input");
      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "p", "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.argumentIdentified( "p,port"));

      // required argument not found
      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "o", "i,input");
      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "p,port", "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.argumentIdentified( "port"));

      // required argument not found
      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   // arguments with 'exclude' and 'required' constraint added, required used,
   // excluded used

   {
      ConstraintAccess  constraints;

      constraints.addConstraint( ConstraintContainer::Constraint::excluded,
                                 "o", "i,input");
      constraints.addConstraint( ConstraintContainer::Constraint::required,
                                 "p", "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.argumentIdentified( "p,port"));
      BOOST_REQUIRE_THROW( constraints.argumentIdentified( "o"), runtime_error);
   } // end scope

} // combinations



// ==================  END OF test_constraint_container.cpp  ==================

