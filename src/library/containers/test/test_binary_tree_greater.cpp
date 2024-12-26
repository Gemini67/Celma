
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template celma::containers::BinaryTree, using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/containers/binary_tree.hpp"


// Boost includes
#define BOOST_TEST_MODULE BinaryTreeTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/check_return.hpp"


using celma::containers::BinaryTree;



namespace {



/// Checks that the contents of a tree are as expected.<br>
/// Always call this function with a binary tree that contains the values
/// 13, 42 and 4711 in ascending order.
/// @param[in]  int_tree  The tree object to tet the contents of.
/// @return  \c true if all tests succeeded.
/// @since  x.y.z, 29.03.2018
template< typename C> bool checkTree3( C& int_tree)
{

   CHECK_RETURN( !int_tree.empty());
   CHECK_RETURN( int_tree.size() == 3);

   // test find for existing and non-existing values

   CHECK_RETURN( int_tree.find( 7) == int_tree.end());
   CHECK_RETURN( int_tree.find( 13) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.find( 13), 13);
   CHECK_RETURN( int_tree.find( 21) == int_tree.end());
   CHECK_RETURN( int_tree.find( 42) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.find( 42), 42);
   CHECK_RETURN( int_tree.find( 625) == int_tree.end());
   CHECK_RETURN( int_tree.find( 4711) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.find( 4711), 4711);
   CHECK_RETURN( int_tree.find( 90125) == int_tree.end());

   // test lower bounds for all positions
   CHECK_RETURN( int_tree.lower_bound( 7) == int_tree.end());

   CHECK_RETURN( int_tree.lower_bound( 13) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 13), 13);

   CHECK_RETURN( int_tree.lower_bound( 40) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 40), 13);

   CHECK_RETURN( int_tree.lower_bound( 42) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 42), 42);

   CHECK_RETURN( int_tree.lower_bound( 4000) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 4000), 42);

   CHECK_RETURN( int_tree.lower_bound( 4711) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 4711), 4711);

   CHECK_RETURN( int_tree.lower_bound( 4712) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 4712), 4711);

   // test upper bound for all positions
   CHECK_RETURN( int_tree.upper_bound( 7) == int_tree.end());
   CHECK_RETURN( int_tree.upper_bound( 13) == int_tree.end());

   CHECK_RETURN( int_tree.upper_bound( 14) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 14), 13);

   CHECK_RETURN( int_tree.upper_bound( 42) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 42), 13);

   CHECK_RETURN( int_tree.upper_bound( 4000) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 4000), 42);

   CHECK_RETURN( int_tree.upper_bound( 4711) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 4711), 42);

   CHECK_RETURN( int_tree.upper_bound( 4712) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 4712), 4711);

   // test iteration over the tree in all directions

   {
      auto  tree_iter = int_tree.begin();

      CHECK_RETURN( tree_iter != int_tree.end());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.end());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.end());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.cbegin();

      CHECK_RETURN( tree_iter != int_tree.cend());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.cend());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.cend());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter == int_tree.cend());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      CHECK_RETURN( tree_iter != int_tree.rend());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.rend());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.rend());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter == int_tree.rend());
   } // end scope

   {
      auto  tree_iter = int_tree.crbegin();

      CHECK_RETURN( tree_iter != int_tree.crend());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.crend());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.crend());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter == int_tree.crend());
   } // end scope

   auto  copy( int_tree);

   CHECK_RETURN( !copy.empty());
   CHECK_RETURN( copy.size() == 3);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      CHECK_RETURN( tree_iter != copy.end());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter != copy.end());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != copy.end());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter == copy.end());
   } // end scope

   return true;
} // checkTree3



} // namespace



/// 
/// @since  x.y.z, 27.03.2018
BOOST_AUTO_TEST_CASE( empty_tree_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   BOOST_REQUIRE( int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 0);
   BOOST_REQUIRE( int_tree.begin() == int_tree.end());
   BOOST_REQUIRE( int_tree.cbegin() == int_tree.cend());
   BOOST_REQUIRE( int_tree.rbegin() == int_tree.rend());
   BOOST_REQUIRE( int_tree.crbegin() == int_tree.crend());
   BOOST_REQUIRE( int_tree.find( 13) == int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 13) == int_tree.end());

   auto  copy( int_tree);

   BOOST_REQUIRE( copy.empty());
   BOOST_REQUIRE( copy.size() == 0);
   BOOST_REQUIRE( copy.begin() == copy.end());
   BOOST_REQUIRE( copy.cbegin() == copy.cend());
   BOOST_REQUIRE( copy.rbegin() == copy.rend());
   BOOST_REQUIRE( copy.crbegin() == copy.crend());
   BOOST_REQUIRE( copy.find( 13) == copy.end());
   BOOST_REQUIRE( copy.lower_bound( 13) == copy.end());

} // empty_tree_tests



/// 
/// @since  x.y.z, 27.03.2018
BOOST_AUTO_TEST_CASE( single_entry_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   int_tree.insert( 42);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 1);

   BOOST_REQUIRE( int_tree.find( 13) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) == int_tree.end());

   BOOST_REQUIRE( int_tree.lower_bound( 13) == int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 42) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 42) == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 43) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 43) == 42);

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.cbegin();

      BOOST_REQUIRE( tree_iter != int_tree.cend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.cend());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   {
      auto  tree_iter = int_tree.crbegin();

      BOOST_REQUIRE( tree_iter != int_tree.crend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.crend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 1);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

   copy.erase( copy.begin());

} // single_entry_tests



/// 
/// @since  x.y.z, 27.03.2018
BOOST_AUTO_TEST_CASE( two_left_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   int_tree.insert( 42);
   int_tree.insert( 13);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 2);

   BOOST_REQUIRE( int_tree.find( 9) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 13) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 21) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) == int_tree.end());

   BOOST_REQUIRE( int_tree.lower_bound( 7) == int_tree.end());
   BOOST_REQUIRE( int_tree.lower_bound( 13) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 13) == 13);
   BOOST_REQUIRE( int_tree.lower_bound( 21) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 21) == 13);
   BOOST_REQUIRE( int_tree.lower_bound( 42) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 42) == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 43) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 43) != 13);

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( *tree_iter == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.cbegin();

      BOOST_REQUIRE( tree_iter != int_tree.cend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.cend());
      BOOST_REQUIRE( *tree_iter == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.cend());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( *tree_iter == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   {
      auto  tree_iter = int_tree.crbegin();

      BOOST_REQUIRE( tree_iter != int_tree.crend());
      BOOST_REQUIRE( *tree_iter == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.crend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.crend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 2);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( *tree_iter == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // two_left_tests



/// 
/// @since  x.y.z, 27.03.2018
BOOST_AUTO_TEST_CASE( two_right_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   int_tree.insert( 42);
   int_tree.insert( 4711);

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
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.cbegin();

      BOOST_REQUIRE( tree_iter != int_tree.cend());
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.cend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.cend());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   {
      auto  tree_iter = int_tree.crbegin();

      BOOST_REQUIRE( tree_iter != int_tree.crend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.crend());
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.crend());
   } // end scope

   auto  copy( int_tree);

   BOOST_REQUIRE( !copy.empty());
   BOOST_REQUIRE( copy.size() == 2);

   // also make one iteration test with the copy
   {
      auto  tree_iter = copy.begin();

      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // two_right_tests



/// 
/// @since  x.y.z, 27.03.2018
BOOST_AUTO_TEST_CASE( three_balanced_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   int_tree.insert( 42);
   int_tree.insert( 13);
   int_tree.insert( 4711);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_balanced_tests



/// 
/// @since  x.y.z, 27.03.2018
BOOST_AUTO_TEST_CASE( three_left_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   int_tree.insert( 4711);
   int_tree.insert( 42);
   int_tree.insert( 13);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_left_tests



/// 
/// @since  x.y.z, 27.03.2018
BOOST_AUTO_TEST_CASE( three_right_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   int_tree.insert( 13);
   int_tree.insert( 42);
   int_tree.insert( 4711);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_right_tests



/// Test with a tree with 3 values, inserted in a way that results in a tree
/// with one element down the left side, and there another element on the right
/// side.
/// @since  x.y.z, 29.03.2018
BOOST_AUTO_TEST_CASE( three_left_right_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   int_tree.insert( 4711);
   int_tree.insert( 13);
   int_tree.insert( 42);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_left_right_tests



/// Test with a tree with 3 values, inserted in a way that results in a tree
/// with one element down the right side, and there another element on the left
/// side.
/// @since  x.y.z, 29.03.2018
BOOST_AUTO_TEST_CASE( three_right_left_tests)
{

   BinaryTree< int, std::greater< int>>  int_tree;


   int_tree.insert( 13);
   int_tree.insert( 4711);
   int_tree.insert( 42);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_right_left_tests



// =====  END OF test_binary_tree_greater.cpp  =====

