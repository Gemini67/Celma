
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
**    Test program for the functions of the module RangeString and the
**    corresponding iterator.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE RangeStringTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/range_string.hpp"


using namespace std;
using namespace celma;



/// Single value.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_one)
{

   common::RangeString<>                  rs( "1");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 1);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // end test_one



/// Two single values.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_two_values)
{

   common::RangeString<>                  rs( "1,2");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 1);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 2);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // end test_two_values



/// Three single values.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_three_values)
{

   common::RangeString<>                  rs( "1,2,4");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 1);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 2);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 4);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // end test_three_values



/// A simple, short range.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_simple_range)
{

   common::RangeString<>                  rs( "3-5");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 3);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 4);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 5);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // end test_simple_range



/// Two simple ranges.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_two_simple_ranges)
{

   common::RangeString<>                  rs( "3-5,11-14");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 3);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 4);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 5);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 11);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 12);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 13);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 14);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // end test_simple_range



/// Single values and ranges mixed.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_simple_mix)
{

   common::RangeString<>                  rs( "1,3-5,9,11-14");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 1);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 3);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 4);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 5);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 9);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 11);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 12);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 13);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 14);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // end test_simple_mix



/// A range with a specific increment.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_increment)
{

   common::RangeString<>                  rs( "1-10[2]");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 1);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 3);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 5);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 7);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 9);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // test_range_increment



/// Two ranges with different increments.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_two_ranges_increment)
{

   common::RangeString<>                  rs( "2-11[2],20-40[3]");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 2);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 4);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 6);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 8);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 10);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 20);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 23);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 26);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 29);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 32);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 35);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 38);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // test_two_ranges_increment



/// Ranges with increments and skipped values.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_mix_all)
{

   common::RangeString<>                  rs( "1-10[2]{3,5},15,20-40[3]{23-35[6]},41,47");
   common::RangeString<>::const_iterator  it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 1);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 7);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 9);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 15);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 20);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 26);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 32);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 38);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 41);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 47);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // test_mix_all



// =========================  END OF test_range_string.cpp  =========================

