
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of lists by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestListTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Test error case that can occur with a list.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( test_list_errors)
{

   // try to set invalid value mode
   {
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but list empty
   {
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values"));

      auto const  as2a = make_arg_array( "-v this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

} // test_list_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler          ah( 0);
   std::list< int>  l = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 6);

      int  idx = 0;
      for (auto entry : l)
      {
         BOOST_REQUIRE_EQUAL( entry, 1 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 6);
   } // end scope

   // now check with a custom list separator
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")->
         setListSep( '.'));

      auto const  as2a = make_arg_array( "-v 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 6);

      int  idx = 0;
      for (auto entry : l)
      {
         BOOST_REQUIRE_EQUAL( entry, 1 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 6);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple values.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};
      int              free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 6);

      int  idx = 0;
      for (auto entry : l)
      {
         BOOST_REQUIRE_EQUAL( entry, 1 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 6);

      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 8);

      int  idx = 0;
      for (auto entry : l)
      {
         BOOST_REQUIRE_EQUAL( entry, 1 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 8);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};
      int              free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler          ah( Handler::hfEndValues);
      std::list< int>  l = { 1, 2, 3};
      int              free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 7);

      int  idx = 0;
      for (auto entry : l)
      {
         BOOST_REQUIRE_EQUAL( entry, 1 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 7);

      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 6);

      int  idx = 0;
      for (auto entry : l)
      {
         BOOST_REQUIRE_EQUAL( entry, 1 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 6);
   } // end scope

   // now the default values should be cleared
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-v 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 2);

      int  idx = 0;
      for (auto entry : l)
      {
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 2);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5 6,7,8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 5);

      int  idx = 0;
      for (auto entry : l)
      {
         BOOST_REQUIRE_EQUAL( entry, 4 + idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 5);
   } // end scope

   // set default values, make argument optional, list should be empty when
   // argument is used without value(s)
   {
      Handler          ah( 0);
      std::list< int>  l = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      auto const  as2a = make_arg_array( "-v", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( l.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the list.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                  ah( 0);
   std::list< std::string>  l;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-v monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( l.size(), 3);

   int  idx = 0;
   for (auto entry : l)
   {
      switch (idx)
      {
      case 0:   BOOST_REQUIRE_EQUAL( entry, "monday");     break;
      case 1:   BOOST_REQUIRE_EQUAL( entry, "tuesday");    break;
      case 2:   BOOST_REQUIRE_EQUAL( entry, "wednesday");  break;
      default:  BOOST_REQUIRE( idx < 3);                   break;
      } // end switch
      ++idx;
   } // end for

   BOOST_REQUIRE_EQUAL( idx, 3);

} // format_values



/// Test feature to sort the values in the list.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( test_sort_values)
{

   // first check the default: values are stored as given
   {
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values"));

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 4);

      int  idx = 0;
      for (auto entry : l)
      {
         switch (idx)
         {
         case 0:   BOOST_REQUIRE_EQUAL( entry, 34532);  break;
         case 1:   BOOST_REQUIRE_EQUAL( entry,  9876);  break;
         case 2:   BOOST_REQUIRE_EQUAL( entry,    33);  break;
         case 3:   BOOST_REQUIRE_EQUAL( entry,     6);  break;
         default:  BOOST_REQUIRE( idx < 4);             break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 4);
   } // end scope

   // now the values should be sorted
   {
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setSortData());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 4);

      int  idx = 0;
      for (auto entry : l)
      {
         switch (idx)
         {
         case 0:   BOOST_REQUIRE_EQUAL( entry,     6);  break;
         case 1:   BOOST_REQUIRE_EQUAL( entry,    33);  break;
         case 2:   BOOST_REQUIRE_EQUAL( entry,  9876);  break;
         case 3:   BOOST_REQUIRE_EQUAL( entry, 34532);  break;
         default:  BOOST_REQUIRE( idx < 4);             break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 4);
   } // end scope

   // should still be sorted when added as multiple values
   {
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setSortData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6 42,13,4711", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 7);

      int  idx = 0;
      for (auto entry : l)
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
      Handler          ah( 0);
      std::list< int>  l = { 11, 255, 17 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setSortData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6 42,13,4711", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 10);

      int  idx = 0;
      for (auto entry : l)
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
         default:  BOOST_REQUIRE( idx < 7);             break;
         } // end switch
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 10);
   } // end scope

} // test_sort_values



/// Test feature that only unique values should be stored in the list.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values are stored as given
   {
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values"));

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 6);

      int  idx = 0;
      for (auto entry : l)
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
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setUniqueData());

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 5);

      int  idx = 0;
      for (auto entry : l)
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
      Handler          ah( 0);
      std::list< int>  l;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 5);

      int  idx = 0;
      for (auto entry : l)
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
      Handler          ah( 0);
      std::list< int>  l = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( l.size(), 5);

      int  idx = 0;
      for (auto entry : l)
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

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler          ah( 0);
      std::list< int>  l = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( l), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,4 6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test "list argument values" with a list.
///
/// @since  1.34.0, 13.12.2019
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream       std_out;
   std::ostringstream       std_err;
   Handler                  ah( std_out, std_err, Handler::hfListArgVar);
   std::list< std::string>  l;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( l), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "--list-arg-vars "
      "-l MONDAY,tuesday,wEdNeSdAy --list-arg-vars", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   BOOST_REQUIRE( !std_out.str().empty());
   // std::cerr << std_out.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-l' value type 'std::list<std::string>', destination container 'l', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-l' value type 'std::list<std::string>', destination container 'l', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



// =====  END OF test_argh_dest_list_c.cpp  =====
