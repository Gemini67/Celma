
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
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


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <iostream>


// project include
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using celma::prog_args::Handler;
using std::cerr;
using std::endl;



int main( int argc, char* argv[])
{

   auto const  as2a = celma::appl::make_arg_array( "-h", nullptr);


   if (argc != 2)
   {
      cerr << "Need exactly one argument:" << endl
           << "   1  for test of parameter with long description" << endl
           << "   2  for test of parameter with long name" << endl
           << "   3  for test of parameter with long name and long description" << endl
           << endl;
      return EXIT_FAILURE;
   } // end if

   if (::atoi( argv[ 1]) == 1)
   {
      Handler      ah( Handler::AllHelp);
      std::string  includeName;

      ah.addArgument( "i,include", DEST_VAR( includeName),
                      "Now here we have a parameter with a very long, long, "
                      "description.\nThis description spawns multiple lines by "
                      "itself, and contains lines that are so long that they must "
                      "be split unto multiple lines in order to get a decent "
                      "output.");

      ah.evalArguments( as2a.mArgC, as2a.mpArgV);
   } // end if

   if (atoi( argv[ 1]) == 2)
   {
      Handler      ah( Handler::AllHelp);
      std::string  includeName;

      ah.addArgument( "i,include-from-this-absolute-directory-path", DEST_VAR( includeName),
                      "Long parameter");

      ah.evalArguments( as2a.mArgC, as2a.mpArgV);
   } // end scope

   if (::atoi( argv[ 1]) == 3)
   {
      Handler      ah( Handler::AllHelp);
      std::string  includeName;

      ah.addArgument( "i,include-from-this-absolute-directory-path", DEST_VAR( includeName),
                      "Now here we have a long parameter with a very long, long, "
                      "description.\nThis description spawns multiple lines by "
                      "itself, and contains lines that are so long that they must "
                      "be split unto multiple lines in order to get a decent "
                      "output.");

      ah.evalArguments( as2a.mArgC, as2a.mpArgV);
   } // end scope

   if (::atoi( argv[ 1]) == 4)
   {
      Handler      ah( Handler::AllHelp);
      std::string  includeName;

      ah.setUsageLineLength( 63);
      ah.addArgument( "i,include-from-this-absolute-directory-path", DEST_VAR( includeName),
                      "Now here we have a long parameter with a very long, long, "
                      "description.\nThis description spawns multiple lines by "
                      "itself, and contains lines that are so long that they must "
                      "be split unto multiple lines in order to get a decent "
                      "output.");

      ah.evalArguments( as2a.mArgC, as2a.mpArgV);
   } // end scope

   cerr << "Invalid value '" << argv[ 1] << "'!" << endl;

   return EXIT_FAILURE;
} // main



// =====  END OF test_long_arg_desc.cpp  =====

