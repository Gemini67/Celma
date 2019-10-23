
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
**    Test program for the feature 'printf log', using the Boost.Test
**    framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogPrintfTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "test_log_dest_msg.hpp"


using celma::log::Logging;
using celma::log::LogLevel;



/// @todo  Should use test classes to set up/tear down the log destination.
///        a) To remove code duplicates.
///        b) To make sure that the cleanup also happens when a test case fails
///           (now it leaves the invalid log destination which causes the next
///           test case to fail).



/// Test that log::printf() with log-id generates a log message as expected.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( log_printf_id)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
                      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG_PRINTF( my_log, info, communication,
               "log message create %s-like function call with %d parameters",
               "printf()", 2);
   const int  log_message_line = __LINE__ - 1 ;

   BOOST_REQUIRE_EQUAL( msg.getLevel(), LogLevel::info);
   BOOST_REQUIRE_EQUAL( msg.getClass(), celma::log::LogClass::communication);
   BOOST_REQUIRE_EQUAL( msg.getProcessId(), getpid());
   BOOST_REQUIRE_EQUAL( msg.getFileName(), "test_log_printf.cpp");
   BOOST_REQUIRE_EQUAL( msg.getFunctionName(), "log_printf_id::test_method");
   BOOST_REQUIRE_EQUAL( msg.getLineNbr(), log_message_line);
   BOOST_REQUIRE_EQUAL( msg.getText(), "log message create printf()-like function call with 2 parameters");
   BOOST_REQUIRE_EQUAL( msg.getErrorNbr(), 0);

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // end log_printf_id



/// Test that log::printf() with log-name generates a log message as expected.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( log_printf_name)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);


   Logging::instance().getLog( my_log)
                      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG_PRINTF( std::string( "mine"), info, communication,
               "log message create %s-like function call with %d parameters",
               "printf()", 2);
   const int  log_message_line = __LINE__ - 1 ;

   BOOST_REQUIRE_EQUAL( msg.getLevel(), LogLevel::info);
   BOOST_REQUIRE_EQUAL( msg.getClass(), celma::log::LogClass::communication);
   BOOST_REQUIRE_EQUAL( msg.getProcessId(), getpid());
   BOOST_REQUIRE_EQUAL( msg.getFileName(), "test_log_printf.cpp");
   BOOST_REQUIRE_EQUAL( msg.getFunctionName(), "log_printf_name::test_method");
   BOOST_REQUIRE_EQUAL( msg.getLineNbr(), log_message_line);
   BOOST_REQUIRE_EQUAL( msg.getText(), "log message create printf()-like function call with 2 parameters");
   BOOST_REQUIRE_EQUAL( msg.getErrorNbr(), 0);

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // end log_printf_name



// =======================  END OF test_log_printf.cpp  =======================
