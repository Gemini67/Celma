
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
**    Test program for the functions of the module int32_to_string.
**
--*/


// header file of module to test
#include "celma/format/detail/int32_to_string.hpp"


// OS/C lib includes
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


// Boost includes
#define BOOST_TEST_MODULE Int32ToStringTest
#include <boost/test/unit_test.hpp>


using celma::format::detail::int32toString;
using celma::format::detail::uint32toString;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.9, 28.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( int32toString( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( int32toString(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( int32toString( -1), string( "-1"));

   int32_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 64];

      ::sprintf( converted, "%d", value);
      BOOST_REQUIRE_EQUAL( int32toString( value), converted);

      ::sprintf( converted, "%d", -value);
      BOOST_REQUIRE_EQUAL( int32toString( -value), converted);

      const int32_t  longer = value + 1;

      ::sprintf( converted, "%d", longer);
      BOOST_REQUIRE_EQUAL( int32toString( longer), converted);

      ::sprintf( converted, "%d", -longer);
      BOOST_REQUIRE_EQUAL( int32toString( -longer), converted);

      // reached last value to check?
      if (longer == 1000000000)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( int32toString( INT_MIN), string( "-2147483648"));
   BOOST_REQUIRE_EQUAL( int32toString( INT_MAX), string( "2147483647"));
   BOOST_REQUIRE_EQUAL( uint32toString( UINT_MAX), string( "4294967295"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.9, 28.11.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( int32toString( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( int32toString( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( int32toString( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   int32_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 32];

      ::sprintf( converted, "%d", value);
      BOOST_REQUIRE_EQUAL( int32toString( buffer, value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%d", -value);
      BOOST_REQUIRE_EQUAL( int32toString( buffer, -value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      const int32_t  longer = value + 1;

      ::sprintf( converted, "%d", longer);
      BOOST_REQUIRE_EQUAL( int32toString( buffer, longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%d", -longer);
      BOOST_REQUIRE_EQUAL( int32toString( buffer, -longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      // reached last value to check?
      if (longer == 1000000000)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int32_t min/max
   BOOST_REQUIRE_EQUAL( int32toString( buffer, INT_MIN), 11);
   BOOST_REQUIRE( ::strcmp( buffer, "-2147483648") == 0);

   BOOST_REQUIRE_EQUAL( int32toString( buffer, INT_MAX), 10);
   BOOST_REQUIRE( ::strcmp( buffer, "2147483647") == 0);

   BOOST_REQUIRE_EQUAL( uint32toString( buffer, UINT_MAX), 10);
   BOOST_REQUIRE( ::strcmp( buffer, "4294967295") == 0);

} // end test_border_cases_buffer



// =====================  END OF test_int32_to_string.cpp  =====================

