
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
**    Test program for the functions of the module LogFilterMinLevel, using the
**    Boost.Test framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogFilterMinLevelTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_filter_min_level.hpp"



/// Test the log filter for a minimum log level.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( min_level)
{

   celma::log::detail::LogFilterMinLevel  minFilter( celma::log::llWarning);

   BOOST_REQUIRE( !minFilter.processLevel( celma::log::llFatal));
   BOOST_REQUIRE( !minFilter.processLevel( celma::log::llError));
   BOOST_REQUIRE( minFilter.processLevel( celma::log::llWarning));
   BOOST_REQUIRE( minFilter.processLevel( celma::log::llInfo));
   BOOST_REQUIRE( minFilter.processLevel( celma::log::llDebug));
   BOOST_REQUIRE( minFilter.processLevel( celma::log::llFullDebug));

} // end min_level



/// Same test, but this time using the standard filter method passFilter().
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( min_level_pass_filter)
{

   celma::log::detail::LogFilterMinLevel  minFilter( celma::log::llWarning);
   celma::log::detail::LogMsg             msg( LOG_MSG_OBJECT_INIT);


   msg.setLevel( celma::log::llFatal);
   BOOST_REQUIRE( !minFilter.passFilter( msg));

   msg.setLevel( celma::log::llError);
   BOOST_REQUIRE( !minFilter.passFilter( msg));

   msg.setLevel( celma::log::llWarning);
   BOOST_REQUIRE( minFilter.passFilter( msg));

   msg.setLevel( celma::log::llInfo);
   BOOST_REQUIRE( minFilter.passFilter( msg));

   msg.setLevel( celma::log::llDebug);
   BOOST_REQUIRE( minFilter.passFilter( msg));

   msg.setLevel( celma::log::llFullDebug);
   BOOST_REQUIRE( minFilter.passFilter( msg));

} // end min_level_pass_filter



// ==================  END OF test_log_filter_min_level.cpp  ==================
