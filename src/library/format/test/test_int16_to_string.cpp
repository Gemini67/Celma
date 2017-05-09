
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
**    Test program for the functions of the module int16_to_string.
**
--*/


// header file of module to test
#include "celma/format/detail/int16_to_string.hpp"


// OS/C lib includes
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


// Boost includes
#define BOOST_TEST_MODULE Int16ToStringTest
#include <boost/test/unit_test.hpp>


using celma::format::detail::int16toString;
using celma::format::detail::uint16toString;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.9, 29.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( int16toString( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( int16toString(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( int16toString( -1), string( "-1"));

   int16_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 64];

      ::sprintf( converted, "%hd", value);
      BOOST_REQUIRE_EQUAL( int16toString( value), converted);

      ::sprintf( converted, "%d", -value);
      BOOST_REQUIRE_EQUAL( int16toString( -value), converted);

      const int16_t  longer = value + 1;

      ::sprintf( converted, "%hd", longer);
      BOOST_REQUIRE_EQUAL( int16toString( longer), converted);

      ::sprintf( converted, "%d", -longer);
      BOOST_REQUIRE_EQUAL( int16toString( -longer), converted);

      // reached last value to check?
      if (longer == 10000)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int16_t min/max
   BOOST_REQUIRE_EQUAL( int16toString( SHRT_MIN), string( "-32768"));
   BOOST_REQUIRE_EQUAL( int16toString( SHRT_MAX), string( "32767"));
   BOOST_REQUIRE_EQUAL( uint16toString( USHRT_MAX), string( "65535"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.9, 29.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( int16toString( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( int16toString( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( int16toString( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   int16_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 32];

      ::sprintf( converted, "%hd", value);
      BOOST_REQUIRE_EQUAL( int16toString( buffer, value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%d", -value);
      BOOST_REQUIRE_EQUAL( int16toString( buffer, -value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      const int16_t  longer = value + 1;

      ::sprintf( converted, "%hd", longer);
      BOOST_REQUIRE_EQUAL( int16toString( buffer, longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%d", -longer);
      BOOST_REQUIRE_EQUAL( int16toString( buffer, -longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      // reached last value to check?
      if (longer == 10000)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int16_t min/max
   BOOST_REQUIRE_EQUAL( int16toString( buffer, SHRT_MIN), 6);
   BOOST_REQUIRE( ::strcmp( buffer, "-32768") == 0);

   BOOST_REQUIRE_EQUAL( int16toString( buffer, SHRT_MAX), 5);
   BOOST_REQUIRE( ::strcmp( buffer, "32767") == 0);

   BOOST_REQUIRE_EQUAL( uint16toString( buffer, USHRT_MAX), 5);
   BOOST_REQUIRE( ::strcmp( buffer, "65535") == 0);

} // end test_border_cases_buffer



// =====================  END OF test_int16_to_string.cpp  =====================

