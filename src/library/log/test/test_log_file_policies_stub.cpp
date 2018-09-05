
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
**    Test program for the modules in log::files, using a policy base stub and
**    the Boost.Test framework.
**
--*/


// modules to test header file includes
#include "celma/log/files/max_size.hpp"
#include "celma/log/files/simple.hpp"
#include "celma/log/files/timestamped.hpp"


// C++ Standard Library includes
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE LogFilesTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/file_operations.hpp"
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/creator.hpp"
#include "celma/test/global_fixture_access.hpp"
#include "celma/log/files/policy_base.hpp"


using celma::log::detail::LogMsg;
using celma::log::filename::Creator;
using celma::log::filename::Definition;
using celma::log::filename::date;
using celma::log::filename::number;


namespace {


/// Helper class to check that the correct file operations are executed.
/// @since  x.y.z, 30.08.2018
class TestFileFuncs: public celma::common::detail::FileFuncsBase
{
public:
   /// Looks like a default constructor.
   TestFileFuncs() = default;

   /// Empty, virtual destructor.
   /// @since  x.y.z, 30.08.2018
   virtual ~TestFileFuncs() = default;

   /// Gets called when a file should be renamed.
   ///
   /// @param[in]  dest
   ///    The new (pah and) name for the file.
   /// @param[in]  src
   ///    The (path and) name of the existing file that should be renamed.
   /// @return  The result of the %rename operation.
   /// @since  x.y.z, 30.08.2018
   virtual int rename( const std::string& dest, const std::string& src) override
   {
      if (mNextRenameParamsIdx >= mRenameParam.size())
         throw std::invalid_argument( "more rename calls than expected");
      if (mRenameParam[ mNextRenameParamsIdx].first != dest)
         throw std::runtime_error( "expected destination '"
            + mRenameParam[ mNextRenameParamsIdx].first + "', got '" + dest
            + "'");
      if (mRenameParam[ mNextRenameParamsIdx].second != src)
         throw std::runtime_error( "expected source '"
            + mRenameParam[ mNextRenameParamsIdx].second + "', got '" + src
            + "'");

      ++mNextRenameParamsIdx;

      return 0;
   } // TestFileFuncs::rename

   /// Gets called when a %file should be removed.
   ///
   /// @param[in]  file  The (path and) name of the file to delete.
   /// @return  The result code of the %remove operation.
   /// @since  x.y.z, 30.08.2018
   virtual int remove( const std::string&) override
   {
      // nothing to do here
      return 0;
   } // TestFileFuncs::remove

   /// Stores the expected names of the destination and source file of the next
   /// rename operation.
   ///
   /// @param[in]  dest
   ///    The (path and) name of the destination file.
   /// @param[in]  src
   ///    The (path and) name of the source file.
   /// @since  x.y.z, 30.08.2018
   void expectedRenameParameters( const std::string& dest,
      const std::string& src)
   {
      mRenameParam.push_back( names_t( dest, src));
   } // TestFileFuncs::expectedRenameParameters

   /// Checks if all expected rename parameters were used.
   ///
   /// @return  \c true if all expected rename parameters were used.
   /// @since  x.y.z, 30.08.2018
   bool allRenameParameters() const
   {
      return mNextRenameParamsIdx == mRenameParam.size();
   } // TestFileFuncs::allRenameParameters

   /// Resets the container with the expected rename parameters as well as the
   /// index of the next expected parameters.
   ///
   /// @since  x.y.z, 30.08.2018
   void resetRenameParameters()
   {
      mRenameParam.clear();
      mNextRenameParamsIdx = 0;
   } // TestFileFuncs::resetRenameParameters

   /// Resets only the index of the next expected parameters.<br>
   /// Use this function if the same file definition is used for multiple tests.
   ///
   /// @since  x.y.z, 02.09.2018
   void resetNextRenameIndex()
   {
      mNextRenameParamsIdx = 0;
   } // TestFileFuncs::resetNextRenameIndex

private:
   /// Type of the expected rename parameters.
   using names_t = std::pair< std::string, std::string>;
   /// Container type used to store the next rename parameters.
   using parameters_t = std::vector< names_t>;

   /// Parameters expected for the rename function calls.
   parameters_t  mRenameParam;
   /// Index of the next expected parameters.
   size_t        mNextRenameParamsIdx = 0;

}; // TestFileFuncs


/// Test environment initialisation.<br>
/// Creates a special functions object. Access to this object is provided
/// through the base class and the method fileFuncsObject.
///
/// @since  x.y.z, 30.08.2018
class TestEnvironment: public celma::test::GlobalFixtureAccess< TestEnvironment>
{
public:
   /// Constructor. Creates the file functions object for the test and passes it
   /// to the file operations class.
   ///
   /// @since  x.y.z, 30.08.2018
   TestEnvironment():
      celma::test::GlobalFixtureAccess< TestEnvironment>(),
      mpTestFileFunctions( new TestFileFuncs())
   {
      celma::common::FileOperations::setFuncImpl( mpTestFileFunctions);
   } // TestEnvironment::TestEnvironment

   /// Destructor. Don't delete anything, just reset the pointer.
   ///
   /// @since  x.y.z, 30.08.2018
   ~TestEnvironment()
   {
      mpTestFileFunctions = nullptr;
   } // TestEnvironment::~TestEnvironment

   /// Returns the file functions object used for the tests.
   ///
   /// @return  The file functions object used for the tests.
   /// @since  x.y.z, 30.08.2018
   TestFileFuncs& fileFuncsObject()
   {
      return *mpTestFileFunctions;
   } // TestEnvironment::fileFuncsObject

private:
   /// Pointer to the file functions object used in the test. Pointer only since
   /// it will be deleted by the FileOperations class.
   TestFileFuncs*  mpTestFileFunctions;

}; // TestEnvironment


} // namespace


BOOST_GLOBAL_FIXTURE( TestEnvironment)



/// Test a simple log file without generations, automatic rolling etc.
///
/// @since  x.y.z, 04.09.2018
BOOST_AUTO_TEST_CASE( simple)
{

   using celma::log::files::Simple;

   Definition  my_def;
   Creator     format_creator( my_def);


   format_creator << "/tmp/logfile_simple.txt";
   Simple  s( my_def);

   s.open();
   BOOST_REQUIRE( s.getResetOpenCalled());
   BOOST_REQUIRE_EQUAL( s.logFileName(), "/tmp/logfile_simple.txt");

   const int    line_nbr = __LINE__;
   LogMsg       lm( "test_log_msg.cpp", "test_simple", line_nbr);
   std::string  text ( 10'000, '=');

   BOOST_REQUIRE_NO_THROW( s.writeMessage( lm, text));

   BOOST_REQUIRE( !s.getResetOpenCalled());
   BOOST_REQUIRE( !s.getResetRollFilesCalled());
   BOOST_REQUIRE( !s.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( s.logFileName(), "/tmp/logfile_simple.txt");
   BOOST_REQUIRE_EQUAL( s.logFileSize(), 10'000);

   BOOST_REQUIRE_NO_THROW( s.writeMessage( lm, text));

   BOOST_REQUIRE( !s.getResetOpenCalled());
   BOOST_REQUIRE( !s.getResetRollFilesCalled());
   BOOST_REQUIRE( !s.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( s.logFileName(), "/tmp/logfile_simple.txt");
   BOOST_REQUIRE_EQUAL( s.logFileSize(), 20'000);

   BOOST_REQUIRE_NO_THROW( s.writeMessage( lm, text));

   BOOST_REQUIRE( !s.getResetOpenCalled());
   BOOST_REQUIRE( !s.getResetRollFilesCalled());
   BOOST_REQUIRE( !s.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( s.logFileName(), "/tmp/logfile_simple.txt");
   BOOST_REQUIRE_EQUAL( s.logFileSize(), 30'000);

   auto  copy( s);
   BOOST_REQUIRE( copy.logFileName().empty());
   BOOST_REQUIRE_EQUAL( copy.logFileSize(), 0);

} // simple



/// Write multiple short messages ino the same file (no rolling).
///
/// @since  x.y.z, 03.09.2018
BOOST_AUTO_TEST_CASE( max_size_dont_roll)
{

   using celma::log::files::MaxSize;

   Definition  my_def;
   Creator     format_creator( my_def);


   format_creator << "/tmp/logfile_ms." << 2 << number << ".txt";
   MaxSize  ms( my_def, 100'000, 3);

   ms.open();
   BOOST_REQUIRE( ms.getResetOpenCalled());
   BOOST_REQUIRE_EQUAL( ms.logFileName(), "/tmp/logfile_ms.00.txt");

   const int    line_nbr = __LINE__;
   LogMsg       lm( "test_log_msg.cpp", "test_simple", line_nbr);
   std::string  text ( 10'000, '=');

   BOOST_REQUIRE_NO_THROW( ms.writeMessage( lm, text));

   BOOST_REQUIRE( !ms.getResetOpenCalled());
   BOOST_REQUIRE( !ms.getResetRollFilesCalled());
   BOOST_REQUIRE( !ms.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ms.logFileName(), "/tmp/logfile_ms.00.txt");
   BOOST_REQUIRE_EQUAL( ms.logFileSize(), 10'000);

   BOOST_REQUIRE_NO_THROW( ms.writeMessage( lm, text));

   BOOST_REQUIRE( !ms.getResetOpenCalled());
   BOOST_REQUIRE( !ms.getResetRollFilesCalled());
   BOOST_REQUIRE( !ms.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ms.logFileName(), "/tmp/logfile_ms.00.txt");
   BOOST_REQUIRE_EQUAL( ms.logFileSize(), 20'000);

   BOOST_REQUIRE_NO_THROW( ms.writeMessage( lm, text));

   BOOST_REQUIRE( !ms.getResetOpenCalled());
   BOOST_REQUIRE( !ms.getResetRollFilesCalled());
   BOOST_REQUIRE( !ms.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ms.logFileName(), "/tmp/logfile_ms.00.txt");
   BOOST_REQUIRE_EQUAL( ms.logFileSize(), 30'000);

   BOOST_REQUIRE_NO_THROW( ms.writeMessage( lm, text));

   BOOST_REQUIRE( !ms.getResetOpenCalled());
   BOOST_REQUIRE( !ms.getResetRollFilesCalled());
   BOOST_REQUIRE( !ms.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ms.logFileName(), "/tmp/logfile_ms.00.txt");
   BOOST_REQUIRE_EQUAL( ms.logFileSize(), 40'000);

   BOOST_REQUIRE_NO_THROW( ms.writeMessage( lm, text));

} // max_size_dont_roll



/// Write very large message, so that each message must be written into a new
/// file.
///
/// @since  x.y.z, 30.08.2018
BOOST_AUTO_TEST_CASE( max_size_roll_always)
{

   using celma::log::files::MaxSize;

   Definition  my_def;
   Creator     format_creator( my_def);


   format_creator << "/tmp/logfile_ms." << 2 << number << ".txt";
   MaxSize  ms( my_def, 100'000, 3);

   ms.open();
   BOOST_REQUIRE( ms.getResetOpenCalled());
   BOOST_REQUIRE_EQUAL( ms.logFileName(), "/tmp/logfile_ms.00.txt");

   const int    line_nbr = __LINE__;
   LogMsg       lm( "test_log_msg.cpp", "test_simple", line_nbr);
   std::string  text ( 50'000, '=');

   BOOST_REQUIRE_NO_THROW( ms.writeMessage( lm, text));

   BOOST_REQUIRE( !ms.getResetOpenCalled());
   BOOST_REQUIRE( !ms.getResetRollFilesCalled());
   BOOST_REQUIRE( !ms.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ms.logFileName(), "/tmp/logfile_ms.00.txt");
   BOOST_REQUIRE_EQUAL( ms.logFileSize(), 50'000);

   TestEnvironment::object().fileFuncsObject().expectedRenameParameters(
      "/tmp/logfile_ms.02.txt", "/tmp/logfile_ms.01.txt");
   TestEnvironment::object().fileFuncsObject().expectedRenameParameters(
      "/tmp/logfile_ms.01.txt", "/tmp/logfile_ms.00.txt");

   BOOST_REQUIRE_NO_THROW( ms.writeMessage( lm, text));

   BOOST_REQUIRE( ms.getResetOpenCalled());
   BOOST_REQUIRE( ms.getResetRollFilesCalled());
   BOOST_REQUIRE( !ms.getResetReOpenCalled());
   BOOST_REQUIRE( TestEnvironment::object().fileFuncsObject().allRenameParameters());
   BOOST_REQUIRE_EQUAL( ms.logFileName(), "/tmp/logfile_ms.00.txt");
   BOOST_REQUIRE_EQUAL( ms.logFileSize(), 50'000);

   auto  copy( ms);
   BOOST_REQUIRE( copy.logFileName().empty());
   BOOST_REQUIRE_EQUAL( copy.logFileSize(), 0);

} // max_size_roll_always



/// Write multiple short messages ino the same file (no rolling).
///
/// @since  x.y.z, 04.09.2018
BOOST_AUTO_TEST_CASE( timestamped_dont_roll)
{

   using celma::log::files::Timestamped;

   Definition  my_def;
   Creator     format_creator( my_def);
   char        timestamp_str[ 128];
   time_t      today = ::time( nullptr);


   format_creator << "/tmp/logfile_ts." << date << ".txt";
   Timestamped  ts( my_def);

   ::strftime( timestamp_str, sizeof( timestamp_str) - 1, "%F",
      ::localtime( &today));

   std::string  exp_filename( std::string( "/tmp/logfile_ts.") + timestamp_str
      + ".txt");

   ts.open();
   BOOST_REQUIRE( ts.getResetOpenCalled());
   BOOST_REQUIRE_EQUAL( ts.logFileName(), exp_filename);

   const int    line_nbr = __LINE__;
   LogMsg       lm( "test_log_msg.cpp", "test_simple", line_nbr);
   std::string  text ( 10'000, '=');

   BOOST_REQUIRE_NO_THROW( ts.writeMessage( lm, text));

   BOOST_REQUIRE( !ts.getResetOpenCalled());
   BOOST_REQUIRE( !ts.getResetRollFilesCalled());
   BOOST_REQUIRE( !ts.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ts.logFileName(), exp_filename);
   BOOST_REQUIRE_EQUAL( ts.logFileSize(), 10'000);

   BOOST_REQUIRE_NO_THROW( ts.writeMessage( lm, text));

   BOOST_REQUIRE( !ts.getResetOpenCalled());
   BOOST_REQUIRE( !ts.getResetRollFilesCalled());
   BOOST_REQUIRE( !ts.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ts.logFileName(), exp_filename);
   BOOST_REQUIRE_EQUAL( ts.logFileSize(), 20'000);

   BOOST_REQUIRE_NO_THROW( ts.writeMessage( lm, text));

   BOOST_REQUIRE( !ts.getResetOpenCalled());
   BOOST_REQUIRE( !ts.getResetRollFilesCalled());
   BOOST_REQUIRE( !ts.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ts.logFileName(), exp_filename);
   BOOST_REQUIRE_EQUAL( ts.logFileSize(), 30'000);

   BOOST_REQUIRE_NO_THROW( ts.writeMessage( lm, text));

   BOOST_REQUIRE( !ts.getResetOpenCalled());
   BOOST_REQUIRE( !ts.getResetRollFilesCalled());
   BOOST_REQUIRE( !ts.getResetReOpenCalled());
   BOOST_REQUIRE_EQUAL( ts.logFileName(), exp_filename);
   BOOST_REQUIRE_EQUAL( ts.logFileSize(), 40'000);

   BOOST_REQUIRE_NO_THROW( ts.writeMessage( lm, text));

   auto  copy( ts);
   BOOST_REQUIRE( copy.logFileName().empty());
   BOOST_REQUIRE_EQUAL( copy.logFileSize(), 0);

} // timestamped_dont_roll



// =====  END OF test_log_file_policies_stub.cpp  =====
