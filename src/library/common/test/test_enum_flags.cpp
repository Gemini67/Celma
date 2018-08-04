
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


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE EnumFlagsTest
#include <boost/test/unit_test.hpp>
#include <utility>


using celma::common::EnumFlags;


namespace {


enum class GlobalEnum
{
   left,
   right,
   top,
   bottom
};


/// Test function to check that passing (multiple) enum values works.
///
/// @param[in]  flag_set  The object with the enum values set.
/// @return  \c true if the given flag set hast at least one bit set.
/// @since  1.8.0, 26.07.2018
bool pass_enum( const EnumFlags< GlobalEnum> flag_set)
{
   return flag_set != 0;
} // pass_enum


} // namespace


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
      EnumFlags< MyEnum>  my_set{ MyEnum::one };
      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set{ MyEnum::one, MyEnum::two};
      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE(   my_set & MyEnum::two);
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set{ MyEnum::one, MyEnum::four};
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
      my_set = { MyEnum::one, MyEnum::three};

      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));

      my_set = EnumFlags< MyEnum>{ MyEnum::two, MyEnum::four};

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
      EnumFlags< MyEnum>  my_set{ MyEnum::one, MyEnum::three };

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
      EnumFlags< MyEnum>  my_set{ MyEnum::one, MyEnum::two, MyEnum::three,
                                  MyEnum::four };

      my_set &= MyEnum::three;

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set{ MyEnum::one, MyEnum::two, MyEnum::three,
                                  MyEnum::four };

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
      EnumFlags< MyEnum>  my_set{ MyEnum::one, MyEnum::two, MyEnum::three,
                                  MyEnum::four };

      my_set ^= { MyEnum::two, MyEnum::three };

      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE(   my_set & MyEnum::four);
   } // end scope

} // test_modifiers



/// Test modifiers.
/// @since  0.8, 14.11.2016
BOOST_AUTO_TEST_CASE( test_clear)
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

      my_set.clear( MyEnum::two);

      BOOST_REQUIRE(   my_set & MyEnum::one);
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));

      my_set.clear( MyEnum::one);

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE( !(my_set & MyEnum::three));
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set{ MyEnum::two, MyEnum::three};

      my_set.clear( { MyEnum::one, MyEnum::two});

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

   {
      EnumFlags< MyEnum>  my_set{ MyEnum::two, MyEnum::three};
      EnumFlags< MyEnum>  clear_set{ MyEnum::one, MyEnum::two, MyEnum::four};

      my_set.clear( clear_set);

      BOOST_REQUIRE( !(my_set & MyEnum::one));
      BOOST_REQUIRE( !(my_set & MyEnum::two));
      BOOST_REQUIRE(   my_set & MyEnum::three);
      BOOST_REQUIRE( !(my_set & MyEnum::four));
   } // end scope

} // test_clear



/// Test that passing enum values to a function that expects an enum flag
/// instance works.
/// @since  0.8, 14.11.2016
BOOST_AUTO_TEST_CASE( pass_to_function)
{

   using celma::common::operator |;

   BOOST_REQUIRE( pass_enum( GlobalEnum::top));
   BOOST_REQUIRE( pass_enum( GlobalEnum::top | GlobalEnum::left));
   BOOST_REQUIRE( pass_enum( GlobalEnum::top | GlobalEnum::left | GlobalEnum::bottom));

} // pass_to_function



/// Enum for insertion operator tests.
enum class PrintableEnum
{
   red,
   blue,
   green,
   cyan
};



/// The insertion operator that prints the symbolic name of an enum value.
std::ostream& operator <<( std::ostream& os, PrintableEnum pe)
{
   switch (pe)
   {
   case PrintableEnum::red:   return os << "red";
   case PrintableEnum::blue:  return os << "blue";
   case PrintableEnum::green: return os << "green";
   case PrintableEnum::cyan:  return os << "cyan";
   default:                   return os << "invalid";
   } // end switch
} // operator <<



/// Test printing the contents of an EnumFlags object using the insertion
/// operator.
/// @since  0.8, 14.11.2016
BOOST_AUTO_TEST_CASE( test_insertion_operator)
{

   {
      EnumFlags< PrintableEnum>  my_set;
      std::ostringstream         oss;

      oss << my_set;
      BOOST_REQUIRE_EQUAL( oss.str(), "0x0");
   } // end scope

   {
      EnumFlags< PrintableEnum>  my_set( PrintableEnum::green);
      std::ostringstream         oss;

      oss << my_set;
      BOOST_REQUIRE_EQUAL( oss.str(), "0x4 = green (2)");
   } // end scope

   {
      EnumFlags< PrintableEnum>  my_set{ PrintableEnum::red, PrintableEnum::cyan};
      std::ostringstream         oss;

      oss << my_set;
      BOOST_REQUIRE_EQUAL( oss.str(), "0x9 = red (0), cyan (3)");
   } // end scope

} // test_insertion_operator



// =====  END OF test_enum_flags.cpp  =====

