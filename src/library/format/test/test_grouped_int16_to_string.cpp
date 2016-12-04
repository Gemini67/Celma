
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
**    Test program for the functions of the module groupedInt16toString.
**
--*/


// first include the module header to test
#include "celma/format/detail/grouped_int16_to_string.hpp"


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C/OS library includes
#include <climits>
#include <cstdio>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE GroupedInt2StringTest
#include <boost/test/unit_test.hpp>


using celma::format::detail::groupedInt16toString;
using celma::format::detail::groupedUint16toString;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( groupedInt16toString( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( groupedInt16toString(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( groupedInt16toString( -1), string( "-1"));

   // u/int16_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt16toString( SHRT_MIN), string( "-32'768"));
   BOOST_REQUIRE_EQUAL( groupedInt16toString( SHRT_MAX), string( "32'767"));
   BOOST_REQUIRE_EQUAL( groupedUint16toString( USHRT_MAX), string( "65'535"));

} // end test_border_cases



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_grouped_char)
{

   BOOST_REQUIRE_EQUAL( groupedInt16toString( 0, '.'), string( "0"));

   BOOST_REQUIRE_EQUAL( groupedInt16toString(  1, '.'), string( "1"));
   BOOST_REQUIRE_EQUAL( groupedInt16toString( -1, '.'), string( "-1"));

   // u/int16_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt16toString( SHRT_MIN, '.'), string( "-32.768"));
   BOOST_REQUIRE_EQUAL( groupedInt16toString( SHRT_MAX, '.'), string( "32.767"));
   BOOST_REQUIRE_EQUAL( groupedUint16toString( USHRT_MAX, '.'), string( "65.535"));

} // end test_border_cases_grouped_char



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int16_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, SHRT_MIN), 7);
   BOOST_REQUIRE( ::strcmp( buffer, "-32'768") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, SHRT_MAX), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "32'767") == 0);

   BOOST_REQUIRE_EQUAL( groupedUint16toString( buffer, USHRT_MAX), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "65'535") == 0);

} // end test_border_cases_buffer



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer_grouped_char)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, 0, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, 1, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, -1, '.'), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int16_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, SHRT_MIN, '.'), 7);
   BOOST_REQUIRE( ::strcmp( buffer, "-32.768") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt16toString( buffer, SHRT_MAX, '.'), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "32.767") == 0);

   BOOST_REQUIRE_EQUAL( groupedUint16toString( buffer, USHRT_MAX, '.'), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "65.535") == 0);

} // end test_border_cases_buffer_grouped_char



// =================  END OF test_grouped_int16_to_string.cpp  =================

