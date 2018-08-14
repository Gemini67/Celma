
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
**    Test program for using a level counter as destination variable in the
**    argument handler, using the Boost.Test framework.
**
--*/


// Boost includes
#define BOOST_TEST_MODULE ArgHDestLevelCounterTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/level_counter.hpp"
#include "celma/prog_args.hpp"
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;
using celma::prog_args::LevelCounter;



/// Verify that errors are detected correctly.
///
/// @since  x.y.z, 13.08.2018
BOOST_AUTO_TEST_CASE( error_cases)
{

   // mixing increment and assignment should throw
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level"));

      const ArgString2Array  as2a( "-v -v 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

   // mixing assignment and increment should throw too
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level"));

      const ArgString2Array  as2a( "-v 5 -v", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

   // trying multiple assignments should throw
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level"));

      const ArgString2Array  as2a( "-v 5 -v 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

   // turn off assignment, then it should throw
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->setValueMode( Handler::ValueMode::none));

      const ArgString2Array  as2a( "-v 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

   // turn off increment (no value), then it should throw
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->setValueMode( Handler::ValueMode::required));

      const ArgString2Array  as2a( "-v", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

} // error_cases



/// Increment the level counter just once.
///
/// @since  x.y.z, 13.08.2018
BOOST_AUTO_TEST_CASE( used_once)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level"));

   const ArgString2Array  as2a( "-v", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 1);

} // used_once



/// Increment the level counter multiple times through multiple uses of the
/// single character argument.
///
/// @since  x.y.z, 13.08.2018
BOOST_AUTO_TEST_CASE( multiple_increment_in_one_arg)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level"));

   const ArgString2Array  as2a( "-vvv", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 3);

} // multiple_increment_in_one_arg



/// Increment the level by multiple uses of the argument.
///
/// @since  x.y.z, 13.08.2018
BOOST_AUTO_TEST_CASE( multiple_increment_args)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level"));

   const ArgString2Array  as2a( "-v -vv -vvv", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 6);

} // multiple_increment_args



/// Check assigning a new level.
///
/// @since  x.y.z, 13.08.2018
BOOST_AUTO_TEST_CASE( assign_level)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level"));

   const ArgString2Array  as2a( "--verbose 4", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 4);

} // assign_level



/// Check that a defined maximum level is not exceeded.
///
/// @since  x.y.z, 13.08.2018
BOOST_AUTO_TEST_CASE( max_value)
{

   using celma::prog_args::upper;

   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->addCheck( upper( 5)));

      const ArgString2Array  as2a( "-v -vv -vvv", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->addCheck( upper( 5)));

      const ArgString2Array  as2a( "-v 6", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::runtime_error);
   } // end scope

} // max_value



// =====  END OF test_argh_dest_level_counter.cpp  =====

