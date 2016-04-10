
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module ConstraintContainer, using the Boost.Test
**    module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// STL includes
#include <string>
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE ConstraintContainerTest
#include <boost/test/unit_test.hpp>


// project includes
#define  protected  public
#define  private    public
#include "celma/prog_args/detail/constraint_container.hpp"


using namespace std;
using namespace celma;


// module definitions


/// Check that an constraint container does nothing.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( empty_constraints)
{

   prog_args::detail::ConstraintContainer  constraints;


   BOOST_REQUIRE_NO_THROW( constraints.argumentIdentified( "a"));
   BOOST_REQUIRE_NO_THROW( constraints.checkRequired());

} // end empty_constraints



/// Duplicate argument(s) in the list should be silently discarded.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_constraint)
{

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "a;b;a", "s");
      BOOST_REQUIRE_EQUAL( constraints.mConstraints.size(), 2);
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "n,name;b;n", "s");
      BOOST_REQUIRE_EQUAL( constraints.mConstraints.size(), 2);
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "n,name;b;name", "s");
      BOOST_REQUIRE_EQUAL( constraints.mConstraints.size(), 2);
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "n,name;b;n,name", "s");
      BOOST_REQUIRE_EQUAL( constraints.mConstraints.size(), 2);
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "n;b;n,name", "s");
      BOOST_REQUIRE_EQUAL( constraints.mConstraints.size(), 2);
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "name;b;n,name", "s");
      BOOST_REQUIRE_EQUAL( constraints.mConstraints.size(), 2);
   } // end scope

} // end duplicate_constraint



/// Add a 'requires' constraint.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_requires_constraint)
{

   // argument with 'required' constraint added, not found

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "o", "i,input");

      BOOST_REQUIRE_THROW( constraints.checkRequired(), runtime_error);
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "output", "i,input");

      BOOST_REQUIRE_THROW( constraints.checkRequired(), runtime_error);
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "o,output", "i,input");

      BOOST_REQUIRE_THROW( constraints.checkRequired(), runtime_error);
   } // end scope

   // argument with 'required' constraint added, found

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "o", "i,input");
      constraints.argumentIdentified( "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "output", "i,input");
      constraints.argumentIdentified( "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "o,output", "i,input");
      constraints.argumentIdentified( "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

} // end one_requires_constraint



/// Add an 'excludes' constraint.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_excludes_constraint)
{

   // argument with 'exclude' constraint added, not used

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "o", "i,input");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "output", "i,input");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "o,output", "i,input");

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   
   // argument with 'excluded' constraint added, found

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "o", "i,input");
      BOOST_REQUIRE_THROW( constraints.argumentIdentified( "o,output"), runtime_error);

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "output", "i,input");
      BOOST_REQUIRE_THROW( constraints.argumentIdentified( "o,output"), runtime_error);

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "o,output", "i,input");
      BOOST_REQUIRE_THROW( constraints.argumentIdentified( "o,output"), runtime_error);

      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

} // end one_excludes_constraint



/// Add different combinations of constraints.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( combinations)
{

   // arguments with 'exclude' and 'required' constraint added, required not used

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "o", "i,input");
      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "p", "o,output");

      // required argument not found
      BOOST_REQUIRE_THROW( constraints.checkRequired(), runtime_error);
   } // end scope

   // arguments with 'exclude' and 'required' constraint added, required used

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "o", "i,input");
      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "p", "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.argumentIdentified( "p,port"));

      // required argument not found
      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "o", "i,input");
      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "p,port", "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.argumentIdentified( "port"));

      // required argument not found
      BOOST_REQUIRE_NO_THROW( constraints.checkRequired());
   } // end scope

   // arguments with 'exclude' and 'required' constraint added, required used,
   // excluded used

   {
      prog_args::detail::ConstraintContainer  constraints;

      constraints.addConstraint( prog_args::detail::ConstraintContainer::cExcluded, "o", "i,input");
      constraints.addConstraint( prog_args::detail::ConstraintContainer::cRequired, "p", "o,output");

      BOOST_REQUIRE_NO_THROW( constraints.argumentIdentified( "p,port"));
      BOOST_REQUIRE_THROW( constraints.argumentIdentified( "o"), runtime_error);
   } // end scope

} // end combinations



// =========================  END OF test_constraint_container.cpp  =========================

