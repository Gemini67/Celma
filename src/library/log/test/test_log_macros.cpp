
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the macros provided by the log module, using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/log/logging.hpp"


// C++ Standard Library includes
#include <iostream>
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE LogMacrosTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_dest_stream.hpp"
#include "celma/log/log_macros.hpp"


using celma::log::Logging;


namespace {


/// Helper class to make sure that the test environment is set up and torn down
/// in any case for each test case.
/// @since
///    1.5.0, 15.06.2018
class TestCaseLogDestStream
{
public:
   /// Constructor, adds a log destination "stream" that writes into #mDest.
   /// @since
   ///    1.5.0, 15.06.2018
   TestCaseLogDestStream()
   {

      mMyLog = Logging::instance().findCreateLog( "mine");

      GET_LOG( mMyLog)->
         addDestination( "stream",
                         new celma::log::detail::LogDestStream( mDest));

   } // TestCaseLogDestStream::TestCaseLogDestStream

   /// Destructor, removes the log destination again.
   /// @since
   ///    1.5.0, 15.06.2018
   ~TestCaseLogDestStream()
   {
      // have to remove the log destinations again
      Logging::instance().getLog( mMyLog)->removeDestination( "stream");
   } // TestCaseLogDestStream::~TestCaseLogDestStream

protected:
   /// The id of the log destination that is added in the constructor.
   celma::log::id_t    mMyLog;
   /// The stream that the log destination writes into.
   std::ostringstream  mDest;

}; // TestCaseLogDestStream


} // namespace



/// Creates log messages using the basic macros.
/// @since
///    1.5.0, 15.06.2018
BOOST_FIXTURE_TEST_CASE( basic_macros, TestCaseLogDestStream)
{

   LOG( mMyLog) << "my first trace log message :-)";

   BOOST_REQUIRE( !mDest.str().empty());
   mDest.str( "");

} // basic_macros



/// Check macro that should create a log message only once.
/// @since
///    1.5.0, 15.06.2018
BOOST_FIXTURE_TEST_CASE( log_once, TestCaseLogDestStream)
{

   for (int i = 0; i < 10; ++i)
   {
      LOG_LEVEL_ONCE( mMyLog, info) << "this message should be created only"
         " once";

      if (i == 0)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if
   } // end for

   for (int i = 0; i < 10; ++i)
   {
      LOG_LEVEL_ONCE( mMyLog, info) << "this message should be created only"
         " once";

      if (i == 0)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if

      LOG_LEVEL_ONCE( mMyLog, info) << "this message should also be created"
         " only once";

      if (i == 0)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if
   } // end for

} // log_once



/// Check macro that should create a log message at most for a given number of
/// times.
/// @since
///    1.5.0, 15.06.2018
BOOST_FIXTURE_TEST_CASE( log_max, TestCaseLogDestStream)
{

   for (int i = 0; i < 10; ++i)
   {
      LOG_LEVEL_MAX( mMyLog, info, 5) << "this message should be created at"
         " most 5 times";

      if (i < 5)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if
   } // end for

   for (int i = 0; i < 10; ++i)
   {
      LOG_LEVEL_MAX( mMyLog, info, 5) << "this message should also be created"
         " at most 5 times";

      if (i < 5)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if

      LOG_LEVEL_MAX( mMyLog, info, 3) << "and this message should be created at"
         " most 3 times";

      if (i < 3)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if
   } // end for

} // log_max



/// Check macro that should create a log message only when the call point has
/// been passed for at least a given number of times.
/// @since
///    1.5.0, 15.06.2018
BOOST_FIXTURE_TEST_CASE( log_after, TestCaseLogDestStream)
{

   for (int i = 0; i < 10; ++i)
   {
      LOG_LEVEL_AFTER( mMyLog, info, 5) << "this message should be created only"
         " when this point has been passed at least 5 times";

      if (i >= 5)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if
   } // end for

   for (int i = 0; i < 10; ++i)
   {
      LOG_LEVEL_AFTER( mMyLog, info, 5) << "this message should also be created"
         " only when this point has been passed at least 5 times";

      if (i >= 5)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if

      LOG_LEVEL_AFTER( mMyLog, info, 8) << "and this message should be created"
         " only when this point has been passed at least 8 times";

      if (i >= 8)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if
   } // end for

} // log_after



/// Check macro that should create a log message only every nth time when the
/// call point is passed.
/// @since
///    1.5.0, 28.06.2018
BOOST_FIXTURE_TEST_CASE( log_every, TestCaseLogDestStream)
{

   for (int i = 1; i < 13; ++i)
   {
      LOG_LEVEL_EVERY( mMyLog, info, 3) << "this message should be created only"
         " when this point is passed for the 3rd, 6th etc. time";

      if (i % 3 == 0)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if
   } // end for

   for (int i = 1; i < 12; ++i)
   {
      LOG_LEVEL_EVERY( mMyLog, info, 3) << "this message should also be created"
         " only when this point has been passed for the 3rd, 6th etc. time";

      if (i % 3 == 0)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if

      LOG_LEVEL_EVERY( mMyLog, info, 6) << "and this message should be created"
         " only when this point has been passed for the 6th, 12th etc. time";

      if (i % 6 == 0)
      {
         BOOST_REQUIRE( !mDest.str().empty());
         mDest.str( "");
      } else
      {
         BOOST_REQUIRE( mDest.str().empty());
      } // end if
   } // end for

} // log_every



// =====  END OF test_log_macros.cpp  =====
