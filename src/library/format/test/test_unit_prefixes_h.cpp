
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "unit prefixes", using the Boost.Test
**    framework.
**
--*/


// headerfile include of the module to test
#include "celma/format/unit_prefixes.hpp"


// C++ Standard Library includes
#include <iostream>
#include <limits>


// Boost includes
#define BOOST_TEST_MODULE UnitPrefixesTest
#include <boost/test/unit_test.hpp>



/// Verify that the format prefixes are correctly applied.
///
/// @since  1.39.0, 09.07.2020
BOOST_AUTO_TEST_CASE( apply_prefixes)
{

   BOOST_REQUIRE_EQUAL( 1_KiB, 1024);
   BOOST_REQUIRE_EQUAL( 10_KiB, 10'240);
   BOOST_REQUIRE_EQUAL( 100_KiB, 102'400);
   BOOST_REQUIRE_EQUAL( 1000_KiB, 1'024'000);

   BOOST_REQUIRE_EQUAL( 1_MiB, 1024_KiB);
   BOOST_REQUIRE_EQUAL( 1_GiB, 1024_MiB);
   BOOST_REQUIRE_EQUAL( 1_TiB, 1024_GiB);
   BOOST_REQUIRE_EQUAL( 1_PiB, 1024_TiB);
   BOOST_REQUIRE_EQUAL( 1_EiB, 1024_PiB);

   BOOST_REQUIRE( 1_EiB < std::numeric_limits< uint64_t>::max());

} // apply_prefixes



// =====  END OF test_unit_prefixes_h.cpp  =====

