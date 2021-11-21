
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "destination start/end pair" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgHDestStartEndTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"


using celma::prog_args::Handler;



/// Check the different combinations that are possible with two variables used
/// as start/end pair.
///
/// @since  1.41.2, 21.07.2020
BOOST_AUTO_TEST_CASE( combinations)
{

   // set only start date, sets both
   {
      Handler  ah( 0);
      int      start_date = 0;
      int      end_date = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s",
         DEST_START_END( start_date, end_date), "the start date"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e",
         DEST_START_END( end_date, start_date), "the end date"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-s 20200610"));
      BOOST_REQUIRE_EQUAL( start_date, 20200610);
      BOOST_REQUIRE_EQUAL( end_date, 20200610);
   } // end scope

   // set only end date, sets both
   {
      Handler  ah( 0);
      int      start_date = 0;
      int      end_date = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s",
         DEST_START_END( start_date, end_date), "the start date"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e",
         DEST_START_END( end_date, start_date), "the end date"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-e 20200610"));
      BOOST_REQUIRE_EQUAL( start_date, 20200610);
      BOOST_REQUIRE_EQUAL( end_date, 20200610);
   } // end scope

   // set start and end date
   {
      Handler  ah( 0);
      int      start_date = 0;
      int      end_date = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s",
         DEST_START_END( start_date, end_date), "the start date"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e",
         DEST_START_END( end_date, start_date), "the end date"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-s 20200610 -e 20200721"));
      BOOST_REQUIRE_EQUAL( start_date, 20200610);
      BOOST_REQUIRE_EQUAL( end_date, 20200721);
   } // end scope

   // set start and end date
   {
      Handler  ah( 0);
      int      start_date = 0;
      int      end_date = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s",
         DEST_START_END( start_date, end_date), "the start date"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e",
         DEST_START_END( end_date, start_date), "the end date"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-e 20200721 -s 20200610"));
      BOOST_REQUIRE_EQUAL( start_date, 20200610);
      BOOST_REQUIRE_EQUAL( end_date, 20200721);
   } // end scope

} // combinations



// =====  END OF test_argh_dest_start_end_c.cpp  =====

