
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "value filter", using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/common/value_filter.hpp"


// Boost includes
#define BOOST_TEST_MODULE ValueFilterTest
#include <boost/test/unit_test.hpp>


using celma::common::ValueFilter;



/// Verify that errors are handled correctly.
///
/// @since  x.y.z, 08.10.2019
BOOST_AUTO_TEST_CASE( errors)
{

   {
      ValueFilter< int>  my_filter;

      BOOST_REQUIRE_THROW( my_filter.matches( 42), std::runtime_error);
   } // end scope

   {
      ValueFilter< int>  my_filter;

      BOOST_REQUIRE_THROW( my_filter.appendSingleValueFilter( 42),
         std::runtime_error);
   } // end scope

   {
      ValueFilter< int>  my_filter;

      BOOST_REQUIRE_THROW( my_filter.appendRangeFilter( 13, 42),
         std::runtime_error);
   } // end scope

   {
      ValueFilter< int>  my_filter;

      BOOST_REQUIRE_THROW( my_filter.appendMinimumFilter( 13),
         std::runtime_error);
   } // end scope

   {
      ValueFilter< int>  my_filter;

      BOOST_REQUIRE_THROW( my_filter.appendMaximumFilter( 42),
         std::runtime_error);
   } // end scope

} // errors



/// Filter for a single value.
///
/// @since  x.y.z, 07.10.2019
BOOST_AUTO_TEST_CASE( test_single_value)
{

   {
      ValueFilter< int>  my_filter;

      my_filter.addSingleValueFilter( 42);

      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( !my_filter.matches( 43));
   } // end scope

   {
      ValueFilter< int>  my_filter;

      my_filter.addSingleValueFilter( 42, true);

      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));
   } // end scope

} // test_single_value



/// Filter for a range of values.
///
/// @since  x.y.z, 07.10.2019
BOOST_AUTO_TEST_CASE( test_value_range)
{

   {
      ValueFilter< int>  my_filter;

      my_filter.addRangeFilter( 100, 200);

      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 199));
      BOOST_REQUIRE( my_filter.matches( 200));
      BOOST_REQUIRE( !my_filter.matches( 201));
   } // end scope

   {
      ValueFilter< int>  my_filter;

      my_filter.addRangeFilter( 100, 200, true);

      BOOST_REQUIRE( my_filter.matches( 99));
      BOOST_REQUIRE( !my_filter.matches( 100));
      BOOST_REQUIRE( !my_filter.matches( 101));

      BOOST_REQUIRE( !my_filter.matches( 199));
      BOOST_REQUIRE( !my_filter.matches( 200));
      BOOST_REQUIRE( my_filter.matches( 201));
   } // end scope

} // test_value_range



/// Filter for a minimum or maximum value.
///
/// @since  x.y.z, 07.10.2019
BOOST_AUTO_TEST_CASE( test_min_max_value)
{

   {
      ValueFilter< int>  my_filter;

      my_filter.addMinimumFilter( 42);

      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));
   } // end scope

   {
      ValueFilter< int>  my_filter;

      my_filter.addMaximumFilter( 42);

      BOOST_REQUIRE( my_filter.matches( 40));
      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 42));
      BOOST_REQUIRE( !my_filter.matches( 43));
   } // end scope

} // test_min_max_value



/// Filter for two single values.
///
/// @since  x.y.z, 07.10.2019
BOOST_AUTO_TEST_CASE( test_single_values_combined)
{

   {
      ValueFilter< int>  my_filter;

      my_filter.addSingleValueFilter( 13);
      my_filter.addSingleValueFilter( 42);

      BOOST_REQUIRE( !my_filter.matches( 11));
      BOOST_REQUIRE( !my_filter.matches( 12));
      BOOST_REQUIRE( my_filter.matches( 13));
      BOOST_REQUIRE( !my_filter.matches( 14));
      BOOST_REQUIRE( !my_filter.matches( 15));

      BOOST_REQUIRE( !my_filter.matches( 40));
      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( !my_filter.matches( 43));
      BOOST_REQUIRE( !my_filter.matches( 44));
   } // end scope

   // one normal and one inverted single value filter: the first is not really
   // used
   {
      ValueFilter< int>  my_filter;

      my_filter.addSingleValueFilter( 13);
      my_filter.addSingleValueFilter( 42, true);

      BOOST_REQUIRE( my_filter.matches( 11));
      BOOST_REQUIRE( my_filter.matches( 12));
      BOOST_REQUIRE( my_filter.matches( 13));
      BOOST_REQUIRE( my_filter.matches( 14));
      BOOST_REQUIRE( my_filter.matches( 15));

      BOOST_REQUIRE( my_filter.matches( 40));
      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));
      BOOST_REQUIRE( my_filter.matches( 44));
   } // end scope

   // two inverted single value filter combined
   {
      ValueFilter< int>  my_filter;

      my_filter.addSingleValueFilter( 13, true);
      my_filter.appendSingleValueFilter( 42, true);

      BOOST_REQUIRE( my_filter.matches( 11));
      BOOST_REQUIRE( my_filter.matches( 12));
      BOOST_REQUIRE( !my_filter.matches( 13));
      BOOST_REQUIRE( my_filter.matches( 14));
      BOOST_REQUIRE( my_filter.matches( 15));

      BOOST_REQUIRE( my_filter.matches( 40));
      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));
      BOOST_REQUIRE( my_filter.matches( 44));
   } // end scope

   // two inverted single value filter: one filter will always match
   {
      ValueFilter< int>  my_filter;

      my_filter.addSingleValueFilter( 13, true);
      my_filter.addSingleValueFilter( 42, true);

      BOOST_REQUIRE( my_filter.matches( 11));
      BOOST_REQUIRE( my_filter.matches( 12));
      BOOST_REQUIRE( my_filter.matches( 13));
      BOOST_REQUIRE( my_filter.matches( 14));
      BOOST_REQUIRE( my_filter.matches( 15));

      BOOST_REQUIRE( my_filter.matches( 40));
      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));
      BOOST_REQUIRE( my_filter.matches( 44));
   } // end scope

} // test_single_values_combined



/// Filter combinations with a range.
///
/// @since  x.y.z, 07.10.2019
BOOST_AUTO_TEST_CASE( test_range_combinations)
{

   // an excluded range with a single value within
   {
      ValueFilter< int>  my_filter;

      my_filter.addRangeFilter( 100, 500, true);
      my_filter.addSingleValueFilter( 250);

      BOOST_REQUIRE( my_filter.matches( 98));
      BOOST_REQUIRE( my_filter.matches( 99));
      BOOST_REQUIRE( !my_filter.matches( 100));
      BOOST_REQUIRE( !my_filter.matches( 101));

      BOOST_REQUIRE( !my_filter.matches( 249));
      BOOST_REQUIRE( my_filter.matches( 250));
      BOOST_REQUIRE( !my_filter.matches( 251));

      BOOST_REQUIRE( !my_filter.matches( 499));
      BOOST_REQUIRE( !my_filter.matches( 500));
      BOOST_REQUIRE( my_filter.matches( 501));
      BOOST_REQUIRE( my_filter.matches( 502));
   } // end scope

} // test_range_combinations



/// Test multiple combinations.
///
/// @since  x.y.z, 09.10.2019
BOOST_AUTO_TEST_CASE( multiple_combinations)
{

   // minimum, single exclude and maximum filter
   {
      ValueFilter< int>  my_filter;

      my_filter.addMinimumFilter( 50);
      BOOST_REQUIRE_NO_THROW( my_filter.appendSingleValueFilter( 75, true));
      BOOST_REQUIRE_NO_THROW( my_filter.appendMaximumFilter( 100));

      BOOST_REQUIRE( !my_filter.matches( 48));
      BOOST_REQUIRE( !my_filter.matches( 49));
      BOOST_REQUIRE( my_filter.matches( 50));
      BOOST_REQUIRE( my_filter.matches( 51));

      BOOST_REQUIRE( my_filter.matches( 74));
      BOOST_REQUIRE( !my_filter.matches( 75));
      BOOST_REQUIRE( my_filter.matches( 76));

      BOOST_REQUIRE( my_filter.matches( 98));
      BOOST_REQUIRE( my_filter.matches( 99));
      BOOST_REQUIRE( !my_filter.matches( 100));
      BOOST_REQUIRE( !my_filter.matches( 101));
   } // end scope

   // range and single excluded
   {
      ValueFilter< int>  my_filter;

      my_filter.addRangeFilter( 100, 200);
      BOOST_REQUIRE_NO_THROW( my_filter.appendSingleValueFilter( 150, true));
      my_filter.addSingleValueFilter( 50);
      my_filter.addSingleValueFilter( 250);

      BOOST_REQUIRE( !my_filter.matches( 49));
      BOOST_REQUIRE( my_filter.matches( 50));
      BOOST_REQUIRE( !my_filter.matches( 51));

      BOOST_REQUIRE( !my_filter.matches( 98));
      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 149));
      BOOST_REQUIRE( !my_filter.matches( 150));
      BOOST_REQUIRE( my_filter.matches( 151));

      BOOST_REQUIRE( my_filter.matches( 199));
      BOOST_REQUIRE( my_filter.matches( 200));
      BOOST_REQUIRE( !my_filter.matches( 201));
      BOOST_REQUIRE( !my_filter.matches( 202));

      BOOST_REQUIRE( !my_filter.matches( 249));
      BOOST_REQUIRE( my_filter.matches( 250));
      BOOST_REQUIRE( !my_filter.matches( 251));
   } // end scope

   // same filters but different order
   {
      ValueFilter< int>  my_filter;

      my_filter.addSingleValueFilter( 50);
      my_filter.addSingleValueFilter( 150, true);
      BOOST_REQUIRE_NO_THROW( my_filter.appendRangeFilter( 100, 200));
      my_filter.addSingleValueFilter( 250);

      BOOST_REQUIRE( !my_filter.matches( 49));
      BOOST_REQUIRE( my_filter.matches( 50));
      BOOST_REQUIRE( !my_filter.matches( 51));

      BOOST_REQUIRE( !my_filter.matches( 98));
      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 149));
      BOOST_REQUIRE( !my_filter.matches( 150));
      BOOST_REQUIRE( my_filter.matches( 151));

      BOOST_REQUIRE( my_filter.matches( 199));
      BOOST_REQUIRE( my_filter.matches( 200));
      BOOST_REQUIRE( !my_filter.matches( 201));
      BOOST_REQUIRE( !my_filter.matches( 202));

      BOOST_REQUIRE( !my_filter.matches( 249));
      BOOST_REQUIRE( my_filter.matches( 250));
      BOOST_REQUIRE( !my_filter.matches( 251));
   } // end scope

   // single value excluded and minimum filter
   {
      ValueFilter< int>  my_filter;

      my_filter.addSingleValueFilter( 200, true);
      BOOST_REQUIRE_NO_THROW( my_filter.appendMinimumFilter( 100));

      BOOST_REQUIRE( !my_filter.matches( 98));
      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 199));
      BOOST_REQUIRE( !my_filter.matches( 200));
      BOOST_REQUIRE( my_filter.matches( 201));
   } // end scope

} // multiple_combinations



// =====  END OF test_filter.cpp  =====

