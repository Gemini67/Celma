
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
**    Test program for reading arguments from an argument file, using the
**    Boost.Test module.
**
--*/


// module to test, header file include
#include "celma/prog_args.hpp"


// Boost includes
#define BOOST_TEST_MODULE ProgArgsArgFileTest
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



/// Error when specifying a file that does not exist.
///
/// @since  1.23.0, 05.04.2019
BOOST_AUTO_TEST_CASE( invalid_file)
{

   Handler  ah( 0);
   int      int_val = 6;


   ah.addArgument( "i", DEST_VAR( int_val), "An integer");
   ah.addArgumentFile( "arg-file");

   auto const  as2a = make_arg_array( "--arg-file xyz", "testprogname");

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
      std::runtime_error);

} // invalid_file



/// Test that no error is generated when the file does not exist.
///
/// @since  1.23.0, 05.04.2019
BOOST_AUTO_TEST_CASE( file_through_flag)
{

   Handler  ah( Handler::hfReadProgArg);
   int      int_val = 6;


   ah.addArgument( "i", DEST_VAR( int_val), "An integer");

   auto const  as2a = make_arg_array( "", "testprogname");

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
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

   auto const  as2a = make_arg_array( "--arg-file " + file_path, "testprogname");

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

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

   auto const  as2a = make_arg_array( "", "testprogname");

   ::unsetenv( "HOME");

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( int_val, 6);

} // no_home



// =====  END OF test_argh_arg_file.cpp  =====

