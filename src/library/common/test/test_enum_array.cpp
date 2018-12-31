
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


// module to test header file include
#include "celma/common/enum_array.hpp"


// Boost includes
#define BOOST_TEST_MODULE EnumArrayTest
#include <boost/test/unit_test.hpp>


using celma::common::EnumArray;



/// Check that accessing the array works with both the enum values and normal
/// integer values.
///
/// @since  1.18.0, 11.12.2018
BOOST_AUTO_TEST_CASE( check_access)
{

   enum class MyEnum
   {
      one, two, three
   };

   EnumArray< int, MyEnum, 10>  ea1;

   ea1[ MyEnum::one] = 1;
   ea1[ MyEnum::two] = 2;
   ea1[ MyEnum::three] = 3;

   BOOST_REQUIRE_EQUAL( ea1[ MyEnum::one], 1);
   BOOST_REQUIRE_EQUAL( ea1[ MyEnum::two], 2);
   BOOST_REQUIRE_EQUAL( ea1[ MyEnum::three], 3);

   BOOST_REQUIRE_EQUAL( ea1[ 0], 1);
   BOOST_REQUIRE_EQUAL( ea1[ 1], 2);
   BOOST_REQUIRE_EQUAL( ea1[ 2], 3);

} // check_access



/// Check using a two-dimensional array with two different enums as indices.
///
/// @since  1.18.0, 11.12.2018
BOOST_AUTO_TEST_CASE( two_dimensional)
{

   enum class Outer
   {
      one = 1, two, three
   };

   enum class Inner
   {
      one = 1, two, three, four, five
   };

   using InnerArray = EnumArray< int, Inner, 6>;
   EnumArray< InnerArray, Outer, 4>  ea2;

   ea2[ Outer::one][ Inner::one] = 101;
   ea2[ Outer::one][ Inner::two] = 102;
   ea2[ Outer::one][ Inner::three] = 103;
   ea2[ Outer::one][ Inner::four] = 104;
   ea2[ Outer::one][ Inner::five] = 105;

   ea2[ Outer::two][ Inner::one] = 201;
   ea2[ Outer::two][ Inner::two] = 202;
   ea2[ Outer::two][ Inner::three] = 203;
   ea2[ Outer::two][ Inner::four] = 204;
   ea2[ Outer::two][ Inner::five] = 205;

   ea2[ Outer::three][ Inner::one] = 301;
   ea2[ Outer::three][ Inner::two] = 302;
   ea2[ Outer::three][ Inner::three] = 303;
   ea2[ Outer::three][ Inner::four] = 304;
   ea2[ Outer::three][ Inner::five] = 305;

   BOOST_REQUIRE_EQUAL( ea2[ Outer::one][ Inner::one], 101);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::one][ Inner::two], 102);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::one][ Inner::three], 103);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::one][ Inner::four], 104);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::one][ Inner::five], 105);

   BOOST_REQUIRE_EQUAL( ea2[ Outer::two][ Inner::one], 201);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::two][ Inner::two], 202);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::two][ Inner::three], 203);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::two][ Inner::four], 204);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::two][ Inner::five], 205);

   BOOST_REQUIRE_EQUAL( ea2[ Outer::three][ Inner::one], 301);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::three][ Inner::two], 302);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::three][ Inner::three], 303);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::three][ Inner::four], 304);
   BOOST_REQUIRE_EQUAL( ea2[ Outer::three][ Inner::five], 305);

   BOOST_REQUIRE_EQUAL( ea2[ 1][ 1], 101);
   BOOST_REQUIRE_EQUAL( ea2[ 1][ 2], 102);
   BOOST_REQUIRE_EQUAL( ea2[ 1][ 3], 103);
   BOOST_REQUIRE_EQUAL( ea2[ 1][ 4], 104);
   BOOST_REQUIRE_EQUAL( ea2[ 1][ 5], 105);

   BOOST_REQUIRE_EQUAL( ea2[ 2][ 1], 201);
   BOOST_REQUIRE_EQUAL( ea2[ 2][ 2], 202);
   BOOST_REQUIRE_EQUAL( ea2[ 2][ 3], 203);
   BOOST_REQUIRE_EQUAL( ea2[ 2][ 4], 204);
   BOOST_REQUIRE_EQUAL( ea2[ 2][ 5], 205);

   BOOST_REQUIRE_EQUAL( ea2[ 3][ 1], 301);
   BOOST_REQUIRE_EQUAL( ea2[ 3][ 2], 302);
   BOOST_REQUIRE_EQUAL( ea2[ 3][ 3], 303);
   BOOST_REQUIRE_EQUAL( ea2[ 3][ 4], 304);
   BOOST_REQUIRE_EQUAL( ea2[ 3][ 5], 305);

} // two_dimensional



/// The special functions like copy constructor etc.
///
/// @since  1.18.0, 11.12.2018
BOOST_AUTO_TEST_CASE( special_functions)
{

   enum class MyEnum
   {
      one = 1, two, three
   };

   EnumArray< int, MyEnum, 10>  ea1 = { 0, 1, 2, 3 };

   BOOST_REQUIRE_EQUAL( ea1[ MyEnum::one], 1);
   BOOST_REQUIRE_EQUAL( ea1[ MyEnum::two], 2);
   BOOST_REQUIRE_EQUAL( ea1[ MyEnum::three], 3);

   // test copy constructor
   {
      auto ea2( const_cast< const EnumArray< int, MyEnum, 10>&>( ea1));

      BOOST_REQUIRE_EQUAL( ea2[ MyEnum::one], 1);
      BOOST_REQUIRE_EQUAL( ea2[ MyEnum::two], 2);
      BOOST_REQUIRE_EQUAL( ea2[ MyEnum::three], 3);
   } // end scope

   {
      EnumArray< int, MyEnum, 10>  ea2;

      ea2 = ea1;

      BOOST_REQUIRE_EQUAL( ea2[ MyEnum::one], 1);
      BOOST_REQUIRE_EQUAL( ea2[ MyEnum::two], 2);
      BOOST_REQUIRE_EQUAL( ea2[ MyEnum::three], 3);
   } // end scope

} // special_functions



// =====  END OF test_enum_array.cpp  =====

