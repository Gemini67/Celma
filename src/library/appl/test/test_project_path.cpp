
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
**    Test program for the functions of the module ProjectPath.
**
--*/


// module to test header file include
#include "celma/appl/project_path.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ProjectPathTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/project_root.hpp"
#include "celma/common/string_util.hpp"


using celma::appl::ProjectPath;
using celma::appl::ProjectRoot;
using celma::common::ensure_last;
using std::runtime_error;
using std::string;


BOOST_TEST_DONT_PRINT_LOG_VALUE( ProjectRoot::ProjRootSrc)



/// Test that all error conditions are caught.
/// @since  1.0.0, 11.01.2017
BOOST_AUTO_TEST_CASE( test_errors)
{

   // create paths
   BOOST_REQUIRE_THROW( ProjectPath( nullptr), runtime_error);

   BOOST_REQUIRE_THROW( ProjectPath( "sub", nullptr), runtime_error);
   BOOST_REQUIRE_THROW( ProjectPath( nullptr, "filename"), runtime_error);

   BOOST_REQUIRE_THROW( ProjectPath( "sub",   "filename", nullptr),
                        runtime_error);
   BOOST_REQUIRE_THROW( ProjectPath( "sub",   nullptr,    "ext"),
                        runtime_error);
   BOOST_REQUIRE_THROW( ProjectPath( "sub",   nullptr,    nullptr),
                        runtime_error);
   BOOST_REQUIRE_THROW( ProjectPath( nullptr, "filename", "ext"),
                        runtime_error);
   BOOST_REQUIRE_THROW( ProjectPath( nullptr, "filename", nullptr),
                        runtime_error);
   BOOST_REQUIRE_THROW( ProjectPath( nullptr, nullptr,    "ext"),
                        runtime_error);
   BOOST_REQUIRE_THROW( ProjectPath( nullptr, nullptr,    nullptr),
                        runtime_error);

} // test_errors



/// Test path creation based upon the value of the environment variable $HOME.
/// @since  1.0.0, 11.01.2017
BOOST_AUTO_TEST_CASE( test_home)
{

   ProjectRoot::reset();

   string  home( ::getenv( "HOME"));

   ensure_last( home);

   {
      ProjectPath  pp( ".cshrc");


      // do the same manually
      string  expResult( home);
      expResult.append( ".cshrc");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);

      std::ostringstream  oss;
      oss << pp;

      BOOST_REQUIRE_EQUAL( oss.str(), expResult);
   } // end scope

   {
      ProjectPath  pp( "etc", "project.cfg");

      // do the same manually
      string  expResult( home);
      expResult.append( "etc/project.cfg");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
   } // end scope
   
   {
      ProjectPath  pp( "etc", "myproject", "xml");

      // do the same manually
      string  expResult( home);
      expResult.append( "etc/myproject.xml");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
   } // end scope

} // test_home



/// Test path creation based upon the value of the environment variable
/// $TEST_PROJ_ROOT_DIR which we set beforehand.
/// @since  1.0.0, 11.01.2017
BOOST_AUTO_TEST_CASE( test_env)
{

   const string  myvar( "TEST_PROJ_ROOT_DIR=/opt/application/celma/");
   ::putenv( const_cast< char*>( myvar.c_str()));

   const string  env( ::getenv( "TEST_PROJ_ROOT_DIR"));

   ProjectRoot::reset();
   ProjectRoot::instance( ProjectRoot::ProjRootSrc::env, "TEST_PROJ_ROOT_DIR");

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::ProjRootSrc::env);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), env);

   {
      ProjectPath  pp( ".cshrc");

      // do the same manually
      string  expResult( env);
      expResult.append( ".cshrc");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope

   {
      ProjectPath  pp( "/etc", "project.cfg");

      // do the same manually
      string  expResult( env);
      expResult.append( "etc/project.cfg");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope
   
   {
      ProjectPath  pp( "/etc/", "myproject", ".xml");

      // do the same manually
      string  expResult( env);
      expResult.append( "etc/myproject.xml");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope

} // test_env



/// Test path creation based upon the current working directory.
/// @since  1.0.0, 11.01.2017
BOOST_AUTO_TEST_CASE( test_cwd)
{

   string  cwd( ::get_current_dir_name());

   ensure_last( cwd);

   ProjectRoot::reset();
   ProjectRoot::instance( ProjectRoot::ProjRootSrc::cwd);

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::ProjRootSrc::cwd);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), cwd);

   {
      ProjectPath  pp( ".cshrc");

      // do the same manually
      string  expResult( cwd);
      expResult.append( ".cshrc");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope

   {
      ProjectPath  pp( "etc/", "project.cfg");

      // do the same manually
      string  expResult( cwd);
      expResult.append( "etc/project.cfg");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope
   
   {
      ProjectPath  pp( "etc", "myproject", "xml");

      // do the same manually
      string  expResult( cwd);
      expResult.append( "etc/myproject.xml");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope

} // test_cwd



/// Test path creation based upon the (absolute) program start path.
/// @since  1.0.0, 11.01.2017
BOOST_AUTO_TEST_CASE( test_prog_path)
{

   const string  projroot( "/opt/application/celma/");
   const string  arg0( projroot + "bin/this_is_my_bin_path");


   ProjectRoot::reset();
   ProjectRoot::instance( ProjectRoot::ProjRootSrc::bin, arg0.c_str());

   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().projectRootSrc(),
                        ProjectRoot::ProjRootSrc::bin);
   BOOST_REQUIRE_EQUAL( ProjectRoot::instance().path(), projroot);

   {
      ProjectPath  pp( ".cshrc");

      // do the same manually
      string  expResult( projroot);
      expResult.append( ".cshrc");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope

   {
      ProjectPath  pp( "etc/", "project.cfg");

      // do the same manually
      string  expResult( projroot);
      expResult.append( "etc/project.cfg");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope
   
   {
      ProjectPath  pp( "/etc", "myproject", "xml");

      // do the same manually
      string  expResult( projroot);
      expResult.append( "etc/myproject.xml");

      BOOST_REQUIRE_EQUAL( pp.str(), expResult);
      BOOST_REQUIRE( ProjectRoot::instance().isOnProject( pp.str()));
   } // end scope

} // test_prog_path



// =====  END OF test_project_path.cpp  =====

