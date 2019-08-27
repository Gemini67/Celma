
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
**    Test program for the argument migration related features in the module
**    "argument handling", using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE ArgMigrationTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;
using std::ostringstream;



/// Error case: An argument cannot be both mandatory and deprecated.
/// @since
///    1.6.0, 29.06.2018
BOOST_AUTO_TEST_CASE( feature_clash)
{

   {
      Handler  ah( 0);
      int      old_arg = 0;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
         ->setIsDeprecated()->setIsMandatory(), std::logic_error);
   } // end scope

   {
      Handler  ah( 0);
      int      old_arg = 0;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
         ->setIsMandatory()->setIsDeprecated(), std::logic_error);
   } // end scope

   {
      Handler      ah( 0);
      int          old_arg = 0;
      std::string  new_arg;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( new_arg), "string"));
      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
         ->setReplacedBy( "-s")->setIsMandatory(), std::logic_error);
   } // end scope

   {
      Handler      ah( 0);
      int          old_arg = 0;
      std::string  new_arg;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( new_arg), "string"));
      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
         ->setIsMandatory()->setReplacedBy( "-s"), std::logic_error);
   } // end scope

} // feature_clash



/// Using a deprecated argument should throw.
/// @since
///    1.6.0, 29.06.2018
BOOST_AUTO_TEST_CASE( invalid_use_of_deprecated_argument)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   int             old_arg = 0;
   std::string     new_arg;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
      ->setIsDeprecated());
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( new_arg), "string"));

   auto const  as2a = make_arg_array( "-i 25", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
      std::runtime_error);

} // invalid_use_of_deprecated_argument



/// Check that the information about a deprecated/replaced argument is printed
/// correctly in "list arguments and variables".
///
/// @since  1.24.2, 23.04.2019
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   {
      ostringstream  std_out;
      ostringstream  err_out;
      Handler        ah( std_out, err_out, Handler::AllHelp
         | Handler::hfUsageCont | Handler::hfListArgVar);
      int            old_arg = 0;
      std::string    new_arg;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
         ->setIsDeprecated());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( new_arg), "string"));

      auto const  as2a = make_arg_array( "--list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( err_out.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << '\n' << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h,--help' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--help-arg' calls function/method 'Prints the usage for the given argument.'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' value type 'int', destination 'old_arg', value not set.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, print dflt, deprecated, no checks, no formats.\n"
         "'-s' value type 'std::string', destination 'new_arg', value not set.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, no formats.\n"
         "\n"));
   } // end scope

   {
      ostringstream  std_out;
      ostringstream  err_out;
      Handler        ah( std_out, err_out, Handler::AllHelp
         | Handler::hfUsageCont | Handler::hfListArgVar);
      int            old_arg = 0;
      std::string    new_arg;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
         ->setReplacedBy( "-s"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( new_arg), "string"));

      auto const  as2a = make_arg_array( "--list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( err_out.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << '\n' << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h,--help' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--help-arg' calls function/method 'Prints the usage for the given argument.'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' value type 'int', destination 'old_arg', value not set.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, print dflt, replaced by \"-s\", no checks, no formats.\n"
         "'-s' value type 'std::string', destination 'new_arg', value not set.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, no formats.\n"
         "\n"));
   } // end scope

} // list_arg_vars



/// Using a replaced argument should throw.
/// @since
///    1.6.0, 03.07.2018
BOOST_AUTO_TEST_CASE( invalid_use_of_replaced_argument)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   int             old_arg = 0;
   std::string     new_arg;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
      ->setReplacedBy( "-s"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( new_arg), "string"));

   auto const  as2a = make_arg_array( "-i 25", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
      std::runtime_error);

} // invalid_use_of_replaced_argument



// =====  END OF test_argh_migration_c.cpp  =====
