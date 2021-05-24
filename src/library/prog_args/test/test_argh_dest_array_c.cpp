
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
**    Test program for the special handling of arrays by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestArrayTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Test error case that can occur with an array.
///
/// @since  1.26.0, 26.04.2019
BOOST_AUTO_TEST_CASE( test_array_errors)
{

   // try to set invalid value mode
   {
      Handler              ah( 0);
      std::array< int, 3>  arr;

      BOOST_REQUIRE_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler              ah( 0);
      std::array< int, 3>  arr;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values"));

      auto const  as2a = make_arg_array( "-a this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

   // try to assign too many values
   {
      Handler              ah( 0);
      std::array< int, 3>  arr;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values"));

      auto const  as2a = make_arg_array( "-a 1,2,3,4", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // try to assign too many values in two parts
   {
      Handler              ah( 0);
      std::array< int, 3>  arr;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-a 1,2 3,4", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // try to specify a formatter for a value index that is greater than the size
   // of the array
   {
      Handler              ah( 0);
      std::array< int, 3>  arr;

      BOOST_REQUIRE_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->addFormatPos( 3, celma::prog_args::lowercase()), std::range_error);
   } // end scope

} // test_array_errors



/// Test feature to set another character as list separator.
///
/// @since  1.26.0, 26.04.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler              ah( 0);
      std::array< int, 3>  arr = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values"));

      auto const  as2a = make_arg_array( "-a 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 4);
      BOOST_REQUIRE_EQUAL( arr[ 1], 5);
      BOOST_REQUIRE_EQUAL( arr[ 2], 6);
   } // end scope

   // now use another character
   {
      Handler              ah( 0);
      std::array< int, 3>  arr = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setListSep( '.'));

      auto const  as2a = make_arg_array( "-a 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 4);
      BOOST_REQUIRE_EQUAL( arr[ 1], 5);
      BOOST_REQUIRE_EQUAL( arr[ 2], 6);
   } // end scope

   // multiple features
   {
      Handler              ah( 0);
      std::array< int, 3>  arr = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setListSep( '.')->setTakesMultiValue()->setSortData()
         ->setUniqueData());

      auto const  as2a = make_arg_array( "-a 6.5 5.4", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 4);
      BOOST_REQUIRE_EQUAL( arr[ 1], 5);
      BOOST_REQUIRE_EQUAL( arr[ 2], 6);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple values.
///
/// @since  1.26.0, 26.04.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler              ah( 0);
      std::array< int, 6>  arr;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values"));

      auto const  as2a = make_arg_array( "-a 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler              ah( 0);
      std::array< int, 6>  arr;
      int                  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-a 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 4);
      BOOST_REQUIRE_EQUAL( arr[ 1], 5);
      BOOST_REQUIRE_EQUAL( arr[ 2], 6);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler              ah( 0);
      std::array< int, 6>  arr;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-a 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 4);
      BOOST_REQUIRE_EQUAL( arr[ 1], 5);
      BOOST_REQUIRE_EQUAL( arr[ 2], 6);
      BOOST_REQUIRE_EQUAL( arr[ 3], 7);
      BOOST_REQUIRE_EQUAL( arr[ 4], 8);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler              ah( 0);
      std::array< int, 6>  arr;
      int                  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-a 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler              ah( Handler::hfEndValues);
      std::array< int, 6>  arr;
      int                  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-a 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 4);
      BOOST_REQUIRE_EQUAL( arr[ 1], 5);
      BOOST_REQUIRE_EQUAL( arr[ 2], 6);
      BOOST_REQUIRE_EQUAL( arr[ 3], 7);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to format the values before they are inserted into the array.
///
/// @since  1.26.0, 26.04.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   {
      Handler                      ah( 0);
      std::array< std::string, 3>  arr;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->addFormat( celma::prog_args::lowercase()));

      auto const  as2a = make_arg_array( "-a monday,TUESDAY,wEdNeSdAy", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], "monday");
      BOOST_REQUIRE_EQUAL( arr[ 1], "tuesday");
      BOOST_REQUIRE_EQUAL( arr[ 2], "wednesday");
   } // end scope

   {
      Handler                      ah( 0);
      std::array< std::string, 3>  arr;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->addFormatPos( 0, celma::prog_args::lowercase())
         ->addFormatPos( 1, celma::prog_args::uppercase())
         ->addFormatPos( 2, celma::prog_args::anycase( "Ullllllllllll"))
         ->setListSep( '.')->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-a MONDAY tuesday.wEdNeSdAy",
         nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], "monday");
      BOOST_REQUIRE_EQUAL( arr[ 1], "TUESDAY");
      BOOST_REQUIRE_EQUAL( arr[ 2], "Wednesday");
   } // end scope

   {
      std::ostringstream           std_out;
      std::ostringstream           std_err;
      Handler                      ah( std_out, std_err, Handler::hfListArgVar);
      std::array< std::string, 3>  arr;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->addFormat( celma::prog_args::lowercase()));

      auto const  as2a = make_arg_array( "-a monday,TUESDAY,wEdNeSdAy --list-arg-var",
         nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], "monday");
      BOOST_REQUIRE_EQUAL( arr[ 1], "tuesday");
      BOOST_REQUIRE_EQUAL( arr[ 2], "wednesday");

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << '\n' << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-a' value type 'std::array<std::string,3>', destination array 'arr', currently 3 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
         "\n"));
   } // end scope

} // format_values



/// Test feature to sort the values in the array.
///
/// @since  1.26.0, 26.04.2019
BOOST_AUTO_TEST_CASE( test_sort_values)
{

   // first check the default: values are stored as given
   {
      Handler              ah( 0);
      std::array< int, 4>  arr = { 0, 0, 0, 0 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values"));

      auto const  as2a = make_arg_array( "-a 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 34532);
      BOOST_REQUIRE_EQUAL( arr[ 1], 9876);
      BOOST_REQUIRE_EQUAL( arr[ 2], 33);
      BOOST_REQUIRE_EQUAL( arr[ 3], 6);
   } // end scope

   // now the values should be sorted
   {
      Handler              ah( 0);
      std::array< int, 4>  arr = { 0, 0, 0, 0 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setSortData());

      auto const  as2a = make_arg_array( "-a 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 6);
      BOOST_REQUIRE_EQUAL( arr[ 1], 33);
      BOOST_REQUIRE_EQUAL( arr[ 2], 9876);
      BOOST_REQUIRE_EQUAL( arr[ 3], 34532);
   } // end scope

   // should still be sorted when added as multiple values
   {
      Handler              ah( 0);
      std::array< int, 7>  arr = { 0, 0, 0, 0, 0, 0, 0 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setSortData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-a 34532,9876,33,6 42,13,4711", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 6);
      BOOST_REQUIRE_EQUAL( arr[ 1], 13);
      BOOST_REQUIRE_EQUAL( arr[ 2], 33);
      BOOST_REQUIRE_EQUAL( arr[ 3], 42);
      BOOST_REQUIRE_EQUAL( arr[ 4], 4711);
      BOOST_REQUIRE_EQUAL( arr[ 5], 9876);
      BOOST_REQUIRE_EQUAL( arr[ 6], 34532);
   } // end scope

} // test_sort_values



/// Test feature that only unique values should be stored in the array.
///
/// @since  1.26.0, 26.04.2019
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values are stored as given
   {
      Handler              ah( 0);
      std::array< int, 6>  arr = { 0, 0, 0, 0, 0, 0 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values"));

      auto const  as2a = make_arg_array( "-a 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 2);
      BOOST_REQUIRE_EQUAL( arr[ 1], 3);
      BOOST_REQUIRE_EQUAL( arr[ 2], 4);
      BOOST_REQUIRE_EQUAL( arr[ 3], 4);
      BOOST_REQUIRE_EQUAL( arr[ 4], 6);
      BOOST_REQUIRE_EQUAL( arr[ 5], 7);
   } // end scope

   // now the duplicate values should cause an error
   {
      Handler              ah( 0);
      std::array< int, 5>  arr = { 0, 0, 0, 0, 0 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setUniqueData( true));

      auto const  as2a = make_arg_array( "-a 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // now the duplicate values should be silently ignored
   {
      Handler              ah( 0);
      std::array< int, 5>  arr = { 0, 0, 0, 0, 0 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setUniqueData()->setListSep('-'));

      auto const  as2a = make_arg_array( "-a 2-3-4-4-6-7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 2);
      BOOST_REQUIRE_EQUAL( arr[ 1], 3);
      BOOST_REQUIRE_EQUAL( arr[ 2], 4);
      BOOST_REQUIRE_EQUAL( arr[ 3], 6);
      BOOST_REQUIRE_EQUAL( arr[ 4], 7);
   } // end scope

   // duplicates should still be ignored when added as multiple values
   {
      Handler              ah( 0);
      std::array< int, 5>  arr = { 0, 0, 0, 0, 0 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "a", DEST_VAR( arr), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-a 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( arr[ 0], 2);
      BOOST_REQUIRE_EQUAL( arr[ 1], 3);
      BOOST_REQUIRE_EQUAL( arr[ 2], 4);
      BOOST_REQUIRE_EQUAL( arr[ 3], 5);
      BOOST_REQUIRE_EQUAL( arr[ 4], 6);
   } // end scope

} // test_unique_values



// =====  END OF test_argh_dest_array_c.cpp  =====

