
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
**    Test program for formatting long lines/multiple line parameter
**    descriptions. Since the usage output cannot be redirected, the test must
**    be done by running the program and look at the output.
**
--*/


// C++ Standard Library includes
#include <iostream>


// project include
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using namespace std;
using namespace celma;



int main( int argc, char* argv[])
{

   celma::appl::ArgString2Array  as2a( "-h", nullptr);


   if (argc != 2)
   {
      cerr << "Need exactly one argument:" << endl
           << "   1  for test of parameter with long description" << endl
           << "   2  for test of parameter with long name" << endl
           << "   3  for test of parameter with long name and long description" << endl
           << endl;
      return EXIT_FAILURE;
   } // end if

   if (atoi( argv[ 1]) == 1)
   {
      prog_args::Handler  ah( prog_args::Handler::AllHelp);
      string              includeName;

      ah.addArgument( "i,include", DEST_VAR( includeName),
                      "Now here we have a parameter with a very long, long, "
                      "description.\nThis description spawns multiple lines by "
                      "itself, and contains lines that are so long that they must "
                      "be split unto multiple lines in order to get a decent "
                      "output.");

      ah.evalArguments( as2a.mArgc, as2a.mpArgv);
   } // end if

   if (atoi( argv[ 1]) == 2)
   {
      prog_args::Handler  ah( prog_args::Handler::AllHelp);
      string              includeName;

      ah.addArgument( "i,include-from-this-absolute-directory-path", DEST_VAR( includeName),
                      "Long parameter");

      ah.evalArguments( as2a.mArgc, as2a.mpArgv);
   } // end scope

   if (atoi( argv[ 1]) == 3)
   {
      prog_args::Handler  ah( prog_args::Handler::AllHelp);
      string              includeName;

      ah.addArgument( "i,include-from-this-absolute-directory-path", DEST_VAR( includeName),
                      "Now here we have a long parameter with a very long, long, "
                      "description.\nThis description spawns multiple lines by "
                      "itself, and contains lines that are so long that they must "
                      "be split unto multiple lines in order to get a decent "
                      "output.");

      ah.evalArguments( as2a.mArgc, as2a.mpArgv);
   } // end scope

   if (atoi( argv[ 1]) == 4)
   {
      prog_args::Handler  ah( prog_args::Handler::AllHelp);
      string              includeName;

      ah.setUsageLineLength( 63);
      ah.addArgument( "i,include-from-this-absolute-directory-path", DEST_VAR( includeName),
                      "Now here we have a long parameter with a very long, long, "
                      "description.\nThis description spawns multiple lines by "
                      "itself, and contains lines that are so long that they must "
                      "be split unto multiple lines in order to get a decent "
                      "output.");

      ah.evalArguments( as2a.mArgc, as2a.mpArgv);
   } // end scope

   cerr << "Invalid value '" << argv[ 1] << "'!" << endl;

   return EXIT_FAILURE;
} // end main



// ======================  END OF test_long_arg_desc.cpp  ======================

