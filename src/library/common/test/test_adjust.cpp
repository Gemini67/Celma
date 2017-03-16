
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// project includes
#include "celma/common/adjust.hpp"


// Boost includes
#define BOOST_TEST_MODULE AdjustTest
#include <boost/test/unit_test.hpp>
#include <utility>



/// Test template function adjustMin.
/// @since  0.13.4, 24.02.2017
BOOST_AUTO_TEST_CASE( test_adjust_min)
{

   {
      int  value = -1;

      celma::common::adjustMin( value, 0);

      BOOST_REQUIRE_EQUAL( value, 0);
   } // end scope

   {
      long int  value = 1;

      celma::common::adjustMin( value, 0L);

      BOOST_REQUIRE_EQUAL( value, 1);
   } // end scope

   {
      int  value = 123;

      celma::common::adjustMin( value, 150);

      BOOST_REQUIRE_EQUAL( value, 150);
   } // end scope

} // test_adjust_min



/// Test template function adjustMax.
/// @since  0.13.4, 24.02.2017
BOOST_AUTO_TEST_CASE( test_adjust_max)
{

   {
      int  value = -1;

      celma::common::adjustMax( value, 0);

      BOOST_REQUIRE_EQUAL( value, -1);
   } // end scope

   {
      long int  value = 1;

      celma::common::adjustMax( value, 0L);

      BOOST_REQUIRE_EQUAL( value, 0);
   } // end scope

   {
      int  value = 123;

      celma::common::adjustMax( value, 150);

      BOOST_REQUIRE_EQUAL( value, 123);
   } // end scope

} // test_adjust_max



// =========================  END OF test_adjust.cpp  =========================

