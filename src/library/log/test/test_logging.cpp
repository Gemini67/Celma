
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module celma::log::Logging, using the Boost.Test
**    framework.
**
--*/


// module to test headerfile include
#include "celma/log/logging.hpp"


// C++ Standard Library includes
#include <iostream>
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE LoggingTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/log_dest_stream.hpp"
#include "celma/log/log_macros.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::log::Logging;



/// Test that handling errors are caught correctly.
///
/// @since  x.y.z, 11.11.2019
BOOST_AUTO_TEST_CASE( errors)
{

   BOOST_REQUIRE( Logging::instance().getLog( 1) == nullptr);

   auto  log_id = Logging::instance().findCreateLog( "basic");
   BOOST_REQUIRE( log_id > 0);

   BOOST_REQUIRE( Logging::instance().getLog( log_id) != nullptr);
   BOOST_REQUIRE_THROW( Logging::instance().getLog( log_id | 0x10),
      celma::common::CelmaRuntimeError);

} // errors



/// Test printing the settings of the logging framework.
///
/// @since  x.y.z, 11.11.2019
BOOST_AUTO_TEST_CASE( printing)
{

   Logging::reset();

   std::ostringstream  oss;

   oss << Logging::instance();

   BOOST_REQUIRE_EQUAL( oss.str(), "next log id: 0x01\n");

   auto  log_id = Logging::instance().findCreateLog( "basic");
   BOOST_REQUIRE( log_id > 0);

   oss.str( "");
   oss << Logging::instance();

   BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
      "next log id: 0x02\n"
      "   log id = 0x01, name = 'basic':\n"
      "      -\n"
      "\n"
   ));

   std::ostringstream  dest;
   GET_LOG( log_id)->addDestination( "stream",
      new celma::log::detail::LogDestStream( dest));

   oss.str( "");
   oss << Logging::instance();

   // std::cout << oss.str();
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
      "next log id: 0x02\n"
      "   log id = 0x01, name = 'basic':\n"
      "      log dest name: stream\n"
      "\n"
      "\n"
   ));

} // printing



// =====  END OF test_logging.cpp  =====
