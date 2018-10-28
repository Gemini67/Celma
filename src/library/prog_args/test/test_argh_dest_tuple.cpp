
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
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
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;



/// Test error case that can occur with a tuple.
/// @since  0.11, 05.01.2017
BOOST_AUTO_TEST_CASE( test_tuple_errors)
{

   // not enough values for the tuple
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      const ArgString2Array  as2a( "-p 3", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   // too many values for the tuple
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      const ArgString2Array  as2a( "-p 3,4,5", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::runtime_error);
   } // end scope

   // conversion error on a value
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      const ArgString2Array  as2a( "-p 3,hello", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           std::bad_cast);
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
         "Key and value")->setPrintDefault(true));

      const ArgString2Array  as2a( "-h", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( oss_err.str().empty());
      // std::cerr << "\n" << oss_std.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Usage:\n"
         "Optional arguments:\n"
         "   -h          Prints the program usage.\n"
         "   -p,--pair   Key and value\n"
         "               Default value: <42,13>\n"
         "\n"));
   } // end scope

   // test with a tuple with two integer values
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      const ArgString2Array  as2a( "-p 3,9", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
   } // end scope

   // test with a tuple with two integer values and another list separator
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
         "Key and value")->setListSep( '-'));

      const ArgString2Array  as2a( "-p 3-9", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
   } // end scope

   // test with a tuple with an integer and a string value
   {
      Handler                        ah( Handler::hfHelpShort);
      std::tuple< int, std::string>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      const ArgString2Array  as2a( "--pair 4711,foobar", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 4711);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), "foobar");
   } // end scope

   // test with a tuple with two integer values that are passed as two separate
   // values
   {
      Handler                ah( 0);
      std::tuple< int, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value")
                                            ->setTakesMultiValue());

      const ArgString2Array  as2a( "-p 3 9", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
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

      const ArgString2Array  as2a( "-p 3,9,27", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
      BOOST_REQUIRE_EQUAL( std::get< 2>( myTuple), 27);
   } // end scope

   // test with a tuple with an integer, a string and another integer value
   {
      Handler                             ah( Handler::hfHelpShort);
      std::tuple< int, std::string, int>  myTuple;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "p,pair", DEST_VAR( myTuple),
                                              "Key and value"));

      const ArgString2Array  as2a( "--pair 4711,foobar,42", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
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

      const ArgString2Array  as2a( "--list-arg-vars --pair 4711,foobar,42 --list-arg-vars",
         nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 4711);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), "foobar");
      BOOST_REQUIRE_EQUAL( std::get< 2>( myTuple), 42);

      BOOST_REQUIRE( oss_err.str().empty());
      // std::cerr << "\n" << oss_std.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'-p,--pair' value type 'std::tuple<int,std::string,int>', destination 'myTuple', value not set.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "\n"
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'-p,--pair' value type 'std::tuple<int,std::string,int>', destination 'myTuple', value = <4711,foobar,42>.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
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

      const ArgString2Array  as2a( "-p 3 9 27", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( std::get< 0>( myTuple), 3);
      BOOST_REQUIRE_EQUAL( std::get< 1>( myTuple), 9);
      BOOST_REQUIRE_EQUAL( std::get< 2>( myTuple), 27);
   } // end scope

} // test_tuple_three



// =====  END OF test_argh_dest_tuple.cpp  =====

