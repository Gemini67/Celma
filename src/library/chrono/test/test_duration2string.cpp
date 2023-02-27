
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the functions of the module "duration 2 string", using the
**    Boost.Test frmework.
**
--*/


// module to test headerfile include
#include "celma/chrono/duration2string.hpp"


// Boost includes
#define BOOST_TEST_MODULE Duration2StringTest
#include <boost/test/unit_test.hpp>


using celma::chrono::duration2string;



/// Verify conversion of seconds period to string.
/// @since  x.y.z, 27.02.2023
BOOST_AUTO_TEST_CASE( conversions)
{

   BOOST_REQUIRE_EQUAL( duration2string( 0), "0s");
   BOOST_REQUIRE_EQUAL( duration2string( 1), "1s");
   BOOST_REQUIRE_EQUAL( duration2string( 59), "59s");
   BOOST_REQUIRE_EQUAL( duration2string( 60), "1m 0s");
   BOOST_REQUIRE_EQUAL( duration2string( 61), "1m 1s");
   BOOST_REQUIRE_EQUAL( duration2string( 60 * 60 - 1), "59m 59s");
   BOOST_REQUIRE_EQUAL( duration2string( 60 * 60), "1h 0m 0s");
   BOOST_REQUIRE_EQUAL( duration2string( 60 * 60 + 60 + 1), "1h 1m 1s");
   BOOST_REQUIRE_EQUAL( duration2string( 24 * 60 * 60 - 1), "23h 59m 59s");
   BOOST_REQUIRE_EQUAL( duration2string( 24 * 60 * 60), "1d 0h 0m 0s");
   BOOST_REQUIRE_EQUAL( duration2string( 24 * 60 * 60 + 3600 + 60 + 1),
      "1d 1h 1m 1s");
   BOOST_REQUIRE_EQUAL( duration2string( 7 * 24 * 60 * 60 - 1), "6d 23h 59m 59s");
   BOOST_REQUIRE_EQUAL( duration2string( 7 * 24 * 60 * 60), "1w 0d 0h 0m 0s");

} // conversions



// =====  END OF test_duration2string.cpp  =====

