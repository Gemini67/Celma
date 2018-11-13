
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
**    Test program for the feature "custom conversion" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Template Library includes
#include <iostream>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerCustomConversionTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;


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
// cppcheck-suppress unusedFunction
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

   const ArgString2Array  as2a( "-e meVal2", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( enumedValue, meVal2);

} // basic_conversion



/// Checks if user-supplied conversion to a user-defined data type wrapped
/// in a CheckAssign<> object works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_assign_conversion)
{

   Handler                              ah( 0);
   celma::common::CheckAssign< MyEnum>  enumedValue( initVal);


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue),
      "Enum"));

   const ArgString2Array  as2a( "-e meVal2", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( enumedValue.hasValue());
   BOOST_REQUIRE_EQUAL( enumedValue, meVal2);

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

   const ArgString2Array  as2a( "-e meVal1,meVal3", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( !enumedValue.empty());
   BOOST_REQUIRE_EQUAL( enumedValue.size(), 2);
   BOOST_REQUIRE_EQUAL( enumedValue[ 0], meVal1);
   BOOST_REQUIRE_EQUAL( enumedValue[ 1], meVal3);

} // vector_conversion



// =====  END OF test_argh_custom_convert.cpp  =====

