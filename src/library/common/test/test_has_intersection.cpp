
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
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
#include <set>
#include <unordered_set>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE HasIntersectionTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/check_return.hpp"


using celma::common::hasIntersection;


namespace {


/// Does some checks with different orders of the values.
///
/// @tparam  C  The type of the container to use for the test.
/// @return  \c true if hasIntersection() always returned the expected result.
/// @since  x.y.z, 05.07.2020
template< template< typename T> class C> bool checkType( bool is_sorted)
{

   // sorte4d, no conflict
   {
      C< int>  one = { 1, 2, 3 };
      C< int>  two = { 4, 5, 6 };

      CHECK_RETURN( !hasIntersection( one, two, false));
      CHECK_RETURN( !hasIntersection( one, two, true));
   } // end scope

   // still sorted and no conflict
   {
      C< int>  one = { 1, 3, 5 };
      C< int>  two = { 2, 4, 6 };

      CHECK_RETURN( !hasIntersection( one, two, false));
      CHECK_RETURN( !hasIntersection( one, two, true));
   } // end scope

   // not sorted, but still no conflict
   {
      C< int>  one = { 3, 2, 1 };
      C< int>  two = { 6, 5, 4 };

      CHECK_RETURN( !hasIntersection( one, two, false));
      CHECK_RETURN( !hasIntersection( one, two, true));
   } // end scope

   // sorted, but conflict
   // consider if the container is really sorted or not
   {
      C< int>  one = { 1, 2, 3 };
      C< int>  two = { 3, 4, 5 };

      CHECK_RETURN( hasIntersection( one, two, is_sorted));
   } // end scope

   // not sorted and conflict
   // consider if the container is really sorted or not
   {
      C< int>  one = { 8, 6, 4, 2 };
      C< int>  two = { 7, 5, 4, 1 };

      CHECK_RETURN( hasIntersection( one, two, is_sorted));
   } // end scope

   return true;
} // checkType


} // namespace



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
      BOOST_REQUIRE( hasIntersection( v1, v2, true));
   else
      BOOST_REQUIRE( !hasIntersection( v1, v2, true));

   v1.push_back( 13);
   v3.clear();
   std::set_intersection( v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
      std::back_inserter( v3));

   if (v3.size() > 0)
      BOOST_REQUIRE( hasIntersection( v1, v2, true));
   else
      BOOST_REQUIRE( !hasIntersection( v1, v2, true));

   v2.push_back( 42);
   v3.clear();
   std::set_intersection( v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
      std::back_inserter( v3));

   if (v3.size() > 0)
      BOOST_REQUIRE( hasIntersection( v1, v2, true));
   else
      BOOST_REQUIRE( !hasIntersection( v1, v2, true));

   v1.push_back( 42);
   v3.clear();
   std::set_intersection( v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
      std::back_inserter( v3));

   if (v3.size() > 0)
      BOOST_REQUIRE( hasIntersection( v1, v2, true));
   else
      BOOST_REQUIRE( !hasIntersection( v1, v2, true));

} // verify_has_intersection



/// Test celma::common::hasIntersection<>() with different container types.
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( has_intersection_types)
{

   BOOST_REQUIRE( checkType< std::unordered_set>( false));
   BOOST_REQUIRE( checkType< std::set>( true));
   BOOST_REQUIRE( checkType< std::vector>( false));

} // has_intersection_types



// =====  END OF test_has_intersection.cpp  =====

