
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
**    Test program for the feature 'argument sub-groups' in the module
**    prog_args::tHandler using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentSubGroupsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;
using std::string;



/// Test argument handling with a single sub-group.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_sub_group)
{

   auto const  as2a = make_arg_array( "-oc mycache", nullptr);
   Handler     masterAH( 0);
   Handler     subAH( 0);
   string      outputName;
   int         outputType = 0;


   BOOST_REQUIRE_NO_THROW( subAH.addArgument( "c",
      DEST_PAIR( outputName, outputType, 1), "cache name"));
   BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", subAH,
      "output arguments"));
   BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE_EQUAL( outputType, 1);
   BOOST_REQUIRE_EQUAL( outputName, "mycache");

} // one_sub_group



/// Two sub-groups with the same argument characters.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( two_sub_groups)
{

   using celma::prog_args::detail::TypedArgBase;

   {
      Handler        masterAH( Handler::hfVerboseArgs);

      Handler        subInput( Handler::hfVerboseArgs);
      string         inputName;
      int            inputType = 0;
      TypedArgBase*  subInputAH = nullptr;

      Handler        subOutput( Handler::hfVerboseArgs);
      string         outputName;
      int            outputType = 0;
      TypedArgBase*  subOutputAH = nullptr;

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c",
         DEST_PAIR( inputName, inputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f",
         DEST_PAIR( inputName, inputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q",
         DEST_PAIR( inputName, inputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( subInputAH = masterAH.addArgument( "i",
         subInput, "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c",
         DEST_PAIR( outputName, outputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f",
         DEST_PAIR( outputName, outputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q",
         DEST_PAIR( outputName, outputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( subOutputAH = masterAH.addArgument( "o",
         subOutput, "output arguments"));

      auto const  as2a = make_arg_array( "-oc mycache", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( !subInputAH->hasValue());
      BOOST_REQUIRE_EQUAL( inputType,  0);
      BOOST_REQUIRE( inputName.empty());

      BOOST_REQUIRE( subOutputAH->hasValue());
      BOOST_REQUIRE_EQUAL( outputType, 1);
      BOOST_REQUIRE_EQUAL( outputName, "mycache");
   } // end scope

   {
      Handler        masterAH( Handler::hfVerboseArgs);

      Handler        subInput( Handler::hfVerboseArgs);
      string         inputName;
      int            inputType = 0;
      TypedArgBase*  subInputAH = nullptr;

      Handler        subOutput( Handler::hfVerboseArgs);
      string         outputName;
      int            outputType = 0;
      TypedArgBase*  subOutputAH = nullptr;

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c",
         DEST_PAIR( inputName, inputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f",
         DEST_PAIR( inputName, inputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q",
         DEST_PAIR( inputName, inputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( subInputAH = masterAH.addArgument( "i",
         subInput, "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c",
         DEST_PAIR( outputName, outputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f",
         DEST_PAIR( outputName, outputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q",
         DEST_PAIR( outputName, outputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( subOutputAH = masterAH.addArgument( "o",
         subOutput, "output arguments"));

      auto const  as2a = make_arg_array( "-if myfile -o -q myqueue", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( subInputAH->hasValue());
      BOOST_REQUIRE_EQUAL( inputType,  2);
      BOOST_REQUIRE_EQUAL( inputName, "myfile");

      BOOST_REQUIRE( subOutputAH->hasValue());
      BOOST_REQUIRE_EQUAL( outputType, 3);
      BOOST_REQUIRE_EQUAL( outputName, "myqueue");
   } // end scope

} // two_sub_groups



/// Twop sub-groups with the same arguments, plus top-level arguments, partially
/// the same as in the sub-group(s).
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( two_sub_groups_mixed_toplevel)
{

   {
      Handler  masterAH( 0);
      string   paramC;
      string   paramL;
      string   paramA;

      Handler  subInput( 0);
      string   inputName;
      int      inputType = 0;

      Handler  subOutput( 0);
      string   outputName;
      int      outputType = 0;

      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "c", DEST_VAR( paramC),
         "top-level argument c"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "l", DEST_VAR( paramL),
         "top-level argument l"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "a", DEST_VAR( paramA),
         "top-level argument a"));

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c",
         DEST_PAIR( inputName, inputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f",
         DEST_PAIR( inputName, inputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q",
         DEST_PAIR( inputName, inputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "i", subInput,
         "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c",
         DEST_PAIR( outputName, outputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f",
         DEST_PAIR( outputName, outputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q",
         DEST_PAIR( outputName, outputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", subOutput,
         "output arguments"));

      auto const  as2a = make_arg_array( "-c valc -oc mycache -l last", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( paramC, "valc");
      BOOST_REQUIRE_EQUAL( inputType,  0);
      BOOST_REQUIRE( inputName.empty());
      BOOST_REQUIRE_EQUAL( outputType, 1);
      BOOST_REQUIRE_EQUAL( outputName, "mycache");
      BOOST_REQUIRE_EQUAL( paramL, "last");
      BOOST_REQUIRE( paramA.empty());
   } // end scope

   {
      Handler  masterAH( 0);
      string   paramC;
      string   paramL;
      string   paramA;

      Handler  subInput( 0);
      string   inputName;
      int      inputType = 0;

      Handler  subOutput( 0);
      string   outputName;
      int      outputType = 0;


      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "c", DEST_VAR( paramC),
         "top-level argument c"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "l", DEST_VAR( paramL),
         "top-level argument l"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "a", DEST_VAR( paramA),
         "top-level argument a"));

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c",
         DEST_PAIR( inputName, inputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f",
         DEST_PAIR( inputName, inputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q",
         DEST_PAIR( inputName, inputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "i", subInput,
         "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c",
         DEST_PAIR( outputName, outputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f",
         DEST_PAIR( outputName, outputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q",
         DEST_PAIR( outputName, outputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", subOutput,
         "output arguments"));

      auto const  as2a = make_arg_array( "-c otherValC -if myfile -a howdy -o "
         "-q myqueue -l lastagain", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( paramC, "otherValC");
      BOOST_REQUIRE_EQUAL( inputType,  2);
      BOOST_REQUIRE_EQUAL( inputName, "myfile");
      BOOST_REQUIRE_EQUAL( paramA, "howdy");
      BOOST_REQUIRE_EQUAL( outputType, 3);
      BOOST_REQUIRE_EQUAL( outputName, "myqueue");
      BOOST_REQUIRE_EQUAL( paramL, "lastagain");
   } // end scope

} // two_sub_groups_mixed_toplevel



/// Sub-groups with multiple arguments.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( sub_multi_args)
{

   {
      Handler  masterAH( 0);
      string   paramC;
      string   paramL;
      string   paramA;

      Handler  subInput( 0);
      string   inputName;
      int      inputType = 0;
      bool     inputFlag1 = false;
      bool     inputFlag2 = false;

      Handler  subOutput( 0);
      string   outputName;
      int      outputType = 0;
      bool     outputFlag1 = false;
      bool     outputFlag2 = false;

      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "c", DEST_VAR( paramC),
         "top-level argument c"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "l", DEST_VAR( paramL),
         "top-level argument l"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "a", DEST_VAR( paramA),
         "top-level argument a"));

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c",
         DEST_PAIR( inputName, inputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f",
         DEST_PAIR( inputName, inputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q",
         DEST_PAIR( inputName, inputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "v", DEST_VAR( inputFlag1),
         "flag 1"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "z", DEST_VAR( inputFlag2),
         "flag 2"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "i", subInput,
         "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c",
         DEST_PAIR( outputName, outputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f",
         DEST_PAIR( outputName, outputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q",
         DEST_PAIR( outputName, outputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "v", DEST_VAR( outputFlag1),
         "flag 1"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "z", DEST_VAR( outputFlag2),
         "flag 2"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", subOutput,
         "output arguments"));

      auto const  as2a = make_arg_array( "-c valc -oc mycache -v -l last",
         nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( paramC, "valc");
      BOOST_REQUIRE_EQUAL( inputType,  0);
      BOOST_REQUIRE( inputName.empty());
      BOOST_REQUIRE( !inputFlag1);
      BOOST_REQUIRE( !inputFlag2);
      BOOST_REQUIRE_EQUAL( outputType, 1);
      BOOST_REQUIRE_EQUAL( outputName, "mycache");
      BOOST_REQUIRE( outputFlag1);
      BOOST_REQUIRE( !outputFlag2);
      BOOST_REQUIRE_EQUAL( paramL, "last");
      BOOST_REQUIRE( paramA.empty());
   } // end scope

   {
      Handler  masterAH( 0);
      string   paramC;
      string   paramL;
      string   paramA;

      Handler  subInput( 0);
      string   inputName;
      int      inputType = 0;
      bool     inputFlag1 = false;
      bool     inputFlag2 = false;

      Handler  subOutput( 0);
      string   outputName;
      int      outputType = 0;
      bool     outputFlag1 = false;
      bool     outputFlag2 = false;

      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "c", DEST_VAR( paramC),
         "top-level argument c"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "l", DEST_VAR( paramL),
         "top-level argument l"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "a", DEST_VAR( paramA),
         "top-level argument a"));

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c",
         DEST_PAIR( inputName, inputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f",
         DEST_PAIR( inputName, inputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q",
         DEST_PAIR( inputName, inputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "v", DEST_VAR( inputFlag1), "flag 1"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "z", DEST_VAR( inputFlag2), "flag 2"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "i", subInput,
         "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c",
         DEST_PAIR( outputName, outputType, 1), "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f",
         DEST_PAIR( outputName, outputType, 2), "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q",
         DEST_PAIR( outputName, outputType, 3), "queue name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "v", DEST_VAR( outputFlag1),
         "flag 1"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "z", DEST_VAR( outputFlag2),
         "flag 2"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", subOutput,
         "output arguments"));

      auto const  as2a = make_arg_array( "-c otherValC -if myfile -z -a howdy "
         "-ovq myqueue -l lastagain", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE_EQUAL( paramC, "otherValC");
      BOOST_REQUIRE_EQUAL( inputType,  2);
      BOOST_REQUIRE_EQUAL( inputName, "myfile");
      BOOST_REQUIRE( !inputFlag1);
      BOOST_REQUIRE( inputFlag2);
      BOOST_REQUIRE_EQUAL( paramA, "howdy");
      BOOST_REQUIRE_EQUAL( outputType, 3);
      BOOST_REQUIRE_EQUAL( outputName, "myqueue");
      BOOST_REQUIRE_EQUAL( paramL, "lastagain");
      BOOST_REQUIRE( outputFlag1);
      BOOST_REQUIRE( !outputFlag2);
   } // end scope

} // sub_multi_args



// =====  END OF test_argument_sub_groups_c.cpp  =====
