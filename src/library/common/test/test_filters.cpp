
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
#include "celma/common/detail/filters.hpp"


// Boost includes
#define BOOST_TEST_MODULE FiltersTest
#include <boost/test/unit_test.hpp>


using celma::common::detail::FilterBase;


BOOST_TEST_DONT_PRINT_LOG_VALUE( FilterBase< int>::Result)



/// 
/// @since  x.y.z, 31.10.2017
BOOST_AUTO_TEST_CASE( test_single_value)
{

   using celma::common::detail::SingleValue;

   {
      SingleValue< int>  sv( 42);

      BOOST_REQUIRE_EQUAL( sv.matches( 41), FilterBase< int>::Result::no_match);
      BOOST_REQUIRE_EQUAL( sv.matches( 42), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( sv.matches( 43), FilterBase< int>::Result::no_match);
   } // end scope

   {
      SingleValue< int>  sv( 42, true);

      BOOST_REQUIRE_EQUAL( sv.matches( 41), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( sv.matches( 42), FilterBase< int>::Result::excluded);
      BOOST_REQUIRE_EQUAL( sv.matches( 43), FilterBase< int>::Result::matches);
   } // end scope

} // test_single_value



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

      BOOST_REQUIRE_EQUAL( vr.matches( 99), FilterBase< int>::Result::no_match);
      BOOST_REQUIRE_EQUAL( vr.matches( 100), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( vr.matches( 101), FilterBase< int>::Result::matches);

      BOOST_REQUIRE_EQUAL( vr.matches( 199), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( vr.matches( 200), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( vr.matches( 201), FilterBase< int>::Result::no_match);
   } // end scope

   {
      ValueRange< int>  vr( 100, 200, true);

      BOOST_REQUIRE_EQUAL( vr.matches( 99), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( vr.matches( 100), FilterBase< int>::Result::excluded);
      BOOST_REQUIRE_EQUAL( vr.matches( 101), FilterBase< int>::Result::excluded);

      BOOST_REQUIRE_EQUAL( vr.matches( 199), FilterBase< int>::Result::excluded);
      BOOST_REQUIRE_EQUAL( vr.matches( 200), FilterBase< int>::Result::excluded);
      BOOST_REQUIRE_EQUAL( vr.matches( 201), FilterBase< int>::Result::matches);
   } // end scope

} // test_value_range



/// 
/// @since  x.y.z, 01.11.2017
BOOST_AUTO_TEST_CASE( test_value_list)
{

   using celma::common::detail::ValueList;

   {
      std::vector< int>  empty;
      BOOST_REQUIRE_THROW( ValueList< int> vl( empty), std::runtime_error);
   } // end scope

   {
      std::vector< int>  values = { 13, 42 };
      ValueList< int>    vl( values);

      BOOST_REQUIRE_EQUAL( vl.matches( 12), FilterBase< int>::Result::no_match);
      BOOST_REQUIRE_EQUAL( vl.matches( 13), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( vl.matches( 14), FilterBase< int>::Result::no_match);

      BOOST_REQUIRE_EQUAL( vl.matches( 41), FilterBase< int>::Result::no_match);
      BOOST_REQUIRE_EQUAL( vl.matches( 42), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( vl.matches( 43), FilterBase< int>::Result::no_match);
   } // end scope

   {
      std::vector< int>  values = { 13, 42 };
      ValueList< int>    vl( values, true);

      BOOST_REQUIRE_EQUAL( vl.matches( 12), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( vl.matches( 13), FilterBase< int>::Result::excluded);
      BOOST_REQUIRE_EQUAL( vl.matches( 14), FilterBase< int>::Result::matches);

      BOOST_REQUIRE_EQUAL( vl.matches( 41), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( vl.matches( 42), FilterBase< int>::Result::excluded);
      BOOST_REQUIRE_EQUAL( vl.matches( 43), FilterBase< int>::Result::matches);
   } // end scope

} // test_value_list



/// 
/// @since  x.y.z, 01.11.2017
BOOST_AUTO_TEST_CASE( test_minimum_value)
{

   using celma::common::detail::MinimumValue;

   {
      MinimumValue< int>  mv( 100);

      BOOST_REQUIRE_EQUAL( mv.matches( 98), FilterBase< int>::Result::no_match);
      BOOST_REQUIRE_EQUAL( mv.matches( 99), FilterBase< int>::Result::no_match);
      BOOST_REQUIRE_EQUAL( mv.matches( 100), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( mv.matches( 101), FilterBase< int>::Result::matches);
   } // end scope

} // test_minimum_value



/// 
/// @since  x.y.z, 02.11.2017
BOOST_AUTO_TEST_CASE( test_maximum_value)
{

   using celma::common::detail::MaximumValue;

   {
      MaximumValue< int>  mv( 100);

      BOOST_REQUIRE_EQUAL( mv.matches( 98), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( mv.matches( 99), FilterBase< int>::Result::matches);
      BOOST_REQUIRE_EQUAL( mv.matches( 100), FilterBase< int>::Result::no_match);
      BOOST_REQUIRE_EQUAL( mv.matches( 101), FilterBase< int>::Result::no_match);
   } // end scope

} // test_minimum_value



// =====  END OF test_filters.cpp  =====

