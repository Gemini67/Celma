
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of unordered sets by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestUnorderedSetTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;



/// Test error case that can occur with an unordered set.
///
/// @since  1.34.0, 06.12.2019
BOOST_AUTO_TEST_CASE( test_unordered_set_errors)
{

   // try to set invalid value mode
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but the unordered set is
   // empty
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v this,should,throw"),
         std::bad_cast);
   } // end scope

} // test_unordered_set_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.34.0, 06.12.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler                   ah( 0);
   std::unordered_set< int>  us = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.34.0, 06.12.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6"));

      BOOST_REQUIRE_EQUAL( us.size(), 6);
      BOOST_REQUIRE( us.find( 4) != us.end());
      BOOST_REQUIRE( us.find( 5) != us.end());
      BOOST_REQUIRE( us.find( 6) != us.end());
   } // end scope

   // now check with a custom list separator
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setListSep( '.'));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4.5.6"));

      BOOST_REQUIRE_EQUAL( us.size(), 6);
      BOOST_REQUIRE( us.find( 4) != us.end());
      BOOST_REQUIRE( us.find( 5) != us.end());
      BOOST_REQUIRE( us.find( 6) != us.end());
   } // end scope

} // test_list_sep



/// Test feature to handle multiple values.
///
/// @since  1.34.0, 06.12.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 4,5,6 7"),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};
      int                       free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7"));

      BOOST_REQUIRE_EQUAL( us.size(), 6);
      BOOST_REQUIRE( us.find( 4) != us.end());
      BOOST_REQUIRE( us.find( 5) != us.end());
      BOOST_REQUIRE( us.find( 6) != us.end());
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7 8"));

      BOOST_REQUIRE_EQUAL( us.size(), 8);
      BOOST_REQUIRE( us.find( 4) != us.end());
      BOOST_REQUIRE( us.find( 5) != us.end());
      BOOST_REQUIRE( us.find( 6) != us.end());
      BOOST_REQUIRE( us.find( 7) != us.end());
      BOOST_REQUIRE( us.find( 8) != us.end());
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};
      int                       free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 4,5,6 7 --endvalues 8"),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler                   ah( Handler::hfEndValues);
      std::unordered_set< int>  us = { 1, 2, 3};
      int                       free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7 --endvalues 8"));

      BOOST_REQUIRE_EQUAL( us.size(), 7);
      BOOST_REQUIRE( us.find( 4) != us.end());
      BOOST_REQUIRE( us.find( 5) != us.end());
      BOOST_REQUIRE( us.find( 6) != us.end());
      BOOST_REQUIRE( us.find( 7) != us.end());
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.34.0, 06.12.2019
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6"));

      BOOST_REQUIRE_EQUAL( us.size(), 6);
      BOOST_REQUIRE( us.find( 4) != us.end());
      BOOST_REQUIRE( us.find( 5) != us.end());
      BOOST_REQUIRE( us.find( 6) != us.end());
   } // end scope

   // now the default values should be cleared
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setClearBeforeAssign());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5"));

      BOOST_REQUIRE_EQUAL( us.size(), 2);
      BOOST_REQUIRE( us.find( 4) != us.end());
      BOOST_REQUIRE( us.find( 5) != us.end());
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5 6,7,8"));

      BOOST_REQUIRE_EQUAL( us.size(), 5);
      BOOST_REQUIRE( us.find( 4) != us.end());
      BOOST_REQUIRE( us.find( 5) != us.end());
      BOOST_REQUIRE( us.find( 6) != us.end());
      BOOST_REQUIRE( us.find( 7) != us.end());
      BOOST_REQUIRE( us.find( 8) != us.end());
   } // end scope

   // set default values, make argument optional, unordered set should be empty
   // when argument is used with value(s)
   {
      Handler                   ah( 0);
      std::unordered_set< int>  us = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v"));
      BOOST_REQUIRE( us.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the
/// unordered set.
///
/// @since  1.34.0, 06.12.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                           ah( 0);
   std::unordered_set< std::string>  us;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( us), "values")
      ->addFormat( celma::prog_args::lowercase()));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v monday,TUESDAY,wEdNeSdAy"));

   BOOST_REQUIRE_EQUAL( us.size(), 3);
   BOOST_REQUIRE( us.find( "monday") != us.end());
   BOOST_REQUIRE( us.find( "tuesday") != us.end());
   BOOST_REQUIRE( us.find( "wednesday") != us.end());

} // format_values



/// Test "list argument values" with an unordered set.
///
/// @since  1.34.0, 06.12.2019
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream                std_out;
   std::ostringstream                std_err;
   Handler                           ah( std_out, std_err, Handler::hfListArgVar);
   std::unordered_set< std::string>  us;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( us), "values")
      ->addFormat( celma::prog_args::lowercase()));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
      "-s MONDAY,tuesday,wEdNeSdAy --list-arg-vars"));

   BOOST_REQUIRE( !std_out.str().empty());
   // std::cerr << std_out.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::unordered_set<std::string>', destination container 'us', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::unordered_set<std::string>', destination container 'us', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



// =====  END OF test_argh_dest_unordered_set_c.cpp  =====

