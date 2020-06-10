
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2020 Rene Eng
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
#include "celma/common/object_enumerator.hpp"


// Boost includes
#define BOOST_TEST_MODULE ObjectEnumeratorTest
#include <boost/test/unit_test.hpp>


using celma::common::ObjectEnumerator;


namespace {


/// Helper class for the test program. Uses enumerated objects.
///
/// @since  1.11.0, 21.08.2018
class CountedOne: public ObjectEnumerator< CountedOne>
{
}; // CountedOne



/// Second helper class for the test program. Also uses enumerated objects.
///
/// @since  1.11.0, 22.08.2018
class CountedTwo: public ObjectEnumerator< CountedTwo>
{
}; // CountedTwo


/// For testing the move constructor: Move-returns a new object.
///
/// @return  A new CountedOne object.
/// @since  1.11.0, 22.08.2018
CountedOne creator()
{
   return CountedOne();
} // creator


} // namespace



/// Check for correct object numbers when using just one class.
///
/// @since  1.11.0, 21.08.2018
BOOST_AUTO_TEST_CASE( one_class)
{

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 0);
   } // end scope

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 1);
   } // end scope

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 2);

      {
         CountedOne  c2( c1);
         BOOST_REQUIRE_EQUAL( c2.objectNbr(), 3);
      } // end scope

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 2);
   } // end scope

} // one_class



/// Check that the move constructor is called: Only one new object is created.
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( move_ctor)
{

   {
      CountedOne  c1 = creator();

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 4);
   } // end scope

} // move_ctor



/// Create objects of two different classes and check that their object numbers
/// are independent.
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( classes_independent)
{

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 5);
   } // end scope

   {
      CountedTwo  c1;

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 0);
   } // end scope

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 6);

      {
         CountedTwo  c2;

         BOOST_REQUIRE_EQUAL( c1.objectNbr(), 6);
         BOOST_REQUIRE_EQUAL( c2.objectNbr(), 1);

         {
            CountedTwo  c3;

            BOOST_REQUIRE_EQUAL( c1.objectNbr(), 6);
            BOOST_REQUIRE_EQUAL( c3.objectNbr(), 2);
         } // end scope
      } // end scope
   } // end scope

   {
      CountedOne  c1;

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 7);
   } // end scope

   {
      CountedTwo  c1;

      BOOST_REQUIRE_EQUAL( c1.objectNbr(), 3);
   } // end scope

} // classes_independent



// =====  END OF test_object_enumerator.cpp  =====

