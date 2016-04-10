
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
**    Test program for the functions of the module RangeGenerator.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE RangeGeneratorTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/range_generator.hpp"


using namespace std;
using namespace celma;



/// Create object with invalid single value.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_invalid_single)
{

   common::RangeGenerator< int>*  ptr = nullptr;


   BOOST_REQUIRE_THROW( ptr = new common::RangeGenerator< int>( -1), logic_error);
   delete ptr;

} // end test_invalid_single



/// Create object with invalid range where the start-value is greater than the
/// end-value.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_invalid_range)
{

   common::RangeGenerator< int>*  ptr = nullptr;


   BOOST_REQUIRE_THROW( ptr = new common::RangeGenerator< int>( 12, 7), logic_error);
   delete ptr;

} // end test_invalid_range



/// Create object with invalid range that includes the iterator-end.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_invalid_range_end)
{

   common::RangeGenerator< int>*  ptr = nullptr;


   BOOST_REQUIRE_THROW( ptr = new common::RangeGenerator< int>( -5, 5), logic_error);
   delete ptr;

} // end test_invalid_range_end



/// Create object with invalid range increment.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_invalid_range_increment)
{

   common::RangeGenerator< int>*  ptr = nullptr;


   BOOST_REQUIRE_THROW( ptr = new common::RangeGenerator< int>( 3, 9, -1), logic_error);
   delete ptr;

} // end test_invalid_range_increment



/// Attempt to set an exclude-value on single-value range.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_single_value_exclude)
{

   common::RangeGenerator< int>  rg( 1);


   BOOST_REQUIRE_THROW( rg.excludeValue( 11), logic_error);

} // end test_single_value_exclude



/// Attempt to set an exclude-value outside of a range.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_value_exclude)
{

   common::RangeGenerator< int>  rg( 10, 20);


   BOOST_REQUIRE_THROW( rg.excludeValue(  9), logic_error);
   BOOST_REQUIRE_THROW( rg.excludeValue( 10), logic_error);
   BOOST_REQUIRE_THROW( rg.excludeValue( 20), logic_error);
   BOOST_REQUIRE_THROW( rg.excludeValue( 21), logic_error);

} // end test_range_value_exclude



/// Attempt to set an exclude-values outside of a range using a container.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_value_exclude_set)
{

   common::RangeGenerator< int>  rg( 10, 20);


   {
      set< int>  excludes;
      excludes.insert( 9);

      BOOST_REQUIRE_THROW( rg.excludeValues( excludes.begin(), excludes.end()),
                           logic_error);
   } // end scope

   {
      set< int>  excludes;
      excludes.insert( 15);
      excludes.insert( 21);

      BOOST_REQUIRE_THROW( rg.excludeValues( excludes.begin(), excludes.end()),
                           logic_error);
   } // end scope

} // end test_range_value_exclude_set



/// Single value range.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_one)
{

   common::RangeGenerator< int>  rg( 1);


   BOOST_REQUIRE( rg != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 1);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

   // test that increment the iterator after end throws
   BOOST_REQUIRE_THROW( ++rg, runtime_error);

} // end test_one



/// Single value range with value 0.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_zero)
{

   common::RangeGenerator< int>  rg( 0);


   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 0);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_zero



/// Range that results in a single value.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_one)
{

   common::RangeGenerator< int>  rg( 5, 5);


   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 5);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_range_one



/// Real range with two values.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_two)
{

   common::RangeGenerator< int>  rg( 5, 6);


   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 5);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 6);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_range_two



/// Range with increment that exceeds the range.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_skip_over)
{

   common::RangeGenerator< int>  rg( 13, 20, 10);


   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 13);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_range_skip_over



/// Range with increment that exactly matches the end value.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_skip_end)
{

   common::RangeGenerator< int>  rg( 13, 23, 10);


   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 13);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 23);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_range_skip_end



/// Range with exclude.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_exclude)
{

   common::RangeGenerator< int>  rg( 14, 16);


   rg.excludeValue( 15);

   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 14);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 16);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_range_exclude



/// Range with increment and multiple values.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_skip)
{

   common::RangeGenerator< int>  rg( 13, 20, 2);


   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 13);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 15);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 17);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 19);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_range_skip



/// Range with increment, multiple values but also exclude values.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_skip_exclude)
{

   common::RangeGenerator< int>  rg( 13, 20, 2);
   set< int>                     excludes;


   excludes.insert( 15);
   excludes.insert( 17);

   rg.excludeValues( excludes.begin(), excludes.end());

   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 13);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 19);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_range_skip_exclude



/// Range that starts with negative numbers and therefore needs to use another
/// iterator-end-value than the default.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_neg)
{

   common::RangeGenerator< int, INT_MIN>  rg( -2, 2);


   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), -2);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), -1);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 0);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 1);

   ++rg;
   BOOST_REQUIRE( static_cast< int>( rg) != rg.end());
   BOOST_REQUIRE_EQUAL( static_cast< int>( rg), 2);

   ++rg;
   BOOST_REQUIRE( rg == rg.end());

} // end test_range_neg



// =========================  END OF test_range_generator.cpp  =========================

