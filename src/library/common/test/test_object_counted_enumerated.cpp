
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
**    Test program for the modules celma::common::ObjectCounter and
**    celma::common::ObjectEnumerator, using the Boost.Test framework.
**
--*/


// module to test, header file include
#include "celma/common/object_counter.hpp"
#include "celma/common/object_enumerator.hpp"


// Boost includes
#define BOOST_TEST_MODULE ObjectCountedEnumeratedTest
#include <boost/test/unit_test.hpp>


using celma::common::ObjectCounter;
using celma::common::ObjectEnumerator;


namespace {


/// Helper class for the test program. Uses counted and enumerated objects.
///
/// @since  x.y.z, 22.08.2018
class CountedOne: public ObjectCounter< CountedOne>,
   public ObjectEnumerator< CountedOne>
{
}; // CountedOne


/// Second helper class for the test program. Also uses counted and enumerated
/// objects.
///
/// @since  x.y.z, 22.08.2018
class CountedTwo: public ObjectCounter< CountedTwo>,
   public ObjectEnumerator< CountedTwo>
{
}; // CountedTwo


} // namespace



/// Simple case: Create and delete one single object.
///
/// @since  x.y.z, 22.08.2018
BOOST_AUTO_TEST_CASE( one_object)
{

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 1);
   } // end scope

} // one_object



/// Create two objects (of the same class).
///
/// @since  x.y.z, 22.08.2018
BOOST_AUTO_TEST_CASE( two_objects)
{

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 2);

      {
         CountedOne  c2( c1);

         BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 2);
         BOOST_REQUIRE_EQUAL( c1.objectNbr(), 2);
         BOOST_REQUIRE_EQUAL( c2.objectNbr(), 3);
      } // end scope

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 2);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);

} // two_objects



/// Create objects of two different classes and make sure that their object
/// numbers are independent.
///
/// @since  x.y.z, 22.08.2018
BOOST_AUTO_TEST_CASE( classes_independent)
{

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);
   BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 4);
      BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);
   BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 5);
      BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);

      {
         CountedTwo  c2;

         BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
         BOOST_REQUIRE_EQUAL( c1.objectNbr(), 5);
         BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 1);
         BOOST_REQUIRE_EQUAL( c2.objectNbr(), 0);

         {
            CountedTwo  c3;

            BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
            BOOST_REQUIRE_EQUAL( c1.objectNbr(), 5);
            BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 2);
            BOOST_REQUIRE_EQUAL( c2.objectNbr(), 0);
            BOOST_REQUIRE_EQUAL( c3.objectNbr(), 1);
         } // end scope

         BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
         BOOST_REQUIRE_EQUAL( c1.objectNbr(), 5);
         BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 1);
         BOOST_REQUIRE_EQUAL( c2.objectNbr(), 0);
      } // end scope

      BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 1);
      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 5);
      BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( CountedOne::numObjects(), 0);
   BOOST_REQUIRE_EQUAL( CountedTwo::numObjects(), 0);

} // classes_independent



// =====  END OF test_object_counted_enumerated.cpp  =====

