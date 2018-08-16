
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
**    Test program for the module prog_args::Handler using the Boost.Test
**    module.
**
--*/


// module to test, header file include
#include "celma/prog_args.hpp"


// STL includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerTest
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args/helpers/triple_logic.hpp"


using celma::appl::ArgString2Array;
using celma::common::CheckAssign;
using celma::prog_args::Handler;
using celma::prog_args::helpers::TripleLogic;
using std::bad_cast;
using std::invalid_argument;
using std::logic_error;
using std::runtime_error;
using std::string;
using std::vector;



/// Test that the standard handling for standard arguments is not invoked when
/// the standard arguments are not enabled.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( std_args_not_used)
{

   Handler  ah( 0);


   {
      ArgString2Array  as2a( "-v", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      ArgString2Array  as2a( "--verbose", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      ArgString2Array  as2a( "-h", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      ArgString2Array  as2a( "--help", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

} // std_args_not_used



/// Tests that errors in setting up the arguments are caught.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( argument_setup_errors)
{

   CheckAssign< int>  iVal;


   // specify the same short argument twice
   {
      Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer"));
      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer"),
                           invalid_argument);
   } // end scope

   // specify the same long argument twice
   {
      Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "int", DEST_VAR( iVal), "Integer"));
      BOOST_REQUIRE_THROW( ah.addArgument( "int", DEST_VAR( iVal), "Integer"),
                           invalid_argument);
   } // end scope

   // specify the same short argument twice (together with different long arguments)
   {
      Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int", DEST_VAR( iVal), "Integer"));
      BOOST_REQUIRE_THROW( ah.addArgument( "i,max", DEST_VAR( iVal), "Integer"),
                           invalid_argument);
   } // end scope

   // specify the same long argument twice (together with different short arguments)
   {
      Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int", DEST_VAR( iVal), "Integer"));
      BOOST_REQUIRE_THROW( ah.addArgument( "m,int", DEST_VAR( iVal), "Integer"),
                           invalid_argument);
   } // end scope

   // specify an invalid range
   {
      Handler  ah( 0);
      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
                                         ->addCheck( celma::prog_args::range( 5, 5)),
                           invalid_argument);
   } // end scope

   // specify another invalid range
   {
      Handler  ah( 0);
      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
                                         ->addCheck( celma::prog_args::range( 5, 2)),
                           invalid_argument);
   } // end scope

   // specify an empty list of values
   {
      Handler  ah( 0);
      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
                                         ->addCheck( celma::prog_args::values( "")),
                           invalid_argument);
   } // end scope

   // specify to use standard short help argument and then specify an application
   // argument
   {
      Handler  ah( Handler::hfHelpShort);
      BOOST_REQUIRE_THROW( ah.addArgument( "h", DEST_VAR( iVal), "Integer"),
                           invalid_argument);
   } // end scope

   // specify to use standard long help argument and then specify an application
   // argument
   {
      Handler  ah( Handler::hfHelpLong);
      BOOST_REQUIRE_THROW( ah.addArgument( "help", DEST_VAR( iVal), "Integer"),
                           invalid_argument);
   } // end scope

   // Ensure that calling unsetFlag() on a wrong type throws.
   {
      Handler  ah( 0);
      int      i = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( i), "int")
                                         ->unsetFlag(),
                           logic_error);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  i;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( i), "int")
                                         ->unsetFlag(),
                           logic_error);
   } // end scope

   {
      Handler  ah( 0);
      string   s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "string")
                                         ->unsetFlag(),
                           logic_error);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "string")
                                         ->unsetFlag(),
                           logic_error);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  vi;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( vi), "int vector")
                                         ->unsetFlag(),
                           logic_error);
   } // end scope

   // flags == boolean arguments cannot be defined mandatory
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "boolean")
                                         ->setIsMandatory(),
                           logic_error);
   } // end scope

   {
      Handler             ah( 0);
      CheckAssign< bool>  flag;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "int")
                                         ->setIsMandatory(),
                           logic_error);
   } // end scope

   // Ensure that calling addFormat() on a wrong type throws.
   {
      Handler  ah( 0);
      bool     dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( dummy), "flag")
                                         ->addFormat( celma::prog_args::uppercase()),
                           logic_error);
   } // end scope

} // argument_setup_errors



/// Test that the short and long standard arguments are handled separately.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( std_args_not_matching)
{

   {
      Handler          ah( Handler::hfHelpShort);
      ArgString2Array  as2a( "--help", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      Handler          ah( Handler::hfHelpLong);
      ArgString2Array  as2a( "-h", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

} // std_args_not_matching



/// Single test case for a call without any argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( no_argument)
{

   Handler             ah( 0);
   CheckAssign< bool>  flag;


   ah.addArgument( "f", DEST_VAR( flag), "Boolean flag");

   ArgString2Array  as2a( "", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( !flag.hasValue());

} // no_argument



/// Verify that errors in the argument string are detected correctly:
/// - Mandatory argument missing
/// - Unknown argument
/// - Argument with required value without a value
/// - Flag argument with value
/// - Free argument without corresponding handler
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( parameter_string_errors)
{

   // mandatory argument missing
   {
      Handler            ah( 0);
      CheckAssign< int>  iVal1;
      CheckAssign< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1), "count")
                                            ->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2), "int"));

      ArgString2Array  as2a( "-i 17", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   // unknown argument
   {
      Handler            ah( 0);
      CheckAssign< int>  iVal1;
      CheckAssign< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1), "count")
                                            ->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2), "int"));

      ArgString2Array  as2a( "-h -c 5", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   // unknown long argument
   {
      Handler            ah( 0);
      CheckAssign< int>  iVal1;
      CheckAssign< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1), "count")
                                            ->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2), "int"));

      ArgString2Array  as2a( "-c 85 --history", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   // Argument with required value without a value (at beginning, i.e. followed
   // by another argument)
   {
      Handler            ah( 0);
      CheckAssign< int>  iVal1;
      CheckAssign< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1), "count")
                                            ->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2), "int"));

      ArgString2Array  as2a( "-i -c 9", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   // Argument with required value without a value (at end)
   {
      Handler            ah( 0);
      CheckAssign< int>  iVal1;
      CheckAssign< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1), "count")
                                            ->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2), "int"));

      ArgString2Array  as2a( "-c 8 -i", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

} // parameter_string_errors



/// Free argument without corresponding handler.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( unexpected_free_value)
{

   // single, unexpected free value
   {
      Handler          ah( 0);
      ArgString2Array  as2a( "free_value", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   // unexpected free value after argument
   {
      Handler          ah( 0);
      ArgString2Array  as2a( "-i 56 free_value", nullptr);
      int                      int_val;

      ah.addArgument( "i", DEST_VAR( int_val), "integer");

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

} // unexpected_free_value



/// Verify that the handling of free values is correct:
/// - detect mandatory free value missing
/// - correctly handle free value after argument without value
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( free_value_handling)
{

   // mandatory free value missing
   {
      Handler               ah( 0);
      CheckAssign< bool>    flag;
      CheckAssign< int>     iVal;
      CheckAssign< string>  name;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,flag", DEST_VAR( flag), "Flag"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",  DEST_VAR( iVal), "Flag"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-",      DEST_VAR( name), "Name")
                                            ->setIsMandatory());

      ArgString2Array  as2a( "-i 17", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   // mandatory free value missing
   {
      Handler               ah( 0);
      CheckAssign< bool>    flag;
      CheckAssign< int>     iVal;
      CheckAssign< string>  name;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,flag", DEST_VAR( flag), "Flag"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",  DEST_VAR( iVal), "Flag"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-",      DEST_VAR( name), "Name")
                                            ->setIsMandatory());

      ArgString2Array  as2a( "-f PROCESS1", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

} // free_value_handling



/// Checks that only one free-value argument can be added.<br>
/// Internally it is stored as argument '-', so it's not really a special case.
/// But it does not hurt to test it explicitly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_free_value)
{

   Handler  ah( 0);
   int      v1;
   int      v2;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( v1), "one"));
   BOOST_REQUIRE_THROW( ah.addArgument( "-", DEST_VAR( v2), "two"), invalid_argument);

} // one_free_value



/// Handling of one boolean flag with a short argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_flag)
{

   Handler             ah( 0);
   CheckAssign< bool>  flag;


   ah.addArgument( "f", DEST_VAR( flag), "Boolean flag");

   ArgString2Array  as2a( "-f", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( flag.hasValue());
   BOOST_REQUIRE( flag.value());

} // one_short_flag



/// Handling of one boolean flag with a short argument which clears/unsets the
/// flag.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_flag_unset)
{

   Handler  ah( 0);
   bool     flag = true;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "f", DEST_VAR( flag), "Boolean flag")
                                         ->unsetFlag());

   ArgString2Array  as2a( "-f", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( !flag);

} // one_short_flag_unset



/// Handling of one boolean flag with a short argument which clears/unsets the
/// flag.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_flag_checked_unset)
{

   Handler             ah( 0);
   CheckAssign< bool>  flag( true);


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "f", DEST_VAR( flag), "Boolean flag")
                                         ->unsetFlag());

   ArgString2Array  as2a( "-f", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( flag.hasValue());
   BOOST_REQUIRE( !flag.value());

} // one_short_flag_checked_unset



/// Handling of one boolean flag with a long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_long_flag)
{

   Handler             ah( 0);
   CheckAssign< bool>  flag;


   ah.addArgument( "flag", DEST_VAR( flag), "Boolean flag");

   ArgString2Array  as2a( "--flag", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( flag.hasValue());
   BOOST_REQUIRE( flag.value());

} // one_long_flag



/// Handling of one boolean flag with both short and long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_flag_both)
{

   {
      Handler             ah( 0);
      CheckAssign< bool>  flag;

      ah.addArgument( "f,flag", DEST_VAR( flag), "Boolean flag");

      ArgString2Array  as2a( "-f", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( flag.hasValue());
      BOOST_REQUIRE( flag.value());
   } // end scope

   {
      Handler             ah( 0);
      CheckAssign< bool>  flag;

      ah.addArgument( "f,flag", DEST_VAR( flag), "Boolean flag");

      ArgString2Array  as2a( "--flag", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( flag.hasValue());
      BOOST_REQUIRE( flag.value());
   } // end scope

} // one_flag_both



/// Handling of one integer argument with a short argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_int)
{

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "m", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "-m 500", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 500);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "m", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "-m500", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 500);
   } // end scope

} // one_short_int



/// Handling of one integer argument with a long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_long_int)
{

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "max_value", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "--max_value 2000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 2000);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "max_value", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "--max_value=7000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 7000);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "max_value", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "--max_value=-81", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), -81);
   } // end scope

} // one_long_int



/// Handling of one free integer argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_free_int)
{

   Handler            ah( 0);
   CheckAssign< int>  repetitions;


   ah.addArgument( "-", DEST_VAR( repetitions), "Number of repetitions");

   ArgString2Array  as2a( "123", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( repetitions.hasValue());
   BOOST_REQUIRE_EQUAL( repetitions.value(), 123);

} // one_free_int



/// Handling of one integer argument with both short and long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_int_both)
{

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "-m 500", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 500);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "-m500", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 500);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "--max_value 2000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 2000);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "--max_value=7000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 7000);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      ArgString2Array  as2a( "--max_value=-135", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( maxValue.value(), -135);
   } // end scope

} // one_int_both



/// Handling of one floating point argument with a short argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_double)
{

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "f", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "-f 7.5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), 7.5);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "f", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "-f7.5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), 7.5);
   } // end scope

} // one_short_double



/// Handling of one floating point argument with a long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_long_double)
{

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "factor", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "--factor 0.9", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), 0.9);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "factor", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "--factor=1.3", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), 1.3);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "factor", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "--factor=-125.75", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), -125.75);
   } // end scope

} // one_long_double



/// Handling of one free floating point argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_free_double)
{

   Handler               ah( 0);
   CheckAssign< double>  factor;


   ah.addArgument( "-", DEST_VAR( factor), "Factor");

   ArgString2Array  as2a( "99.98", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( factor.hasValue());
   BOOST_REQUIRE_EQUAL( factor.value(), 99.98);

} // one_free_double



/// Handling of one floating point argument with both short and long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_double_both)
{

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "f,factor", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "-f 7.5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), 7.5);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "f,factor", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "-f7.5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), 7.5);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "f,factor", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "--factor 0.9", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), 0.9);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< double>  factor;

      ah.addArgument( "f,factor", DEST_VAR( factor), "Factor");

      ArgString2Array  as2a( "--factor=58.9653", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( factor.hasValue());
      BOOST_REQUIRE_EQUAL( factor.value(), 58.9653);
   } // end scope

} // one_double_both



/// Handling of one string argument with a short argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_string)
{

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name");

      ArgString2Array  as2a( "-n PROCESS1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name");

      ArgString2Array  as2a( "-nPROCESS1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

} // one_short_string



/// Handling of one string argument with a long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_long_string)
{

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "name", DEST_VAR( name), "Name");

      ArgString2Array  as2a( "--name MY_PROCESS", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "MY_PROCESS");
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "name", DEST_VAR( name), "Name");

      ArgString2Array  as2a( "--name=OTHER_PROCESS", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "OTHER_PROCESS");
   } // end scope

} // one_long_string



/// Handling of one free string argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_free_string)
{

   Handler               ah( 0);
   CheckAssign< string>  name;


   ah.addArgument( "-", DEST_VAR( name), "Name");

   ArgString2Array  as2a( "PROCESS1", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( name.hasValue());
   BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");

} // one_free_string



/// Handling of one string argument with both short and long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_string_both)
{

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n,name", DEST_VAR( name), "Name");

      ArgString2Array  as2a( "-n PROCESS1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n,name", DEST_VAR( name), "Name");

      ArgString2Array  as2a( "-nPROCESS1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n,name", DEST_VAR( name), "Name");

      ArgString2Array  as2a( "--name MY_PROCESS", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "MY_PROCESS");
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n,name", DEST_VAR( name), "Name");

      ArgString2Array  as2a( "--name OTHER_PROCESS", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "OTHER_PROCESS");
   } // end scope

} // one_string_both



/// Handling of two flags.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( two_flags)
{

   /// Helper class used to provide a fresh set of the Handler object
   /// and the test variables.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, initialises the Handler.
      /// @param[in]  argstring  The argument string to pass to
      ///                        \c ArgString2Array.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "f,faster", DEST_VAR( faster), "Faster");
         ah.addArgument( "slower,s", DEST_VAR( slower), "Slower");
      } // end TestData::TestData

      /// The argument handler.
      Handler          ah;
      /// First checked boolean parameter.
      CheckAssign< bool>  faster;
      /// Second checked boolean parameter.
      CheckAssign< bool>  slower;
      /// Argument string split to argc, argv.
      ArgString2Array     as2a;
   }; // TestData

   {
      TestData  td( "");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.faster.hasValue());
      BOOST_REQUIRE( !td.slower.hasValue());
   } // end scope

   {
      TestData  td( "-f");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.faster.hasValue());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( !td.slower.hasValue());
   } // end scope

   {
      TestData  td( "-s");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.faster.hasValue());
      BOOST_REQUIRE( td.slower.hasValue());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td( "-fs");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.faster.hasValue());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.hasValue());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td( "-f -s");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.faster.hasValue());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.hasValue());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td( "-s -f");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.faster.hasValue());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.hasValue());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td( "-sf");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.faster.hasValue());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.hasValue());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td( "-s --faster");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.faster.hasValue());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.hasValue());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td( "--slower -f");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.faster.hasValue());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.hasValue());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td( "--slower --faster");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.faster.hasValue());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.hasValue());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

} // two_flags



/// Handling of a flag and a string.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( flag_and_string)
{

   /// Helper class used to provide a fresh set of the Handler object
   /// and the test variables.
   /// @since  0.2, 10.04.2016
   struct TestData
   {
      /// Constructor, initialises the Handler.
      /// @param[in]  argstring  The argument string to pass to
      ///                        \c ArgString2Array.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "flag,f", DEST_VAR( flag), "Flag");
         ah.addArgument( "n,name", DEST_VAR( name), "Name");
      } // end TestData::TestData

      /// The argument handler.
      Handler       ah;
      /// First checked parameter, boolean.
      CheckAssign< bool>    flag;
      /// Second checked parameter, string.
      CheckAssign< string>  name;
      /// Argument string split to argc, argv.
      ArgString2Array       as2a;
   }; // TestData

   {
      TestData  td( "-f -n PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-f -nPROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-n PROCESS1 -f");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-nPROCESS1 -f");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-f --name PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--name PROCESS1 -f");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--flag --name PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--name PROCESS1 --flag");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-fn PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-fnPROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.flag.hasValue());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

} // flag_and_string



/// Handling of an integer argument and a string.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( int_and_string)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         maxValue(),
         name(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");
         ah.addArgument( "n,name",      DEST_VAR( name),     "Name");
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler            ah;
      /// Destination variable.
      CheckAssign< int>     maxValue;
      /// Destination variable.
      CheckAssign< string>  name;
      /// Argument string split into argc, argv.
      ArgString2Array       as2a;

   }; // TestData

   {
      TestData  td( "");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.maxValue.hasValue());
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "-m 500");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "-m500");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "--max_value 1000");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "--max_value=4711");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 4711);
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "-n PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.maxValue.hasValue());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-nPROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.maxValue.hasValue());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--name MY_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.maxValue.hasValue());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td( "--name=OTHER_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.maxValue.hasValue());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

   {
      TestData  td( "-m 500 -n PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-m500 -n PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-m 500 -nPROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-m500 -nPROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--max_value 1000 -n PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--max_value 1000 -nPROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--max_value=2000 -n PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--max_value=2000 -nPROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-m 500 --name MY_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td( "-m500 --name MY_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td( "-m 500 --name=OTHER_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

   {
      TestData  td( "-m500 --name=OTHER_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

   {
      TestData  td( "--max_value 1000 --name MY_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td( "--max_value=2000 --name MY_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td( "--max_value 1000 --name=OTHER_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

   {
      TestData  td( "--max_value=3000 --name=OTHER_PROCESS");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 3000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

} // int_and_string



/// Handling of an integer argument and a free string.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( int_and_free_string)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         maxValue(),
         name(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");
         ah.addArgument( "-",           DEST_VAR( name),     "Name");
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler            ah;
      /// Destination variable.
      CheckAssign< int>     maxValue;
      /// Destination variable.
      CheckAssign< string>  name;
      /// Argument string split into argc, argv.
      ArgString2Array       as2a;

   }; // TestData

   {
      TestData  td( "");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.maxValue.hasValue());
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "-m 500");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "-m500");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "--max_value 1000");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "--max_value=4711");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 4711);
      BOOST_REQUIRE( !td.name.hasValue());
   } // end scope

   {
      TestData  td( "PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.maxValue.hasValue());
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-m 500 PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "-m500 PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--max_value 1000 PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td( "--max_value=2000 PROCESS1");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   // free value before named argument
   {
      TestData  td( "PROCESS1 --max_value=2000");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.maxValue.hasValue());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

} // int_and_free_string



/// Use the standard arguments for application parameters.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( application_uses_std_arg)
{

   {
      Handler            ah( 0);
      CheckAssign< int>  valor;


      ah.addArgument( "v", DEST_VAR( valor), "Valor number");

      ArgString2Array  as2a( "-v 25", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( valor.hasValue());
      BOOST_REQUIRE_EQUAL( valor.value(), 25);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  valor;


      ah.addArgument( "v", DEST_VAR( valor), "Valor number");

      ArgString2Array  as2a( "-v25", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( valor.hasValue());
      BOOST_REQUIRE_EQUAL( valor.value(), 25);
   } // end scope

   {
      Handler             ah( 0);
      CheckAssign< bool>  doVerbose;


      ah.addArgument( "verbose", DEST_VAR( doVerbose), "Set verbose on");

      ArgString2Array  as2a( "--verbose", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( doVerbose.hasValue());
      BOOST_REQUIRE( doVerbose.value());
   } // end scope

} // application_uses_std_arg



/// Check that values with wrong types are detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( type_mismatch)
{

   {
      Handler               ah( 0);
      CheckAssign< int>     iVal;
      CheckAssign< double>  fVal;
      CheckAssign< string>  sVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      ArgString2Array  as2a( "-i 3.5", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), bad_cast);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< int>     iVal;
      CheckAssign< double>  fVal;
      CheckAssign< string>  sVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      ArgString2Array  as2a( "-i3.5", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), bad_cast);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< int>     iVal;
      CheckAssign< double>  fVal;
      CheckAssign< string>  sVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      ArgString2Array  as2a( "-i myName", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), bad_cast);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< int>     iVal;
      CheckAssign< double>  fVal;
      CheckAssign< string>  sVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      ArgString2Array  as2a( "-imyName", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), bad_cast);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< int>     iVal;
      CheckAssign< double>  fVal;
      CheckAssign< string>  sVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      ArgString2Array  as2a( "-f myName", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), bad_cast);
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< int>     iVal;
      CheckAssign< double>  fVal;
      CheckAssign< string>  sVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      ArgString2Array  as2a( "-fmyName", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), bad_cast);
   } // end scope

} // type_mismatch



/// Test the handling of optional values.
/// @since  0.13.2, 17.02.2017
BOOST_AUTO_TEST_CASE( test_value_mode)
{

   using callable_int_t = TripleLogic< int>;

   // optional int value, argument not used at all
   {
      Handler         ah( 0);
      int             value = -1;
      callable_int_t  callable( value, 0);

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_int_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      ArgString2Array  as2a( "", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( value, -1);
   } // end scope

   // optional int value, argument used without value
   {
      Handler            ah( 0);
      int                value = -1;
      TripleLogic< int>  callable( value, 0);

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_int_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      ArgString2Array  as2a( "-v", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( value, 0);
   } // end scope

   // optional int value, argument used with value
   {
      Handler            ah( 0);
      int                value = -1;
      TripleLogic< int>  callable( value, 0);

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_int_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      ArgString2Array  as2a( "-v 42", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( value, 42);
   } // end scope

   using callable_string_t = TripleLogic< string>;

   // optional string value, argument not used at all
   {
      Handler  ah( 0);
      string   value( "hello world");
      callable_string_t  callable( value, "me, myself and I");

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_string_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      ArgString2Array  as2a( "", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( value, "hello world");
   } // end scope

   // optional string value, argument used without value
   {
      Handler  ah( 0);
      string   value( "hello world");
      callable_string_t  callable( value, "me, myself and I");

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_string_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      ArgString2Array  as2a( "-v", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( value, "me, myself and I");
   } // end scope

   // optional string value, argument used with value
   {
      Handler  ah( 0);
      string   value( "hello world");
      callable_string_t  callable( value, "me, myself and I");

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_string_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      ArgString2Array  as2a( "-v wonderworld", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( value, "wonderworld");
   } // end scope

} // test_value_mode



/// Special cases with '--' clause to e.g. accept negative values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( hyphen)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         name(),
         minVal(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "n,name", DEST_VAR( name),   "Name");
         ah.addArgument( "m,min",  DEST_VAR( minVal), "Minimum value");
      } // end TestData::TestData

      /// The argument handler object for the test.
     Handler             ah;
      /// Destination variable.
      CheckAssign< string>  name;
      /// Destination variable.
      CheckAssign< int>     minVal;
      /// Argument string split into argc, argv.
      ArgString2Array       as2a;

   }; // TestData

   {
      TestData  td( "-n -hyphenName");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
      BOOST_REQUIRE( !td.name.hasValue());
      BOOST_REQUIRE( !td.minVal.hasValue());
   } // end scope

   {
      TestData  td( "--name -hyphenName");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
      BOOST_REQUIRE( !td.name.hasValue());
      BOOST_REQUIRE( !td.minVal.hasValue());
   } // end scope

   {
      TestData  td( "-m -25");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
      BOOST_REQUIRE( !td.minVal.hasValue());
   } // end scope

   {
      TestData  td( "--min -25");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
      BOOST_REQUIRE( !td.minVal.hasValue());
   } // end scope

   {
      TestData  td( "-n -- -hyphenName");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "-hyphenName");
      BOOST_REQUIRE( !td.minVal.hasValue());
   } // end scope

   {
      TestData  td( "--name=-hyphenName");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "-hyphenName");
      BOOST_REQUIRE( !td.minVal.hasValue());
   } // end scope

   {
      TestData  td( "--name -- -hyphenName");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.name.hasValue());
      BOOST_REQUIRE_EQUAL( td.name.value(), "-hyphenName");
      BOOST_REQUIRE( !td.minVal.hasValue());
   } // end scope

   {
      TestData  td( "-m -- -30");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.name.hasValue());
      BOOST_REQUIRE( td.minVal.hasValue());
      BOOST_REQUIRE_EQUAL( td.minVal.value(), -30);
   } // end scope

   {
      TestData  td( "--min -- -70");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.name.hasValue());
      BOOST_REQUIRE( td.minVal.hasValue());
      BOOST_REQUIRE_EQUAL( td.minVal.value(), -70);
   } // end scope

} // hyphen



/// Check that missing, mandatory argument(s) are detected correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( missing_mandatory)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         iarg(),
         name(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "iarg,i", DEST_VAR( iarg), "integer arg")->setIsMandatory();
         ah.addArgument( "n,name", DEST_VAR( name), "Name");
      } // end TestData::TestData

      /// The argument handler object for the test.
     Handler             ah;
      /// Destination variable.
      CheckAssign< int>     iarg;
      /// Destination variable.
      CheckAssign< string>  name;
      /// Argument string split into argc, argv.
      ArgString2Array       as2a;

   }; // TestData

   {
      TestData  td( "");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-n PROCESS1");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-i 55");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

   {
      TestData  td( "--iarg=5");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData2: public TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData2( const string& argstring):
         TestData( argstring),
         iarg2()
      {
         ah.addArgument( "count,c", DEST_VAR( iarg2), "count")->setIsMandatory();
      } // end TestData2::TestData2

      /// Additional destination variable.
      CheckAssign< int>  iarg2;

   }; // TestData2

   {
      TestData2  td( "-f");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData2  td( "-c 5");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData2  td( "-n");

      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData2  td( "-i 1 -c 2");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

   {
      TestData2  td( "-c 5 -i 9");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

} // missing_mandatory



/// Check formatting functions.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( format_check)
{

   CheckAssign< string>  name;


   {
      Handler       ah( 0);
      ArgString2Array  as2a( "-n process1", nullptr);

      ah.addArgument( "n", DEST_VAR( name), "Name")->addFormat( celma::prog_args::uppercase());

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   name.reset();

   {
      Handler       ah( 0);
      ArgString2Array  as2a( "-n PROceSS1", nullptr);

      ah.addArgument( "n", DEST_VAR( name), "Name")->addFormat( celma::prog_args::lowercase());

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "process1");
   } // end scope

} // format_check



/// Helper class to check the implementation and usage of application specific
/// check classes.
/// @since  0.2, 10.04.2016
class ApplCheckTriple: public celma::prog_args::detail::ICheck
{
public:
   /// Constructor.
   /// @param[in]  first   The first value to accept.
   /// @param[in]  second  The second value to accept.
   /// @param[in]  third   The third value to accept.
   /// @since  0.2, 10.04.2016
   ApplCheckTriple( int first, int second, int third):
      m1( first),
      m2( second),
      m3( third)
   {
   }

   /// Checks if the value in \a val equals one of the three check values.
   /// @param[in]  val  The value to check in string format.
   /// @since  0.2, 10.04.2016
   virtual void checkValue( const string& val) const noexcept( false) override
   {
      int  checkVal = boost::lexical_cast< int>( val);
      if ((checkVal != m1) && (checkVal != m2) && (checkVal != m3))
         throw runtime_error( "not in tripple");
   }

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  0.16.0, 12.08.2017
   virtual std::string toString() const override
   {
      return "";
   }

private:
   int  m1;
   int  m2;
   int  m3;
}; // ApplCheckTriple



/// Helper function to use the application specific check function just like
/// the standard check functions from the library.
/// @param[in]  first   The first allowed value.
/// @param[in]  second  The second allowed value.
/// @param[in]  third   The third allowed value.
/// @return  Pointer to the newly created check object.
/// @since  0.2, 10.04.2016
static celma::prog_args::detail::ICheck* tripple( int first, int second, int third)
{
   return new ApplCheckTriple( first, second, third);
} // tripple



/// Application specific limit check.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( application_check)
{

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      ArgString2Array  as2a( "-i 1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      ArgString2Array  as2a( "-i 110", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      ArgString2Array  as2a( "-i 11", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 11);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      ArgString2Array  as2a( "-i 111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 111);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      ArgString2Array  as2a( "-i 1111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 1111);
   } // end scope

} // application_check



/// Test handling of control characters.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( control_check)
{


   Handler  ah( 0);
   int      value = -1;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( value), "some value"));

   {
      ArgString2Array  as2a( "-v 45 ! -v 47", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
      BOOST_REQUIRE_EQUAL( value, 45);  // since the first part should pass
   } // end scope

} // control_check



/// Test the different features related to handling a vector as destination.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_argument)
{

   {
      Handler   ah( 0);
      int       intArg;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( intArg), "integer argument")
                                         ->setListSep( ';'),
                           invalid_argument);
   } // end scope

   {
      Handler   ah( 0);
      string    stringArg;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( stringArg), "string argument")
                                         ->setListSep( ';'),
                           invalid_argument);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument")
                                            ->setListSep( ';'));

      ArgString2Array  as2a( "-i", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument")
                                            ->setListSep( ';'));

      ArgString2Array  as2a( "-i 17", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( intVec.size(), 1);
      BOOST_REQUIRE_EQUAL( intVec[ 0], 17);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument"));

      ArgString2Array  as2a( "-i 17,99", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( intVec.size(), 2);
      BOOST_REQUIRE_EQUAL( intVec[ 0], 17);
      BOOST_REQUIRE_EQUAL( intVec[ 1], 99);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument")
                                            ->setListSep( ';'));

      ArgString2Array  as2a( "-i 17;99", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( intVec.size(), 2);
      BOOST_REQUIRE_EQUAL( intVec[ 0], 17);
      BOOST_REQUIRE_EQUAL( intVec[ 1], 99);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument"));

      ArgString2Array  as2a( "-i 17 -i 88", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( intVec.size(), 2);
      BOOST_REQUIRE_EQUAL( intVec[ 0], 17);
      BOOST_REQUIRE_EQUAL( intVec[ 1], 88);
   } // end scope

   {
      Handler          ah( 0);
      vector< string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument"));

      ArgString2Array  as2a( "-s hello", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 1);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
   } // end scope

   {
      Handler          ah( 0);
      vector< string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument"));

      ArgString2Array  as2a( "-s hello,world", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 2);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
      BOOST_REQUIRE_EQUAL( stringVec[ 1], "world");
   } // end scope

   {
      Handler          ah( 0);
      vector< string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument"));

      ArgString2Array  as2a( "-s hello -s world", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 2);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
      BOOST_REQUIRE_EQUAL( stringVec[ 1], "world");
   } // end scope

   {
      Handler          ah( 0);
      vector< string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument")
                                            ->setListSep( '-'));

      ArgString2Array  as2a( "-s hello", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 1);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
   } // end scope

   {
      Handler          ah( 0);
      vector< string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument")
                                            ->setListSep( '-'));

      ArgString2Array  as2a( "-s hello-world", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 2);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
      BOOST_REQUIRE_EQUAL( stringVec[ 1], "world");
   } // end scope

   {
      Handler          ah( 0);
      vector< int>     intVec;
      vector< string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument"));

      ArgString2Array  as2a( "-i 3 -s hello -i 89 -s my,world -i 77,57", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( intVec.size(), 4);
      BOOST_REQUIRE_EQUAL( intVec[ 0],  3);
      BOOST_REQUIRE_EQUAL( intVec[ 1], 89);
      BOOST_REQUIRE_EQUAL( intVec[ 2], 77);
      BOOST_REQUIRE_EQUAL( intVec[ 3], 57);

      BOOST_REQUIRE_EQUAL( stringVec.size(), 3);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
      BOOST_REQUIRE_EQUAL( stringVec[ 1], "my");
      BOOST_REQUIRE_EQUAL( stringVec[ 2], "world");
   } // end scope

} // vector_argument



class TestControlArgs
{
public:
   TestControlArgs():
      mOpen( 0),
      mClose( 0),
      mNot( 0)
   {
   } // end TestControlArgs::TestControlArgs

   void open()
   {
      ++mOpen;
   }

   void close()
   {
      ++mClose;
   }

   void exclamation()
   {
      ++mNot;
   }

   int getOpen() const
   {
      return mOpen;
   }
   int getClose() const
   {
      return mClose;
   }
   int getExclamation() const
   {
      return mNot;
   }

private:
   int  mOpen;
   int  mClose;
   int  mNot;

}; // TestControlArgs



/// Checks handling of control characters.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( control_args)
{

   Handler          ah( 0);
   int              intArg1;
   int              intArg2;
   TestControlArgs  tca;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intArg1), "Integer argument 1"));
   BOOST_REQUIRE_NO_THROW( ah.addArgument( "j", DEST_VAR( intArg2), "Integer argument 2"));
   BOOST_REQUIRE_NO_THROW( ah.addControlHandler( '(', std::bind( &TestControlArgs::open, &tca)));
   BOOST_REQUIRE_NO_THROW( ah.addControlHandler( ')', std::bind( &TestControlArgs::close, &tca)));
   BOOST_REQUIRE_NO_THROW( ah.addControlHandler( '!', std::bind( &TestControlArgs::exclamation, &tca)));
   BOOST_REQUIRE_THROW(    ah.addControlHandler( '#', std::bind( &TestControlArgs::open, &tca)),
                           invalid_argument);

   ArgString2Array  as2a( "-i 11 ( ! -j 13 )", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( tca.getOpen(), 1);
   BOOST_REQUIRE_EQUAL( tca.getClose(), 1);
   BOOST_REQUIRE_EQUAL( tca.getExclamation(), 1);

} // control_args



// =====  END OF test_handler.cpp  =====

