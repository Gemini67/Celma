
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "print summary" in the argument handler
**    library, using the Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgPrintSummaryTest
#include <boost/test/unit_test.hpp>


// C++ Standard Library includes
#include <sstream>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args/groups.hpp"
#include "celma/prog_args.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::ArgString2Array;
using celma::common::operator |;
using celma::prog_args::Handler;
using celma::prog_args::SummaryOptions;


namespace {


/// Helper class to provide callback member functions.
/// @since  1.8.0, 11.07.2018
class TestCallbacks
{
public:
   /// Callback function without value.
   /// @since  1.8.0, 11.07.2018
   void void_method()
   {
   } // TestCallbacks::void_method

   /// Callback function with (unused) value.
   /// @since  1.8.0, 11.07.2018
   void value_method( const std::string&)
   {
   } // TestCallbacks::value_method

   /// Used to a callback as 'member function of the current object'.
   /// @param[out]  ah  The argument handler to add the argument to.
   /// @since  1.8.0, 11.07.2018
   void addVoidMember( Handler& ah)
   {
      ah.addArgument( "void-member",
         DEST_MEMBER_METHOD( TestCallbacks, void_member),
         "void method");
   } // TestCallbacks::addVoidMember

   /// Used to a callback as 'member function of the current object'.
   /// @param[out]  ah  The argument handler to add the argument to.
   /// @since  1.8.0, 11.07.2018
   void addValueMember( Handler& ah)
   {
      ah.addArgument( "value-member",
         DEST_MEMBER_METHOD_VALUE( TestCallbacks, value_member),
         "value member");
   } // TestCallbacks::addValueMember

   /// Callback member function without value.
   /// @since  1.8.0, 11.07.2018
   void void_member()
   {
   } // TestCallbacks::void_member

   /// Callback member function with (unused) value.
   /// @since  1.8.0, 11.07.2018
   void value_member( const std::string&)
   {
   } // TestCallbacks::value_member

}; // TestCallbacks


/// Flag, set when void_func() is called.
bool         void_func_called = false;
/// Flag, set when value_func() is called.
bool         value_func_called = false;
/// The value that was passed to the value function.
std::string  func_value;


/// Callback function without a value.
/// @since  1.8.0, 11.07.2018
void void_func()
{

   void_func_called = true;

} // void_func


/// Callback function with a value.
/// @param[in]  value  The value from the command line.
/// @since  1.8.0, 11.07.2018
void value_func( const std::string& value)
{

   value_func_called = true;
   func_value = value;

} // value_func


} // namespce



/// Check that we get an empty summary when no argument is used.
/// @since  1.8.0, 10.07.2018
BOOST_AUTO_TEST_CASE( no_argument_used)
{

   const std::string   empty( "Argument summary:\n"
      "   No arguments used/values set.\n");
   Handler             ah( 0);
   std::ostringstream  oss;
   int                 int1;


   ah.printSummary( oss);
   BOOST_REQUIRE_EQUAL( oss.str(), empty);
   oss.str( "");

   ah.addArgument( "f,first", DEST_VAR( int1), "first integer");

   ah.printSummary( oss);
   BOOST_REQUIRE_EQUAL( oss.str(), empty);
   oss.str( "");

   const ArgString2Array  as2a( "", nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( oss);
   BOOST_REQUIRE_EQUAL( oss.str(), empty);

} // no_argument_used



/// Start testing the summary feature with just one argument, with default
/// (minimal) content.
/// @since  1.8.0, 26.07.2018
BOOST_AUTO_TEST_CASE( one_argument_summary)
{

   const std::string   empty( "Argument summary:\n"
      "   No arguments used/values set.\n");
   Handler             ah( 0);
   std::ostringstream  oss;
   int                 int1;


   ah.addArgument( "f,first", DEST_VAR( int1), "first integer");

   ah.printSummary( oss);
   BOOST_REQUIRE_EQUAL( oss.str(), empty);
   oss.str( "");

   const ArgString2Array  as2a( "-f 34", nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( oss);
   BOOST_REQUIRE( oss.str() != empty);
   BOOST_REQUIRE_EQUAL( oss.str(),
      "Argument summary:\n"
      "   Value <34> set on variable 'int1'.\n");

} // one_argument_summary



/// Test the summary output with all the different destination types, with
/// default (minimal) content.
/// @since  1.8.0, 26.07.2018
BOOST_AUTO_TEST_CASE( summary_with_all_destination_types)
{

   Handler                         ah( 0);
   std::ostringstream              oss;
   int                             int1 = 0;
   bool                            flag1 = false;
   std::bitset< 10>                bit_set;
   std::vector< std::string>       names;
   std::vector< int>               range_dest;
   double                          dbl_value = 0.0;
   std::bitset< 10>                range_bit_set;
   TestCallbacks                   tcb;
   celma::prog_args::LevelCounter  verbose_level;

   std::tuple< int, std::string, double>  tuple_dest;


   ah.addArgument( "i,integer", DEST_VAR( int1), "numerical");
   ah.addArgument( "f,flag", DEST_VAR( flag1), "boolean flag");
   ah.addArgument( "b,bitset", DEST_VAR( bit_set), "bitset");
   ah.addArgument( "n,names", DEST_VAR( names), "list of names");
   ah.addArgument( "r,range", DEST_RANGE( range_dest, int, std::vector),
      "range");
   ah.addArgument( "d,double", DEST_VAR_VALUE( dbl_value, 3.1415), "double");
   ah.addArgument( "range-bitset", DEST_RANGE_BITSET( range_bit_set, 10),
      "range bitset");
   ah.addArgument( "t,tuple", DEST_VAR( tuple_dest), "tuple");
   ah.addArgument( "void-func", DEST_FUNCTION( void_func), "void function");
   ah.addArgument( "value-func", DEST_FUNCTION_VALUE( value_func),
      "value function");
   ah.addArgument( "void-method", DEST_METHOD( TestCallbacks, void_method, tcb),
      "void method");
   ah.addArgument( "value-method", DEST_METHOD_VALUE( TestCallbacks, value_method, tcb),
      "value method");
   ah.addArgument( "v,verbose_level", DEST_VAR( verbose_level), "verbose level");

   tcb.addVoidMember( ah);
   tcb.addValueMember( ah);

   const ArgString2Array  as2a( "-i 42 -f -b 2,3,4 --names peter,paul,mary "
      "-r 2,5-7 -d --range-bitset 3,5,7 --void-func --value-func=some_value "
      "--void-method --value-method another_value -t 28,unbelievable,12.75 "
      "--void-member --value-member=last_value -vv",
      nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <42> set on variable 'int1'.\n"
      "   Value <true> set on variable 'flag1'.\n"
      "   Value <0000011100> set on variable 'bit_set'.\n"
      "   Value <\"peter\", \"paul\", \"mary\"> set on variable 'names'.\n"
      "   Value <2, 5, 6, 7> set on variable 'range_dest'.\n"
      "   Value <3.141500> set on variable 'dbl_value'.\n"
      "   Value <0010101000> set on variable 'range_bit_set'.\n"
      "   Value <28, \"unbelievable\", 12.750000> set on variable 'tuple_dest'.\n"
      "   Value <[callable]> set on variable 'void_func'.\n"
      "   Value <[callable(value)]> set on variable 'value_func'.\n"
      "   Value <[callable]> set on variable 'TestCallbacks::void_method'.\n"
      "   Value <[callable(value)]> set on variable 'TestCallbacks::value_method'.\n"
      "   Value <2> set on variable 'verbose_level'.\n"
      "   Value <[callable]> set on variable 'TestCallbacks::void_member'.\n"
      "   Value <[callable(value)]> set on variable 'TestCallbacks::value_member'.\n"
   ));

} // summary_with_all_destination_types



/// Test the summary output for argument groups, with default (minimal)
/// content.
/// @since  1.8.0, 26.07.2018
BOOST_AUTO_TEST_CASE( groups_summary)
{

   using celma::prog_args::Groups;

   auto                ah_input = Groups::instance( 0).getArgHandler( "input");
   auto                ah_output = Groups::instance( 0).getArgHandler( "output");
   std::string         input_name;
   std::string         output_name;
   std::ostringstream  oss;

   ah_input->addArgument( "input-name", DEST_VAR( input_name), "input name");
   ah_output->addArgument( "output-name", DEST_VAR( output_name), "output name");

   const ArgString2Array  as2a( "--input-name source --output-name destination",
      nullptr);
   BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));

   Groups::instance().printSummary( oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <\"source\"> set on variable 'input_name'.\n"
      "   Value <\"destination\"> set on variable 'output_name'.\n"
   ));

} // groups_summary



/// Test the summary output for an argument handler ith sub-groups, with
/// default (minimal) content.
/// @since  1.8.0, 26.07.2018
BOOST_AUTO_TEST_CASE( subgroups_summary)
{

   Handler             ah( 0);
   Handler             ah_input( ah, 0);
   Handler             ah_output( ah, 0);
   std::string         input_filename;
   std::string         input_queuename;
   std::string         output_filename;
   std::string         output_queuename;
   std::ostringstream  oss;


   ah_input.addArgument( "f,file", DEST_VAR( input_filename), "input file name");
   ah_input.addArgument( "q,queue", DEST_VAR( input_queuename), "input queue name");

   ah_output.addArgument( "f,file", DEST_VAR( output_filename), "output file name");
   ah_output.addArgument( "q,queue", DEST_VAR( output_queuename), "output queue name");

   ah.addArgument( "i,input", ah_input, "input parameters");
   ah.addArgument( "o,output", ah_output, "output parameters");

   const ArgString2Array  as2a( "-if input_file_name --output --queue output_queue_name",
      nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <\"input_file_name\"> set on variable 'input_filename'.\n"
      "   Value <\"output_queue_name\"> set on variable 'output_queuename'.\n"
   ));

} // subgroups_summary



/// Start testing the summary feature with just one argument, with type
/// information.
/// @since  1.8.0, 27.07.2018
BOOST_AUTO_TEST_CASE( one_argument_summary_with_type)
{

   const std::string   empty( "Argument summary:\n"
      "   No arguments used/values set.\n");
   Handler             ah( 0);
   std::ostringstream  oss;
   int                 int1;


   ah.addArgument( "f,first", DEST_VAR( int1), "first integer");

   ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key, oss);
   BOOST_REQUIRE_EQUAL( oss.str(), empty);
   oss.str( "");

   const ArgString2Array  as2a( "-f 34", nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_type, oss);
   BOOST_REQUIRE( oss.str() != empty);
   BOOST_REQUIRE_EQUAL( oss.str(),
      "Argument summary:\n"
      "   Value <34 [int]> set on variable 'int1'.\n");

} // one_argument_summary_with_type



/// Test the summary output with all the different destination types, with type
/// inormation.
/// @since  1.8.0, 27.07.2018
BOOST_AUTO_TEST_CASE( summary_with_all_destination_types_with_type)
{

   Handler                         ah( 0);
   std::ostringstream              oss;
   int                             int1 = 0;
   bool                            flag1 = false;
   std::bitset< 10>                bit_set;
   std::vector< std::string>       names;
   std::vector< int>               range_dest;
   double                          dbl_value = 0.0;
   std::bitset< 10>                range_bit_set;
   TestCallbacks                   tcb;
   celma::prog_args::LevelCounter  verbose_level;

   std::tuple< int, std::string, double>  tuple_dest;


   ah.addArgument( "i,integer", DEST_VAR( int1), "numerical");
   ah.addArgument( "f,flag", DEST_VAR( flag1), "boolean flag");
   ah.addArgument( "b,bitset", DEST_VAR( bit_set), "bitset");
   ah.addArgument( "n,names", DEST_VAR( names), "list of names");
   ah.addArgument( "r,range", DEST_RANGE( range_dest, int, std::vector),
      "range");
   ah.addArgument( "d,double", DEST_VAR_VALUE( dbl_value, 3.1415), "double");
   ah.addArgument( "range-bitset", DEST_RANGE_BITSET( range_bit_set, 10),
      "range bitset");
   ah.addArgument( "t,tuple", DEST_VAR( tuple_dest), "tuple");
   ah.addArgument( "void-func", DEST_FUNCTION( void_func), "void function");
   ah.addArgument( "value-func", DEST_FUNCTION_VALUE( value_func),
      "value function");
   ah.addArgument( "void-method", DEST_METHOD( TestCallbacks, void_method, tcb),
      "void method");
   ah.addArgument( "value-method", DEST_METHOD_VALUE( TestCallbacks, value_method, tcb),
      "value method");
   ah.addArgument( "v,verbose_level", DEST_VAR( verbose_level), "verbose level");

   tcb.addVoidMember( ah);
   tcb.addValueMember( ah);

   const ArgString2Array  as2a( "-i 42 -f -b 2,3,4 --names peter,paul,mary "
      "-r 2,5-7 -d --range-bitset 3,5,7 --void-func --value-func=some_value "
      "--void-method --value-method another_value -t 28,unbelievable,12.75 "
      "--void-member --value-member=last_value -v --verbose_level",
      nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_type, oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <42 [int]> set on variable 'int1'.\n"
      "   Value <true [bool]> set on variable 'flag1'.\n"
      "   Value <0000011100 [std::bitset<10>]> set on variable 'bit_set'.\n"
      "   Value <\"peter\", \"paul\", \"mary\" [std::vector<std::string>]> set on variable 'names'.\n"
      "   Value <2, 5, 6, 7 [std::vector<int>]> set on variable 'range_dest'.\n"
      "   Value <3.141500 [double]> set on variable 'dbl_value'.\n"
      "   Value <0010101000 [std::bitset<10>]> set on variable 'range_bit_set'.\n"
      "   Value <28, \"unbelievable\", 12.750000 [std::tuple<int,std::string,double>]> set on variable 'tuple_dest'.\n"
      "   Value <[callable]> set on variable 'void_func'.\n"
      "   Value <[callable(value)]> set on variable 'value_func'.\n"
      "   Value <[callable]> set on variable 'TestCallbacks::void_method'.\n"
      "   Value <[callable(value)]> set on variable 'TestCallbacks::value_method'.\n"
      "   Value <2 [LevelCounter]> set on variable 'verbose_level'.\n"
      "   Value <[callable]> set on variable 'TestCallbacks::void_member'.\n"
      "   Value <[callable(value)]> set on variable 'TestCallbacks::value_member'.\n"
   ));

} // summary_with_all_destination_types_with_type



/// Test the summary output for argument groups, with type information.
/// @since  1.8.0, 27.07.2018
BOOST_AUTO_TEST_CASE( groups_summary_with_type)
{

   using celma::prog_args::Groups;

   Groups::instance().removeAllArgHandler();

   auto                ah_input = Groups::instance( 0).getArgHandler( "input");
   auto                ah_output = Groups::instance( 0).getArgHandler( "output");
   std::string         input_name;
   std::string         output_name;
   std::ostringstream  oss;

   ah_input->addArgument( "input-name", DEST_VAR( input_name), "input name");
   ah_output->addArgument( "output-name", DEST_VAR( output_name), "output name");

   const ArgString2Array  as2a( "--input-name source --output-name destination",
      nullptr);
   BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));

   Groups::instance().printSummary( SummaryOptions::with_type, oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <\"source\" [std::string]> set on variable 'input_name'.\n"
      "   Value <\"destination\" [std::string]> set on variable 'output_name'.\n"
   ));

} // groups_summary_with_type



/// Test the summary output for an argument handler ith sub-groups, with type
/// information.
/// @since  1.8.0, 27.07.2018
BOOST_AUTO_TEST_CASE( subgroups_summary_with_type)
{

   Handler             ah( 0);
   Handler             ah_input( ah, 0);
   Handler             ah_output( ah, 0);
   std::string         input_filename;
   std::string         input_queuename;
   std::string         output_filename;
   std::string         output_queuename;
   std::ostringstream  oss;


   ah_input.addArgument( "f,file", DEST_VAR( input_filename), "input file name");
   ah_input.addArgument( "q,queue", DEST_VAR( input_queuename), "input queue name");

   ah_output.addArgument( "f,file", DEST_VAR( output_filename), "output file name");
   ah_output.addArgument( "q,queue", DEST_VAR( output_queuename), "output queue name");

   ah.addArgument( "i,input", ah_input, "input parameters");
   ah.addArgument( "o,output", ah_output, "output parameters");

   const ArgString2Array  as2a( "-if input_file_name --output --queue output_queue_name",
      nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_type, oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <\"input_file_name\" [std::string]> set on variable 'input_filename'.\n"
      "   Value <\"output_queue_name\" [std::string]> set on variable 'output_queuename'.\n"
   ));

} // subgroups_summary_with_type



/// Start testing the summary feature with just one argument, including the
/// argument key.
/// @since  1.8.0, 27.07.2018
BOOST_AUTO_TEST_CASE( one_argument_summary_with_key)
{

   const std::string   empty( "Argument summary:\n"
      "   No arguments used/values set.\n");
   Handler             ah( 0);
   std::ostringstream  oss;
   int                 int1;


   ah.addArgument( "f,first", DEST_VAR( int1), "first integer");

   ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key, oss);
   BOOST_REQUIRE_EQUAL( oss.str(), empty);
   oss.str( "");

   const ArgString2Array  as2a( "-f 34", nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_key, oss);
   BOOST_REQUIRE( oss.str() != empty);
   BOOST_REQUIRE_EQUAL( oss.str(),
      "Argument summary:\n"
      "   Value <34> set on variable 'int1' by argument '-f,--first'.\n");

} // one_argument_summary_with_key



/// Test the summary output with all the different destination types, including
/// the argument key.
/// @since  1.8.0, 27.07.2018
BOOST_AUTO_TEST_CASE( summary_with_all_destination_types_with_key)
{

   Handler                         ah( 0);
   std::ostringstream              oss;
   int                             int1 = 0;
   bool                            flag1 = false;
   std::bitset< 10>                bit_set;
   std::vector< std::string>       names;
   std::vector< int>               range_dest;
   double                          dbl_value = 0.0;
   std::bitset< 10>                range_bit_set;
   TestCallbacks                   tcb;
   celma::prog_args::LevelCounter  verbose_level;

   std::tuple< int, std::string, double>  tuple_dest;


   ah.addArgument( "i,integer", DEST_VAR( int1), "numerical");
   ah.addArgument( "f,flag", DEST_VAR( flag1), "boolean flag");
   ah.addArgument( "b,bitset", DEST_VAR( bit_set), "bitset");
   ah.addArgument( "n,names", DEST_VAR( names), "list of names");
   ah.addArgument( "r,range", DEST_RANGE( range_dest, int, std::vector),
      "range");
   ah.addArgument( "d,double", DEST_VAR_VALUE( dbl_value, 3.1415), "double");
   ah.addArgument( "range-bitset", DEST_RANGE_BITSET( range_bit_set, 10),
      "range bitset");
   ah.addArgument( "t,tuple", DEST_VAR( tuple_dest), "tuple");
   ah.addArgument( "void-func", DEST_FUNCTION( void_func), "void function");
   ah.addArgument( "value-func", DEST_FUNCTION_VALUE( value_func),
      "value function");
   ah.addArgument( "void-method", DEST_METHOD( TestCallbacks, void_method, tcb),
      "void method");
   ah.addArgument( "value-method", DEST_METHOD_VALUE( TestCallbacks, value_method, tcb),
      "value method");
   ah.addArgument( "v,verbose_level", DEST_VAR( verbose_level), "verbose level");

   tcb.addVoidMember( ah);
   tcb.addValueMember( ah);

   const ArgString2Array  as2a( "-i 42 -f -b 2,3,4 --names peter,paul,mary "
      "-r 2,5-7 -d --range-bitset 3,5,7 --void-func --value-func=some_value "
      "--void-method --value-method another_value -t 28,unbelievable,12.75 "
      "--void-member --value-member=last_value -vv",
      nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_key, oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <42> set on variable 'int1' by argument '-i,--integer'.\n"
      "   Value <true> set on variable 'flag1' by argument '-f,--flag'.\n"
      "   Value <0000011100> set on variable 'bit_set' by argument '-b,--bitset'.\n"
      "   Value <\"peter\", \"paul\", \"mary\"> set on variable 'names' by argument '-n,--names'.\n"
      "   Value <2, 5, 6, 7> set on variable 'range_dest' by argument '-r,--range'.\n"
      "   Value <3.141500> set on variable 'dbl_value' by argument '-d,--double'.\n"
      "   Value <0010101000> set on variable 'range_bit_set' by argument '--range-bitset'.\n"
      "   Value <28, \"unbelievable\", 12.750000> set on variable 'tuple_dest' by argument '-t,--tuple'.\n"
      "   Value <[callable]> set on variable 'void_func' by argument '--void-func'.\n"
      "   Value <[callable(value)]> set on variable 'value_func' by argument '--value-func'.\n"
      "   Value <[callable]> set on variable 'TestCallbacks::void_method' by argument '--void-method'.\n"
      "   Value <[callable(value)]> set on variable 'TestCallbacks::value_method' by argument '--value-method'.\n"
      "   Value <2> set on variable 'verbose_level' by argument '-v,--verbose_level'.\n"
      "   Value <[callable]> set on variable 'TestCallbacks::void_member' by argument '--void-member'.\n"
      "   Value <[callable(value)]> set on variable 'TestCallbacks::value_member' by argument '--value-member'.\n"
   ));

} // summary_with_all_destination_types_with_key



/// Test the summary output for argument groups, including the argument key.
/// @since  1.8.0, 27.07.2018
BOOST_AUTO_TEST_CASE( groups_summary_with_key)
{

   using celma::prog_args::Groups;

   Groups::instance().removeAllArgHandler();

   auto                ah_input = Groups::instance( 0).getArgHandler( "input");
   auto                ah_output = Groups::instance( 0).getArgHandler( "output");
   std::string         input_name;
   std::string         output_name;
   std::ostringstream  oss;

   ah_input->addArgument( "input-name", DEST_VAR( input_name), "input name");
   ah_output->addArgument( "output-name", DEST_VAR( output_name), "output name");

   const ArgString2Array  as2a( "--input-name source --output-name destination",
      nullptr);
   BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));

   Groups::instance().printSummary( SummaryOptions::with_key, oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <\"source\"> set on variable 'input_name' by argument '--input-name'.\n"
      "   Value <\"destination\"> set on variable 'output_name' by argument '--output-name'.\n"
   ));

} // groups_summary_with_key



/// Test the summary output for an argument handler ith sub-groups, including
/// the argument key
/// @since  1.8.0, 27.07.2018
BOOST_AUTO_TEST_CASE( subgroups_summary_with_key)
{

   Handler             ah( 0);
   Handler             ah_input( ah, 0);
   Handler             ah_output( ah, 0);
   std::string         input_filename;
   std::string         input_queuename;
   std::string         output_filename;
   std::string         output_queuename;
   std::ostringstream  oss;


   ah_input.addArgument( "f,file", DEST_VAR( input_filename), "input file name");
   ah_input.addArgument( "q,queue", DEST_VAR( input_queuename), "input queue name");

   ah_output.addArgument( "f,file", DEST_VAR( output_filename), "output file name");
   ah_output.addArgument( "q,queue", DEST_VAR( output_queuename), "output queue name");

   ah.addArgument( "i,input", ah_input, "input parameters");
   ah.addArgument( "o,output", ah_output, "output parameters");

   const ArgString2Array  as2a( "-if input_file_name --output --queue output_queue_name",
      nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_key, oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <\"input_file_name\"> set on variable 'input_filename' by argument '-i,--input'/'-f,--file'.\n"
      "   Value <\"output_queue_name\"> set on variable 'output_queuename' by argument '-o,--output'/'-q,--queue'.\n"
   ));

} // subgroups_summary_with_key



/// Start testing the full summary feature with just one argument.
/// @since  1.8.0, 04.07.2018
BOOST_AUTO_TEST_CASE( one_argument_summary_full)
{

   const std::string   empty( "Argument summary:\n"
      "   No arguments used/values set.\n");
   Handler             ah( 0);
   std::ostringstream  oss;
   int                 int1;


   ah.addArgument( "f,first", DEST_VAR( int1), "first integer");

   ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key, oss);
   BOOST_REQUIRE_EQUAL( oss.str(), empty);
   oss.str( "");

   const ArgString2Array  as2a( "-f 34", nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key, oss);
   BOOST_REQUIRE( oss.str() != empty);
   BOOST_REQUIRE_EQUAL( oss.str(),
      "Argument summary:\n"
      "   Value <34 [int]> set on variable 'int1' by argument '-f,--first'.\n");

} // one_argument_summary_full



/// Test the full summary output with all the different destination types.
/// @since  1.8.0, 10.07.2018
BOOST_AUTO_TEST_CASE( summary_with_all_destination_types_full)
{

   Handler                         ah( 0);
   std::ostringstream              oss;
   int                             int1 = 0;
   bool                            flag1 = false;
   std::bitset< 10>                bit_set;
   std::vector< std::string>       names;
   std::vector< int>               range_dest;
   double                          dbl_value = 0.0;
   std::bitset< 10>                range_bit_set;
   TestCallbacks                   tcb;
   celma::prog_args::LevelCounter  verbose_level;

   std::tuple< int, std::string, double>  tuple_dest;


   ah.addArgument( "i,integer", DEST_VAR( int1), "numerical");
   ah.addArgument( "f,flag", DEST_VAR( flag1), "boolean flag");
   ah.addArgument( "b,bitset", DEST_VAR( bit_set), "bitset");
   ah.addArgument( "n,names", DEST_VAR( names), "list of names");
   ah.addArgument( "r,range", DEST_RANGE( range_dest, int, std::vector),
      "range");
   ah.addArgument( "d,double", DEST_VAR_VALUE( dbl_value, 3.1415), "double");
   ah.addArgument( "range-bitset", DEST_RANGE_BITSET( range_bit_set, 10),
      "range bitset");
   ah.addArgument( "t,tuple", DEST_VAR( tuple_dest), "tuple");
   ah.addArgument( "void-func", DEST_FUNCTION( void_func), "void function");
   ah.addArgument( "value-func", DEST_FUNCTION_VALUE( value_func),
      "value function");
   ah.addArgument( "void-method", DEST_METHOD( TestCallbacks, void_method, tcb),
      "void method");
   ah.addArgument( "value-method", DEST_METHOD_VALUE( TestCallbacks, value_method, tcb),
      "value method");
   ah.addArgument( "v,verbose_level", DEST_VAR( verbose_level), "verbose level");

   tcb.addVoidMember( ah);
   tcb.addValueMember( ah);

   const ArgString2Array  as2a( "-i 42 -f -b 2,3,4 --names peter,paul,mary "
      "-r 2,5-7 -d --range-bitset 3,5,7 --void-func --value-func=some_value "
      "--void-method --value-method another_value -t 28,unbelievable,12.75 "
      "--void-member --value-member=last_value --verbose_level --verbose_level",
      nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key, oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <42 [int]> set on variable 'int1' by argument '-i,--integer'.\n"
      "   Value <true [bool]> set on variable 'flag1' by argument '-f,--flag'.\n"
      "   Value <0000011100 [std::bitset<10>]> set on variable 'bit_set' by argument '-b,--bitset'.\n"
      "   Value <\"peter\", \"paul\", \"mary\" [std::vector<std::string>]> set on variable 'names' by argument '-n,--names'.\n"
      "   Value <2, 5, 6, 7 [std::vector<int>]> set on variable 'range_dest' by argument '-r,--range'.\n"
      "   Value <3.141500 [double]> set on variable 'dbl_value' by argument '-d,--double'.\n"
      "   Value <0010101000 [std::bitset<10>]> set on variable 'range_bit_set' by argument '--range-bitset'.\n"
      "   Value <28, \"unbelievable\", 12.750000 [std::tuple<int,std::string,double>]> set on variable 'tuple_dest' by argument '-t,--tuple'.\n"
      "   Value <[callable]> set on variable 'void_func' by argument '--void-func'.\n"
      "   Value <[callable(value)]> set on variable 'value_func' by argument '--value-func'.\n"
      "   Value <[callable]> set on variable 'TestCallbacks::void_method' by argument '--void-method'.\n"
      "   Value <[callable(value)]> set on variable 'TestCallbacks::value_method' by argument '--value-method'.\n"
      "   Value <2 [LevelCounter]> set on variable 'verbose_level' by argument '-v,--verbose_level'.\n"
      "   Value <[callable]> set on variable 'TestCallbacks::void_member' by argument '--void-member'.\n"
      "   Value <[callable(value)]> set on variable 'TestCallbacks::value_member' by argument '--value-member'.\n"
   ));

} // summary_with_all_destination_types_full



/// Test the full summary output for argument groups.
/// @since  1.8.0, 11.07.2018
BOOST_AUTO_TEST_CASE( groups_summary_full)
{

   using celma::prog_args::Groups;

   Groups::instance().removeAllArgHandler();

   auto                ah_input = Groups::instance( 0).getArgHandler( "input");
   auto                ah_output = Groups::instance( 0).getArgHandler( "output");
   std::string         input_name;
   std::string         output_name;
   std::ostringstream  oss;

   ah_input->addArgument( "input-name", DEST_VAR( input_name), "input name");
   ah_output->addArgument( "output-name", DEST_VAR( output_name), "output name");

   const ArgString2Array  as2a( "--input-name source --output-name destination",
      nullptr);
   BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));

   Groups::instance().printSummary(
     SummaryOptions::with_type | SummaryOptions::with_key,
     oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <\"source\" [std::string]> set on variable 'input_name' by argument '--input-name'.\n"
      "   Value <\"destination\" [std::string]> set on variable 'output_name' by argument '--output-name'.\n"
   ));

} // groups_summary_full



/// Test the full summary output for an argument handler ith sub-groups.
/// @since  1.8.0, 12.07.2018
BOOST_AUTO_TEST_CASE( subgroups_summary_full)
{

   Handler             ah( 0);
   Handler             ah_input( ah, 0);
   Handler             ah_output( ah, 0);
   std::string         input_filename;
   std::string         input_queuename;
   std::string         output_filename;
   std::string         output_queuename;
   std::ostringstream  oss;


   ah_input.addArgument( "f,file", DEST_VAR( input_filename), "input file name");
   ah_input.addArgument( "q,queue", DEST_VAR( input_queuename), "input queue name");

   ah_output.addArgument( "f,file", DEST_VAR( output_filename), "output file name");
   ah_output.addArgument( "q,queue", DEST_VAR( output_queuename), "output queue name");

   ah.addArgument( "i,input", ah_input, "input parameters");
   ah.addArgument( "o,output", ah_output, "output parameters");

   const ArgString2Array  as2a( "-if input_file_name --output --queue output_queue_name",
      nullptr);
   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key, oss);
   BOOST_REQUIRE( !oss.str().empty());
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Argument summary:\n"
      "   Value <\"input_file_name\" [std::string]> set on variable 'input_filename' by argument '-i,--input'/'-f,--file'.\n"
      "   Value <\"output_queue_name\" [std::string]> set on variable 'output_queuename' by argument '-o,--output'/'-q,--queue'.\n"
   ));

} // subgroups_summary_full



// =====  END OF test_argh_summary.cpp  =====

