
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


// C++ Standard Library includes
#include <algorithm>
#include <vector>

#include <iostream>

// Boost includes
#define BOOST_TEST_MODULE BinaryTreeTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/check_return.hpp"


using celma::containers::BinaryTree;


namespace {


bool test_permutation( const std::vector< int>& numbers);
template< typename I> bool test_iteration_fwd( I first, I last);
template< typename I> bool test_iteration_bwd( I first, I last);


} // namespace


/// 
/// @since  x.y.z, 02.04.2017
BOOST_AUTO_TEST_CASE( permutations_tests)
{

   std::vector< int>  numbers{ 1, 2, 3, 4, 5, 6, 7, 8 };


   do
   {
      BOOST_REQUIRE( test_permutation( numbers));
   } while (std::next_permutation( numbers.begin(), numbers.end()));

} // empty_tree_tests



namespace {



bool test_permutation( const std::vector< int>& numbers)
{

#if 0
   std::cout << "numbers = ";
   for (auto n : numbers)
      std::cout << n << ",";
   std::cout << std::endl;
#endif

   BinaryTree< int>  int_tree;

   for (auto n : numbers)
      int_tree.insert( n);

   CHECK_RETURN( int_tree.size() == numbers.size(), "Unexpected number of elements in tree!");

   CHECK_RETURN( test_iteration_fwd( int_tree.begin(), int_tree.end()),
                 "iterator");

   CHECK_RETURN( test_iteration_fwd( int_tree.cbegin(), int_tree.cend()),
                 "const_iterator");

   CHECK_RETURN( test_iteration_bwd( int_tree.rbegin(), int_tree.rend()),
                 "reverse_iterator");

   CHECK_RETURN( test_iteration_bwd( int_tree.crbegin(), int_tree.crend()),
                 "const_reverse_iterator");

   return true;
} // test_permutation



template< typename I> bool test_iteration_fwd( I first, I last)
{

   int  idx = 1;


   while (first != last)
   {
      CHECK_RETURN( *first == idx, "Wrong value from iteration, expected " +
                                   std::to_string( idx) + ", got " +
                                   std::to_string( *first) + "!");

      ++first;
      ++idx;
   } // end while

   return true;
} // 



template< typename I> bool test_iteration_bwd( I first, I last)
{

   int  idx = 8;


   while (first != last)
   {
      CHECK_RETURN( *first == idx, "Wrong value from iteration, expected " +
                                   std::to_string( idx) + ", got " +
                                   std::to_string( *first) + "!");

      ++first;
      --idx;
   } // end while

   return true;
} // 



} // namespace



// ================  END OF test_binary_tree_permutations.cpp  ================

