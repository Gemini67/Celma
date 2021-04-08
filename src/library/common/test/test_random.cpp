
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "random", using the Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/common/random.hpp"


// OS/C lib includes
#include <ctime>


// Boost includes
#define BOOST_TEST_MODULE RandomTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/check_for.hpp"


using celma::common::RandomRange;



BOOST_AUTO_TEST_CASE( unix_random)
{

   RandomRange< celma::common::UnixRandom>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE( r >= -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // unix_random



BOOST_AUTO_TEST_CASE( min_std_rand0)
{

   RandomRange< celma::common::MinStdRand0>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE( r >= -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // min_std_rand0



BOOST_AUTO_TEST_CASE( min_std_rand)
{

   RandomRange< celma::common::MinStdRand>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE( r >= -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // min_std_rand



BOOST_AUTO_TEST_CASE( mt_19937)
{

   RandomRange< celma::common::Mt19937>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // mt_19337



BOOST_AUTO_TEST_CASE( mt_19937_64)
{

   RandomRange< celma::common::Mt19937_64>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // mt_19337_64



BOOST_AUTO_TEST_CASE( ranlux_24_base)
{

   RandomRange< celma::common::RanLux24Base>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // ranlux_24_base



BOOST_AUTO_TEST_CASE( ranlux_48_base)
{

   RandomRange< celma::common::RanLux48Base>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // ranlux_48_base



BOOST_AUTO_TEST_CASE( ranlux_24)
{

   RandomRange< celma::common::RanLux24>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // ranlux_24



BOOST_AUTO_TEST_CASE( ranlux_48)
{

   RandomRange< celma::common::RanLux48>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // ranlux_48



BOOST_AUTO_TEST_CASE( knuth_b)
{

   RandomRange< celma::common::KnuthB>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // knuth_b



BOOST_AUTO_TEST_CASE( default_gen)
{

   RandomRange<>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // default_gen



// =====  END OF test_random.cpp  =====

