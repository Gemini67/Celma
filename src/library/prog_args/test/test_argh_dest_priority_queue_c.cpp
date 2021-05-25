
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
**    Test program for the special handling of priority-queues by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestPriorityQueueTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Test error case that can occur with a priority queue.
///
/// @since  1.34.0, 29.12.2019
BOOST_AUTO_TEST_CASE( test_priority_queue_errors)
{

   // try to set invalid value mode
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but vector empty
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values"));

      auto const  as2a = make_arg_array( "-v this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

   // constraint "unique data" cannot be set for priority queues
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setUniqueData(), std::logic_error);
   } // end scope

   // sorting data in a priority queue is not possible
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setSortData(), std::logic_error);
   } // end scope

} // test_priority_queue_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.34.0, 29.12.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler                    ah( 0);
   std::priority_queue< int>  pq;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.34.0, 29.12.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( pq.size(), 3);

      int  expected = 6;
      while (!pq.empty())
      {
         const int  value = pq.top();
         BOOST_REQUIRE_EQUAL( value, expected);
         pq.pop();
         --expected;
      } // end while
      BOOST_REQUIRE_EQUAL( expected, 3);
   } // end scope

   // now check with a custom list separator
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setListSep( '.'));

      auto const  as2a = make_arg_array( "-v 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( pq.size(), 3);

      int  expected = 6;
      while (!pq.empty())
      {
         const int  value = pq.top();
         BOOST_REQUIRE_EQUAL( value, expected);
         pq.pop();
         --expected;
      } // end while
      BOOST_REQUIRE_EQUAL( expected, 3);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple, separate values.
///
/// @since  1.34.0, 29.12.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;
      int                        free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( pq.size(), 3);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( pq.size(), 5);
   } // end scope

   // accept multi-values, verify that nothing is stored in the free value
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;
      int                        free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( pq.size(), 5);
      BOOST_REQUIRE_EQUAL( free, -1);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler                    ah( 0);
      std::priority_queue< int>  pq;
      int                        free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler                    ah( Handler::hfEndValues);
      std::priority_queue< int>  pq;
      int                        free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( pq.size(), 4);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to format the values before they are inserted into the priority
/// queue.
///
/// @since  1.34.0, 29.12.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                            ah( 0);
   std::priority_queue< std::string>  pq;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( pq), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-v monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( pq.size(), 3);

   int  idx = 0;
   while (!pq.empty())
   {
      const std::string  value = pq.top();

      switch (idx)
      {
      case 0:   BOOST_REQUIRE_EQUAL( value, "wednesday");  break;
      case 1:   BOOST_REQUIRE_EQUAL( value, "tuesday");    break;
      case 2:   BOOST_REQUIRE_EQUAL( value, "monday");     break;
      default:  BOOST_REQUIRE( idx < 3);                   break;
      } // end switch

      pq.pop();
      ++idx;
   } // end while
   BOOST_REQUIRE_EQUAL( idx, 3);

} // format_values



/// Test output in usage etc. for a priority queue.
///
/// @since  1.34.0, 29.12.2019
BOOST_AUTO_TEST_CASE( usage_help)
{

   // test output of usage
   {
      std::ostringstream                 std_out;
      std::ostringstream                 std_err;
      Handler                            ah( std_out, std_err, Handler::AllHelp
         | Handler::hfUsageCont);
      std::priority_queue< int>          int_prio_queue;
      std::priority_queue< std::string>  str_prio_queue;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_prio_queue),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_prio_queue),
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
      std::ostringstream                 std_out;
      std::ostringstream                 std_err;
      Handler                            ah( std_out, std_err,
         Handler::hfListArgVar);
      std::priority_queue< int>          int_prio_queue;
      std::priority_queue< std::string>  str_prio_queue;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_prio_queue),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_prio_queue),
         "string values")->addFormat( celma::prog_args::lowercase()));

      auto const  as2a = make_arg_array( "--list-arg-vars "
         "-i 1,2,3 -s world,hello --list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( int_prio_queue.size(), 3);
      BOOST_REQUIRE_EQUAL( str_prio_queue.size(), 2);

      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' value type 'std::priority_queue<int>', destination container 'int_prio_queue', currently no values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s' value type 'std::priority_queue<std::string>', destination container 'str_prio_queue', currently no values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' value type 'std::priority_queue<int>', destination container 'int_prio_queue', currently 3 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s' value type 'std::priority_queue<std::string>', destination container 'str_prio_queue', currently 2 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
         "\n"));
   } // end scope

   // test argument help
   {
      std::ostringstream                 std_out;
      std::ostringstream                 std_err;
      Handler                            ah( std_out, std_err,
         Handler::hfUsageCont | Handler::hfHelpArgFull);
      std::priority_queue< int>          int_prio_queue;
      std::priority_queue< std::string>  str_prio_queue;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( int_prio_queue),
         "integer values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( str_prio_queue),
         "string values")->addFormat( celma::prog_args::lowercase()));

      auto const  as2a = make_arg_array( "-i 1,2,3 --help-arg-full i",
         nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !int_prio_queue.empty());

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-i', usage:\n"
         "   integer values\n"
         "Properties:\n"
         "   destination variable name:  int_prio_queue\n"
         "   destination variable type:  std::priority_queue<int>\n"
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



// =====  END OF test_argh_dest_priority_queue_c.cpp  =====

