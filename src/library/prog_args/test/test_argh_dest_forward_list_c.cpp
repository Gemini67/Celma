
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of forward-lists by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestForwardListTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;


namespace {


/// Helper function to get the size of a forward-list.
///
/// @param[in]  fl  The forward-list object to return the size of.
/// @return  The size of the forward-list, i.e. the number of values it contains.
/// @since  1.34.0, 30.12.2019
template< typename T> size_t size( const std::forward_list< T>& fl)
{
   return std::distance( fl.begin(), fl.end());
} // size


} // namespace



/// Test error case that can occur with a forward-list.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( test_forward_list_errors)
{

   // try to set invalid value mode
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but forward-list empty
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values"));

      auto const  as2a = make_arg_array( "-v this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

} // test_forward_list_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler                  ah( 0);
   std::forward_list< int>  fl = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 6);
   } // end scope

   // now check with a custom list separator
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setListSep( '.'));

      auto const  as2a = make_arg_array( "-v 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 6);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple, separate values.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};
      int                      free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 6);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 8);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};
      int                      free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler                  ah( Handler::hfEndValues);
      std::forward_list< int>  fl = { 1, 2, 3};
      int                      free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 7);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 6);
   } // end scope

   // now the default values should be cleared
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-v 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 2);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5 6,7,8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 5);
   } // end scope

   // set default values, make argument optional, forward-list should be empty
   // when argument is used without value(s)
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      auto const  as2a = make_arg_array( "-v", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( fl.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the forward-
/// list.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                          ah( 0);
   std::forward_list< std::string>  fl;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-v monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( size( fl), 3);

} // format_values



/// Test feature to sort the values in the forward-list.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( test_sort_values)
{

   // first check the default: values are stored as given
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values"));

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 4);
   } // end scope

   // now the values should be sorted
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setSortData());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 4);
   } // end scope

   // should still be sorted when added as multiple values
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setSortData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6 42,13,4711", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 7);
   } // end scope

   // of course sorting should include pre-set values
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 11, 255, 17 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setSortData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 34532,9876,33,6 42,13,4711", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 10);
   } // end scope

} // test_sort_values



/// Test feature that only unique values should be stored in the forward-list.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values are stored as given
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values"));

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 6);
   } // end scope

   // now the duplicate values should be ignored
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setUniqueData());

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 5);
   } // end scope

   // duplicates should still be ignored when added as multiple values
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 5);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( fl), 5);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler                  ah( 0);
      std::forward_list< int>  fl = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( fl), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,4 6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test output in usage etc. for a forward-list.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( usage_help)
{

   // test output of usage
   {
      std::ostringstream               std_out;
      std::ostringstream               std_err;
      Handler                          ah( std_out, std_err, Handler::AllHelp
         | Handler::hfUsageCont);
      std::forward_list< int>          int_forward_list;
      std::forward_list< std::string>  str_forward_list;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_forward_list),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_forward_list),
         "string values"));

      auto const  as2a = make_arg_array( "--help", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -i           integer values\n"
         "   -s           string values\n"
         "\n"));
   } // end scope

   // test output of "list argument variables"
   {
      std::ostringstream               std_out;
      std::ostringstream               std_err;
      Handler                          ah( std_out, std_err,
         Handler::hfListArgVar);
      std::forward_list< int>          int_forward_list;
      std::forward_list< std::string>  str_forward_list;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_forward_list),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_forward_list),
         "string values")->addFormat( celma::prog_args::lowercase()));

      auto const  as2a = make_arg_array( "--list-arg-vars "
         "-i 1,2,3 -s world,hello --list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( size( int_forward_list), 3);
      BOOST_REQUIRE_EQUAL( size( str_forward_list), 2);

      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' value type 'std::forward_list<int>', destination container 'int_forward_list', currently no values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s' value type 'std::forward_list<std::string>', destination container 'str_forward_list', currently no values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' value type 'std::forward_list<int>', destination container 'int_forward_list', currently 3 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s' value type 'std::forward_list<std::string>', destination container 'str_forward_list', currently 2 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
         "\n"));
   } // end scope

   // test argument help
   {
      std::ostringstream               std_out;
      std::ostringstream               std_err;
      Handler                          ah( std_out, std_err,
         Handler::hfUsageCont | Handler::hfHelpArgFull);
      std::forward_list< int>          int_forward_list;
      std::forward_list< std::string>  str_forward_list;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_forward_list),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_forward_list),
         "string values")->addFormat( celma::prog_args::lowercase()));

      auto const  as2a = make_arg_array( "-i 1,2,3 --help-arg-full i",
         nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !int_forward_list.empty());

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-i', usage:\n"
         "   integer values\n"
         "Properties:\n"
         "   destination variable name:  int_forward_list\n"
         "   destination variable type:  std::forward_list<int>\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                none\n"
         "   checks:                     -\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // usage_help



// =====  END OF test_argh_dest_forward_list_c.cpp  =====

