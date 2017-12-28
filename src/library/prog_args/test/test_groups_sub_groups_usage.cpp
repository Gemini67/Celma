
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
**    Test program for the output of the usage of celma::prog_args::Groups
**    combined with sub-arguments.
**    Must be started manually and checked for correctness visually.
**    Run with -h or --help.
**
--*/


#include "celma/prog_args/groups.hpp"
#include "celma/prog_args/destination.hpp"


using celma::prog_args::Groups;
using celma::prog_args::Handler;
using std::string;


int main( int argc, char* argv[])
{

   auto  ah1 = Groups::instance().getArgHandler( "Program Arguments:");
   auto  ah2 = Groups::instance().getArgHandler( "Standard Arguments:",
                                                 Handler::AllHelp);


   bool  quietFlag;
   bool  debugMode;
   int   manInt1;
   bool  printVersion;
   bool  printModList;

   ah1->addArgument( "q",             DEST_VAR( quietFlag), "be quiet");
   ah1->addArgument( "debug_mode",    DEST_VAR( debugMode),
                     "set to activate the debug mode");
   ah1->addArgument( "mandatory_int", DEST_VAR( manInt1),
                     "mandatory integer value")->setIsMandatory();

   ah2->addArgument( "version", DEST_VAR( printVersion),
                     "prints version information");
   ah2->addArgument( "modlist", DEST_VAR( printModList), "prints module list");


   string  inputName;
   int     inputMode = 0;

   Handler  subInput( Handler::hfHelpShort | Handler::hfHelpLong);
   subInput.addArgument( "f", DEST_PAIR( inputName, inputMode, 1),
                         "specifies to read from a file");
   subInput.addArgument( "q", DEST_PAIR( inputName, inputMode, 2),
                         "specifies to read from a queue");
   ah1->addArgument( "i", &subInput, "input arguments");

   string  outputName;
   int     outputMode = 0;

   Handler  subOutput( Handler::hfHelpShort | Handler::hfHelpLong);
   subOutput.addArgument( "f", DEST_PAIR( outputName, outputMode, 1),
                          "specifies to write into a file");
   subOutput.addArgument( "q", DEST_PAIR( outputName, outputMode, 2),
                          "specifies to write into a queue");
   ah1->addArgument( "o", &subOutput, "output arguments");

   Groups::instance().evalArguments( argc, argv);

   return EXIT_SUCCESS;
} // main



// =================  END OF test_groups_sub_groups_usage.cpp  =================
