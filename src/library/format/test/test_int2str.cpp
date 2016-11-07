
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
**    Test program for the functions of the module int2str.
**
--*/


// header file of module to test
#include "celma/format/int2str.hpp"


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C/OS library includes
#include <climits>
#include <cstdio>


// Boost includes
#define BOOST_TEST_MODULE Int2StrTest
#include <boost/test/unit_test.hpp>


using celma::format::int2str;
using celma::format::uint2str;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( int2str( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( int2str(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( int2str( -1), string( "-1"));

   int64_t value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 64];

      ::sprintf( converted, "%ld", value);
      BOOST_REQUIRE_EQUAL( int2str( value), converted);

      ::sprintf( converted, "%ld", -value);
      BOOST_REQUIRE_EQUAL( int2str( -value), converted);

      const int64_t  longer = value + 1;

      ::sprintf( converted, "%ld", longer);
      BOOST_REQUIRE_EQUAL( int2str( longer), converted);

      ::sprintf( converted, "%ld", -longer);
      BOOST_REQUIRE_EQUAL( int2str( -longer), converted);

      // reached last value to check?
      if (longer == 1000000000000000000L)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( int2str( INT_MIN), string( "-2147483648"));
   BOOST_REQUIRE_EQUAL( int2str( INT_MAX), string( "2147483647"));
   BOOST_REQUIRE_EQUAL( int2str( UINT_MAX), string( "4294967295"));

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( int2str( LONG_MIN), string( "-9223372036854775808"));
   BOOST_REQUIRE_EQUAL( int2str( LONG_MIN + 1L),
                        string( "-9223372036854775807"));
   BOOST_REQUIRE_EQUAL( int2str( LONG_MAX - 1L),
                        string( "9223372036854775806"));
   BOOST_REQUIRE_EQUAL( int2str( LONG_MAX), string( "9223372036854775807"));
   BOOST_REQUIRE_EQUAL( uint2str( ULONG_MAX), string( "18446744073709551615"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( int2str( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( int2str( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( int2str( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   int64_t value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 32];

      ::sprintf( converted, "%ld", value);
      BOOST_REQUIRE_EQUAL( int2str( buffer, value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%ld", -value);
      BOOST_REQUIRE_EQUAL( int2str( buffer, -value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      const int64_t  longer = value + 1;

      ::sprintf( converted, "%ld", longer);
      BOOST_REQUIRE_EQUAL( int2str( buffer, longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%ld", -longer);
      BOOST_REQUIRE_EQUAL( int2str( buffer, -longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      // reached last value to check?
      if (longer == 1000000000000000000L)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( int2str( buffer, INT_MIN), 11);
   BOOST_REQUIRE( ::strcmp( buffer, "-2147483648") == 0);

   BOOST_REQUIRE_EQUAL( int2str( buffer, INT_MAX), 10);
   BOOST_REQUIRE( ::strcmp( buffer, "2147483647") == 0);

   BOOST_REQUIRE_EQUAL( int2str( buffer, UINT_MAX), 10);
   BOOST_REQUIRE( ::strcmp( buffer, "4294967295") == 0);

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( int2str( buffer, LONG_MIN), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "-9223372036854775808") == 0);

   BOOST_REQUIRE_EQUAL( int2str( buffer, LONG_MIN + 1L), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "-9223372036854775807") == 0);

   BOOST_REQUIRE_EQUAL( int2str( buffer, LONG_MAX - 1L), 19);
   BOOST_REQUIRE( ::strcmp( buffer, "9223372036854775806") == 0);

   BOOST_REQUIRE_EQUAL( int2str( buffer, LONG_MAX), 19);
   BOOST_REQUIRE( ::strcmp( buffer, "9223372036854775807") == 0);

   BOOST_REQUIRE_EQUAL( uint2str( buffer, ULONG_MAX), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "18446744073709551615") == 0);

} // end test_border_cases_buffer



// =========================  END OF test_int2str.cpp  =========================

