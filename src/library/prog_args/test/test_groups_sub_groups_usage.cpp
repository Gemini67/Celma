
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
**    Test program for the output of the usage of prog_args::Groups combined
**    with sub-arguments.
**    Must be started manually and checked for correctness visually.
**    Run with -h or --help.
**
--*/


#include "celma/prog_args/groups.hpp"


using namespace std;
using namespace celma;


int main( int argc, char* argv[])
{

   prog_args::Groups::SharedArgHndl  ah1( new prog_args::Handler( 0));
   prog_args::Groups::SharedArgHndl  ah2( new prog_args::Handler( prog_args::Handler::AllHelp));

   bool  quietFlag;
   bool  debugMode;
   int   manInt1;
   bool  printVersion;
   bool  printModList;


   ah1->addArgument( "q",             DEST_VAR( quietFlag), "be quiet");
   ah1->addArgument( "debug_mode",    DEST_VAR( debugMode), "set to activate the debug mode");
   ah1->addArgument( "mandatory_int", DEST_VAR( manInt1),   "mandatory integer value")->setIsMandatory();

   ah2->addArgument( "version", DEST_VAR( printVersion), "prints version information");
   ah2->addArgument( "modlist", DEST_VAR( printModList), "prints module list");

   prog_args::Groups::instance().addArgHandler( "Program Arguments:", ah1);
   prog_args::Groups::instance().addArgHandler( "Standard Arguments:", ah2);

   string  inputName;
   int     inputMode = 0;

   prog_args::Handler  subInput( prog_args::Handler::hfHelpShort | prog_args::Handler::hfHelpLong);
   subInput.addArgument( "f", DEST_VAR( inputName), DEST_VAR( inputMode), 1,
                         "specifies to read from a file");
   subInput.addArgument( "q", DEST_VAR( inputName), DEST_VAR( inputMode), 2,
                         "specifies to read from a queue");
   ah1->addArgument( "i", &subInput, "input arguments");

   string  outputName;
   int     outputMode = 0;

   prog_args::Handler  subOutput( prog_args::Handler::hfHelpShort | prog_args::Handler::hfHelpLong);
   subOutput.addArgument( "f", DEST_VAR( outputName), DEST_VAR( outputMode), 1,
                          "specifies to write into a file");
   subOutput.addArgument( "q", DEST_VAR( outputName), DEST_VAR( outputMode), 2,
                          "specifies to write into a queue");
   ah1->addArgument( "o", &subOutput, "output arguments");

   prog_args::Groups::instance().evalArguments( argc, argv);

   return EXIT_SUCCESS;
} // end main



// =========================  END OF test_groups_sub_groups_usage.cpp  =========================
