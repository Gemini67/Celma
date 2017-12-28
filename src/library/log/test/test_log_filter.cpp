
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
**    Test program for the functions of the module LogFilter, using the
**    Boost.Test framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogFilterTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_filter.hpp"


using celma::log::detail::LogFilter;
using celma::log::LogLevel;



/// Empty filter should pass all levels.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( empty)
{

   LogFilter  filters;


   BOOST_REQUIRE( filters.processLevel( LogLevel::fatal));
   BOOST_REQUIRE( filters.processLevel( LogLevel::fullDebug));

} // end empty



/// Check that only levels below the maximum level are accepted.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( max_level)
{

   LogFilter  filters;


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

} // end max_level



// =======================  END OF test_log_filter.cpp  =======================
