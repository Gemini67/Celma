
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "long argument abbreviation" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test, header file include
#include "celma/prog_args.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgHLongArgAbbrTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
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
      const ArgString2Array  as2a( "--in 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   {
      const ArgString2Array  as2a( "--inp 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   {
      const ArgString2Array  as2a( "--inpu 5", nullptr);

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
      const ArgString2Array  as2a( "--inpl 5", nullptr);

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
      const ArgString2Array  as2a( "--ou 5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( outputVal.hasValue());
      BOOST_REQUIRE_EQUAL( outputVal.value(), 5);

      BOOST_REQUIRE( !inputVal.hasValue());
      BOOST_REQUIRE( !inplaceVal.hasValue());
   } // end scope

} // long_arg_abbr



// =====  END OF test_argh_longarg_abbr.cpp  =====

