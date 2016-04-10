 
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
**    Test program for the module clear_container using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <stdint.h>
#include <cstdio>
#include <cstring>


// C++ Standard Library includes
#include <list>
#include <map>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ClearContainerTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/clear_container.hpp"


using namespace std;
using namespace celma;



class TestCountInstances
{
public:
   static uint64_t  mInstances;

   TestCountInstances()
   {
      ++mInstances;
   }
   TestCountInstances( const TestCountInstances&)
   {
      ++mInstances;
   }
   ~TestCountInstances()
   {
      --mInstances;
   }

};


uint64_t  TestCountInstances::mInstances = 0;


/// Clear a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_clear_vector)
{

   {
      vector< int*>  myVec;

      myVec.push_back( new int(   42));
      myVec.push_back( new int( 4711));

      celma::common::Vector::clear( myVec);

      BOOST_REQUIRE( myVec.empty());
   } // end scope

   {
      vector< TestCountInstances*>  myVec;

      myVec.push_back( new TestCountInstances);
      myVec.push_back( new TestCountInstances);
      myVec.push_back( new TestCountInstances);

      celma::common::Vector::clear( myVec);

      BOOST_REQUIRE( myVec.empty());
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

} // end test_clear_vector



/// Clear a container, here: a list.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_clear_list)
{

   {
      list< int*>  myList;

      myList.push_back( new int(   42));
      myList.push_back( new int( 4711));

      celma::common::Container::clear( myList);

      BOOST_REQUIRE( myList.empty());
   } // end scope

   {
      list< TestCountInstances*>  myList;

      myList.push_back( new TestCountInstances);
      myList.push_back( new TestCountInstances);
      myList.push_back( new TestCountInstances);

      celma::common::Container::clear( myList);

      BOOST_REQUIRE( myList.empty());
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

} // end test_clear_list



/// Clear a map.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_clear_map)
{

   {
      map< int, int*>  myMap;

      myMap[   42] = new int(   42);
      myMap[ 4711] = new int( 4711);

      celma::common::Map::clear( myMap);

      BOOST_REQUIRE( myMap.empty());
   } // end scope

   {
      map< int, TestCountInstances*>  myMap;

      myMap[ 1] = new TestCountInstances;
      myMap[ 3] = new TestCountInstances;
      myMap[ 5] = new TestCountInstances;

      celma::common::Map::clear( myMap);

      BOOST_REQUIRE( myMap.empty());
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

} // end test_clear_map



// =========================  END OF test_clear_container.cpp  =========================
