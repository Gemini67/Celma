
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test header file include
#include "celma/common/constexpr_string_concat.hpp"


// Boost includes
#define BOOST_TEST_MODULE ConstexprStringConcatTest
#include <boost/test/unit_test.hpp>


using celma::common::string_concat;



/// Test that the string concatenation functions are really constexpr and
/// correct.
///
/// @since  0.10, 02.01.2017
BOOST_AUTO_TEST_CASE( test_constexpr_concat)
{

   {
      auto constexpr const  str = string_concat( "solitude");

      static_assert( str[ 0] == 's');
      static_assert( str[ 4] == 't');
      static_assert( str[ 7] == 'e');
      static_assert( str[ 8] == '\0');

      // not really necessary anymore, but hey:
      BOOST_REQUIRE( ::strcmp( str.data(), "solitude") == 0);
   } // end scope

   {
      auto constexpr const  str = string_concat( "hello ", "world");

      static_assert( str[ 0] == 'h');
      static_assert( str[ 5] == ' ');
      static_assert( str[ 6] == 'w');
      static_assert( str[ 10] == 'd');

      // not really necessary anymore, but hey:
      BOOST_REQUIRE( ::strcmp( str.data(), "hello world") == 0);
   } // end scope

   {
      auto constexpr const  str = string_concat( "hello ", "world");
      auto constexpr const  str2 = string_concat( str, ", how", " are", " you");

      static_assert( str2[ 13] == 'h');

      // not really necessary anymore, but hey:
      BOOST_REQUIRE( ::strcmp( str2.data(), "hello world, how are you") == 0);
   } // end scope

} // test_constexpr_concat



#define  NAME(x)  #x



/// Test converting a string created by the preprocessor.
///
/// @since  x.y.z, 21.04.2020
BOOST_AUTO_TEST_CASE( concat_pp_string)
{

   constexpr int myvar = -1;
   auto constexpr const  str = string_concat( NAME( myvar));

   static_assert( str[ 0] == 'm');
   static_assert( str[ 2] == 'v');
   static_assert( str[ 4] == 'r');
   static_assert( str[ 5] == '\0');

   // not really necessary anymore, but hey:
   BOOST_REQUIRE( ::strcmp( str.data(), "myvar") == 0);
   BOOST_REQUIRE( myvar == -1);

} // concat_pp_string



template< typename T> constexpr auto testTypeName( const T&)
{
   return string_concat( "unknown");
} // testTypeName


#define  TYPE_NAME( T) \
   constexpr auto testTypeName( const T&) \
   { \
      return string_concat( NAME( T)); \
   }

TYPE_NAME( int)
TYPE_NAME( std::string)



/// Test converting a type name.
///
/// @since  x.y.z, 21.04.2020
BOOST_AUTO_TEST_CASE( concat_typename)
{

   {
      constexpr int         my_int = -1;
      auto constexpr const  str = testTypeName( my_int);

      static_assert( str[ 0] == 'i');
      static_assert( str[ 1] == 'n');
      static_assert( str[ 2] == 't');
      static_assert( str[ 3] == '\0');

      // not really necessary anymore, but hey:
      BOOST_REQUIRE( ::strcmp( str.data(), "int") == 0);
      BOOST_REQUIRE( my_int == -1);
   } // end scope

   {
      std::string           my_string( "hello world");
      auto constexpr const  str = testTypeName( my_string);

      static_assert( str[ 0] == 's');
      static_assert( str[ 3] == ':');
      static_assert( str[ 5] == 's');
      static_assert( str[ 10] == 'g');
      static_assert( str[ 11] == '\0');

      // not really necessary anymore, but hey:
      BOOST_REQUIRE( ::strcmp( str.data(), "std::string") == 0);
      BOOST_REQUIRE( my_string == "hello world");
   } // end scope

} // concat_typename



// =====  END OF test_constexpr_string_concat.cpp  =====

