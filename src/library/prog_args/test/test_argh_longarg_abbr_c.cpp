
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "long argument abbreviation" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test, headerfile include
#include "celma/prog_args.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgHLongArgAbbrTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"


using celma::prog_args::Handler;



/// Check handling of long arguments abbreviation.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( long_arg_abbr)
{

   Handler              ah( 0);
   std::optional< int>  inputVal;
   std::optional< int>  inplaceVal;
   std::optional< int>  outputVal;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "input",   DEST_VAR( inputVal),   "Integer"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "inplace", DEST_VAR( inplaceVal), "Integer"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "output",  DEST_VAR( outputVal),  "Integer"));

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "--in 5"),
      std::runtime_error);

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "--inp 5"),
      std::runtime_error);

   {
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--inpu 5"));
      BOOST_REQUIRE( inputVal.has_value());
      BOOST_REQUIRE_EQUAL( inputVal.value(), 5);

      BOOST_REQUIRE( !inplaceVal.has_value());
      BOOST_REQUIRE( !outputVal.has_value());
   } // end scope

   inputVal.reset();
   inplaceVal.reset();
   outputVal.reset();

   {
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--inpl 5"));
      BOOST_REQUIRE( inplaceVal.has_value());
      BOOST_REQUIRE_EQUAL( inplaceVal.value(), 5);

      BOOST_REQUIRE( !inputVal.has_value());
      BOOST_REQUIRE( !outputVal.has_value());
   } // end scope

   inputVal.reset();
   inplaceVal.reset();
   outputVal.reset();

   {
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--ou 5"));
      BOOST_REQUIRE( outputVal.has_value());
      BOOST_REQUIRE_EQUAL( outputVal.value(), 5);

      BOOST_REQUIRE( !inputVal.has_value());
      BOOST_REQUIRE( !inplaceVal.has_value());
   } // end scope

} // long_arg_abbr



/// Test that abbreviations are not allowed when disabled.
/// @since  1.42.0, 30.11.2020
BOOST_AUTO_TEST_CASE( abbr_disabled)
{

   Handler              ah( Handler::hfNoAbbr);
   std::optional< int>  inputVal;
   std::optional< int>  inplaceVal;
   std::optional< int>  outputVal;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "input",   DEST_VAR( inputVal),   "Integer"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "inplace", DEST_VAR( inplaceVal), "Integer"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "output",  DEST_VAR( outputVal),  "Integer"));

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "--in 5"),
      std::invalid_argument);

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "--inp 5"),
      std::invalid_argument);

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "--inpu 5"),
      std::invalid_argument);

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "--inpl 5"),
      std::invalid_argument);

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "--ou 5"),
      std::invalid_argument);

} // abbr_disabled



// =====  END OF test_argh_longarg_abbr_c.cpp  =====

