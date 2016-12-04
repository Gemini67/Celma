
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


namespace {


inline std::uint16_t operator "" _s( unsigned long long value)
{
    return static_cast< std::uint16_t>( value);
}


inline std::uint16_t operator "" _us( unsigned long long value)
{
    return static_cast< std::uint16_t>( value);
}


} // namespace



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( grouped_int2string( 0_us), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2string(  1_s), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( -1_s), string( "-1"));

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( SHRT_MIN), string( "-32'768"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( SHRT_MIN + 1L), string( "-32'767"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( SHRT_MAX - 1L), string( "32'766"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( SHRT_MAX), string( "32'767"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( USHRT_MAX), string( "65'535"));

} // end test_border_cases



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_grouped_char)
{

   BOOST_REQUIRE_EQUAL( grouped_int2string( 0_s, '.'), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2string(  1_us, '.'), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( -1_us, '.'), string( "-1"));

   // u/int16_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( SHRT_MIN, '.'), string( "-32.768"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( SHRT_MIN + 1L, '.'), string( "-32.767"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( SHRT_MAX - 1L, '.'), string( "32.766"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( SHRT_MAX, '.'), string( "32.767"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( USHRT_MAX, '.'), string( "65.535"));

} // end test_border_cases_grouped_char



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 0_s), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 1_us), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -1_us), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int16_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, SHRT_MIN), 7);
   BOOST_REQUIRE( ::strcmp( buffer, "-32'768") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, SHRT_MIN + 1L), 7);
   BOOST_REQUIRE( ::strcmp( buffer, "-32'767") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, SHRT_MAX - 1L), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "32'766") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, SHRT_MAX), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "32'767") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, USHRT_MAX), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "65'535") == 0);

} // end test_border_cases_buffer



/// Test that the conversion yields the correct results with a different
/// grouping character.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer_grouped_char)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 0_us, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 1_s, '.'), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -1_s, '.'), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int16_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, SHRT_MIN, '.'), 7);
   BOOST_REQUIRE( ::strcmp( buffer, "-32.768") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, SHRT_MIN + 1L, '.'), 7);
   BOOST_REQUIRE( ::strcmp( buffer, "-32.767") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, SHRT_MAX - 1L, '.'), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "32.766") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, SHRT_MAX, '.'), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "32.767") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, USHRT_MAX, '.'), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "65.535") == 0);

} // end test_border_cases_buffer_grouped_char



// ==================  END OF test_grouped_int2string_16.cpp  ==================

