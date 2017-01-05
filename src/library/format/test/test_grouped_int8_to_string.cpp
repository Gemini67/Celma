
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
**    Test program for the functions of the module groupedInt8toString.
**
--*/


// first include the module header to test
#include "celma/format/detail/grouped_int8_to_string.hpp"


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C/OS library includes
#include <climits>
#include <cstdio>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE GroupedInt2StringTest
#include <boost/test/unit_test.hpp>


using celma::format::detail::groupedInt8toString;
using celma::format::detail::groupedUint8toString;
using std::string;



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases)
{

   BOOST_REQUIRE_EQUAL( groupedInt8toString( 0), string( "0"));

   BOOST_REQUIRE_EQUAL( groupedInt8toString(  1), string( "1"));
   BOOST_REQUIRE_EQUAL( groupedInt8toString( -1), string( "-1"));

   // u/int8_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt8toString( -128), string( "-128"));
   BOOST_REQUIRE_EQUAL( groupedInt8toString( 127), string( "127"));
   BOOST_REQUIRE_EQUAL( groupedUint8toString( 255), string( "255"));

} // end test_border_cases



/// Test that the conversion yields the correct results.
/// @since  0.9, 04.12.2016
BOOST_AUTO_TEST_CASE( test_border_cases_buffer)
{

   char  buffer[ 32];


   BOOST_REQUIRE_EQUAL( groupedInt8toString( buffer, 0), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "0") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt8toString( buffer, 1), 1);
   BOOST_REQUIRE( ::strcmp( buffer, "1") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt8toString( buffer, -1), 2);
   BOOST_REQUIRE( ::strcmp( buffer, "-1") == 0);

   // u/int8_t min/max
   BOOST_REQUIRE_EQUAL( groupedInt8toString( buffer, -128), 4);
   BOOST_REQUIRE( ::strcmp( buffer, "-128") == 0);

   BOOST_REQUIRE_EQUAL( groupedInt8toString( buffer, 127), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "127") == 0);

   BOOST_REQUIRE_EQUAL( groupedUint8toString( buffer, 255), 3);
   BOOST_REQUIRE( ::strcmp( buffer, "255") == 0);

} // end test_border_cases_buffer



// =================  END OF test_grouped_int8_to_string.cpp  =================

