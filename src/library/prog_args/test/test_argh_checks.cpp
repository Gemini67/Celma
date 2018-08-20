
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "value checks" in the module Handler,
**    using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE HandlerChecksTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
using celma::common::CheckAssign;
using celma::prog_args::Handler;
using std::overflow_error;
using std::range_error;
using std::runtime_error;
using std::string;
using std::underflow_error;
using std::vector;



/// Check that the 'lower' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_limit)
{

   using celma::prog_args::lower;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10000);
   } // end scope

} // lower_limit



/// Check that the 'lower' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_limit_vector)
{

   using celma::prog_args::lower;

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10000);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      const ArgString2Array  as2a( "-i 10,5,10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

} // lower_limit_vector



/// Check that the 'upper' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( upper_limit)
{

   using celma::prog_args::upper;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 500", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 1);
   } // end scope

} // upper_limit



/// Check that the 'upper' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( upper_limit_vector)
{

   using celma::prog_args::upper;

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 500", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 1);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 50,100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 50);
   } // end scope

} // upper_limit_vector



/// Check that a combination of 'lower' and 'uppper' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_upper_limit)
{

   using celma::prog_args::lower;
   using celma::prog_args::upper;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

} // lower_upper_limit



/// Check that a combination of 'lower' and 'uppper' limit works correctly on a
/// vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_upper_limit_vector)
{

   using celma::prog_args::lower;
   using celma::prog_args::upper;

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 10,200", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      const ArgString2Array  as2a( "-i 20,5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 20);
   } // end scope

} // lower_upper_limit_vector



/// Check that the 'range' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_range)
{

   using celma::prog_args::range;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

} // check_range



/// Check that the 'range' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_range_vector)
{

   using celma::prog_args::range;

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 10,200", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      const ArgString2Array  as2a( "-i 20,5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 20);
   } // end scope

} // check_range_vector



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_string)
{

   using celma::prog_args::values;

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      const ArgString2Array  as2a( "-n peter", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      const ArgString2Array  as2a( "-n Paule", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      const ArgString2Array  as2a( "-n Pete", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      const ArgString2Array  as2a( "-n Peter", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Peter");
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      const ArgString2Array  as2a( "-n Paul", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Paul");
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      const ArgString2Array  as2a( "-n Mary", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Mary");
   } // end scope

} // check_values_string



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_int)
{

   using celma::prog_args::values;

   { 
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 110", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 11", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 11);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 111);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 1111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 1111);
   } // end scope

} // check_values_int



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_int_vector)
{

   using celma::prog_args::values;

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 110", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 11", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 11);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 111);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 1111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 1111);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      const ArgString2Array  as2a( "-i 11,1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         range_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 11);
   } // end scope

} // check_values_int_vector



/// Verify that the "is a file" and "is a directory" checks work correctly.
/// @since  1.4.1, 02.03.2018
BOOST_AUTO_TEST_CASE( correctly_check_file_directory)
{

   using celma::prog_args::isDirectory;
   using celma::prog_args::isFile;

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "File")->addCheck( isFile());

      const ArgString2Array  as2a( "-f /tmp", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "File")->addCheck( isFile());

      const ArgString2Array  as2a( "-f /etc/passwd", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope


   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Directory")
         ->addCheck( isDirectory());

      const ArgString2Array  as2a( "-d /etc/passwd", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Directory")
         ->addCheck( isDirectory());

      const ArgString2Array  as2a( "-d /tmp", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // correctly_check_file_directory



/// Verify that the "is an absolute path" check work correctly.
/// @since  1.4.2, 12.04.2018
BOOST_AUTO_TEST_CASE( correctly_check_absolute_path)
{

   using celma::prog_args::isAbsolutePath;

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      const ArgString2Array  as2a( "-p ./data/file.dat", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      const ArgString2Array  as2a( "-p data/file.dat", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      const ArgString2Array  as2a( "-p ~/data/file.dat", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      const ArgString2Array  as2a( "-p /etc/passwd", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope


} // correctly_check_absolute_path



/// Verify that a combined check for "is a directory" and "is an absolute path"
/// work correctly.
/// @since  1.4.2, 12.04.2018
BOOST_AUTO_TEST_CASE( check_directory_and_absolute_path)
{

   using celma::prog_args::isAbsolutePath;
   using celma::prog_args::isDirectory;

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      const ArgString2Array  as2a( "-d /etc/passwd", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      const ArgString2Array  as2a( "-d etc", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      const ArgString2Array  as2a( "-d ./etc", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      const ArgString2Array  as2a( "-d /etc", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // check_directory_and_absolute_path



/// Verify that the "parent directory exists" check work correctly.
/// @since  1.9.0, 04.08.2018
BOOST_AUTO_TEST_CASE( correctly_check_parent_diretory_exists)
{

   using celma::prog_args::parentDirectoryExists;

   // should throw when the path does not exist
   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "path and filename")
         ->addCheck( parentDirectoryExists());

      const ArgString2Array  as2a( "-f /home/anyusername/textfile.txt", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   { 
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "path and filename")
         ->addCheck( parentDirectoryExists());

      const ArgString2Array  as2a( "-f /etc/textfile.txt", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // correctly_check_parent_diretory_exists



// =====  END OF test_argh_checks.cpp  =====

