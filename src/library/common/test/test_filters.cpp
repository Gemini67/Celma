
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
**    Test program for the specific filter classes using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/common/detail/filters.hpp"


// Boost includes
#define BOOST_TEST_MODULE FiltersTest
#include <boost/test/unit_test.hpp>



/// Check the results of a single value filter.
///
/// @since  x.y.z, 31.10.2017
BOOST_AUTO_TEST_CASE( test_single_value)
{

   using celma::common::detail::SingleValue;

   {
      SingleValue< int>  sv( 42);

      BOOST_REQUIRE( !sv.matches( 41));
      BOOST_REQUIRE( sv.matches( 42));
      BOOST_REQUIRE( !sv.matches( 43));

      BOOST_REQUIRE_EQUAL( sv.str(), "42");
   } // end scope

   {
      SingleValue< int>  sv( 42, true);

      BOOST_REQUIRE( sv.matches( 41));
      BOOST_REQUIRE( !sv.matches( 42));
      BOOST_REQUIRE( sv.matches( 43));

      BOOST_REQUIRE_EQUAL( sv.str(), "!42");
   } // end scope

} // test_single_value



/// Check the results of a value range filter.
///
/// @since  x.y.z, 31.10.2017
BOOST_AUTO_TEST_CASE( test_value_range)
{

   using celma::common::detail::ValueRange;

   {
      BOOST_REQUIRE_THROW( ValueRange< int>  vr( 200, 200), std::range_error);
   } // end scope

   {
      ValueRange< int>  vr( 100, 200);

      BOOST_REQUIRE( !vr.matches( 99));
      BOOST_REQUIRE( vr.matches( 100));
      BOOST_REQUIRE( vr.matches( 101));

      BOOST_REQUIRE( vr.matches( 199));
      BOOST_REQUIRE( vr.matches( 200));
      BOOST_REQUIRE( !vr.matches( 201));

      BOOST_REQUIRE_EQUAL( vr.str(), "100-200");
   } // end scope

   {
      ValueRange< int>  vr( 100, 200, true);

      BOOST_REQUIRE( vr.matches( 99));
      BOOST_REQUIRE( !vr.matches( 100));
      BOOST_REQUIRE( !vr.matches( 101));

      BOOST_REQUIRE( !vr.matches( 199));
      BOOST_REQUIRE( !vr.matches( 200));
      BOOST_REQUIRE( vr.matches( 201));

      BOOST_REQUIRE_EQUAL( vr.str(), "!100-200");
   } // end scope

} // test_value_range



/// Check the resuts of a minimum value filter.
///
/// @since  x.y.z, 01.11.2017
BOOST_AUTO_TEST_CASE( test_minimum_value)
{

   using celma::common::detail::MinimumValue;

   {
      MinimumValue< int>  mv( 100);

      BOOST_REQUIRE( !mv.matches( 98));
      BOOST_REQUIRE( !mv.matches( 99));
      BOOST_REQUIRE( mv.matches( 100));
      BOOST_REQUIRE( mv.matches( 101));

      BOOST_REQUIRE_EQUAL( mv.str(), "[100");
   } // end scope

} // test_minimum_value



/// Check the results of a maximum value filter.
///
/// @since  x.y.z, 02.11.2017
BOOST_AUTO_TEST_CASE( test_maximum_value)
{

   using celma::common::detail::MaximumValue;

   {
      MaximumValue< int>  mv( 100);

      BOOST_REQUIRE( mv.matches( 98));
      BOOST_REQUIRE( mv.matches( 99));
      BOOST_REQUIRE( !mv.matches( 100));
      BOOST_REQUIRE( !mv.matches( 101));

      BOOST_REQUIRE_EQUAL( mv.str(), "]100");
   } // end scope

} // test_maximum_value



// =====  END OF test_filters.cpp  =====

