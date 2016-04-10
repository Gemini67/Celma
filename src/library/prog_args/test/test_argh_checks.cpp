
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "value checks" in the module prog_args::Handler,
**    using the Boost.Test module.
**
--*/


/// @todo: Test of free values
/// @todo: Mandatory free values


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// STL includes
#include <string>
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE HandlerChecksTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args.hpp"
#include "celma/common/arg_string_2_array.hpp"


using namespace std;
using namespace celma;


// module definitions


/// Check that the 'lower' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_limit)
{

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), underflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10000);
   } // end scope

} // end lower_limit



/// Check that the 'lower' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_limit_vector)
{

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), underflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10000);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10));

      common::ArgString2Array  as2a( "-i 10,5,10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), underflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

} // end lower_limit_vector



/// Check that the 'upper' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( upper_limit)
{

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 500", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 1);
   } // end scope

} // end upper_limit



/// Check that the 'upper' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( upper_limit_vector)
{

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 500", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 1);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 50,100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 50);
   } // end scope

} // end upper_limit_vector



/// Check that a combination of 'lower' and 'uppper' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_upper_limit)
{

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), underflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

} // end lower_upper_limit



/// Check that a combination of 'lower' and 'uppper' limit works correctly on a
/// vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_upper_limit_vector)
{

   {
      prog_args::Handler  ah( 0);
      vector< int>         iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), underflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 10,200", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), overflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::lower( 10))
                    ->addCheck( prog_args::upper( 100));

      common::ArgString2Array  as2a( "-i 20,5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), underflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 20);
   } // end scope

} // end lower_upper_limit_vector



/// Check that the 'range' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_range)
{

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

} // end check_range



/// Check that the 'range' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_range_vector)
{

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 10,200", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( prog_args::range( 10, 100));

      common::ArgString2Array  as2a( "-i 20,5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 20);
   } // end scope

} // end check_range_vector



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_string)
{

   {
      prog_args::Handler            ah( 0);
      common::CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( prog_args::values( "Peter,Paul,Mary"));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      prog_args::Handler            ah( 0);
      common::CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( prog_args::values( "Peter,Paul,Mary"));

      common::ArgString2Array  as2a( "-n peter", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      prog_args::Handler            ah( 0);
      common::CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( prog_args::values( "Peter,Paul,Mary"));

      common::ArgString2Array  as2a( "-n Paule", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      prog_args::Handler            ah( 0);
      common::CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( prog_args::values( "Peter,Paul,Mary"));

      common::ArgString2Array  as2a( "-n Pete", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      prog_args::Handler            ah( 0);
      common::CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( prog_args::values( "Peter,Paul,Mary"));

      common::ArgString2Array  as2a( "-n Peter", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Peter");
   } // end scope

   {
      prog_args::Handler            ah( 0);
      common::CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( prog_args::values( "Peter,Paul,Mary"));

      common::ArgString2Array  as2a( "-n Paul", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Paul");
   } // end scope

   {
      prog_args::Handler            ah( 0);
      common::CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( prog_args::values( "Peter,Paul,Mary"));

      common::ArgString2Array  as2a( "-n Mary", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Mary");
   } // end scope

} // end check_values_string



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_int)
{

   { 
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 110", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 11", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 11);
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 111);
   } // end scope

   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 1111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 1111);
   } // end scope

} // end check_values_int



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_int_vector)
{

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 110", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 11", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 11);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 111);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 1111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 1111);
   } // end scope

   {
      prog_args::Handler  ah( 0);
      vector< int>        iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( prog_args::values( "11,111,1111"));

      common::ArgString2Array  as2a( "-i 11,1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), range_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 11);
   } // end scope

} // end check_values_int_vector



// =========================  END OF test_argh_checks.cpp  =========================

