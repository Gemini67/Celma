
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


inline std::uint8_t operator "" _b( unsigned long long value)
{
    return static_cast< std::uint8_t>( value);
}


inline std::uint8_t operator "" _ub( unsigned long long value)
{
    return static_cast< std::uint8_t>( value);
}


} // namespace



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( grouped_int2string( 0_ub), string( "0"));

   BOOST_REQUIRE_EQUAL( grouped_int2string(  1_b), string( "1"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( -1_b), string( "-1"));

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( -128_b), string( "-128"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( -127_b), string( "-127"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( 126_b), string( "126"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( 127_b), string( "127"));
   BOOST_REQUIRE_EQUAL( grouped_int2string( 255_ub), string( "255"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 0_b), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 1_ub), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -1_ub), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int8_t max
   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -128_b), 4);
   BOOST_REQUIRE( ::strcmp( buffer, "-128") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, -127_b), 4);
   BOOST_REQUIRE( ::strcmp( buffer, "-127") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 126_b), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "126") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 127_b), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "127") == 0);

   BOOST_REQUIRE_EQUAL( grouped_int2string( buffer, 255_ub), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "255") == 0);

} // end test_border_cases_buffer



// ==================  END OF test_grouped_int2string_8.cpp  ==================

