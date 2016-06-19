
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



/// Empty filter should pass all levels.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( empty)
{

   LogFilter  filters;


   BOOST_REQUIRE( filters.processLevel( celma::log::llFatal));
   BOOST_REQUIRE( filters.processLevel( celma::log::llFullDebug));

} // end empty



/// Check that only levels below the maximum level are accepted.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( max_level)
{

   LogFilter  filters;


   filters.maxLevel( celma::log::llWarning);

   BOOST_REQUIRE( filters.processLevel( celma::log::llError));
   BOOST_REQUIRE( filters.processLevel( celma::log::llWarning));
   BOOST_REQUIRE( !filters.processLevel( celma::log::llInfo));

   // try to change the max_level, policy ignore: no change
   filters.maxLevel( celma::log::llError);

   // expect same result as before
   BOOST_REQUIRE( filters.processLevel( celma::log::llError));
   BOOST_REQUIRE( filters.processLevel( celma::log::llWarning));
   BOOST_REQUIRE( !filters.processLevel( celma::log::llInfo));

} // end max_level



// =======================  END OF test_log_filter.cpp  =======================
