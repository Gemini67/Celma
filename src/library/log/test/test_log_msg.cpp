
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the class detail::LogMsg, using the Boost.Test framework.
**
--*/


// include of the tested module's header file
#include "celma/log/detail/log_msg.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogMsgTest
#include <boost/test/unit_test.hpp>


// project includes


using celma::log::detail::LogMsg;



/// Test the default values set by the LogMsg class.
/// @since  1.0.0, 04.10.2017
BOOST_AUTO_TEST_CASE( test_defaults)
{

   const int  line_nbr = __LINE__;
   LogMsg     lm( "test_log_msg.cpp", "test_simple", line_nbr);


   BOOST_REQUIRE_EQUAL( lm.getProcessId(), ::getpid());
   BOOST_REQUIRE_EQUAL( lm.getThreadId(), ::pthread_self());
   BOOST_REQUIRE_EQUAL( lm.getFileName(), "test_log_msg.cpp");
   BOOST_REQUIRE_EQUAL( lm.getFunctionName(), "test_simple");
   BOOST_REQUIRE_EQUAL( lm.getLineNbr(), line_nbr);
   BOOST_REQUIRE_EQUAL( lm.getClass(), celma::log::LogClass::undefined);
   BOOST_REQUIRE_EQUAL( lm.getLevel(), celma::log::LogLevel::undefined);
   BOOST_REQUIRE_EQUAL( lm.getErrorNbr(), 0);
   BOOST_REQUIRE( lm.getText().empty());

} // test_defaults



/// Test the values set by the initialisation macro.
/// @since  1.0.0, 04.10.2017
BOOST_AUTO_TEST_CASE( test_macro)
{

   const int  line_nbr = __LINE__ + 1;
   LogMsg     lm( LOG_MSG_OBJECT_INIT);


   BOOST_REQUIRE_EQUAL( lm.getFileName(), "test_log_msg.cpp");
   BOOST_REQUIRE_EQUAL( lm.getFunctionName(), "test_macro::test_method");
   BOOST_REQUIRE_EQUAL( lm.getLineNbr(), line_nbr);

} // test_macro



/// Test the setter methods of the LogMsg class.
/// @since  1.0.0, 04.10.2017
BOOST_AUTO_TEST_CASE( test_setters)
{

   const int  line_nbr = __LINE__ + 1;
   LogMsg     lm( LOG_MSG_OBJECT_INIT);


   BOOST_REQUIRE_EQUAL( lm.getProcessId(), ::getpid());
   BOOST_REQUIRE_EQUAL( lm.getThreadId(), ::pthread_self());
   BOOST_REQUIRE_EQUAL( lm.getFileName(), "test_log_msg.cpp");
   BOOST_REQUIRE_EQUAL( lm.getFunctionName(), "test_setters::test_method");
   BOOST_REQUIRE_EQUAL( lm.getLineNbr(), line_nbr);

   lm.setClass( celma::log::LogClass::communication);
   BOOST_REQUIRE_EQUAL( lm.getClass(), celma::log::LogClass::communication);

   lm.setLevel( celma::log::LogLevel::info);
   BOOST_REQUIRE_EQUAL( lm.getLevel(), celma::log::LogLevel::info);

   lm.setErrorNumber( 4711);
   BOOST_REQUIRE_EQUAL( lm.getErrorNbr(), 4711);

   lm.setText( "the text of the log message");
   BOOST_REQUIRE_EQUAL( lm.getText(), "the text of the log message");

   lm.setCustomProperty( "prop_name1", "the first property");
   lm.setCustomProperty( "prop_name2", "the second property");
   BOOST_REQUIRE_EQUAL( lm.getPropertyValue( "prop_name1"), "the first property");
   BOOST_REQUIRE_EQUAL( lm.getPropertyValue( "prop_name2"), "the second property");
   BOOST_REQUIRE( lm.getPropertyValue( "prop_name3").empty());

} // test_setters



// =========================  END OF test_log_msg.cpp  =========================
