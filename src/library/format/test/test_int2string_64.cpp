
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
#define BOOST_TEST_MODULE Int2String64Test
#include <boost/test/unit_test.hpp>


using celma::format::int2string;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.9, 28.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( int2string( 0L), string( "0"));

   BOOST_REQUIRE_EQUAL( int2string(  1L), string( "1"));
   BOOST_REQUIRE_EQUAL( int2string( -1L), string( "-1"));

   int64_t value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 64];

      ::sprintf( converted, "%ld", value);
      BOOST_REQUIRE_EQUAL( int2string( value), converted);

      ::sprintf( converted, "%ld", -value);
      BOOST_REQUIRE_EQUAL( int2string( -value), converted);

      const int64_t  longer = value + 1;

      ::sprintf( converted, "%ld", longer);
      BOOST_REQUIRE_EQUAL( int2string( longer), converted);

      ::sprintf( converted, "%ld", -longer);
      BOOST_REQUIRE_EQUAL( int2string( -longer), converted);

      // reached last value to check?
      if (longer == 1000000000000000000L)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( int2string( LONG_MIN), string( "-9223372036854775808"));
   BOOST_REQUIRE_EQUAL( int2string( LONG_MIN + 1L),
                        string( "-9223372036854775807"));
   BOOST_REQUIRE_EQUAL( int2string( LONG_MAX - 1L),
                        string( "9223372036854775806"));
   BOOST_REQUIRE_EQUAL( int2string( LONG_MAX), string( "9223372036854775807"));
   BOOST_REQUIRE_EQUAL( int2string( ULONG_MAX), string( "18446744073709551615"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( int2string( buffer, 0L), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, 1L), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, -1L), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   int64_t value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 32];

      ::sprintf( converted, "%ld", value);
      BOOST_REQUIRE_EQUAL( int2string( buffer, value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%ld", -value);
      BOOST_REQUIRE_EQUAL( int2string( buffer, -value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      const int64_t  longer = value + 1;

      ::sprintf( converted, "%ld", longer);
      BOOST_REQUIRE_EQUAL( int2string( buffer, longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%ld", -longer);
      BOOST_REQUIRE_EQUAL( int2string( buffer, -longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      // reached last value to check?
      if (longer == 1000000000000000000L)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( int2string( buffer, LONG_MIN), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "-9223372036854775808") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, LONG_MIN + 1L), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "-9223372036854775807") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, LONG_MAX - 1L), 19);
   BOOST_REQUIRE( ::strcmp( buffer, "9223372036854775806") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, LONG_MAX), 19);
   BOOST_REQUIRE( ::strcmp( buffer, "9223372036854775807") == 0);

   BOOST_REQUIRE_EQUAL( int2string( buffer, ULONG_MAX), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "18446744073709551615") == 0);

} // end test_border_cases_buffer



// ======================  END OF test_int2string_64.cpp  ======================

