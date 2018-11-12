
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
**    Test program for the functions of the module celma::log::filter::Filters,
**    using the Boost.Test framework.
**
--*/


// project includes
#include "celma/log/filter/filters.hpp"


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogFiltersTest
#include <boost/test/unit_test.hpp>


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



// =====  END OF test_log_filters.cpp  =====
