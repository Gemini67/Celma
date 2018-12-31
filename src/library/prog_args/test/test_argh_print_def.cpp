
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


#include <iostream>
#include <vector>
#include "celma/prog_args.hpp"



/// Test program for generating usage output with default values of optional
/// arguments.
///
/// @since  0.2, 10.04.2016
int main( int argc, char* argv[])
{

   try
   {
      celma::prog_args::Handler         ah( celma::prog_args::Handler::AllHelp);
      bool                              flagArg;
      int                               intArgMandatory;
      int                               intArgOptDef = 4711;
      std::string                       stringArgOptDef( "hello world");
      std::vector< int>                 vectorArgOpt;
      celma::common::CheckAssign< int>  intArgOptDef2;

      ah.addArgument( "f,flag",      DEST_VAR( flagArg),
                      "Boolean flag, no default");
      ah.addArgument( "m,mandatory", DEST_VAR( intArgMandatory),
                      "Mandatory integer argument, no default")->setIsMandatory();
      ah.addArgument( "o,optional",  DEST_VAR( intArgOptDef),
                      "Optional integer argument, *with* default");
      ah.addArgument( "p,optional-string", DEST_VAR( stringArgOptDef),
                      "Optional string argument, *with* default");
      ah.addArgument( "l,list",      DEST_VAR( vectorArgOpt),
                      "Optional vector argument, don't print default");
      ah.addArgument( "c,checked",   DEST_VAR( intArgOptDef2),
                      "Optional integer argument, using CheckAssign<>, *with* default");

      ah.evalArguments( argc, argv);
   } catch (const std::exception& e)
   {
      std::cerr << "caught exception: " << e.what() << std::endl;
      ::exit( EXIT_FAILURE);
   } // end try

   ::exit( EXIT_SUCCESS);
} // main



// =====  END OF test_argh_print_def.cpp  =====

