
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the special handling of value filters by the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgHandlerDestValueFilterTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::common::ValueFilter;
using celma::prog_args::Handler;



/// Test error case that can occur with a value filter.
///
/// @since  x.y.z, 18.10.2019
BOOST_AUTO_TEST_CASE( test_value_filter_errors)
{

   // try to set invalid value mode
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->setValueMode( Handler::ValueMode::none), std::logic_error);
   } // end scope

   // another invalid value mode
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->setValueMode( Handler::ValueMode::optional), std::logic_error);
   } // end scope

   // try to set list separator
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->setListSep( '-'), std::logic_error);
   } // end scope

   // try to add a formatter
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->addFormat( celma::prog_args::lowercase()), std::logic_error);
   } // end scope

   // try to add a check fuunction
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->addCheck( celma::prog_args::isFile()), std::logic_error);
   } // end scope

   // try to set the feature "multiple argument values allowed"
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->setTakesMultiValue(), std::logic_error);
   } // end scope

   // try to set the feature "sort data"
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->setSortData(), std::logic_error);
   } // end scope

   // try to set the feature "unique data"
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->setUniqueData(), std::logic_error);
   } // end scope

   // try to set the feature "clear destination"
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->setClearBeforeAssign(), std::logic_error);
   } // end scope

   // try to set the feature "allow inversion"
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
         ->allowsInversion(), std::invalid_argument);
   } // end scope

   // no value
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter"));

      auto const  args = make_arg_array( "-v", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( args.mArgC, args.mpArgV),
         std::runtime_error);
   } // end scope

   // failed cardinality check
   {
      Handler            ah( 0);
      ValueFilter< int>  v;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter"));

      auto const  args = make_arg_array( "-v 42 -v 4711", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( args.mArgC, args.mpArgV),
         std::runtime_error);
   } // end scope

} // test_value_filter_errors



/// For completeness: Set value mode "required" again.
///
/// @since  x.y.z, 18.10.2019
BOOST_AUTO_TEST_CASE( value_mode)
{

   Handler            ah( 0);
   ValueFilter< int>  v;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( v), "value filter")
      ->setValueMode( Handler::ValueMode::required));

} // value_mode



/// Test some basic cases.
///
/// @since  x.y.z, 21.10.2019
BOOST_AUTO_TEST_CASE( basics)
{

   {
      Handler            ah( 0);
      ValueFilter< int>  my_filter;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( my_filter),
         "value filter"));

      auto const  args = make_arg_array( "-v 42", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( args.mArgC, args.mpArgV));

      BOOST_REQUIRE( !my_filter.empty());
      BOOST_REQUIRE_EQUAL( my_filter.size(), 1);

      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( !my_filter.matches( 43));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "42");
   } // end scope

   {
      Handler            ah( 0);
      ValueFilter< int>  my_filter;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( my_filter),
         "value filter"));

      auto const  args = make_arg_array( "-v 42,100-200+!150,4711", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( args.mArgC, args.mpArgV));

      BOOST_REQUIRE( !my_filter.empty());
      BOOST_REQUIRE_EQUAL( my_filter.size(), 3);

      BOOST_REQUIRE( !my_filter.matches( 41));
      BOOST_REQUIRE( my_filter.matches( 42));
      BOOST_REQUIRE( !my_filter.matches( 43));

      BOOST_REQUIRE( !my_filter.matches( 99));
      BOOST_REQUIRE( my_filter.matches( 100));
      BOOST_REQUIRE( my_filter.matches( 101));

      BOOST_REQUIRE( my_filter.matches( 149));
      BOOST_REQUIRE( !my_filter.matches( 150));
      BOOST_REQUIRE( my_filter.matches( 151));

      BOOST_REQUIRE( my_filter.matches( 199));
      BOOST_REQUIRE( my_filter.matches( 200));
      BOOST_REQUIRE( !my_filter.matches( 201));

      BOOST_REQUIRE( !my_filter.matches( 4710));
      BOOST_REQUIRE( my_filter.matches( 4711));
      BOOST_REQUIRE( !my_filter.matches( 4712));

      BOOST_REQUIRE_EQUAL( my_filter.str(), "42,100-200+!150,4711");
   } // end scope

} // basics



/// Test with using "list argument vars".
///
/// @since  x.y.z, 21.10.2019
BOOST_AUTO_TEST_CASE( list_arg_vars)
{

   std::ostringstream  std_oss;
   std::ostringstream  err_oss;
   Handler             ah( std_oss, err_oss, Handler::hfListArgVar);
   ValueFilter< int>   my_filter;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( my_filter),
      "value filter"));

   auto const  args = make_arg_array( "--list-arg-vars -v 42,4711 --list-arg-vars", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( args.mArgC, args.mpArgV));
   BOOST_REQUIRE( err_oss.str().empty());

   // std::cout << std_oss.str() << std::endl;
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_oss,
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
      "'-v' value type 'celma::common::ValueFilter<int>', destination value filter 'my_filter', currently no filters.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
      "\n"
      "Arguments:\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
      "'-v' value type 'celma::common::ValueFilter<int>', destination value filter 'my_filter', currently 2 filters.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
      "\n"));

} // list_arg_vars



// =====  END OF test_argh_dest_value_filter_c.cpp  =====

