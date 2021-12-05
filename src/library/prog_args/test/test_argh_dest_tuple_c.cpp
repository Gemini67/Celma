
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the handling of tuples by the module prog_args::Handler,
**    using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestTupleTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;
using celma::prog_args::SummaryOptions;
using celma::test::multilineStringCompare;



/// Test error case that can occur with a tuple.
/// @since  0.11, 05.01.2017
BOOST_AUTO_TEST_CASE( test_tuple_errors)
{

   // not possible to add a general format for a tuple
   {
      Handler                        ah( 0);
      std::tuple< int, std::string>  myTuple;

      BOOST_REQUIRE_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
         "Key and value")->addFormat( celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope

   // not possible to add a general format for a tuple
   {
      Handler                                ah( 0);
      std::tuple< int, std::string, double>  myTuple;

      BOOST_REQUIRE_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")->addFormat( celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope

   // not possible to add a general format for a tuple
   {
      Handler                             ah( 0);
      std::tuple< int, std::string, int>  myTuple;

      BOOST_REQUIRE_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")->addFormat( celma::prog_args::lowercase()),
         std::logic_error);
   } // end scope

   // try to specify a formatter for all values (index == -1).
   {
      Handler                             ah( 0);
      std::tuple< int, std::string, int>  myTuple;

      BOOST_REQUIRE_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")
         ->addFormatPos( -1, celma::prog_args::lowercase()), std::logic_error);
   } // end scope

   // try to specify a formatter for a value index that is greater than the size
   // of the tuple
   {
      Handler                             ah( 0);
      std::tuple< int, std::string, int>  myTuple;

      BOOST_REQUIRE_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")
         ->addFormatPos( 3, celma::prog_args::lowercase()), std::range_error);
   } // end scope

   // not enough values for the tuple
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-p 3"), std::runtime_error);
   } // end scope

   // too many values for the tuple
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-p 3,4,5"),
         std::runtime_error);
   } // end scope

   // conversion error on a value
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-p 3,hello"),
                           std::bad_cast);
   } // end scope

   // error when mandatory tuple argument is not used
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value")->setIsMandatory());
      BOOST_REQUIRE_THROW( evalArgumentString( ah, ""), std::runtime_error);
   } // end scope

} // test_tuple_errors



/// Test destination type tuple with two elements.
/// @since  0.11, 04.01.2017
BOOST_AUTO_TEST_CASE( test_tuple_two)
{

   // print the default values of the tuple in the usage
   {
      std::tuple< int, int>  myTuple = { 42, 13 };
      std::ostringstream     oss_std;
      std::ostringstream     oss_err;
      Handler                ah( oss_std, oss_err,
         Handler::hfHelpShort | Handler::hfUsageCont);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
         "Key and value")->setPrintDefault( true));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-h"));
      BOOST_REQUIRE( oss_err.str().empty());
      // std::cerr << "\n" << oss_std.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h          Prints the program usage.\n"
         "   -p,--pair   Key and value\n"
         "               Default value: <42, 13>\n"
         "\n"));
   } // end scope

   // test with a tuple with two integer values
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-p 3,9"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);

      using celma::common::operator |;

      std::ostringstream  std_out;
      ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key,
         std_out);

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Argument summary:\n"
         "   Value <3, 9 [std::tuple<int,int>]> set on variable 'myTuple' by argument '-p,--pair'.\n"));
   } // end scope

   // no error when tuple argument is not used
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
   } // end scope

   // test with a tuple with two integer values and another list separator
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
         "Key and value")->setListSep( '-'));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-p 3-9"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
   } // end scope

   // test with a tuple with an integer and a string value
   {
      Handler                        ah( Handler::hfHelpShort);
      std::tuple< int, std::string>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--pair 4711,foobar"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 4711);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), "foobar");

      using celma::common::operator |;

      std::ostringstream  std_out;
      ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key,
         std_out);

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Argument summary:\n"
         "   Value <4711, \"foobar\" [std::tuple<int,std::string>]> set on variable 'myTuple' by argument '-p,--pair'.\n"));
   } // end scope

   // test usage with a tuple with an integer and a string value
   {
      std::ostringstream             std_out;
      std::ostringstream             std_err;
      Handler                        ah( std_out, std_err, Handler::hfHelpShort
         | Handler::hfListArgVar | Handler::hfUsageCont);
      std::tuple< int, std::string>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
         "Key and value")->setListSep( ';')->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-h"));
      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h                Prints the program usage.\n"
         "   --list-arg-vars   Prints the list of arguments and their destination\n"
         "                     variables.\n"
         "   -p,--pair         Key and value\n"
         "\n"));
   } // end scope

   // test usage and other features with a tuple with an integer and a string
   // value
   {
      std::ostringstream             std_out;
      std::ostringstream             std_err;
      Handler                        ah( std_out, std_err, Handler::hfHelpShort
         | Handler::hfListArgVar | Handler::hfUsageCont);
      std::tuple< int, std::string>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
         "Key and value")->setListSep( ';')->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--pair 4711;foobar "
         "--list-arg-vars"));
      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-p,--pair' value type 'std::tuple<int,std::string>', destination 'myTuple', value = <4711, \"foobar\">.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
   } // end scope

   // test with a tuple with two integer values that are passed as two separate
   // values
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value")
                                            ->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-p 3 9"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
   } // end scope

   // test "list arguments and variables" with a tuple
   {
      std::ostringstream             oss;
      Handler                        ah( oss, std::cerr, Handler::hfListArgVar);
      std::tuple< int, int>          myTuple;
      std::tuple< int, std::string>  myTuple2;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value")
                                            ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s,string-pair",
         DEST_VAR( myTuple2), "Key and string value")->setListSep( '-'));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars -p 13,42"
         " -s 7-wonderful --list-arg-vars"));
      BOOST_REQUIRE( !oss.str().empty());
      // std::cerr << oss.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-p,--pair' value type 'std::tuple<int,int>', destination 'myTuple', value not set.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s,--string-pair' value type 'std::tuple<int,std::string>', destination 'myTuple2', value not set.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-p,--pair' value type 'std::tuple<int,int>', destination 'myTuple', value = <13, 42>.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s,--string-pair' value type 'std::tuple<int,std::string>', destination 'myTuple2', value = <7, \"wonderful\">.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
   } // end scope

} // test_tuple_two



/// Test destination type tuple with three elements.
/// @since  0.11, 04.01.2017
BOOST_AUTO_TEST_CASE( test_tuple_three)
{

   // test with a tuple with three integer values
   {
      Handler                     ah( 0);
      std::tuple< int, int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-p 3,9,27"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
      BOOST_REQUIRE_EQUAL( std::get< 2>( myTuple), 27);
   } // end scope

   // print the default values of a tuple with 3 integers in the usage
   {
      std::ostringstream          oss_std;
      Handler                     ah( oss_std, std::cerr, Handler::AllHelp
         | Handler::hfUsageCont);
      std::tuple< int, int, int>  myTuple = { 2, 3, 5 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")->setPrintDefault( true));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-h"));
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help     Prints the program usage.\n"
         "   --help-arg    Prints the usage for the given argument.\n"
         "   -t,--triple   Key and value\n"
         "                 Default value: <2, 3, 5>\n"
         "\n"));
   } // end scope

   // test with a tuple with an integer, a string and another integer value
   {
      Handler                             ah( Handler::hfHelpShort);
      std::tuple< int, std::string, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--pair 4711,foobar,42"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 4711);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), "foobar");
      BOOST_REQUIRE_EQUAL( std::get< 2>( myTuple), 42);
   } // end scope

   // test with a tuple with an integer, a string and another integer value
   {
      std::ostringstream                  oss_std;
      std::ostringstream                  oss_err;
      Handler                             ah( oss_std, oss_err,
         Handler::hfListArgVar | Handler::hfHelpShort | Handler::hfUsageCont);
      std::tuple< int, std::string, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
         "--pair 4711,foobar,42 --list-arg-vars"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 4711);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), "foobar");
      BOOST_REQUIRE_EQUAL( std::get< 2>( myTuple), 42);

      BOOST_REQUIRE( oss_err.str().empty());
      // std::cerr << "\n" << oss_std.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std,
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-p,--pair' value type 'std::tuple<int,std::string,int>', destination 'myTuple', value not set.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-p,--pair' value type 'std::tuple<int,std::string,int>', destination 'myTuple', value = <4711, \"foobar\", 42>.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
   } // end scope

   // test with a tuple with three integer values that are passed as separate
   // values
   {
      Handler                     ah( 0);
      std::tuple< int, int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value")
                                            ->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-p 3 9 27"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
      BOOST_REQUIRE_EQUAL( std::get< 2>( myTuple), 27);
   } // end scope

   // test "list arguments and variables" with a tuple with 3 integers
   {
      std::ostringstream          oss;
      Handler                     ah( oss, std::cerr, Handler::hfListArgVar);
      std::tuple< int, int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
                                              "Key and value")
                                            ->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
         "-t 13,42,4711 --list-arg-vars"));
      BOOST_REQUIRE( !oss.str().empty());
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-t,--triple' value type 'std::tuple<int,int,int>', destination 'myTuple', value not set.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-t,--triple' value type 'std::tuple<int,int,int>', destination 'myTuple', value = <13, 42, 4711>.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));

      using celma::common::operator |;

      std::ostringstream  std_out;
      ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key,
         std_out);

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Argument summary:\n"
         "   Value <[callable]> set on variable 'Handler::listArgVars' by argument '--list-arg-vars'.\n"
         "   Value <13, 42, 4711 [std::tuple<int,int,int>]> set on variable 'myTuple' by argument '-t,--triple'.\n"));
   } // end scope

   // print usage with a tuple with 2 integers and a string in between
   {
      std::ostringstream                  oss;
      Handler                             ah( oss, std::cerr,
         Handler::AllHelp | Handler::hfUsageCont);
      std::tuple< int, std::string, int>  myTuple = { 42, "hello world", 4711 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")->setTakesMultiValue()->setPrintDefault( true));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-h"));
      BOOST_REQUIRE( !oss.str().empty());
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help     Prints the program usage.\n"
         "   --help-arg    Prints the usage for the given argument.\n"
         "   -t,--triple   Key and value\n"
         "                 Default value: <42, \"hello world\", 4711>\n"
         "\n"));
   } // end scope

   // test "list arguments and variables" with a tuple with 2 integers and a
   // string in between
   {
      std::ostringstream                  oss;
      Handler                             ah( oss, std::cerr,
         Handler::hfListArgVar);
      std::tuple< int, std::string, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
         "-t 13,'hello world',4711 --list-arg-vars"));
      BOOST_REQUIRE( !oss.str().empty());
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-t,--triple' value type 'std::tuple<int,std::string,int>', destination 'myTuple', value not set.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-t,--triple' value type 'std::tuple<int,std::string,int>', destination 'myTuple', value = <13, \"hello world\", 4711>.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
   } // end scope

   // print usage with a tuple with an integer, a string and a double
   {
      std::ostringstream                     oss;
      Handler                                ah( oss, std::cerr,
         Handler::AllHelp | Handler::hfUsageCont);
      std::tuple< int, std::string, double>  myTuple = { 42, "hello world", 3.1415 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")->setTakesMultiValue()->setPrintDefault( true));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-h"));
      BOOST_REQUIRE( !oss.str().empty());
      // std::cerr << oss.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help     Prints the program usage.\n"
         "   --help-arg    Prints the usage for the given argument.\n"
         "   -t,--triple   Key and value\n"
         "                 Default value: <42, \"hello world\", 3.141500>\n"
         "\n"));
   } // end scope

   // test "list arguments and variables" with a tuple with an integer, a string
   // and a double
   {
      std::ostringstream                     oss;
      Handler                                ah( oss, std::cerr,
         Handler::hfListArgVar);
      std::tuple< int, std::string, double>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "t,triple", DEST_VAR( myTuple),
         "Key and value")->setTakesMultiValue());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-vars "
         "-t 13,'hello world',3.1415 --list-arg-vars"));
      BOOST_REQUIRE( !oss.str().empty());
      // std::cerr << oss.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-t,--triple' value type 'std::tuple<int,std::string,double>', destination 'myTuple', value not set.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"
         "Arguments:\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-t,--triple' value type 'std::tuple<int,std::string,double>', destination 'myTuple', value = <13, \"hello world\", 3.141500>.\n"
         "   value 'required' (2), optional, takes multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
   } // end scope

} // test_tuple_three



/// Specify a formatter for the string value in the tuple.
///
/// @since  1.32.0, 21.08.2019
BOOST_AUTO_TEST_CASE( test_tuple_format)
{

   std::tuple< int, std::string>  my_tuple;
   Handler                        ah( 0);


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( my_tuple),
      "Key and value")->setPrintDefault( true)
      ->addFormatPos( 1, celma::prog_args::lowercase()));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-p 7,SeVeN"));

   BOOST_REQUIRE_EQUAL( std::get< 0>( my_tuple), 7);
   BOOST_REQUIRE_EQUAL( std::get< 1>( my_tuple), "seven");

} // test_tuple_format



// =====  END OF test_argh_dest_tuple_c.cpp  =====

