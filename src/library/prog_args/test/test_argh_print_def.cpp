
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


#include <iostream>
#include <vector>
#include "celma/prog_args.hpp"


using namespace std;
using namespace celma;


/// Test program for generating usage output with default values of optional
/// arguments.
/// @since  0.2, 10.04.2016
int main( int argc, char* argv[])
{

   prog_args::Handler         ah( prog_args::Handler::AllHelp);
   bool                       flagArg;
   int                        intArgMandatory;
   int                        intArgOptDef = 4711;
   string                     stringArgOptDef( "hello world");
   vector< int>               vectorArgOpt;
   common::CheckAssign< int>  intArgOptDef2;


   try
   {
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
   } catch (const exception& e)
   {
      cerr << "caught exception: " << e.what() << endl;
      exit( EXIT_FAILURE);
   } // end try

   exit( EXIT_SUCCESS);
}



// =========================  END OF test_argh_print_def.cpp  =========================

