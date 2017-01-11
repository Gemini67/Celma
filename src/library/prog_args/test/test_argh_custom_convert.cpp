
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "custom conversion" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// STL includes
#include <string>
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerCustomConversion
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/handler.hpp"
#include "celma/appl/arg_string_2_array.hpp"


using namespace std;
using namespace celma;


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
static MyEnum string2enum( const string& enumText)
{
   if (enumText == "meVal1")
      return meVal1;
   if (enumText == "meVal2")
      return meVal2;
   if (enumText == "meVal3")
      return meVal3;
   return initVal;
}



/// Conversion function called by boost::lexical_cast<>: Converts the value in
/// the string into the corresponding enum.
/// @param[in]   source  The stream to read the string value from.
/// @param[out]  me      The enum variable to store the value in.
/// @return  The stream as passed as input parameter.
/// @since  0.2, 10.04.2016
static istream& operator >>( istream& source, MyEnum& me)
{

   string  v;


   source >> v;
   me = string2enum( v.c_str());

   return source;
} // end operator >>



/// Checks if user-supplied conversion to a user-defined data type works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( basic_conversion)
{

   prog_args::Handler  ah( 0);
   MyEnum              enumedValue( initVal);


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue), "Enum")
                                         ->setIsMandatory());

   appl::ArgString2Array  as2a( "-e meVal2", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( enumedValue, meVal2);

} // end basic_conversion



/// Checks if user-supplied conversion to a user-defined data type wrapped
/// in a CheckAssign<> object works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_assign_conversion)
{

   prog_args::Handler            ah( 0);
   common::CheckAssign< MyEnum>  enumedValue( initVal);


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue), "Enum"));

   appl::ArgString2Array  as2a( "-e meVal2", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( enumedValue.hasValue());
   BOOST_REQUIRE_EQUAL( enumedValue, meVal2);

} // end check_assign_conversion



/// Checks if user-supplied conversion to a user-defined data type wrapped
/// in a CheckAssign<> object works.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_conversion)
{

   prog_args::Handler  ah( 0);
   vector< MyEnum>  enumedValue;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "e,enum", DEST_VAR( enumedValue), "Enum"));

   appl::ArgString2Array  as2a( "-e meVal1,meVal3", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( !enumedValue.empty());
   BOOST_REQUIRE_EQUAL( enumedValue.size(), 2);
   BOOST_REQUIRE_EQUAL( enumedValue[ 0], meVal1);
   BOOST_REQUIRE_EQUAL( enumedValue[ 1], meVal3);

} // end vector_conversion



// ===================  END OF test_argh_custom_convert.cpp  ===================

