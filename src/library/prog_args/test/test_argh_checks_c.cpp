
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
**    Test program for the feature "value checks" in the module Handler,
**    using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE HandlerChecksTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::common::CheckAssign;
using celma::prog_args::Handler;
using std::overflow_error;
using std::out_of_range;
using std::runtime_error;
using std::string;
using std::underflow_error;
using std::vector;



/// Verify that general errors regarding checks are caught.
///
/// @since  1.23.1, 15.04.2019
BOOST_AUTO_TEST_CASE( errors)
{

   {
      Handler  ah( 0);
      bool     dummy = false;

      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( dummy), "flag")
         ->addCheck( nullptr), std::logic_error);
   } // end scope

   {
      Handler      ah( 0);
      std::string  dummy;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( dummy), "string")
         ->addCheck( nullptr), std::invalid_argument);
   } // end scope

   // specify an invalid range
   {
      Handler  ah( 0);
      int      iVal = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
                                         ->addCheck( celma::prog_args::range( 5, 5)),
                           std::invalid_argument);
   } // end scope

   // specify another invalid range
   {
      Handler  ah( 0);
      int      iVal = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
                                         ->addCheck( celma::prog_args::range( 5, 2)),
                           std::invalid_argument);
   } // end scope

   // specify an empty list of values
   {
      Handler  ah( 0);
      int      iVal = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
                                         ->addCheck( celma::prog_args::values( "")),
                           std::invalid_argument);
   } // end scope

   // adding two minimum/lower checks should throw
   {
      Handler  ah( 0);
      int      iVal = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( celma::prog_args::lower( 20))
         ->addCheck( celma::prog_args::lower( 30)),
         std::logic_error);
   } // end scope

   // adding two range checks should throw
   {
      Handler  ah( 0);
      int      iVal = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( celma::prog_args::range( 20, 100))
         ->addCheck( celma::prog_args::range( 50, 90)),
         std::logic_error);
   } // end scope

   // adding two maximum/upper checks should throw
   {
      Handler  ah( 0);
      int      iVal = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( celma::prog_args::upper( 20))
         ->addCheck( celma::prog_args::upper( 30)),
         std::logic_error);
   } // end scope

   // adding two values checks should throw
   {
      Handler  ah( 0);
      int      iVal = -1;

      BOOST_REQUIRE_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( celma::prog_args::values( "10,20,30"))
         ->addCheck( celma::prog_args::values( "11,12,13")),
         std::logic_error);
   } // end scope

} // errors



/// Check that the 'lower' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_limit)
{

   using celma::prog_args::lower;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "-i 10000 --help-arg-full i", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10000);

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-i', usage:\n"
         "   Integer\n"
         "Properties:\n"
         "   destination variable name:  iVal\n"
         "   destination variable type:  int\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     Value >= 10\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // lower_limit



/// Check that the 'lower' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_limit_vector)
{

   using celma::prog_args::lower;

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "-i 10000", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10000);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10));

      auto const  as2a = make_arg_array( "-i 10,5,10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

} // lower_limit_vector



/// Check that the 'upper' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( upper_limit)
{

   using celma::prog_args::upper;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 500", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      CheckAssign< int>   iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 1 --help-arg-full i", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 1);

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-i', usage:\n"
         "   Integer\n"
         "Properties:\n"
         "   destination variable name:  iVal\n"
         "   destination variable type:  int\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     Value < 100\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // upper_limit



/// Check that the 'upper' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( upper_limit_vector)
{

   using celma::prog_args::upper;

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 500", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 1);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 50,100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 50);
   } // end scope

} // upper_limit_vector



/// Check that a combination of 'lower' and 'uppper' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_upper_limit)
{

   using celma::prog_args::lower;
   using celma::prog_args::upper;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      CheckAssign< int>   iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 99 --help-arg-full i", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-i', usage:\n"
         "   Integer\n"
         "Properties:\n"
         "   destination variable name:  iVal\n"
         "   destination variable type:  int\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     Value >= 10, Value < 100\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

} // lower_upper_limit



/// Check that a combination of 'lower' and 'uppper' limit works correctly on a
/// vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( lower_upper_limit_vector)
{

   using celma::prog_args::lower;
   using celma::prog_args::upper;

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 10,200", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         overflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")->addCheck( lower( 10))
         ->addCheck( upper( 100));

      auto const  as2a = make_arg_array( "-i 20,5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         underflow_error);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 20);
   } // end scope

} // lower_upper_limit_vector



/// Check that the 'range' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_range)
{

   using celma::prog_args::range;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 10);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 99", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 99);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

} // check_range



/// Check that the 'range' limit works correctly on a vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_range_vector)
{

   using celma::prog_args::range;

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 10", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      vector< int>        iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 99 --help-arg-full i", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 99);

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-i', usage:\n"
         "   Integer\n"
         "Properties:\n"
         "   destination variable name:  iVal\n"
         "   destination variable type:  std::vector<int>\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                none\n"
         "   checks:                     10 <= value < 100\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 100", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 10000", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 10,200", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 10);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;

      ah.addArgument( "i", DEST_VAR( iVal), "Integer")
         ->addCheck( range( 10, 100));

      auto const  as2a = make_arg_array( "-i 20,5", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 20);
   } // end scope

} // check_range_vector



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_string)
{

   using celma::prog_args::values;

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      auto const  as2a = make_arg_array( "-n peter", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      auto const  as2a = make_arg_array( "-n Paule", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      auto const  as2a = make_arg_array( "-n Pete", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !name.hasValue());
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      auto const  as2a = make_arg_array( "-n Peter", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Peter");
   } // end scope

   {
      Handler               ah( 0);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      auto const  as2a = make_arg_array( "-n Paul", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Paul");
   } // end scope

   {
      std::ostringstream    std_out;
      std::ostringstream    std_err;
      Handler               ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      CheckAssign< string>  name;

      ah.addArgument( "n", DEST_VAR( name), "Name")
                    ->addCheck( values( "Peter,Paul,Mary"));

      auto const  as2a = make_arg_array( "-n Mary --help-arg-full n", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( name.hasValue());
      BOOST_REQUIRE_EQUAL( name.value(), "Mary");

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-n', usage:\n"
         "   Name\n"
         "Properties:\n"
         "   destination variable name:  name\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     Value in ( \"Mary\", \"Paul\", \"Peter\")\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // check_values_string



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_int)
{

   using celma::prog_args::values;

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 110", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 11", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 11);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 111);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 1111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 1111);
   } // end scope

} // check_values_int



/// Check that the 'list of values' limit works correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( check_values_int_vector)
{

   using celma::prog_args::values;

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 110", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( iVal.empty());
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 11", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 11);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 111);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 1111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 1111);
   } // end scope

   {
      Handler       ah( 0);
      vector< int>  iVal;


      ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                    ->addCheck( values( "11,111,1111"));

      auto const  as2a = make_arg_array( "-i 11,1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         out_of_range);
      BOOST_REQUIRE( !iVal.empty());
      BOOST_REQUIRE_EQUAL( iVal.size(), 1);
      BOOST_REQUIRE_EQUAL( iVal[ 0], 11);
   } // end scope

} // check_values_int_vector



/// Verify that the "is a file" and "is a directory" checks work correctly.
/// @since  1.4.1, 02.03.2018
BOOST_AUTO_TEST_CASE( correctly_check_file_directory)
{

   using celma::prog_args::isDirectory;
   using celma::prog_args::isFile;

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "File")->addCheck( isFile());

      auto const  as2a = make_arg_array( "-f /tmp", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "File")->addCheck( isFile());

      auto const  as2a = make_arg_array( "-f /etc/passwd", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope


   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Directory")
         ->addCheck( isDirectory());

      auto const  as2a = make_arg_array( "-d /etc/passwd", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      string              dest;

      ah.addArgument( "d", DEST_VAR( dest), "Directory")
         ->addCheck( isDirectory());

      auto const  as2a = make_arg_array( "-d /tmp --help-arg-full d", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-d', usage:\n"
         "   Directory\n"
         "Properties:\n"
         "   destination variable name:  dest\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     is a directory\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Directory")
         ->addCheck( isDirectory());

      auto const  as2a = make_arg_array( "-d /tmp", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // correctly_check_file_directory



/// Verify that the "is an absolute path" check work correctly.
/// @since  1.4.2, 12.04.2018
BOOST_AUTO_TEST_CASE( correctly_check_absolute_path)
{

   using celma::prog_args::isAbsolutePath;

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      auto const  as2a = make_arg_array( "-p ./data/file.dat", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      auto const  as2a = make_arg_array( "-p data/file.dat", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      auto const  as2a = make_arg_array( "-p ~/data/file.dat", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      auto const  as2a = make_arg_array( "-p /etc/passwd", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler              ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      string              dest;

      ah.addArgument( "p", DEST_VAR( dest), "Path")->addCheck( isAbsolutePath());

      auto const  as2a = make_arg_array( "-p /etc/passwd --help-arg-full p", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-p', usage:\n"
         "   Path\n"
         "Properties:\n"
         "   destination variable name:  dest\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     is an absolute path\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // correctly_check_absolute_path



/// Verify that a combined check for "is a directory" and "is an absolute path"
/// work correctly.
/// @since  1.4.2, 12.04.2018
BOOST_AUTO_TEST_CASE( check_directory_and_absolute_path)
{

   using celma::prog_args::isAbsolutePath;
   using celma::prog_args::isDirectory;

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      auto const  as2a = make_arg_array( "-d /etc/passwd", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      auto const  as2a = make_arg_array( "-d etc", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      auto const  as2a = make_arg_array( "-d ./etc", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         runtime_error);
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      auto const  as2a = make_arg_array( "-d /etc", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      string              dest;

      ah.addArgument( "d", DEST_VAR( dest), "Dir")->addCheck( isAbsolutePath())
         ->addCheck( isDirectory());

      auto const  as2a = make_arg_array( "-d /etc --help-arg-full d", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-d', usage:\n"
         "   Dir\n"
         "Properties:\n"
         "   destination variable name:  dest\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     is an absolute path, is a directory\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // check_directory_and_absolute_path



/// Verify that the "parent directory exists" check work correctly.
///
/// @since  1.9.0, 04.08.2018
BOOST_AUTO_TEST_CASE( correctly_check_parent_diretory_exists)
{

   using celma::prog_args::parentDirectoryExists;

   // should throw when the path does not exist
   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "path and filename")
         ->addCheck( parentDirectoryExists());

      auto const  as2a = make_arg_array( "-f /home/anyusername/textfile.txt", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   // should throw when the path does exist but is not a directory
   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "path and filename")
         ->addCheck( parentDirectoryExists());

      auto const  as2a = make_arg_array( "-f /etc/services/textfile.txt", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::runtime_error);
   } // end scope

   {
      Handler  ah( 0);
      string   dest;

      ah.addArgument( "f", DEST_VAR( dest), "path and filename")
         ->addCheck( parentDirectoryExists());

      auto const  as2a = make_arg_array( "-f /etc/textfile.txt", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      string              dest;

      ah.addArgument( "f", DEST_VAR( dest), "path and filename")
         ->addCheck( parentDirectoryExists());

      auto const  as2a = make_arg_array( "-f /etc/textfile.txt --help-arg-full f",
         nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-f', usage:\n"
         "   path and filename\n"
         "Properties:\n"
         "   destination variable name:  dest\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     parent directory exists\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // correctly_check_parent_diretory_exists



/// Verify the "pattern" check.
///
/// @since  1.19.0, 25.12.2018
BOOST_AUTO_TEST_CASE( pattern_check)
{

   using celma::prog_args::pattern;

   // check against a pattern for a name: one word starting with an uppercase
   {
      Handler  ah( 0);
      string   name;

      ah.addArgument( "n", DEST_VAR( name), "A name")
         ->addCheck( pattern( "^[A-Z][a-z]+"));

      auto const  as2a = make_arg_array( "-n Peter", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // check against a pattern for a name: one word starting with an uppercase
   {
      Handler  ah( 0);
      string   name;

      ah.addArgument( "n", DEST_VAR( name), "A name")
         ->addCheck( pattern( "^[A-Z][a-z]+"));

      auto const  as2a = make_arg_array( "-n HansPeter", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::out_of_range);
   } // end scope

   // check against a pattern for a name: one word starting with an uppercase
   {
      Handler  ah( 0);
      string   name;

      ah.addArgument( "n", DEST_VAR( name), "A name")
         ->addCheck( pattern( "^[A-Z][a-z]+"));

      auto const  as2a = make_arg_array( "-n peter", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::out_of_range);
   } // end scope

   // check against a pattern for a name: one word starting with an uppercase
   {
      Handler  ah( 0);
      string   name;

      ah.addArgument( "n", DEST_VAR( name), "A name")
         ->addCheck( pattern( "^[A-Z][a-z]+"));

      auto const  as2a = make_arg_array( "-n Peter123", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::out_of_range);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      string              name;

      ah.addArgument( "n", DEST_VAR( name), "A name")
         ->addCheck( pattern( "^[A-Z][a-z]+"));

      auto const  as2a = make_arg_array( "-n Peterchen --help-arg-full n", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-n', usage:\n"
         "   A name\n"
         "Properties:\n"
         "   destination variable name:  name\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     Value matches '^[A-Z][a-z]+'\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

   // pass the pattern directly
   {
      Handler     ah( 0);
      string      name;
      std::regex  reg_ex( "^[A-Z][a-z]+");

      ah.addArgument( "n", DEST_VAR( name), "A name")
         ->addCheck( pattern( reg_ex));

      auto const  as2a = make_arg_array( "-n Peter", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // pattern_check



/// Verifies that the 'minimum length' check works correctly.
///
/// @since  1.23.0, 11.04.2019
BOOST_AUTO_TEST_CASE( minimum_length)
{

   using celma::prog_args::minLength;

   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( minLength( 0)), std::invalid_argument);
   } // end scope

   // value too short
   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( minLength( 6)));

      auto const  as2a = make_arg_array( "-s hello", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::underflow_error);
   } // end scope

   // value just about long enough
   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( minLength( 6)));

      auto const  as2a = make_arg_array( "-s worlds", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      std::string         dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( minLength( 6)));

      auto const  as2a = make_arg_array( "-s worlds --help-arg-full s", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-s', usage:\n"
         "   string\n"
         "Properties:\n"
         "   destination variable name:  dest\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     Length >= 6\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // minimum_length



/// Verifies that the 'maximum length' check works correctly.
///
/// @since  1.23.0, 12.04.2019
BOOST_AUTO_TEST_CASE( maximum_length)
{

   using celma::prog_args::maxLength;

   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( maxLength( 0)), std::invalid_argument);
   } // end scope

   // value too long
   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( maxLength( 6)));

      auto const  as2a = make_arg_array( "-s wonderful", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::overflow_error);
   } // end scope

   // value just about short enough
   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( maxLength( 6)));

      auto const  as2a = make_arg_array( "-s worlds", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      std::string         dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( maxLength( 6)));

      auto const  as2a = make_arg_array( "-s worlds --help-arg-full s", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-s', usage:\n"
         "   string\n"
         "Properties:\n"
         "   destination variable name:  dest\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     Length <= 6\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // maximum_length



/// Verifies that combinations of the 'minimum length' and 'maximum length'
/// checks work correctly.
///
/// @since  1.23.0, 12.04.2019
BOOST_AUTO_TEST_CASE( min_max_length)
{

   using celma::prog_args::maxLength;
   using celma::prog_args::minLength;

   // value too short
   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( minLength( 6))->addCheck( maxLength( 12)));

      auto const  as2a = make_arg_array( "-s hello", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::underflow_error);
   } // end scope

   // value length in range
   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( minLength( 6))->addCheck( maxLength( 12)));

      auto const  as2a = make_arg_array( "-s wonderful", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // value too long
   {
      Handler      ah( 0);
      std::string  dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( minLength( 6))->addCheck( maxLength( 12)));

      auto const  as2a = make_arg_array( "-s outstandingly", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
         std::overflow_error);
   } // end scope

   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfUsageCont
         | Handler::hfHelpArgFull);
      std::string         dest;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest), "string")
         ->addCheck( minLength( 6))->addCheck( maxLength( 12)));

      auto const  as2a = make_arg_array( "-s wonderful --help-arg-full s", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-s', usage:\n"
         "   string\n"
         "Properties:\n"
         "   destination variable name:  dest\n"
         "   destination variable type:  std::string\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 1\n"
         "   checks:                     Length >= 6, Length <= 12\n"
         "   check original value:       false\n"
         "   formats:                    -\n"
         "   constraints:                -\n"
         "   is hidden:                  false\n"
         "   takes multiple values:      false\n"
         "   allows inverting:           false\n"
         "   is deprecated:              false\n"
         "   is replaced:                false\n"
         "\n"));
   } // end scope

} // min_max_length



/// Helper class to check the implementation and usage of application specific
/// check classes.
/// @since  0.2, 10.04.2016
class ApplCheckTriple: public celma::prog_args::detail::ICheck
{
public:
   /// Constructor.
   /// @param[in]  first   The first value to accept.
   /// @param[in]  second  The second value to accept.
   /// @param[in]  third   The third value to accept.
   /// @since  0.2, 10.04.2016
   ApplCheckTriple( int first, int second, int third):
      ICheck( "application check triple"),
      m1( first),
      m2( second),
      m3( third)
   {
   }

   /// Checks if the value in \a val equals one of the three check values.
   /// @param[in]  val  The value to check in string format.
   /// @since  0.2, 10.04.2016
   virtual void checkValue( const string& val) const noexcept( false) override
   {
      int  checkVal = boost::lexical_cast< int>( val);
      if ((checkVal != m1) && (checkVal != m2) && (checkVal != m3))
         throw runtime_error( "not in tripple");
   }

   /// Returns a text description of the check.
   /// @return  A string with the text description of the check.
   /// @since  0.16.0, 12.08.2017
   virtual std::string toString() const override
   {
      return "";
   }

private:
   int  m1;
   int  m2;
   int  m3;
}; // ApplCheckTriple



/// Helper function to use the application specific check function just like
/// the standard check functions from the library.
/// @param[in]  first   The first allowed value.
/// @param[in]  second  The second allowed value.
/// @param[in]  third   The third allowed value.
/// @return  Pointer to the newly created check object.
/// @since  0.2, 10.04.2016
static celma::prog_args::detail::ICheck* tripple( int first, int second, int third)
{
   return new ApplCheckTriple( first, second, third);
} // tripple



/// Application specific limit check.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( application_check)
{

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      auto const  as2a = make_arg_array( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      auto const  as2a = make_arg_array( "-i 1", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           runtime_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      auto const  as2a = make_arg_array( "-i 110", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           runtime_error);
      BOOST_REQUIRE( !iVal.hasValue());
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      auto const  as2a = make_arg_array( "-i 11", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 11);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      auto const  as2a = make_arg_array( "-i 111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 111);
   } // end scope

   {
      Handler            ah( 0);
      CheckAssign< int>  iVal;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( iVal), "Integer value")
                                            ->addCheck( tripple( 11, 111, 1111)));

      auto const  as2a = make_arg_array( "-i 1111", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( iVal.hasValue());
      BOOST_REQUIRE_EQUAL( iVal.value(), 1111);
   } // end scope

} // application_check



/// Test handling of control characters.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( control_check)
{


   Handler  ah( 0);
   int      value = -1;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( value), "some value"));

   {
      auto const  as2a = make_arg_array( "-v 45 ! -v 47", nullptr);
      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
                           runtime_error);
      BOOST_REQUIRE_EQUAL( value, 45);  // since the first part should pass
   } // end scope

} // control_check



// =====  END OF test_argh_checks_c.cpp  =====
