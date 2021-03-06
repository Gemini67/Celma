
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test, header file include
#include "celma/common/contains.hpp"


// C++ Standard Library includes
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ContainsTest
#include <boost/test/unit_test.hpp>


using celma::common::contains;


/// Verify that contains() works on containers without find method.
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( container_wo_find)
{

   {
      std::vector< int>  my_cont;

      my_cont.push_back( 42);

      BOOST_REQUIRE( !contains( my_cont, 13));
      BOOST_REQUIRE( contains( my_cont, 42));
      BOOST_REQUIRE( !contains( my_cont, 4711));
   } // end scope

   {
      std::vector< int>  my_cont;

      my_cont.push_back( 7373);
      my_cont.push_back( 42);

      BOOST_REQUIRE( !contains( my_cont, 13));
      BOOST_REQUIRE( contains( my_cont, 42));
      BOOST_REQUIRE( !contains( my_cont, 4711));
   } // end scope

   {
      std::list< int>  my_cont;

      my_cont.push_back( 42);

      BOOST_REQUIRE( !contains( my_cont, 13));
      BOOST_REQUIRE( contains( my_cont, 42));
      BOOST_REQUIRE( !contains( my_cont, 4711));
   } // end scope

   {
      std::list< int>  my_cont;

      my_cont.push_back( 7373);
      my_cont.push_back( 42);

      BOOST_REQUIRE( !contains( my_cont, 13));
      BOOST_REQUIRE( contains( my_cont, 42));
      BOOST_REQUIRE( !contains( my_cont, 4711));
   } // end scope

} // container_wo_find



/// Verify that contains() works on containers with a special find method.
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( container_with_find)
{

   {
      std::set< int>  my_cont;

      my_cont.insert( 42);

      BOOST_REQUIRE( !contains( my_cont, 13));
      BOOST_REQUIRE( contains( my_cont, 42));
      BOOST_REQUIRE( !contains( my_cont, 4711));
   } // end scope

   {
      std::set< int>  my_cont;

      my_cont.insert( 7373);
      my_cont.insert( 42);

      BOOST_REQUIRE( !contains( my_cont, 13));
      BOOST_REQUIRE( contains( my_cont, 42));
      BOOST_REQUIRE( !contains( my_cont, 4711));
   } // end scope

   {
      std::map< int, int>  my_cont;

      my_cont.insert( std::make_pair( 4, 16));

      BOOST_REQUIRE( !contains( my_cont, 2));
      BOOST_REQUIRE( contains( my_cont, 4));
      BOOST_REQUIRE( !contains( my_cont, 7));
   } // end scope

   {
      std::map< int, int>  my_cont;

      my_cont.insert( std::make_pair( 4, 16));
      my_cont.insert( std::make_pair( 9, 81));

      BOOST_REQUIRE( !contains( my_cont, 5));
      BOOST_REQUIRE( contains( my_cont, 9));
      BOOST_REQUIRE( !contains( my_cont, 13));
   } // end scope

} // container_with_find



/// Verify that contains() works on containers using a hash function.
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( hash_container)
{

   {
      std::unordered_set< int>  my_cont;

      my_cont.insert( 42);

      BOOST_REQUIRE( !contains( my_cont, 13));
      BOOST_REQUIRE( contains( my_cont, 42));
      BOOST_REQUIRE( !contains( my_cont, 4711));
   } // end scope

   {
      std::unordered_set< int>  my_cont;

      my_cont.insert( 7373);
      my_cont.insert( 42);

      BOOST_REQUIRE( !contains( my_cont, 13));
      BOOST_REQUIRE( contains( my_cont, 42));
      BOOST_REQUIRE( !contains( my_cont, 4711));
   } // end scope

   {
      std::unordered_map< int, int>  my_cont;

      my_cont.insert( std::make_pair( 4, 16));

      BOOST_REQUIRE( !contains( my_cont, 2));
      BOOST_REQUIRE( contains( my_cont, 4));
      BOOST_REQUIRE( !contains( my_cont, 7));
   } // end scope

   {
      std::unordered_map< int, int>  my_cont;

      my_cont.insert( std::make_pair( 4, 16));
      my_cont.insert( std::make_pair( 9, 81));

      BOOST_REQUIRE( !contains( my_cont, 5));
      BOOST_REQUIRE( contains( my_cont, 9));
      BOOST_REQUIRE( !contains( my_cont, 13));
   } // end scope

} // hash_container



/// Verify that contains() works on C arrays.
///
/// @since  1.26.0, 29.04.2019
BOOST_AUTO_TEST_CASE( c_array)
{

   {
      int  arr[ 3];

      arr[ 0] = 13;
      arr[ 1] = 42;
      arr[ 2] = 4711;

      BOOST_REQUIRE( !contains( arr, 12));
      BOOST_REQUIRE( contains( arr, 13));
      BOOST_REQUIRE( !contains( arr, 14));

      BOOST_REQUIRE( !contains( arr, 41));
      BOOST_REQUIRE( contains( arr, 42));
      BOOST_REQUIRE( !contains( arr, 43));

      BOOST_REQUIRE( !contains( arr, 4710));
      BOOST_REQUIRE( contains( arr, 4711));
      BOOST_REQUIRE( !contains( arr, 4712));
   } // end scope

   {
      int  arr[ 3];

      arr[ 0] = 4711;
      arr[ 1] = 42;
      arr[ 2] = 13;

      BOOST_REQUIRE( !contains( arr, 12));
      BOOST_REQUIRE( contains( arr, 13));
      BOOST_REQUIRE( !contains( arr, 14));

      BOOST_REQUIRE( !contains( arr, 41));
      BOOST_REQUIRE( contains( arr, 42));
      BOOST_REQUIRE( !contains( arr, 43));

      BOOST_REQUIRE( !contains( arr, 4710));
      BOOST_REQUIRE( contains( arr, 4711));
      BOOST_REQUIRE( !contains( arr, 4712));
   } // end scope

   {
      int  arr[ 5];

      arr[ 0] = 13;
      arr[ 1] = 42;
      arr[ 2] = 4711;

      BOOST_REQUIRE( !contains( arr, 3, 12));
      BOOST_REQUIRE( contains( arr, 3, 13));
      BOOST_REQUIRE( !contains( arr, 3, 14));

      BOOST_REQUIRE( !contains( arr, 3, 41));
      BOOST_REQUIRE( contains( arr, 3, 42));
      BOOST_REQUIRE( !contains( arr, 3, 43));

      BOOST_REQUIRE( !contains( arr, 3, 4710));
      BOOST_REQUIRE( contains( arr, 3, 4711));
      BOOST_REQUIRE( !contains( arr, 3, 4712));
   } // end scope

   {
      int  arr[ 5];

      arr[ 0] = 4711;
      arr[ 1] = 42;
      arr[ 2] = 13;

      BOOST_REQUIRE( !contains( arr, 3, 12));
      BOOST_REQUIRE( contains( arr, 3, 13));
      BOOST_REQUIRE( !contains( arr, 3, 14));

      BOOST_REQUIRE( !contains( arr, 3, 41));
      BOOST_REQUIRE( contains( arr, 3, 42));
      BOOST_REQUIRE( !contains( arr, 3, 43));

      BOOST_REQUIRE( !contains( arr, 3, 4710));
      BOOST_REQUIRE( contains( arr, 3, 4711));
      BOOST_REQUIRE( !contains( arr, 3, 4712));
   } // end scope

} // c_array



// =====  END OF test_contains.cpp  =====

