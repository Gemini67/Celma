 
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module clear_container using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/common/clear_container.hpp"


// C++ Standard Library includes
#include <list>
#include <map>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ClearContainerTest
#include <boost/test/unit_test.hpp>


namespace {


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


} // namespace



/// Clear a vector.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_clear_vector)
{

   using std::vector;

   {
      vector< int*>  myVec;

      myVec.push_back( new int(   42));
      myVec.push_back( new int( 4711));

      celma::common::Vector::clear( myVec);

      BOOST_REQUIRE( myVec.empty());
   } // end scope

   {
      std::vector< TestCountInstances*>  myVec;

      myVec.push_back( new TestCountInstances);
      myVec.push_back( new TestCountInstances);
      myVec.push_back( new TestCountInstances);

      celma::common::Vector::clear( myVec);

      BOOST_REQUIRE( myVec.empty());
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

} // test_clear_vector



/// Clear a container, here: a list.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_clear_list)
{

   {
      std::list< int*>  myList;

      myList.push_back( new int(   42));
      myList.push_back( new int( 4711));

      celma::common::Container::clear( myList);

      BOOST_REQUIRE( myList.empty());
   } // end scope

   {
      std::list< TestCountInstances*>  myList;

      myList.push_back( new TestCountInstances);
      myList.push_back( new TestCountInstances);
      myList.push_back( new TestCountInstances);

      celma::common::Container::clear( myList);

      BOOST_REQUIRE( myList.empty());
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

} // test_clear_list



/// Clear a map.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_clear_map)
{

   {
      std::map< int, int*>  myMap;

      myMap[   42] = new int(   42);
      myMap[ 4711] = new int( 4711);

      celma::common::Map::clear( myMap);

      BOOST_REQUIRE( myMap.empty());
   } // end scope

   {
      std::map< int, TestCountInstances*>  myMap;

      myMap[ 1] = new TestCountInstances;
      myMap[ 3] = new TestCountInstances;
      myMap[ 5] = new TestCountInstances;

      celma::common::Map::clear( myMap);

      BOOST_REQUIRE( myMap.empty());
      BOOST_REQUIRE_EQUAL( TestCountInstances::mInstances, 0);
   } // end scope

} // test_clear_map



// =====  END OF test_clear_container.cpp  =====

