
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
#define BOOST_TEST_MODULE GroupedInt2String32Test
#include <boost/test/unit_test.hpp>


using celma::format::grouped_int2string;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( grouped_int2string( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2string(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( -1), string( "-1"));

   // u/int32_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( INT_MIN),
                        string( "-2'147'483'648"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( INT_MIN + 1L),
                        string( "-2'147'483'647"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( INT_MAX - 1L),
                        string( "2'147'483'646"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( INT_MAX),
                        string( "2'147'483'647"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( UINT_MAX),
                        string( "4'294'967'295"));

} // end test_border_cases



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_grouped_char)
{

   BOOST_REQUIRE_EQUAL( grouped_int2string( 0, '.'), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2string(  1, '.'), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( -1, '.'), string( "-1"));

   // u/int32_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( INT_MIN, '.'),
                        string( "-2.147.483.648"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( INT_MIN + 1L, '.'),
                        string( "-2.147.483.647"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( INT_MAX - 1L, '.'),
                        string( "2.147.483.646"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( INT_MAX, '.'),
                        string( "2.147.483.647"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( UINT_MAX, '.'),
                        string( "4.294.967.295"));

} // end test_border_cases_grouped_char



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int32_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, INT_MIN), 14);
   BOOST_REQUIRE( ::strcmp( buffer, "-2'147'483'648") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, INT_MIN + 1L), 14);
   BOOST_REQUIRE( ::strcmp( buffer, "-2'147'483'647") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, INT_MAX - 1L), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "2'147'483'646") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, INT_MAX), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "2'147'483'647") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, UINT_MAX), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "4'294'967'295") == 0);

} // end test_border_cases_buffer



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer_grouped_char)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 0, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 1, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -1, '.'), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int32_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, INT_MIN, '.'), 14);
   BOOST_REQUIRE( ::strcmp( buffer, "-2.147.483.648") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, INT_MIN + 1L, '.'), 14);
   BOOST_REQUIRE( ::strcmp( buffer, "-2.147.483.647") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, INT_MAX - 1L, '.'), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "2.147.483.646") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, INT_MAX, '.'), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "2.147.483.647") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, UINT_MAX, '.'), 13);
   BOOST_REQUIRE( ::strcmp( buffer, "4.294.967.295") == 0);

} // end test_border_cases_buffer_grouped_char



// ==================  END OF test_grouped_int2string_32.cpp  ==================

