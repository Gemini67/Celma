
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
**    Test program for the output of the usage of sub-arguments.
**    In the test, the output of the program is automatically checked.
**
--*/


#include "celma/prog_args/groups.hpp"

#include <string>


using celma::prog_args::Handler;



int main( int argc, char* argv[])
{

   Handler  ah( Handler::AllHelp);
   bool     quietFlag;
   bool     debugMode;
   int      manInt1;


   ah.addArgument( "q",             DEST_VAR( quietFlag), "be quiet");
   ah.addArgument( "debug_mode",    DEST_VAR( debugMode), "set to activate the debug mode");
   ah.addArgument( "mandatory_int", DEST_VAR( manInt1),   "mandatory integer value")->setIsMandatory();

   std::string  inputName;
   int          inputMode = 0;

   Handler  subInput( Handler::hfHelpShort | Handler::hfHelpLong);
   subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputMode), 1,
                         "specifies to read from a file");
   subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputMode), 2,
                         "specifies to read from a queue");
   ah.addArgument( "i", &subInput, "input arguments");

   std::string  outputName;
   int          outputMode = 0;

   Handler  subOutput( Handler::hfHelpShort | Handler::hfHelpLong);
   subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputMode), 1,
                          "specifies to write into a file");
   subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputMode), 2,
                          "specifies to write into a queue");
   ah.addArgument( "o", &subOutput, "output arguments");

   ah.evalArguments( argc, argv);

   return EXIT_SUCCESS;
} // end main



// =========================  END OF test_sub_groups_usage.cpp  =========================
