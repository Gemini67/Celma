
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
**    Test program for the module celma::common::FileOperations, using the
**    Boost.Test framework.
**
--*/


// headerfile of the module to test
#include "celma/common/file_operations.hpp"


// Boost includes
#define BOOST_TEST_MODULE FileOperationsTest
#include <boost/test/unit_test.hpp>


using celma::common::FileOperations;



/// Attempt to assign a NULL pointer as file-functions implementation throws.
/// @since  1.4.0, 01.03.2018
BOOST_AUTO_TEST_CASE( assign_null_throws)
{

   BOOST_REQUIRE_THROW( FileOperations::setFuncImpl( nullptr),
      std::runtime_error);

} // assign_null_throws



/// Test for renaming a file.
/// @since  1.4.0, 28.02.2018
BOOST_AUTO_TEST_CASE( rename_existing_file_and_remove)
{

   FILE*  fp = ::fopen( "/tmp/old_filename.txt", "w");
   ::fwrite( "hello", 5, 1, fp);
   ::fclose( fp);

   BOOST_REQUIRE( FileOperations::rename( "/tmp/new_filename.txt",
      "/tmp/old_filename.txt") == 0);

   
   BOOST_REQUIRE( FileOperations::remove( "/tmp/new_filename.txt") == 0);

   fp = ::fopen( "/tmp/new_filename.txt", "r");
   BOOST_REQUIRE( fp == nullptr);

} // rename_existing_file_and_remove



// =====  END OF test_file_operations.cpp  =====

