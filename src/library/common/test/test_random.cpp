
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



/// Create random numbers using the C random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( unix_random)
{

   RandomRange< celma::common::UnixRandom>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE( r >= -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // unix_random



/// Create random numbers using the std::minstd_rand0 random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( min_std_rand0)
{

   RandomRange< celma::common::MinStdRand0>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE( r >= -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // min_std_rand0



/// Create random numbers using the std::minstd_rand random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( min_std_rand)
{

   RandomRange< celma::common::MinStdRand>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE( r >= -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // min_std_rand



/// Create random numbers using the std::mt19937 random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( mt_19937)
{

   RandomRange< celma::common::Mt19937>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // mt_19337



/// Create random numbers using the std::mt19937_64 random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( mt_19937_64)
{

   RandomRange< celma::common::Mt19937_64>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // mt_19337_64



/// Create random numbers using the std::ranlux24_base random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( ranlux_24_base)
{

   RandomRange< celma::common::RanLux24Base>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // ranlux_24_base



/// Create random numbers using the std::ranlux48_base random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( ranlux_48_base)
{

   RandomRange< celma::common::RanLux48Base>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // ranlux_48_base



/// Create random numbers using the std::ranlux24 random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( ranlux_24)
{

   RandomRange< celma::common::RanLux24>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // ranlux_24



/// Create random numbers using the std::ranlux48 random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( ranlux_48)
{

   RandomRange< celma::common::RanLux48>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // ranlux_48



/// Create random numbers using the std::knuth_b random generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( knuth_b)
{

   RandomRange< celma::common::KnuthB>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // knuth_b



/// Create random numbers using the default (std::default_random_engine) random
/// generator.
///
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( default_gen)
{

   RandomRange<>  rr( ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // default_gen



/// Create random numbers using a customised linear congruential engine.
///
/// @since  1.45.0, 08.04.2021
BOOST_AUTO_TEST_CASE( custom_lin_cong)
{

   using my_engine = std::linear_congruential_engine< std::uint_fast32_t, 48271, 0, 2147483647>;
   using my_generator = celma::common::Custom< my_engine>;

   RandomRange< my_generator>  rr( my_engine(), ::time( nullptr), -100, 100, 1000);


   CHECK_FOR (auto r : rr)
   {
      BOOST_REQUIRE_GE( r, -100);
      BOOST_REQUIRE( r <   100);
   } CHECK_FOR_COUNT( 1000);

} // custom_lin_cong



// =====  END OF test_random.cpp  =====

