
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module celma::common::Filter, using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/common/detail/filter.hpp"


// Boost includes
#define BOOST_TEST_MODULE FilterTest
#include <boost/test/unit_test.hpp>


using celma::common::detail::Filter;



/// Test that error conditions are handled correctly.
///
/// @since  x.y.z, 09.10.2019
BOOST_AUTO_TEST_CASE( errors)
{

   {
      Filter< int>  my_filter;

      BOOST_REQUIRE_THROW( my_filter.matches( 41), std::runtime_error);
   } // end scope

} // errors



/// Single value filter.
///
/// @since  x.y.z, 31.10.2017
BOOST_AUTO_TEST_CASE( test_single_value)
{

   {
      Filter< int>  my_filter;

      my_filter.addSingleValueFilter( 42);

      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( !my_filter.matches( 43));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "42");
   } // end scope

   {
      Filter< int>  my_filter;

      my_filter.addSingleValueFilter( 42, true);

      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "!42");
   } // end scope

} // test_single_value



/// Value range filter.
///
/// @since  x.y.z, 31.10.2017
BOOST_AUTO_TEST_CASE( test_value_range)
{

   {
      Filter< int>  my_filter;

      my_filter.addRangeFilter( 100, 200);

      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 199));
      BOOST_REQUIRE( my_filter.matches( 200));
      BOOST_REQUIRE( !my_filter.matches( 201));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "100-200");
   } // end scope

   {
      Filter< int>  my_filter;

      my_filter.addRangeFilter( 100, 200, true);

      BOOST_REQUIRE( my_filter.matches( 99));
      BOOST_REQUIRE( !my_filter.matches( 100));
      BOOST_REQUIRE( !my_filter.matches( 101));

      BOOST_REQUIRE( !my_filter.matches( 199));
      BOOST_REQUIRE( !my_filter.matches( 200));
      BOOST_REQUIRE( my_filter.matches( 201));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "!100-200");
   } // end scope

} // test_value_range



/// Minimum or maximum value filter.
///
/// @since  x.y.z, 02.11.2017
BOOST_AUTO_TEST_CASE( test_min_max_value)
{

   {
      Filter< int>  my_filter;

      my_filter.addMinimumFilter( 42);

      BOOST_REQUIRE( !my_filter.matches( 40));
      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "[42");
   } // end scope

   {
      Filter< int>  my_filter;

      my_filter.addMaximumFilter( 42);

      BOOST_REQUIRE( my_filter.matches( 40));
      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 42));
      BOOST_REQUIRE( !my_filter.matches( 43));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "]42");
   } // end scope

} // test_min_max_value



/// Single value filters combined.
///
/// @since  x.y.z, 06.11.2017
BOOST_AUTO_TEST_CASE( test_single_values_combined)
{

   // two single value filters cannot be true at the same time
   {
      Filter< int>  my_filter;

      my_filter.addSingleValueFilter( 13);
      my_filter.addSingleValueFilter( 42);

      BOOST_REQUIRE( !my_filter.matches( 11));
      BOOST_REQUIRE( !my_filter.matches( 12));
      BOOST_REQUIRE( !my_filter.matches( 13));
      BOOST_REQUIRE( !my_filter.matches( 14));
      BOOST_REQUIRE( !my_filter.matches( 15));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "13+42");
   } // end scope

   // two inverted single value filters: everything except these two values
   {
      Filter< int>  my_filter;

      my_filter.addSingleValueFilter( 13, true);
      my_filter.addSingleValueFilter( 42, true);

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

      BOOST_REQUIRE_EQUAL( my_filter.str(), "!13+!42");
   } // end scope

} // test_single_values_combined



/// Combinations of/with ranges.
///
/// @since  x.y.z, 06.11.2017
BOOST_AUTO_TEST_CASE( test_range_combinations)
{

   // two ranges, one big range with an exclude-range within
   {
      Filter< int>  my_filter;

      my_filter.addRangeFilter( 100, 500);
      my_filter.addRangeFilter( 300, 400, true);

      BOOST_REQUIRE( !my_filter.matches( 98));
      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 298));
      BOOST_REQUIRE( my_filter.matches( 299));
      BOOST_REQUIRE( !my_filter.matches( 300));
      BOOST_REQUIRE( !my_filter.matches( 301));

      BOOST_REQUIRE( !my_filter.matches( 399));
      BOOST_REQUIRE( !my_filter.matches( 400));
      BOOST_REQUIRE( my_filter.matches( 401));
      BOOST_REQUIRE( my_filter.matches( 402));

      BOOST_REQUIRE( my_filter.matches( 499));
      BOOST_REQUIRE( my_filter.matches( 500));
      BOOST_REQUIRE( !my_filter.matches( 501));
      BOOST_REQUIRE( !my_filter.matches( 502));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "100-500+!300-400");
   } // end scope

   // a range with a single excluded value within
   {
      Filter< int>  my_filter;

      my_filter.addRangeFilter( 100, 500);
      my_filter.addSingleValueFilter( 250, true);

      BOOST_REQUIRE( !my_filter.matches( 98));
      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 249));
      BOOST_REQUIRE( !my_filter.matches( 250));
      BOOST_REQUIRE( my_filter.matches( 251));

      BOOST_REQUIRE( my_filter.matches( 499));
      BOOST_REQUIRE( my_filter.matches( 500));
      BOOST_REQUIRE( !my_filter.matches( 501));
      BOOST_REQUIRE( !my_filter.matches( 502));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "100-500+!250");
   } // end scope

} // test_range_combinations



/// Minimum and maximum value filter.
///
/// @since  x.y.z, 09.10.2019
BOOST_AUTO_TEST_CASE( min_and_max_value)
{

   {
      Filter< int>  my_filter;

      my_filter.addMinimumFilter( 42);
      my_filter.addMaximumFilter( 84);

      BOOST_REQUIRE( !my_filter.matches( 40));
      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));

      BOOST_REQUIRE( my_filter.matches( 82));
      BOOST_REQUIRE( my_filter.matches( 83));
      BOOST_REQUIRE( !my_filter.matches( 84));
      BOOST_REQUIRE( !my_filter.matches( 85));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "[42+]84");
   } // end scope

} // test_min_max_value



// =====  END OF test_filter.cpp  =====

