
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
**    Test program for the functions of the module groupedInt32toString.
**
--*/


// first include the module header to test
#include "celma/format/detail/grouped_int32_to_string.hpp"


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


using celma::format::detail::groupedInt32toString;
using celma::format::detail::groupedUint32toString;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( groupedInt32toString( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( groupedInt32toString(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( groupedInt32toString( -1), string( "-1"));

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt32toString( INT_MIN), string( "-2'147'483'648"));
   BOOST_REQUIRE_EQUAL( groupedInt32toString( INT_MAX), string( "2'147'483'647"));
   BOOST_REQUIRE_EQUAL( groupedUint32toString( UINT_MAX), string( "4'294'967'295"));

} // end test_border_cases



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_grouped_char)
{

   BOOST_REQUIRE_EQUAL( groupedInt32toString( 0, '.'), string( "0"));

   BOOST_REQUIRE_EQUAL( groupedInt32toString(  1, '.'), string( "1"));
   BOOST_REQUIRE_EQUAL( groupedInt32toString( -1, '.'), string( "-1"));

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt32toString( INT_MIN, '.'),
                        string( "-2.147.483.648"));
   BOOST_REQUIRE_EQUAL( groupedInt32toString( INT_MAX, '.'),
                        string( "2.147.483.647"));
   BOOST_REQUIRE_EQUAL( groupedUint32toString( UINT_MAX, '.'),
                        string( "4.294.967.295"));

} // end test_border_cases_grouped_char



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, INT_MIN), 14);
   BOOST_REQUIRE( ::strcmp( buffer, "-2'147'483'648") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, INT_MAX), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "2'147'483'647") == 0);

   BOOST_REQUIRE_EQUAL( groupedUint32toString( buffer, UINT_MAX), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "4'294'967'295") == 0);

} // end test_border_cases_buffer



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer_grouped_char)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, 0, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, 1, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, -1, '.'), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, INT_MIN, '.'), 14);
   BOOST_REQUIRE( ::strcmp( buffer, "-2.147.483.648") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt32toString( buffer, INT_MAX, '.'), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "2.147.483.647") == 0);

   BOOST_REQUIRE_EQUAL( groupedUint32toString( buffer, UINT_MAX, '.'), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "4.294.967.295") == 0);

} // end test_border_cases_buffer_grouped_char



// =================  END OF test_grouped_int32_to_string.cpp  =================

