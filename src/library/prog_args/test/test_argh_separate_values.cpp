
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
**    Test program for the feature "multiple, separate values" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test, header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ArgHMultipleSeparateValuesTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/arg_string_2_array.hpp"


using celma::common::ArgString2Array;
using celma::prog_args::Handler;
using std::string;
using std::vector;


// module definitions


/// Check attempted wrong usage of feature.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( wrong_destination)
{

   Handler  ah( 0);
   bool     wrong_dest;


   BOOST_REQUIRE_THROW( ah.addArgument( "w", DEST_VAR( wrong_dest),
                                        "multiple values not allowed")->
                                      setTakesMultiValue(), std::invalid_argument);

} // wrong_destination



/// Feature correctly activated but not used.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( feature_unused)
{

   Handler       ah( 0);
   vector< int>  dest;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( dest),
                                           "multiple integers allowed")->
                                         setTakesMultiValue());

   ArgString2Array  as2a( "-v 1,2,3", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( !dest.empty());
   BOOST_REQUIRE_EQUAL( dest.size(), 3);
   BOOST_REQUIRE_EQUAL( dest[ 0], 1);
   BOOST_REQUIRE_EQUAL( dest[ 1], 2);
   BOOST_REQUIRE_EQUAL( dest[ 2], 3);

} // feature_unused



/// Feature correctly activated and used once.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( feature_used_once)
{

   Handler       ah( 0);
   vector< int>  dest;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( dest),
                                           "multiple integers allowed")->
                                         setTakesMultiValue());

   ArgString2Array  as2a( "-v 1,2 3", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( !dest.empty());
   BOOST_REQUIRE_EQUAL( dest.size(), 3);
   BOOST_REQUIRE_EQUAL( dest[ 0], 1);
   BOOST_REQUIRE_EQUAL( dest[ 1], 2);
   BOOST_REQUIRE_EQUAL( dest[ 2], 3);

} // feature_used_once



/// Feature correctly activated and used several times.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( feature_used_often)
{

   Handler       ah( 0);
   vector< int>  dest;


   BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( dest),
                                           "multiple integers allowed")->
                                         setTakesMultiValue());

   ArgString2Array  as2a( "-v 1,2 3 4,5,6 7 8 9", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( !dest.empty());
   BOOST_REQUIRE_EQUAL( dest.size(), 9);
   BOOST_REQUIRE_EQUAL( dest[ 0], 1);
   BOOST_REQUIRE_EQUAL( dest[ 1], 2);
   BOOST_REQUIRE_EQUAL( dest[ 2], 3);
   BOOST_REQUIRE_EQUAL( dest[ 3], 4);
   BOOST_REQUIRE_EQUAL( dest[ 4], 5);
   BOOST_REQUIRE_EQUAL( dest[ 5], 6);
   BOOST_REQUIRE_EQUAL( dest[ 6], 7);
   BOOST_REQUIRE_EQUAL( dest[ 7], 8);
   BOOST_REQUIRE_EQUAL( dest[ 8], 9);

} // feature_used_often



/// Feature used by two destinations.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( two_destinations)
{

   // two destinations, values for first only, feature not used
   {
      Handler          ah( 0);
      vector< int>     dest1;
      vector< string>  dest2;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( dest1),
                                              "multiple integers allowed")->
                                            setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest2),
                                              "multiple strings allowed")->
                                            setTakesMultiValue());

      ArgString2Array  as2a( "-i 1,2,3", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !dest1.empty());
      BOOST_REQUIRE_EQUAL( dest1.size(), 3);
      BOOST_REQUIRE_EQUAL( dest1[ 0], 1);
      BOOST_REQUIRE_EQUAL( dest1[ 1], 2);
      BOOST_REQUIRE_EQUAL( dest1[ 2], 3);

      BOOST_REQUIRE( dest2.empty());
   } // end scope

   // two destinations, values for second only, feature not used
   {
      Handler          ah( 0);
      vector< int>     dest1;
      vector< string>  dest2;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( dest1),
                                              "multiple integers allowed")->
                                            setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest2),
                                              "multiple strings allowed")->
                                            setTakesMultiValue());

      ArgString2Array  as2a( "-s hello,world", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( dest1.empty());

      BOOST_REQUIRE( !dest2.empty());
      BOOST_REQUIRE_EQUAL( dest2.size(), 2);
      BOOST_REQUIRE_EQUAL( dest2[ 0], "hello");
      BOOST_REQUIRE_EQUAL( dest2[ 1], "world");
   } // end scope

   // two destinations, values for first only, feature used
   {
      Handler          ah( 0);
      vector< int>     dest1;
      vector< string>  dest2;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( dest1),
                                              "multiple integers allowed")->
                                            setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest2),
                                              "multiple strings allowed")->
                                            setTakesMultiValue());

      ArgString2Array  as2a( "-i 1,2,3 4 5 6", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !dest1.empty());
      BOOST_REQUIRE_EQUAL( dest1.size(), 6);
      BOOST_REQUIRE_EQUAL( dest1[ 0], 1);
      BOOST_REQUIRE_EQUAL( dest1[ 1], 2);
      BOOST_REQUIRE_EQUAL( dest1[ 2], 3);
      BOOST_REQUIRE_EQUAL( dest1[ 3], 4);
      BOOST_REQUIRE_EQUAL( dest1[ 4], 5);
      BOOST_REQUIRE_EQUAL( dest1[ 5], 6);

      BOOST_REQUIRE( dest2.empty());
   } // end scope

   // two destinations, values for second only, feature used
   {
      Handler          ah( 0);
      vector< int>     dest1;
      vector< string>  dest2;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( dest1),
                                              "multiple integers allowed")->
                                            setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest2),
                                              "multiple strings allowed")->
                                            setTakesMultiValue());

      ArgString2Array  as2a( "-s hello,world nice to meet you", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( dest1.empty());

      BOOST_REQUIRE( !dest2.empty());
      BOOST_REQUIRE_EQUAL( dest2.size(), 6);
      BOOST_REQUIRE_EQUAL( dest2[ 0], "hello");
      BOOST_REQUIRE_EQUAL( dest2[ 1], "world");
      BOOST_REQUIRE_EQUAL( dest2[ 2], "nice");
      BOOST_REQUIRE_EQUAL( dest2[ 3], "to");
      BOOST_REQUIRE_EQUAL( dest2[ 4], "meet");
      BOOST_REQUIRE_EQUAL( dest2[ 5], "you");
   } // end scope

   // two destinations, values for both
   {
      Handler          ah( 0);
      vector< int>     dest1;
      vector< string>  dest2;


      BOOST_REQUIRE_NO_THROW( ah.addArgument( "i", DEST_VAR( dest1),
                                              "multiple integers allowed")->
                                            setTakesMultiValue());
      BOOST_REQUIRE_NO_THROW( ah.addArgument( "s", DEST_VAR( dest2),
                                              "multiple strings allowed")->
                                            setTakesMultiValue());

      ArgString2Array  as2a( "-i 1,2,3 4 5 6 -s hello,world nice to meet you",
                             nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !dest1.empty());
      BOOST_REQUIRE_EQUAL( dest1.size(), 6);
      BOOST_REQUIRE_EQUAL( dest1[ 0], 1);
      BOOST_REQUIRE_EQUAL( dest1[ 1], 2);
      BOOST_REQUIRE_EQUAL( dest1[ 2], 3);
      BOOST_REQUIRE_EQUAL( dest1[ 3], 4);
      BOOST_REQUIRE_EQUAL( dest1[ 4], 5);
      BOOST_REQUIRE_EQUAL( dest1[ 5], 6);

      BOOST_REQUIRE( !dest2.empty());
      BOOST_REQUIRE_EQUAL( dest2.size(), 6);
      BOOST_REQUIRE_EQUAL( dest2[ 0], "hello");
      BOOST_REQUIRE_EQUAL( dest2[ 1], "world");
      BOOST_REQUIRE_EQUAL( dest2[ 2], "nice");
      BOOST_REQUIRE_EQUAL( dest2[ 3], "to");
      BOOST_REQUIRE_EQUAL( dest2[ 4], "meet");
      BOOST_REQUIRE_EQUAL( dest2[ 5], "you");
   } // end scope

} // two_destinations



/// Multiple arguments, two with separate value lists, and a single free value.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( mixed_single_free)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& arguments):
         ah( 0),
         dest_vec(),
         dest_i1( -1),
         dest_i2( -1),
         dest_free( -1),
         as2a( arguments, nullptr)
      {
         BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( dest_vec),
                                                 "multiple integers allowed")->
                                               setTakesMultiValue());
         BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( dest_i1),
                                                 "single integer allowed"));
         BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( dest_i2),
                                                 "single integer allowed"));
         BOOST_REQUIRE_NO_THROW( ah.addArgument( DEST_VAR( dest_free),
                                                 "single free integer allowed"));
      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler          ah;
      /// Destination variable.
      vector< int>     dest_vec;
      /// Destination variable.
      int              dest_i1;   // l
      /// Destination variable.
      int              dest_i2;   // r
      /// Destination variable.
      int              dest_free;
      /// Argument string split into argc, argv.
      ArgString2Array  as2a;

   }; // TestData

   {
      TestData  td( "4711");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE_EQUAL( td.dest_free, 4711);
   } // end scope

   {
      TestData  td( "-v 1 2 3");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE_EQUAL( td.dest_free, -1);
   } // end scope

   {
      TestData  td( "4711 -v 1 2 3");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE_EQUAL( td.dest_free, 4711);
   } // end scope

   {
      TestData  td( "-v 1 2 3 -l 13 -r 42 4711");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, 13);
      BOOST_REQUIRE_EQUAL( td.dest_i2, 42);
      BOOST_REQUIRE_EQUAL( td.dest_free, 4711);
   } // end scope

   {
      TestData  td( "-v 1 2 3 --endvalues 4711");


      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           std::runtime_error);
   } // end scope


   {
      TestData  td( "-v 1 2 3 --endvalues 4711");


      td.ah.addArgumentEndValues( "endvalues");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE_EQUAL( td.dest_free, 4711);
   } // end scope

} // mixed_single_free



/// Multiple arguments, two with separate value lists, and multiple free values.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( mixed_multiple_free)
{

   /// Helper class used to create/initialise the objects for the test.
   /// @since  0.2, 10.04.2016
   class TestData
   {
   public:
      /// Constructor, does all the work.
      /// @param[in]  argstring  The argument string for this test.
      /// @since  0.2, 10.04.2016
      TestData( const string& arguments):
         ah( 0),
         dest_vec(),
         dest_i1( -1),
         dest_i2( -1),
         dest_free(),
         as2a( arguments, nullptr)
      {

         BOOST_REQUIRE_NO_THROW( ah.addArgument( "v", DEST_VAR( dest_vec),
                                                 "multiple integers allowed")->
                                               setTakesMultiValue());
         BOOST_REQUIRE_NO_THROW( ah.addArgument( "l", DEST_VAR( dest_i1),
                                                 "single integer allowed"));
         BOOST_REQUIRE_NO_THROW( ah.addArgument( "r", DEST_VAR( dest_i2),
                                                 "single integer allowed"));
         BOOST_REQUIRE_NO_THROW( ah.addArgument( DEST_VAR( dest_free),
                                                 "multiple free integers allowed"));

      } // end TestData::TestData

      /// The argument handler object for the test.
      Handler          ah;
      /// Destination variable.
      vector< int>     dest_vec;
      /// Destination variable.
      int              dest_i1;   // l
      /// Destination variable.
      int              dest_i2;   // r
      /// Destination variable.
      vector< int>     dest_free;
      /// Argument string split into argc, argv.
      ArgString2Array  as2a;

   }; // TestData

   {
      TestData  td( "4711");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE( !td.dest_free.empty());
      BOOST_REQUIRE_EQUAL( td.dest_free.size(), 1);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 0], 4711);
   } // end scope

   {
      TestData  td( "4711 90125");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE( !td.dest_free.empty());
      BOOST_REQUIRE_EQUAL( td.dest_free.size(), 2);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 0], 4711);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 1], 90125);
   } // end scope

   {
      TestData  td( "-v 1 2 3");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE( td.dest_free.empty());
   } // end scope

   {
      TestData  td( "4711 -v 1 2 3");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE( !td.dest_free.empty());
      BOOST_REQUIRE_EQUAL( td.dest_free.size(), 1);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 0], 4711);
   } // end scope

   {
      TestData  td( "4711 90125 -v 1 2 3");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE( !td.dest_free.empty());
      BOOST_REQUIRE_EQUAL( td.dest_free.size(), 2);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 0], 4711);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 1], 90125);
   } // end scope

   {
      TestData  td( "-v 1 2 3 -l 13 -r 42 4711");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, 13);
      BOOST_REQUIRE_EQUAL( td.dest_i2, 42);
      BOOST_REQUIRE( !td.dest_free.empty());
      BOOST_REQUIRE_EQUAL( td.dest_free.size(), 1);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 0], 4711);
   } // end scope

   {
      TestData  td( "-v 1 2 3 -l 13 -r 42 4711 90125");


      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, 13);
      BOOST_REQUIRE_EQUAL( td.dest_i2, 42);
      BOOST_REQUIRE( !td.dest_free.empty());
      BOOST_REQUIRE_EQUAL( td.dest_free.size(), 2);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 0], 4711);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 1], 90125);
   } // end scope

   {
      TestData  td( "-v 1 2 3 --endvalues 4711");


      BOOST_REQUIRE_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv),
                           std::runtime_error);
   } // end scope

   {
      TestData  td( "-v 1 2 3 --endvalues 4711");


      td.ah.addArgumentEndValues( "endvalues");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE( !td.dest_free.empty());
      BOOST_REQUIRE_EQUAL( td.dest_free.size(), 1);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 0], 4711);
   } // end scope

   {
      TestData  td( "-v 1 2 3 --endvalues 4711 90125");


      td.ah.addArgumentEndValues( "endvalues");

      BOOST_REQUIRE_NO_THROW( td.ah.evalArguments( td.as2a.mArgc, td.as2a.mpArgv));
      BOOST_REQUIRE( !td.dest_vec.empty());
      BOOST_REQUIRE_EQUAL( td.dest_vec.size(), 3);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 0], 1);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 1], 2);
      BOOST_REQUIRE_EQUAL( td.dest_vec[ 2], 3);
      BOOST_REQUIRE_EQUAL( td.dest_i1, -1);
      BOOST_REQUIRE_EQUAL( td.dest_i2, -1);
      BOOST_REQUIRE( !td.dest_free.empty());
      BOOST_REQUIRE_EQUAL( td.dest_free.size(), 2);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 0], 4711);
      BOOST_REQUIRE_EQUAL( td.dest_free[ 1], 90125);
   } // end scope

} // mixed_multiple_free



// ==================  END OF test_argh_separate_values.cpp  ==================

