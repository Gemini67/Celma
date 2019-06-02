
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
**    Test program for the feature "value formatting" in the module Handler,
**    using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE HandlerFormatTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Verify that errors regarding formats are caught.
///
/// @since  1.23.1, 15.04.2019
BOOST_AUTO_TEST_CASE( errors)
{

   // ensure that calling addFormat() with a NULL object pointer throws
   {
      Handler  ah( 0);
      bool     dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( dummy), "flag")
         ->addFormat( nullptr), std::logic_error);
   } // end scope

   // ensure that calling addFormat() with a NULL object pointer throws
   {
      Handler  ah( 0);
      int      dummy = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( dummy), "int")
         ->addFormat( nullptr), std::invalid_argument);
   } // end scope

   // ensure that calling addFormat() on a wrong type throws
   {
      Handler  ah( 0);
      bool     dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( dummy), "flag")
         ->addFormat( celma::prog_args::uppercase()), std::logic_error);
   } // end scope

   // ensure that calling addFormat() with an empty format pattern throws
   {
      Handler      ah( 0);
      std::string  dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( dummy), "string")
         ->addFormat( celma::prog_args::anycase( "")), std::invalid_argument);
   } // end scope

} // errors



/// Check formatting to upper- and lowercase.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( format_case)
{

   celma::common::CheckAssign< std::string>  name;


   {
      Handler                ah( 0);
      auto const  as2a = make_arg_array( "-n process1", nullptr);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addFormat( celma::prog_args::uppercase());

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   name.reset();

   {
      Handler                ah( 0);
      auto const  as2a = make_arg_array( "-n PROceSS1", nullptr);

      ah.addArgument( "n", DEST_VAR( name), "Name")
         ->addFormat( celma::prog_args::lowercase());

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "process1");
   } // end scope

   // test with a string directly
   {
      Handler                ah( 0);
      auto const  as2a = make_arg_array( "-a PROceSS1", nullptr);
      std::string            my_string;

      ah.addArgument( "a", DEST_VAR( my_string), "another string")
         ->addFormat( celma::prog_args::uppercase());

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "PROCESS1");
   } // end scope

} // format_case



/// Check any-case formatting.
///
/// @since  1.23.0, 11.04.2019
BOOST_AUTO_TEST_CASE( format_anycase)
{

   // must throw when the format string is empty
   {
      Handler                ah( 0);
      auto const  as2a = make_arg_array( "-a bigSmAlL", nullptr);
      std::string            my_string;

      BOOST_REQUIRE_THROW( ah.addArgument( "a", DEST_VAR( my_string),
         "another string")->addFormat( celma::prog_args::anycase( "")),
         std::invalid_argument);
   } // end scope

   // test special anycase formatting
   {
      Handler                ah( 0);
      auto const  as2a = make_arg_array( "-a bigSmAlL", nullptr);
      std::string            my_string;

      ah.addArgument( "a", DEST_VAR( my_string), "another string")
         ->addFormat( celma::prog_args::anycase( "UUUlllll"));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "BIGsmall");
   } // end scope

   // format string longer than input string
   {
      Handler                ah( 0);
      auto const  as2a = make_arg_array( "-a bigS", nullptr);
      std::string            my_string;

      ah.addArgument( "a", DEST_VAR( my_string), "another string")
         ->addFormat( celma::prog_args::anycase( "UUUlllll"));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "BIGs");
   } // end scope

   // format string shorter than input string
   {
      Handler                ah( 0);
      auto const  as2a = make_arg_array( "-a bigSmAlL", nullptr);
      std::string            my_string;

      ah.addArgument( "a", DEST_VAR( my_string), "another string")
         ->addFormat( celma::prog_args::anycase( "UUUl"));

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !my_string.empty());
      BOOST_REQUIRE_EQUAL( my_string, "BIGsmAlL");
   } // end scope

} // format_anycase



// =====  END OF test_argh_format_c.cpp  =====

