
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of vectors by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestVectorTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


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

      ArgString2Array  as2a( "-v this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
         std::bad_cast);
   } // end scope

} // test_vector_errors



/// Test feature to set another character as list separator.
/// @since  1.2.0, 28.12.2017
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler  ah( 0);
      std::vector< int>  v = { 1, 2, 3};

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "values"));

      ArgString2Array  as2a( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
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

      ArgString2Array  as2a( "-v 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
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

      ArgString2Array  as2a( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
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

      ArgString2Array  as2a( "-v 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
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

      ArgString2Array  as2a( "-v 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
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

      ArgString2Array  as2a( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
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

      ArgString2Array  as2a( "-v 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
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

      ArgString2Array  as2a( "-v 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
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

      ArgString2Array  as2a( "-v 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( v.size(), 2);
      BOOST_REQUIRE_EQUAL( v[ 0], 4);
      BOOST_REQUIRE_EQUAL( v[ 1], 5);
   } // end scope

} // test_clear_dest



// ====================  END OF test_argh_dest_vector.cpp  ====================

