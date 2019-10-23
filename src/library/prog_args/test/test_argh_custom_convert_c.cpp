
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "custom conversion" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Template Library includes
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerCustomConversionTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/format/to_string.hpp"
#include "celma/prog_args.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::common::operator |;
using celma::prog_args::Handler;
using celma::prog_args::SummaryOptions;
using celma::test::multilineStringCompare;


// module definitions


/// Test enum.
enum MyEnum
{
   initVal,
   meVal1,
   meVal2,
   meVal3
};



/// Helper function to convert an enum name in string format into the
/// corresponding enum.
static MyEnum string2enum( const std::string& enumText)
{
   if (enumText == "meVal1")
      return meVal1;
   if (enumText == "meVal2")
      return meVal2;
   if (enumText == "meVal3")
      return meVal3;
   return initVal;
} // string2enum



/// Conversion function called by boost::lexical_cast<>: Converts the value in
/// the string into the corresponding enum.
/// @param[in]   source  The stream to read the string value from.
/// @param[out]  me      The enum variable to store the value in.
/// @return  The stream as passed as input parameter.
/// @since  0.2, 10.04.2016
static std::istream& operator >>( std::istream& source, MyEnum& me)
{

   std::string  v;


   source >> v;
   me = string2enum( v);

   return source;
} // operator >>



/// Checks if user-supplied conversion to a user-defined data type works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( basic_conversion)
{

   Handler  ah( 0);
   MyEnum   enumedValue( initVal);


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
      "Enum")->setIsMandatory());

   auto const  as2a = make_arg_array( "-e meVal2", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( enumedValue, meVal2);

   // to improve coverage: try to convert the enum to a string
   const std::string  str( celma::format::toString( enumedValue));
   BOOST_REQUIRE_EQUAL( str, "2");

} // basic_conversion



/// Checks if user-supplied conversion to a user-defined data type wrapped
/// in a CheckAssign<> object works.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_assign_conversion)
{

   using celma::common::CheckAssign;

   using enum_check_assign = CheckAssign< MyEnum>;

   {
      Handler            ah( 0);
      enum_check_assign  enumedValue;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum"));

      auto const  as2a = make_arg_array( "-e meVal2", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( enumedValue.hasValue());
      BOOST_REQUIRE_EQUAL( enumedValue, meVal2);
   } // end scope

   // test usage
   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::AllHelp
         | Handler::hfUsageCont | Handler::hfListArgVar);
      enum_check_assign  enumedValue;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum"));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help         Prints the program usage.\n"
         "   --help-arg        Prints the usage for the given argument.\n"
         "   --list-arg-vars   Prints the list of arguments and their destination\n"
         "                     variables.\n"
         "   -e,--enum         Enum\n"
         "\n"));
   } // end scope

   // test list arguments and variables and print summary
   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::AllHelp
         | Handler::hfUsageCont | Handler::hfListArgVar);
      enum_check_assign   enumedValue;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum"));

      auto const  as2a = make_arg_array( "-e meVal2 --list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( enumedValue, meVal2);
      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h,--help' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--help-arg' calls function/method 'Prints the usage for the given argument.'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'-e,--enum' value type 'unknown', destination 'CheckAssign< enumedValue>', value = 2.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "\n"));

      using celma::common::operator |;

      std_out.str( "");
      ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key,
         std_out);

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Argument summary:\n"
         "   Value <[callable]> set on variable 'Handler::listArgVars' by argument '--list-arg-vars'.\n"
         "   Value <2 [unknown]> set on variable 'enumedValue' by argument '-e,--enum'.\n"));

   } // end scope

} // check_assign_conversion



/// Checks if user-supplied conversion to a user-defined data type wrapped
/// in a CheckAssign<> object works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_conversion)
{

   Handler               ah( 0);
   std::vector< MyEnum>  enumedValue;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
      "Enum"));

   auto const  as2a = make_arg_array( "-e meVal1,meVal3", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( !enumedValue.empty());
   BOOST_REQUIRE_EQUAL( enumedValue.size(), 2);
   BOOST_REQUIRE_EQUAL( enumedValue[ 0], meVal1);
   BOOST_REQUIRE_EQUAL( enumedValue[ 1], meVal3);

   // to improve coverage: try to convert the enum to a string
   const std::string  str( celma::format::toString( enumedValue.begin(),
      enumedValue.end()));
   BOOST_REQUIRE_EQUAL( str, "1, 3");

} // vector_conversion



/// Checks of some destination-vector specific features.
///
/// @since  1.23.0, 10.04.2019
BOOST_AUTO_TEST_CASE( vector_features)
{

   {
      Handler               ah( 0);
      std::vector< MyEnum>  enumedValue = { initVal, meVal2 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum")->setClearBeforeAssign()->setUniqueData()->setSortData());

      auto const  as2a = make_arg_array( "-e meVal1,meVal3", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !enumedValue.empty());
      BOOST_REQUIRE_EQUAL( enumedValue.size(), 2);
      BOOST_REQUIRE_EQUAL( enumedValue[ 0], meVal1);
      BOOST_REQUIRE_EQUAL( enumedValue[ 1], meVal3);
   } // end scope

   // entries must be sorted
   {
      Handler               ah( 0);
      std::vector< MyEnum>  enumedValue = { initVal, meVal2 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum")->setClearBeforeAssign()->setUniqueData()->setSortData()
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-e meVal3 meVal1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !enumedValue.empty());
      BOOST_REQUIRE_EQUAL( enumedValue.size(), 2);
      BOOST_REQUIRE_EQUAL( enumedValue[ 0], meVal1);
      BOOST_REQUIRE_EQUAL( enumedValue[ 1], meVal3);
   } // end scope

   {
      Handler               ah( 0);
      std::vector< MyEnum>  enumedValue = { initVal, meVal2 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum")->setClearBeforeAssign()->setUniqueData()->setSortData());

      auto const  as2a = make_arg_array( "-e meVal1,meVal3,meVal1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !enumedValue.empty());
      BOOST_REQUIRE_EQUAL( enumedValue.size(), 2);
      BOOST_REQUIRE_EQUAL( enumedValue[ 0], meVal1);
      BOOST_REQUIRE_EQUAL( enumedValue[ 1], meVal3);
   } // end scope

   {
      Handler               ah( 0);
      std::vector< MyEnum>  enumedValue = { initVal, meVal2 };

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum")->setClearBeforeAssign()->setUniqueData( true)->setSortData());

      auto const  as2a = make_arg_array( "-e meVal1,meVal3,meVal1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

} // vector_features



/// UsAge features with the vector of cutom enum.
/// @since  1.23.0, 10.04.2019
BOOST_AUTO_TEST_CASE( vector_usage)
{

   using celma::test::multilineStringCompare;

   {
      std::ostringstream    std_out;
      std::ostringstream    std_err;
      Handler               ah( std_out, std_err, Handler::AllHelp
         | Handler::hfUsageCont | Handler::hfListArgVar);
      std::vector< MyEnum>  enumedValue;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum")->setListSep( ';'));

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help         Prints the program usage.\n"
         "   --help-arg        Prints the usage for the given argument.\n"
         "   --list-arg-vars   Prints the list of arguments and their destination\n"
         "                     variables.\n"
         "   -e,--enum         Enum\n"
         "\n"));
   } // end scope

   {
      std::ostringstream    std_out;
      std::ostringstream    std_err;
      Handler               ah( std_out, std_err, Handler::AllHelp
         | Handler::hfUsageCont | Handler::hfListArgVar);
      std::vector< MyEnum>  enumedValue;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum")->setListSep( ';'));

      auto const  as2a = make_arg_array( "-e meVal1;meVal3 --list-arg-vars", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Arguments:\n"
         "'-h,--help' calls function/method 'Handler::usage'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--help-arg' calls function/method 'Prints the usage for the given argument.'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "'-e,--enum' value type 'std::vector<unknown>', destination vector 'enumedValue', currently 2 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
         "\n"));
   } // end scope

   {
      std::ostringstream    std_out;
      std::ostringstream    std_err;
      Handler               ah( std_out, std_err, 0);
      std::vector< MyEnum>  enumedValue;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
         "Enum")->setListSep( ';'));

      auto const  as2a = make_arg_array( "-e meVal1;meVal3", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( std_out.str().empty());

      ah.printSummary( SummaryOptions::with_type | SummaryOptions::with_key,
         std_out);

      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Argument summary:\n"
         "   Value <1, 3 [std::vector<unknown>]> set on variable 'enumedValue' by argument '-e,--enum'.\n"));
   } // end scope

} // vector_usage



// =====  END OF test_argh_custom_convert_c.cpp  =====
