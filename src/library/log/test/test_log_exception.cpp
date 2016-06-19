
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
**    Test program for the feature 'log exception', using the Boost.Test
**    framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogExceptionTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "test_log_dest_msg.hpp"


using celma::log::Logging;


// module definitions
static int  exception_line = -1;


// static functions prototypes
static void exceptionFunc();


/// Test that the data of an exception is correctly copied into the log message
/// object.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( log_exception)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
                      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   try
   {
      exceptionFunc();
      BOOST_FAIL( "no exception thrown");
   } catch (const celma::common::CelmaRuntimeError& eb)
   {
      LOG( my_log) << eb;
   } // end try

   BOOST_REQUIRE_EQUAL( msg.getLevel(), celma::log::llError);
   BOOST_REQUIRE_EQUAL( msg.getClass(), celma::log::LogClass::sysCall);
   BOOST_REQUIRE_EQUAL( msg.getProcessId(), getpid());
   BOOST_REQUIRE_EQUAL( msg.getFileName(), "test_log_exception.cpp");
   BOOST_REQUIRE_EQUAL( msg.getFunctionName(), "exceptionFunc");
   BOOST_REQUIRE_EQUAL( msg.getLineNbr(), exception_line);
   BOOST_REQUIRE_EQUAL( msg.getText(), "catch this!");
   BOOST_REQUIRE_EQUAL( msg.getErrorNbr(), 0);

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // end log_exception



/// Test that the data of an exception is correctly copied into the log message
/// object, but log level and class should not be overwritten.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( log_exception_class_level)
{

   const auto                  my_log = Logging::instance().findCreateLog( "mine");
   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);

   Logging::instance().getLog( my_log)
                      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   try
   {
      exceptionFunc();
      BOOST_FAIL( "no exception thrown");
   } catch (const celma::common::CelmaRuntimeError& eb)
   {
      LOG( my_log) << celma::log::llFatal << celma::log::LogClass::communication << eb;
   } // end try

   BOOST_REQUIRE_EQUAL( msg.getLevel(), celma::log::llFatal);
   BOOST_REQUIRE_EQUAL( msg.getClass(), celma::log::LogClass::communication);
   BOOST_REQUIRE_EQUAL( msg.getProcessId(), getpid());
   BOOST_REQUIRE_EQUAL( msg.getFileName(), "test_log_exception.cpp");
   BOOST_REQUIRE_EQUAL( msg.getFunctionName(), "exceptionFunc");
   BOOST_REQUIRE_EQUAL( msg.getLineNbr(), exception_line);
   BOOST_REQUIRE_EQUAL( msg.getText(), "catch this!");
   BOOST_REQUIRE_EQUAL( msg.getErrorNbr(), 0);

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "msg");

} // end log_exception_class_level



/// Throws an exception.
/// @since  0.3, 19.06.2016
static void exceptionFunc()
{

   exception_line = __LINE__ + 1;
   throw CELMA_RuntimeError( "catch this!");
} // end exceptionFunc



// ======================  END OF test_log_exception.cpp  ======================
