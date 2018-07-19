
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// project includes
#include "celma/common/bitset_iterator.hpp"


// Boost includes
#define BOOST_TEST_MODULE AdjustTest
#include <boost/test/unit_test.hpp>



/// Test that the iterator works correctly on an empty bitset.
/// @since  1.7.0, 17.07.2018
BOOST_AUTO_TEST_CASE( empty_bitset)
{

   std::bitset< 10>  bs;
   auto              iter = std::begin( bs);


   BOOST_REQUIRE( iter == std::end( bs));

} // empty_bitset



/// Test that the iterator works correctly on a full bitset.
/// @since  1.7.0, 17.07.2018
BOOST_AUTO_TEST_CASE( full_bitset)
{

   std::bitset< 5>  bs;


   bs.flip();

   auto  iter = std::begin( bs);


   BOOST_REQUIRE( iter != std::end( bs));
   BOOST_REQUIRE_EQUAL( *iter, 0);

   ++iter;
   BOOST_REQUIRE( iter != std::end( bs));
   BOOST_REQUIRE_EQUAL( *iter, 1);

   iter++;
   BOOST_REQUIRE( iter != std::end( bs));
   BOOST_REQUIRE_EQUAL( *iter, 2);

   {
      auto  copy( iter);
      --copy;
      copy++;
      BOOST_REQUIRE( iter == copy);
   } // end scope

   ++iter;
   BOOST_REQUIRE( iter != std::end( bs));
   BOOST_REQUIRE_EQUAL( *iter, 3);

   iter++;
   BOOST_REQUIRE( iter != std::end( bs));
   BOOST_REQUIRE_EQUAL( *iter, 4);

   ++iter;
   BOOST_REQUIRE( iter == std::end( bs));

} // full_bitset



/// Tests the bitset iterator with a range based for.
/// @since  1.7.0, 17.07.2018
BOOST_AUTO_TEST_CASE( range_based_for)
{

   std::bitset< 10>  bs;


   bs[ 1] = true;
   bs[ 8] = true;

   int  check = 0;

   for (auto bs_iter : bs)
   {
      if (check == 0)
         BOOST_REQUIRE_EQUAL( bs_iter, 1);
      else
         BOOST_REQUIRE_EQUAL( bs_iter, 8);
      ++check;
   } // end for

} // range_based_for



/// Test that the reverse iterator works correctly on an empty bitset.
/// @since  1.7.0, 17.07.2018
BOOST_AUTO_TEST_CASE( empty_bitset_reverse)
{

   std::bitset< 10>  bs;
   auto              iter = std::rbegin( bs);


   BOOST_REQUIRE( iter == std::rend( bs));

} // empty_bitset_reverse



/// Test that the reverse iterator works correctly on a full bitset.
/// @since  1.7.0, 17.07.2018
BOOST_AUTO_TEST_CASE( full_bitset_reverse)
{

   std::bitset< 5>  bs;


   bs.flip();

   auto  iter = std::rbegin( bs);


   BOOST_REQUIRE( iter != std::rend( bs));
   BOOST_REQUIRE_EQUAL( *iter, 4);

   ++iter;
   BOOST_REQUIRE( iter != std::rend( bs));
   BOOST_REQUIRE_EQUAL( *iter, 3);

   iter++;
   BOOST_REQUIRE( iter != std::rend( bs));
   BOOST_REQUIRE_EQUAL( *iter, 2);

   {
      auto  copy( iter);
      --copy;
      copy++;
      BOOST_REQUIRE( iter == copy);
   } // end scope

   ++iter;
   BOOST_REQUIRE( iter != std::rend( bs));
   BOOST_REQUIRE_EQUAL( *iter, 1);

   iter++;
   BOOST_REQUIRE( iter != std::rend( bs));
   BOOST_REQUIRE_EQUAL( *iter, 0);

   ++iter;
   BOOST_REQUIRE( iter == std::rend( bs));

} // full_bitset_reverse



// =====  END OF test_bitset_iterator.cpp  =====

