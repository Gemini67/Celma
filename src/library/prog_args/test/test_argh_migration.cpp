
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
**    Test program for the argument migration related features in the module
**    "argument handling", using the Boost.Test module.
**
--*/


// C++ Standard Library includes
#include <sstream>
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE ArgMigrationTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;



/// Error case: An argument cannot be both mandatory and deprecated.
/// @since
///    1.6.0, 29.06.2018
BOOST_AUTO_TEST_CASE( feature_clash)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   int                  old_arg = 0;


   BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
      ->setIsDeprecated()->setIsMandatory(), std::logic_error);
   BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
      ->setIsMandatory()->setIsDeprecated(), std::logic_error);

} // feature_clash



/// Using a deprecated argument should throw.
/// @since
///    1.6.0, 29.06.2018
BOOST_AUTO_TEST_CASE( invalid_use_of_deprecated_argument)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   int                  old_arg = 0;
   std::string          new_arg;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
      ->setIsDeprecated());
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( new_arg), "string"));

   const ArgString2Array  as2a( "-i 25", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
      std::runtime_error);

} // invalid_use_of_deprecated_argument



/// Using a replaced argument should throw.
/// @since
///    1.6.0, 03.07.2018
BOOST_AUTO_TEST_CASE( invalid_use_of_replaced_argument)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   int                  old_arg = 0;
   std::string          new_arg;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( old_arg), "integer")
      ->setReplacedBy( "-s"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( new_arg), "string"));

   const ArgString2Array  as2a( "-i 25", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
      std::runtime_error);

} // invalid_use_of_replaced_argument



// =====  END OF test_argh_migration.cpp  =====
