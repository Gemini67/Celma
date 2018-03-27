
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module detail::StreamLog, using the Boost.Test
**    framework.
**
--*/


// include of the tested module's header file
#include "celma/log/detail/stream_log.hpp"


// Boost includes
#define BOOST_TEST_MODULE StreamLogTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "test_log_dest_msg.hpp"


using celma::log::Logging;



/// 
/// @since  0.11, 12.12.2016
BOOST_AUTO_TEST_CASE( test_default)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
                      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG( my_log) << "log message text only";

   BOOST_REQUIRE_EQUAL( msg.getProcessId(), ::getpid());
   BOOST_REQUIRE_EQUAL( msg.getFileName(), "test_stream_log.cpp");

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // test_default



/// 
/// @since  0.11, 12.12.2016
BOOST_AUTO_TEST_CASE( test_one_custom_property)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
                      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG( my_log) << "custom property 'color' = "
                << celma::log::detail::customProperty( "color") << "cyan";

   BOOST_REQUIRE_EQUAL( msg.getPropertyValue( "color"), "cyan");

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // test_one_custom_property



/// 
/// @since  0.11, 12.12.2016
BOOST_AUTO_TEST_CASE( test_two_custom_properties)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
                      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG( my_log) << "custom properties 'color' and 'price'"
                << celma::log::detail::customProperty( "color") << "cyan"
                << "< test >"
                << celma::log::detail::customProperty( "price") << 45.2;

   BOOST_REQUIRE_EQUAL( msg.getPropertyValue( "color"), "cyan");
   BOOST_REQUIRE_EQUAL( msg.getPropertyValue( "price"), "45.2");

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // test_two_custom_properties



// =======================  END OF test_stream_log.cpp  =======================
