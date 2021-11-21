
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
**    Test program for the special handling of dequess by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestDequeTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;



/// Test error case that can occur with a deque.
///
/// @since  1.34.0, 05.12.2019
BOOST_AUTO_TEST_CASE( test_deque_errors)
{

   // try to set invalid value mode
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but deque empty
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v this,should,throw"),
         std::bad_cast);
   } // end scope

} // test_deque_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.34.0, 05.12.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler           ah( 0);
   std::deque< int>  d = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.34.0, 05.12.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6"));
      BOOST_REQUIRE_EQUAL( d.size(), 3);

      int  idx = 0;
      for (auto const& entry : d)
      {
         BOOST_REQUIRE( idx < 3);
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 3);
   } // end scope

   // now check with a custom list separator
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setListSep( '.'));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4.5.6"));
      BOOST_REQUIRE_EQUAL( d.size(), 3);

      int  idx = 0;
      for (auto const& entry : d)
      {
         BOOST_REQUIRE( idx < 3);
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 3);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple, separate values.
///
/// @since  1.34.0, 05.12.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 4,5,6 7"),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler           ah( 0);
      std::deque< int>  d;
      int               free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7"));
      BOOST_REQUIRE_EQUAL( d.size(), 3);

      int  idx = 0;
      for (auto const& entry : d)
      {
         BOOST_REQUIRE( idx < 3);
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 3);

      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7 8"));
      BOOST_REQUIRE_EQUAL( d.size(), 5);

      int  idx = 0;
      for (auto const& entry : d)
      {
         BOOST_REQUIRE( idx < 5);
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler           ah( 0);
      std::deque< int>  d;
      int               free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 4,5,6 7 --endvalues 8"),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler           ah( Handler::hfEndValues);
      std::deque< int>  d;
      int               free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6 7 --endvalues 8"));
      BOOST_REQUIRE_EQUAL( d.size(), 4);

      int  idx = 0;
      for (auto const& entry : d)
      {
         BOOST_REQUIRE( idx < 4);
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE( idx == 4);

      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.34.0, 05.12.2019
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler           ah( 0);
      std::deque< int>  d = { 1, 2, 3 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5,6"));
      BOOST_REQUIRE_EQUAL( d.size(), 6);

      int  idx = 0;
      for (auto const& entry : d)
      {
         BOOST_REQUIRE( idx < 6);
         BOOST_REQUIRE_EQUAL( entry, 1 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE( idx == 6);
   } // end scope

   // now the default values should be cleared
   {
      Handler           ah( 0);
      std::deque< int>  d = { 1, 2, 3 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setClearBeforeAssign());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5"));
      BOOST_REQUIRE_EQUAL( d.size(), 2);

      int  idx = 0;
      for (auto const& entry : d)
      {
         BOOST_REQUIRE( idx < 2);
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE( idx == 2);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler           ah( 0);
      std::deque< int>  d = { 1, 2, 3 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 4,5 6,7,8"));
      BOOST_REQUIRE_EQUAL( d.size(), 5);

      int  idx = 0;
      for (auto const& entry : d)
      {
         BOOST_REQUIRE( idx < 6);
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE( idx == 5);
   } // end scope

   // set default values, make argument optional, queue should be empty when
   // argument is used without value(s)
   {
      Handler           ah( 0);
      std::deque< int>  d = { 1, 2, 3 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v"));
      BOOST_REQUIRE( d.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the queue.
///
/// @since  1.34.0, 05.12.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                   ah( 0);
   std::deque< std::string>  d;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
      ->addFormat( celma::prog_args::lowercase()));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v monday,TUESDAY,wEdNeSdAy"));
   BOOST_REQUIRE_EQUAL( d.size(), 3);

   int  idx = 0;
   for (auto const& entry : d)
   {
      if (idx == 0)
         BOOST_REQUIRE_EQUAL( entry, "monday");
      else if (idx == 1)
         BOOST_REQUIRE_EQUAL( entry, "tuesday");
      else if (idx == 2)
         BOOST_REQUIRE_EQUAL( entry, "wednesday");
      else
         BOOST_REQUIRE( idx < 3);
      ++idx;
   } // end for
   BOOST_REQUIRE_EQUAL( idx, 3);

} // format_values



/// Test feature to sort the values in the queue.
///
/// @since  1.34.0, 05.12.2019
BOOST_AUTO_TEST_CASE( test_sort_values)
{

   // first check the default: values are stored as given
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 34532,9876,33,6"));
      BOOST_REQUIRE_EQUAL( d.size(), 4);

      int  idx = 0;
      for (auto const& entry : d)
      {
         if (idx == 0)
            BOOST_REQUIRE_EQUAL( entry, 34532);
         else if (idx == 1)
            BOOST_REQUIRE_EQUAL( entry, 9876);
         else if (idx == 2)
            BOOST_REQUIRE_EQUAL( entry, 33);
         else if (idx == 2)
            BOOST_REQUIRE_EQUAL( entry, 6);
         else
            BOOST_REQUIRE( idx < 4);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 4);
   } // end scope

   // now the values should be sorted
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setSortData());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 34532,9876,33,6"));
      BOOST_REQUIRE_EQUAL( d.size(), 4);

      int  idx = 0;
      for (auto const& entry : d)
      {
         if (idx == 0)
            BOOST_REQUIRE_EQUAL( entry, 6);
         else if (idx == 1)
            BOOST_REQUIRE_EQUAL( entry, 33);
         else if (idx == 2)
            BOOST_REQUIRE_EQUAL( entry, 9876);
         else if (idx == 2)
            BOOST_REQUIRE_EQUAL( entry, 34532);
         else
            BOOST_REQUIRE( idx < 4);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 4);
   } // end scope

   // should still be sorted when added as multiple values
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setSortData()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 34532,9876,33,6 42,13,4711"));
      BOOST_REQUIRE_EQUAL( d.size(), 7);

      int  idx = 0;
      for (auto const& entry : d)
      {
         switch (idx)
         {
         case 0:   BOOST_REQUIRE_EQUAL( entry,     6);  break;
         case 1:   BOOST_REQUIRE_EQUAL( entry,    13);  break;
         case 2:   BOOST_REQUIRE_EQUAL( entry,    33);  break;
         case 3:   BOOST_REQUIRE_EQUAL( entry,    42);  break;
         case 4:   BOOST_REQUIRE_EQUAL( entry,  4711);  break;
         case 5:   BOOST_REQUIRE_EQUAL( entry,  9876);  break;
         case 6:   BOOST_REQUIRE_EQUAL( entry, 34532);  break;
         default:  BOOST_REQUIRE( idx < 7);             break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 7);
   } // end scope

   // of course sorting should include pre-set values
   {
      Handler           ah( 0);
      std::deque< int>  d = { 11, 255, 17 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setSortData()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 34532,9876,33,6 42,13,4711"));
      BOOST_REQUIRE_EQUAL( d.size(), 10);

      int  idx = 0;
      for (auto const& entry : d)
      {
         switch (idx)
         {
         case 0:   BOOST_REQUIRE_EQUAL( entry,     6);  break;
         case 1:   BOOST_REQUIRE_EQUAL( entry,    11);  break;
         case 2:   BOOST_REQUIRE_EQUAL( entry,    13);  break;
         case 3:   BOOST_REQUIRE_EQUAL( entry,    17);  break;
         case 4:   BOOST_REQUIRE_EQUAL( entry,    33);  break;
         case 5:   BOOST_REQUIRE_EQUAL( entry,    42);  break;
         case 6:   BOOST_REQUIRE_EQUAL( entry,   255);  break;
         case 7:   BOOST_REQUIRE_EQUAL( entry,  4711);  break;
         case 8:   BOOST_REQUIRE_EQUAL( entry,  9876);  break;
         case 9:   BOOST_REQUIRE_EQUAL( entry, 34532);  break;
         default:  BOOST_REQUIRE( idx < 10);            break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 10);
   } // end scope

} // test_sort_values



/// Test feature that only unique values should be stored in the queue.
///
/// @since  1.34.0, 05.12.2019
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values are stored as given
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,3,4,4,6,7"));
      BOOST_REQUIRE_EQUAL( d.size(), 6);

      int  idx = 0;
      for (auto const& entry : d)
      {
         switch (idx)
         {
         case 0:   BOOST_REQUIRE_EQUAL( entry, 2);  break;
         case 1:   BOOST_REQUIRE_EQUAL( entry, 3);  break;
         case 2:   BOOST_REQUIRE_EQUAL( entry, 4);  break;
         case 3:   BOOST_REQUIRE_EQUAL( entry, 4);  break;
         case 4:   BOOST_REQUIRE_EQUAL( entry, 6);  break;
         case 5:   BOOST_REQUIRE_EQUAL( entry, 7);  break;
         default:  BOOST_REQUIRE( idx < 6);         break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 6);
   } // end scope

   // now the duplicate values should be ignored
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setUniqueData());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,3,4,4,6,7"));
      BOOST_REQUIRE_EQUAL( d.size(), 5);

      int  idx = 0;
      for (auto const& entry : d)
      {
         switch (idx)
         {
         case 0:   BOOST_REQUIRE_EQUAL( entry, 2);  break;
         case 1:   BOOST_REQUIRE_EQUAL( entry, 3);  break;
         case 2:   BOOST_REQUIRE_EQUAL( entry, 4);  break;
         case 3:   BOOST_REQUIRE_EQUAL( entry, 6);  break;
         case 4:   BOOST_REQUIRE_EQUAL( entry, 7);  break;
         default:  BOOST_REQUIRE( idx < 5);         break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 5);
   } // end scope

   // duplicates should still be ignored when added as multiple values
   {
      Handler           ah( 0);
      std::deque< int>  d;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setUniqueData()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,3,4 3,5,6"));
      BOOST_REQUIRE_EQUAL( d.size(), 5);

      int  idx = 0;
      for (auto const& entry : d)
      {
         switch (idx)
         {
         case 0:   BOOST_REQUIRE_EQUAL( entry, 2);  break;
         case 1:   BOOST_REQUIRE_EQUAL( entry, 3);  break;
         case 2:   BOOST_REQUIRE_EQUAL( entry, 4);  break;
         case 3:   BOOST_REQUIRE_EQUAL( entry, 5);  break;
         case 4:   BOOST_REQUIRE_EQUAL( entry, 6);  break;
         default:  BOOST_REQUIRE( idx < 5);         break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 5);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler           ah( 0);
      std::deque< int>  d = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setUniqueData()->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 2,3,4 3,5,6"));
      BOOST_REQUIRE_EQUAL( d.size(), 5);

      int  idx = 0;
      for (auto const& entry : d)
      {
         switch (idx)
         {
         case 0:   BOOST_REQUIRE_EQUAL( entry, 3);  break;
         case 1:   BOOST_REQUIRE_EQUAL( entry, 5);  break;
         case 2:   BOOST_REQUIRE_EQUAL( entry, 6);  break;
         case 3:   BOOST_REQUIRE_EQUAL( entry, 2);  break;
         case 4:   BOOST_REQUIRE_EQUAL( entry, 4);  break;
         default:  BOOST_REQUIRE( idx < 5);         break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 5);
   } // end scope

   // duplicates values should be treated as error
   {
      Handler           ah( 0);
      std::deque< int>  d = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( d), "values")
         ->setUniqueData( true)->setTakesMultiValue());
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 2,4 6,7"),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test "list argument values" with a deque.
///
/// @since  1.34.0, 06.12.2019
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream        std_out;
   std::ostringstream        std_err;
   Handler                   ah( std_out, std_err, Handler::hfListArgVar);
   std::deque< std::string>  d;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( d), "values")
      ->addFormat( celma::prog_args::lowercase()));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
      "-s MONDAY,tuesday,wEdNeSdAy --list-arg-vars"));

   BOOST_REQUIRE( !std_out.str().empty());
   // std::cerr << std_out.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::deque<std::string>', destination container 'd', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::deque<std::string>', destination container 'd', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



// =====  END OF test_argh_dest_deque_c.cpp  =====

