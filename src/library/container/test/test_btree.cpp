
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template celma::container::btree, using the
**    Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/container/btree.hpp"


// Boost includes
#define BOOST_TEST_MODULE BTreeTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/check_for.hpp"


using celma::container::btree;


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



/// 
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( fill_tree)
{

   btree< int, int>  int_tree;


   for (int i = 0; i < 1000; ++i)
   {
      int_tree.insert( { i, i * i});
   } // end for

   for (int i = 0; i < 1000; ++i)
   {
      BOOST_REQUIRE( int_tree.find( i) != int_tree.end());
   } // end for

   auto const&  const_ref = int_tree;

   for (int i = 0; i < 1000; ++i)
   {
      BOOST_REQUIRE( const_ref.find( i) != const_ref.end());
   } // end for

   int  idx = 0;
   CHECK_FOR( auto iter = int_tree.begin(); iter != int_tree.end(); ++iter)
   {
      BOOST_REQUIRE_EQUAL( iter->first, idx);
      BOOST_REQUIRE_EQUAL( iter->second, idx * idx);
      ++idx;

      if (idx % 5 == 0)
      {
         iter++;
         iter--;
      } // end if
   } // end for
   CHECK_FOR_COUNT( 1000)
   
   idx = 0;
   CHECK_FOR( auto const_iter = const_ref.begin();
      const_iter != const_ref.end(); ++const_iter)
   {
      BOOST_REQUIRE_EQUAL( const_iter->first, idx);
      BOOST_REQUIRE_EQUAL( const_iter->second, idx * idx);
      ++idx;

      if (idx % 5 == 0)
      {
         const_iter++;
         const_iter--;
      } // end if
   } // end for
   CHECK_FOR_COUNT( 1000)

   auto  copy( int_tree);

   BOOST_REQUIRE_EQUAL( copy.size(), 1000);

   BOOST_REQUIRE_EQUAL( int_tree.erase( 2000), 0);

   for (int i = 0; i < 1000; ++i)
   {
      int_tree.erase( i);
   } // end for

   BOOST_REQUIRE( int_tree.empty());

   BOOST_REQUIRE_EQUAL( copy.size(), 1000);

   for (int i = 1000; i-- >0;)
   {
      auto  iter = copy.find( i);
      BOOST_REQUIRE( iter != copy.end());
      copy.erase( iter);
   } // end for

   BOOST_REQUIRE( copy.empty());

} // fill_tree



/// 
///
/// @since  x.y.z, 05.07.2020
BOOST_AUTO_TEST_CASE( fill_tree_reverse)
{

   btree< int, int>  int_tree;


   for (int i = 1000; i-- > 0;)
   {
      int_tree.insert( { i, i * i});
   } // end for

   for (int i = 0; i < 1000; ++i)
   {
      BOOST_REQUIRE( int_tree.find( i) != int_tree.end());
   } // end for

   auto const&  const_ref = int_tree;

   for (int i = 0; i < 1000; ++i)
   {
      BOOST_REQUIRE( const_ref.find( i) != const_ref.end());
   } // end for

   int  idx = 999;
   CHECK_FOR( auto riter = int_tree.rbegin(); riter != int_tree.rend(); ++riter)
   {
      BOOST_REQUIRE_EQUAL( riter->first, idx);
      BOOST_REQUIRE_EQUAL( riter->second, idx * idx);
      --idx;

      if (idx % 5 == 0)
      {
         riter--;
         riter++;
      } // end if
   } // end for
   CHECK_FOR_COUNT( 1000)
   
   idx = 999;
   CHECK_FOR( auto const_riter = const_ref.rbegin();
      const_riter != const_ref.rend(); const_riter++)
   {
      BOOST_REQUIRE_EQUAL( const_riter->first, idx);
      BOOST_REQUIRE_EQUAL( const_riter->second, idx * idx);
      --idx;

      if (idx % 5 == 0)
      {
         const_riter--;
         const_riter++;
      } // end if
   } // end for
   CHECK_FOR_COUNT( 1000)
   
} // fill_tree_reverse



// =====  END OF test_btree.cpp  =====

