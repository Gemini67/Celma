
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
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



using celma::containers::BinaryTree;


/// 
/// @since  x.y.z, 24.03.2017
BOOST_AUTO_TEST_CASE( single_entry_tests)
{

   BinaryTree< int>  int_tree;


   BOOST_REQUIRE( int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 0);

   int_tree.insert( 42);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 1);

   auto  tree_iter = int_tree.begin();

   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 42);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter == int_tree.end());

} // single_entry_tests



/// 
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( two_left_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 42);
   int_tree.insert( 13);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 2);

   auto  tree_iter = int_tree.begin();

   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 13);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 42);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter == int_tree.end());

} // two_left_tests



/// 
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( two_right_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 42);
   int_tree.insert( 4711);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 2);

   auto  tree_iter = int_tree.begin();

   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 42);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 4711);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter == int_tree.end());

} // two_right_tests



/// 
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( three_balanced_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 42);
   int_tree.insert( 13);
   int_tree.insert( 4711);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 3);

   auto  tree_iter = int_tree.begin();

   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 13);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 42);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 4711);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter == int_tree.end());

} // three_balanced_tests



/// 
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( three_left_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 4711);
   int_tree.insert( 42);
   int_tree.insert( 13);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 3);

   auto  tree_iter = int_tree.begin();

   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 13);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 42);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 4711);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter == int_tree.end());

} // three_left_tests



/// 
/// @since  x.y.z, 25.03.2017
BOOST_AUTO_TEST_CASE( three_right_tests)
{

   BinaryTree< int>  int_tree;


   int_tree.insert( 13);
   int_tree.insert( 42);
   int_tree.insert( 4711);

   BOOST_REQUIRE( !int_tree.empty());
   BOOST_REQUIRE( int_tree.size() == 3);

   auto  tree_iter = int_tree.begin();

   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 13);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 42);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter != int_tree.end());
   BOOST_REQUIRE( *tree_iter == 4711);

   ++tree_iter;
   BOOST_REQUIRE( tree_iter == int_tree.end());

} // three_right_tests



// =====================  END OF test_binary_tree.cpp  =====================

