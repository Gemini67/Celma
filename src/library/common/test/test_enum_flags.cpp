
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test header file include
#include "celma/common/enum_flags.hpp"


// Boost includes
#define BOOST_TEST_MODULE EnumFlagsTest
#include <boost/test/unit_test.hpp>
#include <utility>


using celma::common::EnumFlags;


/// Test the different constructors.
/// @since  0.8, 13.11.2016
BOOST_AUTO_TEST_CASE( test_constructor)
{

   enum class MyEnum
   {
      one,
      two,
      three,
      four
   };
   
   {
      EnumFlags< MyEnum>  my_set;
      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( MyEnum::one);
      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( MyEnum::two);
      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE(   my_set & MyEnum::two);
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( MyEnum::four);
      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE(   my_set & MyEnum::four);
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( { MyEnum::one } );
      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( { MyEnum::one, MyEnum::two} );
      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE(   my_set & MyEnum::two);
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( { MyEnum::one, MyEnum::four} );
      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE(   my_set & MyEnum::four);
   } // end scope

} // test_constructor



/// Test assignment operators.
/// @since  0.8, 13.11.2016
BOOST_AUTO_TEST_CASE( test_assignment)
{

   enum class MyEnum
   {
      one,
      two,
      three,
      four
   };
   
   {
      EnumFlags< MyEnum>  my_set;
      my_set = MyEnum::one;

      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));

      my_set = MyEnum::four;

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE(   my_set & MyEnum::four);
   } // end scope

   {
      EnumFlags< MyEnum>  my_set;
      my_set = { MyEnum::one, MyEnum::three };

      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));

      my_set = EnumFlags< MyEnum>( { MyEnum::two, MyEnum::four });

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE(   my_set & MyEnum::two);
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE(   my_set & MyEnum::four);
   } // end scope

} // test_assignment



/// Test comparison.
/// @since  0.8, 13.11.2016
BOOST_AUTO_TEST_CASE( test_comparison)
{

   enum class MyEnum
   {
      one,
      two,
      three,
      four
   };
   
   {
      EnumFlags< MyEnum>  my_set( MyEnum::one);

      BOOST_REQUIRE( my_set == MyEnum::one);
      BOOST_REQUIRE( my_set != MyEnum::two);
      BOOST_REQUIRE( my_set != MyEnum::three);
      BOOST_REQUIRE( my_set != MyEnum::four);

      my_set = MyEnum::three;

      BOOST_REQUIRE( my_set != MyEnum::one);
      BOOST_REQUIRE( my_set != MyEnum::two);
      BOOST_REQUIRE( my_set == MyEnum::three);
      BOOST_REQUIRE( my_set != MyEnum::four);

      auto  value_list = { MyEnum::one, MyEnum::three };
      BOOST_REQUIRE( my_set != value_list);
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( { MyEnum::one, MyEnum::three } );

      BOOST_REQUIRE( my_set != MyEnum::one);
      BOOST_REQUIRE( my_set != MyEnum::two);
      BOOST_REQUIRE( my_set != MyEnum::three);
      BOOST_REQUIRE( my_set != MyEnum::four);

      auto  value_list1 = { MyEnum::one, MyEnum::three };

      BOOST_REQUIRE( my_set == value_list1);

      auto  value_list2 = { MyEnum::one, MyEnum::four };

      BOOST_REQUIRE( my_set != value_list2);
   } // end scope

} // test_comparison



/// Test modifiers.
/// @since  0.8, 13.11.2016
BOOST_AUTO_TEST_CASE( test_modifiers)
{

   enum class MyEnum
   {
      one,
      two,
      three,
      four
   };
   
   {
      EnumFlags< MyEnum>  my_set( MyEnum::one);
      my_set |= MyEnum::two;

      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE(   my_set & MyEnum::two);
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( MyEnum::one);
      my_set |= { MyEnum::three, MyEnum::four };

      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE(   my_set & MyEnum::four);
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( { MyEnum::one, MyEnum::two, MyEnum::three,
                                    MyEnum::four } );

      my_set &= MyEnum::three;

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( { MyEnum::one, MyEnum::two, MyEnum::three,
                                    MyEnum::four } );

      my_set &= { MyEnum::two, MyEnum::three };

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE(   my_set & MyEnum::two);
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set;

      my_set ^= MyEnum::three;

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set( { MyEnum::one, MyEnum::two, MyEnum::three,
                                    MyEnum::four } );

      my_set ^= { MyEnum::two, MyEnum::three };

      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE(   my_set & MyEnum::four);
   } // end scope

} // test_modifiers


// =======================  END OF test_enum_flags.cpp  =======================

