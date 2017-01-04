
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


// Boost includes
#define BOOST_TEST_MODULE ConstexprStringFromTest
#include <boost/test/unit_test.hpp>
#include <utility>


// project includes
#include "celma/common/constexpr_string_from.hpp"


using celma::common::string_from;



/// Test that the conversion of a number is really constexpr and correct.
/// @since  0.10, 31.12.2016
BOOST_AUTO_TEST_CASE( test_constexpr_conversion)
{

   static_assert( string_from< int, 127>::value[ 0] == '1');
   static_assert( string_from< int, 127>::value[ 1] == '2');
   static_assert( string_from< int, 127>::value[ 2] == '7');

   // no really necessary anymore if the lines above compiled correctly
   BOOST_REQUIRE( ::strcmp( string_from< int, 127>::value, "127") == 0);

   static_assert( string_from< int, -127>::value[ 0] == '-');
   static_assert( string_from< int, -127>::value[ 1] == '1');
   static_assert( string_from< int, -127>::value[ 2] == '2');
   static_assert( string_from< int, -127>::value[ 3] == '7');

   // no really necessary anymore if the lines above compiled correctly
   BOOST_REQUIRE( ::strcmp( string_from< int, -127>::value, "-127") == 0);

   constexpr const char*  max_int = string_from< unsigned short int,
                                                 std::numeric_limits< unsigned short int>::max()>
                                               ::value;
   static_assert( max_int[ 0] == '6');
   static_assert( max_int[ 1] == '5');
   static_assert( max_int[ 2] == '5');
   static_assert( max_int[ 3] == '3');
   static_assert( max_int[ 4] == '5');

   // no really necessary anymore if the lines above compiled correctly
   BOOST_REQUIRE( ::strcmp( string_from< unsigned short int,
                                         std::numeric_limits< unsigned short int>::max()>
                                       ::value,
                            "65535") == 0);

} // end test_constexpr_conversion



// ==================  END OF test_constexpr_string_from.cpp  ==================

