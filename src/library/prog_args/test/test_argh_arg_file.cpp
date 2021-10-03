
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for reading arguments from an argument file, using the
**    Boost.Test module.
**
--*/


// module to test, headerfile include
#include "celma/prog_args.hpp"


// Boost includes
#define BOOST_TEST_MODULE ProgArgsArgFileTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/global_fixture_access.hpp"
#include "celma/test/test_prog_arguments.hpp"


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



/// Error when specifying a file that does not exist.
///
/// @since  1.23.0, 05.04.2019
BOOST_AUTO_TEST_CASE( invalid_file)
{

   Handler  ah( 0);
   int      int_val = 6;


   ah.addArgument( "i", DEST_VAR( int_val), "An integer");
   ah.addArgumentFile( "arg-file");

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "--arg-file xyz"),
      std::runtime_error);

} // invalid_file



/// Test that no error is generated when the argument file does not exist.
///
/// @since  1.23.0, 05.04.2019
BOOST_AUTO_TEST_CASE( file_through_flag)
{

   Handler  ah( Handler::hfReadProgArg);
   int      int_val = 6;


   ah.addArgument( "i", DEST_VAR( int_val), "An integer");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "", "testprogname"));
   BOOST_REQUIRE_EQUAL( int_val, 6);

} // file_through_flag



/// Use the argument with the complete path and filename.
///
/// @since  1.23.0, 05.04.2019
BOOST_AUTO_TEST_CASE( file_through_arg)
{

   BOOST_REQUIRE_EQUAL( TestEnvironment::object().argC(), 2);
   BOOST_REQUIRE( TestEnvironment::object().argV() != nullptr);
   BOOST_REQUIRE( TestEnvironment::object().argV()[ 1] != nullptr);

   Handler  ah( 0);
   int      int_val = 6;

   ah.addArgument( "i", DEST_VAR( int_val), "An integer");
   ah.addArgumentFile( "arg-file");

   std::string  file_path( TestEnvironment::object().argV()[ 1]);

   file_path.append( "/test_file_args.txt");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--arg-file " + file_path,
      "testprogname"));

   BOOST_REQUIRE_EQUAL( int_val, 42);

} // file_through_arg



/// No error when the HOME environment variable is not set.
///
/// @since  1.27.0, 28.05.2019
BOOST_AUTO_TEST_CASE( no_home)
{

   Handler  ah( Handler::hfReadProgArg);
   int      int_val = 6;


   ah.addArgument( "i", DEST_VAR( int_val), "An integer");

   ::unsetenv( "HOME");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "", "testprogname"));
   BOOST_REQUIRE_EQUAL( int_val, 6);

} // no_home



// =====  END OF test_argh_arg_file.cpp  =====

