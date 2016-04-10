
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the output of the usage of sub-arguments.
**    In the test, the output of the program is automatically checked.
**
--*/


#include "celma/prog_args/groups.hpp"


using namespace std;
using namespace celma;


int main( int argc, char* argv[])
{

   prog_args::Handler  ah( prog_args::Handler::AllHelp);
   bool                quietFlag;
   bool                debugMode;
   int                 manInt1;


   ah.addArgument( "q",             DEST_VAR( quietFlag), "be quiet");
   ah.addArgument( "debug_mode",    DEST_VAR( debugMode), "set to activate the debug mode");
   ah.addArgument( "mandatory_int", DEST_VAR( manInt1),   "mandatory integer value")->setIsMandatory();

   string  inputName;
   int     inputMode = 0;

   prog_args::Handler  subInput( prog_args::Handler::hfHelpShort | prog_args::Handler::hfHelpLong);
   subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputMode), 1,
                         "specifies to read from a file");
   subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputMode), 2,
                         "specifies to read from a queue");
   ah.addArgument( "i", &subInput, "input arguments");

   string  outputName;
   int     outputMode = 0;

   prog_args::Handler  subOutput( prog_args::Handler::hfHelpShort | prog_args::Handler::hfHelpLong);
   subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputMode), 1,
                          "specifies to write into a file");
   subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputMode), 2,
                          "specifies to write into a queue");
   ah.addArgument( "o", &subOutput, "output arguments");

   ah.evalArguments( argc, argv);

   return EXIT_SUCCESS;
} // end main



// =========================  END OF test_sub_groups_usage.cpp  =========================
