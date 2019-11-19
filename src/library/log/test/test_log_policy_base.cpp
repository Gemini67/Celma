
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
**    Test program for the module celma::log::detail::PolicyBase, using the
**    Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/log/files/policy_base.hpp"


// C++ Standard Library includes
#include <stdexcept>
#include <string>


// Boost includes
#define BOOST_TEST_MODULE LogPolicyBaseTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/creator.hpp"
#include "celma/log/filename/definition.hpp"


namespace {


/// Helper class to test the module PolicyBase.
///
/// @since  1.25.0, 03.05.2019
class TestPolicyBase: public celma::log::files::PolicyBase
{
public:
   /// Constructor. Stores the object to use to create the log file names.
   ///
   /// @param[in]  fname_def  Log filename definition.
   /// @throw
   ///    std::invalid_argument when the filename definition contains no parts.
   /// @since  1.25.0, 03.05.2019
   explicit TestPolicyBase( const celma::log::filename::Definition& fname_def)
      noexcept( false):
         PolicyBase( fname_def),
         mOpenCheckResults(),
         mWriteCheckResults()
   {
   } // TestPolicyBase::TestPolicyBase

   /// Empty, virtual destructor.
   ///
   /// @since  1.25.0, 03.05.2019
   virtual ~TestPolicyBase() = default;

   /// Specifies the results to return from openCheck() calls.
   ///
   /// @param[in]  results  The list of results to return.
   /// @since  1.25.0, 20.05.2019
   void setOpenCheckResult( const std::vector< bool>& results)
   {
      mOpenCheckResults = results;
   } // TestPolicyBase::setOpenCheckResult

   /// Specifies the results to return from writeCheck() calls.
   ///
   /// @param[in]  results  The list of results to return.
   /// @since  1.25.0, 20.05.2019
   void setWriteCheckResult( const std::vector< bool>& results)
   {
      mWriteCheckResults = results;
   } // TestPolicyBase::setWriteCheckResult

private:
   /// Check if the currently opened log file is valid for writing into.
   ///
   /// @return
   /// - \c true if it is (still) okay to write into the current log file.
   /// - \c false if a new log file should be opened.
   /// @since  1.25.0, 03.05.2019
   bool openCheck() override
   {
      return mOpenCheckResults[ mOpenCheckCalls++];
   } // TestPolicyBase::openCheck

   /// Called to check if the next log message can still be written into the
   /// current log file.
   ///
   /// @param[in]  msg
   ///    The log message object.
   /// @param[in]  msg_text
   ///    The formatted text of the log message.
   /// @return
   ///   - \c true if the log message can be written into the current log file.
   ///   - \c false if a new file should be opened for this log message.
   /// @since  1.25.0, 03.05.2019
   bool writeCheck( const celma::log::detail::LogMsg& msg,
      const std::string& msg_text) override
   {
      return mWriteCheckResults[ mWriteCheckCalls++];
   } // TestPolicyBase::writeCheck

   /// Called after the log message was written into the log file. Can be used
   /// to adjust counters etc.
   ///
   /// @param[in]  msg
   ///    The log message object.
   /// @param[in]  msg_text
   ///    The formatted text of the log message that was written into the log
   ///    file.
   /// @since  1.25.0, 03.05.2019
   void written( const celma::log::detail::LogMsg& msg,
      const std::string& msg_text) override
   {
   } // TestPolicyBase::written

   /// The list of results to return from openCheck().
   std::vector< bool>  mOpenCheckResults;
   /// Counter of openCheck() calls, needed to determine the result to return.
   int                 mOpenCheckCalls = 0;
   /// The list of results to return from writeCheck().
   std::vector< bool>  mWriteCheckResults;
   /// Counter of writeCheck() calls, needed to determine the result to return.
   int                 mWriteCheckCalls = 0;

}; // TestPolicyBase


} // namespace



/// Test that some error conditions are detected correctly.
///
/// @since  1.25.0, 03.05.2019
BOOST_AUTO_TEST_CASE( errors)
{

   // no filename defined
   {
      celma::log::filename::Definition  my_def;
      BOOST_REQUIRE_THROW( TestPolicyBase  tpb( my_def), std::invalid_argument);
   } // end scope

   // filename defined, but test policy says open fails
   {
      celma::log::filename::Definition  my_def;
      celma::log::filename::Creator     fnc( my_def);

      fnc << "/tmp/somefile.log";

      {
         BOOST_REQUIRE_NO_THROW( TestPolicyBase  tpb( my_def));
      } // end scope

      TestPolicyBase  tpb( my_def);
      tpb.setOpenCheckResult( { false, false });

      BOOST_REQUIRE_THROW( tpb.open(), std::runtime_error);
   } // end scope

} // errors



/// File open/open check should succeed on re-open.
///
/// @since  1.25.0, 20.05.2019
BOOST_AUTO_TEST_CASE( succeed_on_reopen)
{

   celma::log::filename::Definition  my_def;
   celma::log::filename::Creator     fnc( my_def);

   fnc << "/tmp/somefile.log";

   TestPolicyBase  tpb( my_def);

   tpb.setOpenCheckResult( { false, true });
   BOOST_REQUIRE_NO_THROW( tpb.open());

} // succeed_on_reopen



/// Write the second message fails (write check fails, then open check fails).
///
/// @since  1.25.0, 20.05.2019
BOOST_AUTO_TEST_CASE( fail_second_write)
{

   celma::log::filename::Definition  my_def;
   celma::log::filename::Creator     fnc( my_def);

   fnc << "/tmp/somefile.log";

   TestPolicyBase  tpb( my_def);

   tpb.setOpenCheckResult( { false, true, false, false });
   BOOST_REQUIRE_NO_THROW( tpb.open());

   celma::log::detail::LogMsg  msg( "test.cpp", "fail_second_write", 1000);

   tpb.setWriteCheckResult( { true, false, true });
   BOOST_REQUIRE_NO_THROW( tpb.writeMessage( msg, "hello"));
   BOOST_REQUIRE_THROW( tpb.writeMessage( msg, "hello again"),
      std::runtime_error);

} // fail_second_write



// =====  END OF test_log_policy_base.cpp  =====

