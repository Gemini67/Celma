
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the template RangeDest.
**
--*/


// module to test header file include
#include "celma/common/range_dest.hpp"


// C++ Standard Library includes
#include <iostream>
#include <bitset>
#include <list>
#include <set>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE RangeDestTest
#include <boost/test/unit_test.hpp>


using celma::common::RangeDest;



/// Store integer value in a vector.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_int_vector)
{

   using std::vector;

   vector< int>                   myVector;
   RangeDest< int, vector< int>>  rd( myVector);


   rd.set( 15);

   BOOST_REQUIRE( !myVector.empty());
   BOOST_REQUIRE_EQUAL( myVector[ 0], 15);

} // test_int_vector



/// Store string values in a vector.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_string_vector)
{

   using std::string;
   using std::vector;

   vector< string>                      myVector;
   RangeDest< string, vector< string>>  rd( myVector);


   rd.set( "hello");
   rd.set( "world");

   BOOST_REQUIRE( !myVector.empty());
   BOOST_REQUIRE_EQUAL( myVector.size(), 2);
   BOOST_REQUIRE_EQUAL( myVector[ 0], "hello");
   BOOST_REQUIRE_EQUAL( myVector[ 1], "world");

} // test_string_vector



/// Store integer value in a list.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_int_list)
{

   using std::list;

   list< int>                   myList;
   RangeDest< int, list< int>>  rd( myList);


   rd.set( 15);

   auto  cit = myList.begin();

   BOOST_REQUIRE( !myList.empty());
   BOOST_REQUIRE_EQUAL( *cit, 15);

} // test_int_list



/// Store string values in a list.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_string_list)
{

   using std::list;
   using std::string;

   list< string>                      myList;
   RangeDest< string, list< string>>  rd( myList);


   rd.set( "hello");
   rd.set( "world");

   BOOST_REQUIRE( !myList.empty());
   BOOST_REQUIRE_EQUAL( myList.size(), 2);

   auto  cit = myList.begin();

   BOOST_REQUIRE_EQUAL( *cit, "hello");
   ++cit;
   BOOST_REQUIRE_EQUAL( *cit, "world");

} // test_string_list



/// Store integer value in a set.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_int_set)
{

   using std::set;

   set< int>                   mySet;
   RangeDest< int, set< int>>  rd( mySet);


   rd.set( 15);

   auto  cit = mySet.begin();

   BOOST_REQUIRE( !mySet.empty());
   BOOST_REQUIRE_EQUAL( *cit, 15);

} // test_int_set



/// Store string values in a set.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_string_set)
{

   using std::set;
   using std::string;

   set< string>                      mySet;
   RangeDest< string, set< string>>  rd( mySet);


   rd.set( "hello");
   rd.set( "world");

   BOOST_REQUIRE( !mySet.empty());
   BOOST_REQUIRE_EQUAL( mySet.size(), 2);

   auto  cit = mySet.begin();

   BOOST_REQUIRE_EQUAL( *cit, "hello");
   ++cit;
   BOOST_REQUIRE_EQUAL( *cit, "world");

} // test_string_set



/// Set flags in a bitset.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_bitset)
{

   using std::bitset;

   bitset< 1024>                      myBitset;
   RangeDest< size_t, bitset< 1024>>  rd( myBitset);


   rd.set( 15);
   rd.set( 25);

   BOOST_REQUIRE( !myBitset.none());
   BOOST_REQUIRE_EQUAL( myBitset.count(), 2);
   BOOST_REQUIRE( myBitset[ 15]);
   BOOST_REQUIRE( myBitset[ 25]);

} // test_bitset



// =====  END OF test_range_dest_c.cpp  =====

