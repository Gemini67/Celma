
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
**    Test program for the functions of the module grouped_int2string.
**
--*/


// first include the module header to test
#include "celma/format/grouped_int2string.hpp"


// C/OS library includes
#include <climits>


// Boost includes
#define BOOST_TEST_MODULE GroupedInt2String64Test
#include <boost/test/unit_test.hpp>


using celma::format::grouped_int2string;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.9, 28.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( grouped_int2string( 0L), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2string(  1L), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( -1L), string( "-1"));

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( LONG_MIN),
                        string( "-9'223'372'036'854'775'808"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( LONG_MIN + 1L),
                        string( "-9'223'372'036'854'775'807"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( LONG_MAX - 1L),
                        string( "9'223'372'036'854'775'806"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( LONG_MAX),
                        string( "9'223'372'036'854'775'807"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( ULONG_MAX),
                        string( "18'446'744'073'709'551'615"));

} // end test_border_cases



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.9, 28.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_grouped_char)
{

   BOOST_REQUIRE_EQUAL( grouped_int2string( 0L, '.'), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2string(  1L, '.'), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( -1L, '.'), string( "-1"));

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( LONG_MIN, '.'),
                        string( "-9.223.372.036.854.775.808"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( LONG_MIN + 1L, '.'),
                        string( "-9.223.372.036.854.775.807"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( LONG_MAX - 1L, '.'),
                        string( "9.223.372.036.854.775.806"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( LONG_MAX, '.'),
                        string( "9.223.372.036.854.775.807"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( ULONG_MAX, '.'),
                        string( "18.446.744.073.709.551.615"));

} // end test_border_cases_grouped_char



/// Test that the conversion yields the correct results.
/// @since  0.9, 28.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 0L), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 1L), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -1L), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, LONG_MIN), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "-9'223'372'036'854'775'808") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, LONG_MIN + 1L), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "-9'223'372'036'854'775'807") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, LONG_MAX - 1L), 25);
   BOOST_REQUIRE( ::strcmp( buffer, "9'223'372'036'854'775'806") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, LONG_MAX), 25);
   BOOST_REQUIRE( ::strcmp( buffer, "9'223'372'036'854'775'807") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, ULONG_MAX), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "18'446'744'073'709'551'615") == 0);

} // end test_border_cases_buffer



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.9, 28.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer_grouped_char)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 0L, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 1L, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -1L, '.'), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, LONG_MIN, '.'), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "-9.223.372.036.854.775.808") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, LONG_MIN + 1L, '.'), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "-9.223.372.036.854.775.807") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, LONG_MAX - 1L, '.'), 25);
   BOOST_REQUIRE( ::strcmp( buffer, "9.223.372.036.854.775.806") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, LONG_MAX, '.'), 25);
   BOOST_REQUIRE( ::strcmp( buffer, "9.223.372.036.854.775.807") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, ULONG_MAX, '.'), 26);
   BOOST_REQUIRE( ::strcmp( buffer, "18.446.744.073.709.551.615") == 0);

} // end test_border_cases_buffer_grouped_char



// ==================  END OF test_grouped_int2string_64.cpp  ==================

