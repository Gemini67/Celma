
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
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

   auto constexpr const  str = string_concat( "hello ", "world");

   static_assert( str[ 0] == 'h');
   static_assert( str[ 5] == ' ');
   static_assert( str[ 6] == 'w');
   static_assert( str[ 10] == 'd');

   // not really necessary anymore, but hey:
   BOOST_REQUIRE( ::strcmp( str.data(), "hello world") == 0);

   auto constexpr const  str2 = string_concat( str, ", how", " are", " you");

   static_assert( str2[ 13] == 'h');

   // not really necessary anymore, but hey:
   BOOST_REQUIRE( ::strcmp( str2.data(), "hello world, how are you") == 0);

} // test_constexpr_concat



// =====  END OF test_constexpr_string_concat.cpp  =====

