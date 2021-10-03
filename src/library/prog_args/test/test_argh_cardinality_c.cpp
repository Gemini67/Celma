
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "argument cardinality" in the module
**    ArgumentHandler, using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ArgHCardinalityTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;



/// Check that arguments with a cardinality that are not used at all do not lead
/// to an error.
///
/// @since  1.22.0, 29.03.2019
BOOST_AUTO_TEST_CASE( unused_args)
{

   // test with default cardinality
   {
      Handler            ah( 0);
      std::vector< int>  vec;
      bool               dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( vec),
         "A vector of ints"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "x", DEST_VAR( dummy),
         "Another argument"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-x"));
   } // end scope

   // test with "exact" cardinality
   {
      Handler            ah( 0);
      std::vector< int>  vec;
      bool               dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( vec),
         "A vector of ints")->setCardinality(
         celma::prog_args::cardinality_exact( 3)));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "x", DEST_VAR( dummy),
         "Another argument"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-x"));
   } // end scope

   // test with "max" cardinality
   {
      Handler            ah( 0);
      std::vector< int>  vec;
      bool               dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( vec),
         "A vector of ints")->setCardinality(
         celma::prog_args::cardinality_max( 4)));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "x", DEST_VAR( dummy),
         "Another argument"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-x"));
   } // end scope

   // test with "range" cardinality
   {
      Handler            ah( 0);
      std::vector< int>  vec;
      bool               dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( vec),
         "A vector of ints")->setCardinality(
         celma::prog_args::cardinality_range( 3, 7)));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "x", DEST_VAR( dummy),
         "Another argument"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-x"));
   } // end scope

} // unused_args



/// Cardinality information should be printed in 
///
/// @since  1.23.1, 17.04.2019
BOOST_AUTO_TEST_CASE( cardinality_printed)
{

   // test with default cardinality
   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfHelpArgFull
         | Handler::hfListArgVar | Handler::hfUsageCont);
      std::vector< int>   vec;
      bool                dummy = false;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( vec),
         "A vector of ints"));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "x", DEST_VAR( dummy),
         "Another argument"));

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah,
         "--list-arg-vars -v 3,9 --list-arg-vars --help-arg-full v"));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Arguments:\n"
         "'--help-arg-full' calls function/method 'Prints the usage for the given argument.'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-v' value type 'std::vector<int>', destination container 'vec', currently no values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-x' boolean flag, destination 'dummy', not set.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"
         "Arguments:\n"
         "'--help-arg-full' calls function/method 'Prints the usage for the given argument.'.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-v' value type 'std::vector<int>', destination container 'vec', currently 2 values.\n"
         "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "'-x' boolean flag, destination 'dummy', not set.\n"
         "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
         "\n"
         "Argument '-v', usage:\n"
         "   A vector of ints\n"
         "Properties:\n"
         "   destination variable name:  vec\n"
         "   destination variable type:  std::vector<int>\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                none\n"
         "   checks:                     -\n"
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

   // test with "exact" cardinality
   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfHelpArgFull
         | Handler::hfUsageCont);
      std::vector< int>   vec;
      bool                dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( vec),
         "A vector of ints")->setCardinality(
         celma::prog_args::cardinality_exact( 3)));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "x", DEST_VAR( dummy),
         "Another argument"));

      // does not throw despite the missing value for the vector
      // since "help-arg-full" sets the "usage printed flag"
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah,
         "-v 13,14 --help-arg-full v"));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-v', usage:\n"
         "   A vector of ints\n"
         "Properties:\n"
         "   destination variable name:  vec\n"
         "   destination variable type:  std::vector<int>\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                exactly 3\n"
         "   checks:                     -\n"
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

   // test with "max" cardinality
   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfHelpArgFull
         | Handler::hfUsageCont);
      std::vector< int>   vec;
      bool                dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( vec),
         "A vector of ints")->setCardinality(
         celma::prog_args::cardinality_max( 4)));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "x", DEST_VAR( dummy),
         "Another argument"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 13,14 --help-arg-full v"));
      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-v', usage:\n"
         "   A vector of ints\n"
         "Properties:\n"
         "   destination variable name:  vec\n"
         "   destination variable type:  std::vector<int>\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                at most 4\n"
         "   checks:                     -\n"
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

   // test with "range" cardinality
   {
      std::ostringstream  std_out;
      std::ostringstream  std_err;
      Handler             ah( std_out, std_err, Handler::hfHelpArgFull
         | Handler::hfUsageCont);
      std::vector< int>  vec;
      bool               dummy;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( vec),
         "A vector of ints")->setCardinality(
         celma::prog_args::cardinality_range( 3, 7)));
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "x", DEST_VAR( dummy),
         "Another argument"));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 13,14 --help-arg-full v"));

      BOOST_REQUIRE( std_err.str().empty());
      BOOST_REQUIRE( !std_out.str().empty());
      // std::cerr << "\n" << std_out.str() << std::endl;
      BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
         "Argument '-v', usage:\n"
         "   A vector of ints\n"
         "Properties:\n"
         "   destination variable name:  vec\n"
         "   destination variable type:  std::vector<int>\n"
         "   is mandatory:               false\n"
         "   value mode:                 'required' (2)\n"
         "   cardinality:                between 3 and 7\n"
         "   checks:                     -\n"
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

} // unused_args



/// Handling of a boolean flag that's used twice on the command line.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( boolean_used_twice)
{

   Handler               ah( 0);
   std::optional< bool>  flag;


   ah.addArgument( "f", DEST_VAR( flag), "Boolean flag");

  BOOST_REQUIRE_THROW( evalArgumentString( ah, "-f -f"),
      std::runtime_error);

} // boolean_used_twice



/// Handling of an integer value that's set twice on the command line.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( int_set_twice)
{

   Handler              ah( 0);
   std::optional< int>  value;


   ah.addArgument( "v", DEST_VAR( value), "integer value");

  BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 1 -v 2"),
      std::runtime_error);

} // int_set_twice



/// Handling of an integer value that allows setting 2 values (not really
/// sensible ...).
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( int_allow_max_two)
{

   using celma::prog_args::cardinality_max;

   // set just one value
   {
      Handler              ah( 0);
      std::optional< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( cardinality_max( 2));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 1"));
   } // end scope

   // set two values, still okay
   {
      Handler              ah( 0);
      std::optional< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( cardinality_max( 2));

     BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 1 -v 2"));
   } // end scope

   // setting three values should fail
   {
      Handler              ah( 0);
      std::optional< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( cardinality_max( 2));

     BOOST_REQUIRE_THROW( evalArgumentString( ah, "-v 1 -v 2 -v 3"),
         std::runtime_error);
   } // end scope

} // int_allow_max_two



/// Handling of a vector that allows any number of values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_multiple)
{

   Handler            ah( 0);
   std::vector< int>  values;


   ah.addArgument( "v", DEST_VAR( values), "integer values");

  BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 1 -v 2,3,4 -v 5"));

} // vector_multiple



/// Handling of a vector that allows a maximum of 3 values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_max_3)
{

   using celma::prog_args::cardinality_max;
   using std::runtime_error;

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      ///
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0),
         values()
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( cardinality_max( 3))
                       ->setTakesMultiValue();
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler            ah;
      /// Destination variable.
      std::vector< int>  values;

   }; // TestData

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-v 1,2,3,4"),
                           runtime_error);
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-v 1,2 -v 3,4"),
                           runtime_error);
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-v 1 2 3 4"),
                           runtime_error);
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-v 1,2,3 -v 4"),
                           runtime_error);
   } // end scope

} // vector_max_3



/// Handling of a vector that expects exactly 3 values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_exact_3)
{

   using celma::prog_args::cardinality_exact;
   using std::runtime_error;

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      ///
      /// @since  1.46.1, 22.0.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0),
         values()
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( cardinality_exact( 3))
                       ->setTakesMultiValue();
      } // TestData::TestData

      /// The argument handler object for the test.
      Handler            ah;
      /// Destination variable.
      std::vector< int>  values;

   }; // TestData

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-v 1,2"),
                           runtime_error);
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-v 1,2,3"));
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-v 1,2,3,4"),
                           runtime_error);
   } // end scope

} // vector_exact_3



/// Handling of a C array that expects exactly 3 values.
///
/// @since  1.26.0, 29.04.2019
BOOST_AUTO_TEST_CASE( c_array_exact_3)
{

   using celma::prog_args::cardinality_exact;
   using std::runtime_error;

   /// Helper class used to create/initialise the objects for the test.
   ///
   /// @since  1.26.0, 29.04.2019
   class TestData
   {
   public:
      /// Constructor, does all the work.
      ///
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  1.26.0, 29.04.2019
      TestData():
         ah( 0),
         values()
      {
         ah.addArgument( "a", DEST_VAR( values), "integer values")
            ->setCardinality( cardinality_exact( 3))->setTakesMultiValue();
      } // TestData::TestData

      /// The argument handler object for the test.
      Handler  ah;
      /// Destination variable.
      int      values[ 3];

   }; // TestData

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-a 1,2"), runtime_error);
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-a 1,2,3"));
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-a 1,2,3,4"),
         runtime_error);
   } // end scope

} // c_array_exact_3



/// Handling of an array that expects exactly 3 values.
///
/// @since  1.26.0, 28.04.2019
BOOST_AUTO_TEST_CASE( array_exact_3)
{

   using celma::prog_args::cardinality_exact;
   using std::runtime_error;

   /// Helper class used to create/initialise the objects for the test.
   ///
   /// @since  1.26.0, 28.04.2019
   class TestData
   {
   public:
      /// Constructor, does all the work.
      ///
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  1.26.0, 28.04.2019
      TestData():
         ah( 0),
         values()
      {
         ah.addArgument( "a", DEST_VAR( values), "integer values")
                       ->setCardinality( cardinality_exact( 3))
                       ->setTakesMultiValue();
      } // TestData::TestData

      /// The argument handler object for the test.
      Handler              ah;
      /// Destination variable.
      std::array< int, 3>  values;

   }; // TestData

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-a 1,2"),
         runtime_error);
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-a 1,2,3"));
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-a 1,2,3,4"),
         runtime_error);
   } // end scope

} // array_exact_3



/// Handling of a vector that expects 2 to 5 values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_range_2_5)
{

   using celma::prog_args::cardinality_range;
   using std::runtime_error;

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @since  1.46.1, 22.08.2021  (no argument string parameter anymore)
      /// @since  0.2, 10.04.2016
      TestData():
         ah( 0),
         values()
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( cardinality_range( 2, 5))
                       ->setTakesMultiValue();
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler            ah;
      /// Destination variable.
      std::vector< int>  values;

   }; // TestData

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-v 1"),
                           runtime_error);
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-v 1,2"));
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-v 1,2,3"));
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-v 1,2,3,4"));
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( td.ah, "-v 1,2,3,4,5"));
   } // end scope

   {
      TestData  td;
      BOOST_REQUIRE_THROW( evalArgumentString( td.ah, "-v 1,2,3,4,5,6"),
                           runtime_error);
   } // end scope

} // vector_range_2_5



// =====  END OF test_argh_cardinality_c.cpp  =====

