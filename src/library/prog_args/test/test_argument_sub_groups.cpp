
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
**    Test program for the feature 'argument sub-groups' in the module
**    prog_args::tHandler using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentSubGroupsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using namespace std;
using namespace celma;


// module definitions


/// Test adding an invalid sub-group (NULL pointer).
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( invalid_sub_group)
{

   prog_args::Handler   masterAH( 0);
   prog_args::Handler*  subAH = nullptr;


   BOOST_REQUIRE_THROW( masterAH.addArgument( "o", subAH, "output arguments"),
                        runtime_error);

} // end invalid_sub_group



/// Test argument handling with a single sub-group.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( one_sub_group)
{

   appl::ArgString2Array  as2a( "-oc mycache", nullptr);
   prog_args::Handler     masterAH( 0);
   prog_args::Handler     subAH( 0);
   string                 outputName;
   int                    outputType = 0;


   BOOST_REQUIRE_NO_THROW( subAH.addArgument( "c", DEST_VAR( outputName), DEST_VAR( outputType), 1, "cache name"));
   BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", &subAH, "output arguments"));
   BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( outputType, 1);
   BOOST_REQUIRE_EQUAL( outputName, "mycache");

} // end one_sub_group



/// Two sub-groups with the same argument characters.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( two_sub_groups)
{

   {
      prog_args::Handler                masterAH( prog_args::Handler::hfVerboseArgs);

      prog_args::Handler                subInput( prog_args::Handler::hfVerboseArgs);
      string                            inputName;
      int                               inputType = 0;
      prog_args::detail::TypedArgBase*  subInputAH = nullptr;

      prog_args::Handler                subOutput( prog_args::Handler::hfVerboseArgs);
      string                            outputName;
      int                               outputType = 0;
      prog_args::detail::TypedArgBase*  subOutputAH = nullptr;


      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c", DEST_VAR( inputName), DEST_VAR( inputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( subInputAH = masterAH.addArgument( "i", &subInput, "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c", DEST_VAR( outputName), DEST_VAR( outputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( subOutputAH = masterAH.addArgument( "o", &subOutput, "output arguments"));

      appl::ArgString2Array  as2a( "-oc mycache", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));

      BOOST_REQUIRE( !subInputAH->hasValue());
      BOOST_REQUIRE_EQUAL( inputType,  0);
      BOOST_REQUIRE( inputName.empty());

      BOOST_REQUIRE( subOutputAH->hasValue());
      BOOST_REQUIRE_EQUAL( outputType, 1);
      BOOST_REQUIRE_EQUAL( outputName, "mycache");
   } // end scope

   {
      prog_args::Handler                masterAH( prog_args::Handler::hfVerboseArgs);

      prog_args::Handler                subInput( prog_args::Handler::hfVerboseArgs);
      string                            inputName;
      int                               inputType = 0;
      prog_args::detail::TypedArgBase*  subInputAH = nullptr;

      prog_args::Handler                subOutput( prog_args::Handler::hfVerboseArgs);
      string                            outputName;
      int                               outputType = 0;
      prog_args::detail::TypedArgBase*  subOutputAH = nullptr;


      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c", DEST_VAR( inputName), DEST_VAR( inputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( subInputAH = masterAH.addArgument( "i", &subInput, "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c", DEST_VAR( outputName), DEST_VAR( outputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( subOutputAH = masterAH.addArgument( "o", &subOutput, "output arguments"));

      appl::ArgString2Array  as2a( "-if myfile -o -q myqueue", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));

      BOOST_REQUIRE( subInputAH->hasValue());
      BOOST_REQUIRE_EQUAL( inputType,  2);
      BOOST_REQUIRE_EQUAL( inputName, "myfile");

      BOOST_REQUIRE( subOutputAH->hasValue());
      BOOST_REQUIRE_EQUAL( outputType, 3);
      BOOST_REQUIRE_EQUAL( outputName, "myqueue");
   } // end scope

} // end two_sub_groups



/// Twop sub-groups with the same arguments, plus top-level arguments, partially
/// the same as in the sub-group(s).
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( two_sub_groups_mixed_toplevel)
{

   {
      prog_args::Handler  masterAH( 0);
      string              paramC;
      string              paramL;
      string              paramA;

      prog_args::Handler  subInput( 0);
      string              inputName;
      int                 inputType = 0;

      prog_args::Handler  subOutput( 0);
      string              outputName;
      int                 outputType = 0;


      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "c", DEST_VAR( paramC), "top-level argument c"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "l", DEST_VAR( paramL), "top-level argument l"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "a", DEST_VAR( paramA), "top-level argument a"));

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c", DEST_VAR( inputName), DEST_VAR( inputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "i", &subInput, "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c", DEST_VAR( outputName), DEST_VAR( outputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", &subOutput, "output arguments"));

      appl::ArgString2Array  as2a( "-c valc -oc mycache -l last", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( paramC, "valc");
      BOOST_REQUIRE_EQUAL( inputType,  0);
      BOOST_REQUIRE( inputName.empty());
      BOOST_REQUIRE_EQUAL( outputType, 1);
      BOOST_REQUIRE_EQUAL( outputName, "mycache");
      BOOST_REQUIRE_EQUAL( paramL, "last");
      BOOST_REQUIRE( paramA.empty());
   } // end scope

   {
      prog_args::Handler  masterAH( 0);
      string              paramC;
      string              paramL;
      string              paramA;

      prog_args::Handler  subInput( 0);
      string              inputName;
      int                 inputType = 0;

      prog_args::Handler  subOutput( 0);
      string              outputName;
      int                 outputType = 0;


      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "c", DEST_VAR( paramC), "top-level argument c"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "l", DEST_VAR( paramL), "top-level argument l"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "a", DEST_VAR( paramA), "top-level argument a"));

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c", DEST_VAR( inputName), DEST_VAR( inputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "i", &subInput, "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c", DEST_VAR( outputName), DEST_VAR( outputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", &subOutput, "output arguments"));

      appl::ArgString2Array  as2a( "-c otherValC -if myfile -a howdy -o -q myqueue -l lastagain", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( paramC, "otherValC");
      BOOST_REQUIRE_EQUAL( inputType,  2);
      BOOST_REQUIRE_EQUAL( inputName, "myfile");
      BOOST_REQUIRE_EQUAL( paramA, "howdy");
      BOOST_REQUIRE_EQUAL( outputType, 3);
      BOOST_REQUIRE_EQUAL( outputName, "myqueue");
      BOOST_REQUIRE_EQUAL( paramL, "lastagain");
   } // end scope

} // end two_sub_groups_mixed_toplevel



/// Sub-groups with multiple arguments.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( sub_multi_args)
{

   {
      prog_args::Handler  masterAH( 0);
      string           paramC;
      string           paramL;
      string           paramA;

      prog_args::Handler  subInput( 0);
      string           inputName;
      int              inputType = 0;
      bool             inputFlag1 = false;
      bool             inputFlag2 = false;

      prog_args::Handler  subOutput( 0);
      string           outputName;
      int              outputType = 0;
      bool             outputFlag1 = false;
      bool             outputFlag2 = false;

      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "c", DEST_VAR( paramC), "top-level argument c"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "l", DEST_VAR( paramL), "top-level argument l"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "a", DEST_VAR( paramA), "top-level argument a"));

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c", DEST_VAR( inputName), DEST_VAR( inputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "v", DEST_VAR( inputFlag1), "flag 1"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "z", DEST_VAR( inputFlag2), "flag 2"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "i", &subInput, "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c", DEST_VAR( outputName), DEST_VAR( outputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "v", DEST_VAR( outputFlag1), "flag 1"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "z", DEST_VAR( outputFlag2), "flag 2"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", &subOutput, "output arguments"));

      appl::ArgString2Array  as2a( "-c valc -oc mycache -v -l last", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));
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
      prog_args::Handler  masterAH( 0);
      string              paramC;
      string              paramL;
      string              paramA;

      prog_args::Handler  subInput( 0);
      string              inputName;
      int                 inputType = 0;
      bool                inputFlag1 = false;
      bool                inputFlag2 = false;

      prog_args::Handler  subOutput( 0);
      string              outputName;
      int                 outputType = 0;
      bool                outputFlag1 = false;
      bool                outputFlag2 = false;


      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "c", DEST_VAR( paramC), "top-level argument c"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "l", DEST_VAR( paramL), "top-level argument l"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "a", DEST_VAR( paramA), "top-level argument a"));

      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "c", DEST_VAR( inputName), DEST_VAR( inputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "v", DEST_VAR( inputFlag1), "flag 1"));
      BOOST_REQUIRE_NO_THROW( subInput.addArgument( "z", DEST_VAR( inputFlag2), "flag 2"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "i", &subInput, "input arguments"));

      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "c", DEST_VAR( outputName), DEST_VAR( outputType), 1, "cache name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputType), 2, "file name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputType), 3, "queue name"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "v", DEST_VAR( outputFlag1), "flag 1"));
      BOOST_REQUIRE_NO_THROW( subOutput.addArgument( "z", DEST_VAR( outputFlag2), "flag 2"));
      BOOST_REQUIRE_NO_THROW( masterAH.addArgument( "o", &subOutput, "output arguments"));

      appl::ArgString2Array  as2a( "-c otherValC -if myfile -z -a howdy -ovq myqueue -l lastagain", nullptr);
      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));
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

} // end sub_multi_args



// ===================  END OF test_argument_sub_groups.cpp  ===================
