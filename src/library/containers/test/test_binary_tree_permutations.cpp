
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

   std::vector< int>  numbers{ 2, 4, 6, 8, 10, 12, 14, 16 };


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

   {
      auto  result = int_tree.lower_bound( 0);
      CHECK_RETURN( result != int_tree.end(), "lower bound 0 found");
      CHECK_RETURN( *result == 2, "lower bound correct");
   } // end scope

   {
      auto  result = int_tree.upper_bound( 0);
      CHECK_RETURN( result != int_tree.end(), "upper bound 0 found");
      CHECK_RETURN( *result == 2, "upper bound correct");
   } // end scope

   for (auto n : numbers)
   {
      auto  result = int_tree.find( n);
      CHECK_RETURN( result != int_tree.end(), "value found");
      CHECK_RETURN( *result == n, "value correct");

      auto  result_lower_bound = int_tree.lower_bound( n);
      CHECK_RETURN( result_lower_bound != int_tree.end(), "lower bound found");
      CHECK_RETURN( *result_lower_bound == n, "lower bound n correct");

      if (n < 16)
      {
         result_lower_bound = int_tree.lower_bound( n + 1);
         CHECK_RETURN( result_lower_bound != int_tree.end(), "lower bound found");
         CHECK_RETURN( *result_lower_bound == n + 2, "lower bound n + 2 correct");

         auto  result_upper_bound = int_tree.upper_bound( n);
         CHECK_RETURN( result_upper_bound != int_tree.end(), "upper bound found");
         CHECK_RETURN( *result_upper_bound == n + 2, "upper bound n correct");
      } // end if
   } // end for

   CHECK_RETURN( int_tree.upper_bound( 16) == int_tree.end(), "no upper bound for 16");
   CHECK_RETURN( int_tree.lower_bound( 17) == int_tree.end(), "no lower bound for 17");

   CHECK_RETURN( test_iteration_fwd( int_tree.begin(), int_tree.end()),
                 "iterator");

   CHECK_RETURN( test_iteration_fwd( int_tree.cbegin(), int_tree.cend()),
                 "const_iterator");

   CHECK_RETURN( test_iteration_bwd( int_tree.rbegin(), int_tree.rend()),
                 "reverse_iterator");

   CHECK_RETURN( test_iteration_bwd( int_tree.crbegin(), int_tree.crend()),
                 "const_reverse_iterator");

   auto  copy( int_tree);

   CHECK_RETURN( copy.size() == numbers.size(), "Unexpected number of elements in copy!");

   CHECK_RETURN( test_iteration_fwd( copy.begin(), copy.end()), "iterator on copy");

   CHECK_RETURN( test_iteration_bwd( copy.crbegin(), copy.crend()),
                 "const_reverse_iterator on copy");

   return true;
} // test_permutation



template< typename I> bool test_iteration_fwd( I first, I last)
{

   int  idx = 2;


   while (first != last)
   {
      CHECK_RETURN( *first == idx, "Wrong value from iteration, expected " +
                                   std::to_string( idx) + ", got " +
                                   std::to_string( *first) + "!");

      ++first;
      idx += 2;
   } // end while

   return true;
} // 



template< typename I> bool test_iteration_bwd( I first, I last)
{

   int  idx = 16;


   while (first != last)
   {
      CHECK_RETURN( *first == idx, "Wrong value from iteration, expected " +
                                   std::to_string( idx) + ", got " +
                                   std::to_string( *first) + "!");

      ++first;
      idx -= 2;
   } // end while

   return true;
} // 



} // namespace



// ================  END OF test_binary_tree_permutations.cpp  ================

