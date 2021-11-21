
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
**    Test program for the special handling of maps by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <map>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestMapTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/check_for.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;



/// Test error case that can occur with a map.
///
/// @since  1.41.0, 16.02.2020
BOOST_AUTO_TEST_CASE( test_map_errors)
{

   // try to set invalid value mode
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but map empty
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // try to add a formatter for a specific position
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->addFormatPos( 1, celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-m this,should;throw,immediately"),
         std::bad_cast);
   } // end scope

   // cannot use same character as list and pair separator
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setPairFormat( ";"), std::invalid_argument);
   } // end scope

   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setListSep( '+')->setPairFormat( "+"), std::invalid_argument);
   } // end scope

   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")->
         setPairFormat( ";{}"), std::invalid_argument);
   } // end scope

   // wrong format of values in argument list
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-m this;should;throw;immediately"),
         std::runtime_error);
   } // end scope

   // a map cannot be sorted
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setSortData(), std::logic_error);
   } // end scope

   // try to set the same separator as list and pair separator
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setListSep( ','), std::invalid_argument);
   } // end scope

   // wrong length of separator string
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setPairFormat( ""), std::invalid_argument);
   } // end scope
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setPairFormat( "ab"), std::invalid_argument);
   } // end scope
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setPairFormat( "abcd"), std::invalid_argument);
   } // end scope

} // test_map_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.41.0, 16.02.2020
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler                      ah( 0);
   std::map< int, std::string>  m;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.41.0, 16.02.2020
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 4,four;5,five;6,six"));
      BOOST_REQUIRE_EQUAL( m.size(), 3);

      CHECK_FOR (auto map_iter : m)
      {
         switch (counter)
         {
         case 1:
            BOOST_REQUIRE_EQUAL( map_iter.first, 4);
            BOOST_REQUIRE_EQUAL( map_iter.second, "four");
            break;
         case 2:
            BOOST_REQUIRE_EQUAL( map_iter.first, 5);
            BOOST_REQUIRE_EQUAL( map_iter.second, "five");
            break;
         case 3:
            BOOST_REQUIRE_EQUAL( map_iter.first, 6);
            BOOST_REQUIRE_EQUAL( map_iter.second, "six");
            break;
         default:
            BOOST_REQUIRE( counter == 0);
            break;
         } // end switch
      } // end for
      CHECK_FOR_COUNT( 3);
   } // end scope

   // now check with a custom list separator
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setListSep( '+')->setPairFormat( "-"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 4-four+5-five+6-six"));
      BOOST_REQUIRE_EQUAL( m.size(), 3);

      CHECK_FOR (auto map_iter : m)
      {
         switch (counter)
         {
         case 1:
            BOOST_REQUIRE_EQUAL( map_iter.first, 4);
            BOOST_REQUIRE_EQUAL( map_iter.second, "four");
            break;
         case 2:
            BOOST_REQUIRE_EQUAL( map_iter.first, 5);
            BOOST_REQUIRE_EQUAL( map_iter.second, "five");
            break;
         case 3:
            BOOST_REQUIRE_EQUAL( map_iter.first, 6);
            BOOST_REQUIRE_EQUAL( map_iter.second, "six");
            break;
         default:
            BOOST_REQUIRE( counter == 0);
            break;
         } // end switch
      } // end for
      CHECK_FOR_COUNT( 3);
   } // end scope

   // specify a pair format, but the values don't match the format
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setPairFormat( ",{}"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-m (4,four);(5,five)"),
         std::runtime_error);
   } // end scope

   // and now with a special pair format
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setPairFormat( ",{}"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m {4,four};{5,five};{6,six}"));
      BOOST_REQUIRE_EQUAL( m.size(), 3);

      CHECK_FOR (auto map_iter : m)
      {
         switch (counter)
         {
         case 1:
            BOOST_REQUIRE_EQUAL( map_iter.first, 4);
            BOOST_REQUIRE_EQUAL( map_iter.second, "four");
            break;
         case 2:
            BOOST_REQUIRE_EQUAL( map_iter.first, 5);
            BOOST_REQUIRE_EQUAL( map_iter.second, "five");
            break;
         case 3:
            BOOST_REQUIRE_EQUAL( map_iter.first, 6);
            BOOST_REQUIRE_EQUAL( map_iter.second, "six");
            break;
         default:
            BOOST_REQUIRE( counter == 0);
            break;
         } // end switch
      } // end for
      CHECK_FOR_COUNT( 3);
   } // end scope

} // test_list_sep



/// Test that the cardinality is checked correctly.
///
/// @since  1.41.0, 16.02.2020
BOOST_AUTO_TEST_CASE( test_cardinality)
{

   Handler                      ah( 0);
   std::map< int, std::string>  m;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
      ->setCardinality( celma::prog_args::cardinality_max( 3)));

   BOOST_REQUIRE_THROW( evalArgumentString( ah, "-m 4,four;5,five;6,six;7,seven"),
      std::runtime_error);

} // test_cardinality



/// Check that formatting the values works.
///
/// @since  1.41.0, 13.07.2020
BOOST_AUTO_TEST_CASE( formatting)
{

   Handler                              ah( 0);
   std::map< std::string, std::string>  m;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
      ->addFormatKey( celma::prog_args::lowercase())
      ->addFormatValue( celma::prog_args::uppercase()));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m One,einS;tWo,ZwEi;ThReE,dREI"));
   BOOST_REQUIRE_EQUAL( m.size(), 3);

   CHECK_FOR (auto const& v : m)
   {
      switch (counter)
      {
      case 1:
         BOOST_REQUIRE_EQUAL( v.first, "one");
         BOOST_REQUIRE_EQUAL( v.second, "EINS");
         break;
      case 2:
         BOOST_REQUIRE_EQUAL( v.first, "three");
         BOOST_REQUIRE_EQUAL( v.second, "DREI");
         break;
      case 3:
         BOOST_REQUIRE_EQUAL( v.first, "two");
         BOOST_REQUIRE_EQUAL( v.second, "ZWEI");
         break;
      default:
         BOOST_REQUIRE( counter == 0);
         break;
      } // end switch
   } // end for
   CHECK_FOR_COUNT( 3);

} // test_cardinality



/// Test feature to handle multiple, separate values.
///
/// @since  1.41.0, 17.02.2020
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-s 4,four;5,five;6,six 7,seven"),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;
      int                          free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 4,four;5,five;6,six 7"));
      BOOST_REQUIRE_EQUAL( m.size(), 3);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;
      int                          free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 4,four;5,five;6,six 7,seven 8,eight"));
      BOOST_REQUIRE_EQUAL( m.size(), 5);
      BOOST_REQUIRE_EQUAL( free, -1);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;
      int                          free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-m 4,four;5,five;6,six 7,seven "
         "--endvalues 8"),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler                      ah( Handler::hfEndValues);
      std::map< int, std::string>  m;
      int                          free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 4,four;5,five;6,six 7,seven "
         "--endvalues 8"));
      BOOST_REQUIRE_EQUAL( m.size(), 4);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.41.0, 16.02.2020
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 4,four;5,five;6,six"));
      BOOST_REQUIRE_EQUAL( m.size(), 6);

      int  idx = 0;
      for (auto map_iter : m)
      {
         switch (idx)
         {
         case 0:
            BOOST_REQUIRE_EQUAL( map_iter.first, 1);
            BOOST_REQUIRE_EQUAL( map_iter.second, "one");
            break;
         case 1:
            BOOST_REQUIRE_EQUAL( map_iter.first, 2);
            BOOST_REQUIRE_EQUAL( map_iter.second, "two");
            break;
         case 2:
            BOOST_REQUIRE_EQUAL( map_iter.first, 3);
            BOOST_REQUIRE_EQUAL( map_iter.second, "three");
            break;
         case 3:
            BOOST_REQUIRE_EQUAL( map_iter.first, 4);
            BOOST_REQUIRE_EQUAL( map_iter.second, "four");
            break;
         case 4:
            BOOST_REQUIRE_EQUAL( map_iter.first, 5);
            BOOST_REQUIRE_EQUAL( map_iter.second, "five");
            break;
         case 5:
            BOOST_REQUIRE_EQUAL( map_iter.first, 6);
            BOOST_REQUIRE_EQUAL( map_iter.second, "six");
            break;
         default:
            BOOST_REQUIRE( idx < 6);
            break;
         } // end switch

         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 6);
   } // end scope

   // now the default values should be cleared
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setClearBeforeAssign());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 4,four;5,five"));
      BOOST_REQUIRE_EQUAL( m.size(), 2);

      int  idx = 0;
      for (auto map_iter : m)
      {
         switch (idx)
         {
         case 0:
            BOOST_REQUIRE_EQUAL( map_iter.first, 4);
            BOOST_REQUIRE_EQUAL( map_iter.second, "four");
            break;
         case 1:
            BOOST_REQUIRE_EQUAL( map_iter.first, 5);
            BOOST_REQUIRE_EQUAL( map_iter.second, "five");
            break;
         default:
            BOOST_REQUIRE( idx < 2);
            break;
         } // end switch

         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 2);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 4,four;5,five 6,six;7,seven;8,eight"));
      BOOST_REQUIRE_EQUAL( m.size(), 5);

      int  idx = 0;
      for (auto map_iter : m)
      {
         switch (idx)
         {
         case 0:
            BOOST_REQUIRE_EQUAL( map_iter.first, 4);
            BOOST_REQUIRE_EQUAL( map_iter.second, "four");
            break;
         case 1:
            BOOST_REQUIRE_EQUAL( map_iter.first, 5);
            BOOST_REQUIRE_EQUAL( map_iter.second, "five");
            break;
         case 2:
            BOOST_REQUIRE_EQUAL( map_iter.first, 6);
            BOOST_REQUIRE_EQUAL( map_iter.second, "six");
            break;
         case 3:
            BOOST_REQUIRE_EQUAL( map_iter.first, 7);
            BOOST_REQUIRE_EQUAL( map_iter.second, "seven");
            break;
         case 4:
            BOOST_REQUIRE_EQUAL( map_iter.first, 8);
            BOOST_REQUIRE_EQUAL( map_iter.second, "eight");
            break;
         default:
            BOOST_REQUIRE( idx < 5);
            break;
         } // end switch

         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 5);
   } // end scope

   // set default values, make argument optional, map should be empty when
   // argument is used without value(s)
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m"));
      BOOST_REQUIRE( m.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the map.
///
/// @since  1.41.0, 17.02.2020
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                      ah( 0);
   std::map< int, std::string>  m;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
      ->addFormatValue( celma::prog_args::lowercase()));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 1,monday;2,TUESDAY;3,wEdNeSdAy"));
   BOOST_REQUIRE_EQUAL( m.size(), 3);

   for (auto map_iter : m)
   {
      if (map_iter.first == 1)
      {
         BOOST_REQUIRE_EQUAL( map_iter.second, "monday");
      } else if (map_iter.first == 2)
      {
         BOOST_REQUIRE_EQUAL( map_iter.second, "tuesday");
      } else
      {
         BOOST_REQUIRE_EQUAL( map_iter.second, "wednesday");
      } // end if
   } // end for

} // format_values



/// Test feature that only unique values should be stored in the map.
/// Setting the same value multiple times would simply ignore those where the
/// key already exists in the map.
///
/// @since  1.41.0, 20.02.2020
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values overwrite silently
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( m), "values"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,two;3,three;4,four;4,five;6,six;7,seven"));
      BOOST_REQUIRE_EQUAL( m.size(), 5);

      int  idx = 0;
      for (auto map_iter : m)
      {
         switch (idx)
         {
         case 0:
            BOOST_REQUIRE_EQUAL( map_iter.first, 2);
            BOOST_REQUIRE_EQUAL( map_iter.second, "two");
            break;
         case 1:
            BOOST_REQUIRE_EQUAL( map_iter.first, 3);
            BOOST_REQUIRE_EQUAL( map_iter.second, "three");
            break;
         case 2:
            BOOST_REQUIRE_EQUAL( map_iter.first, 4);
            BOOST_REQUIRE_EQUAL( map_iter.second, "four");
            break;
         case 3:
            BOOST_REQUIRE_EQUAL( map_iter.first, 6);
            BOOST_REQUIRE_EQUAL( map_iter.second, "six");
            break;
         case 4:
            BOOST_REQUIRE_EQUAL( map_iter.first, 7);
            BOOST_REQUIRE_EQUAL( map_iter.second, "seven");
            break;
         default:
            BOOST_REQUIRE( idx < 5);
            break;
         } // end switch

         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 5);
   } // end scope

   // mode "ignore unique data without errors" can be set, even when it does not
   // make much sense
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( m), "values")
         ->setUniqueData());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,two;3,three;4,four;4,five;6,six;7,seven"));
      BOOST_REQUIRE_EQUAL( m.size(), 5);

      int  idx = 0;
      for (auto map_iter : m)
      {
         switch (idx)
         {
         case 0:
            BOOST_REQUIRE_EQUAL( map_iter.first, 2);
            BOOST_REQUIRE_EQUAL( map_iter.second, "two");
            break;
         case 1:
            BOOST_REQUIRE_EQUAL( map_iter.first, 3);
            BOOST_REQUIRE_EQUAL( map_iter.second, "three");
            break;
         case 2:
            BOOST_REQUIRE_EQUAL( map_iter.first, 4);
            BOOST_REQUIRE_EQUAL( map_iter.second, "four");
            break;
         case 3:
            BOOST_REQUIRE_EQUAL( map_iter.first, 6);
            BOOST_REQUIRE_EQUAL( map_iter.second, "six");
            break;
         case 4:
            BOOST_REQUIRE_EQUAL( map_iter.first, 7);
            BOOST_REQUIRE_EQUAL( map_iter.second, "seven");
            break;
         default:
            BOOST_REQUIRE( idx < 5);
            break;
         } // end switch

         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 5);
   } // end scope

   // duplicates should lead to an error, also when conflicting with pre-set
   // values
   {
      Handler                      ah( 0);
      std::map< int, std::string>  m = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( m), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 2,two;4,four 6,six;7,seven"),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test "list argument values" with a map.
///
/// @since  1.41.0, 20.02.2020
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream           std_out;
   std::ostringstream           std_err;
   Handler                      ah( std_out, std_err, Handler::hfListArgVar);
   std::map< int, std::string>  m;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( m), "values")
      ->addFormatValue( celma::prog_args::lowercase()));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
      "-m 1,MONDAY;2,tuesday;3,wEdNeSdAy --list-arg-vars"));

   BOOST_REQUIRE( !std_out.str().empty());
   // std::cerr << std_out.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-m' value type 'std::map<int,std::string>', destination container 'm', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-m' value type 'std::map<int,std::string>', destination container 'm', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



/// Test constraint "disjoint" with two maps.
///
/// @since  1.41.0, 20.02.2020
BOOST_AUTO_TEST_CASE( disjoint_maps)
{

   using celma::prog_args::disjoint;

   {
      Handler                      ah( 0);
      std::map< int, std::string>  map1;
      std::map< int, std::string>  map2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( map1), "left"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( map2), "right"));

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( disjoint( "l;r")));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-l 1,one;2,two;3,three -r 4,four;5,five;6,six"));
   } // end scope

   // throw if the data in the sets is not disjoint
   {
      Handler                      ah( 0);
      std::map< int, std::string>  map1;
      std::map< int, std::string>  map2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( map1), "left"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( map2), "right"));

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( disjoint( "l;r")));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-l 1,one;2,two;3,three "
         "-r 4,four;5,five;6,six;1,one"),
         std::runtime_error);
   } // end scope

} // disjoint_maps



// =====  END OF test_argh_dest_map_c.cpp  =====

