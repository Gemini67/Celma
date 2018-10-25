
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "value argument" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test, header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHValueArgTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;



/// Test handling of errors.
/// @since  1.1.0, 25.09.2017
BOOST_AUTO_TEST_CASE( test_errors)
{

   // wrong setup: changing the value mode not allowed on value argument
   {
      Handler  ah( 0);
      int      my_dest = 0;

      BOOST_REQUIRE_THROW(
         ah.addArgument( "left", DEST_VAR_VALUE( my_dest, -1),
            "left")->setValueMode( Handler::ValueMode::required),
         std::logic_error);
   } // end scope

   // wrong setup: value checks not allowed on value argument
   {
      Handler  ah( 0);
      int      my_dest = 0;

      BOOST_REQUIRE_THROW(
         ah.addArgument( "left", DEST_VAR_VALUE( my_dest, -1),
             "left")->addCheck( celma::prog_args::lower( -1)),
         std::logic_error);
   } // end scope

   // wrong usage: argument used two times
   {
      Handler  ah( 0);
      int      my_dest = 0;

      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "left", DEST_VAR_VALUE( my_dest, -1), "left"));

      const ArgString2Array  as2a( "--left --left", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

} // test_errors



/// Test correct usage of a value argument.
/// @since  1.1.0, 15.11.2017
BOOST_AUTO_TEST_CASE( test_value_arg)
{

   // use the first value argument
   {
      Handler  ah( 0);
      int      my_dest = 0;

      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "left", DEST_VAR_VALUE( my_dest, -1), "left"));
      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "right", DEST_VAR_VALUE( my_dest, 1), "right"));

      const ArgString2Array  as2a( "--left", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( my_dest, -1);
   } // end scope

   // use the second value argument
   {
      Handler  ah( 0);
      int      my_dest = 0;

      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "left", DEST_VAR_VALUE( my_dest, -1), "left"));
      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "right", DEST_VAR_VALUE( my_dest, 1), "right"));

      const ArgString2Array  as2a( "--right", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( my_dest, 1);
   } // end scope

   // error when using both value arguments
   {
      Handler  ah( 0);
      int      my_dest = 0;

      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "left", DEST_VAR_VALUE( my_dest, -1), "left"));
      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "right", DEST_VAR_VALUE( my_dest, 1), "right"));

      const ArgString2Array  as2a( "--right --left", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   // allow use of both value arguments
   {
      Handler  ah( 0);
      int      my_dest = 0;

      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "left", DEST_VAR_VALUE( my_dest, -1), "left")
            ->checkOriginalValue( false));
      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "right", DEST_VAR_VALUE( my_dest, 1), "right")
            ->checkOriginalValue( false));

      const ArgString2Array  as2a( "--right --left", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( my_dest, -1);
   } // end scope

} // test_value_arg



/// Usage and other outputs.
///
/// @since  1.15.0, 19.10.2018
BOOST_AUTO_TEST_CASE( usage_and_info)
{

   {
      std::ostringstream  oss_std;
      std::ostringstream  oss_err;
      Handler             ah( oss_std, oss_err, Handler::AllHelp
         | Handler::hfVerboseArgs | Handler::hfUsageCont);
      int                 my_dest = 0;

      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "l,left", DEST_VAR_VALUE( my_dest, -1), "left"));
      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "r,right", DEST_VAR_VALUE( my_dest, 1), "right")
            ->setPrintDefault( false));

      const ArgString2Array  as2a( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( !oss_std.str().empty());
      // std::cerr << "\n" << oss_std.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Handler::usage: is set\n"
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -l,--left    left\n"
         "                Default value: 0\n"
         "   -r,--right   right\n"
         "\n"));
   } // end scope

   {
      std::ostringstream  oss_std;
      std::ostringstream  oss_err;
      Handler             ah( oss_std, oss_err, Handler::AllHelp
         | Handler::hfListArgVar | Handler::hfUsageCont);
      int                 my_dest = 0;

      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "l,left", DEST_VAR_VALUE( my_dest, -1), "left"));
      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "r,right", DEST_VAR_VALUE( my_dest, 1), "right")
            ->setPrintDefault( false));

      const ArgString2Array  as2a( "--list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( !oss_std.str().empty());
      // std::cerr << "\n" << oss_std.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Arguments:\n"
         "'-h,--help' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--help-arg' calls function/method 'Prints the usage for the given argument.'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'-l,--left' value type 'int', destination 'my_dest', set-value '-1', value not set.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, print dflt, no checks, no formats\n"
         "'-r,--right' value type 'int', destination 'my_dest', set-value '1', value not set.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "\n"));
   } // end scope

   {
      std::ostringstream  oss_std;
      std::ostringstream  oss_err;
      Handler             ah( oss_std, oss_err, Handler::AllHelp
         | Handler::hfListArgVar | Handler::hfUsageCont);
      int                 my_dest = 0;

      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "l,left", DEST_VAR_VALUE( my_dest, -1), "left"));
      BOOST_REQUIRE_NO_THROW(
         ah.addArgument( "r,right", DEST_VAR_VALUE( my_dest, 1), "right")
            ->setPrintDefault( false));

      const ArgString2Array  as2a( "-r --list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( !oss_std.str().empty());
      // std::cerr << "\n" << oss_std.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Arguments:\n"
         "'-h,--help' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--help-arg' calls function/method 'Prints the usage for the given argument.'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'-l,--left' value type 'int', destination 'my_dest', set-value '-1', value not set.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, print dflt, no checks, no formats\n"
         "'-r,--right' value type 'int', destination 'my_dest', set-value '1', value = 1.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "\n"));
   } // end scope

} // usage_and_info



// =====  END OF test_argh_value_arg.cpp  =====

