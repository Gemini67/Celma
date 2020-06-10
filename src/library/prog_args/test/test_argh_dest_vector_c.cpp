
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of vectors by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestVectorTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Test error case that can occur with a vector.
///
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_vector_errors)
{

   // try to set invalid value mode
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but vector empty
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      auto const  as2a = make_arg_array( "-v this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

} // test_vector_errors



/// Test error case when vector specific features are specified for non-vector
/// destination types.
///
/// @since  1.9.0, 04.08.2018
BOOST_AUTO_TEST_CASE( vector_features_on_non_vector_dest)
{

   Handler      ah( 0);
   std::string  str;


   BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( str), "string")
      ->setClearBeforeAssign(), std::invalid_argument);

   BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( str), "string")
      ->setTakesMultiValue(), std::invalid_argument);

   BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( str), "string")
      ->setSortData(), std::invalid_argument);

   BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( str), "string")
      ->setUniqueData(), std::invalid_argument);

} // vector_features_on_non_vector_dest



/// For completeness: Set value mode "required" again.
///
/// @since  1.24.2, 23.04.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler            ah( 0);
   std::vector< int>  v = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
   } // end scope

   // now check with a custom list separator
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setListSep( '.'));

      auto const  as2a = make_arg_array( "-v 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple, separate values.
///
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};
      int                free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 8);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
      BOOST_REQUIRE_EQUAL( v[ 6], 7);
      BOOST_REQUIRE_EQUAL( v[ 7], 8);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};
      int                free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler            ah( Handler::hfEndValues);
      std::vector< int>  v = { 1, 2, 3};
      int                free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 7);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
      BOOST_REQUIRE_EQUAL( v[ 6], 7);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
   } // end scope

   // now the default values should be cleared
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-v 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 2);
      BOOST_REQUIRE_EQUAL( v[ 0], 4);
      BOOST_REQUIRE_EQUAL( v[ 1], 5);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5 6,7,8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 5);
      BOOST_REQUIRE_EQUAL( v[ 0], 4);
      BOOST_REQUIRE_EQUAL( v[ 1], 5);
      BOOST_REQUIRE_EQUAL( v[ 2], 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 7);
      BOOST_REQUIRE_EQUAL( v[ 4], 8);
   } // end scope

   // set default values, make argument optional, vector should be empty when
   // argument is used without value(s)
   {
      Handler            ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      auto const  as2a = make_arg_array( "-v", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( v.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the vector.
///
/// @since  1.23.0, 09.04.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                    ah( 0);
   std::vector< std::string>  v;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-v monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( v.size(), 3);
   BOOST_REQUIRE_EQUAL( v[ 0], "monday");
   BOOST_REQUIRE_EQUAL( v[ 1], "tuesday");
   BOOST_REQUIRE_EQUAL( v[ 2], "wednesday");

} // format_values



/// Test feature to format the values before they are inserted into the vector,
/// depending on their position in the vector.
///
/// @since  1.32.0, 20.08.2019
BOOST_AUTO_TEST_CASE( different_format_values)
{

   {
      Handler                    ah( 0);
      std::vector< std::string>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->addFormatPos( 0, celma::prog_args::lowercase())
         ->addFormatPos( 1, celma::prog_args::uppercase())
         ->addFormatPos( 2, celma::prog_args::anycase( "Ulllllllllll")));

      auto const  as2a = make_arg_array( "-v MONDAY,tuesday,wEdNeSdAy", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 3);
      BOOST_REQUIRE_EQUAL( v[ 0], "monday");
      BOOST_REQUIRE_EQUAL( v[ 1], "TUESDAY");
      BOOST_REQUIRE_EQUAL( v[ 2], "Wednesday");
   } // end scope

   // almost the same but with a gap
   {
      Handler                    ah( 0);
      std::vector< std::string>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->addFormatPos( 0, celma::prog_args::lowercase())
         ->addFormatPos( 1, celma::prog_args::uppercase())
         ->addFormatPos( 3, celma::prog_args::anycase( "Ulllllllllll")));

      auto const  as2a = make_arg_array( "-v MONDAY,tuesday,wEdNeSdAy,thursDAY", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 4);
      BOOST_REQUIRE_EQUAL( v[ 0], "monday");
      BOOST_REQUIRE_EQUAL( v[ 1], "TUESDAY");
      BOOST_REQUIRE_EQUAL( v[ 2], "wEdNeSdAy");
      BOOST_REQUIRE_EQUAL( v[ 3], "Thursday");
   } // end scope

   // a default format plus one special format
   {
      Handler                    ah( 0);
      std::vector< std::string>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->addFormat( celma::prog_args::lowercase())
         ->addFormatPos( 1, celma::prog_args::uppercase()));

      auto const  as2a = make_arg_array( "-v MONDAY,tuesday,wEdNeSdAy", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 3);
      BOOST_REQUIRE_EQUAL( v[ 0], "monday");
      BOOST_REQUIRE_EQUAL( v[ 1], "TUESDAY");
      BOOST_REQUIRE_EQUAL( v[ 2], "wednesday");
   } // end scope

   // multiple formattings should also work correctly with multiple, separate
   // values
   {
      Handler                    ah( 0);
      std::vector< std::string>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->addFormatPos( 0, celma::prog_args::lowercase())
         ->addFormatPos( 1, celma::prog_args::uppercase())
         ->addFormatPos( 3, celma::prog_args::anycase( "Ulllllllllll"))
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v MONDAY,tuesday wEdNeSdAy,thursDAY", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 4);
      BOOST_REQUIRE_EQUAL( v[ 0], "monday");
      BOOST_REQUIRE_EQUAL( v[ 1], "TUESDAY");
      BOOST_REQUIRE_EQUAL( v[ 2], "wEdNeSdAy");
      BOOST_REQUIRE_EQUAL( v[ 3], "Thursday");
   } // end scope

   // multiple formattings should also work correctly when the vector contains
   // default values
   {
      Handler                    ah( 0);
      std::vector< std::string>  v = { "some", "default", "values" };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->addFormatPos( 3, celma::prog_args::lowercase())
         ->addFormatPos( 4, celma::prog_args::uppercase())
         ->addFormatPos( 6, celma::prog_args::anycase( "Ulllllllllll"))
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v MONDAY,tuesday wEdNeSdAy,thursDAY", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 7);
      BOOST_REQUIRE_EQUAL( v[ 3], "monday");
      BOOST_REQUIRE_EQUAL( v[ 4], "TUESDAY");
      BOOST_REQUIRE_EQUAL( v[ 5], "wEdNeSdAy");
      BOOST_REQUIRE_EQUAL( v[ 6], "Thursday");
   } // end scope


   // test output of "list argument variables"
   {
      std::ostringstream         std_out;
      std::ostringstream         std_err;
      Handler                    ah( std_out, std_err, Handler::hfListArgVar);
      std::vector< std::string>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->addFormat( celma::prog_args::lowercase())
         ->addFormatPos( 1, celma::prog_args::uppercase()));

      auto const  as2a = make_arg_array( "--list-arg-vars "
         "-v MONDAY,tuesday,wEdNeSdAy --list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 3);
      BOOST_REQUIRE_EQUAL( v[ 0], "monday");
      BOOST_REQUIRE_EQUAL( v[ 1], "TUESDAY");
      BOOST_REQUIRE_EQUAL( v[ 2], "wednesday");

      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-v' value type 'std::vector<std::string>', destination container 'v', currently no values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 2 formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-v' value type 'std::vector<std::string>', destination container 'v', currently 3 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 2 formats.\n"
         "\n"));
   } // end scope

   // test argument help
   {
      std::ostringstream         std_out;
      std::ostringstream         std_err;
      Handler                    ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      std::vector< std::string>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->addFormat( celma::prog_args::lowercase())
         ->addFormatPos( 1, celma::prog_args::uppercase()));

      auto const  as2a = make_arg_array( "-v ONE,two,THREE --help-arg-full v",
         nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !v.empty());
      BOOST_REQUIRE_EQUAL( v[ 0], "one");
      BOOST_REQUIRE_EQUAL( v[ 1], "TWO");
      BOOST_REQUIRE_EQUAL( v[ 2], "three");

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-v', usage:\n"
         "   values\n"
         "Properties:\n"
         "   destination variable name:  v\n"
         "   destination variable type:  std::vector<std::string>\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                none\n"
         "   checks:                     -\n"
         "   check original value:       false\n"
         "   formats:                    all: lowercase; idx 1: uppercase\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // different_format_values



/// Test feature to sort the values in the vector.
///
/// @since  1.9.0, 04.08.2018
BOOST_AUTO_TEST_CASE( test_sort_values)
{

   // first check the default: values are stored as given
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 4);
      BOOST_REQUIRE_EQUAL( v[ 0], 34532);
      BOOST_REQUIRE_EQUAL( v[ 1], 9876);
      BOOST_REQUIRE_EQUAL( v[ 2], 33);
      BOOST_REQUIRE_EQUAL( v[ 3], 6);
   } // end scope

   // now the values should be sorted
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setSortData());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 4);
      BOOST_REQUIRE_EQUAL( v[ 0], 6);
      BOOST_REQUIRE_EQUAL( v[ 1], 33);
      BOOST_REQUIRE_EQUAL( v[ 2], 9876);
      BOOST_REQUIRE_EQUAL( v[ 3], 34532);
   } // end scope

   // should still be sorted when added as multiple values
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setSortData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6 42,13,4711", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 7);
      BOOST_REQUIRE_EQUAL( v[ 0], 6);
      BOOST_REQUIRE_EQUAL( v[ 1], 13);
      BOOST_REQUIRE_EQUAL( v[ 2], 33);
      BOOST_REQUIRE_EQUAL( v[ 3], 42);
      BOOST_REQUIRE_EQUAL( v[ 4], 4711);
      BOOST_REQUIRE_EQUAL( v[ 5], 9876);
      BOOST_REQUIRE_EQUAL( v[ 6], 34532);
   } // end scope

   // of course sorting should include pre-set values
   {
      Handler            ah( 0);
      std::vector< int>  v = { 11, 255, 17 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setSortData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6 42,13,4711", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 10);
      BOOST_REQUIRE_EQUAL( v[ 0], 6);
      BOOST_REQUIRE_EQUAL( v[ 1], 11);
      BOOST_REQUIRE_EQUAL( v[ 2], 13);
      BOOST_REQUIRE_EQUAL( v[ 3], 17);
      BOOST_REQUIRE_EQUAL( v[ 4], 33);
      BOOST_REQUIRE_EQUAL( v[ 5], 42);
      BOOST_REQUIRE_EQUAL( v[ 6], 255);
      BOOST_REQUIRE_EQUAL( v[ 7], 4711);
      BOOST_REQUIRE_EQUAL( v[ 8], 9876);
      BOOST_REQUIRE_EQUAL( v[ 9], 34532);
   } // end scope

} // test_sort_values



/// Test feature that only unique values should be stored in the vector.
///
/// @since  1.9.0, 04.08.2018
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values are stored as given
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 0], 2);
      BOOST_REQUIRE_EQUAL( v[ 1], 3);
      BOOST_REQUIRE_EQUAL( v[ 2], 4);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 6);
      BOOST_REQUIRE_EQUAL( v[ 5], 7);
   } // end scope

   // now the duplicate values should be ignored
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setUniqueData());

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 5);
      BOOST_REQUIRE_EQUAL( v[ 0], 2);
      BOOST_REQUIRE_EQUAL( v[ 1], 3);
      BOOST_REQUIRE_EQUAL( v[ 2], 4);
      BOOST_REQUIRE_EQUAL( v[ 3], 6);
      BOOST_REQUIRE_EQUAL( v[ 4], 7);
   } // end scope

   // duplicates should still be ignored when added as multiple values
   {
      Handler            ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 5);
      BOOST_REQUIRE_EQUAL( v[ 0], 2);
      BOOST_REQUIRE_EQUAL( v[ 1], 3);
      BOOST_REQUIRE_EQUAL( v[ 2], 4);
      BOOST_REQUIRE_EQUAL( v[ 3], 5);
      BOOST_REQUIRE_EQUAL( v[ 4], 6);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler            ah( 0);
      std::vector< int>  v = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 5);
      BOOST_REQUIRE_EQUAL( v[ 0], 3);
      BOOST_REQUIRE_EQUAL( v[ 1], 5);
      BOOST_REQUIRE_EQUAL( v[ 2], 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 2);
      BOOST_REQUIRE_EQUAL( v[ 4], 4);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler            ah( 0);
      std::vector< int>  v = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,4 6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // test_unique_values



// =====  END OF test_argh_dest_vector_c.cpp  =====

