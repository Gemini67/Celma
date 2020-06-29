
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template celma::container::BinaryTree, using the
**    Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/container/binary_tree.hpp"


// C++ Standard Library includes
#include <algorithm>
#include <iostream>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE BinaryTreePermutationsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/check_return.hpp"


using celma::container::BinaryTree;


namespace {


bool test_permutation( const std::vector< int>& numbers);
template< typename I> bool test_iteration_fwd( I first, I last);
template< typename I> bool test_iteration_bwd( I first, I last);


} // namespace


/// Creates all permutation of a sequence of numbers, and then checks the
/// binary tree with each of the permutation.<br>
/// The idea is course to test all possible combinations of inserting numbers
/// and storing them at the correct position in the tree.
/// @since
///    x.y.z, 02.04.2017
BOOST_AUTO_TEST_CASE( permutations_tests)
{

   std::vector< int>  numbers{ 2, 4, 6, 8, 10, 12, 14, 16 };


   do
   {
      BOOST_REQUIRE( test_permutation( numbers));
   } while (std::next_permutation( numbers.begin(), numbers.end()));

} // permutations_tests



namespace {



/// Tests the binary tree for the given sequence of numbers.
/// @param[in]  numbers
///    The numbers in the next sequence to test.
/// @return
///    \c true if all tests succeeded.
/// @since
///    x.y.z, 02.04.2017
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

   CHECK_RETURN_MSG( int_tree.size() == numbers.size(), "Unexpected number of elements in tree!");

   {
      auto  result = int_tree.lower_bound( 0);
      CHECK_RETURN_MSG( result != int_tree.end(), "lower bound 0 found");
      CHECK_RETURN_MSG( *result == 2, "lower bound correct");
   } // end scope

   {
      auto  result = int_tree.upper_bound( 0);
      CHECK_RETURN_MSG( result != int_tree.end(), "upper bound 0 found");
      CHECK_RETURN_MSG( *result == 2, "upper bound correct");
   } // end scope

   for (auto n : numbers)
   {
      auto  result = int_tree.find( n);
      CHECK_RETURN_MSG( result != int_tree.end(), "value found");
      CHECK_RETURN_MSG( *result == n, "value correct");

      auto  result_lower_bound = int_tree.lower_bound( n);
      CHECK_RETURN_MSG( result_lower_bound != int_tree.end(), "lower bound found");
      CHECK_RETURN_MSG( *result_lower_bound == n, "lower bound n correct");

      if (n < 16)
      {
         result_lower_bound = int_tree.lower_bound( n + 1);
         CHECK_RETURN_MSG( result_lower_bound != int_tree.end(), "lower bound found");
         CHECK_RETURN_MSG( *result_lower_bound == n + 2, "lower bound n + 2 correct");

         auto  result_upper_bound = int_tree.upper_bound( n);
         CHECK_RETURN_MSG( result_upper_bound != int_tree.end(), "upper bound found");
         CHECK_RETURN_MSG( *result_upper_bound == n + 2, "upper bound n correct");
      } // end if
   } // end for

   CHECK_RETURN_MSG( int_tree.upper_bound( 16) == int_tree.end(), "no upper bound for 16");
   CHECK_RETURN_MSG( int_tree.lower_bound( 17) == int_tree.end(), "no lower bound for 17");

   CHECK_RETURN_MSG( test_iteration_fwd( int_tree.begin(), int_tree.end()),
                 "iterator");

   CHECK_RETURN_MSG( test_iteration_fwd( int_tree.cbegin(), int_tree.cend()),
                 "const_iterator");

   CHECK_RETURN_MSG( test_iteration_bwd( int_tree.rbegin(), int_tree.rend()),
                 "reverse_iterator");

   CHECK_RETURN_MSG( test_iteration_bwd( int_tree.crbegin(), int_tree.crend()),
                 "const_reverse_iterator");

   auto  copy( int_tree);

   CHECK_EQUAL_RETURN( copy.size(), numbers.size());

   CHECK_RETURN_MSG( test_iteration_fwd( copy.begin(), copy.end()), "iterator on copy");

   CHECK_RETURN_MSG( test_iteration_bwd( copy.crbegin(), copy.crend()),
                 "const_reverse_iterator on copy");

   return true;
} // test_permutation



/// Checks that all values are found in the correct order when iterating over
/// the tree.
/// @tparam  I
///    The type of the iterator to use.
/// @param[in]  first
///    Iterator pointing to the first elemenz.
/// @param[in]  last
///    Iterator pointing behind the lasz elemen.
/// @return
///    \c true if the values were in the correct order.
/// @since
///    x.y.z, 02.04.2017
template< typename I> bool test_iteration_fwd( I first, I last)
{

   int  idx = 2;


   while (first != last)
   {
      CHECK_RETURN_MSG( *first == idx, "Wrong value from iteration, expected " +
                                   std::to_string( idx) + ", got " +
                                   std::to_string( *first) + "!");

      ++first;
      idx += 2;
   } // end while

   CHECK_RETURN_MSG( idx == 18, "Not all values found!");

   return true;
} // test_iteration_fwd



/// Checks that all values are found in the correct order when iterating
/// backwards over the tree.
/// @tparam  I
///    The type of the iterator to use.
/// @param[in]  first
///    Pointer to the element to start iterating with (last element).
/// @param[in]  last
///    Pointer to the end of the sequence (here: pointer before the first
///    element).
/// @return
///    \c true if the values were in the correct order.
/// @since
///    x.y.z, 02.04.2017
template< typename I> bool test_iteration_bwd( I first, I last)
{

   int  idx = 16;


   while (first != last)
   {
      CHECK_RETURN_MSG( *first == idx, "Wrong value from iteration, expected " +
                                   std::to_string( idx) + ", got " +
                                   std::to_string( *first) + "!");

      ++first;
      idx -= 2;
   } // end while

   CHECK_RETURN_MSG( idx == 0, "Not all values found!");

   return true;
} // test_iteration_bwd



} // namespace


// =====  END OF test_binary_tree_permutations.cpp  =====

