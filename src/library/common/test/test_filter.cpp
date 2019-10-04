
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the specific filter classes using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/common/filter.hpp"


// Boost includes
#define BOOST_TEST_MODULE FilterTest
#include <boost/test/unit_test.hpp>


using celma::common::Filter;


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
   } // end scope

   {
      Filter< int>  my_filter;

      my_filter.addSingleValueFilter( 42, true);

      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 42));
      BOOST_REQUIRE( my_filter.matches( 43));
   } // end scope

} // test_single_value



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
   } // end scope

} // test_value_range



/// 
/// @since  x.y.z, 02.11.2017
BOOST_AUTO_TEST_CASE( test_value_list)
{

   {
      Filter< int>  my_filter;
      std::vector< int>  value_list = { 6, 24 };

      my_filter.addValueListFilter( value_list);

      BOOST_REQUIRE( !my_filter.matches( 5));
      BOOST_REQUIRE( my_filter.matches( 6));
      BOOST_REQUIRE( !my_filter.matches( 7));

      BOOST_REQUIRE( !my_filter.matches( 23));
      BOOST_REQUIRE( my_filter.matches( 24));
      BOOST_REQUIRE( !my_filter.matches( 25));
   } // end scope

   {
      Filter< int>  my_filter;
      std::vector< int>  value_list = { 6, 24 };

      my_filter.addValueListFilter( value_list, true);

      BOOST_REQUIRE( my_filter.matches( 5));
      BOOST_REQUIRE( !my_filter.matches( 6));
      BOOST_REQUIRE( my_filter.matches( 7));

      BOOST_REQUIRE( my_filter.matches( 23));
      BOOST_REQUIRE( !my_filter.matches( 24));
      BOOST_REQUIRE( my_filter.matches( 25));
   } // end scope

} // test_value_list



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
   } // end scope

   {
      Filter< int>  my_filter;

      my_filter.addMaximumFilter( 42);

      BOOST_REQUIRE( my_filter.matches( 40));
      BOOST_REQUIRE( my_filter.matches( 41));
      BOOST_REQUIRE( !my_filter.matches( 42));
      BOOST_REQUIRE( !my_filter.matches( 43));
   } // end scope

} // test_min_max_value



/// 
/// @since  x.y.z, 06.11.2017
BOOST_AUTO_TEST_CASE( test_single_values_combined)
{

   {
      Filter< int>  my_filter;

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
   } // end scope

} // test_single_values_combined



/// 
/// @since  x.y.z, 06.11.2017
BOOST_AUTO_TEST_CASE( test_range_combinations)
{

   // a range with an excluded range within
   {
      Filter< int>  my_filter;

      my_filter.addRangeFilter( 100, 500);
      my_filter.addRangeFilter( 200, 399, true);

      BOOST_REQUIRE( !my_filter.matches( 98));
      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 198));
      BOOST_REQUIRE( my_filter.matches( 199));
      BOOST_REQUIRE( !my_filter.matches( 200));
      BOOST_REQUIRE( !my_filter.matches( 201));

      BOOST_REQUIRE( !my_filter.matches( 398));
      BOOST_REQUIRE( !my_filter.matches( 399));
      BOOST_REQUIRE( my_filter.matches( 400));
      BOOST_REQUIRE( my_filter.matches( 401));

      BOOST_REQUIRE( my_filter.matches( 499));
      BOOST_REQUIRE( my_filter.matches( 500));
      BOOST_REQUIRE( !my_filter.matches( 501));
      BOOST_REQUIRE( !my_filter.matches( 502));
   } // end scope

   // a range with an excluded single value within
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
   } // end scope

   // two excluded ranges
   {
      Filter< int>  my_filter;

      my_filter.addRangeFilter( 10, 20, true);
      my_filter.addRangeFilter( 50, 60, true);

      BOOST_REQUIRE( my_filter.matches( 8));
      BOOST_REQUIRE( my_filter.matches( 9));
      BOOST_REQUIRE( !my_filter.matches( 10));
      BOOST_REQUIRE( !my_filter.matches( 11));

      BOOST_REQUIRE( !my_filter.matches( 18));
      BOOST_REQUIRE( !my_filter.matches( 19));
      BOOST_REQUIRE( !my_filter.matches( 20));
      BOOST_REQUIRE( my_filter.matches( 21));
      BOOST_REQUIRE( my_filter.matches( 22));

      BOOST_REQUIRE( my_filter.matches( 48));
      BOOST_REQUIRE( my_filter.matches( 49));
      BOOST_REQUIRE( !my_filter.matches( 50));
      BOOST_REQUIRE( !my_filter.matches( 51));

      BOOST_REQUIRE( !my_filter.matches( 58));
      BOOST_REQUIRE( !my_filter.matches( 59));
      BOOST_REQUIRE( !my_filter.matches( 60));
      BOOST_REQUIRE( my_filter.matches( 61));
      BOOST_REQUIRE( my_filter.matches( 62));
   } // end scope

   // an excluded range with a single value within
   {
      Filter< int>  my_filter;

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



// =====  END OF test_filter.cpp  =====

