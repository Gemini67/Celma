
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test header file include
#include "celma/common/current_total.hpp"


// Boost includes
#define BOOST_TEST_MODULE CurrentTotalTest
#include <boost/test/unit_test.hpp>


using celma::common::CurrentTotal;



/// Verify that counters are 0 after initialisation.
///
/// @since  1.11.0, 07.09.2018
BOOST_AUTO_TEST_CASE( init)
{

   CurrentTotal< 3>  stats;


   BOOST_REQUIRE_EQUAL( stats[ 0], 0);
   BOOST_REQUIRE_EQUAL( stats[ 1], 0);
   BOOST_REQUIRE_EQUAL( stats[ 2], 0);

} // init



/// Check that using only one statistic value does not affect the others.
///
/// @since  1.11.0, 07.09.2018
BOOST_AUTO_TEST_CASE( only_one)
{

   CurrentTotal< 4>  four;

   BOOST_REQUIRE_EQUAL( four[ 0], 0);
   BOOST_REQUIRE_EQUAL( four[ 1], 0);
   BOOST_REQUIRE_EQUAL( four[ 2], 0);
   BOOST_REQUIRE_EQUAL( four[ 3], 0);

   ++four[ 0];

   BOOST_REQUIRE_EQUAL( four[ 0], 1);
   BOOST_REQUIRE_EQUAL( four[ 1], 0);
   BOOST_REQUIRE_EQUAL( four[ 2], 0);
   BOOST_REQUIRE_EQUAL( four[ 3], 0);

   BOOST_REQUIRE_EQUAL( four.totalValue( 0), 0);
   BOOST_REQUIRE_EQUAL( four.totalValue( 1), 0);
   BOOST_REQUIRE_EQUAL( four.totalValue( 2), 0);
   BOOST_REQUIRE_EQUAL( four.totalValue( 3), 0);

   four.add2Total();

   BOOST_REQUIRE_EQUAL( four[ 0], 0);
   BOOST_REQUIRE_EQUAL( four[ 1], 0);
   BOOST_REQUIRE_EQUAL( four[ 2], 0);
   BOOST_REQUIRE_EQUAL( four[ 3], 0);

   BOOST_REQUIRE_EQUAL( four.totalValue( 0), 1);
   BOOST_REQUIRE_EQUAL( four.totalValue( 1), 0);
   BOOST_REQUIRE_EQUAL( four.totalValue( 2), 0);
   BOOST_REQUIRE_EQUAL( four.totalValue( 3), 0);

} // only_one



/// Check that updating the total of a single value works correctly.
///
/// @since  1.11.0, 07.09.2018
BOOST_AUTO_TEST_CASE( one_total)
{

   CurrentTotal< 3>  three;


   ++three[ 0];
   ++three[ 1];
   ++three[ 1];
   ++three[ 2];
   ++three[ 2];
   ++three[ 2];

   BOOST_REQUIRE_EQUAL( three[ 0], 1);
   BOOST_REQUIRE_EQUAL( three[ 1], 2);
   BOOST_REQUIRE_EQUAL( three[ 2], 3);

   three.add2Total( false, 1);

   BOOST_REQUIRE_EQUAL( three[ 0], 1);
   BOOST_REQUIRE_EQUAL( three[ 1], 2);
   BOOST_REQUIRE_EQUAL( three[ 2], 3);

   BOOST_REQUIRE_EQUAL( three.totalValue( 0), 0);
   BOOST_REQUIRE_EQUAL( three.totalValue( 1), 2);
   BOOST_REQUIRE_EQUAL( three.totalValue( 2), 0);

} // only_one



/// Update the total multiple times.
///
/// @since  1.11.0, 07.09.2018
BOOST_AUTO_TEST_CASE( multiple_total)
{

   CurrentTotal< 1>  one;


   one.inc( 0);

   BOOST_REQUIRE_EQUAL( one[ 0], 1);

   one.add2Total();

   BOOST_REQUIRE_EQUAL( one.totalValue( 0), 1);

   one.inc( 0, 2);

   BOOST_REQUIRE_EQUAL( one[ 0], 2);

   one.add2Total();

   BOOST_REQUIRE_EQUAL( one.totalValue( 0), 3);

   one.inc( 0, 3);

   BOOST_REQUIRE_EQUAL( one[ 0], 3);

   one.add2Total();

   BOOST_REQUIRE_EQUAL( one.totalValue( 0), 6);

   one.inc( 0, 4);

   BOOST_REQUIRE_EQUAL( one[ 0], 4);

   one.add2Total();

   BOOST_REQUIRE_EQUAL( one.totalValue( 0), 10);

} // multiple_total



/// Check resetting current values and totals.
///
/// @since  1.11.0, 07.09.2018
BOOST_AUTO_TEST_CASE( resetting)
{

   CurrentTotal< 3>  three;


   three.inc( 0, 1);
   three.inc( 1, 2);
   three.inc( 2, 3);

   three.add2Total( false);

   three.resetCurrent( 0);
   three.resetTotal( 1);
   three.reset( 2);

   BOOST_REQUIRE_EQUAL( three.currentValue( 0), 0);
   BOOST_REQUIRE_EQUAL( three.currentValue( 1), 2);
   BOOST_REQUIRE_EQUAL( three.currentValue( 2), 0);

   BOOST_REQUIRE_EQUAL( three.totalValue( 0), 1);
   BOOST_REQUIRE_EQUAL( three.totalValue( 1), 0);
   BOOST_REQUIRE_EQUAL( three.totalValue( 2), 0);

   const CurrentTotal< 3>  copy( three);

   BOOST_REQUIRE_EQUAL( copy[ 0], 0);
   BOOST_REQUIRE_EQUAL( copy[ 1], 2);
   BOOST_REQUIRE_EQUAL( copy[ 2], 0);

   BOOST_REQUIRE_EQUAL( copy.currentValue( 0), 0);
   BOOST_REQUIRE_EQUAL( copy.currentValue( 1), 2);
   BOOST_REQUIRE_EQUAL( copy.currentValue( 2), 0);

   BOOST_REQUIRE_EQUAL( copy.totalValue( 0), 1);
   BOOST_REQUIRE_EQUAL( copy.totalValue( 1), 0);
   BOOST_REQUIRE_EQUAL( copy.totalValue( 2), 0);

} // resetting



// =====  END OF test_current_total.cpp  =====

