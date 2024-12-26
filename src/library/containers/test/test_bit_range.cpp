
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template celma::containers::BitRange<>, using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/containers/bit_range.hpp"


// Boost includes
#define BOOST_TEST_MODULE BitRangeTest
#include <boost/test/unit_test.hpp>


using celma::containers::BitRange;



/// 
/// @since
///    x.y.z, 26.06.2018
BOOST_AUTO_TEST_CASE( empty_range_set)
{

   BitRange< 10, 20>  br;


   BOOST_REQUIRE_EQUAL( br.count(), 0);
   BOOST_REQUIRE_EQUAL( br.size(), 10);
   BOOST_REQUIRE( br.none());
   BOOST_REQUIRE( !br.all());
   BOOST_REQUIRE( !br.any());

   BOOST_REQUIRE( !br[ 10]);
   BOOST_REQUIRE( !br[ 19]);

   BOOST_REQUIRE_EQUAL( br.to_string(), "00000000000000000000");
   BOOST_REQUIRE_EQUAL( br.to_ulong(), 0);
   BOOST_REQUIRE_EQUAL( br.to_ullong(), 0);

   {
      auto const  copy( br);

      BOOST_REQUIRE_EQUAL( copy.count(), 0);
      BOOST_REQUIRE( copy.none());
      BOOST_REQUIRE( !copy.all());
      BOOST_REQUIRE( !copy.any());

      BOOST_REQUIRE( !copy[ 10]);
      BOOST_REQUIRE( !copy[ 19]);

      BOOST_REQUIRE( br == copy);
   } // end scope

   {
      auto  copy( br);

      copy.flip();

      BOOST_REQUIRE_EQUAL( copy.count(), 10);

      copy.reset();

      BOOST_REQUIRE_EQUAL( copy.count(), 0);
   } // end scope

} // empty_range_set



/// 
/// @since
///    x.y.z, 27.06.2018
BOOST_AUTO_TEST_CASE( single_bit)
{

   BitRange< 10, 20>  br;


   br.set( 15);

   BOOST_REQUIRE_EQUAL( br.count(), 1);
   BOOST_REQUIRE( !br.none());
   BOOST_REQUIRE( !br.all());
   BOOST_REQUIRE( br.any());

   BOOST_REQUIRE( !br[ 10]);
   BOOST_REQUIRE( br[ 15]);
   BOOST_REQUIRE( !br[ 19]);

   BOOST_REQUIRE( !br.test( 10));
   BOOST_REQUIRE( br.test( 15));

   BOOST_REQUIRE_EQUAL( br.to_string(), "00001000000000000000");
   BOOST_REQUIRE_EQUAL( br.to_ulong(), 0x8000);
   BOOST_REQUIRE_EQUAL( br.to_ullong(), 0x8000);

   br.reset( 15);

   BOOST_REQUIRE_EQUAL( br.count(), 0);
   BOOST_REQUIRE( br.none());
   BOOST_REQUIRE( !br.all());
   BOOST_REQUIRE( !br.any());

} // single_bit



/// 
/// @since
///    x.y.z, 27.06.2018
BOOST_AUTO_TEST_CASE( boundary_bits)
{

   BitRange< 10, 20>  br;


   br.set( 10);
   br.set( 19);

   BOOST_REQUIRE_EQUAL( br.count(), 2);
   BOOST_REQUIRE_EQUAL( br.size(), 10);
   BOOST_REQUIRE( !br.none());
   BOOST_REQUIRE( !br.all());
   BOOST_REQUIRE( br.any());

   BOOST_REQUIRE( br[ 10]);
   BOOST_REQUIRE( !br[ 15]);
   BOOST_REQUIRE( br[ 19]);

   BOOST_REQUIRE_EQUAL( br.to_string(), "10000000010000000000");
   BOOST_REQUIRE_EQUAL( br.to_ulong(), 0x80400);
   BOOST_REQUIRE_EQUAL( br.to_ullong(), 0x80400);

   {
      auto  copy( br);

      BOOST_REQUIRE( br == copy);

      copy.reset();

      BOOST_REQUIRE( br != copy);

      BOOST_REQUIRE_EQUAL( copy.count(), 0);
      BOOST_REQUIRE( copy.none());
      BOOST_REQUIRE( !copy.all());
      BOOST_REQUIRE( !copy.any());
   } // end scope

   {
      auto  copy( br);

      copy.flip( 15);

      BOOST_REQUIRE_EQUAL( copy.count(), 3);

      copy.flip( 15);

      BOOST_REQUIRE_EQUAL( copy.count(), 2);
   } // end scope

   br.reset( 10);

   BOOST_REQUIRE_EQUAL( br.count(), 1);
   BOOST_REQUIRE( !br.none());
   BOOST_REQUIRE( !br.all());
   BOOST_REQUIRE( br.any());

   BOOST_REQUIRE( !br[ 10]);
   BOOST_REQUIRE( !br[ 15]);
   BOOST_REQUIRE( br[ 19]);

} // boundary_bits



/// 
/// @since
///    x.y.z, 27.06.2018
BOOST_AUTO_TEST_CASE( setters)
{

   BitRange< 10, 20>  br;


   br[ 15] = true;

   BOOST_REQUIRE_EQUAL( br.count(), 1);
   BOOST_REQUIRE( !br.none());
   BOOST_REQUIRE( !br.all());
   BOOST_REQUIRE( br.any());

   BOOST_REQUIRE( br[ 15]);

} // setters



/// Test the copy-constructor that allows to copy from a BitRange with a
/// different range.
/// @since
///    x.y.z, 28.06.2018
BOOST_AUTO_TEST_CASE( intersect_copy)
{

   // copy-construct with non-intersecting ranges
   {
      BitRange< 10, 20>  br10_20;

      br10_20[ 15] = true;
      br10_20[ 19] = true;

      BitRange< 20, 40>  br20_40( br10_20);

      BOOST_REQUIRE_EQUAL( br20_40.count(), 0);
   } // end scope

   // copy-construct with intersecting ranges
   {
      BitRange< 10, 30>  br10_30;

      br10_30[ 15] = true;
      br10_30[ 22] = true;
      br10_30[ 27] = true;

      BitRange< 20, 40>  br20_40( br10_30);

      BOOST_REQUIRE_EQUAL( br20_40.count(), 2);
      BOOST_REQUIRE( br20_40[ 22]);
      BOOST_REQUIRE( br20_40[ 27]);
   } // end scope

   // copy-construct with sub-range
   {
      BitRange< 10, 30>  br10_30;

      br10_30[ 12] = true;
      br10_30[ 15] = true;
      br10_30[ 22] = true;
      br10_30[ 27] = true;

      BitRange< 15, 25>  br15_25( br10_30);

      BOOST_REQUIRE_EQUAL( br15_25.count(), 2);
      BOOST_REQUIRE( br15_25[ 15]);
      BOOST_REQUIRE( br15_25[ 22]);
   } // end scope

} // intersect_copy



/// Test the assignment operator that allows to copy from a BitRange with a
/// different range.
/// @since
///    x.y.z, 28.06.2018
BOOST_AUTO_TEST_CASE( intersect_assign)
{

   // assign with non-intersecting ranges
   {
      BitRange< 10, 20>  br10_20;

      br10_20[ 15] = true;
      br10_20[ 19] = true;

      BitRange< 20, 40>  br20_40;
      br20_40 = br10_20;

      BOOST_REQUIRE_EQUAL( br20_40.count(), 0);
   } // end scope

   // assign with intersecting ranges
   {
      BitRange< 10, 30>  br10_30;

      br10_30[ 15] = true;
      br10_30[ 22] = true;
      br10_30[ 27] = true;

      BitRange< 20, 40>  br20_40;
      br20_40 = br10_30;

      BOOST_REQUIRE_EQUAL( br20_40.count(), 2);
      BOOST_REQUIRE( br20_40[ 22]);
      BOOST_REQUIRE( br20_40[ 27]);
   } // end scope

   // copy-construct with sub-range
   {
      BitRange< 10, 30>  br10_30;

      br10_30[ 12] = true;
      br10_30[ 15] = true;
      br10_30[ 22] = true;
      br10_30[ 27] = true;

      BitRange< 15, 25>  br15_25( br10_30);

      BOOST_REQUIRE_EQUAL( br15_25.count(), 2);
      BOOST_REQUIRE( br15_25[ 15]);
      BOOST_REQUIRE( br15_25[ 22]);
   } // end scope

} // intersect_assign



// =====  END OF test_bit_range.cpp  =====

