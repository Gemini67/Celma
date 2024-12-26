
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template celma::containers::btree, using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/containers/btree.hpp"


// Boost includes
#define BOOST_TEST_MODULE BTreeTest
#include <boost/test/unit_test.hpp>



using celma::containers::btree;


/// 
/// @since  x.y.z, 26.03.2018
BOOST_AUTO_TEST_CASE( empty_tree_tests)
{

   btree< int, int>  int_tree;


   BOOST_REQUIRE( int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 0);
   BOOST_REQUIRE( int_tree.begin() == int_tree.end());
   BOOST_REQUIRE( int_tree.rbegin() == int_tree.rend());
   BOOST_REQUIRE( int_tree.find( 13) == int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 13) == int_tree.end());

   auto  copy( int_tree);

   BOOST_REQUIRE( copy.empty());
   BOOST_REQUIRE( copy.size() == 0);
   BOOST_REQUIRE( copy.begin() == copy.end());
   BOOST_REQUIRE( copy.rbegin() == copy.rend());
   BOOST_REQUIRE( copy.find( 13) == copy.end());
   BOOST_REQUIRE( copy.lower_bound( 13) == copy.end());

} // empty_tree_tests



/// 
/// @since  x.y.z, 26.03.2018
BOOST_AUTO_TEST_CASE( single_entry_tests)
{

   btree< int, int>  int_tree;


   int_tree.insert( 42, 42);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 1);

   BOOST_REQUIRE( !int_tree.exists( 13));
   BOOST_REQUIRE( int_tree.find( 13) == int_tree.end());
   BOOST_REQUIRE( int_tree.exists( 42));
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( !int_tree.exists( 4711));
   BOOST_REQUIRE( int_tree.find( 4711) == int_tree.end());

   BOOST_REQUIRE( int_tree.lower_bound( 13) != int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 13)->first == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 42)->first == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 43) == int_tree.end());

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 1);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

   copy.erase( copy.begin());

} // single_entry_tests



/// 
/// @since  x.y.z, 26.03.2018
BOOST_AUTO_TEST_CASE( two_left_tests)
{

   btree< int, int>  int_tree;


   int_tree.insert( 42, 42);
   int_tree.insert( 13, 13);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 2);

   BOOST_REQUIRE( int_tree.find( 9) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 13) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 21) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) == int_tree.end());

   BOOST_REQUIRE( int_tree.lower_bound( 7) != int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 7)->first == 13);
   BOOST_REQUIRE( int_tree.lower_bound( 13) != int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 13)->first == 13);
   BOOST_REQUIRE( int_tree.lower_bound( 21) != int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 21)->first == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 42)->first == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 43) == int_tree.end());

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 2);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // two_left_tests



/// 
/// @since  x.y.z, 26.03.2018
BOOST_AUTO_TEST_CASE( two_right_tests)
{

   btree< int, int>  int_tree;


   int_tree.insert( 42, 42);
   int_tree.insert( 4711, 4711);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 2);

   BOOST_REQUIRE( int_tree.find( 13) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 625) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 90125) == int_tree.end());

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 2);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // two_right_tests



/// 
/// @since  x.y.z, 26.03.2018
BOOST_AUTO_TEST_CASE( three_balanced_tests)
{

   btree< int, int>  int_tree;


   int_tree.insert( 42, 42);
   int_tree.insert( 13, 13);
   int_tree.insert( 4711, 4711);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 3);

   BOOST_REQUIRE( int_tree.find( 7) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 13) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 21) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 625) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 90125) == int_tree.end());

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 3);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // three_balanced_tests



/// 
/// @since  x.y.z, 26.03.2018
BOOST_AUTO_TEST_CASE( three_left_tests)
{

   btree< int, int>  int_tree;


   int_tree.insert( 4711, 4711);
   int_tree.insert( 42, 42);
   int_tree.insert( 13, 13);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 3);

   BOOST_REQUIRE( int_tree.find( 7) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 13) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 21) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 625) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 90125) == int_tree.end());

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 3);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // three_left_tests



/// 
/// @since  x.y.z, 26.03.2018
BOOST_AUTO_TEST_CASE( three_right_tests)
{

   btree< int, int>  int_tree;


   int_tree.insert( 13, 13);
   int_tree.insert( 42, 42);
   int_tree.insert( 4711, 4711);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 3);

   BOOST_REQUIRE( int_tree.find( 7) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 13) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 21) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 625) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 90125) == int_tree.end());

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 3);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( tree_iter->first == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // three_right_tests



// =====  END OF test_btree.cpp  =====

