
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module celma::common::ObjectCounter, using the
**    Boost.Test framework.
**
--*/


// module to test, header file include
#include "celma/common/object_counter.hpp"


// Boost includes
#define BOOST_TEST_MODULE ObjectCounterTest
#include <boost/test/unit_test.hpp>


using celma::common::ObjectCounter;


namespace {


/// Helper class for the test program. Uses counted objects.
///
/// @since  1.11.0, 21.08.2018
class CountedOne: public ObjectCounter< CountedOne>
{
}; // CountedOne


/// Second helper class for the test program. Also uses counted objects.
///
/// @since  1.11.0, 22.08.2018
class CountedTwo: public ObjectCounter< CountedTwo>
{
}; // CountedTwo


/// For testing the move constructor: Move-returns a new object.
///
/// @return  A new CountedOne object.
/// @since  1.11.0, 22.08.2018
CountedOne creator()
{
   return std::move( CountedOne());
} // creator


} // namespace



/// Simple case: Create and delete one single object.
///
/// @since  1.11.0, 21.08.2018
BOOST_AUTO_TEST_CASE( one_object)
{

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

} // one_object



/// Create two objects (of the same class).
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( two_objects)
{

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);

      {
         CountedOne  c2( c1);

         BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 2);
      } // end scope

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

} // two_objects



/// Test the move constructor.
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( move_ctor)
{

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

   {
      CountedOne  c1 = creator();

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

} // move_ctor



/// Create objects of two different classes and make sure that their object
/// numbers are independent.
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( classes_independent)
{

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);
   BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);
   BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);

      {
         CountedTwo  c2;

         BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
         BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 1);

         {
            CountedTwo  c3;

            BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
            BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 2);
         } // end scope

         BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
         BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 1);
      } // end scope

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);
   BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);

} // classes_independent



// =====  END OF test_object_counter.cpp  =====

