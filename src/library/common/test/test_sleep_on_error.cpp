
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// project includes
#include "celma/common/sleep_on_error.hpp"


// Boost includes
#define BOOST_TEST_MODULE SleepOnErrorTest
#include <boost/test/unit_test.hpp>



/// Some basic tests using the template SleepOnError.
/// @since  0.13.4, 24.02.2017
BOOST_AUTO_TEST_CASE( test_basics)
{

   celma::common::SleepOnError<>  soe( 50000, 1000000,
                                       []( int& val)
                                       {
                                          val *= 2;
                                       });

   // default value
   BOOST_REQUIRE_EQUAL( soe.nextSleepTime(), 0);

   soe.sleep( true);

   // minimum value
   BOOST_REQUIRE_EQUAL( soe.nextSleepTime(), 50000);

   // reset to 0
   soe.sleep( false);

   BOOST_REQUIRE_EQUAL( soe.nextSleepTime(), 0);

   soe.sleep( true);

   // minimum value
   BOOST_REQUIRE_EQUAL( soe.nextSleepTime(), 50000);

   soe.sleep( true);

   // function called for the first time
   BOOST_REQUIRE_EQUAL( soe.nextSleepTime(), 100000);

   soe.sleep( true);   // 200'000
   soe.sleep( true);   // 400'000
   soe.sleep( true);   // 800'000

   BOOST_REQUIRE_EQUAL( soe.nextSleepTime(), 800000);

   soe.sleep( true);   // 1'600'000  -> max

   BOOST_REQUIRE_EQUAL( soe.nextSleepTime(), 1000000);

} // test_basics



// =====  END OF test_sleep_on_error.cpp  =====

