
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
**    Test program for the functions of the module string_to.
**
--*/


// first include the module header to test
#include "celma/format/string_to.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE StringToTest
#include <boost/test/unit_test.hpp>



/// Test the conversion of integer values.
///
/// @since  1.17.0, 24.11.2018
BOOST_AUTO_TEST_CASE( test_ints)
{

   using celma::format::stringTo;

   std::string  str( "100");


   BOOST_REQUIRE_EQUAL( stringTo< int8_t>( str), 100);
   BOOST_REQUIRE_EQUAL( stringTo< uint8_t>( str), 100);

   str = "-100";

   BOOST_REQUIRE_EQUAL( stringTo< int8_t>( str), -100);

   str = "-128";

   BOOST_REQUIRE_EQUAL( stringTo< int8_t>( str), -128);

   str = "40000";

   BOOST_REQUIRE_EQUAL( stringTo< uint16_t>( str), 40000);

   str = "-25000";

   BOOST_REQUIRE_EQUAL( stringTo< int16_t>( str), -25000);

   str = "2935125485";

   BOOST_REQUIRE_EQUAL( stringTo< uint32_t>( str), 2935125485);

   str = "-98245782";

   BOOST_REQUIRE_EQUAL( stringTo< int32_t>( str), -98245782);

} // test_ints



/// Test the conversion of floating point values.
///
/// @since  1.17.0, 24.11.2018
BOOST_AUTO_TEST_CASE( test_floats)
{

   using celma::format::stringTo;

   std::string  str( "3.1415");


   BOOST_REQUIRE_CLOSE_FRACTION( stringTo< float>( str), 3.1415, 0.0001);
   BOOST_REQUIRE_CLOSE_FRACTION( stringTo< double>( str), 3.1415, 0.0001);
   BOOST_REQUIRE_CLOSE_FRACTION( stringTo< long double>( str), 3.1415, 0.0001);

   str = "-583743.9355763";

   BOOST_REQUIRE_CLOSE_FRACTION( stringTo< double>( str), -583743.9355763,
      0.000001);
   BOOST_REQUIRE_CLOSE_FRACTION( stringTo< long double>( str), -583743.9355763,
      0.000001);

} // test_floats



// =====  END OF test_string_to.cpp  =====

