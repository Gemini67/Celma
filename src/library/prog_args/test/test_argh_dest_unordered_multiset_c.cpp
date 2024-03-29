
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
**    Test program for the special handling of unordered multi-sets by the
**    module prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestUnorderedMultiSetTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;



/// Test error case that can occur with an unordered multi-set.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( test_unordered_multiset_errors)
{

   // try to set invalid value mode
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but multi-set empty
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v this,should,throw"),
         std::bad_cast);
   } // end scope

} // test_unordered_multiset_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler                        ah( 0);
   std::unordered_multiset< int>  ums = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6"));

      BOOST_REQUIRE_EQUAL( ums.size(), 6);

      for (int i = 1; i < 7; ++i)
      {
         BOOST_REQUIRE( ums.find( i) != ums.end());
      } // end for
   } // end scope

   // now check with a custom list separator
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setListSep( '.'));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4.5.6"));

      BOOST_REQUIRE_EQUAL( ums.size(), 6);

      for (int i = 1; i < 7; ++i)
      {
         BOOST_REQUIRE( ums.find( i) != ums.end());
      } // end for
   } // end scope

} // test_list_sep



/// Test feature to handle multiple, separate values.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 4,5,6 7"),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};
      int                            free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7"));

      BOOST_REQUIRE_EQUAL( ums.size(), 6);

      for (int i = 1; i < 7; ++i)
      {
         BOOST_REQUIRE( ums.find( i) != ums.end());
      } // end for

      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7 8"));

      BOOST_REQUIRE_EQUAL( ums.size(), 8);

      for (int i = 1; i < 9; ++i)
      {
         BOOST_REQUIRE( ums.find( i) != ums.end());
      } // end for
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};
      int                            free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 4,5,6 7 --endvalues 8"),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler                        ah( Handler::hfEndValues);
      std::unordered_multiset< int>  ums = { 1, 2, 3};
      int                            free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7 --endvalues 8"));

      BOOST_REQUIRE_EQUAL( ums.size(), 7);

      for (int i = 1; i < 8; ++i)
      {
         BOOST_REQUIRE( ums.find( i) != ums.end());
      } // end for

      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6"));

      BOOST_REQUIRE_EQUAL( ums.size(), 6);

      for (int i = 1; i < 6; ++i)
      {
         BOOST_REQUIRE( ums.find( i) != ums.end());
      } // end for
   } // end scope

   // now the default values should be cleared
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setClearBeforeAssign());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5"));

      BOOST_REQUIRE_EQUAL( ums.size(), 2);

      for (int i = 4; i < 6; ++i)
      {
         BOOST_REQUIRE( ums.find( i) != ums.end());
      } // end for
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5 6,7,8"));

      BOOST_REQUIRE_EQUAL( ums.size(), 5);

      for (int i = 4; i < 9; ++i)
      {
         BOOST_REQUIRE( ums.find( i) != ums.end());
      } // end for
   } // end scope

   // set default values, make argument optional, vector should be empty when
   // argument is used without value(s)
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v"));

      BOOST_REQUIRE( ums.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the
/// unordered multi-set.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                                ah( 0);
   std::unordered_multiset< std::string>  ums;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
      ->addFormat( celma::prog_args::lowercase()));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v monday,TUESDAY,wEdNeSdAy"));

   BOOST_REQUIRE_EQUAL( ums.size(), 3);

   BOOST_REQUIRE( ums.find( "monday") != ums.end());
   BOOST_REQUIRE( ums.find( "tuesday") != ums.end());
   BOOST_REQUIRE( ums.find( "wednesday") != ums.end());

} // format_values



/// Test feature that only unique values should be stored in the unordered
/// multi-set.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values are stored as given
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,3,4,4,6,7"));

      BOOST_REQUIRE_EQUAL( ums.size(), 6);
   } // end scope

   // now the duplicate values should be ignored
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setUniqueData());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,3,4,4,6,7"));

      BOOST_REQUIRE_EQUAL( ums.size(), 5);
   } // end scope

   // duplicates should still be ignored when added as multiple values
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setUniqueData()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,3,4 3,5,6"));

      BOOST_REQUIRE_EQUAL( ums.size(), 5);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setUniqueData()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,3,4 3,5,6"));

      BOOST_REQUIRE_EQUAL( ums.size(), 5);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler                        ah( 0);
      std::unordered_multiset< int>  ums = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ums), "values")
         ->setUniqueData( true)->setTakesMultiValue());
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 2,4 6,7"),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test "list argument values" with a set.
///
/// @since  1.34.0, 18.12.2019
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream                     std_out;
   std::ostringstream                     std_err;
   Handler                                ah( std_out, std_err,
      Handler::hfListArgVar);
   std::unordered_multiset< std::string>  ums;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( ums), "values")
      ->addFormat( celma::prog_args::lowercase()));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
      "-s MONDAY,tuesday,wEdNeSdAy --list-arg-vars"));

   BOOST_REQUIRE( !std_out.str().empty());
   // std::cerr << std_out.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::unordered_multiset<std::string>', destination container 'ums', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::unordered_multiset<std::string>', destination container 'ums', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



// =====  END OF test_argh_dest_unordered_multiset_c.cpp  =====

