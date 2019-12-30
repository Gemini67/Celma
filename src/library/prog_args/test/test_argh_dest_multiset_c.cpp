
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
**    Test program for the special handling of multi-sets by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestMultiSetTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Test error case that can occur with a multi-set.
///
/// @since  x.y.z, 17.12.2019
BOOST_AUTO_TEST_CASE( test_multiset_errors)
{

   // try to set invalid value mode
   {
      Handler              ah( 0);
      std::multiset< int>  ms;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler              ah( 0);
      std::multiset< int>  ms;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but multi-set empty
   {
      Handler              ah( 0);
      std::multiset< int>  ms;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values"));

      auto const  as2a = make_arg_array( "-v this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

   // a multi-set cannot be sorted
   {
      Handler              ah( 0);
      std::multiset< int>  ms;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( ms), "values")
         ->setSortData(), std::logic_error);
   } // end scope

} // test_multiset_errors



/// For completeness: Set value mode "required" again.
///
/// @since  x.y.z, 17.12.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler              ah( 0);
   std::multiset< int>  ms = { 1, 2, 3};


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  x.y.z, 17.12.2019
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 6);

      int  idx = 1;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 7);
   } // end scope

   // now check with a custom list separator
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setListSep( '.'));

      auto const  as2a = make_arg_array( "-v 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 6);

      int  idx = 1;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 7);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple, separate values.
///
/// @since  x.y.z, 17.12.2019
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};
      int                  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 6);

      int  idx = 1;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 7);

      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 8);


      int  idx = 1;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 9);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};
      int                  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler              ah( Handler::hfEndValues);
      std::multiset< int>  ms = { 1, 2, 3};
      int                  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 7);

      int  idx = 1;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 8);

      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  x.y.z, 17.12.2019
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values"));

      auto const  as2a = make_arg_array( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 6);

      int  idx = 1;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 7);
   } // end scope

   // now the default values should be cleared
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-v 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 2);

      int  idx = 4;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 6);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 4,5 6,7,8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 5);

      int  idx = 4;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 9);
   } // end scope

   // set default values, make argument optional, vector should be empty when
   // argument is used without value(s)
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      auto const  as2a = make_arg_array( "-v", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( ms.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the multi-
/// set.
///
/// @since  x.y.z, 17.12.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                      ah( 0);
   std::multiset< std::string>  ms;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
      ->addFormat( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-v monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( ms.size(), 3);

   int  idx = 0;
   for (auto const& value : ms)
   {
      switch (idx)
      {
      case 0:   BOOST_REQUIRE_EQUAL( value, "monday");     break;
      case 1:   BOOST_REQUIRE_EQUAL( value, "tuesday");    break;
      case 2:   BOOST_REQUIRE_EQUAL( value, "wednesday");  break;
      default:  BOOST_REQUIRE( idx < 3);                   break;
      } // end switch
      ++idx;
   } // end for
   BOOST_REQUIRE_EQUAL( idx, 3);

} // format_values



/// Test feature that only unique values should be stored in the multi-set.
///
/// @since  x.y.z, 17.12.2019
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values are stored as given
   {
      Handler              ah( 0);
      std::multiset< int>  ms;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values"));

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 6);

      int  idx = 2;
      for (auto const& value : ms)
      {
         // well ...
         if ((idx == 5) && (value == 4))
            idx = 4;
         else if ((idx == 5) && (value == 6))
            idx = 6;
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 8);
   } // end scope

   // now the duplicate values should be ignored
   {
      Handler              ah( 0);
      std::multiset< int>  ms;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setUniqueData());

      auto const  as2a = make_arg_array( "-v 2,3,4,4,6,7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 5);

      int  idx = 2;
      for (auto const& value : ms)
      {
         if (idx == 5)
            ++idx;
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 8);
   } // end scope

   // duplicates should still be ignored when added as multiple values
   {
      Handler              ah( 0);
      std::multiset< int>  ms;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 5);

      int  idx = 2;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 7);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setUniqueData()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,3,4 3,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( ms.size(), 5);

      int  idx = 2;
      for (auto const& value : ms)
      {
         BOOST_REQUIRE_EQUAL( value, idx);
         ++idx;
      } // end for
      BOOST_REQUIRE_EQUAL( idx, 7);
   } // end scope

   // duplicates should still be ignored when conflicting with pre-set values
   {
      Handler              ah( 0);
      std::multiset< int>  ms = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( ms), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,4 6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test "list argument values" with a multi-set.
///
/// @since  x.y.z, 17.12.2019
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream           std_out;
   std::ostringstream           std_err;
   Handler                      ah( std_out, std_err, Handler::hfListArgVar);
   std::multiset< std::string>  ms;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( ms), "values")
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
      "'-s' value type 'std::multiset<std::string>', destination container 'ms', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::multiset<std::string>', destination container 'ms', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



// =====  END OF test_argh_dest_multiset_c.cpp  =====

