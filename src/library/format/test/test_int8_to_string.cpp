
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
**    Test program for the functions of the module int8_to_string.
**
--*/


// header file of module to test
#include "celma/format/detail/int8_to_string.hpp"


// OS/C lib includes
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


// Boost includes
#define BOOST_TEST_MODULE Int8ToStringTest
#include <boost/test/unit_test.hpp>


using celma::format::detail::int8toString;
using celma::format::detail::uint8toString;
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

   BOOST_REQUIRE_EQUAL( int8toString( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( int8toString(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( int8toString( -1), string( "-1"));

   int8_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 64];

      ::sprintf( converted, "%hhd", value);
      BOOST_REQUIRE_EQUAL( int8toString( value), converted);

      ::sprintf( converted, "%hhd", static_cast< int8_t>( -value));
      BOOST_REQUIRE_EQUAL( int8toString( -value), converted);

      const int8_t  longer = value + 1;

      ::sprintf( converted, "%hhd", longer);
      BOOST_REQUIRE_EQUAL( int8toString( longer), converted);

      ::sprintf( converted, "%hhd", static_cast< int8_t>( -longer));
      BOOST_REQUIRE_EQUAL( int8toString( -longer), converted);

      // reached last value to check?
      if (longer == 100)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int8_t min/max
   BOOST_REQUIRE_EQUAL( int8toString( -128_b), string( "-128"));
   BOOST_REQUIRE_EQUAL( int8toString( 127_b), string( "127"));
   BOOST_REQUIRE_EQUAL( uint8toString( 255_ub), string( "255"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( int8toString( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( int8toString( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( int8toString( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   int8_t  value = 9;

   // test all cases where the resulting string requires one character more
   for (;;)
   {
      char  converted[ 32];

      ::sprintf( converted, "%hhd", value);
      BOOST_REQUIRE_EQUAL( int8toString( buffer, value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%hhd", static_cast< int8_t>( -value));
      BOOST_REQUIRE_EQUAL( int8toString( buffer, -value), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      const int8_t  longer = value + 1;

      ::sprintf( converted, "%hhd", longer);
      BOOST_REQUIRE_EQUAL( int8toString( buffer, longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      ::sprintf( converted, "%hhd", static_cast< int8_t>( -longer));
      BOOST_REQUIRE_EQUAL( int8toString( buffer, -longer), ::strlen( converted));
      BOOST_REQUIRE( ::strcmp( buffer, converted) == 0);

      // reached last value to check?
      if (longer == 100)
         break;   // for

      value = value * 10 + 9;
   } // end for

   // u/int8_t min/max
   BOOST_REQUIRE_EQUAL( int8toString( buffer, -128_b), 4);
   BOOST_REQUIRE( ::strcmp( buffer, "-128") == 0);

   BOOST_REQUIRE_EQUAL( int8toString( buffer, 127_b), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "127") == 0);

   BOOST_REQUIRE_EQUAL( uint8toString( buffer, 255_ub), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "255") == 0);

} // end test_border_cases_buffer



// =====================  END OF test_int8_to_string.cpp  =====================

