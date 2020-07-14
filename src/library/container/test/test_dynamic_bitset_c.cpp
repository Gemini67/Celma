
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the class celma::container::DynamicBitset, using the
**    Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/container/dynamic_bitset.hpp"


// C++ Standard Library includes
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE DynamicBitsetTest
#include <boost/test/unit_test.hpp>


#include "celma/test/check_for.hpp"


BOOST_TEST_DONT_PRINT_LOG_VALUE( celma::container::DynamicBitset)
BOOST_TEST_DONT_PRINT_LOG_VALUE( celma::container::DynamicBitset::iterator)
BOOST_TEST_DONT_PRINT_LOG_VALUE( celma::container::DynamicBitset::reverse_iterator)


using celma::container::DynamicBitset;



/// Verify some error cases with a dynamic bitset.
///
/// @since  1.37.0, 10.06.2020
BOOST_AUTO_TEST_CASE( errors)
{

   {
      DynamicBitset  dbs( 100);

      dbs.set( 80);
      BOOST_REQUIRE_THROW( dbs.to_ulong(), std::overflow_error);
   } // end scope

   {
      DynamicBitset  dbs( 10);
      auto const     copy( dbs);

      BOOST_REQUIRE_THROW( copy[ 20], std::out_of_range);
   } // end scope

} // errors



/// Test some operations with a dynamic bitset where 0 or none bit is set.
///
/// @since  1.37.0, 08.06.2020
BOOST_AUTO_TEST_CASE( test_one)
{

   DynamicBitset  dbs( 5);


   BOOST_REQUIRE( dbs.none());
   BOOST_REQUIRE( !dbs.any());
   BOOST_REQUIRE( !dbs.all());

   BOOST_REQUIRE_EQUAL( dbs.size(), 5);
   BOOST_REQUIRE_EQUAL( dbs.count(), 0);
   BOOST_REQUIRE_THROW( dbs.test( 6), std::out_of_range);

   dbs.set( 2);

   BOOST_REQUIRE( !dbs.none());
   BOOST_REQUIRE( dbs.any());
   BOOST_REQUIRE( !dbs.all());

   BOOST_REQUIRE_EQUAL( dbs.size(), 5);
   BOOST_REQUIRE_EQUAL( dbs.count(), 1);
   BOOST_REQUIRE( dbs.test( 2));
   BOOST_REQUIRE( dbs[ 2]);
   BOOST_REQUIRE_THROW( dbs.test( 6), std::out_of_range);
   BOOST_REQUIRE_EQUAL( dbs.to_string(), "00100");

   auto const copy = dbs;
   BOOST_REQUIRE( copy == dbs);
   BOOST_REQUIRE( copy[ 2]);

   dbs[ 20] = true;
   BOOST_REQUIRE( dbs[ 20]);
   BOOST_REQUIRE( !(copy == dbs));
  
} // test_one



/// Set and flips some bits in the dynamic bitset.
///
/// @since  1.37.0, 10.06.2020
BOOST_AUTO_TEST_CASE( set_flip)
{

   DynamicBitset  dbs( 10);


   dbs.set();
   BOOST_REQUIRE_EQUAL( dbs.count(), 10);

   dbs.reset();
   BOOST_REQUIRE_EQUAL( dbs.count(), 0);

   dbs.set( 1);
   dbs.set( 3);
   dbs.set( 5);
   dbs.set( 7);
   dbs.set( 9);

   BOOST_REQUIRE_EQUAL( dbs.count(), 5);
   BOOST_REQUIRE( dbs[ 1]);
   BOOST_REQUIRE( dbs[ 3]);
   BOOST_REQUIRE( dbs[ 7]);
   BOOST_REQUIRE( dbs[ 9]);
   BOOST_REQUIRE_EQUAL( dbs.to_string(), "001010101010");

   auto const copy( ~dbs);
   dbs.flip();
   BOOST_REQUIRE_EQUAL( dbs.count(), 7);
   BOOST_REQUIRE_EQUAL( dbs, copy);

   dbs.reset( 4);
   dbs.flip( 6);
   BOOST_REQUIRE_EQUAL( dbs.count(), 5);

   dbs.reset( 14);
   dbs.flip( 25);
   BOOST_REQUIRE_EQUAL( dbs.count(), 6);

} // set_flip



/// Test the logic operations with two dynamic bitsets with the same size.
///
/// @since  1.37.0, 10.06.2020
BOOST_AUTO_TEST_CASE( logic_same_size)
{

   DynamicBitset  dbs1( 5);
   DynamicBitset  dbs2( 5);


   dbs1.set( 0);
   dbs1.set( 2);

   dbs2.set( 1);
   dbs2.set( 2);

   {
      auto  copy( dbs2);
      copy |= dbs1;

      BOOST_REQUIRE_EQUAL( copy.count(), 3);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 7);

      auto  ored = dbs2 | dbs1;
      BOOST_REQUIRE_EQUAL( ored.count(), 3);
      BOOST_REQUIRE_EQUAL( ored.to_ulong(), 7);
   } // end scope
   
   {
      auto  copy( dbs2);
      copy &= dbs1;

      BOOST_REQUIRE_EQUAL( copy.count(), 1);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 4);

      auto  anded = dbs2 & dbs1;
      BOOST_REQUIRE_EQUAL( anded.count(), 1);
      BOOST_REQUIRE_EQUAL( anded.to_ulong(), 4);
   } // end scope
   
   {
      auto  copy( dbs2);
      copy ^= dbs1;

      BOOST_REQUIRE_EQUAL( copy.count(), 2);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 3);

      auto  xored = dbs2 ^ dbs1;
      BOOST_REQUIRE_EQUAL( xored.count(), 2);
      BOOST_REQUIRE_EQUAL( xored.to_ulong(), 3);
   } // end scope
   
} // logic_same_size



/// Test the logic operations with two dynamic bitsets with different sizes.
///
/// @since  1.37.0, 10.06.2020
BOOST_AUTO_TEST_CASE( logic_different_size)
{

   DynamicBitset  dbs1( 5);
   DynamicBitset  dbs2( 15);


   dbs1.set( 0);
   dbs1.set( 2);

   dbs2.set(  1);
   dbs2.set(  2);
   dbs2.set( 10);
   dbs2.set( 12);

   {
      auto copy( dbs1);
      copy |= dbs2;

      BOOST_REQUIRE_EQUAL( copy.count(), 5);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 5127);

      auto  ored = dbs1 | dbs2;
      BOOST_REQUIRE_EQUAL( copy, ored);
   } // end scope
   
   {
      auto copy( dbs1);
      copy &= dbs2;

      BOOST_REQUIRE_EQUAL( copy.count(), 1);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 4);

      auto  anded = dbs1 & dbs2;
      BOOST_REQUIRE_EQUAL( copy, anded);
   } // end scope
   
   {
      auto copy( dbs1);
      copy ^= dbs2;

      BOOST_REQUIRE_EQUAL( copy.count(), 4);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 5123);

      auto  xored = dbs1 ^ dbs2;
      BOOST_REQUIRE_EQUAL( copy, xored);
   } // end scope
   
   {
      auto copy( dbs2);
      copy |= dbs1;

      BOOST_REQUIRE_EQUAL( copy.count(), 5);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 5127);

      auto  ored = dbs2 | dbs1;
      BOOST_REQUIRE_EQUAL( copy, ored);
   } // end scope
   
   {
      auto copy( dbs2);
      copy &= dbs1;

      BOOST_REQUIRE_EQUAL( copy.count(), 1);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 4);

      auto  anded = dbs2 & dbs1;
      BOOST_REQUIRE_EQUAL( copy, anded);
   } // end scope
   
   {
      auto copy( dbs2);
      copy ^= dbs1;

      BOOST_REQUIRE_EQUAL( copy.count(), 4);
      BOOST_REQUIRE_EQUAL( copy.to_ulong(), 5123);

      auto  xored = dbs2 ^ dbs1;
      BOOST_REQUIRE_EQUAL( copy, xored);
   } // end scope
   
} // logic_different_size



/// Test the shift operations of the dynamic bitset.
///
/// @since  1.37.0, 10.06.2020
BOOST_AUTO_TEST_CASE( shift)
{

   {
      DynamicBitset  dbs( 0);

      dbs <<= 4;
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 0);
      BOOST_REQUIRE_EQUAL( dbs.count(), 0);

      dbs >>= 4;
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 0);
      BOOST_REQUIRE_EQUAL( dbs.count(), 0);

      dbs[ 4] = true;

      auto const copy( dbs << 0);
      dbs <<= 0;
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 16);
      BOOST_REQUIRE_EQUAL( dbs.count(), 1);
      BOOST_REQUIRE_EQUAL( dbs, copy);

      auto const copy2( dbs >> 0);
      dbs >>= 0;
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 16);
      BOOST_REQUIRE_EQUAL( dbs.count(), 1);
      BOOST_REQUIRE_EQUAL( dbs, copy);

   } // end scope

   {
      DynamicBitset  dbs( 5);
      unsigned long  result = 1;

      dbs.set( 0);

      for (int i = 0; i < 10; ++i)
      {
         auto copy( dbs << 1);
         result <<= 1;
         dbs <<= 1;

         BOOST_REQUIRE_EQUAL( dbs.to_ulong(), result);
         BOOST_REQUIRE_EQUAL( dbs.count(), 1);
         BOOST_REQUIRE_EQUAL( dbs, copy);
      } // end for
   } // end scope

   {
      DynamicBitset  dbs( 5);
      unsigned long  result = 5;

      dbs.set( 0);
      dbs.set( 2);

      for (int i = 0; i < 20; ++i)
      {
         auto copy( dbs << 1);
         result <<= 1;
         dbs <<= 1;

         BOOST_REQUIRE_EQUAL( dbs.to_ulong(), result);
         BOOST_REQUIRE_EQUAL( dbs.count(), 2);
         BOOST_REQUIRE_EQUAL( dbs, copy);
      } // end for
   } // end scope

   {
      DynamicBitset  dbs( 11);
      unsigned long  result = 1 << 10;

      dbs.set( 10);

      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), result);

      for (int i = 0; i < 10; ++i)
      {
         auto copy( dbs >> 1);
         result >>= 1;
         dbs >>= 1;

         BOOST_REQUIRE_EQUAL( dbs.to_ulong(), result);
         BOOST_REQUIRE_EQUAL( dbs.count(), 1);
         BOOST_REQUIRE_EQUAL( dbs, copy);
      } // end for
   } // end scope

   {
      DynamicBitset  dbs( 50);
      unsigned long  result = 5L << 40;

      dbs.set( 42);
      dbs.set( 40);

      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), result);

      for (int i = 0; i < 38; ++i)
      {
         auto copy( dbs >> 1);
         result >>= 1;
         dbs >>= 1;

         BOOST_REQUIRE_EQUAL( dbs.to_ulong(), result);
         BOOST_REQUIRE_EQUAL( dbs.count(), 2);
         BOOST_REQUIRE_EQUAL( dbs, copy);
      } // end for
   } // end scope

} // shift



/// Test the resize operation.
///
/// @since  1.37.0, 16.06.2020
BOOST_AUTO_TEST_CASE( resize)
{

   DynamicBitset  dbs( 5);


   dbs.resize( 8, true);

   BOOST_REQUIRE_EQUAL( dbs.size(), 8);
   BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 224);  // 128 + 64 + 32

   dbs.resize( 5, true);

   BOOST_REQUIRE_EQUAL( dbs.size(), 5);
   BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 0);

} // resize



/// Test constructors that allow different data types.
///
/// @since  1.37.0, 16.06.2020
BOOST_AUTO_TEST_CASE( conversion_constructor)
{

   {
      std::bitset< 6>  bs;

      bs[ 3] = 1;
      bs[ 5] = 1;

      DynamicBitset  dbs( bs);

      BOOST_REQUIRE_EQUAL( dbs.count(), 2);
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 40);
   } // end scope


   {
      std::vector< bool>  vb;

      vb.resize( 6);

      vb[ 3] = 1;
      vb[ 5] = 1;

      DynamicBitset  dbs( vb);

      BOOST_REQUIRE_EQUAL( dbs.count(), 2);
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 40);
   } // end scope

   {
      DynamicBitset  dbs( []()
      {
         std::vector< bool>  vb;

         vb.resize( 6);

         vb[ 3] = 1;
         vb[ 5] = 1;
         return vb;
      }());

      BOOST_REQUIRE_EQUAL( dbs.count(), 2);
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 40);
   } // end scope

} // conversion_constructor



/// Test assignments.
///
/// @since  1.37.0, 16.06.2020
BOOST_AUTO_TEST_CASE( assignment)
{

   {
      DynamicBitset  bs( 5);

      bs[ 1] = true;
      bs[ 3] = true;

      auto  copy( bs);
      BOOST_REQUIRE_EQUAL( copy, bs);
   } // end scope

   {
      DynamicBitset  copy( []()
      {
         DynamicBitset  bs( 5);

         bs[ 1] = true;
         bs[ 3] = true;
         return bs;
      }());

      BOOST_REQUIRE_EQUAL( copy.count(), 2);
      BOOST_REQUIRE_EQUAL( copy[ 1], true);
      BOOST_REQUIRE_EQUAL( copy[ 3], true);
   } // end scope

   {
      std::bitset< 6>  bs;

      bs[ 3] = 1;
      bs[ 5] = 1;

      DynamicBitset  dbs( 8);

      dbs[ 4] = true;
      dbs[ 7] = true;

      dbs = bs;

      BOOST_REQUIRE_EQUAL( dbs.count(), 2);
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 40);
   } // end scope

   {
      std::vector< bool>  vb;

      vb.resize( 6);

      vb[ 3] = 1;
      vb[ 5] = 1;

      DynamicBitset  dbs( 8);

      dbs[ 4] = true;
      dbs[ 7] = true;

      dbs = vb;

      BOOST_REQUIRE_EQUAL( dbs.count(), 2);
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 40);
   } // end scope

   {
      DynamicBitset  dbs( 8);

      dbs[ 4] = true;
      dbs[ 7] = true;

      dbs = []()
      {
         std::vector< bool>  vb;

         vb.resize( 6);

         vb[ 3] = 1;
         vb[ 5] = 1;
         return vb;
      }();

      BOOST_REQUIRE_EQUAL( dbs.count(), 2);
      BOOST_REQUIRE_EQUAL( dbs.to_ulong(), 40);
   } // end scope

} // conversion_constructor



/// Test the iterators.
///
/// @since  1.37.0, 20.06.2020
BOOST_AUTO_TEST_CASE( iterate_empty)
{

   DynamicBitset  dbs( 8);


   CHECK_FOR (auto dbi : dbs)
   {
      BOOST_REQUIRE( dbi == 0);
   } // end for
   CHECK_FOR_NEVER;

   auto const& dbs_r = dbs;

   CHECK_FOR (auto dbi : dbs_r)
   {
      BOOST_REQUIRE( dbi == 0);
   } // end for
   CHECK_FOR_NEVER;

   CHECK_FOR (auto riter = dbs.rbegin(); riter != dbs.rend(); ++riter)
   {
      BOOST_REQUIRE( riter == dbs.rend());
   } // end for
   CHECK_FOR_NEVER;

   CHECK_FOR (auto riter = dbs_r.rbegin(); riter != dbs_r.rend(); ++riter)
   {
      BOOST_REQUIRE( riter == dbs_r.end());
   } // end for
   CHECK_FOR_NEVER;

} // iterate_empty



/// Test that iterating past the end does not crash.
///
/// @since  1.37.0, 20.06.2020
BOOST_AUTO_TEST_CASE( exceed_end)
{

   {
      DynamicBitset  dbs( 8);
      auto           iter = dbs.begin();


      BOOST_REQUIRE_EQUAL( iter, dbs.end());
      ++iter;
      BOOST_REQUIRE_EQUAL( iter, dbs.end());
      iter++;
      BOOST_REQUIRE_EQUAL( iter, dbs.end());

      --iter;
      BOOST_REQUIRE_EQUAL( iter, dbs.end());
      iter--;
      BOOST_REQUIRE_EQUAL( iter, dbs.end());

      auto  riter = dbs.rbegin();

      BOOST_REQUIRE_EQUAL( riter, dbs.rend());
      ++riter;
      BOOST_REQUIRE_EQUAL( riter, dbs.rend());
      riter++;
      BOOST_REQUIRE_EQUAL( riter, dbs.rend());

      --riter;
      BOOST_REQUIRE_EQUAL( riter, dbs.rend());
      riter--;
      BOOST_REQUIRE_EQUAL( riter, dbs.rend());
   } // end scope

   {
      DynamicBitset  dbs( 8);

      dbs[ 0] = true;

      auto  iter = dbs.begin();

      --iter;
      BOOST_REQUIRE_EQUAL( iter, dbs.end());

      iter = dbs.begin();
      ++iter;
      BOOST_REQUIRE_EQUAL( iter, dbs.end());
   } // end scope

   {
      DynamicBitset  dbs( 8);

      dbs[ 7] = true;

      auto  iter = dbs.begin();

      iter--;
      BOOST_REQUIRE_EQUAL( iter, dbs.end());

      iter = dbs.begin();
      iter++;
      BOOST_REQUIRE_EQUAL( iter, dbs.end());
   } // end scope

   {
      DynamicBitset  dbs( 8);

      dbs[ 0] = true;

      auto  riter = dbs.rbegin();

      --riter;
      BOOST_REQUIRE_EQUAL( riter, dbs.rend());

      riter = dbs.rbegin();
      ++riter;
      BOOST_REQUIRE_EQUAL( riter, dbs.rend());
   } // end scope

   {
      DynamicBitset  dbs( 8);

      dbs[ 7] = true;

      auto  riter = dbs.rbegin();

      riter--;
      BOOST_REQUIRE_EQUAL( riter, dbs.rend());

      riter = dbs.rbegin();
      riter++;
      BOOST_REQUIRE_EQUAL( riter, dbs.rend());
   } // end scope

} // exceed_end



/// Test iterating over a dynamic bitset where one flag in the middle is set.
///
/// @since  1.37.0, 21.06.2020
BOOST_AUTO_TEST_CASE( iterate_one)
{

   DynamicBitset  dbs( 20);


   dbs[ 10] = true;

   CHECK_FOR (auto dbi : dbs)
   {
      BOOST_REQUIRE( dbi == 10);
   } // end for
   CHECK_FOR_ONCE;

   auto const& dbs_r = dbs;

   CHECK_FOR (auto dbi : dbs_r)
   {
      BOOST_REQUIRE( dbi == 10);
   } // end for
   CHECK_FOR_ONCE;

   CHECK_FOR (auto riter = dbs.rbegin(); riter != dbs.rend(); ++riter)
   {
      BOOST_REQUIRE( *riter == 10);
   } // end for
   CHECK_FOR_ONCE;

   CHECK_FOR (auto riter = dbs_r.rbegin(); riter != dbs_r.rend(); ++riter)
   {
      BOOST_REQUIRE( *riter == 10);
   } // end for
   CHECK_FOR_ONCE;

} // iterate_one



/// Test iterating over a dynamic bitset where the first flag is set.
///
/// @since  1.37.0, 21.06.2020
BOOST_AUTO_TEST_CASE( iterate_first)
{

   DynamicBitset  dbs( 20);


   dbs[ 0] = true;

   CHECK_FOR (auto dbi : dbs)
   {
      BOOST_REQUIRE( dbi == 0);
   } // end for
   CHECK_FOR_ONCE;

   auto const& dbs_r = dbs;

   CHECK_FOR (auto dbi : dbs_r)
   {
      BOOST_REQUIRE( dbi == 0);
   } // end for
   CHECK_FOR_ONCE;

   CHECK_FOR (auto riter = dbs.rbegin(); riter != dbs.rend(); ++riter)
   {
      BOOST_REQUIRE( *riter == 0);
   } // end for
   CHECK_FOR_ONCE;

   CHECK_FOR (auto riter = dbs_r.rbegin(); riter != dbs_r.rend(); ++riter)
   {
      BOOST_REQUIRE( *riter == 0);
   } // end for
   CHECK_FOR_ONCE;

} // iterate_first



/// Test iterating over a dynamic bitset where the first flag is set.
///
/// @since  1.37.0, 28.06.2020
BOOST_AUTO_TEST_CASE( const_iterate_first)
{

   DynamicBitset  dbs( 20);


   dbs[ 0] = true;

   auto const  cdbs( dbs);

   CHECK_FOR (auto dbi = cdbs.cbegin(); dbi != cdbs.cend(); ++dbi)
   {
      BOOST_REQUIRE( *dbi == 0);
   } // end for
   CHECK_FOR_ONCE;

   auto const& cdbs_r = cdbs;

   CHECK_FOR (auto dbi : cdbs_r)
   {
      BOOST_REQUIRE( dbi == 0);
   } // end for
   CHECK_FOR_ONCE;

   CHECK_FOR (auto riter = dbs.crbegin(); riter != dbs.crend(); ++riter)
   {
      BOOST_REQUIRE( *riter == 0);
   } // end for
   CHECK_FOR_ONCE;

   CHECK_FOR (auto riter = cdbs_r.crbegin(); riter != cdbs_r.crend(); ++riter)
   {
      BOOST_REQUIRE( *riter == 0);
   } // end for
   CHECK_FOR_ONCE;

} // const_iterate_first



/// Test iterating over a dynamic bitset where the last flag is set.
///
/// @since  1.37.0, 21.06.2020
BOOST_AUTO_TEST_CASE( iterate_last)
{

   DynamicBitset  dbs( 20);


   dbs[ 19] = true;

   CHECK_FOR (auto dbi : dbs)
   {
      BOOST_REQUIRE( dbi == 19);
   } // end for
   CHECK_FOR_ONCE;

   auto const& dbs_r = dbs;

   CHECK_FOR (auto dbi : dbs_r)
   {
      BOOST_REQUIRE( dbi == 19);
   } // end for
   CHECK_FOR_ONCE;

   CHECK_FOR (auto riter = dbs.rbegin(); riter != dbs.rend(); ++riter)
   {
      BOOST_REQUIRE( *riter == 19);
   } // end for
   CHECK_FOR_ONCE;

   CHECK_FOR (auto riter = dbs_r.rbegin(); riter != dbs_r.rend(); ++riter)
   {
      BOOST_REQUIRE( *riter == 19);
   } // end for
   CHECK_FOR_ONCE;

} // iterate_last



/// Test iterating over a dynamic bitset where the last flag is set.
///
/// @since  1.37.0, 21.06.2020
BOOST_AUTO_TEST_CASE( iterate_first_middle_last)
{

   DynamicBitset  dbs( 20);


   dbs[  0] = true;
   dbs[ 10] = true;
   dbs[ 19] = true;

   CHECK_FOR (auto dbi : dbs)
   {
      BOOST_REQUIRE( (dbi == 0) || (dbi == 10) || (dbi == 19));
   } // end for
   CHECK_FOR_COUNT( 3);

   auto const& dbs_r = dbs;

   CHECK_FOR (auto dbi : dbs_r)
   {
      BOOST_REQUIRE( (dbi == 0) || (dbi == 10) || (dbi == 19));
   } // end for
   CHECK_FOR_COUNT( 3);

   CHECK_FOR (auto riter = dbs.rbegin(); riter != dbs.rend(); ++riter)
   {
      BOOST_REQUIRE( (*riter == 0) || (*riter == 10) || (*riter == 19));
   } // end for
   CHECK_FOR_COUNT( 3);

   CHECK_FOR (auto riter = dbs_r.rbegin(); riter != dbs_r.rend(); ++riter)
   {
      BOOST_REQUIRE( (*riter == 0) || (*riter == 10) || (*riter == 19));
   } // end for
   CHECK_FOR_COUNT( 3);

} // iterate_first_middle_last



/// Test iterating in both ways.
///
/// @since  1.37.0, 25.06.2020
BOOST_AUTO_TEST_CASE( iterate_back_and_forth)
{

   DynamicBitset  dbs( 20);


   dbs[  0] = true;
   dbs[ 10] = true;
   dbs[ 19] = true;

   auto  iter = dbs.begin();
   ++iter;

   BOOST_REQUIRE_EQUAL( *iter, 10);

   --iter;
   ++iter;
   BOOST_REQUIRE_EQUAL( *iter, 10);

   iter++;
   iter--;
   BOOST_REQUIRE_EQUAL( *iter, 10);

   iter--;
   BOOST_REQUIRE_EQUAL( iter, dbs.begin());

   auto  riter = dbs.rbegin();
   ++riter;

   BOOST_REQUIRE_EQUAL( *riter, 10);

   --riter;
   ++riter;
   BOOST_REQUIRE_EQUAL( *riter, 10);

   riter++;
   riter--;
   BOOST_REQUIRE_EQUAL( *riter, 10);

   riter--;
   BOOST_REQUIRE_EQUAL( riter, dbs.rbegin());

} // iterate_back_and_forth



// =====  END OF test_dynamic_bitset_c.cpp  =====

