
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
**    Test program for the functions of the module LogFilterMaxLevel, using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/log/filter/detail/log_filter_max_level.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogFilterMaxLevelTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_msg.hpp"


using celma::log::LogLevel;
using celma::log::filter::detail::LogFilterMaxLevel;



/// Test the log filter for a maximum log level.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( max_level)
{

   LogFilterMaxLevel  maxFilter( LogLevel::warning);

   BOOST_REQUIRE( maxFilter.processLevel( LogLevel::fatal));
   BOOST_REQUIRE( maxFilter.processLevel( LogLevel::error));
   BOOST_REQUIRE( maxFilter.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !maxFilter.processLevel( LogLevel::info));
   BOOST_REQUIRE( !maxFilter.processLevel( LogLevel::debug));
   BOOST_REQUIRE( !maxFilter.processLevel( LogLevel::fullDebug));

} // max_level



/// Same test, but this time using the standard filter method passFilter().
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( max_level_pass_filter)
{

   LogFilterMaxLevel           maxFilter( LogLevel::warning);
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);


   msg.setLevel( LogLevel::fatal);
   BOOST_REQUIRE( maxFilter.passFilter( msg));

   msg.setLevel( LogLevel::error);
   BOOST_REQUIRE( maxFilter.passFilter( msg));

   msg.setLevel( LogLevel::warning);
   BOOST_REQUIRE( maxFilter.passFilter( msg));

   msg.setLevel( LogLevel::info);
   BOOST_REQUIRE( !maxFilter.passFilter( msg));

   msg.setLevel( LogLevel::debug);
   BOOST_REQUIRE( !maxFilter.passFilter( msg));

   msg.setLevel( LogLevel::fullDebug);
   BOOST_REQUIRE( !maxFilter.passFilter( msg));

} // max_level_pass_filter



// ====  END OF test_log_filter_max_level.cpp  =====
