
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
**    Test program for the special handling of stacks by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestStackTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Test error case that can occur with a stack.
///
/// @since  1.34.0, 02.12.2019
BOOST_AUTO_TEST_CASE( test_stack_errors)
{

   // try to set invalid value mode
   {
      Handler           ah( 0);
      std::stack< int>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // cannot set "sort data" for stacks
   {
      Handler           ah( 0);
      std::stack< int>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->setSortData(), std::logic_error);
   } // end scope

   // cannot set "unique value handling" for stacks
   {
      Handler           ah( 0);
      std::stack< int>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->setUniqueData( true), std::logic_error);
   } // end scope

   // cannot add a formatter for a specific position
   {
      Handler                   ah( 0);
      std::stack< std::string>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->addFormatPos( 3, celma::prog_args::lowercase()), std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler           ah( 0);
      std::stack< int>  s;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values"));

      auto const  as2a = make_arg_array( "-v this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

} // test_stack_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.34.0, 03.12.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler           ah( 0);
   std::stack< int>  s;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.34.0, 03.12.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler           ah( 0);
      std::stack< int>  s;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 3);
   } // end scope

   // now check with a custom list separator
   {
      Handler           ah( 0);
      std::stack< int>  s;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values")->
         setListSep( '.'));

      auto const  as2a = make_arg_array( "-v 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 3);
   } // end scope

} // test_list_sep



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler           ah( 0);
      std::stack< int>  s;

      s.push( 1);
      s.push( 2);
      s.push( 3);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 6);
   } // end scope

   // now the default values should be cleared
   {
      Handler           ah( 0);
      std::stack< int>  s;

      s.push( 1);
      s.push( 2);
      s.push( 3);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-v 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 2);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler           ah( 0);
      std::stack< int>  s;

      s.push( 1);
      s.push( 2);
      s.push( 3);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5 6,7,8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 5);
   } // end scope

   // set default values, make argument optional, stack should be empty when
   // argument is used without value(s)
   {
      Handler           ah( 0);
      std::stack< int>  s;

      s.push( 1);
      s.push( 2);
      s.push( 3);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      auto const  as2a = make_arg_array( "-v", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( s.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the stack.
///
/// @since  1.34.0, 03.12.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                   ah( 0);
   std::stack< std::string>  s;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-v monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( s.size(), 3);

   int  idx = 0;
   while (!s.empty())
   {
      const std::string  top_value = s.top();

      if (idx == 0)
         BOOST_REQUIRE_EQUAL( top_value, "wednesday");
      else if (idx == 1)
         BOOST_REQUIRE_EQUAL( top_value, "tuesday");
      else if (idx == 2)
         BOOST_REQUIRE_EQUAL( top_value, "monday");
      else
         BOOST_REQUIRE( idx < 3);

      ++idx;
      s.pop();
   } // end while

} // format_values



/// Test output in usage etc. for a stack.
///
/// @since  1.34.0, 03.12.2019
BOOST_AUTO_TEST_CASE( usage_help)
{

   // test output of usage
   {
      std::ostringstream        std_out;
      std::ostringstream        std_err;
      Handler                   ah( std_out, std_err, Handler::AllHelp
         | Handler::hfUsageCont);
      std::stack< int>          int_stack;
      std::stack< std::string>  str_stack;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_stack),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_stack),
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
      std::ostringstream        std_out;
      std::ostringstream        std_err;
      Handler                   ah( std_out, std_err, Handler::hfListArgVar);
      std::stack< int>          int_stack;
      std::stack< std::string>  str_stack;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_stack),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_stack),
         "string values")->addFormat( celma::prog_args::lowercase()));

      auto const  as2a = make_arg_array( "--list-arg-vars "
         "-i 1,2,3 -s world,hello --list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( int_stack.size(), 3);
      BOOST_REQUIRE_EQUAL( str_stack.size(), 2);

      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' value type 'std::stack<int>', destination container 'int_stack', currently no values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s' value type 'std::stack<std::string>', destination container 'str_stack', currently no values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' value type 'std::stack<int>', destination container 'int_stack', currently 3 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s' value type 'std::stack<std::string>', destination container 'str_stack', currently 2 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
         "\n"));
   } // end scope

   // test argument help
   {
      std::ostringstream        std_out;
      std::ostringstream        std_err;
      Handler                   ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      std::stack< int>          int_stack;
      std::stack< std::string>  str_stack;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_stack),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_stack),
         "string values")->addFormat( celma::prog_args::lowercase()));

      auto const  as2a = make_arg_array( "-i 1,2,3 --help-arg-full i",
         nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !int_stack.empty());

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-i', usage:\n"
         "   integer values\n"
         "Properties:\n"
         "   destination variable name:  int_stack\n"
         "   destination variable type:  std::stack<int>\n"
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



// =====  END OF test_argh_dest_stack_c.cpp  =====

