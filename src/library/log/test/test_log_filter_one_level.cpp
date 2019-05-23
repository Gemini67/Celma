
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the functions of the module LogFilterLevel, using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/log/filter/detail/log_filter_level.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogFilterLevelTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_msg.hpp"


using celma::log::LogLevel;
using celma::log::filter::detail::LogFilterLevel;



/// Test the log filter for one specific log level.
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( one_level)
{

   LogFilterLevel  oneFilter( LogLevel::warning);

   BOOST_REQUIRE( !oneFilter.processLevel( LogLevel::fatal));
   BOOST_REQUIRE( !oneFilter.processLevel( LogLevel::error));
   BOOST_REQUIRE( oneFilter.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !oneFilter.processLevel( LogLevel::info));
   BOOST_REQUIRE( !oneFilter.processLevel( LogLevel::debug));
   BOOST_REQUIRE( !oneFilter.processLevel( LogLevel::fullDebug));

} // one_level



/// Same test, but this time using the standard filter method passFilter().
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( one_level_pass_filter)
{

   LogFilterLevel              oneFilter( LogLevel::warning);
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);


   msg.setLevel( LogLevel::fatal);
   BOOST_REQUIRE( !oneFilter.passFilter( msg));

   msg.setLevel( LogLevel::error);
   BOOST_REQUIRE( !oneFilter.passFilter( msg));

   msg.setLevel( LogLevel::warning);
   BOOST_REQUIRE( oneFilter.passFilter( msg));

   msg.setLevel( LogLevel::info);
   BOOST_REQUIRE( !oneFilter.passFilter( msg));

   msg.setLevel( LogLevel::debug);
   BOOST_REQUIRE( !oneFilter.passFilter( msg));

   msg.setLevel( LogLevel::fullDebug);
   BOOST_REQUIRE( !oneFilter.passFilter( msg));

} // one_level_pass_filter



// ====  END OF test_log_filter_one_level.cpp  =====

