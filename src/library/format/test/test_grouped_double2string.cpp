
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
**    Test program for the function celma::format::grouped_double2str(), using
**    the Boost.Test framework.
**
--*/


// first include the module header to test
#include "celma/format/grouped_double2string.hpp"


// OS/C lib includes
#include <cmath>


// Boost includes
#define BOOST_TEST_MODULE GroupedDoubleString32Test
#include <boost/test/unit_test.hpp>


using celma::format::grouped_double2string;



/// Test several conversion of a floating point number into the grouped format.
///
/// @since  1.13.0, 04.10.2018
BOOST_AUTO_TEST_CASE( grouped_double_conversions)
{

   BOOST_REQUIRE_EQUAL( grouped_double2string( 0.0, 1), "0.0");
   BOOST_REQUIRE_EQUAL( grouped_double2string( 0.001, 3), "0.001");
   BOOST_REQUIRE_EQUAL( grouped_double2string( 100.001, 3), "100.001");
   BOOST_REQUIRE_EQUAL( grouped_double2string( M_PI, 7), "3.1415927");

   BOOST_REQUIRE_EQUAL( grouped_double2string( 123456.789, 2), "123'456.79");
   BOOST_REQUIRE_EQUAL( grouped_double2string( 1000000.001, 4), "1'000'000.0010");

   BOOST_REQUIRE_EQUAL( grouped_double2string( -1000000.001, 4), "-1'000'000.0010");

} // grouped_double_conversions



// =====  END OF test_grouped_double2string.cpp  =====

