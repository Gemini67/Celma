
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module prog_args::Handler using the Boost.Test
**    module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerTest
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/prog_args/helpers/triple_logic.hpp"
#include "celma/prog_args/eval_argument_string.hpp"


using celma::prog_args::Handler;
using celma::prog_args::helpers::TripleLogic;



/// Check some cases where the functions of the argument handler are used
/// wrongly.
///
/// @since  1.22.0, 03.04.2019
BOOST_AUTO_TEST_CASE( wrong_usage)
{

   Handler  ah( 0);


   BOOST_REQUIRE_THROW( ah.getValueHandlerObj(), std::runtime_error);
   BOOST_REQUIRE_THROW( ah.addArgumentListArgGroups( "L"), std::invalid_argument);

} // wrong_usage



/// Test that the standard handling for standard arguments is not invoked when
/// the standard arguments are not enabled.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( std_args_not_used)
{

   Handler  ah( 0);


   {
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v"),
         std::invalid_argument);
   } // end scope

   {
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "--verbose"),
         std::invalid_argument);
   } // end scope

   {
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-h"),
         std::invalid_argument);
   } // end scope

   {
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "--help"),
         std::invalid_argument);
   } // end scope

} // std_args_not_used



/// Tests that errors in setting up the arguments are caught.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( argument_setup_errors)
{

   std::optional< int>  iVal;


   // specify the same short argument twice
   {
      Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer"));
      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer"),
         std::invalid_argument);
   } // end scope

   // specify the same long argument twice
   {
      Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "int", DEST_VAR( iVal), "Integer"));
      BOOST_REQUIRE_THROW( ah.addArgument( "int", DEST_VAR( iVal), "Integer"),
         std::invalid_argument);
   } // end scope

   // specify the same short argument twice (together with different long arguments)
   {
      Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int", DEST_VAR( iVal), "Integer"));
      BOOST_REQUIRE_THROW( ah.addArgument( "i,max", DEST_VAR( iVal), "Integer"),
         std::invalid_argument);
   } // end scope

   // specify the same long argument twice (together with different short arguments)
   {
      Handler  ah( 0);
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int", DEST_VAR( iVal), "Integer"));
      BOOST_REQUIRE_THROW( ah.addArgument( "m,int", DEST_VAR( iVal), "Integer"),
         std::invalid_argument);
   } // end scope

   // specify to use standard short help argument and then specify an application
   // argument
   {
      Handler  ah( Handler::hfHelpShort);
      BOOST_REQUIRE_THROW( ah.addArgument( "h", DEST_VAR( iVal), "Integer"),
         std::invalid_argument);
   } // end scope

   // specify to use standard long help argument and then specify an application
   // argument
   {
      Handler  ah( Handler::hfHelpLong);
      BOOST_REQUIRE_THROW( ah.addArgument( "help", DEST_VAR( iVal), "Integer"),
         std::invalid_argument);
   } // end scope

   // Ensure that calling unsetFlag() on a wrong type throws.
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "boolean")
         ->unsetFlag(), std::logic_error);
   } // end scope

   {
      Handler  ah( 0);
      int      i = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( i), "int")
         ->unsetFlag(), std::logic_error);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  i;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( i), "int")
         ->unsetFlag(), std::logic_error);
   } // end scope

   {
      Handler      ah( 0);
      std::string  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "string")
         ->unsetFlag(), std::logic_error);
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< std::string>  s;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( s), "string")
         ->unsetFlag(), std::logic_error);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  vi;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( vi), "int vector")
         ->unsetFlag(), std::logic_error);
   } // end scope

   // flags == boolean arguments cannot be defined mandatory
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "boolean")
         ->setIsMandatory(), std::logic_error);
   } // end scope

   {
      Handler               ah( 0);
      std::optional< bool>  flag;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "int")
         ->setIsMandatory(), std::logic_error);
   } // end scope

   // ensure that calling setSortData() on a wrong type throws.
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "boolean")
         ->setSortData(), std::logic_error);
   } // end scope

   {
      Handler  ah( 0);
      int      i_val = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( i_val), "int")
         ->setSortData(), std::logic_error);
   } // end scope

   {
      Handler      ah( 0);
      std::string  str;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( str), "string")
         ->setSortData(), std::logic_error);
   } // end scope

   // ensure that calling setUniqueData() on a wrong type throws.
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "boolean")
         ->setUniqueData(), std::logic_error);
   } // end scope

   {
      Handler  ah( 0);
      int      i_val = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( i_val), "int")
         ->setUniqueData(), std::logic_error);
   } // end scope

   {
      Handler      ah( 0);
      std::string  str;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( str), "string")
         ->setUniqueData(), std::logic_error);
   } // end scope

   // ensure that calling "check original value" on a wrong type throws.
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "boolean")
         ->checkOriginalValue( true), std::logic_error);
   } // end scope
   {
      Handler  ah( 0);
      int      int_val = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( int_val), "integer")
         ->checkOriginalValue( false), std::logic_error);
   } // end scope

   // ensure that calling "add key formatter" on a wrong type throws.
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "boolean")
         ->addFormatKey( celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "boolean")
         ->addFormatValue( celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope
   {
      Handler            ah( 0);
      std::vector< int>  ints;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( ints), "integers")
         ->addFormatKey( celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope
   {
      Handler  ah( 0);
      std::vector< int>  ints;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( ints), "integers")
         ->addFormatValue( celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope

} // argument_setup_errors



/// Test that the short and long standard arguments are handled separately.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( std_args_not_matching)
{

   {
      Handler     ah( Handler::hfHelpShort);
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "--help"),
         std::invalid_argument);
   } // end scope

   {
      Handler     ah( Handler::hfHelpLong);
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-h"),
         std::invalid_argument);
   } // end scope

} // std_args_not_matching



/// Single test case for a call without any argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( no_argument)
{

   Handler               ah( 0);
   std::optional< bool>  flag;


   ah.addArgument( "f", DEST_VAR( flag), "Boolean flag");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
   BOOST_REQUIRE( !flag.has_value());

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
      Handler              ah( 0);
      std::optional< int>  iVal1;
      std::optional< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1),
         "count")->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2),
         "int"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 17"),
         std::runtime_error);
   } // end scope

   // unknown argument
   {
      Handler              ah( 0);
      std::optional< int>  iVal1;
      std::optional< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1),
         "count")->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2),
         "int"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-h -c 5"),
         std::invalid_argument);
   } // end scope

   // unknown long argument
   {
      Handler              ah( 0);
      std::optional< int>  iVal1;
      std::optional< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1),
         "count")->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2), "int"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-c 85 --history"),
         std::invalid_argument);
   } // end scope

   // Argument with required value without a value (at beginning, i.e. followed
   // by another argument)
   {
      Handler              ah( 0);
      std::optional< int>  iVal1;
      std::optional< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1), "count")
                                            ->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2), "int"));

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i -c 9"),
        celma::prog_args::argument_error);
   } // end scope

   // Argument with required value without a value (at end)
   {
      Handler              ah( 0);
      std::optional< int>  iVal1;
      std::optional< int>  iVal2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c,count", DEST_VAR( iVal1), "count")
                                            ->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",   DEST_VAR( iVal2), "int"));

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "-c 8 -i"),
        celma::prog_args::argument_error);
   } // end scope

} // parameter_string_errors



/// Free argument without corresponding handler.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( unexpected_free_value)
{

   // single, unexpected free value
   {
      Handler  ah( 0);

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "free_value"),
                           std::invalid_argument);
   } // end scope

   // unexpected free value after argument
   {
      Handler  ah( 0);
      int      int_val;

      ah.addArgument( "i", DEST_VAR( int_val), "integer");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 56 free_value"),
         std::invalid_argument);
   } // end scope

} // unexpected_free_value



/// Exclamation mark on command line used on argument that does not support
/// this.
///
/// @since  1.27.0, 28.05.2019
BOOST_AUTO_TEST_CASE( unsupported_exclamation_mark)
{

   // try to set exclamation mark on a destination type that does not support it
   {
      Handler  ah( 0);
      bool     flag = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "a flag")
         ->allowsInversion(), std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);
      int      ival = 42;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( ival),
         "an integer value")->allowsInversion(), std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);
      bool     flag = false;

      ah.addArgument( "f", DEST_VAR( flag), "a flag");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "! -f"),
                           std::invalid_argument);
   } // end scope

   {
      Handler  ah( 0);
      int      ival = 42;

      ah.addArgument( "i", DEST_VAR( ival), "an integer value");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "! -i 42"),
                           std::invalid_argument);
   } // end scope

   // exclamation mark used between argument and value
   {
      Handler  ah( 0);
      int      ival = 42;

      ah.addArgument( "i", DEST_VAR( ival), "an integer value");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i ! 42"),
                           celma::prog_args::argument_error);
   } // end scope

} // unsupported_exclamation_mark



/// Verify that the handling of free values is correct:
/// - detect mandatory free value missing
/// - correctly handle free value after argument without value
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( free_value_handling)
{

   // mandatory free value missing
   {
      Handler                      ah( 0);
      std::optional< bool>         flag;
      std::optional< int>          iVal;
      std::optional< std::string>  name;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,flag", DEST_VAR( flag), "Flag"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",  DEST_VAR( iVal), "Flag"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-",      DEST_VAR( name), "Name")
                                            ->setIsMandatory());

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 17"),
                           std::runtime_error);
   } // end scope

   // mandatory free value missing
   {
      Handler                      ah( 0);
      std::optional< bool>         flag;
      std::optional< int>          iVal;
      std::optional< std::string>  name;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f,flag", DEST_VAR( flag), "Flag"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i,int",  DEST_VAR( iVal), "Flag"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-",      DEST_VAR( name), "Name")
                                            ->setIsMandatory());

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f PROCESS1"));
      BOOST_REQUIRE( name.has_value());
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
   BOOST_REQUIRE_THROW( ah.addArgument( "-", DEST_VAR( v2), "two"),
      std::invalid_argument);

} // one_free_value



/// Handling of one boolean flag with a short argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_flag)
{

   Handler               ah( 0);
   std::optional< bool>  flag;


   ah.addArgument( "f", DEST_VAR( flag), "Boolean flag");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f"));
   BOOST_REQUIRE( flag.has_value());
   BOOST_REQUIRE( flag.value());

} // one_short_flag



/// Handling of one boolean flag with a short argument which clears/unsets the
/// flag.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_flag_unset)
{

   Handler  ah( 0);
   bool     flag = true;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "f", DEST_VAR( flag), "Boolean flag"));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f"));
   BOOST_REQUIRE( !flag);

} // one_short_flag_unset



/// Handling of one boolean flag with a short argument which clears/unsets the
/// flag.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_flag_checked_unset)
{

   Handler               ah( 0);
   std::optional< bool>  flag;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "f", DEST_VAR( flag), "Boolean flag")
      ->unsetFlag());

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f"));
   BOOST_REQUIRE( flag.has_value());
   BOOST_REQUIRE( !flag.value());

} // one_short_flag_checked_unset



/// Handling of one boolean flag with a long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_long_flag)
{

   Handler               ah( 0);
   std::optional< bool>  flag;


   ah.addArgument( "flag", DEST_VAR( flag), "Boolean flag");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--flag"));
   BOOST_REQUIRE( flag.has_value());
   BOOST_REQUIRE( flag.value());

} // one_long_flag



/// Handling of one boolean flag with both short and long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_flag_both)
{

   {
      Handler               ah( 0);
      std::optional< bool>  flag;

      ah.addArgument( "f,flag", DEST_VAR( flag), "Boolean flag");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f"));
      BOOST_REQUIRE( flag.has_value());
      BOOST_REQUIRE( flag.value());
   } // end scope

   {
      Handler               ah( 0);
      std::optional< bool>  flag;

      ah.addArgument( "f,flag", DEST_VAR( flag), "Boolean flag");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--flag"));
      BOOST_REQUIRE( flag.has_value());
      BOOST_REQUIRE( flag.value());
   } // end scope

} // one_flag_both



/// Handling of one integer argument with a short argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_int)
{

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "m", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 500"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 500);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "m", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m500"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 500);
   } // end scope

} // one_short_int



/// Handling of one integer argument with a long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_long_int)
{

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "max_value", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--max_value 2000"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 2000);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "max_value", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--max_value=7000"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 7000);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "max_value", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--max_value=-81"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), -81);
   } // end scope

} // one_long_int



/// Handling of one free integer argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_free_int)
{

   Handler              ah( 0);
   std::optional< int>  repetitions;


   ah.addArgument( "-", DEST_VAR( repetitions), "Number of repetitions");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "123"));
   BOOST_REQUIRE( repetitions.has_value());
   BOOST_REQUIRE_EQUAL( repetitions.value(), 123);

} // one_free_int



/// Handling of one integer argument with both short and long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_int_both)
{

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m 500"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 500);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-m500"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 500);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--max_value 2000"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 2000);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--max_value=7000"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), 7000);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  maxValue;

      ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--max_value=-135"));
      BOOST_REQUIRE( maxValue.has_value());
      BOOST_REQUIRE_EQUAL( maxValue.value(), -135);
   } // end scope

} // one_int_both



/// Handling of one floating point argument with a short argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_double)
{

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "f", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f 7.5"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), 7.5);
   } // end scope

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "f", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f7.5"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), 7.5);
   } // end scope

} // one_short_double



/// Handling of one floating point argument with a long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_long_double)
{

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "factor", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--factor 0.9"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), 0.9);
   } // end scope

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "factor", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--factor=1.3"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), 1.3);
   } // end scope

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "factor", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--factor=-125.75"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), -125.75);
   } // end scope

} // one_long_double



/// Handling of one free floating point argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_free_double)
{

   Handler                 ah( 0);
   std::optional< double>  factor;


   ah.addArgument( "-", DEST_VAR( factor), "Factor");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "99.98"));
   BOOST_REQUIRE( factor.has_value());
   BOOST_REQUIRE_EQUAL( factor.value(), 99.98);

} // one_free_double



/// Handling of one floating point argument with both short and long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_double_both)
{

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "f,factor", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f 7.5"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), 7.5);
   } // end scope

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "f,factor", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-f7.5"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), 7.5);
   } // end scope

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "f,factor", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--factor 0.9"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), 0.9);
   } // end scope

   {
      Handler                 ah( 0);
      std::optional< double>  factor;

      ah.addArgument( "f,factor", DEST_VAR( factor), "Factor");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--factor=58.9653"));
      BOOST_REQUIRE( factor.has_value());
      BOOST_REQUIRE_EQUAL( factor.value(), 58.9653);
   } // end scope

} // one_double_both



/// Handling of one string argument with a short argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_short_string)
{

   {
      Handler                      ah( 0);
      std::optional< std::string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n PROCESS1"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< std::string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-nPROCESS1"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

} // one_short_string



/// Handling of one string argument with a long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_long_string)
{

   {
      Handler                      ah( 0);
      std::optional< std::string>  name;

      ah.addArgument( "name", DEST_VAR( name), "Name");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--name MY_PROCESS"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "MY_PROCESS");
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< std::string>  name;

      ah.addArgument( "name", DEST_VAR( name), "Name");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--name=OTHER_PROCESS"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "OTHER_PROCESS");
   } // end scope

} // one_long_string



/// Handling of one free string argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_free_string)
{

   Handler                      ah( 0);
   std::optional< std::string>  name;


   ah.addArgument( "-", DEST_VAR( name), "Name");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "PROCESS1"));
   BOOST_REQUIRE( name.has_value());
   BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");

} // one_free_string



/// Handling of one string argument with both short and long argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_string_both)
{

   {
      Handler                      ah( 0);
      std::optional< std::string>  name;

      ah.addArgument( "n,name", DEST_VAR( name), "Name");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-n PROCESS1"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< std::string>  name;

      ah.addArgument( "n,name", DEST_VAR( name), "Name");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-nPROCESS1"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "PROCESS1");
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< std::string>  name;

      ah.addArgument( "n,name", DEST_VAR( name), "Name");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--name MY_PROCESS"));
      BOOST_REQUIRE( name.has_value());
      BOOST_REQUIRE_EQUAL( name.value(), "MY_PROCESS");
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< std::string>  name;

      ah.addArgument( "n,name", DEST_VAR( name), "Name");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--name OTHER_PROCESS"));
      BOOST_REQUIRE( name.has_value());
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
      /// @since  1.46.1, 2208.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0)
      {
         ah.addArgument( "f,faster", DEST_VAR( faster), "Faster");
         ah.addArgument( "slower,s", DEST_VAR( slower), "Slower");
      } // end TestData::TestData

      /// The argument handler.
      Handler               ah;
      /// First checked boolean parameter.
      std::optional< bool>  faster;
      /// Second checked boolean parameter.
      std::optional< bool>  slower;
   }; // TestData

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, ""));
      BOOST_REQUIRE( !td.faster.has_value());
      BOOST_REQUIRE( !td.slower.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-f"));
      BOOST_REQUIRE( td.faster.has_value());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( !td.slower.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-s"));
      BOOST_REQUIRE( !td.faster.has_value());
      BOOST_REQUIRE( td.slower.has_value());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-fs"));
      BOOST_REQUIRE( td.faster.has_value());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.has_value());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-f -s"));
      BOOST_REQUIRE( td.faster.has_value());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.has_value());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-s -f"));
      BOOST_REQUIRE( td.faster.has_value());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.has_value());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-sf"));
      BOOST_REQUIRE( td.faster.has_value());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.has_value());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-s --faster"));
      BOOST_REQUIRE( td.faster.has_value());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.has_value());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--slower -f"));
      BOOST_REQUIRE( td.faster.has_value());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.has_value());
      BOOST_REQUIRE( td.slower.value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--slower --faster"));
      BOOST_REQUIRE( td.faster.has_value());
      BOOST_REQUIRE( td.faster.value());
      BOOST_REQUIRE( td.slower.has_value());
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
      /// @since  1.46.1, 22.08.2021  (no argument string anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0)
      {
         ah.addArgument( "flag,f", DEST_VAR( flag), "Flag");
         ah.addArgument( "n,name", DEST_VAR( name), "Name");
      } // end TestData::TestData

      /// The argument handler.
      Handler                      ah;
      /// First checked parameter, boolean.
      std::optional< bool>         flag;
      /// Second checked parameter, string.
      std::optional< std::string>  name;
   }; // TestData

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-f -n PROCESS1"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-f -nPROCESS1"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-n PROCESS1 -f"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-nPROCESS1 -f"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-f --name PROCESS1"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--name PROCESS1 -f"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--flag --name PROCESS1"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--name PROCESS1 --flag"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-fn PROCESS1"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-fnPROCESS1"));
      BOOST_REQUIRE( td.flag.has_value());
      BOOST_REQUIRE( td.flag.value());
      BOOST_REQUIRE( td.name.has_value());
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
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0),
         maxValue(),
         name()
      {
         ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");
         ah.addArgument( "n,name",      DEST_VAR( name),     "Name");
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler                      ah;
      /// Destination variable.
      std::optional< int>          maxValue;
      /// Destination variable.
      std::optional< std::string>  name;

   }; // TestData

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, ""));
      BOOST_REQUIRE( !td.maxValue.has_value());
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m 500"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m500"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value 1000"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value=4711"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 4711);
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-n PROCESS1"));
      BOOST_REQUIRE( !td.maxValue.has_value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-nPROCESS1"));
      BOOST_REQUIRE( !td.maxValue.has_value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--name MY_PROCESS"));
      BOOST_REQUIRE( !td.maxValue.has_value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--name=OTHER_PROCESS"));
      BOOST_REQUIRE( !td.maxValue.has_value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m 500 -n PROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m500 -n PROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m 500 -nPROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m500 -nPROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value 1000 -n PROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value 1000 -nPROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value=2000 -n PROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value=2000 -nPROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m 500 --name MY_PROCESS"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m500 --name MY_PROCESS"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m 500 --name=OTHER_PROCESS"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m500 --name=OTHER_PROCESS"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value 1000 --name MY_PROCESS"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value=2000 --name MY_PROCESS"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "MY_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value 1000 --name=OTHER_PROCESS"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "OTHER_PROCESS");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value=3000 --name=OTHER_PROCESS"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 3000);
      BOOST_REQUIRE( td.name.has_value());
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
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0),
         maxValue(),
         name()
      {
         ah.addArgument( "max_value,m", DEST_VAR( maxValue), "Maximum value");
         ah.addArgument( "-",           DEST_VAR( name),     "Name");
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler                      ah;
      /// Destination variable.
      std::optional< int>          maxValue;
      /// Destination variable.
      std::optional< std::string>  name;

   }; // TestData

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, ""));
      BOOST_REQUIRE( !td.maxValue.has_value());
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m 500"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m500"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value 1000"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value=4711"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 4711);
      BOOST_REQUIRE( !td.name.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "PROCESS1"));
      BOOST_REQUIRE( !td.maxValue.has_value());
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m 500 PROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m500 PROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 500);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value 1000 PROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 1000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--max_value=2000 PROCESS1"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

   // free value before named argument
   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "PROCESS1 --max_value=2000"));
      BOOST_REQUIRE( td.maxValue.has_value());
      BOOST_REQUIRE_EQUAL( td.maxValue.value(), 2000);
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "PROCESS1");
   } // end scope

} // int_and_free_string



/// Use the standard arguments for application parameters.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( application_uses_std_arg)
{

   {
      Handler              ah( 0);
      std::optional< int>  valor;

      ah.addArgument( "v", DEST_VAR( valor), "Valor number");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 25"));
      BOOST_REQUIRE( valor.has_value());
      BOOST_REQUIRE_EQUAL( valor.value(), 25);
   } // end scope

   {
      Handler              ah( 0);
      std::optional< int>  valor;

      ah.addArgument( "v", DEST_VAR( valor), "Valor number");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v25"));
      BOOST_REQUIRE( valor.has_value());
      BOOST_REQUIRE_EQUAL( valor.value(), 25);
   } // end scope

   {
      Handler               ah( 0);
      std::optional< bool>  doVerbose;

      ah.addArgument( "verbose", DEST_VAR( doVerbose), "Set verbose on");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--verbose"));
      BOOST_REQUIRE( doVerbose.has_value());
      BOOST_REQUIRE( doVerbose.value());
   } // end scope

} // application_uses_std_arg



/// Check that values with wrong types are detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( type_mismatch)
{

   {
      Handler                      ah( 0);
      std::optional< int>          iVal;
      std::optional< double>       fVal;
      std::optional< std::string>  sVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 3.5"), std::bad_cast);
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< int>          iVal;
      std::optional< double>       fVal;
      std::optional< std::string>  sVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i3.5"), std::bad_cast);
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< int>          iVal;
      std::optional< double>       fVal;
      std::optional< std::string>  sVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i myName"), std::bad_cast);
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< int>          iVal;
      std::optional< double>       fVal;
      std::optional< std::string>  sVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-imyName"), std::bad_cast);
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< int>          iVal;
      std::optional< double>       fVal;
      std::optional< std::string>  sVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-f myName"), std::bad_cast);
   } // end scope

   {
      Handler                      ah( 0);
      std::optional< int>          iVal;
      std::optional< double>       fVal;
      std::optional< std::string>  sVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer");
      ah.addArgument( "f", DEST_VAR( fVal), "Double");
      ah.addArgument( "s", DEST_VAR( sVal), "String");

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-fmyName"), std::bad_cast);
   } // end scope

} // type_mismatch



/// Test the handling of optional values.
/// @since  0.13.2, 17.02.2017
BOOST_AUTO_TEST_CASE( test_value_mode)
{

   // re-set the same value mode
   {
      Handler         ah( 0);
      int             value = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( value), "int value")
         ->setValueMode( Handler::ValueMode::required));
   } // end scope

   using callable_int_t = TripleLogic< int>;

   // optional int value, argument not used at all
   {
      Handler         ah( 0);
      int             value = -1;
      callable_int_t  callable( value, 0);

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_int_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
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

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v"));
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

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 42"));
      BOOST_REQUIRE_EQUAL( value, 42);
   } // end scope

   using callable_string_t = TripleLogic< std::string>;

   // optional string value, argument not used at all
   {
      Handler            ah( 0);
      std::string        value( "hello world");
      callable_string_t  callable( value, "me, myself and I");

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_string_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
      BOOST_REQUIRE_EQUAL( value, "hello world");
   } // end scope

   // optional string value, argument used without value
   {
      Handler            ah( 0);
      std::string        value( "hello world");
      callable_string_t  callable( value, "me, myself and I");

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_string_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v"));
      BOOST_REQUIRE_EQUAL( value, "me, myself and I");
   } // end scope

   // optional string value, argument used with value
   {
      Handler            ah( 0);
      std::string        value( "hello world");
      callable_string_t  callable( value, "me, myself and I");

      ah.addArgument( "v", DEST_METHOD_VALUE( callable_string_t, assign, callable),
                      "A value")
                    ->setValueMode( Handler::ValueMode::optional);

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v wonderworld"));
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
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0),
         name(),
         minVal()
      {
         ah.addArgument( "n,name", DEST_VAR( name),   "Name");
         ah.addArgument( "m,min",  DEST_VAR( minVal), "Minimum value");
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler                      ah;
      /// Destination variable.
      std::optional< std::string>  name;
      /// Destination variable.
      std::optional< int>          minVal;

   }; // TestData

   {
      TestData  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-n -hyphenName"),
         celma::prog_args::argument_error);
      BOOST_REQUIRE( !td.name.has_value());
      BOOST_REQUIRE( !td.minVal.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "--name -hyphenName"),
         celma::prog_args::argument_error);
      BOOST_REQUIRE( !td.name.has_value());
      BOOST_REQUIRE( !td.minVal.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-m -25"),
         celma::prog_args::argument_error);
      BOOST_REQUIRE( !td.minVal.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "--min -25"),
         celma::prog_args::argument_error);
      BOOST_REQUIRE( !td.minVal.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-n -- -hyphenName"));
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "-hyphenName");
      BOOST_REQUIRE( !td.minVal.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--name=-hyphenName"));
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "-hyphenName");
      BOOST_REQUIRE( !td.minVal.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--name -- -hyphenName"));
      BOOST_REQUIRE( td.name.has_value());
      BOOST_REQUIRE_EQUAL( td.name.value(), "-hyphenName");
      BOOST_REQUIRE( !td.minVal.has_value());
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-m -- -30"));
      BOOST_REQUIRE( !td.name.has_value());
      BOOST_REQUIRE( td.minVal.has_value());
      BOOST_REQUIRE_EQUAL( td.minVal.value(), -30);
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--min -- -70"));
      BOOST_REQUIRE( !td.name.has_value());
      BOOST_REQUIRE( td.minVal.has_value());
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
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0),
         iarg(),
         name()
      {
         ah.addArgument( "iarg,i", DEST_VAR( iarg), "integer arg")->setIsMandatory();
         ah.addArgument( "n,name", DEST_VAR( name), "Name");
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler                      ah;
      /// Destination variable.
      std::optional< int>          iarg;
      /// Destination variable.
      std::optional< std::string>  name;

   }; // TestData

   {
      TestData  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, ""),
                           std::runtime_error);
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-n PROCESS1"),
                           std::runtime_error);
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-i 55"));
   } // end scope

   {
      TestData  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "--iarg=5"));
   } // end scope

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData2: public TestData
   {
   public:
      /// Constructor, does all the work.
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData2():
         TestData(),
         iarg2()
      {
         ah.addArgument( "count,c", DEST_VAR( iarg2), "count")->setIsMandatory();
      } // end TestData2::TestData2

      /// Additional destination variable.
      std::optional< int>  iarg2;

   }; // TestData2

   {
      TestData2  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-f"),
                           std::invalid_argument);
   } // end scope

   {
      TestData2  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-c 5"),
                           std::runtime_error);
   } // end scope

   {
      TestData2  td;

      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-n"),
                           celma::prog_args::argument_error);
   } // end scope

   {
      TestData2  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-i 1 -c 2"));
   } // end scope

   {
      TestData2  td;

      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-c 5 -i 9"));
   } // end scope

} // missing_mandatory



/// Test the different features related to handling a vector as destination.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_argument)
{

   {
      Handler  ah( 0);
      int      intArg;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( intArg), "integer argument")
                                         ->setListSep( ';'),
                           std::invalid_argument);
   } // end scope

   {
      Handler      ah( 0);
      std::string  stringArg;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( stringArg), "string argument")
                                         ->setListSep( ';'),
                           std::invalid_argument);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument")
                                            ->setListSep( ';'));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i"),
                           celma::prog_args::argument_error);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument")
                                            ->setListSep( ';'));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 17"));
      BOOST_REQUIRE_EQUAL( intVec.size(), 1);
      BOOST_REQUIRE_EQUAL( intVec[ 0], 17);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 17,99"));
      BOOST_REQUIRE_EQUAL( intVec.size(), 2);
      BOOST_REQUIRE_EQUAL( intVec[ 0], 17);
      BOOST_REQUIRE_EQUAL( intVec[ 1], 99);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument")
                                            ->setListSep( ';'));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 17;99"));
      BOOST_REQUIRE_EQUAL( intVec.size(), 2);
      BOOST_REQUIRE_EQUAL( intVec[ 0], 17);
      BOOST_REQUIRE_EQUAL( intVec[ 1], 99);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  intVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 17 -i 88"));
      BOOST_REQUIRE_EQUAL( intVec.size(), 2);
      BOOST_REQUIRE_EQUAL( intVec[ 0], 17);
      BOOST_REQUIRE_EQUAL( intVec[ 1], 88);
   } // end scope

   {
      Handler                    ah( 0);
      std::vector< std::string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-s hello"));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 1);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
   } // end scope

   {
      Handler                    ah( 0);
      std::vector< std::string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-s hello,world"));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 2);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
      BOOST_REQUIRE_EQUAL( stringVec[ 1], "world");
   } // end scope

   {
      Handler                    ah( 0);
      std::vector< std::string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-s hello -s world"));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 2);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
      BOOST_REQUIRE_EQUAL( stringVec[ 1], "world");
   } // end scope

   {
      Handler                    ah( 0);
      std::vector< std::string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument")
                                            ->setListSep( '-'));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-s hello"));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 1);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
   } // end scope

   {
      Handler                    ah( 0);
      std::vector< std::string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument")
                                            ->setListSep( '-'));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-s hello-world"));
      BOOST_REQUIRE_EQUAL( stringVec.size(), 2);
      BOOST_REQUIRE_EQUAL( stringVec[ 0], "hello");
      BOOST_REQUIRE_EQUAL( stringVec[ 1], "world");
   } // end scope

   {
      Handler                    ah( 0);
      std::vector< int>          intVec;
      std::vector< std::string>  stringVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intVec), "vector<int> argument"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( stringVec), "vector<string> argument"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 3 -s hello -i 89 -s my,world -i 77,57"));
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
   TestControlArgs( bool exp_inversion):
      mExpectInversion( exp_inversion)
   {
   }

   void open()
   {
      ++mOpen;
   }

   void close()
   {
      ++mClose;
   }

   int getOpen() const
   {
      return mOpen;
   }
   int getClose() const
   {
      return mClose;
   }

   void assign( const std::string&, bool inverted)
   {
      if (inverted != mExpectInversion)
         throw std::logic_error( "'inverted' not set as expected");
      mExpectInversion = false;
   }

private:
   bool  mExpectInversion;
   int   mOpen = 0;
   int   mClose = 0;

}; // TestControlArgs



/// Checks handling of control characters.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( control_args)
{

   {
      Handler          ah( 0);
      int              intArg1;
      int              intArg2;
      TestControlArgs  tca( true);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( intArg1), "Integer argument 1"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "j", DEST_VAR( intArg2), "Integer argument 2"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c",
         DEST_METHOD_VALUE( TestControlArgs, assign, tca), "check")
         ->allowsInversion());
      BOOST_REQUIRE_NO_THROW( ah.addBracketHandler(
         std::bind( &TestControlArgs::open, &tca),
         std::bind( &TestControlArgs::close, &tca)));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-i 11 ( -j 13 ) ! -c 42"));
      BOOST_REQUIRE_EQUAL( tca.getOpen(), 1);
      BOOST_REQUIRE_EQUAL( tca.getClose(), 1);
   } // end scope

   {
      Handler          ah( 0);
      TestControlArgs  tca( false);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c",
         DEST_METHOD_VALUE( TestControlArgs, assign, tca), "check")
         ->allowsInversion());

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-c ! 42"),
         celma::prog_args::argument_error);
   } // end scope

   {
      Handler          ah( 0);
      TestControlArgs  tca( false);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "c",
         DEST_METHOD_VALUE( TestControlArgs, assign, tca), "check")
         ->allowsInversion());

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-i 11 ( ! -j 13 )"),
         std::invalid_argument);
   } // end scope

} // control_args



// =====  END OF test_handler_c.cpp  =====

