
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of vector of booleans by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestVectorBoolTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
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
/// @since  1.23.0, 05.04.2019
class EnumFormatter: public celma::prog_args::detail::IFormat
{
public:
   /// Constructor, sets the formatters name in the base class.
   ///
   /// @since  1.33.0, 05.11.2019
   EnumFormatter():
      IFormat( "enum-formatter")
   {
   } // EnumFormatter::EnumFormatter

   /// Empty, virtual destructor.
   ///
   /// @since  1.23.0, 05.04.2019
   ~EnumFormatter() override = default;

   /// Returns the value of the enum as string in \a val.
   ///
   /// @param[in,out]  val  The value to change the formatting of.
   /// @since  1.23.0, 05.04.2019
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



/// Test error case that can occur with a vector of booleans.
///
/// @since  1.40.0, 04.06.2020
BOOST_AUTO_TEST_CASE( test_vector_bool_errors)
{

   // assign wrong value types
   {
      Handler             ah( 0);
      std::vector< bool>  vb;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values"));

      auto const  as2a = make_arg_array( "-b this,should,throw", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::bad_cast);
   } // end scope

} // test_vector_bool_errors



/// Test feature to set another character as list separator.
///
/// @since  1.40.0, 04.06.2020
BOOST_AUTO_TEST_CASE( test_list_sep)
{

   // first check with the default list separator
   {
      Handler             ah( 0);
      std::vector< bool>  vb;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values"));

      auto const  as2a = make_arg_array( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 4]);
      BOOST_REQUIRE( vb[ 5]);
      BOOST_REQUIRE( vb[ 6]);
   } // end scope

   // now check with another list separator
   {
      Handler             ah( 0);
      std::vector< bool>  vb;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->setListSep( '.'));

      auto const  as2a = make_arg_array( "-b 4.5.6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 4]);
      BOOST_REQUIRE( vb[ 5]);
      BOOST_REQUIRE( vb[ 6]);
   } // end scope

} // test_list_sep



/// Test feature to handle multiple values.
///
/// @since  1.40.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_multi_values)
{

   // first check with the default behaviour: no multi-values
   {
      Handler             ah( 0);
      std::vector< bool>  vb;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values"));

      auto const  as2a = make_arg_array( "-b 4,5,6 7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // first check with the default behaviour: no multi-values, additional value
   // is interpreted as a free value
   {
      Handler             ah( 0);
      std::vector< bool>  vb;
      int                 free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-b 4,5,6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 4]);
      BOOST_REQUIRE( vb[ 5]);
      BOOST_REQUIRE( vb[ 6]);
      BOOST_REQUIRE_EQUAL( free, 7);
   } // end scope

   // now accept multi-values
   {
      Handler             ah( 0);
      std::vector< bool>  vb;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->setTakesMultiValue());

      auto const  as2a = make_arg_array( "-b 4,5,6 7 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 4]);
      BOOST_REQUIRE( vb[ 5]);
      BOOST_REQUIRE( vb[ 6]);
      BOOST_REQUIRE( vb[ 7]);
   } // end scope

   // accept multi-values, would want to add a free value, but flag is not set
   {
      Handler             ah( 0);
      std::vector< bool>  vb;
      int                 free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-b 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // accept multi-values, but still add a free value
   {
      Handler             ah( Handler::hfEndValues);
      std::vector< bool>  vb;
      int                 free = -1;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_VAR( free), "free value"));

      auto const  as2a = make_arg_array( "-b 4,5,6 7 --endvalues 8", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 4]);
      BOOST_REQUIRE( vb[ 5]);
      BOOST_REQUIRE( vb[ 6]);
      BOOST_REQUIRE( vb[ 7]);
      BOOST_REQUIRE_EQUAL( free, 8);
   } // end scope

   // allow a maximum of 3 bits to be set
   {
      Handler             ah( 0);
      std::vector< bool>  vb;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->setCardinality( celma::prog_args::cardinality_max( 3)));

      auto const  as2a = make_arg_array( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // allow a maximum of 3 bits to be set, try to set 4
   {
      Handler             ah( 0);
      std::vector< bool>  vb;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->setCardinality( celma::prog_args::cardinality_max( 3)));

      auto const  as2a = make_arg_array( "-b 4,5,6,7", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // set the bits through the values of an enum
   {
      Handler             ah( 0);
      std::vector< bool>  vb;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->addFormat( new EnumFormatter()));

      auto const  as2a = make_arg_array( "-b second,fifth,seventh", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 2]);
      BOOST_REQUIRE( vb[ 5]);
      BOOST_REQUIRE( vb[ 7]);
   } // end scope

} // test_multi_values



/// Test feature to clear the destination before assigning the values.
///
/// @since  1.40.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_clear_dest)
{

   // first check the default: values are appended
   {
      Handler             ah( 0);
      std::vector< bool>  vb( 10);

      vb[ 2] = true;
      vb[ 3] = true;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values"));

      auto const  as2a = make_arg_array( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 2]);
      BOOST_REQUIRE( vb[ 3]);
      BOOST_REQUIRE( vb[ 4]);
      BOOST_REQUIRE( vb[ 5]);
      BOOST_REQUIRE( vb[ 6]);
   } // end scope

   // now the default values should be cleared
   {
      Handler             ah( 0);
      std::vector< bool>  vb( 10);

      vb[ 2] = true;
      vb[ 3] = true;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->setClearBeforeAssign());

      auto const  as2a = make_arg_array( "-b 4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !vb[ 2]);
      BOOST_REQUIRE( !vb[ 3]);
      BOOST_REQUIRE( vb[ 4]);
      BOOST_REQUIRE( vb[ 5]);
   } // end scope

} // test_clear_dest



/// Test feature to reset the flags instead of setting them.
///
/// @since  1.40.0, 12.07.2020
BOOST_AUTO_TEST_CASE( test_resetting_flags)
{

   // simple case of unsetting the flags
   {
      Handler             ah( 0);
      std::vector< bool>  vb( 10);

      vb[ 2] = true;
      vb[ 4] = true;
      vb[ 5] = true;
      vb[ 6] = true;
      vb[ 7] = true;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->unsetFlag());

      auto const  as2a = make_arg_array( "-b 4,5,6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 2]);
      BOOST_REQUIRE( !vb[ 4]);
      BOOST_REQUIRE( !vb[ 5]);
      BOOST_REQUIRE( !vb[ 6]);
      BOOST_REQUIRE( vb[ 7]);
   } // end scope

   // combination of multiple features
   {
      Handler             ah( 0);
      std::vector< bool>  vb( 10);

      vb[ 2] = true;
      vb[ 4] = true;
      vb[ 5] = true;
      vb[ 6] = true;
      vb[ 7] = true;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values")
         ->unsetFlag()->setTakesMultiValue()->setListSep( '.'));

      auto const  as2a = make_arg_array( "-b 4.5.6 7", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( vb[ 2]);
      BOOST_REQUIRE( !vb[ 4]);
      BOOST_REQUIRE( !vb[ 5]);
      BOOST_REQUIRE( !vb[ 6]);
      BOOST_REQUIRE( !vb[ 7]);
   } // end scope

} // test_list_sep



/// Print information about the argument.
///
/// @since  1.40.0, 12.07.2020
BOOST_AUTO_TEST_CASE( list_var)
{

   std::ostringstream  oss_std;
   std::ostringstream  oss_err;
   Handler             ah( oss_std, oss_err, Handler::hfListArgVar
      | Handler::hfHelpShort | Handler::hfUsageCont);
   std::vector< bool>  vb( 10);


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "b", DEST_VAR( vb), "values"));

   auto const  as2a = make_arg_array( "--list-arg-var -b 4,5,6 --list-arg-var",
      nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

   BOOST_REQUIRE( oss_err.str().empty());
   // std::cerr << "\n" << oss_std.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std,
      "Arguments:\n"
      "'-h' calls function/method 'Handler::usage'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-b' value type 'std::vector<bool>', destination vector 'vb', currently no values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "\n"
      "Arguments:\n"
      "'-h' calls function/method 'Handler::usage'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-b' value type 'std::vector<bool>', destination vector 'vb', currently 3 values.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "\n"));

} // list_var



// =====  END OF test_argh_dest_vector_bool_c.cpp  =====

