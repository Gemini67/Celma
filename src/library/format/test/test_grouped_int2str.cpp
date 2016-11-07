
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
**    Test program for the functions of the module grouped_int2str.
**
--*/


// first include the module header to test
#include "celma/format/grouped_int2str.hpp"


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C/OS library includes
#include <climits>
#include <cstdio>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE Int2StrTest
#include <boost/test/unit_test.hpp>


using celma::format::grouped_int2str;
using celma::format::grouped_uint2str;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( grouped_int2str( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2str(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( -1), string( "-1"));

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( grouped_int2str( INT_MIN), string( "-2'147'483'648"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( INT_MAX), string( "2'147'483'647"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( UINT_MAX), string( "4'294'967'295"));

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2str( LONG_MIN),
                        string( "-9'223'372'036'854'775'808"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( LONG_MIN + 1L),
                        string( "-9'223'372'036'854'775'807"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( LONG_MAX - 1L),
                        string( "9'223'372'036'854'775'806"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( LONG_MAX),
                        string( "9'223'372'036'854'775'807"));
   BOOST_REQUIRE_EQUAL( grouped_uint2str( ULONG_MAX),
                        string( "18'446'744'073'709'551'615"));

} // end test_border_cases



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_grouped_char)
{

   BOOST_REQUIRE_EQUAL( grouped_int2str( 0, '.'), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2str(  1, '.'), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( -1, '.'), string( "-1"));

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( grouped_int2str( INT_MIN, '.'),
                        string( "-2.147.483.648"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( INT_MAX, '.'),
                        string( "2.147.483.647"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( UINT_MAX, '.'),
                        string( "4.294.967.295"));

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2str( LONG_MIN, '.'),
                        string( "-9.223.372.036.854.775.808"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( LONG_MIN + 1L, '.'),
                        string( "-9.223.372.036.854.775.807"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( LONG_MAX - 1L, '.'),
                        string( "9.223.372.036.854.775.806"));
   BOOST_REQUIRE_EQUAL( grouped_int2str( LONG_MAX, '.'),
                        string( "9.223.372.036.854.775.807"));
   BOOST_REQUIRE_EQUAL( grouped_uint2str( ULONG_MAX, '.'),
                        string( "18.446.744.073.709.551.615"));

} // end test_border_cases_grouped_char



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, INT_MIN), 14);
   BOOST_REQUIRE( ::strcmp( buffer, "-2'147'483'648") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, INT_MAX), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "2'147'483'647") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, UINT_MAX), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "4'294'967'295") == 0);

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, LONG_MIN), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "-9'223'372'036'854'775'808") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, LONG_MIN + 1L), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "-9'223'372'036'854'775'807") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, LONG_MAX - 1L), 25);
   BOOST_REQUIRE( ::strcmp( buffer, "9'223'372'036'854'775'806") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, LONG_MAX), 25);
   BOOST_REQUIRE( ::strcmp( buffer, "9'223'372'036'854'775'807") == 0);

   BOOST_REQUIRE_EQUAL( grouped_uint2str( buffer, ULONG_MAX), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "18'446'744'073'709'551'615") == 0);

} // end test_border_cases_buffer



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer_grouped_char)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, 0, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, 1, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, -1, '.'), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, INT_MIN, '.'), 14);
   BOOST_REQUIRE( ::strcmp( buffer, "-2.147.483.648") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, INT_MAX, '.'), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "2.147.483.647") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, UINT_MAX, '.'), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "4.294.967.295") == 0);

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, LONG_MIN, '.'), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "-9.223.372.036.854.775.808") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, LONG_MIN + 1L, '.'), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "-9.223.372.036.854.775.807") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, LONG_MAX - 1L, '.'), 25);
   BOOST_REQUIRE( ::strcmp( buffer, "9.223.372.036.854.775.806") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2str( buffer, LONG_MAX, '.'), 25);
   BOOST_REQUIRE( ::strcmp( buffer, "9.223.372.036.854.775.807") == 0);

   BOOST_REQUIRE_EQUAL( grouped_uint2str( buffer, ULONG_MAX, '.'), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "18.446.744.073.709.551.615") == 0);

} // end test_border_cases_buffer_grouped_char



// =====================  END OF test_grouped_int2str.cpp  =====================

