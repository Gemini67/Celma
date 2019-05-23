
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the different types of log files with specific names/
**    generations, using the Boost.Test framework.
**
--*/


#define BOOST_TEST_MODULE LogFileTypesTest
#include <boost/test/unit_test.hpp>


// C++ Standard Library includes
#include <string>
#include <vector>

#if __has_include( <filesystem>)
#   include <filesystem>
namespace filesys = std::filesystem;
#else
#   include <boost/filesystem.hpp>
namespace filesys = boost::filesystem;
#endif

// project includes
#include "celma/common/file_operations.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/filename/creator.hpp"
#include "celma/log/files/factory.hpp"
#include "celma/log/files/max_size.hpp"
#include "celma/log/files/simple.hpp"
#include "celma/log/files/timestamped.hpp"
#include "celma/log/formatting/creator.hpp"
#include "celma/log/formatting/format.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"

// test includes
#include "test_file_funcs_impl.hpp"
#include "test_i_dir_list.hpp"


using celma::log::Logging;


namespace {


/// Stores the list of all directories that are created during the test and
/// deletes them afterwards.
///
/// @since  x.y.z, 08.03.2018
class GlobalFixture: public celma::log::TestIDirList
{
public:
   /// Constructor, sets a special file operations policy that stores the names
   /// of the directories, that are created during a test, in the internal
   /// container.
   ///
   /// @since  x.y.z, 08.03.2018
   GlobalFixture();

   /// Destructor, removes all the directories that were created during the
   /// tests.
   ///
   /// @since  x.y.z, 08.03.2018
   ~GlobalFixture();

   /// Gets called when a directory is created.
   ///
   /// @param[in]  dir_name
   ///    The (path and) name of the directory that is created.
   /// @since  x.y.z, 08.03.2018
   virtual void dirCreated( const std::string& dir_name) override;

private:
   /// The type of the container used to store the directory names.
   using dir_list_t = std::vector< std::string>;

   /// The names of the directories created during the tests.
   dir_list_t  mDirectories;

}; // GlobalFixture


} // namespace


BOOST_GLOBAL_FIXTURE( GlobalFixture);



/// Test writing log messages into simple log files.
///
/// @since  x.y.z, 09.03.2018
BOOST_AUTO_TEST_CASE( test_simple)
{

   namespace clf = celma::log::files;
   namespace clfn = celma::log::filename;
   namespace clfo = celma::log::formatting;

   clfn::Definition  filename_def;
   clfn::Creator     path_creator( filename_def);

   path_creator << "/tmp/logtest_simple_" << clfn::pid << "_"
      << clfn::formatString( "%j") << clfn::date << "/logfile_" << clfn::number
      << ".txt";

   clfo::Definition  format_def;
   clfo::Creator     format_creator( format_def);

   format_creator << clfo::date << "|" << clfo::time << "." << clfo::time_us
      << "|" << clfo::text;

   auto const  my_log = Logging::instance().findCreateLog( "mylog");
   Logging::instance().getLog( my_log)
      ->addDestination( "file", clf::factory< clf::LogFileTypes::simple>( filename_def))
      ->setFormatter( new clfo::Format( format_def));

   for (int i = 0; i < 1000; ++i)
   {
      LOG( my_log) << "Log message number " << i << ".";
   } // end for

} // test_simple



/// Test writing log messages into log files with a maximum size.
///
/// @since  x.y.z, 21.02.2018
BOOST_AUTO_TEST_CASE( test_max_size)
{

   namespace clf = celma::log::files;
   namespace clfn = celma::log::filename;
   namespace clfo = celma::log::formatting;

   clfn::Definition  filename_def;
   clfn::Creator     path_creator( filename_def);

   path_creator << "/tmp/logtest_maxsize_" << clfn::pid << "_"
      << clfn::formatString( "%j") << clfn::date << "/logfile_" << clfn::number
      << ".txt";

   clfo::Definition  format_def;
   clfo::Creator     format_creator( format_def);

   format_creator << clfo::date << "|" << clfo::time << "." << clfo::time_us
      << "|" << clfo::text;

   auto const  my_log = Logging::instance().findCreateLog( "mylog");
   Logging::instance().getLog( my_log)
      ->addDestination( "file", clf::factory( filename_def, 10000, 10))
      ->setFormatter( new clfo::Format( format_def));

   for (int i = 0; i < 1000; ++i)
   {
      LOG( my_log) << "Log message number " << i << ".";
   } // end for

} // test_max_size



/// Test writing log messages into log files organizing their contents by
/// timestamp.
///
/// @since  x.y.z, 09.03.2018
BOOST_AUTO_TEST_CASE( test_timestamped)
{

   namespace clf = celma::log::files;
   namespace clfn = celma::log::filename;
   namespace clfo = celma::log::formatting;

   clfn::Definition  filename_def;
   clfn::Creator     path_creator( filename_def);

   path_creator << "/tmp/logtest_timestamped" << clfn::pid
      << clfn::path_sep << "logfile" << clfn::formatString( "%T") << clfn::date
      << "_" << clfn::number << ".txt";

   clfo::Definition  format_def;
   clfo::Creator     format_creator( format_def);

   format_creator << clfo::date << "|" << clfo::time << "." << clfo::time_us
      << "|" << clfo::text;

   auto const  my_log = Logging::instance().findCreateLog( "mylog");
   Logging::instance().getLog( my_log)
      ->addDestination( "file",
         clf::factory< clf::LogFileTypes::timestamped>( filename_def))
      ->setFormatter( new clfo::Format( format_def));

   for (int i = 0; i < 1000; ++i)
   {
      LOG( my_log) << "Log message number " << i << ".";
   } // end for

} // test_timestamped



namespace {



/// Constructor, sets a special file operations policy that stores the names
/// of the directories, that are created during a test, in the internal
/// container.
///
/// @since  x.y.z, 08.03.2018
GlobalFixture::GlobalFixture()
{

   celma::common::FileOperations::setFuncImpl(
      new celma::log::TestFileFuncsImpl( this));

} // GlobalFixture::GlobalFixture



/// Destructor, removes all the directories that were created during the
/// tests.
///
/// @since  x.y.z, 08.03.2018
GlobalFixture::~GlobalFixture()
{

   for (auto const& dir_name : mDirectories)
   {
      filesys::remove_all( dir_name);
   } // end for

} // GlobalFixture::~GlobalFixture



/// Gets called when a directory is created.
///
/// @param[in]  dir_name
///    The (path and) name of the directory that is created.
/// @since  x.y.z, 08.03.2018
void GlobalFixture::dirCreated( const std::string& dir_name)
{

   mDirectories.push_back( dir_name);

} // GlobalFixture::dirCreated



} // namespace



// =====  END OF test_log_file_types.cpp  =====
