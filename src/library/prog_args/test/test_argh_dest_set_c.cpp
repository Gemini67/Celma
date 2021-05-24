
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
**    Test program for the special handling of sets by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <set>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestSetTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Test error case that can occur with a set.
///
/// @since  1.34.0, 14.11.2019
BOOST_AUTO_TEST_CASE( test_set_errors)
{

   // try to set invalid value mode
   {
      Handler         ah( 0);
      std::set< int>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler         ah( 0);
      std::set< int>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but set empty
   {
      Handler         ah( 0);
      std::set< int>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // try to add a formatter for a specific position
   {
      Handler         ah( 0);
      std::set< int>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->addFormatPos( 1, celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values"));

      auto const  as2a = make_arg_array( "-s this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

   // a set cannot be sorted
   {
      Handler         ah( 0);
      std::set< int>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setSortData(), std::logic_error);
   } // end scope

} // test_set_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.34.0, 14.11.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler         ah( 0);
   std::set< int>  s = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.34.0, 14.11.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values"));

      auto const  as2a = make_arg_array( "-s 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 6);

      int  exp_val = 1;
      for (auto set_iter : s)
      {
         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

   // now check with a custom list separator
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")->
         setListSep( '.'));

      auto const  as2a = make_arg_array( "-s 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 6);

      int  exp_val = 1;
      for (auto set_iter : s)
      {
         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

} // test_list_sep



/// Test that the cardinality is checked correctly.
///
/// @since  1.34.0, 15.11.2019
BOOST_AUTO_TEST_CASE( test_cardinality)
{

   Handler         ah( 0);
   std::set< int>  s = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
      ->setCardinality( celma::prog_args::cardinality_max( 3)));

   auto const  as2a = make_arg_array( "-s 4,5,6,7", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
      std::runtime_error);
   BOOST_REQUIRE_EQUAL( s.size(), 6);

   int  exp_val = 1;
   for (auto set_iter : s)
   {
      BOOST_REQUIRE_EQUAL( set_iter, exp_val);
      ++exp_val;
   } // end for

} // test_cardinality



/// Test feature to handle multiple, separate values.
///
/// @since  1.34.0, 15.11.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values"));

      auto const  as2a = make_arg_array( "-s 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};
      int             free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-s 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 6);

      int  exp_val = 1;
      for (auto set_iter : s)
      {
         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};
      int             free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-s 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 8);

      int  exp_val = 1;
      for (auto set_iter : s)
      {
         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( free, -1);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};
      int             free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-s 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler         ah( Handler::hfEndValues);
      std::set< int>  s = { 1, 2, 3};
      int             free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-s 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 7);

      int  exp_val = 1;
      for (auto set_iter : s)
      {
         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.34.0, 15.11.2019
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values"));

      auto const  as2a = make_arg_array( "-s 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 6);

      int  exp_val = 1;
      for (auto set_iter : s)
      {
         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

   // now the default values should be cleared
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-s 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 2);

      int  exp_val = 4;
      for (auto set_iter : s)
      {
         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-s 4,5 6,7,8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 5);

      int  exp_val = 4;
      for (auto set_iter : s)
      {
         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for
   } // end scope

   // set default values, make argument optional, set should be empty when
   // argument is used without value(s)
   {
      Handler         ah( 0);
      std::set< int>  s = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      auto const  as2a = make_arg_array( "-s", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( s.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the set.
///
/// @since  1.34.0, 15.11.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                 ah( 0);
   std::set< std::string>  s;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-s monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( s.size(), 3);

   int  idx = 0;
   for (auto set_iter : s)
   {
      if (idx == 0)
      {
         BOOST_REQUIRE_EQUAL( set_iter, "monday");
      } else if (idx == 1)
      {
         BOOST_REQUIRE_EQUAL( set_iter, "tuesday");
      } else if (idx == 2)
      {
         BOOST_REQUIRE_EQUAL( set_iter, "wednesday");
      } else
      {
         BOOST_REQUIRE( idx < 3);
      } // end if
      ++idx;
   } // end for

} // format_values



/// Test feature that only unique values should be stored in the set.
/// Setting the same value multiple times would simply override in the set.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values overwrite silently
   {
      Handler         ah( 0);
      std::set< int>  s;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values"));

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 5);

      int  exp_val = 2;
      for (auto set_iter : s)
      {
         if (exp_val == 5)
            ++exp_val;

         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( exp_val, 8);
   } // end scope

   // mode "ignore unique data without errors" can be set, even when it does not
   // make much sense
   {
      Handler         ah( 0);
      std::set< int>  s;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->setUniqueData());

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( s.size(), 5);

      int  exp_val = 2;
      for (auto set_iter : s)
      {
         if (exp_val == 5)
            ++exp_val;

         BOOST_REQUIRE_EQUAL( set_iter, exp_val);
         ++exp_val;
      } // end for

      BOOST_REQUIRE_EQUAL( exp_val, 8);
   } // end scope

   // duplicates should lead to an error, also when conflicting with pre-set
   // values
   {
      Handler         ah( 0);
      std::set< int>  s = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( s), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,4 6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test "list argument values" with a set.
///
/// @since  1.34.0, 15.11.2019
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream      std_out;
   std::ostringstream      std_err;
   Handler                 ah( std_out, std_err, Handler::hfListArgVar);
   std::set< std::string>  s;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( s), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "--list-arg-vars "
      "-s MONDAY,tuesday,wEdNeSdAy --list-arg-vars", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   BOOST_REQUIRE( !std_out.str().empty());
   // std::cerr << std_out.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::set<std::string>', destination container 's', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::set<std::string>', destination container 's', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



/// Test constraint "disjoint" with two sets.
///
/// @since  1.34.0, 15.11.2019
BOOST_AUTO_TEST_CASE( disjoint_sets)
{

   using celma::prog_args::disjoint;

   {
      Handler         ah( 0);
      std::set< int>  set1;
      std::set< int>  set2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( set1), "left"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( set2), "right"));

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( disjoint( "l;r")));

      auto const  as2a = make_arg_array( "-l 1,2,3 -r 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // throw if the data in the sets is not disjoint
   {
      Handler         ah( 0);
      std::set< int>  set1;
      std::set< int>  set2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( set1), "left"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( set2), "right"));

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( disjoint( "l;r")));

      auto const  as2a = make_arg_array( "-l 1,2,3 -r 4,5,6,1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // disjoint_sets



// =====  END OF test_argh_dest_set_c.cpp  =====

