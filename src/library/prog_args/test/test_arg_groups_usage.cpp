
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
**    Test program for the output of the usage of prog_args::Groups.
**    Must be started manually and checked for correctness visually.
**    Run with -h or --help.
**
--*/


#include "celma/prog_args/groups.hpp"


using celma::prog_args::Groups;
using celma::prog_args::Handler;


int main( int argc, char* argv[])
{

   auto  ah1( Groups::instance().getArgHandler( "Program Arguments:"));
   auto  ah2( Groups::instance().getArgHandler( "Standard Arguments:", Handler::AllHelp));
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

   try
   {
      Groups::instance().evalArguments( argc, argv);
   } catch (const std::exception& e)
   {
      std::cerr << "caught exception: " << e.what() << std::endl;
      exit( EXIT_FAILURE);
   } // end try

   return EXIT_SUCCESS;
} // end main



// ====================  END OF test_arg_groups_usage.cpp  ====================
