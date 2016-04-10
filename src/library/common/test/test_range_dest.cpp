
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the template RangeDest.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>
#include <bitset>
#include <list>
#include <set>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE RangeDestTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/range_dest.hpp"


using namespace std;
using namespace celma;



/// Store integer value in a vector.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_int_vector)
{

   vector< int>                            myVector;
   common::RangeDest< int, vector< int> >  rd( myVector);


   rd.set( 15);

   BOOST_REQUIRE( !myVector.empty());
   BOOST_REQUIRE_EQUAL( myVector[ 0], 15);

} // end test_int_vector



/// Store string values in a vector.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_string_vector)
{

   vector< string>                               myVector;
   common::RangeDest< string, vector< string> >  rd( myVector);


   rd.set( "hello");
   rd.set( "world");

   BOOST_REQUIRE( !myVector.empty());
   BOOST_REQUIRE_EQUAL( myVector.size(), 2);
   BOOST_REQUIRE_EQUAL( myVector[ 0], "hello");
   BOOST_REQUIRE_EQUAL( myVector[ 1], "world");

} // end test_string_vector



/// Store integer value in a list.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_int_list)
{

   list< int>                            myList;
   common::RangeDest< int, list< int> >  rd( myList);


   rd.set( 15);

   list< int>::const_iterator  cit = myList.begin();

   BOOST_REQUIRE( !myList.empty());
   BOOST_REQUIRE_EQUAL( *cit, 15);

} // end test_int_list



/// Store string values in a list.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_string_list)
{

   list< string>                               myList;
   common::RangeDest< string, list< string> >  rd( myList);


   rd.set( "hello");
   rd.set( "world");

   BOOST_REQUIRE( !myList.empty());
   BOOST_REQUIRE_EQUAL( myList.size(), 2);

   list< string>::const_iterator  cit = myList.begin();

   BOOST_REQUIRE_EQUAL( *cit, "hello");
   ++cit;
   BOOST_REQUIRE_EQUAL( *cit, "world");

} // end test_string_list



/// Store integer value in a set.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_int_set)
{

   set< int>                            mySet;
   common::RangeDest< int, set< int> >  rd( mySet);


   rd.set( 15);

   set< int>::const_iterator  cit = mySet.begin();

   BOOST_REQUIRE( !mySet.empty());
   BOOST_REQUIRE_EQUAL( *cit, 15);

} // end test_int_set



/// Store string values in a set.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_string_set)
{

   set< string>                               mySet;
   common::RangeDest< string, set< string> >  rd( mySet);


   rd.set( "hello");
   rd.set( "world");

   BOOST_REQUIRE( !mySet.empty());
   BOOST_REQUIRE_EQUAL( mySet.size(), 2);

   set< string>::const_iterator  cit = mySet.begin();

   BOOST_REQUIRE_EQUAL( *cit, "hello");
   ++cit;
   BOOST_REQUIRE_EQUAL( *cit, "world");

} // end test_string_set



/// Set flags in a bitset.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_bitset)
{

   bitset< 1024>                               myBitset;
   common::RangeDest< size_t, bitset< 1024> >  rd( myBitset);


   rd.set( 15);
   rd.set( 25);

   BOOST_REQUIRE( !myBitset.none());
   BOOST_REQUIRE_EQUAL( myBitset.count(), 2);
   BOOST_REQUIRE( myBitset[ 15]);
   BOOST_REQUIRE( myBitset[ 25]);

} // end test_bitset



// =========================  END OF test_range_dest.cpp  =========================

