
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the functions of the module LogFilterMinLevel, using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/log/filter/detail/log_filter_min_level.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogFilterMinLevelTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_msg.hpp"


using celma::log::filter::detail::LogFilterMinLevel;
using celma::log::LogLevel;



/// Test the log filter for a minimum log level.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( min_level)
{

   LogFilterMinLevel  minFilter( LogLevel::warning);


   BOOST_REQUIRE( !minFilter.processLevel( LogLevel::fatal));
   BOOST_REQUIRE( !minFilter.processLevel( LogLevel::error));
   BOOST_REQUIRE( minFilter.processLevel( LogLevel::warning));
   BOOST_REQUIRE( minFilter.processLevel( LogLevel::info));
   BOOST_REQUIRE( minFilter.processLevel( LogLevel::debug));
   BOOST_REQUIRE( minFilter.processLevel( LogLevel::fullDebug));

} // min_level



/// Same test, but this time using the standard filter method passFilter().
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( min_level_pass_filter)
{

   LogFilterMinLevel           minFilter( LogLevel::warning);
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);


   msg.setLevel( LogLevel::fatal);
   BOOST_REQUIRE( !minFilter.passFilter( msg));

   msg.setLevel( LogLevel::error);
   BOOST_REQUIRE( !minFilter.passFilter( msg));

   msg.setLevel( LogLevel::warning);
   BOOST_REQUIRE( minFilter.passFilter( msg));

   msg.setLevel( LogLevel::info);
   BOOST_REQUIRE( minFilter.passFilter( msg));

   msg.setLevel( LogLevel::debug);
   BOOST_REQUIRE( minFilter.passFilter( msg));

   msg.setLevel( LogLevel::fullDebug);
   BOOST_REQUIRE( minFilter.passFilter( msg));

} // min_level_pass_filter



// =====  END OF test_log_filter_min_level.cpp  =====
