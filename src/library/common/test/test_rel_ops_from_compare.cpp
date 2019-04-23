
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
#include "celma/common/rel_ops_from_compare.hpp"
 
 
// C++ Standard Library includes
#include <iostream>
 
 
// Boost includes
#define BOOST_TEST_MODULE RelOpsFromCompareTest
#include <boost/test/unit_test.hpp>
 
 
using celma::common::RelOpsFromCompare;
 
 
namespace {
 
 
class Number : public RelOpsFromCompare< Number>
{
public:
   Number( int val):
         mValue( val)
   {
   }
 
   int compare( const Number& other) const
   {
      return mValue - other.mValue;
   }
 
private:
   int  mValue;
 
};
 
 
} // namespace
 
 
 
/// Test the relational operators with two objects.
/// @since  1.22.0, 27.03.2019
BOOST_AUTO_TEST_CASE( comparisons)
{
 
   Number  n1( 15);
   Number  n2( 27);
 
 
   BOOST_REQUIRE( n1 < n2);
   BOOST_REQUIRE( n1 <= n2);
   BOOST_REQUIRE( n1 <= n1);
   BOOST_REQUIRE( n1 == n1);
   BOOST_REQUIRE( n2 == n2);
   BOOST_REQUIRE( n1 != n2);
   BOOST_REQUIRE( n2 != n1);
   BOOST_REQUIRE( n2 >= n1);
   BOOST_REQUIRE( n2 >= n2);
   BOOST_REQUIRE( n2 > n1);
 
   BOOST_REQUIRE( !(n1 < n1));
   BOOST_REQUIRE( !(n2 < n2));
   BOOST_REQUIRE( !(n2 < n1));
   BOOST_REQUIRE( !(n2 <= n1));
   BOOST_REQUIRE( !(n1 == n2));
   BOOST_REQUIRE( !(n1 != n1));
   BOOST_REQUIRE( !(n2 != n2));
   BOOST_REQUIRE( !(n1 >= n2));
   BOOST_REQUIRE( !(n1 >= n2));
   BOOST_REQUIRE( !(n1 > n2));
   BOOST_REQUIRE( !(n1 > n1));
   BOOST_REQUIRE( !(n2 > n2));
 
} // comparisons



// =====  END OF test_rel_ops_from_compare.cpp  =====

