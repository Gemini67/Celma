
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of dynamic bitsets by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestDynamicBitsetTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/container/dynamic_bitset.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::container::DynamicBitset;
using celma::prog_args::Handler;


namespace {


enum bit_names
{
   zero,
   first,
   second,
   third,
   fourth,
   fifth,
   sixth,
   seventh,
   eighth,
   nineth,
   tenth
};


/// Helper class to convert an enum name into its value.
///
/// @since  1.37.0, 28.06.2020
class EnumFormatter final : public celma::prog_args::detail::IFormat
{
public:
   /// Constructor, sets the formatters name in the base class.
   ///
   /// @since  1.37.0, 28.06.2020
   EnumFormatter():
      IFormat( "enum-formatter")
   {
   } // EnumFormatter::EnumFormatter

   /// Empty, virtual destructor.
   ///
   /// @since  1.37.0, 28.06.2020
   ~EnumFormatter() override = default;

   /// Returns the value of the enum as string in \a val.
   ///
   /// @param[in,out]  val  The value to change the formatting of.
   /// @since  1.37.0, 28.06.2020
   void formatValue( std::string& val) const override
   {
      if (val == "zero")
         val = "0";
      else if (val == "first")
         val = "1";
      else if (val == "second")
         val = "2";
      else if (val == "third")
         val = "3";
      else if (val == "fourth")
         val = "4";
      else if (val == "fifth")
         val = "5";
      else if (val == "sixth")
         val = "6";
      else if (val == "seventh")
         val = "7";
      else if (val == "eighth")
         val = "8";
      else if (val == "nineth")
         val = "9";
      else if (val == "tenth")
         val = "10";
      else
         throw std::runtime_error( "'" + val + "' is not a valid enum name");
   } // EnumFormatter::formatValue

}; // EnumFormatter


} // namespace



/// Test error case that can occur with a bitset.
///
/// @since  1.37.0, 28.06.2020
BOOST_AUTO_TEST_CASE( test_bitset_errors)
{

   // assign wrong value types
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-b this,should,throw"),
         std::bad_cast);
   } // end scope

} // test_bitset_errors



/// Test feature to set another character as list separator.
///
/// @since  1.37.0, 28.06.2020
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4,5,6"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 3);
      BOOST_REQUIRE( dbs[ 4]);
      BOOST_REQUIRE( dbs[ 5]);
      BOOST_REQUIRE( dbs[ 6]);
   } // end scope

   // now check with another list separator
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->setListSep( '.'));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4.5.6"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 3);
      BOOST_REQUIRE( dbs[ 4]);
      BOOST_REQUIRE( dbs[ 5]);
      BOOST_REQUIRE( dbs[ 6]);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple values.
///
/// @since  1.37.0, 28.06.2020
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-b 4,5,6 7"),
         std::invalid_argument);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);
      int            free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4,5,6 7"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 3);
      BOOST_REQUIRE( dbs[ 4]);
      BOOST_REQUIRE( dbs[ 5]);
      BOOST_REQUIRE( dbs[ 6]);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4,5,6 7 8"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 5);
      BOOST_REQUIRE( dbs[ 4]);
      BOOST_REQUIRE( dbs[ 5]);
      BOOST_REQUIRE( dbs[ 6]);
      BOOST_REQUIRE( dbs[ 7]);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);
      int            free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-b 4,5,6 7 --endvalues 8"),
         std::invalid_argument);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler        ah( Handler::hfEndValues);
      DynamicBitset  dbs( 10);
      int            free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4,5,6 7 --endvalues 8"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 4);
      BOOST_REQUIRE( dbs[ 4]);
      BOOST_REQUIRE( dbs[ 5]);
      BOOST_REQUIRE( dbs[ 6]);
      BOOST_REQUIRE( dbs[ 7]);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

   // allow a maximum of 3 bits to be set
   {
      Handler           ah( 0);
      std::bitset< 10>  b;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( b), "values")
         ->setCardinality( celma::prog_args::cardinality_max( 3)));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4,5,6"));
   } // end scope

   // allow a maximum of 3 bits to be set, try to set 4
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->setCardinality( celma::prog_args::cardinality_max( 3)));
      BOOST_REQUIRE_THROW( evalArgumentString( ah, "-b 4,5,6,7"),
         std::runtime_error);
   } // end scope

   // set the bits through the values of an enum
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->addFormat( new EnumFormatter()));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b second,fifth,seventh"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 3);
      BOOST_REQUIRE( dbs[ 2]);
      BOOST_REQUIRE( dbs[ 5]);
      BOOST_REQUIRE( dbs[ 7]);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.37.0, 28.06.2020
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      dbs.set( 2);
      dbs.set( 3);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4,5,6"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 5);
      BOOST_REQUIRE( dbs[ 2]);
      BOOST_REQUIRE( dbs[ 3]);
      BOOST_REQUIRE( dbs[ 4]);
      BOOST_REQUIRE( dbs[ 5]);
      BOOST_REQUIRE( dbs[ 6]);
   } // end scope

   // now the default values should be cleared
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      dbs.set( 2);
      dbs.set( 3);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->setClearBeforeAssign());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4,5"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 2);
      BOOST_REQUIRE( dbs[ 4]);
      BOOST_REQUIRE( dbs[ 5]);
   } // end scope

} // test_clear_dest



/// Test feature to reset the flags instead of setting them.
///
/// @since  1.37.0, 28.06.2020
BOOST_AUTO_TEST_CASE( test_resetting_flags)
{

   // simple case of unsetting the flags
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      dbs.set( 2);
      dbs.set( 4);
      dbs.set( 5);
      dbs.set( 6);
      dbs.set( 7);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->unsetFlag());
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4,5,6"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 2);
      BOOST_REQUIRE( dbs[ 2]);
      BOOST_REQUIRE( dbs[ 7]);
   } // end scope

   // combination of multiple features
   {
      Handler        ah( 0);
      DynamicBitset  dbs( 10);

      dbs.set( 2);
      dbs.set( 4);
      dbs.set( 5);
      dbs.set( 6);
      dbs.set( 7);

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values")
         ->unsetFlag()->setTakesMultiValue()->setListSep( '.'));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-b 4.5.6 7"));
      BOOST_REQUIRE_EQUAL( dbs.count(), 1);
      BOOST_REQUIRE( dbs[ 2]);
   } // end scope

} // test_list_sep



/// Print information about the argument.
///
/// @since  1.37.0, 28.06.2020
BOOST_AUTO_TEST_CASE( list_var)
{

   std::ostringstream  oss_std;
   std::ostringstream  oss_err;
   Handler             ah( oss_std, oss_err, Handler::hfListArgVar
      | Handler::hfHelpShort | Handler::hfUsageCont);
   DynamicBitset       dbs( 10);


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( dbs), "values"));
   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--list-arg-var -b 4,5,6 "
      "--list-arg-var"));

   BOOST_REQUIRE( oss_err.str().empty());
   // std::cerr << "\n" << oss_std.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std,
      "Arguments:\n"
      "'-h' calls function/method 'Handler::usage'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-b' value type 'celma::container::DynamicBitset', destination bitset 'dbs', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "\n"
      "Arguments:\n"
      "'-h' calls function/method 'Handler::usage'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-b' value type 'celma::container::DynamicBitset', destination bitset 'dbs', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "\n"));

} // list_var



// =====  END OF test_argh_dest_bitset_c.cpp  =====

