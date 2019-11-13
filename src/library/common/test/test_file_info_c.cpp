
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
**    Test program for the module celma::common::FileInfo, using the Boost.Test
**    framework.
**
--*/


// headerfile of the module to test
#include "celma/common/file_info.hpp"


// Boost includes
#define BOOST_TEST_MODULE FileInfoTest
#include <boost/test/unit_test.hpp>


using celma::common::FileInfo;
using celma::common::fileInfo;



/// Test creating a FileInfo object with a file that does not exist.
///
/// @since  1.4.0, 27.02.2018
BOOST_AUTO_TEST_CASE( test_errors)
{

   {
      BOOST_REQUIRE_THROW( FileInfo( "xyz"), std::runtime_error);
   } // end scope

   {
      BOOST_REQUIRE_THROW( FileInfo( "/tmp/xyz123"), std::runtime_error);
   } // end scope

   {
      BOOST_REQUIRE_THROW( FileInfo( 42), std::runtime_error);
   } // end scope

} // test_errors



/// Test the functions of the class FileInfo with one object.
///
/// @since  1.4.0, 27.02.2018
BOOST_AUTO_TEST_CASE( test_object)
{

   BOOST_REQUIRE_NO_THROW( FileInfo  fi_tmp( "/etc/passwd"));
   FileInfo  fi( "/etc/passwd");

   BOOST_REQUIRE( fi.isFile());
   BOOST_REQUIRE( !fi.isDirectory());

   BOOST_REQUIRE( fi.size() > 100);

   // test with std::string constructor
   FileInfo  fi2( std::string( "/etc/passwd"));
   BOOST_REQUIRE_EQUAL( fi.size(), fi2.size());

   // test with FILE* constructor
   FILE*  fp = ::fopen( "/etc/passwd", "r");
   BOOST_REQUIRE( fp != nullptr);
   FileInfo  fi3( fp);
   BOOST_REQUIRE_EQUAL( fi.size(), fi3.size());

   // test with file descriptor constructor
   FileInfo  fi4( ::fileno( fp));
   BOOST_REQUIRE_EQUAL( fi.size(), fi4.size());

   // test with given file data
   struct stat  my_stat;
   BOOST_REQUIRE( ::fstat( ::fileno( fp), &my_stat) == 0);
   FileInfo  fi5( my_stat);
   BOOST_REQUIRE_EQUAL( fi.size(), fi5.size());

   ::fclose( fp);

} // test_object



/// Test the function fileInfo() with the different initialisation values.
///
/// @since  1.4.0, 27.02.2018
BOOST_AUTO_TEST_CASE( test_one_off)
{

   BOOST_REQUIRE( fileInfo( "/etc/passwd").isFile());
   BOOST_REQUIRE( !fileInfo( std::string( "/etc/passwd")).isDirectory());

   size_t  filesize = fileInfo( "/etc/passwd").size();

   FILE*  fp = ::fopen( "/etc/passwd", "r");
   BOOST_REQUIRE( fp != nullptr);

   BOOST_REQUIRE_EQUAL( fileInfo( fp).size(), filesize);
   BOOST_REQUIRE_EQUAL( fileInfo( ::fileno( fp)).size(), filesize);

} // test_one_off



/// Test retrieving the parent directory from a FileInfo object.
///
/// @since  1.9.0, 04.08.2018
BOOST_AUTO_TEST_CASE( parent_directory)
{

   BOOST_REQUIRE_EQUAL( fileInfo( "/").parentDirectory(), "/");
   BOOST_REQUIRE_EQUAL( fileInfo( "/etc").parentDirectory(), "/");
   BOOST_REQUIRE_EQUAL( fileInfo( "/etc/passwd").parentDirectory(), "/etc");

} // parent_directory



// =====  END OF test_file_info_c.cpp  =====

