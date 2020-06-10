
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "destination pair" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ArgHOutputStreams
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;
using celma::test::multilineStringCompare;
using std::ostringstream;



/// Specify a destination of type pair with a boolean flag as first part of the
/// pair.
/// @since
///    1.5.0, 25.06.2018
BOOST_AUTO_TEST_CASE( destination_bool)
{

   // check output in usage
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out, Handler::hfHelpShort | Handler::hfUsageCont);
      bool            dest_flag = false;
      bool            second_flag = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f",
         DEST_PAIR( dest_flag, second_flag, true), "two flags"));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -f   two flags\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // check extended parameter properties
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont | Handler::hfListArgVar);
      bool            dest_flag = false;
      bool            second_flag = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f",
         DEST_PAIR( dest_flag, second_flag, true), "two flags"));

      auto const  as2a = make_arg_array( "--list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-f' store first value with type 'bool' in 'dest_flag', second value with type 'bool' in 'second_flag'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // finally: set the value
   {
      Handler  ah( 0);
      bool     dest_flag = false;
      bool     second_flag = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f",
         DEST_PAIR( dest_flag, second_flag, true), "two flags"));

      auto const  as2a = make_arg_array( "-f", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( dest_flag);
      BOOST_REQUIRE( second_flag);
   } // end scope

   // flag with reverse logic
   {
      Handler  ah( 0);
      bool     dest_flag = true;
      bool     second_flag = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "f",
         DEST_PAIR( dest_flag, second_flag, true), "two flags"));

      auto const  as2a = make_arg_array( "-f", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !dest_flag);
      BOOST_REQUIRE( second_flag);
   } // end scope

} // destination_bool



/// Specify a destination of type pair with an integer variable as first part of
/// the pair.
/// @since
///    1.5.0, 25.06.2018
BOOST_AUTO_TEST_CASE( destination_int)
{

   // check output in usage
   {
      ostringstream  std_out;
      ostringstream  err_out;
      Handler        ah( std_out,
         err_out, Handler::hfHelpShort | Handler::hfUsageCont);
      int            dest_int = 0;
      std::string    second_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i",
         DEST_PAIR( dest_int, second_string, std::string( "int set")), "int and string"));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -i   int and string\n"
         "        Default value: 0\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // check output in usage with suppressed default value
   {
      ostringstream  std_out;
      ostringstream  err_out;
      Handler        ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont);
      int            dest_int = 0;
      std::string    second_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i",
         DEST_PAIR( dest_int, second_string, std::string( "int set")),
         "int and string")->setPrintDefault( false));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -i   int and string\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // check extended parameter properties
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont | Handler::hfListArgVar);
      int             dest_int = 0;
      std::string     second_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i",
         DEST_PAIR( dest_int, second_string, std::string( "int set")),
         "int and string"));

      auto const  as2a = make_arg_array( "--list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-i' store first value with type 'int' in 'dest_int', second value with type 'std::string' in 'second_string'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, no formats.\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // finally: set the value
   {
      Handler      ah( 0);
      int          dest_int = 0;
      std::string  second_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i",
         DEST_PAIR( dest_int, second_string, std::string( "int set")),
         "int and string"));

      auto const  as2a = make_arg_array( "-i 25", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( dest_int, 25);
      BOOST_REQUIRE_EQUAL( second_string, "int set");
   } // end scope

   // set a negative value
   {
      Handler      ah( 0);
      int          dest_int = 0;
      std::string  second_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i",
         DEST_PAIR( dest_int, second_string, std::string( "int set")),
         "int and string"));

      auto const  as2a = make_arg_array( "-i -- -25", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( dest_int, -25);
      BOOST_REQUIRE_EQUAL( second_string, "int set");
   } // end scope

} // destination_int



/// Specify a destination of type pair with a string variable as first part of
/// the pair.
/// @since
///    1.5.0, 25.06.2018
BOOST_AUTO_TEST_CASE( destination_string)
{

   // check output in usage
   {
      ostringstream  std_out;
      ostringstream  err_out;
      Handler        ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont);
      std::string    dest_string;
      int            second_int = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s",
         DEST_PAIR( dest_string, second_int, 42), "string and int"));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -s   string and int\n"
         "        Default value: \"\"\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // check output in usage with suppressed default value
   {
      ostringstream  std_out;
      ostringstream  err_out;
      Handler        ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont);
      std::string    dest_string;
      int            second_int = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s",
         DEST_PAIR( dest_string, second_int, 42), "string and int")
         ->setPrintDefault( false));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -s   string and int\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // check extended parameter properties
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont | Handler::hfListArgVar);
      std::string     dest_string;
      int             second_int = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s",
         DEST_PAIR( dest_string, second_int, 42), "string and int"));

      auto const  as2a = make_arg_array( "--list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-s' store first value with type 'std::string' in 'dest_string', second value with type 'int' in 'second_int'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, no formats.\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // finally: set the value
   {
      Handler      ah( 0);
      std::string  dest_string;
      int          second_int = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s",
         DEST_PAIR( dest_string, second_int, 42), "string and int"));

      auto const  as2a = make_arg_array( "-s 'hello world'", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( dest_string, "hello world");
      BOOST_REQUIRE_EQUAL( second_int, 42);
   } // end scope

} // destination_string



/// Specify a destination of type pair with a vector of ints variable as first
/// part of the pair.
/// @since
///    1.5.0, 25.06.2018
BOOST_AUTO_TEST_CASE( destination_vector)
{

   // check output in usage
   // default value is never printed for vector
   {
      ostringstream      std_out;
      ostringstream      err_out;
      Handler            ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont);
      std::vector< int>  dest_vector;
      std::string        second_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_PAIR( dest_vector, second_string, std::string( "vec set")),
         "vector and string"));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -v   vector and string\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // check extended parameter properties
   {
      ostringstream      std_out;
      ostringstream      err_out;
      Handler            ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont | Handler::hfListArgVar);
      std::vector< int>  dest_vector;
      std::string        second_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_PAIR( dest_vector, second_string, std::string( "vec set")),
         "vector and string"));

      auto const  as2a = make_arg_array( "--list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-v' store first value with type 'std::vector<int>' in 'dest_vector', second value with type 'std::string' in 'second_string'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // finally: set the value
   {
      Handler            ah( 0);
      std::vector< int>  dest_vector;
      std::string        second_string;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_PAIR( dest_vector, second_string, std::string( "vec set")),
         "vector and string"));

      auto const  as2a = make_arg_array( "-v 2,3,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( dest_vector.size(), 3);
      BOOST_REQUIRE_EQUAL( second_string, "vec set");
   } // end scope

   // use special features of destination vector
   {
      Handler            ah( 0);
      std::vector< int>  dest_vector;
      std::string        second_string;

      dest_vector.push_back( 5);
      dest_vector.push_back( 12);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v",
         DEST_PAIR( dest_vector, second_string, std::string( "vec set")),
         "vector and string")->setListSep( '-')->setClearBeforeAssign()
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-v 2-4-6 10-15-20", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( dest_vector.size(), 6);
      BOOST_REQUIRE_EQUAL( second_string, "vec set");
   } // end scope

} // destination_vector



/// Specify a destination of type pair with a bitset variable as first part of
/// the pair.
/// @since
///    1.5.0, 26.06.2018
BOOST_AUTO_TEST_CASE( destination_bitset)
{

   // check output in usage
   {
      ostringstream     std_out;
      ostringstream     err_out;
      Handler           ah( std_out, err_out, Handler::hfHelpShort | Handler::hfUsageCont);
      std::bitset< 10>  dest_bitset;
      int               second_int = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b",
         DEST_PAIR( dest_bitset, second_int, 42), "bitset and int"));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -b   bitset and int\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // check extended parameter properties
   {
      ostringstream     std_out;
      ostringstream     err_out;
      Handler           ah( std_out, err_out,
         Handler::hfHelpShort | Handler::hfUsageCont | Handler::hfListArgVar);
      std::bitset< 10>  dest_bitset;
      int               second_int = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b",
         DEST_PAIR( dest_bitset, second_int, 42), "bitset and int"));

      auto const  as2a = make_arg_array( "--list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-b' store first value with type 'std::bitset<10>' in 'dest_bitset', second value with type 'int' in 'second_int'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // finally: set the value
   {
      Handler           ah( 0);
      std::bitset< 10>  dest_bitset;
      int               second_int = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b",
         DEST_PAIR( dest_bitset, second_int, 42), "bitset and int"));

      auto const  as2a = make_arg_array( "-b 2,4,8'", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( dest_bitset.count(), 3);
      BOOST_REQUIRE_EQUAL( second_int, 42);
   } // end scope

   // finally: set the value with extended bitset features
   {
      Handler           ah( 0);
      std::bitset< 10>  dest_bitset;
      int               second_int = 0;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b",
         DEST_PAIR( dest_bitset, second_int, 42), "bitset and int")
         ->setListSep( '-')->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-b 2-4-8'", nullptr);

      dest_bitset[ 3] = true;
      dest_bitset[ 7] = true;

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( dest_bitset.count(), 3);
      BOOST_REQUIRE_EQUAL( second_int, 42);
   } // end scope

} // destination_bitset



// =====  END OF test_argh_dest_pair_c.cpp  =====
