
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
**    Test program for reading arguments from an environment variable, using
**    the Boost.Test module.
**
--*/


// module to test, header file include
#include "celma/prog_args.hpp"


// OS/C lib includes
#include <cstdlib>


// Boost includes
#define BOOST_TEST_MODULE ProgArgsEnvVarTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/global_fixture_access.hpp"
#include "celma/test/test_prog_arguments.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;


namespace {


/// Test environment initialisation: Need the start argument of the test program.
///
/// @since  1.22.0, 02.04.2019
class TestEnvironment: public celma::test::GlobalFixtureAccess< TestEnvironment>
{
public:
   /// Constructor.
   ///
   /// @since  1.22.0, 02.04.2019
   TestEnvironment():
      celma::test::GlobalFixtureAccess< TestEnvironment>(),
      mProgArgs()
   {
   } // TestEnvironment::TestEnvironment

   /// Returns the number of arguments.
   ///
   /// @return  The number of arguments passed to the test program.
   /// @since  1.22.0, 03.04.2019
   int argC() const
   {
      return mProgArgs.argC();
   } // TestEnvironment::argC

   /// Returns the pointer to the list of arguments.
   ///
   /// @return  Pointer to the list of argument strings.
   /// @since  1.22.0, 03.04.2019
   char** argV() const
   {
      return mProgArgs.argV();
   } // TestEnvironment::argV

private:
   /// Provides information about the program argments.
   celma::test::TestProgArguments  mProgArgs;

}; // TestEnvironment


} // namespace


BOOST_GLOBAL_FIXTURE( TestEnvironment);



/// Nothing bad should happen if the environment variable does not exist at all,
/// or exists but has no value, i.e. is an empty string.
///
/// @since  1.22.0, 01.04.2019
BOOST_AUTO_TEST_CASE( no_or_empty_env)
{

   {
      Handler  ah( Handler::hfEnvVarArgs);
      bool     flag = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f", DEST_VAR( flag), "a flag"));

      auto const  as2a = make_arg_array( "", "testprogname");
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   {
      Handler  ah( Handler::hfEnvVarArgs);
      bool     flag = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f", DEST_VAR( flag), "a flag"));

      auto const  as2a = make_arg_array( "", "testprogname");

      ::setenv( "TESTPROGNAME", "", 1);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      ::unsetenv( "TESTPROGNAME");
   } // end scope

} // no_or_empty_env



/// Now actually set argument(s) through the environment variable.
///
/// @since  1.22.0, 01.04.2019
BOOST_AUTO_TEST_CASE( set_through_env)
{

   // set an argument through the environment variable
   {
      Handler  ah( Handler::hfEnvVarArgs);
      bool     flag = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f", DEST_VAR( flag), "a flag"));

      auto const  as2a = make_arg_array( "", "testprogname");

      ::setenv( "TESTPROGNAME", "-f", 1);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      ::unsetenv( "TESTPROGNAME");

      BOOST_REQUIRE( flag);
   } // end scope

   // set a boolean flag both through the environment variable and the command
   // line
   {
      Handler  ah( Handler::hfEnvVarArgs);
      bool     flag = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f", DEST_VAR( flag), "a flag"));

      auto const  as2a = make_arg_array( "-f", "testprogname");

      ::setenv( "TESTPROGNAME", "-f", 1);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      ::unsetenv( "TESTPROGNAME");

      BOOST_REQUIRE( flag);
   } // end scope

   // set an argument through the environment variable, but overwrite it on the
   // command line
   {
      Handler  ah( Handler::hfEnvVarArgs);
      int      value = 13;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( value), "value"));

      auto const  as2a = make_arg_array( "-v 4711", "testprogname");

      ::setenv( "TESTPROGNAME", "-v 42", 1);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      ::unsetenv( "TESTPROGNAME");

      BOOST_REQUIRE_EQUAL( value, 4711);
   } // end scope

   // use the function instead of the start flag
   {
      Handler  ah( 0);
      int      value = 13;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( value), "value"));

      ah.checkEnvVarArgs( "ANOTHERTESTPROGNAME");
      auto const  as2a = make_arg_array( "", "testprogname");

      ::setenv( "ANOTHERTESTPROGNAME", "-v 42", 1);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      ::unsetenv( "ANOTHERTESTPROGNAME");

      BOOST_REQUIRE_EQUAL( value, 42);
   } // end scope

   // mix of arguments in the environment variable and on the command line
   {
      Handler  ah( Handler::hfEnvVarArgs);
      bool     flag1 = false;
      bool     flag2 = false;
      bool     flag3 = false;
      bool     flag4 = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "1", DEST_VAR( flag1), "flag one"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "2", DEST_VAR( flag2), "flag two"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "3", DEST_VAR( flag3), "flag three"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "4", DEST_VAR( flag4), "flag four"));

      auto const  as2a = make_arg_array( "-13", "testprogname");

      ::setenv( "TESTPROGNAME", "-2 -4", 1);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      ::unsetenv( "TESTPROGNAME");

      BOOST_REQUIRE( flag1);
      BOOST_REQUIRE( flag2);
      BOOST_REQUIRE( flag3);
      BOOST_REQUIRE( flag4);
   } // end scope

} // set_through_env



/// Set argument in environment variable that an argument file should be read.
///
/// @since  1.22.0, 02.04.2019
BOOST_AUTO_TEST_CASE( file_through_env)
{

   BOOST_REQUIRE_EQUAL( TestEnvironment::object().argC(), 2);
   BOOST_REQUIRE( TestEnvironment::object().argV() != nullptr);

   Handler  ah( Handler::hfEnvVarArgs);
   int      int_val = 6;

   ah.addArgument( "i", DEST_VAR( int_val), "An integer");
   ah.addArgumentFile( "arg-file");

   auto const  as2a = make_arg_array( "", "testprogname");
   std::string            env_value( "--arg-file ");

   env_value.append( TestEnvironment::object().argV()[ 1])
      .append( "/test_file_args.txt");

   ::setenv( "TESTPROGNAME", env_value.c_str(), 1);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   ::unsetenv( "TESTPROGNAME");

   BOOST_REQUIRE_EQUAL( int_val, 42);

} // file_through_env



/// Set argument in environment variable that an argument file should be read,
/// and afterwards overwrite the value.
///
/// @since  1.22.0, 02.04.2019
BOOST_AUTO_TEST_CASE( file_through_env_overwrite)
{

   BOOST_REQUIRE_EQUAL( TestEnvironment::object().argC(), 2);
   BOOST_REQUIRE( TestEnvironment::object().argV() != nullptr);

   Handler  ah( Handler::hfEnvVarArgs);
   int      int_val = 6;

   ah.addArgument( "i", DEST_VAR( int_val), "An integer");
   ah.addArgumentFile( "arg-file");

   auto const  as2a = make_arg_array( "-i 999", "testprogname");
   std::string            env_value( "--arg-file ");

   env_value.append( TestEnvironment::object().argV()[ 1])
      .append( "/test_file_args.txt");

   ::setenv( "TESTPROGNAME", env_value.c_str(), 1);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   ::unsetenv( "TESTPROGNAME");

   BOOST_REQUIRE_EQUAL( int_val, 999);

} // file_through_env_overwrite



// =====  END OF test_argh_env_var.cpp  =====

