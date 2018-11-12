
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
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



/// Test program for generating the verbose output of the argument handler.
/// @since  0.2, 10.04.2016
int main( int argc, char* argv[])
{

   prog_args::Handler  ah( prog_args::Handler::hfVerboseArgs);
   bool                flagArg;
   int                 intArg;
   string              stringArg;


   try
   {
      ah.addArgument( "f,flag",    DEST_VAR( flagArg),   "flag");
      ah.addArgument( "i,integer", DEST_VAR( intArg),    "integer");
      ah.addArgument( "s,string",  DEST_VAR( stringArg), "string");

      ah.evalArguments( argc, argv);
   } catch (const exception& e)
   {
      cerr << "caught exception: " << e.what() << endl;
      exit( EXIT_FAILURE);
   } // end try

   exit( EXIT_SUCCESS);
} // main



// ===================  END OF test_argh_verbose_output.cpp  ===================

