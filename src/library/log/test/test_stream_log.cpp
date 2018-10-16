
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module celma::log::detail::StreamLog, using the
**    Boost.Test framework.
**
--*/


// include of the tested module's header file
#include "celma/log/detail/stream_log.hpp"


// C++ Standard Library includes
#include <iostream>
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE StreamLogTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/formatting/creator.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "test_log_dest_msg.hpp"


using celma::log::Logging;



/// Adds a log message as destination.
/// @since
///    0.11, 12.12.2016
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



/// Checks that a custom property is correctly stored in the log message object.
///
/// @since  0.11, 12.12.2016
BOOST_AUTO_TEST_CASE( test_one_custom_property)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG( my_log) << "custom property 'color' = "
                << celma::log::customProperty( "color") << "cyan";

   BOOST_REQUIRE_EQUAL( msg.getPropertyValue( "color"), "cyan");

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // test_one_custom_property



/// Two custom properties msut be stored in the log message.
///
/// @since  0.11, 12.12.2016
BOOST_AUTO_TEST_CASE( test_two_custom_properties)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG( my_log) << "custom properties 'color' and 'price'"
                << celma::log::customProperty( "color") << "cyan"
                << "< test >"
                << celma::log::customProperty( "price") << 45.2;

   BOOST_REQUIRE_EQUAL( msg.getPropertyValue( "color"), "cyan");
   BOOST_REQUIRE_EQUAL( msg.getPropertyValue( "price"), "45.2");

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // test_two_custom_properties



/// Check that the contents of a stream are added to the log message.
///
/// @since  x.y.z, 12.10.2018
BOOST_AUTO_TEST_CASE( add_stream_to_log)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   std::ostringstream  oss;
   oss << "string and int (" << 42 << ")";

   LOG( my_log) << "ostringstream contents: '" << oss << "'.";

   const std::string  exp_result( "ostringstream contents: 'string and int (42)'.");
   auto               log_text( msg.getText());

   BOOST_REQUIRE_EQUAL( log_text.substr( log_text.length() - exp_result.length()),
                        exp_result);

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // add_stream_to_log



/// Add the value of an attribute to the text of the log message.
///
/// @since  x.y.z, 12.10.2018
BOOST_AUTO_TEST_CASE( add_attribute_to_log)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG_ATTRIBUTE( "color", "blue");

   LOG( my_log) << "value of attribute 'color' is '"
      << celma::log::attributeValue( "color") << "'.";

   const std::string  exp_result( "value of attribute 'color' is 'blue'.");
   auto               log_text( msg.getText());

   BOOST_REQUIRE_EQUAL( log_text, exp_result);

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // add_attribute_to_log



// =====  END OF test_stream_log.cpp  =====
