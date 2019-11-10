
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
**    Test program for the function celma::common::hasIntersection(), using the
**    Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/common/has_intersection.hpp"


// C++ Standard Library include
#include <algorithm>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE HasIntersectionTest
#include <boost/test/unit_test.hpp>


using celma::common::hasIntersection;



/// Test that the template function celma::common::hasIntersection<>() returns
/// the correct result.
///
/// @since  1.33.0, 30.10.2019
BOOST_AUTO_TEST_CASE( verify_has_intersection)
{

   std::vector< int>  v1;
   std::vector< int>  v2;
   std::vector< int>  v3;

   std::set_intersection( v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
      std::back_inserter( v3));

   if (v3.size() > 0)
      BOOST_REQUIRE( hasIntersection( v1, v2));
   else
      BOOST_REQUIRE( !hasIntersection( v1, v2));

   v1.push_back( 13);
   v3.clear();
   std::set_intersection( v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
      std::back_inserter( v3));

   if (v3.size() > 0)
      BOOST_REQUIRE( hasIntersection( v1, v2));
   else
      BOOST_REQUIRE( !hasIntersection( v1, v2));

   v2.push_back( 42);
   v3.clear();
   std::set_intersection( v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
      std::back_inserter( v3));

   if (v3.size() > 0)
      BOOST_REQUIRE( hasIntersection( v1, v2));
   else
      BOOST_REQUIRE( !hasIntersection( v1, v2));

   v1.push_back( 42);
   v3.clear();
   std::set_intersection( v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
      std::back_inserter( v3));

   if (v3.size() > 0)
      BOOST_REQUIRE( hasIntersection( v1, v2));
   else
      BOOST_REQUIRE( !hasIntersection( v1, v2));

} // verify_has_intersection



// =====  END OF test_has_intersection.cpp  =====

