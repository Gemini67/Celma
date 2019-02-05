
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test header file include
#include "celma/common/merge_sorted_cont.hpp"


// C++ Standard Library includes
#include <deque>
#include <list>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE MergeSortedContTest
#include <boost/test/unit_test.hpp>


using celma::common::MergeSortedCont;



/// Test 'merging' one single input container.
/// @since  0.10, 14.12.2016
BOOST_AUTO_TEST_CASE( test_merge_one)
{

   MergeSortedCont< int, std::vector< int>, std::list< int>>  msc;


   std::list< int>  list1 = { 1, 3, 5 };
   msc.addCont( list1);

   auto  result = msc.merge();

   BOOST_REQUIRE_EQUAL( result.size(), 3);
   BOOST_REQUIRE_EQUAL( result[ 0], 1);
   BOOST_REQUIRE_EQUAL( result[ 1], 3);
   BOOST_REQUIRE_EQUAL( result[ 2], 5);

} // test_merge_one



/// Test merging two input containers.
/// @since  0.10, 14.12.2016
BOOST_AUTO_TEST_CASE( test_merge_two)
{

   {
      MergeSortedCont< int, std::vector< int>, std::list< int>>  msc;

      std::list< int>  list1 = { 1, 2, 3 };
      msc.addCont( list1);

      std::list< int>  list2 = { 4, 5, 6 };
      msc.addCont( list2);

      auto  result = msc.merge();

      BOOST_REQUIRE_EQUAL( result.size(), 6);
      BOOST_REQUIRE_EQUAL( result[ 0], 1);
      BOOST_REQUIRE_EQUAL( result[ 1], 2);
      BOOST_REQUIRE_EQUAL( result[ 2], 3);
      BOOST_REQUIRE_EQUAL( result[ 3], 4);
      BOOST_REQUIRE_EQUAL( result[ 4], 5);
      BOOST_REQUIRE_EQUAL( result[ 5], 6);
   } // end scope


   {
      MergeSortedCont< int, std::vector< int>, std::list< int>>  msc;

      std::list< int>  list1 = { 4, 5, 6 };
      msc.addCont( list1);

      std::list< int>  list2 = { 1, 2, 3 };
      msc.addCont( list2);

      auto  result = msc.merge();

      BOOST_REQUIRE_EQUAL( result.size(), 6);
      BOOST_REQUIRE_EQUAL( result[ 0], 1);
      BOOST_REQUIRE_EQUAL( result[ 1], 2);
      BOOST_REQUIRE_EQUAL( result[ 2], 3);
      BOOST_REQUIRE_EQUAL( result[ 3], 4);
      BOOST_REQUIRE_EQUAL( result[ 4], 5);
      BOOST_REQUIRE_EQUAL( result[ 5], 6);
   } // end scope


   {
      MergeSortedCont< int, std::vector< int>, std::list< int>>  msc;

      std::list< int>  list1 = { 1, 3, 5 };
      msc.addCont( list1);

      std::list< int>  list2 = { 2, 4, 6 };
      msc.addCont( list2);

      auto  result = msc.merge();

      BOOST_REQUIRE_EQUAL( result.size(), 6);
      BOOST_REQUIRE_EQUAL( result[ 0], 1);
      BOOST_REQUIRE_EQUAL( result[ 1], 2);
      BOOST_REQUIRE_EQUAL( result[ 2], 3);
      BOOST_REQUIRE_EQUAL( result[ 3], 4);
      BOOST_REQUIRE_EQUAL( result[ 4], 5);
      BOOST_REQUIRE_EQUAL( result[ 5], 6);
   } // end scope

} // test_merge_two



/// Test merging three input containers.
/// @since  0.10, 14.12.2016
BOOST_AUTO_TEST_CASE( test_merge_three)
{

   {
      MergeSortedCont< int, std::vector< int>, std::deque< int>>  msc;

      std::deque< int>  queue1 = { 1, 2, 3 };
      msc.addCont( queue1);

      std::deque< int>  queue2 = { 4, 5, 6 };
      msc.addCont( queue2);

      std::deque< int>  queue3 = { 7, 8, 9 };
      msc.addCont( queue3);

      auto  result = msc.merge();

      BOOST_REQUIRE_EQUAL( result.size(), 9);
      BOOST_REQUIRE_EQUAL( result[ 0], 1);
      BOOST_REQUIRE_EQUAL( result[ 1], 2);
      BOOST_REQUIRE_EQUAL( result[ 2], 3);
      BOOST_REQUIRE_EQUAL( result[ 3], 4);
      BOOST_REQUIRE_EQUAL( result[ 4], 5);
      BOOST_REQUIRE_EQUAL( result[ 5], 6);
      BOOST_REQUIRE_EQUAL( result[ 6], 7);
      BOOST_REQUIRE_EQUAL( result[ 7], 8);
      BOOST_REQUIRE_EQUAL( result[ 8], 9);
   } // end scope

   {
      MergeSortedCont< int, std::vector< int>, std::deque< int>>  msc;

      std::deque< int>  queue1 = { 1, 4, 7 };
      msc.addCont( queue1);

      std::deque< int>  queue2 = { 2, 5, 8 };
      msc.addCont( queue2);

      std::deque< int>  queue3 = { 3, 6, 9 };
      msc.addCont( queue3);

      auto  result = msc.merge();

      BOOST_REQUIRE_EQUAL( result.size(), 9);
      BOOST_REQUIRE_EQUAL( result[ 0], 1);
      BOOST_REQUIRE_EQUAL( result[ 1], 2);
      BOOST_REQUIRE_EQUAL( result[ 2], 3);
      BOOST_REQUIRE_EQUAL( result[ 3], 4);
      BOOST_REQUIRE_EQUAL( result[ 4], 5);
      BOOST_REQUIRE_EQUAL( result[ 5], 6);
      BOOST_REQUIRE_EQUAL( result[ 6], 7);
      BOOST_REQUIRE_EQUAL( result[ 7], 8);
      BOOST_REQUIRE_EQUAL( result[ 8], 9);
   } // end scope

   {
      MergeSortedCont< int, std::vector< int>, std::deque< int>>  msc;

      std::deque< int>  queue1 = { 1, 2, 7 };
      msc.addCont( queue1);

      std::deque< int>  queue2 = { 3, 4, 8 };
      msc.addCont( queue2);

      std::deque< int>  queue3 = { 5, 6, 9 };
      msc.addCont( queue3);

      auto  result = msc.merge();

      BOOST_REQUIRE_EQUAL( result.size(), 9);
      BOOST_REQUIRE_EQUAL( result[ 0], 1);
      BOOST_REQUIRE_EQUAL( result[ 1], 2);
      BOOST_REQUIRE_EQUAL( result[ 2], 3);
      BOOST_REQUIRE_EQUAL( result[ 3], 4);
      BOOST_REQUIRE_EQUAL( result[ 4], 5);
      BOOST_REQUIRE_EQUAL( result[ 5], 6);
      BOOST_REQUIRE_EQUAL( result[ 6], 7);
      BOOST_REQUIRE_EQUAL( result[ 7], 8);
      BOOST_REQUIRE_EQUAL( result[ 8], 9);
   } // end scope

} // test_merge_three



// =====  END OF test_merge_sorted_cont.cpp  =====

