
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the output of the usage of sub-arguments.
**    In the test, the output of the program is automatically checked.
**
--*/


// module to test header file include
#include "celma/prog_args/groups.hpp"


// C++ Standard Library includes
#include <string>


// project includes
#include "celma/prog_args/destination.hpp"


using celma::prog_args::destination;
using celma::prog_args::Handler;



int main( int argc, char* argv[])
{

   Handler  ah( Handler::AllHelp);
   bool     quietFlag;
   bool     debugMode;
   int      manInt1;


   ah.addArgument( "q",             DEST_VAR( quietFlag), "be quiet");
   ah.addArgument( "debug_mode",    DEST_VAR( debugMode),
                   "set to activate the debug mode");
   ah.addArgument( "mandatory_int", DEST_VAR( manInt1),
                   "mandatory integer value")
                 ->setIsMandatory();

   std::string  inputName;
   int          inputMode = 0;

   Handler  subInput( Handler::hfHelpShort | Handler::hfHelpLong);
   subInput.addArgument( "f", DEST_PAIR( inputName, inputMode, 1),
      "specifies to read from a file")->setPrintDefault( false);
   subInput.addArgument( "q", DEST_PAIR( inputName, inputMode, 2),
      "specifies to read from a queue")->setPrintDefault( false);
   ah.addArgument( "i", &subInput, "input arguments");

   std::string  outputName;
   int          outputMode = 0;

   Handler  subOutput( Handler::hfHelpShort | Handler::hfHelpLong);
   subOutput.addArgument( "f", DEST_PAIR( outputName, outputMode, 1),
      "specifies to write into a file")->setPrintDefault( false);
   subOutput.addArgument( "q", DEST_PAIR( outputName, outputMode, 2),
      "specifies to write into a queue")->setPrintDefault( false);
   ah.addArgument( "o", &subOutput, "output arguments");

   ah.evalArguments( argc, argv);

   return EXIT_SUCCESS;
} // end main



// =====  END OF test_sub_groups_usage.cpp  =====

