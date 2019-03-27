
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test header file include
#include "celma/format/range_value_string.hpp"


// C++ Standard Library includes
#include <set>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE RangeValueStringTest
#include <boost/test/unit_test.hpp>


using celma::format::rangeValueString;



/// Container contains only single values.
/// @since  1.21.0, 27.03.2019
BOOST_AUTO_TEST_CASE( single_values)
{

   std::vector< int>  vec;


   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "");

   vec.push_back( 1);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "1");

   vec.push_back( 11);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "1, 11");

   vec.push_back( 111);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "1, 11, 111");

} // single_values



/// Container contains only a range.
/// @since  1.21.0, 27.03.2019
BOOST_AUTO_TEST_CASE( single_range)
{

   std::vector< int>  vec;


   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "");

   vec.push_back( 11);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "11");

   vec.push_back( 12);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "11, 12");

   vec.push_back( 13);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "11-13");

   vec.push_back( 14);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "11-14");

   vec.push_back( 15);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "11-15");

} // single_range



/// A range that is first followed by single values and later by another range.
/// @since  1.21.0, 27.03.2019
BOOST_AUTO_TEST_CASE( range_value_range)
{

   std::vector< int>  vec;


   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "");

   vec.push_back( 25);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25");

   vec.push_back( 26);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25, 26");

   vec.push_back( 27);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25-27");

   vec.push_back( 28);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25-28");

   vec.push_back( 30);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25-28, 30");

   vec.push_back( 31);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25-28, 30, 31");

   vec.push_back( 32);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25-28, 30-32");

} // range_value_range



/// Single value(s) followed by a range.
/// @since  1.21.0, 27.03.2019
BOOST_AUTO_TEST_CASE( value_range)
{

   std::vector< int>  vec;


   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "");

   vec.push_back( 25);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25");

   vec.push_back( 26);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25, 26");

   vec.push_back( 28);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25, 26, 28");

   vec.push_back( 29);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25, 26, 28, 29");

   vec.push_back( 30);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25, 26, 28-30");

   vec.push_back( 31);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec.begin(), vec.end()), "25, 26, 28-31");

   vec.push_back( 32);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec), "25, 26, 28-32");

} // value_range



/// Some tests with another separator for single values.
/// @since  1.21.0, 27.03.2019
BOOST_AUTO_TEST_CASE( separator)
{

   std::vector< int>  vec;


   BOOST_REQUIRE_EQUAL( rangeValueString( vec, ","), "");

   vec.push_back( 1);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec.begin(), vec.end(), ","), "1");

   vec.push_back( 11);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec, ","), "1,11");

   vec.push_back( 111);

   BOOST_REQUIRE_EQUAL( rangeValueString( vec, "."), "1.11.111");

} // separator



/// Test with another container: set.
/// @since  1.21.0, 27.03.2019
BOOST_AUTO_TEST_CASE( set_container)
{

   std::set< uint16_t>  data_set;


   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "");

   data_set.insert( 25);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25");

   data_set.insert( 26);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25, 26");

   data_set.insert( 28);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25, 26, 28");

   data_set.insert( 29);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25, 26, 28, 29");

   data_set.insert( 30);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25, 26, 28-30");

   data_set.insert( 31);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set.begin(), data_set.end()), "25, 26, 28-31");

   data_set.insert( 32);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25, 26, 28-32");

   data_set.insert( 50);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25, 26, 28-32, 50");

   data_set.insert( 51);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25, 26, 28-32, 50, 51");

   data_set.insert( 52);

   BOOST_REQUIRE_EQUAL( rangeValueString( data_set), "25, 26, 28-32, 50-52");

} // set_container



// =====  END OF test_range_value_string.cpp  =====

