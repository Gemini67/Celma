
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
#include <stdexcept>
#include <string>
#include <vector>
#include "celma/prog_args.hpp"


using celma::prog_args::Handler;



/// Test program for generating the verbose output of the argument handler.
///
/// @since  0.2, 10.04.2016
int main( int argc, char* argv[])
{

   try
   {
      Handler      ah( Handler::hfVerboseArgs);
      bool         flagArg;
      int          intArg;
      std::string  stringArg;

      ah.addArgument( "f,flag",    DEST_VAR( flagArg),   "flag");
      ah.addArgument( "i,integer", DEST_VAR( intArg),    "integer");
      ah.addArgument( "s,string",  DEST_VAR( stringArg), "string");

      ah.evalArguments( argc, argv);
   } catch (const std::exception& e)
   {
      std::cerr << "caught exception: " << e.what() << std::endl;
      ::exit( EXIT_FAILURE);
   } // end try

   ::exit( EXIT_SUCCESS);
} // main



// =====  END OF test_argh_verbose_output.cpp  =====

