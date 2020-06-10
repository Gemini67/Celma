
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
**    Test program for the module "parse filter string", using the Boost.Test
**    framework.
**
--*/


// module to test headerfile include
#include "celma/common/parse_filter_string.hpp"


// Boost includes
#define BOOST_TEST_MODULE ParseFilterStringTest
#include <boost/test/unit_test.hpp>


using celma::common::parseFilterString;



/// Verify that errors are handled correctly.
///
/// @since  1.31.0, 09.10.2019
BOOST_AUTO_TEST_CASE( errors)
{

   {
      BOOST_REQUIRE_THROW( auto filters = parseFilterString< int>( ""),
         std::invalid_argument);
   } // end scope

   {
      BOOST_REQUIRE_THROW( auto filters = parseFilterString< int>( "!"),
         std::invalid_argument);
   } // end scope

   {
      BOOST_REQUIRE_THROW( auto filters = parseFilterString< int>( "+"),
         std::invalid_argument);
   } // end scope

   {
      BOOST_REQUIRE_THROW( auto filters = parseFilterString< int>( "42,!"),
         std::invalid_argument);
   } // end scope

   {
      BOOST_REQUIRE_THROW( auto filters = parseFilterString< int>( "42+!"),
         std::invalid_argument);
   } // end scope

   {
      BOOST_REQUIRE_THROW( auto filters = parseFilterString< int>( "hello world"),
         boost::bad_lexical_cast);
   } // end scope

} // errors



/// Filter for a single value.
///
/// @since  1.31.0, 10.10.2019
BOOST_AUTO_TEST_CASE( test_single_value)
{

   {
      auto const  filters = parseFilterString< int>( "42");

      BOOST_REQUIRE( !filters.matches( 41));
      BOOST_REQUIRE( filters.matches( 42));
      BOOST_REQUIRE( !filters.matches( 43));
   } // end scope

   {
      auto const  filters = parseFilterString< int>( "!42");

      BOOST_REQUIRE( filters.matches( 41));
      BOOST_REQUIRE( !filters.matches( 42));
      BOOST_REQUIRE( filters.matches( 43));
   } // end scope

} // test_single_value



/// Filter for a range of values.
///
/// @since  1.31.0, 10.10.2019
BOOST_AUTO_TEST_CASE( test_value_range)
{

   {
      auto const  filters = parseFilterString< int>( "100-200");

      BOOST_REQUIRE( !filters.matches( 99));
      BOOST_REQUIRE( filters.matches( 100));
      BOOST_REQUIRE( filters.matches( 101));

      BOOST_REQUIRE( filters.matches( 199));
      BOOST_REQUIRE( filters.matches( 200));
      BOOST_REQUIRE( !filters.matches( 201));
   } // end scope

   {
      auto const  filters = parseFilterString< int>( "!100-200");

      BOOST_REQUIRE( filters.matches( 99));
      BOOST_REQUIRE( !filters.matches( 100));
      BOOST_REQUIRE( !filters.matches( 101));

      BOOST_REQUIRE( !filters.matches( 199));
      BOOST_REQUIRE( !filters.matches( 200));
      BOOST_REQUIRE( filters.matches( 201));
   } // end scope

} // test_value_range



/// Filter for a minimum or maximum value.
///
/// @since  1.31.0, 10.10.2019
BOOST_AUTO_TEST_CASE( test_min_max_value)
{

   {
      auto const  filters = parseFilterString< int>( "[42");

      BOOST_REQUIRE( !filters.matches( 41));
      BOOST_REQUIRE( !filters.matches( 41));
      BOOST_REQUIRE( filters.matches( 42));
      BOOST_REQUIRE( filters.matches( 43));
   } // end scope

   {
      auto const  filters = parseFilterString< int>( "]42");

      BOOST_REQUIRE( filters.matches( 40));
      BOOST_REQUIRE( filters.matches( 41));
      BOOST_REQUIRE( !filters.matches( 42));
      BOOST_REQUIRE( !filters.matches( 43));
   } // end scope

} // test_min_max_value



/// Filter for two single values.
///
/// @since  1.31.0, 10.10.2019
BOOST_AUTO_TEST_CASE( test_single_values_combined)
{

   {
      auto const  filters = parseFilterString< int>( "13,42");

      BOOST_REQUIRE( !filters.matches( 11));
      BOOST_REQUIRE( !filters.matches( 12));
      BOOST_REQUIRE( filters.matches( 13));
      BOOST_REQUIRE( !filters.matches( 14));
      BOOST_REQUIRE( !filters.matches( 15));

      BOOST_REQUIRE( !filters.matches( 40));
      BOOST_REQUIRE( !filters.matches( 41));
      BOOST_REQUIRE( filters.matches( 42));
      BOOST_REQUIRE( !filters.matches( 43));
      BOOST_REQUIRE( !filters.matches( 44));
   } // end scope

   // one normal and one inverted single value filter: the first is not really
   // used
   {
      auto const  filters = parseFilterString< int>( "13,!42");

      BOOST_REQUIRE( filters.matches( 11));
      BOOST_REQUIRE( filters.matches( 12));
      BOOST_REQUIRE( filters.matches( 13));
      BOOST_REQUIRE( filters.matches( 14));
      BOOST_REQUIRE( filters.matches( 15));

      BOOST_REQUIRE( filters.matches( 40));
      BOOST_REQUIRE( filters.matches( 41));
      BOOST_REQUIRE( !filters.matches( 42));
      BOOST_REQUIRE( filters.matches( 43));
      BOOST_REQUIRE( filters.matches( 44));
   } // end scope

   // two inverted single value filter combined
   {
      auto const  filters = parseFilterString< int>( "!13+!42");

      BOOST_REQUIRE( filters.matches( 11));
      BOOST_REQUIRE( filters.matches( 12));
      BOOST_REQUIRE( !filters.matches( 13));
      BOOST_REQUIRE( filters.matches( 14));
      BOOST_REQUIRE( filters.matches( 15));

      BOOST_REQUIRE( filters.matches( 40));
      BOOST_REQUIRE( filters.matches( 41));
      BOOST_REQUIRE( !filters.matches( 42));
      BOOST_REQUIRE( filters.matches( 43));
      BOOST_REQUIRE( filters.matches( 44));
   } // end scope

   // two inverted single value filter: one filter will always match
   {
      auto const  filters = parseFilterString< int>( "!13,!42");

      BOOST_REQUIRE( filters.matches( 11));
      BOOST_REQUIRE( filters.matches( 12));
      BOOST_REQUIRE( filters.matches( 13));
      BOOST_REQUIRE( filters.matches( 14));
      BOOST_REQUIRE( filters.matches( 15));

      BOOST_REQUIRE( filters.matches( 40));
      BOOST_REQUIRE( filters.matches( 41));
      BOOST_REQUIRE( filters.matches( 42));
      BOOST_REQUIRE( filters.matches( 43));
      BOOST_REQUIRE( filters.matches( 44));
   } // end scope

} // test_single_values_combined



/// Filter combinations with a range.
///
/// @since  1.31.0, 10.10.2019
BOOST_AUTO_TEST_CASE( test_range_combinations)
{

   // an excluded range with a single value within
   {
      auto const  filters = parseFilterString< int>( "!100-500,250");

      BOOST_REQUIRE( filters.matches( 98));
      BOOST_REQUIRE( filters.matches( 99));
      BOOST_REQUIRE( !filters.matches( 100));
      BOOST_REQUIRE( !filters.matches( 101));

      BOOST_REQUIRE( !filters.matches( 249));
      BOOST_REQUIRE( filters.matches( 250));
      BOOST_REQUIRE( !filters.matches( 251));

      BOOST_REQUIRE( !filters.matches( 499));
      BOOST_REQUIRE( !filters.matches( 500));
      BOOST_REQUIRE( filters.matches( 501));
      BOOST_REQUIRE( filters.matches( 502));
   } // end scope

} // test_range_combinations



/// Test multiple combinations.
///
/// @since  1.31.0, 10.10.2019
BOOST_AUTO_TEST_CASE( multiple_combinations)
{

   // minimum, single exclude and maximum filter
   {
      auto const  filters = parseFilterString< int>( "[50+!75+]100");

      BOOST_REQUIRE( !filters.matches( 48));
      BOOST_REQUIRE( !filters.matches( 49));
      BOOST_REQUIRE( filters.matches( 50));
      BOOST_REQUIRE( filters.matches( 51));

      BOOST_REQUIRE( filters.matches( 74));
      BOOST_REQUIRE( !filters.matches( 75));
      BOOST_REQUIRE( filters.matches( 76));

      BOOST_REQUIRE( filters.matches( 98));
      BOOST_REQUIRE( filters.matches( 99));
      BOOST_REQUIRE( !filters.matches( 100));
      BOOST_REQUIRE( !filters.matches( 101));
   } // end scope

   // range and single excluded
   {
      auto const  filters = parseFilterString< int>( "100-200+!150,50,250");

      BOOST_REQUIRE( !filters.matches( 49));
      BOOST_REQUIRE( filters.matches( 50));
      BOOST_REQUIRE( !filters.matches( 51));

      BOOST_REQUIRE( !filters.matches( 98));
      BOOST_REQUIRE( !filters.matches( 99));
      BOOST_REQUIRE( filters.matches( 100));
      BOOST_REQUIRE( filters.matches( 101));

      BOOST_REQUIRE( filters.matches( 149));
      BOOST_REQUIRE( !filters.matches( 150));
      BOOST_REQUIRE( filters.matches( 151));

      BOOST_REQUIRE( filters.matches( 199));
      BOOST_REQUIRE( filters.matches( 200));
      BOOST_REQUIRE( !filters.matches( 201));
      BOOST_REQUIRE( !filters.matches( 202));

      BOOST_REQUIRE( !filters.matches( 249));
      BOOST_REQUIRE( filters.matches( 250));
      BOOST_REQUIRE( !filters.matches( 251));
   } // end scope

   // same filters but different order
   {
      auto const  filters = parseFilterString< int>( "50,!150+100-200,250");

      BOOST_REQUIRE( !filters.matches( 49));
      BOOST_REQUIRE( filters.matches( 50));
      BOOST_REQUIRE( !filters.matches( 51));

      BOOST_REQUIRE( !filters.matches( 98));
      BOOST_REQUIRE( !filters.matches( 99));
      BOOST_REQUIRE( filters.matches( 100));
      BOOST_REQUIRE( filters.matches( 101));

      BOOST_REQUIRE( filters.matches( 149));
      BOOST_REQUIRE( !filters.matches( 150));
      BOOST_REQUIRE( filters.matches( 151));

      BOOST_REQUIRE( filters.matches( 199));
      BOOST_REQUIRE( filters.matches( 200));
      BOOST_REQUIRE( !filters.matches( 201));
      BOOST_REQUIRE( !filters.matches( 202));

      BOOST_REQUIRE( !filters.matches( 249));
      BOOST_REQUIRE( filters.matches( 250));
      BOOST_REQUIRE( !filters.matches( 251));
   } // end scope

   // single value excluded and minimum filter
   {
      auto const  filters = parseFilterString< int>( "!200+[100");

      BOOST_REQUIRE( !filters.matches( 98));
      BOOST_REQUIRE( !filters.matches( 99));
      BOOST_REQUIRE( filters.matches( 100));
      BOOST_REQUIRE( filters.matches( 101));

      BOOST_REQUIRE( filters.matches( 199));
      BOOST_REQUIRE( !filters.matches( 200));
      BOOST_REQUIRE( filters.matches( 201));
   } // end scope

} // multiple_combinations



// =====  END OF test_parse_filter_string.cpp  =====

