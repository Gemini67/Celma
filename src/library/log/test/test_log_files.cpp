
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the modules in log::files, using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/log/files/handler.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE LogFilesTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/filename/creator.hpp"
#include "celma/log/filename/definition.hpp"
#include "celma/log/files/counted.hpp"
#include "celma/log/files/handler.hpp"
#include "celma/log/files/max_size.hpp"
#include "celma/log/files/simple.hpp"
#include "celma/log/files/timestamped.hpp"



/// Test some error conditions.
/// @since  1.0.0, 21.12.2017
BOOST_AUTO_TEST_CASE( test_errors)
{

   namespace clfn = celma::log::filename;
   namespace clf = celma::log::files;

   clfn::Definition  my_def;
   clfn::Creator     format_creator( my_def);

   format_creator << "/var/log/logfile.txt";

   // log files with maximum size, but no log file generation number in the
   // log filename definition
   {
      BOOST_REQUIRE_THROW(
         clf::Handler< clf::MaxSize>  hms( new clf::MaxSize( my_def, 1'000'000,
            10)),
         std::runtime_error);
   } // end scope

   // log files per timestamp, but no timestamp in the log filename definition
   {
      BOOST_REQUIRE_THROW(
         clf::Handler< clf::Timestamped>  ht( new clf::Timestamped( my_def)),
         std::runtime_error);
   } // end scope

   // log files with number of entries, but no log file generation number in the
   // log filename definition
   {
      BOOST_REQUIRE_THROW(
         clf::Handler< clf::Counted>  hct( new clf::Counted( my_def, 1'000, 10)),
         std::runtime_error);
   } // end scope

   // no filename defined
   {
      clfn::Definition  ldef;
      clfn::Creator     lfc( ldef);

      BOOST_REQUIRE_THROW(
         clf::Handler< clf::Simple>  hct( new clf::Simple( ldef)),
         std::invalid_argument);
   } // end scope

   // simple log file handling, but invalid path
   {
      clfn::Definition  ldef;
      clfn::Creator     lfc( ldef);

      lfc << "/x/y/z/logfile.txt";

      BOOST_REQUIRE_THROW(
         clf::Handler< clf::Simple>  hct( new clf::Simple( ldef)),
         std::runtime_error);
   } // end scope

} // test_errors



/// Try to create log file handlers with the different log file policies.
/// @since  1.0.0, 14.12.2017
BOOST_AUTO_TEST_CASE( test_one)
{

   namespace clfn = celma::log::filename;
   namespace clf = celma::log::files;

   {
      clfn::Definition  my_def;
      clfn::Creator     format_creator( my_def);

      format_creator << "/tmp/logfile.txt";
      clf::Handler< clf::Simple>  hs( new clf::Simple( my_def));
      hs.setFormatter();
   } // end scope

   {
      clfn::Definition  my_def;
      clfn::Creator     format_creator( my_def);

      format_creator << "/tmp/logfile_ms." << 2 << clfn::number << ".txt";
      clf::Handler< clf::MaxSize>  hms( new clf::MaxSize( my_def, 1'000'000, 10));
      hms.setFormatter();
   } // end scope

   {
      clfn::Definition  my_def;
      clfn::Creator     format_creator( my_def);

      format_creator << "/tmp/logfile_ts." << clfn::date << ".txt";
      clf::Handler< clf::Timestamped>  ht( new clf::Timestamped( my_def));
      ht.setFormatter();
   } // end scope

   {
      clfn::Definition  my_def;
      clfn::Creator     format_creator( my_def);

      format_creator << "/tmp/logfile_ms." << 2 << clfn::number << ".txt";
      clf::Handler< clf::Counted>  hct( new clf::Counted( my_def, 1'000, 10));
      hct.setFormatter();
   } // end scope

} // test_one



// =====  END OF test_log_files.cpp  =====

