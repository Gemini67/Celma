
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
**    Test program for the feature "argument cardinality" in the module
**    ArgumentHandler, using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// C++ Standard Library includes
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ArgHCardinalityTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using namespace std;
using namespace celma;



/// Handling of a boolean flag that's used twice on the command line.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( boolean_used_twice)
{

   prog_args::Handler          ah( 0);
   common::CheckAssign< bool>  flag;


   ah.addArgument( "f", DEST_VAR( flag), "Boolean flag");

   appl::ArgString2Array  as2a( "-f -f", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), runtime_error);

} // boolean_used_twice



/// Handling of an integer value that's set twice on the command line.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( int_set_twice)
{

   prog_args::Handler         ah( 0);
   common::CheckAssign< int>  value;


   ah.addArgument( "v", DEST_VAR( value), "integer value");

   appl::ArgString2Array  as2a( "-v 1 -v 2", nullptr);

   BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), runtime_error);

} // int_set_twice



/// Handling of an integer value that allows setting 2 values (not really
/// sensible ...).
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( int_allow_max_two)
{

   // set just one value
   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( prog_args::cardinality_max( 2));

      appl::ArgString2Array  as2a( "-v 1", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   } // end scope

   // set two values, still okay
   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( prog_args::cardinality_max( 2));

      appl::ArgString2Array  as2a( "-v 1 -v 2", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   } // end scope

   // setting three values should fail
   {
      prog_args::Handler         ah( 0);
      common::CheckAssign< int>  value;

      ah.addArgument( "v", DEST_VAR( value), "integer value")
                    ->setCardinality( prog_args::cardinality_max( 2));

      appl::ArgString2Array  as2a( "-v 1 -v 2 -v 3", nullptr);

      BOOST_REQUIRE_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv), runtime_error);
   } // end scope

} // int_allow_max_two



/// Handling of a vector that allows any number of values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_multiple)
{

   prog_args::Handler  ah( 0);
   vector< int>        values;


   ah.addArgument( "v", DEST_VAR( values), "integer values");

   appl::ArgString2Array  as2a( "-v 1 -v 2,3,4 -v 5", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

} // vector_multiple



/// Handling of a vector that allows a maximum of 3 values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_max_3)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         values(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( prog_args::cardinality_max( 3))
                       ->setTakesMultiValue();
      } // end TestData::TestData

      /// The argument handler object for the test.
      prog_args::Handler       ah;
      /// Destination variable.
      vector< int>             values;
      /// Argument string split into argc, argv.
      appl::ArgString2Array  as2a;

   }; // TestData

   {
      TestData  td( "-v 1,2,3,4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1,2 -v 3,4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1 2 3 4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1,2,3 -v 4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

} // vector_max_3



/// Handling of a vector that expects exactly 3 values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_exact_3)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         values(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( prog_args::cardinality_exact( 3))
                       ->setTakesMultiValue();
      } // end TestData::TestData

      /// The argument handler object for the test.
      prog_args::Handler       ah;
      /// Destination variable.
      vector< int>             values;
      /// Argument string split into argc, argv.
      appl::ArgString2Array  as2a;

   }; // TestData

   {
      TestData  td( "-v 1,2");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1,2,3");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

   {
      TestData  td( "-v 1,2,3,4");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

} // vector_exact_3



/// Handling of a vector that expects 2 to 5 values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( vector_range_2_5)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& argstring):
         ah( 0),
         values(),
         as2a( argstring, nullptr)
      {
         ah.addArgument( "v", DEST_VAR( values), "integer values")
                       ->setCardinality( prog_args::cardinality_range( 2, 5))
                       ->setTakesMultiValue();
      } // end TestData::TestData

      /// The argument handler object for the test.
      prog_args::Handler       ah;
      /// Destination variable.
      vector< int>             values;
      /// Argument string split into argc, argv.
      appl::ArgString2Array  as2a;

   }; // TestData

   {
      TestData  td( "-v 1");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

   {
      TestData  td( "-v 1,2");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

   {
      TestData  td( "-v 1,2,3");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

   {
      TestData  td( "-v 1,2,3,4");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

   {
      TestData  td( "-v 1,2,3,4,5");
      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
   } // end scope

   {
      TestData  td( "-v 1,2,3,4,5,6");
      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           runtime_error);
   } // end scope

} // vector_range_2_5



// =====================  END OF test_argh_cardinality.cpp  ====================
