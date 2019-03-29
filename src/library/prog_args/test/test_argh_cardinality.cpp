
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
**    Test program for the feature "argument cardinality" in the module
**    ArgumentHandler, using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <stdexcept>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ArgHCardinalityTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
using celma::common::CheckAssign;
using celma::prog_args::Handler;



/// Check that arguments with a cardinality that are not used at all do not lead
/// to an error.
///
/// @since  x.y.z, 29.03.2019
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

      const ArgString2Array  as2a( "-x", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
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

      const ArgString2Array  as2a( "-x", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
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

      const ArgString2Array  as2a( "-x", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
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

      const ArgString2Array  as2a( "-x", nullptr);
      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

} // unused_args



/// Handling of a boolean flag that's used twice on the command line.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( boolean_used_twice)
{

   Handler             ah( 0);
   CheckAssign< bool>  flag;


   ah.addArgument( "f", DEST_VAR( flag), "Boolean flag");

   const ArgString2Array  as2a( "-f -f", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
      std::runtime_error);

} // boolean_used_twice



/// Handling of an integer value that's set twice on the command line.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( int_set_twice)
{

   Handler            ah( 0);
   CheckAssign< int>  value;


   ah.addArgument( "v", DEST_VAR( value), "integer value");

   const ArgString2Array  as2a( "-v 1 -v 2", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
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
      Handler            ah( 0);
      CheckAssign< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( cardinality_max( 2));

      const ArgString2Array  as2a( "-v 1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // set two values, still okay
   {
      Handler            ah( 0);
      CheckAssign< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( cardinality_max( 2));

      const ArgString2Array  as2a( "-v 1 -v 2", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   } // end scope

   // setting three values should fail
   {
      Handler            ah( 0);
      CheckAssign< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( cardinality_max( 2));

      const ArgString2Array  as2a( "-v 1 -v 2 -v 3", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV),
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

   const ArgString2Array  as2a( "-v 1 -v 2,3,4 -v 5", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

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
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      explicit TestData( const std::string& argstring):
         ah( 0),
         values(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( cardinality_max( 3))
                       ->setTakesMultiValue();
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler                ah;
      /// Destination variable.
      std::vector< int>      values;
      /// Argument string split into argc, argv.
      const ArgString2Array  as2a;

   }; // TestData

   {
      TestData  td( "-v 1,2,3,4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1,2 -v 3,4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1 2 3 4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1,2,3 -v 4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
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
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      explicit TestData( const std::string& argstring):
         ah( 0),
         values(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( cardinality_exact( 3))
                       ->setTakesMultiValue();
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler                ah;
      /// Destination variable.
      std::vector< int>      values;
      /// Argument string split into argc, argv.
      const ArgString2Array  as2a;

   }; // TestData

   {
      TestData  td( "-v 1,2");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1,2,3");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   {
      TestData  td( "-v 1,2,3,4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

} // vector_exact_3



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
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      explicit TestData( const std::string& argstring):
         ah( 0),
         values(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( cardinality_range( 2, 5))
                       ->setTakesMultiValue();
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler                ah;
      /// Destination variable.
      std::vector< int>      values;
      /// Argument string split into argc, argv.
      const ArgString2Array  as2a;

   }; // TestData

   {
      TestData  td( "-v 1");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1,2");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   {
      TestData  td( "-v 1,2,3");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   {
      TestData  td( "-v 1,2,3,4");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   {
      TestData  td( "-v 1,2,3,4,5");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV));
   } // end scope

   {
      TestData  td( "-v 1,2,3,4,5,6");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgC, td.as2a.mpArgV),
                           runtime_error);
   } // end scope

} // vector_range_2_5



// =====  END OF test_argh_cardinality.cpp  =====
