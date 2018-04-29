
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of bitsets by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestBitsetTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;



/// Test error case that can occur with a bitset.
/// @since
///    1.4.3, 29.04.2018
BOOST_AUTO_TEST_CASE( test_bitset_errors)
{

   // assign wrong value types
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values"));

      ArgString2Array  as2a( "-b this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::bad_cast);
   } // end scope

   // try to set a bit that is outside the range of the bitset
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values"));

      ArgString2Array  as2a( "-b 25", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

   // try to set a bit that is outside the range of the bitset
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values"));

      ArgString2Array  as2a( "-b 3,25", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

} // test_bitset_errors



/// Test feature to set another character as list separator.
/// @since
///    1.4.3, 29.04.2018
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values"));

      ArgString2Array  as2a( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 3);
      BOOST_REQUIRE( b[ 4]);
      BOOST_REQUIRE( b[ 5]);
      BOOST_REQUIRE( b[ 6]);
   } // end scope

   // now check with another list separator
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values")
         ->setListSep( '.'));

      ArgString2Array  as2a( "-b 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 3);
      BOOST_REQUIRE( b[ 4]);
      BOOST_REQUIRE( b[ 5]);
      BOOST_REQUIRE( b[ 6]);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple values.
/// @since
///    1.4.3, 29.04.2018
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values"));

      ArgString2Array  as2a( "-b 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler  ah( 0);
      std::bitset< 10>  b;
      int  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      ArgString2Array  as2a( "-b 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 3);
      BOOST_REQUIRE( b[ 4]);
      BOOST_REQUIRE( b[ 5]);
      BOOST_REQUIRE( b[ 6]);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values")
         ->setTakesMultiValue());

      ArgString2Array  as2a( "-b 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 5);
      BOOST_REQUIRE( b[ 4]);
      BOOST_REQUIRE( b[ 5]);
      BOOST_REQUIRE( b[ 6]);
      BOOST_REQUIRE( b[ 7]);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler  ah( 0);
      std::bitset< 10>  b;
      int  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      ArgString2Array  as2a( "-b 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler  ah( Handler::hfEndValues);
      std::bitset< 10>  b;
      int  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      ArgString2Array  as2a( "-b 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 4);
      BOOST_REQUIRE( b[ 4]);
      BOOST_REQUIRE( b[ 5]);
      BOOST_REQUIRE( b[ 6]);
      BOOST_REQUIRE( b[ 7]);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
/// @since
///    1.4.3, 29.04.2018
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      b.set( 2);
      b.set( 3);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values"));

      ArgString2Array  as2a( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 5);
      BOOST_REQUIRE( b[ 2]);
      BOOST_REQUIRE( b[ 3]);
      BOOST_REQUIRE( b[ 4]);
      BOOST_REQUIRE( b[ 5]);
      BOOST_REQUIRE( b[ 6]);
   } // end scope

   // now the default values should be cleared
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      b.set( 2);
      b.set( 3);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values")
         ->setClearBeforeAssign());

      ArgString2Array  as2a( "-b 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 2);
      BOOST_REQUIRE( b[ 4]);
      BOOST_REQUIRE( b[ 5]);
   } // end scope

} // test_clear_dest



/// Test feature to reset the flags instead of setting them.
/// @since
///    1.4.3, 29.04.2018
BOOST_AUTO_TEST_CASE( test_resetting_flags)
{

   // simple case of unsetting the flags
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      b.set( 2);
      b.set( 4);
      b.set( 5);
      b.set( 6);
      b.set( 7);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values")
         ->unsetFlag());

      ArgString2Array  as2a( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 2);
      BOOST_REQUIRE( b[ 2]);
      BOOST_REQUIRE( b[ 7]);
   } // end scope

   // combination of multiple features
   {
      Handler  ah( 0);
      std::bitset< 10>  b;

      b.set( 2);
      b.set( 4);
      b.set( 5);
      b.set( 6);
      b.set( 7);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values")
         ->unsetFlag()->setTakesMultiValue()->setListSep( '.'));

      ArgString2Array  as2a( "-b 4.5.6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( b.count(), 1);
      BOOST_REQUIRE( b[ 2]);
   } // end scope

} // test_list_sep



// =====  END OF test_argh_dest_bitset.cpp  =====

