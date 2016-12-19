
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
#define BOOST_TEST_MODULE Int2ToString16Test
#include <boost/test/unit_test.hpp>


using celma::format::int2string;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.9, 29.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( int2string( static_cast< uint16_t>(  0)), string( "0"));

   BOOST_REQUIRE_EQUAL( int2string( static_cast< uint16_t>(  1)), string( "1"));
   BOOST_REQUIRE_EQUAL( int2string( static_cast< int16_t>(  -1)), string( "-1"));

   int16_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 64];

      ::sprintf( converted, "%hd", value);
      BOOST_REQUIRE_EQUAL( int2string( value), converted);

      ::sprintf( converted, "%hd", static_cast< int16_t>( -value));
      BOOST_REQUIRE_EQUAL( int2string( -value), converted);

      const int16_t  longer = value + 1;

      ::sprintf( converted, "%hd", longer);
      BOOST_REQUIRE_EQUAL( int2string( longer), converted);

      ::sprintf( converted, "%hd", static_cast< int16_t>( -longer));
      BOOST_REQUIRE_EQUAL( int2string( -longer), converted);

      // reached last value to check?
      if (longer == 10000)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int16_t min/max
   BOOST_REQUIRE_EQUAL( int2string( SHRT_MIN), string( "-32768"));
   BOOST_REQUIRE_EQUAL( int2string( SHRT_MAX), string( "32767"));
   BOOST_REQUIRE_EQUAL( int2string( USHRT_MAX), string( "65535"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.9, 29.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( int2string( buffer, static_cast< uint16_t>( 0)), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, static_cast< uint16_t>( 1)), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, static_cast< int16_t>( -1)), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   int16_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 32];

      ::sprintf( converted, "%hd", value);
      BOOST_REQUIRE_EQUAL( int2string( buffer, value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%hd", static_cast< int16_t>( -value));
      BOOST_REQUIRE_EQUAL( int2string( buffer, -value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      const int16_t  longer = value + 1;

      ::sprintf( converted, "%hd", longer);
      BOOST_REQUIRE_EQUAL( int2string( buffer, longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%hd", static_cast< int16_t>( -longer));
      BOOST_REQUIRE_EQUAL( int2string( buffer, -longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      // reached last value to check?
      if (longer == 10000)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int16_t min/max
   BOOST_REQUIRE_EQUAL( int2string( buffer, SHRT_MIN), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "-32768") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, SHRT_MAX), 5);
   BOOST_REQUIRE( ::strcmp( buffer, "32767") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, USHRT_MAX), 5);
   BOOST_REQUIRE( ::strcmp( buffer, "65535") == 0);

} // end test_border_cases_buffer



// ======================  END OF test_int2string_16.cpp  ======================

