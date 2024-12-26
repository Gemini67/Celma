
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "big integer", using the Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/common/big_int.hpp"


// Boost includes
#define BOOST_TEST_MODULE BigIntTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/format/unit_literals.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::common::BigInt;



/// 
/// @since  x.y.z, 08.02.2023
BOOST_AUTO_TEST_CASE( basics)
{

   BigInt  my_number;


   my_number = static_cast< uint32_t>( 10);
   my_number += 10;

   std::cout << static_cast< uint64_t>( my_number) << std::endl;

   my_number += std::numeric_limits< uint32_t>::max() - 23;

   std::cout << static_cast< uint64_t>( my_number) << std::endl;

   for (int i = 0; i < 10; ++i)
   {
      std::cout << static_cast< uint64_t>( ++my_number) << std::endl;
   } // end for

   my_number = std::numeric_limits< uint64_t>::max();
   std::cout << static_cast< uint64_t>( my_number) << std::endl;

   ++my_number;

   std::cout << "length now = " << my_number.internalLength() << std::endl;
   std::cout << "value[ 0]  = " << my_number.element( 0) << std::endl;
   std::cout << "value[ 1]  = " << my_number.element( 1) << std::endl;
   std::cout << "value[ 2]  = " << my_number.element( 2) << std::endl;

   BigInt  number2( static_cast< uint32_t>( 100));

   my_number += number2;

   std::cout << "length now = " << my_number.internalLength() << std::endl;
   std::cout << "value[ 0]  = " << my_number.element( 0) << std::endl;
   std::cout << "value[ 1]  = " << my_number.element( 1) << std::endl;
   std::cout << "value[ 2]  = " << my_number.element( 2) << std::endl;

} // basics



BOOST_AUTO_TEST_CASE( shift_right)
{

   BigInt    startvalue( 0b1010101010101010101010101010101010101010101010101010101010101010);
   uint64_t  int_value = 0b1010101010101010101010101010101010101010101010101010101010101010;


   // must stop by shifting 63 bits
   // because my implementation (correctly?) returns 0,
   // while the C++/integer calculation does shiftval mod 64 == 0, i.e. does not
   // shift
   for (int i = 0; i < 64; ++i)
   {
      BigInt  copy( startvalue);
      copy >>= i;

      uint64_t  int_copy = int_value;
      int_copy >>= i;

#if 0
      std::cerr << "shifted " << i << ", expect "
         << static_cast< uint64_t>( copy) << " to be " << int_copy << std::endl;
#endif
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( copy), int_copy);
   } // end for

} // shift_right



BOOST_AUTO_TEST_CASE( multiplication)
{

   {
      BigInt  big;
      big *= 5;
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 0);
   } // end scope

   {
      BigInt  big( 0U);
      big *= 5;
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 0);
   } // end scope

   {
      BigInt  big( 5U);
      big *= 0;
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 0);
   } // end scope

   {
      BigInt  big( 1U);
      big *= 5;
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 5);
   } // end scope

   {
      BigInt  big( 5U);
      big *= 1;
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 5);
   } // end scope

   {
      BigInt  big( 123U);
      big *= 456;
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 56'088);
   } // end scope

   {
      BigInt  big( std::numeric_limits< uint32_t>::max());
      big *= std::numeric_limits< uint32_t>::max();
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big),
         18446744065119617025UL);
   } // end scope

   // test big numbers multiplication by multiply with 2 and doing left-shifts
   BigInt  big1( std::numeric_limits< uint64_t>::max());
   BigInt  big2( big1);

   for (int i = 0; i < 100; ++i)
   {
      big1 *= 2;
      big2 <<= 1;

      BOOST_REQUIRE( (big1 <=> big2) == 0);  
   } // end for

} // multiplication



/// 
/// @since  x.y.z, 18.08.2024
BOOST_AUTO_TEST_CASE( big_multiplication)
{

   {
      BigInt  big1( "0x100000001");
      BigInt  big2( "0xa0000000a");

      big1 *= big2;
      auto  result = big1.toHexString();
      BOOST_REQUIRE_EQUAL( result, "0xa000000140000000a");
   } // end scope

} // big_multiplication



/// 
/// @since  x.y.z, 05.08.2024
BOOST_AUTO_TEST_CASE( division_32bit)
{

   {
      BigInt  big;
      big.divide( 15);
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 0);
   } // end scope

   {
      BigInt  big( 14U);
      big.divide( 15);
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 0);
   } // end scope

   {
      BigInt  big( 39U);
      big.divide( 15);
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 2);
   } // end scope

   {
      BigInt  big( static_cast< uint64_t>( std::numeric_limits< uint32_t>::max()) + 1UL);
      big.divide( 10);
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 429'496'729UL);
   } // end scope

   {
      BigInt  big( 1'234'567'890'123'456UL);
      big.divide( 10);
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big), 123'456'789'012'345L);
   } // end scope

} // division_32bit



/// 
/// @since  x.y.z, 07.01.2024
BOOST_AUTO_TEST_CASE( from_string)
{

   {
      BigInt  my_number( "1234567");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( my_number), 1'234'567);
   } // end scope

   {
      BigInt  my_number( "1234567890");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( my_number), 1'234'567'890);
   } // end scope

   {
      BigInt  my_number( "1234567890123");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( my_number), 1'234'567'890'123UL);
   } // end scope

   {
      BigInt  my_number( "18446744065119617025");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( my_number),
         18'446'744'065'119'617'025UL);
   } // end scope

} // from_string



/// 
/// @since  x.y.z, 18.08.2024
BOOST_AUTO_TEST_CASE( from_hex_string)
{

   {
      BigInt  my_number( "0x10000001");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( my_number), 268'435'457);
   } // end scope

   {
      BigInt  my_number( "0xabcdef");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( my_number), 11'259'375);
   } // end scope

   {
      BigInt  my_number( "0x100000001");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( my_number), 4'294'967'297);
   } // end scope


   {
      BigInt  my_number( "0x1000 1000 1000 1000");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( my_number), 1'152'939'097'061'330'944);
   } // end scope


} // from_hex_string



/// 
/// @since  x.y.z, 05.08.2024
BOOST_AUTO_TEST_CASE( to_string)
{

   {
      BigInt       my_number( 1_KiB);
      std::string  expected( "1024");

      std::string  result = my_number.toString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( 1_MiB);
      std::string  expected( "1'048'576");

      std::string  result = my_number.toString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( 1_GiB);
      std::string  expected( "1'073'741'824");

      std::string  result = my_number.toString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( 1_EiB);
      std::string  expected( "1'152'921'504'606'846'976");

      std::string  result = my_number.toString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( 10000000000000000000UL);
      std::string  expected( "10'000'000'000'000'000'000");

      std::string  result = my_number.toString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( "123456789112233445566778899111222333444555666777888999");
      std::string  expected( "123'456'789'112'233'445'566'778'899'111'222'333'444'555'666'777'888'999");

      std::string  result = my_number.toString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

} // to_string



/// 
/// @since  x.y.z, 06.08.2024
BOOST_AUTO_TEST_CASE( to_string_grouped)
{

   {
      BigInt       my_number( 1_KiB);
      std::string  expected( "1'024");

      std::string  result = my_number.toString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( 1_MiB);
      std::string  expected( "1048576");

      std::string  result = my_number.toString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( 1_GiB);
      std::string  expected( "1073741824");

      std::string  result = my_number.toString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( 1_EiB);
      std::string  expected( "1152921504606846976");

      std::string  result = my_number.toString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( 10000000000000000000UL);
      std::string  expected( "10000000000000000000");

      std::string  result = my_number.toString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( "123456789112233445566778899111222333444555666777888999");
      std::string  expected( "123456789112233445566778899111222333444555666777888999");

      std::string  result = my_number.toString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

} // to_string_grouped



/// 
/// @since  x.y.z, 18.08.2024
BOOST_AUTO_TEST_CASE( to_hex_string)
{

   {
      BigInt       my_number( 1UL);
      std::string  expected( "0x1");

      std::string  result = my_number.toHexString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( "0x1234567890abcdef");
      std::string  expected( "0x1234567890abcdef");

      std::string  result = my_number.toHexString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( "0x1234567890abcdef1234567890abcdef");
      std::string  expected( "0x1234567890abcdef1234567890abcdef");

      std::string  result = my_number.toHexString();
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

} // to_hex_string



/// 
/// @since  x.y.z, 18.08.2024
BOOST_AUTO_TEST_CASE( to_hex_string_grouped)
{

   {
      BigInt       my_number( 1UL);
      std::string  expected( "0x1");

      std::string  result = my_number.toHexString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( "0x1234567890abcdef");
      std::string  expected( "0x12345678 90abcdef");

      std::string  result = my_number.toHexString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

   {
      BigInt       my_number( "0x1234567890abcdef1234567890abcdef");
      std::string  expected( "0x12345678 90abcdef 12345678 90abcdef");

      std::string  result = my_number.toHexString( true);
      BOOST_REQUIRE_EQUAL( expected, result);
   } // end scope

} // to_hex_string_grouped



/// 
/// @since
///    x.y.z, 12.08.2024
BOOST_AUTO_TEST_CASE( factorial_square)
{

   BigInt  bi( 1U);


   for (uint32_t i = 1; i < 70; ++i)
   {
      bi *= i;
   } // end for

   BOOST_REQUIRE_EQUAL( bi.toString( true),
      "171'122'452'428'141'311'372'468'338'881'272'839'092'270'544'893'520'369'393'648'040'923'257'279'754'140'647'424'000'000'000'000'000");

   {
      auto const  squared( celma::common::square( bi));

      // std::cout << "result = " << squared.toString() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( squared.toString(),
         "292828937250214861924095173871975771809150966033987953390866386178085"
         "627353765116225560384007505052516276929737531917510797564746850590165"
         "92823736689314689089877835776000000000000000000000000000000"));

      {
         auto const  squared2( celma::common::square( squared));

         // std::cout << "result2 = " << squared2.toString() << std::endl;
         BOOST_REQUIRE( celma::test::multilineStringCompare( squared2.toString(),
            "857487864910902731402766060312156915135028779631775846768394493166"
            "157967979917779222720544886562172368685832059529811217861602370195"
            "737432492067096272082854528812128715568994350057274761120422386453"
            "808175919242174509538407953126094992094682179460092403667554383318"
            "872152865047951638123286834128866690203720504111931052691777625522"
            "176000000000000000000000000000000000000000000000000000000000000"));
      } // end scope
   } // end scope

   auto  bi2 = celma::common::factorial( 69);

   BOOST_REQUIRE( (bi <=> bi2) == 0);

   for (uint32_t i = 69; i >= 1; --i)
   {
      bi /= i;
   } // end for

   BOOST_REQUIRE_EQUAL( bi, 1U);

} // factorial_square



/// 
/// @since  x.y.z, 25.10.2024
BOOST_AUTO_TEST_CASE( calc_power)
{

   BigInt       my_number( 2UL);
   auto const   result = power( my_number, 1014);
   std::string  result_string = result.toString( true);


   std::cout << "power( 2, 1024) = " << result_string << std::endl;


} // calc_power



// ===== test_big_int_c.cpp =====

