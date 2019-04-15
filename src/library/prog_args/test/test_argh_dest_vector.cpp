
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


// module to test header file include
#include "celma/prog_args.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestVectorTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;



/// Test error case that can occur with a vector.
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_vector_errors)
{

   // assign wrong value types
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      const ArgString2Array  as2a( "-v this,should,throw", nullptr);

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



/// Test feature to set another character as list separator.
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      const ArgString2Array  as2a( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
   } // end scope

   // first check with the default list separator
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")->
         setListSep( '.'));

      const ArgString2Array  as2a( "-v 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple values.
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      const ArgString2Array  as2a( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};
      int  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      const ArgString2Array  as2a( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setTakesMultiValue());

      const ArgString2Array  as2a( "-v 4,5,6 7 8", nullptr);

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
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};
      int  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      const ArgString2Array  as2a( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler  ah( Handler::hfEndValues);
      std::vector< int>  v = { 1, 2, 3};
      int  free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      const ArgString2Array  as2a( "-v 4,5,6 7 --endvalues 8", nullptr);

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
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      const ArgString2Array  as2a( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 4);
      BOOST_REQUIRE_EQUAL( v[ 4], 5);
      BOOST_REQUIRE_EQUAL( v[ 5], 6);
   } // end scope

   // now the default values should be cleared
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setClearBeforeAssign());

      const ArgString2Array  as2a( "-v 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 2);
      BOOST_REQUIRE_EQUAL( v[ 0], 4);
      BOOST_REQUIRE_EQUAL( v[ 1], 5);
   } // end scope

   // make sure that the previously added values are not deleted when the
   // feature "multi-value" is used
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setClearBeforeAssign()->setTakesMultiValue());

      const ArgString2Array  as2a( "-v 4,5 6,7,8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 5);
      BOOST_REQUIRE_EQUAL( v[ 0], 4);
      BOOST_REQUIRE_EQUAL( v[ 1], 5);
      BOOST_REQUIRE_EQUAL( v[ 2], 6);
      BOOST_REQUIRE_EQUAL( v[ 3], 7);
      BOOST_REQUIRE_EQUAL( v[ 4], 8);
   } // end scope

} // test_clear_dest



/// Test feature to format the values before they are inserted into the vector.
///
/// @since  x.y.z, 09.04.2019
BOOST_AUTO_TEST_CASE( format_values)
{

   Handler                    ah( 0);
   std::vector< std::string>  v;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
      ->addFormat( celma::prog_args::lowercase()));

   const ArgString2Array  as2a( "-v monday,TUESDAY,wEdNeSdAy", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( v.size(), 3);
   BOOST_REQUIRE_EQUAL( v[ 0], "monday");
   BOOST_REQUIRE_EQUAL( v[ 1], "tuesday");
   BOOST_REQUIRE_EQUAL( v[ 2], "wednesday");

} // format_values



/// Test feature to sort the values in the vector.
///
/// @since  1.9.0, 04.08.2018
BOOST_AUTO_TEST_CASE( test_sort_values)
{

   // first check the default: values are stored as given
   {
      Handler  ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      const ArgString2Array  as2a( "-v 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 4);
      BOOST_REQUIRE_EQUAL( v[ 0], 34532);
      BOOST_REQUIRE_EQUAL( v[ 1], 9876);
      BOOST_REQUIRE_EQUAL( v[ 2], 33);
      BOOST_REQUIRE_EQUAL( v[ 3], 6);
   } // end scope

   // now the values should be sorted
   {
      Handler  ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setSortData());

      const ArgString2Array  as2a( "-v 34532,9876,33,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( v.size(), 4);
      BOOST_REQUIRE_EQUAL( v[ 0], 6);
      BOOST_REQUIRE_EQUAL( v[ 1], 33);
      BOOST_REQUIRE_EQUAL( v[ 2], 9876);
      BOOST_REQUIRE_EQUAL( v[ 3], 34532);
   } // end scope

   // should still be sorted when added as multiple values
   {
      Handler  ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setSortData()->setTakesMultiValue());

      const ArgString2Array  as2a( "-v 34532,9876,33,6 42,13,4711", nullptr);

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
      Handler  ah( 0);
      std::vector< int>  v = { 11, 255, 17 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setSortData()->setTakesMultiValue());

      const ArgString2Array  as2a( "-v 34532,9876,33,6 42,13,4711", nullptr);

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
      Handler  ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      const ArgString2Array  as2a( "-v 2,3,4,4,6,7", nullptr);

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
      Handler  ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setUniqueData());

      const ArgString2Array  as2a( "-v 2,3,4,4,6,7", nullptr);

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
      Handler  ah( 0);
      std::vector< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setUniqueData()->setTakesMultiValue());

      const ArgString2Array  as2a( "-v 2,3,4 3,5,6", nullptr);

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
      Handler  ah( 0);
      std::vector< int>  v = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setUniqueData()->setTakesMultiValue());

      const ArgString2Array  as2a( "-v 2,3,4 3,5,6", nullptr);

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
      Handler  ah( 0);
      std::vector< int>  v = { 3, 5, 6 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values")
         ->setUniqueData( true)->setTakesMultiValue());

      const ArgString2Array  as2a( "-v 2,4 6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // test_unique_values



// =====  END OF test_argh_dest_vector.cpp  =====

