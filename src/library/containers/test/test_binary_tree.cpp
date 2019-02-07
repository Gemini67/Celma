
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
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
/// @since  x.y.z, 27.03.2018
bool checkTree3( BinaryTree< int>& int_tree)
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
   CHECK_RETURN( int_tree.lower_bound( 7) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 7), 13);

   CHECK_RETURN( int_tree.lower_bound( 13) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 13), 13);

   CHECK_RETURN( int_tree.lower_bound( 40) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 40), 42);

   CHECK_RETURN( int_tree.lower_bound( 42) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 42), 42);

   CHECK_RETURN( int_tree.lower_bound( 4000) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 4000), 4711);

   CHECK_RETURN( int_tree.lower_bound( 4711) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.lower_bound( 4711), 4711);

   CHECK_RETURN( int_tree.lower_bound( 4712) == int_tree.end());

   // test upper bound for all positions
   CHECK_RETURN( int_tree.upper_bound( 7) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 7), 13);

   CHECK_RETURN( int_tree.upper_bound( 13) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 13), 42);

   CHECK_RETURN( int_tree.upper_bound( 40) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 40), 42);

   CHECK_RETURN( int_tree.upper_bound( 42) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 42), 4711);

   CHECK_RETURN( int_tree.upper_bound( 4000) != int_tree.end());
   CHECK_EQUAL_RETURN( *int_tree.upper_bound( 4000), 4711);

   CHECK_RETURN( int_tree.upper_bound( 4711) == int_tree.end());

   // test iteration over the tree in all directions

   {
      auto  tree_iter = int_tree.begin();

      CHECK_RETURN( tree_iter != int_tree.end());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.end());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.end());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.cbegin();

      CHECK_RETURN( tree_iter != int_tree.cend());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.cend());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.cend());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter == int_tree.cend());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      CHECK_RETURN( tree_iter != int_tree.rend());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.rend());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.rend());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter == int_tree.rend());
   } // end scope

   {
      auto  tree_iter = int_tree.crbegin();

      CHECK_RETURN( tree_iter != int_tree.crend());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.crend());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != int_tree.crend());
      CHECK_EQUAL_RETURN( *tree_iter, 13);

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
      CHECK_EQUAL_RETURN( *tree_iter, 13);

      ++tree_iter;
      CHECK_RETURN( tree_iter != copy.end());
      CHECK_EQUAL_RETURN( *tree_iter, 42);

      ++tree_iter;
      CHECK_RETURN( tree_iter != copy.end());
      CHECK_EQUAL_RETURN( *tree_iter, 4711);

      ++tree_iter;
      CHECK_RETURN( tree_iter == copy.end());
   } // end scope

   return true;
} // checkTree3



} // namespace



/// Test that operations on an empty tree return the correct values.
/// @since  x.y.z, 02.04.2017
BOOST_AUTO_TEST_CASE( empty_tree_tests)
{

   BinaryTree< int>  int_tree;


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



/// Test with a single value in the tree.
/// @since  x.y.z, 24.03.2017
BOOST_AUTO_TEST_CASE( single_entry_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 42);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 1);

   BOOST_REQUIRE( int_tree.find( 13) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) == int_tree.end());

   BOOST_REQUIRE( int_tree.lower_bound( 13) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 13) == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 42) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 42) == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 43) == int_tree.end());

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



/// Test a tree with two values, inserted in reverse order.
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( two_left_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 42);
   int_tree.insert( 13);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 2);

   BOOST_REQUIRE( int_tree.find( 9) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 13) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 21) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 42) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4711) == int_tree.end());

   BOOST_REQUIRE( int_tree.lower_bound( 7) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 7) == 13);
   BOOST_REQUIRE( int_tree.lower_bound( 13) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 13) == 13);
   BOOST_REQUIRE( int_tree.lower_bound( 21) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 21) == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 42) != int_tree.end());
   BOOST_REQUIRE( *int_tree.lower_bound( 42) == 42);
   BOOST_REQUIRE( int_tree.lower_bound( 43) == int_tree.end());

   {
      auto  tree_iter = int_tree.begin();

      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( *tree_iter == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.cbegin();

      BOOST_REQUIRE( tree_iter != int_tree.cend());
      BOOST_REQUIRE( *tree_iter == 13);

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
      BOOST_REQUIRE( *tree_iter == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   {
      auto  tree_iter = int_tree.crbegin();

      BOOST_REQUIRE( tree_iter != int_tree.crend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.crend());
      BOOST_REQUIRE( *tree_iter == 13);

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
      BOOST_REQUIRE( *tree_iter == 13);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != copy.end());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // two_left_tests



/// Test a tree with two values, inserted in ascending order.
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( two_right_tests)
{

   BinaryTree< int>  int_tree;


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
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.end());
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.end());
   } // end scope

   {
      auto  tree_iter = int_tree.cbegin();

      BOOST_REQUIRE( tree_iter != int_tree.cend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.cend());
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.cend());
   } // end scope

   {
      auto  tree_iter = int_tree.rbegin();

      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter != int_tree.rend());
      BOOST_REQUIRE( *tree_iter == 42);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == int_tree.rend());
   } // end scope

   {
      auto  tree_iter = int_tree.crbegin();

      BOOST_REQUIRE( tree_iter != int_tree.crend());
      BOOST_REQUIRE( *tree_iter == 4711);

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
      BOOST_REQUIRE( *tree_iter == 4711);

      ++tree_iter;
      BOOST_REQUIRE( tree_iter == copy.end());
   } // end scope

} // two_right_tests



/// Test with a tree with 3 values, inserted in a way resulting in a balanced
/// binary tree.
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( three_balanced_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 42);
   int_tree.insert( 13);
   int_tree.insert( 4711);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_balanced_tests



/// Test with a tree with 3 values, inserted in a way that results in a list
/// down the left side of the tree.
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( three_left_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 4711);
   int_tree.insert( 42);
   int_tree.insert( 13);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_left_tests



/// Test with a tree with 3 values, inserted in a way that results in a list
/// down the right side of the tree.
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( three_right_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 13);
   int_tree.insert( 42);
   int_tree.insert( 4711);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_right_tests



/// Test with a tree with 3 values, inserted in a way that results in a tree
/// with one element down the left side, and there another element on the right
/// side.
/// @since  x.y.z, 28.03.2018
BOOST_AUTO_TEST_CASE( three_left_right_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 4711);
   int_tree.insert( 13);
   int_tree.insert( 42);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_left_right_tests



/// Test with a tree with 3 values, inserted in a way that results in a tree
/// with one element down the right side, and there another element on the left
/// side.
/// @since  x.y.z, 28.03.2018
BOOST_AUTO_TEST_CASE( three_right_left_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 13);
   int_tree.insert( 4711);
   int_tree.insert( 42);

   BOOST_REQUIRE( checkTree3( int_tree));

} // three_right_left_tests



/// Test that erase() deletes the correct entry, by deleting the last entry of
/// an unbalanced tree.
///
/// @since  x.y.z, 05.02.2019
BOOST_AUTO_TEST_CASE( erase_dereasing)
{

   BinaryTree< int>  int_tree;


   for (int i = 0; i < 10; ++i)
      int_tree.insert( i);

   BOOST_REQUIRE( int_tree.check());

   for (int to_del = 0; to_del < 10; ++to_del)
   {
      BOOST_REQUIRE_EQUAL( int_tree.size(), 10 - to_del);

      for (int i = 0; i < 10 - to_del; ++i)
         BOOST_REQUIRE( int_tree.find( i) != int_tree.end());

      int_tree.erase( int_tree.find( 9 - to_del));
      BOOST_REQUIRE( int_tree.check());
   } // end for

} // erase_dereasing



/// Test that erase() deletes the correct entry, by deleting the first (root)
/// entry of an unbalanced tree.
///
/// @since  x.y.z, 05.02.2019
BOOST_AUTO_TEST_CASE( erase_increasing)
{

   BinaryTree< int>  int_tree;


   for (int i = 0; i < 10; ++i)
      int_tree.insert( i);

   BOOST_REQUIRE( int_tree.check());

   for (int to_del = 0; to_del < 10; ++to_del)
   {
      BOOST_REQUIRE_EQUAL( int_tree.size(), 10 - to_del);

      for (int i = to_del; i < 10; ++i)
         BOOST_REQUIRE( int_tree.find( i) != int_tree.end());

      int_tree.erase( int_tree.find( to_del));
      BOOST_REQUIRE( int_tree.check());
   } // end for

} // erase_increasing



/// Test that erase() deletes the correct entry, by deleting the entries with
/// both left and right subtrees.
///
/// @since  x.y.z, 05.02.2019
BOOST_AUTO_TEST_CASE( erase_middle)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 3);

   int_tree.insert( 1);
   int_tree.insert( 0);
   int_tree.insert( 2);

   int_tree.insert( 5);
   int_tree.insert( 4);
   int_tree.insert( 6);

   // internally should be
   //       3
   //   1       5
   // 0   2   4   6

   for (int i = 0; i < 7; ++i)
      BOOST_REQUIRE( int_tree.find( i) != int_tree.end());

   BOOST_REQUIRE( int_tree.check());

   BOOST_REQUIRE( int_tree.erase( int_tree.find( 1)) != int_tree.end());

   BOOST_REQUIRE( int_tree.check());

   BOOST_REQUIRE( int_tree.find( 0) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 1) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 2) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 3) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 5) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 6) != int_tree.end());

   {
      auto  tree_iter = int_tree.cbegin();

      for (int i = 0; i < 7; ++i)
      {
         if (i == 1)
            continue;

         BOOST_REQUIRE( tree_iter != int_tree.cend());
         BOOST_REQUIRE( *tree_iter == i);
         ++tree_iter;
      } // end for
   } // end scope

   BOOST_REQUIRE( int_tree.erase( int_tree.find( 5)) != int_tree.end());

   BOOST_REQUIRE( int_tree.check());

   BOOST_REQUIRE( int_tree.find( 0) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 1) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 2) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 3) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 5) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 6) != int_tree.end());

   // now should be
   //       3
   //   2       6
   // 0       4
   BOOST_REQUIRE( int_tree.erase( int_tree.find( 3)) != int_tree.end());

   BOOST_REQUIRE( int_tree.check());

   BOOST_REQUIRE( int_tree.find( 0) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 1) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 2) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 3) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 5) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 6) != int_tree.end());

   BOOST_REQUIRE( int_tree.erase( int_tree.find( 4)) != int_tree.end());

   BOOST_REQUIRE( int_tree.check());

   BOOST_REQUIRE( int_tree.find( 0) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 1) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 2) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 3) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 5) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 6) != int_tree.end());

   // erasing the greatest value, must return end() iterator
   BOOST_REQUIRE( int_tree.erase( int_tree.find( 6)) == int_tree.end());

   BOOST_REQUIRE( int_tree.check());

   BOOST_REQUIRE( int_tree.find( 0) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 1) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 2) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 3) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 5) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 6) == int_tree.end());

   // erasing the greatest value, must return end() iterator
   BOOST_REQUIRE( int_tree.erase( int_tree.find( 2)) == int_tree.end());

   BOOST_REQUIRE( int_tree.check());

   BOOST_REQUIRE( int_tree.find( 0) != int_tree.end());
   BOOST_REQUIRE( int_tree.find( 1) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 2) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 3) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 4) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 5) == int_tree.end());
   BOOST_REQUIRE( int_tree.find( 6) == int_tree.end());

   BOOST_REQUIRE( int_tree.erase( int_tree.find( 0)) == int_tree.end());

   BOOST_REQUIRE( int_tree.check());
   BOOST_REQUIRE( int_tree.empty());

} // erase_middle



// =====  END OF test_binary_tree.cpp  =====

