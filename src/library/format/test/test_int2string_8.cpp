
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
**    Test program for the functions of the module int2string.
**
--*/


// header file of module to test
#include "celma/format/int2string.hpp"


// OS/C lib includes
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


// Boost includes
#define BOOST_TEST_MODULE Int2ToString8Test
#include <boost/test/unit_test.hpp>


using celma::format::int2string;
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
/// @since  0.9, 29.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( int2string( static_cast< uint8_t>(  0)), string( "0"));

   BOOST_REQUIRE_EQUAL( int2string( static_cast< uint8_t>(  1)), string( "1"));
   BOOST_REQUIRE_EQUAL( int2string( static_cast< int8_t>(  -1)), string( "-1"));

   int8_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 64];

      ::sprintf( converted, "%hhd", value);
      BOOST_REQUIRE_EQUAL( int2string( value), converted);

      ::sprintf( converted, "%hhd", static_cast< int8_t>( -value));
      BOOST_REQUIRE_EQUAL( int2string( -value), converted);

      const int8_t  longer = value + 1;

      ::sprintf( converted, "%hhd", longer);
      BOOST_REQUIRE_EQUAL( int2string( longer), converted);

      ::sprintf( converted, "%hhd", static_cast< int8_t>( -longer));
      BOOST_REQUIRE_EQUAL( int2string( -longer), converted);

      // reached last value to check?
      if (longer == 100)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int8_t min/max
   BOOST_REQUIRE_EQUAL( int2string( -128_b), string( "-128"));
   BOOST_REQUIRE_EQUAL( int2string( 127_b), string( "127"));
   BOOST_REQUIRE_EQUAL( int2string( 255_ub), string( "255"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.9, 29.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( int2string( buffer, static_cast< uint8_t>( 0)), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, static_cast< uint8_t>( 1)), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, static_cast< int8_t>( -1)), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   int8_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 32];

      ::sprintf( converted, "%hhd", value);
      BOOST_REQUIRE_EQUAL( int2string( buffer, value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%hhd", static_cast< int8_t>( -value));
      BOOST_REQUIRE_EQUAL( int2string( buffer, -value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      const int8_t  longer = value + 1;

      ::sprintf( converted, "%hhd", longer);
      BOOST_REQUIRE_EQUAL( int2string( buffer, longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%hhd", static_cast< int8_t>( -longer));
      BOOST_REQUIRE_EQUAL( int2string( buffer, -longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      // reached last value to check?
      if (longer == 100)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int8_t min/max
   BOOST_REQUIRE_EQUAL( int2string( buffer, -128_b), 4);
   BOOST_REQUIRE( ::strcmp( buffer, "-128") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, 127_b), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "127") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, 255_ub), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "255") == 0);

} // end test_border_cases_buffer



// ======================  END OF test_int2string_8.cpp  ======================

