
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "suffix percentage", using the Boost.Test
**    framework.
**
--*/


// module to test headerfile include
#include "celma/common/suffix_percentage.hpp"


// Boost includes
#define BOOST_TEST_MODULE SuffixPercentageTest
#include <boost/test/unit_test.hpp>



/// 
/// @since  x.y.z, 01.05.2023
BOOST_AUTO_TEST_CASE( percentage)
{

   BOOST_REQUIRE_EQUAL( 5.0_pc, 0.05);
   BOOST_REQUIRE_EQUAL( 5_pc, 0.05);
   BOOST_REQUIRE_EQUAL( 200 * 5_pc, 10.0);

} // percentage



/// 
/// @since  x.y.z, 01.05.2023
BOOST_AUTO_TEST_CASE( permille)
{

   BOOST_REQUIRE_EQUAL( 5.0_pm, 0.005);
   BOOST_REQUIRE_EQUAL( 5_pm, 0.005);
   BOOST_REQUIRE_EQUAL( 200 * 5_pm, 1.0);

} // permille



// =====  END OF test_suffix_percentage.cpp  =====

