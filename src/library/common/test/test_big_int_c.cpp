
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023-2025 Rene Eng
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



/// 
/// @since
///    x.y.z, 21.01.2025
BOOST_AUTO_TEST_CASE( comparison)
{

   BOOST_REQUIRE( BigInt( 1U) == BigInt( 1U));
   BOOST_REQUIRE( BigInt( std::numeric_limits< uint64_t>::max())
      == BigInt( std::numeric_limits< uint64_t>::max()));

   BOOST_REQUIRE( BigInt( 2U) > BigInt( 1U));
   BOOST_REQUIRE( BigInt( 1U) < BigInt( 2U));

   BigInt  lhs( "12345678901234567890");
   BigInt  rhs( lhs);

   BOOST_REQUIRE( lhs == rhs);

   ++lhs;
   BOOST_REQUIRE( !(lhs == rhs));
   BOOST_REQUIRE( lhs > rhs);
   BOOST_REQUIRE( lhs >= rhs);

} // comparison



/// 
/// @since
///    x.y.z, 29.12.2024
BOOST_AUTO_TEST_CASE( addition)
{

   BigInt  bi( 2'000'000'000UL);
   BigInt  value( bi);

   value += bi;
   BOOST_REQUIRE_EQUAL( value, 4'000'000'000UL);

   value += bi;
   BOOST_REQUIRE_EQUAL( value, 6'000'000'000UL);

   value = std::numeric_limits< uint64_t>::max();
   BOOST_REQUIRE_EQUAL( value, 18'446'744'073'709'551'615UL);

   ++value;

   BOOST_REQUIRE_EQUAL( value.toString( true), "18'446'744'073'709'551'616");

} // addition



/// 
/// @since
///    x.y.z, 29.12.2024
BOOST_AUTO_TEST_CASE( subtraction)
{

   {
      BigInt  value( std::numeric_limits< uint64_t>::max());

      ++value;

      BOOST_REQUIRE_EQUAL( value.toString( true), "18'446'744'073'709'551'616");

      --value;

      BOOST_REQUIRE_EQUAL( value, 18'446'744'073'709'551'615UL);
   } // end scope

   {
      BigInt  v1( "26'430'668'800'000'000'000");
      BigInt  v2( "16'106'127'360'000'000'000");

      v1 -= v2;

      BOOST_REQUIRE_EQUAL( v1.toString( true), "10'324'541'440'000'000'000");
   } // end scope

} // subtraction



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



BOOST_AUTO_TEST_CASE( factorial)
{

   {
      BigInt  big80( celma::common::factorial( 80));

      BOOST_REQUIRE_EQUAL( big80.toString( true),
         "71'569'457'046'263'802'294'811'533'723'186'532'165'584'657'342'365'"
         "752'577'109'445'058'227'039'255'480'148'842'668'944'867'280'814'080'"
         "000'000'000'000'000'000");
   } // end scope

   {
      BigInt  big100( celma::common::factorial( 100));

      BOOST_REQUIRE_EQUAL( big100.toString( true),
         "93'326'215'443'944'152'681'699'238'856'266'700'490'715'968'264'381'"
         "621'468'592'963'895'217'599'993'229'915'608'941'463'976'156'518'286'"
         "253'697'920'827'223'758'251'185'210'916'864'000'000'000'000'000'000'"
         "000'000");
   } // end scope

   {
      BigInt  big101( celma::common::factorial( 101));

      BOOST_REQUIRE_EQUAL( big101.toString( true),
         "9'425'947'759'838'359'420'851'623'124'482'936'749'562'312'794'702'"
         "543'768'327'889'353'416'977'599'316'221'476'503'087'861'591'808'346'"
         "911'623'490'003'549'599'583'369'706'302'603'264'000'000'000'000'000'"
         "000'000'000");
   } // end scope

} // factorial



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
/// @since  x.y.z, 21.01.2025
BOOST_AUTO_TEST_CASE( big_division)
{

   {
      BigInt  big1( std::numeric_limits< uint64_t>::max());

      BigInt  big2( big1);
      big2 *= 12'345;
      big2 /= big1;

      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big2), 12'345);
   } // end scope

   {
      BigInt  big1( std::numeric_limits< uint64_t>::max());

      BigInt  big2( big1);
      big2 *= 123'456;

      BigInt  remainder;
      big2.divide( big1, &remainder);

      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big2), 123'456);
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( remainder), 0);
   } // end scope

   {
      BigInt  big1( "1'000'000'000'000'000'000'000'000'000");
      BigInt  big2( 30'000'000'000UL);
      BigInt  remainder;

      big1.divide( big2, &remainder);

      BOOST_REQUIRE_EQUAL( big1.toString( true),
         "33'333'333'333'333'333");
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( remainder), 10'000'000'000UL);
   } // end scope

   {
      BigInt  big100( celma::common::factorial( 100));
      BigInt  big101( celma::common::factorial( 101));

      BigInt  big_div = big101 / big100;
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( big_div), 101);
   } // end scope

} // big_division



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



/// Convert numbers into hexadecimal format.
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



/// Verify the calculation of soome factorials.
/// @since  x.y.z, 12.08.2024
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



/// Check the power calculation.
/// @since  x.y.z, 25.10.2024
BOOST_AUTO_TEST_CASE( calc_power)
{

   {
      BigInt      my_number( 2UL);
      auto const  result = power( my_number, 1024);

      BOOST_REQUIRE_EQUAL( result.toString( true),
         "179'769'313'486'231'590'772'930'519'078'902'473'361'797'697'894'230'"
         "657'273'430'081'157'732'675'805'500'963'132'708'477'322'407'536'021'"
         "120'113'879'871'393'357'658'789'768'814'416'622'492'847'430'639'474'"
         "124'377'767'893'424'865'485'276'302'219'601'246'094'119'453'082'952'"
         "085'005'768'838'150'682'342'462'881'473'913'110'540'827'237'163'350'"
         "510'684'586'298'239'947'245'938'479'716'304'835'356'329'624'224'137'"
         "216");
   } // end scope

   {
      BigInt       my_number( 317U);
      auto const   result = power( my_number, 295);

      BOOST_REQUIRE_EQUAL( result.toString( true),
         "649'355'247'170'566'107'917'986'971'663'470'655'140'988'140'153'898'"
         "034'879'413'178'966'633'911'142'623'399'569'152'547'665'149'428'500'"
         "624'559'247'703'219'976'478'756'147'008'688'356'428'918'296'988'311'"
         "723'204'260'487'988'618'895'094'124'727'648'816'535'470'032'699'613'"
         "130'753'746'482'959'235'144'056'113'456'971'360'695'121'717'355'784'"
         "978'405'468'062'599'283'144'851'612'044'333'242'867'358'235'087'173'"
         "975'209'850'142'958'927'402'162'599'200'412'108'055'103'229'930'544'"
         "235'866'476'840'118'591'382'745'513'772'118'247'407'093'086'297'272'"
         "716'246'621'030'453'875'653'126'259'746'425'303'653'384'850'776'848'"
         "964'876'557'681'037'875'537'150'272'363'641'849'452'377'673'025'519'"
         "267'176'852'149'931'198'061'091'026'552'627'194'208'649'927'449'999'"
         "745'781'382'668'900'428'301'053'339'702'792'921'890'674'908'719'008'"
         "874'906'193'035'371'750'137'921'241'369'647'529'615'802'229'962'372'"
         "737'796'958'002'264'822'229'244'964'096'954'878'927'485'782'504'059'"
         "726'065'684'645'486'414'925'493");
   } // end scope

} // calc_power



/// Test if the square root is calculated correctly.
/// @since  x.y.z, 23.01.2025
BOOST_AUTO_TEST_CASE( square_root)
{

   {
      BigInt          big1( std::numeric_limits< uint64_t>::max());
      const uint64_t  result
         = static_cast< uint64_t>( std::numeric_limits< uint32_t>::max()) + 1;

      ++big1;
      BigInt  root( celma::common::sqrt( big1));
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( root), result);

      // test if the result is still correct, even if the number is not a square
      ++big1;
      root = celma::common::sqrt( big1);
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( root), result);

      ++big1;
      root = celma::common::sqrt( big1);
      BOOST_REQUIRE_EQUAL( static_cast< uint64_t>( root), result);
   } // end scope

   // square root of a really big number
   {
      BigInt  big1( celma::common::factorial( 101U));
      BigInt  big_square( big1);


      big_square *= big1;

      BigInt  big_sqrt( celma::common::sqrt( big_square));

      BOOST_REQUIRE( big1.compare( big_sqrt) == 0);
   } // end scope

} // square_root



// ===== test_big_int_c.cpp =====

