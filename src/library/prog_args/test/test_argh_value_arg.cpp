
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
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


// Boost includes
#define BOOST_TEST_MODULE ArgHValueArgTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/arg_string_2_array.hpp"


using celma::common::ArgString2Array;
using celma::prog_args::Handler;



/// Test handling of errors.
/// @since  x.y.z, 25.09.2017
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

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           std::runtime_error);
   } // end scope

} // test_errors



/// Test correct usage of a value argument.
/// @since  x.y.z, 15.11.2017
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

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
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

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
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

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
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

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( my_dest, -1);
   } // end scope

} // test_value_arg



// =====================  END OF test_argh_value_arg.cpp  =====================

