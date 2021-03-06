
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature 'stream formatter', using the Boost.Test
**    framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE LogCustomStreamFormatter
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/format_stream_default.hpp"
#include "celma/log/detail/i_format_stream.hpp"
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log_dest_stream.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/formatting/creator.hpp"
#include "celma/log/formatting/format.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "test_log_dest_msg.hpp"


using celma::log::Logging;


class CustomStreamFormatter final : public celma::log::detail::IFormatStream
{
private:
   /// Interface definition of the method to be implmented by derived classes.
   /// @param[out]  out  The stream to write into.
   /// @param[in]   msg  The message to format the data of.
   /// @since  1.0.0, 19.06.2016
   virtual void format( std::ostream& out,
                        const celma::log::detail::LogMsg& msg) const override
   {
      out << msg.getText();
   } // CustomStreamFormatter::format

}; // CustomStreamFormatter


/// Helper class to make sure that the test environment is torn down in any case.
/// @since  1.0.0, 19.06.2016
class TestCaseLogDestStream
{
public:
   TestCaseLogDestStream()
   {

      mMyLog = Logging::instance().findCreateLog( "mine");

      GET_LOG( mMyLog)->
         addDestination( "stream",
                         new celma::log::detail::LogDestStream( mDest));

   }

   ~TestCaseLogDestStream()
   {
      // have to remove the log destinations again
      Logging::instance().getLog( mMyLog)->removeDestination( "stream");
   }

protected:
   celma::log::id_t    mMyLog;
   std::ostringstream  mDest;

}; // TestCaseLogDestStream



/// Test the default stream log format.
/// @since  1.0.0, 19.06.2016
BOOST_FIXTURE_TEST_CASE( default_log_format, TestCaseLogDestStream)
{

   celma::log::detail::LogMsg  msg( LOG_MSG_OBJECT_INIT);


   Logging::instance().getLog( mMyLog)
      ->addDestination( "msg", new celma::log::test::LogDestMsg( msg));

   LOG( mMyLog) << celma::log::LogLevel::debug << "A simple text built from "
      << 3 << " parts.";

   std::ostringstream  exp_string;
   std::unique_ptr< celma::log::detail::IFormatStream> fsd =
                   std::make_unique< celma::log::detail::FormatStreamDefault>();
   fsd->formatMsg( exp_string, msg);

   BOOST_REQUIRE_EQUAL( mDest.str(), exp_string.str());

   // have to remove the log destinations again
   Logging::instance().getLog( mMyLog)->removeDestination( "msg");

} // default_log_format



/// Test the custom stream log format.
/// @since  1.0.0, 19.06.2016
BOOST_FIXTURE_TEST_CASE( custom_log_format, TestCaseLogDestStream)
{

   GET_LOG( mMyLog)->getDestination( "stream")
      ->setFormatter( new CustomStreamFormatter());

   LOG( mMyLog) << celma::log::LogLevel::debug << "A simple text built from "
                << 3 << " parts.";

   // with this formatter, the log message should contain only the text
   BOOST_REQUIRE_EQUAL( mDest.str(), "A simple text built from 3 parts.");

} // custom_log_format



/// Test the output produced with a log format object.
/// @since  1.0.0, 03.10.2017
BOOST_FIXTURE_TEST_CASE( test_log_formatter, TestCaseLogDestStream)
{

   namespace clf = celma::log::formatting;

   clf::Definition  fmt_def;
   clf::Creator     fmt_creator( fmt_def);

   fmt_creator << clf::text;

   GET_LOG( mMyLog)->getDestination( "stream")
      ->setFormatter( new clf::Format( fmt_def));

   LOG( mMyLog) << celma::log::LogLevel::debug << "A simple text built from "
                << 3 << " parts.";

   // with this formatter, the log message should contain only the text
   BOOST_REQUIRE_EQUAL( mDest.str(), "A simple text built from 3 parts.");

} // test_log_formatter



// =====  END OF test_log_custom_stream_formatter.cpp  =====

