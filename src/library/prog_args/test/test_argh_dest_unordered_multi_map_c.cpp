
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of unordered multi-maps by the
**    module prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <map>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestUnorderedMultiMapTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/check_for.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;



/// Test error case that can occur with a multi-map.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_unordered_multimap_errors)
{

   // try to set invalid value mode
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // valid value mode, but "clear before assign" not set
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // valid value mode, "clear before assign" set, but multi-map empty
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional),
         std::logic_error);
   } // end scope

   // try to add a formatter for a specific position
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->addFormatPos( 1, celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope

   // assign wrong value types
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values"));

      auto const  as2a = make_arg_array( "-m this,should;throw,immediately", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

   // cannot use same character as list and pair separator
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setPairFormat( ";"), std::invalid_argument);
   } // end scope

   {
      Handler                           ah( 0);
      std::multimap< int, std::string>  umm;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setListSep( '+')->setPairFormat( "+"), std::invalid_argument);
   } // end scope

   {
      Handler                           ah( 0);
      std::multimap< int, std::string>  umm;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")->
         setPairFormat( ";{}"), std::invalid_argument);
   } // end scope

   // wrong format of values in argument list
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values"));

      auto const  as2a = make_arg_array( "-m this;should;throw;immediately", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // a multimap cannot be sorted
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setSortData(), std::logic_error);
   } // end scope

} // test_unordered_multimap_errors



/// For completeness: Set value mode "required" again.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler                                     ah( 0);
   std::unordered_multimap< int, std::string>  umm;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test feature to set another character as list separator.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values"));

      auto const  as2a = make_arg_array( "-m 4,four;5,five;6,six", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 3);

      bool  got_four = false;
      bool  got_five = false;
      bool  got_six = false;

      for (auto map_iter : umm)
      {
         if (!got_four && (map_iter.first == 4) && (map_iter.second == "four"))
         {
            got_four = true;
         } else if (!got_five && (map_iter.first == 5)
                    && (map_iter.second == "five"))
         {
            got_five = true;
         } else if (!got_six && (map_iter.first == 6)
                    && (map_iter.second == "six"))
         {
            got_six = true;
         } else
         {
            // should never get here
            BOOST_REQUIRE( map_iter.first == 0);
         } // end if
      } // end for

      BOOST_REQUIRE( got_four);
      BOOST_REQUIRE( got_five);
      BOOST_REQUIRE( got_six);
   } // end scope

   // now check with a custom list separator
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")->
         setListSep( '+')->setPairFormat( "-"));

      auto const  as2a = make_arg_array( "-m 4-four+5-five+6-six", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 3);

      bool  got_four = false;
      bool  got_five = false;
      bool  got_six = false;

      for (auto map_iter : umm)
      {
         if (!got_four && (map_iter.first == 4) && (map_iter.second == "four"))
         {
            got_four = true;
         } else if (!got_five && (map_iter.first == 5)
                    && (map_iter.second == "five"))
         {
            got_five = true;
         } else if (!got_six && (map_iter.first == 6)
                    && (map_iter.second == "six"))
         {
            got_six = true;
         } else
         {
            // should never get here
            BOOST_REQUIRE( map_iter.first == 0);
         } // end if
      } // end for

      BOOST_REQUIRE( got_four);
      BOOST_REQUIRE( got_five);
      BOOST_REQUIRE( got_six);
   } // end scope

} // test_list_sep



/// Test that the cardinality is checked correctly.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_cardinality)
{

   Handler                                     ah( 0);
   std::unordered_multimap< int, std::string>  umm;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
      ->setCardinality( celma::prog_args::cardinality_max( 3)));

   auto const  as2a = make_arg_array( "-m 4,four;5,five;6,six;7,seven", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
      std::runtime_error);
   BOOST_REQUIRE_EQUAL( umm.size(), 3);

} // test_cardinality



/// Test feature to handle multiple, separate values.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values"));

      auto const  as2a = make_arg_array( "-s 4,four;5,five;6,six 7,seven",
         nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;
      int                                         free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-m 4,four;5,five;6,six 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 3);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;
      int                                         free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-m 4,four;5,five;6,six 7,seven 8,eight", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 5);
      BOOST_REQUIRE_EQUAL( free, -1);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;
      int                                         free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-m 4,four;5,five;6,six 7,seven "
         "--endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler                                     ah( Handler::hfEndValues);
      std::unordered_multimap< int, std::string>  umm;
      int                                         free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-m 4,four;5,five;6,six 7,seven "
         "--endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 4);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm
         = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values"));

      auto const  as2a = make_arg_array( "-m 4,four;5,five;6,six", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 6);

      bool  got_one = false;
      bool  got_two = false;
      bool  got_three = false;
      bool  got_four = false;
      bool  got_five = false;
      bool  got_six = false;

      for (auto map_iter : umm)
      {
         if (!got_one && (map_iter.first == 1) && (map_iter.second == "one"))
         {
            got_one = true;
         } else if (!got_two && (map_iter.first == 2)
                    && (map_iter.second == "two"))
         {
            got_two = true;
         } else if (!got_three && (map_iter.first == 3)
                    && (map_iter.second == "three"))
         {
            got_three = true;
         } else if (!got_four && (map_iter.first == 4)
                    && (map_iter.second == "four"))
         {
            got_four = true;
         } else if (!got_five && (map_iter.first == 5)
                    && (map_iter.second == "five"))
         {
            got_five = true;
         } else if (!got_six && (map_iter.first == 6)
                    && (map_iter.second == "six"))
         {
            got_six = true;
         } else
         {
            // should never get here
            BOOST_REQUIRE( map_iter.first == 0);
         } // end if
      } // end for

      BOOST_REQUIRE( got_one);
      BOOST_REQUIRE( got_two);
      BOOST_REQUIRE( got_three);
      BOOST_REQUIRE( got_four);
      BOOST_REQUIRE( got_five);
      BOOST_REQUIRE( got_six);
   } // end scope

   // now the default values should be cleared
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm
         = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-m 4,four;5,five", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 2);

      bool  got_four = false;
      bool  got_five = false;

      for (auto map_iter : umm)
      {
         if (!got_four && (map_iter.first == 4) && (map_iter.second == "four"))
         {
            got_four = true;
         } else if (!got_five && (map_iter.first == 5)
                    && (map_iter.second == "five"))
         {
            got_five = true;
         } else
         {
            // should never get here
            BOOST_REQUIRE( map_iter.first == 0);
         } // end if
      } // end for

      BOOST_REQUIRE( got_four);
      BOOST_REQUIRE( got_five);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm
         = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-m 4,four;5,five 6,six;7,seven;8,eight", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 5);

      bool  got_four = false;
      bool  got_five = false;
      bool  got_six = false;
      bool  got_seven = false;
      bool  got_eight = false;

      for (auto map_iter : umm)
      {
         if (!got_four && (map_iter.first == 4)
                    && (map_iter.second == "four"))
         {
            got_four = true;
         } else if (!got_five && (map_iter.first == 5)
                    && (map_iter.second == "five"))
         {
            got_five = true;
         } else if (!got_six && (map_iter.first == 6)
                    && (map_iter.second == "six"))
         {
            got_six = true;
         } else if (!got_seven && (map_iter.first == 7)
                    && (map_iter.second == "seven"))
         {
            got_seven = true;
         } else if (!got_eight && (map_iter.first == 8)
                    && (map_iter.second == "eight"))
         {
            got_eight = true;
         } else
         {
            // should never get here
            BOOST_REQUIRE( map_iter.first == 0);
         } // end if
      } // end for

      BOOST_REQUIRE( got_four);
      BOOST_REQUIRE( got_five);
      BOOST_REQUIRE( got_six);
      BOOST_REQUIRE( got_seven);
      BOOST_REQUIRE( got_eight);
   } // end scope

   // set default values, make argument optional, multi-map should be empty when
   // argument is used without value(s)
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm
         = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
         ->setClearBeforeAssign()->setValueMode( Handler::ValueMode::optional));

      auto const  as2a = make_arg_array( "-m", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( umm.empty());
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the
/// unordered multi-map.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                                     ah( 0);
   std::unordered_multimap< int, std::string>  umm;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
      ->addFormatValue( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "-m 1,monday;2,TUESDAY;3,wEdNeSdAy",
      nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( umm.size(), 3);

   bool  got_one = false;
   bool  got_two = false;
   bool  got_three = false;

   for (auto map_iter : umm)
   {
      if (!got_one && (map_iter.first == 1) && (map_iter.second == "monday"))
      {
         got_one = true;
      } else if (!got_two && (map_iter.first == 2)
                 && (map_iter.second == "tuesday"))
      {
         got_two = true;
      } else if (!got_three && (map_iter.first == 3)
                 && (map_iter.second == "wednesday"))
      {
         got_three = true;
      } else
      {
         BOOST_REQUIRE_EQUAL( map_iter.first, 0);
      } // end if
   } // end for

   BOOST_REQUIRE( got_one);
   BOOST_REQUIRE( got_two);
   BOOST_REQUIRE( got_three);

} // format_values



/// Test feature that only unique values should be stored in the unordered
/// multi-map.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_unique_values)
{

   // first check the default: duplicate values lead to multiple entries
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( umm), "values"));

      auto const  as2a = make_arg_array(
         "-v 2,two;3,three;4,four;4,five;6,six;7,seven", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 6);

      bool  got_two = false;
      bool  got_three = false;
      bool  got_four_four = false;
      bool  got_four_five = false;
      bool  got_six = false;
      bool  got_seven = false;

      CHECK_FOR (auto map_iter : umm)
      {
         if (!got_two && (map_iter.first == 2) && (map_iter.second == "two"))
         {
            got_two = true;
         } else if (!got_three && (map_iter.first == 3)
                    && (map_iter.second == "three"))
         {
            got_three = true;
         } else if (!got_four_four && (map_iter.first == 4)
                    && (map_iter.second == "four"))
         {
            got_four_four = true;
         } else if (!got_four_five&& (map_iter.first == 4)
                    && (map_iter.second == "five"))
         {
            got_four_five = true;
         } else if (!got_six && (map_iter.first == 6)
                    && (map_iter.second == "six"))
         {
            got_six = true;
         } else if (!got_seven && (map_iter.first == 7)
                    && (map_iter.second == "seven"))
         {
            got_seven = true;
         } else
         {
            BOOST_REQUIRE_EQUAL( map_iter.first, 0);
         } // end switch
      } // end for
      CHECK_FOR_COUNT( 6);

      BOOST_REQUIRE( got_two);
      BOOST_REQUIRE( got_three);
      BOOST_REQUIRE( got_four_four);
      BOOST_REQUIRE( got_four_five);
      BOOST_REQUIRE( got_six);
      BOOST_REQUIRE( got_seven);
   } // end scope

   // mode "ignore non-unique data without errors" can be set
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( umm), "values")
         ->setUniqueData());

      auto const  as2a = make_arg_array( "-v 2,two;3,three;4,four;4,five;6,six;7,seven", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( umm.size(), 5);

      bool  got_two = false;
      bool  got_three = false;
      bool  got_four = false;
      bool  got_six = false;
      bool  got_seven = false;

      CHECK_FOR (auto map_iter : umm)
      {
         if (!got_two && (map_iter.first == 2) && (map_iter.second == "two"))
         {
            got_two = true;
         } else if (!got_three && (map_iter.first == 3)
                    && (map_iter.second == "three"))
         {
            got_three = true;
         } else if (!got_four && (map_iter.first == 4)
                    && (map_iter.second == "four"))
         {
            got_four = true;
         } else if (!got_six && (map_iter.first == 6)
                    && (map_iter.second == "six"))
         {
            got_six = true;
         } else if (!got_seven && (map_iter.first == 7)
                    && (map_iter.second == "seven"))
         {
            got_seven = true;
         } else
         {
            BOOST_REQUIRE_EQUAL( map_iter.first, 0);
         } // end switch
      } // end for
      CHECK_FOR_COUNT( 5);

      BOOST_REQUIRE( got_two);
      BOOST_REQUIRE( got_three);
      BOOST_REQUIRE( got_four);
      BOOST_REQUIRE( got_six);
      BOOST_REQUIRE( got_seven);
   } // end scope

   // duplicates should lead to an error, also when conflicting with pre-set
   // values
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  umm
         = { { 1, "one" }, { 2, "two"}, { 3, "three"}};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( umm), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2,two;4,four 6,six;7,seven", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // test_unique_values



/// Test "list argument values" with an unordered multi-map.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream                          std_out;
   std::ostringstream                          std_err;
   Handler                                     ah( std_out, std_err,
      Handler::hfListArgVar);
   std::unordered_multimap< int, std::string>  umm;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "m", DEST_VAR( umm), "values")
      ->addFormatValue( celma::prog_args::lowercase()));

   auto const  as2a = make_arg_array( "--list-arg-vars "
      "-m 1,MONDAY;2,tuesday;3,wEdNeSdAy --list-arg-vars", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   BOOST_REQUIRE( !std_out.str().empty());
   // std::cerr << std_out.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-m' value type 'std::unordered_multimap<int,std::string>', destination container 'umm', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-m' value type 'std::unordered_multimap<int,std::string>', destination container 'umm', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, 1 formats.\n"
      "\n"));

} // list_arg_vars



/// Test constraint "disjoint" with two maps.
///
/// @since  1.41.0, 12.07.2020
BOOST_AUTO_TEST_CASE( disjoint_unordered_multimaps)
{

   using celma::prog_args::disjoint;

   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  map1;
      std::unordered_multimap< int, std::string>  map2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( map1), "left"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( map2), "right"));

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( disjoint( "l;r")));

      auto const  as2a = make_arg_array( "-l 1,one;2,two;3,three -r 4,four;5,five;6,six",
         nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // throw if the data in the sets is not disjoint
   {
      Handler                                     ah( 0);
      std::unordered_multimap< int, std::string>  map1;
      std::unordered_multimap< int, std::string>  map2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( map1), "left"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( map2), "right"));

      BOOST_REQUIRE_NO_THROW( ah.addConstraint( disjoint( "l;r")));

      auto const  as2a = make_arg_array( "-l 1,one;2,two;3,three -r 4,four;5,five;6,six;1,one",
         nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // disjoint_unordered_multimaps



// =====  END OF test_argh_dest_unordered_multi_map_c.cpp  =====

