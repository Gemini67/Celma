
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the functions of the module celma::log::filter::Filters,
**    using the Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/log/filter/filters.hpp"


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogFiltersTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_msg.hpp"


using celma::log::filter::detail::DuplicatePolicy;
using celma::log::filter::Filters;
using celma::log::LogLevel;



/// Empty filter should pass all levels.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( empty)
{

   Filters  filters;


   BOOST_REQUIRE( filters.processLevel( LogLevel::fatal));
   BOOST_REQUIRE( filters.processLevel( LogLevel::fullDebug));

} // empty



/// Check that only levels below the maximum level are accepted.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( max_level)
{

   Filters  filters;


   filters.maxLevel( LogLevel::warning);

   BOOST_REQUIRE( filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::info));

   // try to change the max_level, policy ignore: no change
   filters.maxLevel( LogLevel::error);

   // expect same result as before
   BOOST_REQUIRE( filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::info));

} // max_level



/// Check that only levels above the minimum level are accepted.
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( min_level)
{

   Filters  filters;


   filters.minLevel( LogLevel::warning);

   BOOST_REQUIRE( !filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( filters.processLevel( LogLevel::info));

   // try to change the min_level, policy ignore: no change
   filters.minLevel( LogLevel::info);

   // expect same result as before
   BOOST_REQUIRE( !filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( filters.processLevel( LogLevel::info));

} // min_level



/// Check that only the exact specified level is accepted.
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( one_level)
{

   Filters  filters;


   filters.level( LogLevel::warning);

   BOOST_REQUIRE( !filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::info));

   // try to change the filter level, policy ignore: no change
   filters.level( LogLevel::error);

   // expect same result as before
   BOOST_REQUIRE( !filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::info));

} // one_level



/// Check that only levels below the maximum level are accepted.
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( max_level_replaced)
{

   Filters  filters;


   filters.maxLevel( LogLevel::warning);

   BOOST_REQUIRE( filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::info));

   // change the filter duplicate policy so we can replace the filter
   Filters::setDuplicatePolicy( DuplicatePolicy::replace);
   // change the max_level
   filters.maxLevel( LogLevel::error);

   BOOST_REQUIRE( filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::info));

} // max_level_replaced



/// Check that only levels above the minimum level are accepted.
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( min_level_replaced)
{

   Filters  filters;


   filters.minLevel( LogLevel::warning);

   BOOST_REQUIRE( !filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( filters.processLevel( LogLevel::info));

   // change the filter duplicate policy so we can replace the filter
   Filters::setDuplicatePolicy( DuplicatePolicy::replace);
   // change the min_level
   filters.minLevel( LogLevel::info);

   BOOST_REQUIRE( !filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( filters.processLevel( LogLevel::info));

} // min_level_replaced



/// Check that only the exact specified level is accepted.
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( one_level_replaced)
{

   Filters  filters;


   filters.level( LogLevel::warning);

   BOOST_REQUIRE( !filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::info));

   // change the filter duplicate policy so we can replace the filter
   Filters::setDuplicatePolicy( DuplicatePolicy::replace);
   // change the filter level
   filters.level( LogLevel::error);

   BOOST_REQUIRE( filters.processLevel( LogLevel::error));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::warning));
   BOOST_REQUIRE( !filters.processLevel( LogLevel::info));

} // one_level_replaced



/// Check filter for one log message class.
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( filter_one_class)
{

   Filters                     filters;
   celma::log::detail::LogMsg  msg( "test_log_filers.cpp", "filter_one_class",
      __LINE__ - 1);


   filters.classes( "data");

   msg.setClass( celma::log::LogClass::data);
   BOOST_REQUIRE( filters.pass( msg));

   msg.setClass( celma::log::LogClass::communication);
   BOOST_REQUIRE( !filters.pass( msg));

} // filter_one_class



/// Check filter for multiple log message classes.
///
/// @since  x.y.z, 23.05.2019
BOOST_AUTO_TEST_CASE( filter_classes)
{

   Filters                     filters;
   celma::log::detail::LogMsg  msg( "test_log_filers.cpp", "filter_classes",
      __LINE__ - 1);


   filters.classes( "application,data");

   msg.setClass( celma::log::LogClass::data);
   BOOST_REQUIRE( filters.pass( msg));

   msg.setClass( celma::log::LogClass::communication);
   BOOST_REQUIRE( !filters.pass( msg));

   msg.setClass( celma::log::LogClass::application);
   BOOST_REQUIRE( filters.pass( msg));

} // filter_classes



// =====  END OF test_log_filters.cpp  =====

