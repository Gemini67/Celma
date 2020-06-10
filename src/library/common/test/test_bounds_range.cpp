
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "bounds range", using the Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/common/bounds_range.hpp"


// C++ Standard Library include
#include <map>


// Boost includes
#define BOOST_TEST_MODULE BoundRangeTest
#include <boost/test/unit_test.hpp>


using celma::common::bounds_range;



/// Search range with one value.
///
/// @since  1.29.0, 22.06.2019
BOOST_AUTO_TEST_CASE( single_value_range)
{

   std::multimap< int, int>  mm;


   mm.insert( { 1, 1});
   mm.insert( { 2, 2});
   mm.insert( { 2, 4});
   mm.insert( { 3, 3});
   mm.insert( { 3, 9});
   mm.insert( { 3, 27});

   int  i = 0;
   for ([[maybe_unused]] auto it : bounds_range( mm, 0))
   {
      BOOST_REQUIRE( false);
   } // end for

   for (auto it : bounds_range( mm, 1))
   {
      BOOST_REQUIRE_EQUAL( it.first, 1);
      if (i == 0)
         BOOST_REQUIRE_EQUAL( it.second, 1);
      else
         BOOST_REQUIRE( i < 1);
      ++i;
   } // end for

   i = 0;
   for (auto it : bounds_range( mm, 2))
   {
      BOOST_REQUIRE_EQUAL( it.first, 2);
      if (i == 0)
         BOOST_REQUIRE_EQUAL( it.second, 2);
      else if (i == 1)
         BOOST_REQUIRE_EQUAL( it.second, 4);
      else
         BOOST_REQUIRE( i < 2);
      ++i;
   } // end for

   i = 0;
   for (auto it : bounds_range( mm, 3))
   {
      BOOST_REQUIRE_EQUAL( it.first, 3);
      if (i == 0)
         BOOST_REQUIRE_EQUAL( it.second, 3);
      else if (i == 1)
         BOOST_REQUIRE_EQUAL( it.second, 9);
      else if (i == 2)
         BOOST_REQUIRE_EQUAL( it.second, 27);
      else
         BOOST_REQUIRE( i < 3);
      ++i;
   } // end for

   i = 0;
   for ([[maybe_unused]] auto it : bounds_range( mm, 4))
   {
      BOOST_REQUIRE( false);
   } // end for

} // single_value_range



/// Search range with two values.
///
/// @since  1.29.0, 23.06.2019
BOOST_AUTO_TEST_CASE( two_value_range)
{

   std::multimap< int, int>  mm;


   mm.insert( { 1, 1});
   mm.insert( { 2, 2});
   mm.insert( { 2, 4});
   mm.insert( { 3, 3});
   mm.insert( { 3, 9});
   mm.insert( { 3, 27});

   int  i = 0;
   for ([[maybe_unused]] auto it : bounds_range( mm, -1, 0))
   {
      BOOST_REQUIRE( false);
   } // end for

   for (auto it : bounds_range( mm, 0, 1))
   {
      BOOST_REQUIRE_EQUAL( it.first, 1);
      if (i == 0)
         BOOST_REQUIRE_EQUAL( it.second, 1);
      else
         BOOST_REQUIRE( i < 1);
      ++i;
   } // end for

   i = 0;
   for (auto it : bounds_range( mm, 1, 1))
   {
      BOOST_REQUIRE_EQUAL( it.first, 1);
      if (i == 0)
         BOOST_REQUIRE_EQUAL( it.second, 1);
      else
         BOOST_REQUIRE( i < 1);
      ++i;
   } // end for

   i = 0;
   for (auto it : bounds_range( mm, 1, 2))
   {
      if (i == 0)
      {
         BOOST_REQUIRE_EQUAL( it.first, 1);
         BOOST_REQUIRE_EQUAL( it.second, 1);
      } else if (i == 1)
      {
         BOOST_REQUIRE_EQUAL( it.first, 2);
         BOOST_REQUIRE_EQUAL( it.second, 2);
      } else if (i == 2)
      {
         BOOST_REQUIRE_EQUAL( it.first, 2);
         BOOST_REQUIRE_EQUAL( it.second, 4);
      } else
      {
         BOOST_REQUIRE( i < 3);
      } // end if
      ++i;
   } // end for

   i = 0;
   for (auto it : bounds_range( mm, 3, 4))
   {
      BOOST_REQUIRE_EQUAL( it.first, 3);
      if (i == 0)
         BOOST_REQUIRE_EQUAL( it.second, 3);
      else if (i == 1)
         BOOST_REQUIRE_EQUAL( it.second, 9);
      else if (i == 2)
         BOOST_REQUIRE_EQUAL( it.second, 27);
      else
         BOOST_REQUIRE( i < 3);
      ++i;
   } // end for

   i = 0;
   for ([[maybe_unused]] auto it : bounds_range( mm, 4, 10))
   {
      BOOST_REQUIRE( false);
   } // end for

} // two_value_range



// =====  END OF test_bounds_range.cpp  =====
