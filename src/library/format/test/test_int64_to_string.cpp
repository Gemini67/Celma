
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
**    Test program for the functions of the module int64_to_string.
**
--*/


// header file of module to test
#include "celma/format/detail/int64_to_string.hpp"


// OS/C lib includes
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


// Boost includes
#define BOOST_TEST_MODULE Int64ToStringTest
#include <boost/test/unit_test.hpp>


using celma::format::detail::int64toString;
using celma::format::detail::uint64toString;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( int64toString( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( int64toString(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( int64toString( -1), string( "-1"));

   int64_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 64];

      ::sprintf( converted, "%ld", value);
      BOOST_REQUIRE_EQUAL( int64toString( value), converted);

      ::sprintf( converted, "%ld", -value);
      BOOST_REQUIRE_EQUAL( int64toString( -value), converted);

      const int64_t  longer = value + 1;

      ::sprintf( converted, "%ld", longer);
      BOOST_REQUIRE_EQUAL( int64toString( longer), converted);

      ::sprintf( converted, "%ld", -longer);
      BOOST_REQUIRE_EQUAL( int64toString( -longer), converted);

      // reached last value to check?
      if (longer == 1000000000000000000L)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( int64toString( INT_MIN), string( "-2147483648"));
   BOOST_REQUIRE_EQUAL( int64toString( INT_MAX), string( "2147483647"));
   BOOST_REQUIRE_EQUAL( int64toString( UINT_MAX), string( "4294967295"));

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( int64toString( LONG_MIN), string( "-9223372036854775808"));
   BOOST_REQUIRE_EQUAL( int64toString( LONG_MIN + 1L),
                        string( "-9223372036854775807"));
   BOOST_REQUIRE_EQUAL( int64toString( LONG_MAX - 1L),
                        string( "9223372036854775806"));
   BOOST_REQUIRE_EQUAL( int64toString( LONG_MAX), string( "9223372036854775807"));
   BOOST_REQUIRE_EQUAL( uint64toString( ULONG_MAX), string( "18446744073709551615"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.6, 05.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( int64toString( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( int64toString( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( int64toString( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   int64_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 32];

      ::sprintf( converted, "%ld", value);
      BOOST_REQUIRE_EQUAL( int64toString( buffer, value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%ld", -value);
      BOOST_REQUIRE_EQUAL( int64toString( buffer, -value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      const int64_t  longer = value + 1;

      ::sprintf( converted, "%ld", longer);
      BOOST_REQUIRE_EQUAL( int64toString( buffer, longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%ld", -longer);
      BOOST_REQUIRE_EQUAL( int64toString( buffer, -longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      // reached last value to check?
      if (longer == 1000000000000000000L)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( int64toString( buffer, INT_MIN), 11);
   BOOST_REQUIRE( ::strcmp( buffer, "-2147483648") == 0);

   BOOST_REQUIRE_EQUAL( int64toString( buffer, INT_MAX), 10);
   BOOST_REQUIRE( ::strcmp( buffer, "2147483647") == 0);

   BOOST_REQUIRE_EQUAL( int64toString( buffer, UINT_MAX), 10);
   BOOST_REQUIRE( ::strcmp( buffer, "4294967295") == 0);

   // u/int64_t max
   BOOST_REQUIRE_EQUAL( int64toString( buffer, LONG_MIN), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "-9223372036854775808") == 0);

   BOOST_REQUIRE_EQUAL( int64toString( buffer, LONG_MIN + 1L), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "-9223372036854775807") == 0);

   BOOST_REQUIRE_EQUAL( int64toString( buffer, LONG_MAX - 1L), 19);
   BOOST_REQUIRE( ::strcmp( buffer, "9223372036854775806") == 0);

   BOOST_REQUIRE_EQUAL( int64toString( buffer, LONG_MAX), 19);
   BOOST_REQUIRE( ::strcmp( buffer, "9223372036854775807") == 0);

   BOOST_REQUIRE_EQUAL( uint64toString( buffer, ULONG_MAX), 20);
   BOOST_REQUIRE( ::strcmp( buffer, "18446744073709551615") == 0);

} // end test_border_cases_buffer



// =====================  END OF test_int64_to_string.cpp  =====================

