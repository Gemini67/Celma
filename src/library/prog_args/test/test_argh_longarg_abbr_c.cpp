
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
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
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::make_arg_array;
using celma::common::CheckAssign;
using celma::prog_args::Handler;



/// Check handling of long arguments abbreviation.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( long_arg_abbr)
{

   Handler            ah( 0);
   CheckAssign< int>  inputVal;
   CheckAssign< int>  inplaceVal;
   CheckAssign< int>  outputVal;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "input",   DEST_VAR( inputVal),   "Integer"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "inplace", DEST_VAR( inplaceVal), "Integer"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "output",  DEST_VAR( outputVal),  "Integer"));

   {
      auto const  as2a = make_arg_array( "--in 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   {
      auto const  as2a = make_arg_array( "--inp 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   {
      auto const  as2a = make_arg_array( "--inpu 5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( inputVal.hasValue());
      BOOST_REQUIRE_EQUAL( inputVal.value(), 5);

      BOOST_REQUIRE( !inplaceVal.hasValue());
      BOOST_REQUIRE( !outputVal.hasValue());
   } // end scope

   inputVal.reset();
   inplaceVal.reset();
   outputVal.reset();

   {
      auto const  as2a = make_arg_array( "--inpl 5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( inplaceVal.hasValue());
      BOOST_REQUIRE_EQUAL( inplaceVal.value(), 5);

      BOOST_REQUIRE( !inputVal.hasValue());
      BOOST_REQUIRE( !outputVal.hasValue());
   } // end scope

   inputVal.reset();
   inplaceVal.reset();
   outputVal.reset();

   {
      auto const  as2a = make_arg_array( "--ou 5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( outputVal.hasValue());
      BOOST_REQUIRE_EQUAL( outputVal.value(), 5);

      BOOST_REQUIRE( !inputVal.hasValue());
      BOOST_REQUIRE( !inplaceVal.hasValue());
   } // end scope

} // long_arg_abbr



/// Test that abbreviations are not allowed when disabled.
/// @since  1.42.0, 30.11.2020
BOOST_AUTO_TEST_CASE( abbr_disabled)
{

   Handler            ah( Handler::hfNoAbbr);
   CheckAssign< int>  inputVal;
   CheckAssign< int>  inplaceVal;
   CheckAssign< int>  outputVal;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "input",   DEST_VAR( inputVal),   "Integer"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "inplace", DEST_VAR( inplaceVal), "Integer"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "output",  DEST_VAR( outputVal),  "Integer"));

   {
      auto const  as2a = make_arg_array( "--in 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   {
      auto const  as2a = make_arg_array( "--inp 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   {
      auto const  as2a = make_arg_array( "--inpu 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   inputVal.reset();
   inplaceVal.reset();
   outputVal.reset();

   {
      auto const  as2a = make_arg_array( "--inpl 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   inputVal.reset();
   inplaceVal.reset();
   outputVal.reset();

   {
      auto const  as2a = make_arg_array( "--ou 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // abbr_disabled



// =====  END OF test_argh_longarg_abbr_c.cpp  =====

