
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the functions of the module RangeString and the
**    corresponding iterator.
**
--*/


// module to test header file include
#include "celma/common/range_string.hpp"


// Boost includes
#define BOOST_TEST_MODULE RangeStringTest
#include <boost/test/unit_test.hpp>


using celma::common::RangeString;



/// Single value.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_one)
{

   RangeString<>  rs( "1");
   auto           it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 1);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // test_one



/// Two single values.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_two_values)
{

   RangeString<>  rs( "1,2");
   auto           it = rs.begin();


   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 1);

   ++it;
   BOOST_REQUIRE( it != rs.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( it), 2);

   ++it;
   BOOST_REQUIRE( it == rs.end());

} // test_two_values



/// Three single values.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_three_values)
{

   RangeString<>  rs( "1,2,4");
   auto           it = rs.begin();


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

} // test_three_values



/// A simple, short range.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_simple_range)
{

   RangeString<>  rs( "3-5");
   auto           it = rs.begin();


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

} // test_simple_range



/// Two simple ranges.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_two_simple_ranges)
{

   RangeString<>  rs( "3-5,11-14");
   auto           it = rs.begin();


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

} // test_simple_range



/// Single values and ranges mixed.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_simple_mix)
{

   RangeString<>  rs( "1,3-5,9,11-14");
   auto           it = rs.begin();


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

} // test_simple_mix



/// A range with a specific increment.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_increment)
{

   RangeString<>  rs( "1-10[2]");
   auto           it = rs.begin();


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

   RangeString<>  rs( "2-11[2],20-40[3]");
   auto           it = rs.begin();


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

   RangeString<>  rs( "1-10[2]{3,5},15,20-40[3]{23-35[6]},41,47");
   auto           it = rs.begin();


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



// =====  END OF test_range_string.cpp  =====

