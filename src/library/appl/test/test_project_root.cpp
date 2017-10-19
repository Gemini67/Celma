
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
**    Test program for the functions of the module celma::appl::ProjectRoot.
**
--*/


// module to test header file include
#include "celma/appl/project_root.hpp"


// Boost includes
#define BOOST_TEST_MODULE ProjectRootTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/string_util.hpp"


using celma::appl::ProjectRoot;
using celma::common::ensure_last;
using std::runtime_error;
using std::string;


BOOST_TEST_DONT_PRINT_LOG_VALUE( ProjectRoot::ProjRootSrc)



/// Test that all error conditions are caught.
/// @since  x.y.z, 11.01.2017
BOOST_AUTO_TEST_CASE( test_errors)
{

   // set project root
   BOOST_REQUIRE_THROW( ProjectRoot::instance( ProjectRoot::ProjRootSrc::env),
                        runtime_error);
   BOOST_REQUIRE_THROW( ProjectRoot::instance( ProjectRoot::ProjRootSrc::env,
                                               "THIS_VARIABLE_DOES_NOT_EXIST"),
                        runtime_error);
   BOOST_REQUIRE_THROW( ProjectRoot::instance( ProjectRoot::ProjRootSrc::bin),
                        runtime_error);

} // test_errors



/// Test path creation based upon the value of the environment variable $HOME.
/// @since  x.y.z, 11.01.2017
BOOST_AUTO_TEST_CASE( test_home)
{

   string  home( ::getenv( "HOME"));

   ensure_last( home);

   // initialisation through constructor
   ProjectRoot::reset();
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::ProjRootSrc::home);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), home);

} // test_home



/// Test path creation based upon the value of the environment variable
/// $TEST_PROJ_ROOT_DIR which we set beforehand.
/// @since  x.y.z, 11.01.2017
BOOST_AUTO_TEST_CASE( test_env)
{

   const string  myvar( "TEST_PROJ_ROOT_DIR=/opt/application/celma/");
   ::putenv( const_cast< char*>( myvar.c_str()));

   const string  env( ::getenv( "TEST_PROJ_ROOT_DIR"));

   ProjectRoot::reset();
   // initialisation through constructor
   ProjectRoot::instance( ProjectRoot::ProjRootSrc::env, "TEST_PROJ_ROOT_DIR");

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::instance().ProjRootSrc::env);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), env);

   ProjectRoot::reset();
   // initialisation through method
   ProjectRoot::instance().setProjectRoot( ProjectRoot::ProjRootSrc::env,
                                           "TEST_PROJ_ROOT_DIR");

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::instance().ProjRootSrc::env);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), env);

} // test_env



/// Test path creation based upon the current working directory.
/// @since  x.y.z, 11.01.2017
BOOST_AUTO_TEST_CASE( test_cwd)
{

   string  cwd( ::get_current_dir_name());

   ensure_last( cwd);

   ProjectRoot::reset();
   // initialisation through constructor
   ProjectRoot::instance( ProjectRoot::ProjRootSrc::cwd);

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::instance().ProjRootSrc::cwd);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), cwd);

   ProjectRoot::reset();
   // initialisation through method
   ProjectRoot::instance().setProjectRoot( ProjectRoot::ProjRootSrc::cwd);

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::instance().ProjRootSrc::cwd);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), cwd);

} // test_cwd



/// Test path creation based upon the (absolute) program start path.
/// @since  x.y.z, 11.01.2017
BOOST_AUTO_TEST_CASE( test_prog_path)
{

   const string  projroot( "/opt/application/celma/");
   const string  arg0( projroot + "bin/this_is_my_bin_path");


   ProjectRoot::reset();
   // initialisation through constructor
   ProjectRoot::instance( ProjectRoot::ProjRootSrc::bin, arg0.c_str());

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::instance().ProjRootSrc::bin);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), projroot);

   ProjectRoot::reset();
   // initialisation through method
   ProjectRoot::instance().setProjectRoot( ProjectRoot::ProjRootSrc::bin, arg0.c_str());

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::instance().ProjRootSrc::bin);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), projroot);

} // test_prog_path



// ======================  END OF test_project_root.cpp  ======================

