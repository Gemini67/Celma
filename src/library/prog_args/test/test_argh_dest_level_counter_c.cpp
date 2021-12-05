
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using a level counter as destination variable in the
**    argument handler, using the Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE ArgHDestLevelCounterTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/prog_args/level_counter.hpp"


using celma::prog_args::Handler;
using celma::prog_args::LevelCounter;


namespace {


enum class VerboseLevels
{
   none = 0,
   low = 1,
   medium = 2,
   high = 3
};


class EnumFormatter final : public celma::prog_args::detail::IFormat
{
public:
   /// Constructor, sets the formatters name in the base class.
   ///
   /// @since  1.33.0, 05.11.2019
   EnumFormatter():
      IFormat( "enum-formatter")
   {
   } // EnumFormatter::EnumFormatter

   /// Empty, virtual destructor.
   ///
   /// @since  1.23.0, 09.04.2019
   ~EnumFormatter() override = default;

   /// Returns the value of the enum as string in \a val.
   ///
   /// @param[in,out]  val  The value to change the formatting of.
   /// @since  1.23.0, 09.04.2019
   void formatValue( std::string& val) const override
   {
      if (val == "none")
         val = "0";
      else if (val == "low")
         val = "1";
      else if (val == "medium")
         val = "2";
      else if (val == "high")
         val = "3";
      else
         throw std::runtime_error( "'" + val + "' is not a valid enum name");
   } // EnumFormatter::formatValue

}; // EnumFormatter


} // namespace



/// Verify that errors are detected correctly.
///
/// @since  1.11.0, 13.08.2018
BOOST_AUTO_TEST_CASE( error_cases)
{

   // trying to set the level-counter specific "allow mixing of increment and
   // assignment" feature on other data types should throw
   {
      Handler       ah( 0);
      int           int_var;
      std::string   string_var;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( int_var),
         "int var")->setAllowMixIncSet(), std::invalid_argument);

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( string_var),
         "string var")->setAllowMixIncSet(), std::invalid_argument);
   } // end scope

   // mixing increment and assignment should throw
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v -v 5"),
         std::runtime_error);
   } // end scope

   // mixing assignment and increment should throw too
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 5 -v"),
         std::runtime_error);
   } // end scope

   // trying multiple assignments should throw
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 5 -v 7"),
         std::runtime_error);
   } // end scope

   // turn off assignment, then it should throw
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->setValueMode( Handler::ValueMode::none));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 5"),
         std::invalid_argument);
   } // end scope

   // turn off increment (no value), then it should throw
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->setValueMode( Handler::ValueMode::required));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v"),
         celma::prog_args::argument_error);
   } // end scope

   // try to set value mode "command" on a level counter
   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->setValueMode( Handler::ValueMode::command),
         std::invalid_argument);
   } // end scope

} // error_cases



/// Increment the level counter just once.
///
/// @since  1.11.0, 13.08.2018
BOOST_AUTO_TEST_CASE( used_once)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level"));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v"));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 1);

} // used_once



/// Increment the level counter multiple times through multiple uses of the
/// single character argument.
///
/// @since  1.11.0, 13.08.2018
BOOST_AUTO_TEST_CASE( multiple_increment_in_one_arg)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level"));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-vvv"));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 3);

} // multiple_increment_in_one_arg



/// Increment the level by multiple uses of the argument.
///
/// @since  1.11.0, 13.08.2018
BOOST_AUTO_TEST_CASE( multiple_increment_args)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level"));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v -vv -vvv"));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 6);

} // multiple_increment_args



/// Check assigning a new level.
///
/// @since  1.11.0, 13.08.2018
BOOST_AUTO_TEST_CASE( assign_level)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level"));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--verbose 4"));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 4);

} // assign_level



/// Check that a defined maximum level is not exceeded.
///
/// @since  1.11.0, 13.08.2018
BOOST_AUTO_TEST_CASE( max_value)
{

   using celma::prog_args::upper;

   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->addCheck( upper( 5)));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v -vv -vvv"),
         std::runtime_error);
   } // end scope

   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->addCheck( upper( 5)));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 6"),
         std::runtime_error);
   } // end scope

} // max_value



/// Check that mixing increment and assignment works when enabled.
///
/// @since  1.11.0, 20.08.2018
BOOST_AUTO_TEST_CASE( mixing_arguments)
{

   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->setAllowMixIncSet());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v -v 5"));
      BOOST_REQUIRE_EQUAL( verbose_level.value(), 5);
   } // end scope

   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->setAllowMixIncSet());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 5 -vv"));
      BOOST_REQUIRE_EQUAL( verbose_level.value(), 7);
   } // end scope

   {
      Handler       ah( 0);
      LevelCounter  verbose_level;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
         "verbose level")->setAllowMixIncSet());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 5 -v 7"));
      BOOST_REQUIRE_EQUAL( verbose_level.value(), 7);
   } // end scope

} // mixing_arguments



/// Use the symbolic names of an enum to set the level.
///
/// @since  1.23.0, 09.04.2019
BOOST_AUTO_TEST_CASE( level_through_enum)
{

   Handler       ah( 0);
   LevelCounter  verbose_level;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v,verbose", DEST_VAR( verbose_level),
      "verbose level")->addFormat( new EnumFormatter()));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v low"));
   BOOST_REQUIRE_EQUAL( verbose_level.value(), 1);

} // level_through_enum



// =====  END OF test_argh_dest_level_counter_c.cpp  =====

