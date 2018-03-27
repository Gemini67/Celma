
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


// C++ Standard Library includes
#include <stdexcept>
#include <iostream>
#include <string>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;
using std::cout;
using std::endl;
using std::string;


namespace {


// local functions prototypes
void printUsage( int flags, int argc, char* argv[]);


} // namespace




/// Test program for generating the usage output with/-out hidden arguments
/// of the argument handler.
/// @since  0.2, 10.04.2016
int main( int argc, char* argv[])
{

   printUsage( Handler::hfHelpShort | Handler::hfUsageCont
      | Handler::hfArgHidden, argc, argv);

   cout << endl << string( 80, '-') << endl << endl;

   printUsage( Handler::hfHelpShort | Handler::hfUsageHidden
      | Handler::hfUsageCont, argc, argv);

   cout << endl << string( 80, '-') << endl << endl;

   ArgString2Array  as2a( "--print-hidden -h", argv[ 0]);
   printUsage( Handler::hfHelpShort | Handler::hfUsageCont
      | Handler::hfArgHidden, as2a.mArgc, as2a.mpArgv);

   exit( EXIT_SUCCESS);
} // main



namespace {



/// Creates an argument handler object with different combinations of optional,
/// mandatory and hidden fields.
/// @param[in]  flags   The flags to pass to the argument handler constructor.
/// @param[in]  argc    Number of arguments.
/// @param[in]  argv[]  List of argument strings.
/// @since  0.2, 10.04.2016
void printUsage( int flags, int argc, char* argv[])
{

   Handler  ah( flags);
   bool     flagArg = false;
   int      intArgOpt = 0;
   int      intArgMan;
   string   stringArgOpt;
   string   stringArgMan;
   bool     hiddenFlagArg = false;
   int      hiddenIntArgOpt = 0;
   int      hiddenIntArgMan;
   string   hiddenStringArgOpt;
   string   hiddenStringArgMan;


   try
   {
      ah.addArgument( "flag", DEST_VAR( flagArg), "flag");
      ah.addArgument( "int-opt", DEST_VAR( intArgOpt), "integer optional");
      ah.addArgument( "int-man", DEST_VAR( intArgMan), "integer mandatory")
         ->setIsMandatory();
      ah.addArgument( "string-opt", DEST_VAR( stringArgOpt), "string optional");
      ah.addArgument( "string-man", DEST_VAR( stringArgMan), "string mandatory")
         ->setIsMandatory();
      ah.addArgument( "hidden-flag", DEST_VAR( hiddenFlagArg), "hidden flag")
         ->setIsHidden();
      ah.addArgument( "hidden-int-opt", DEST_VAR( hiddenIntArgOpt),
         "hidden integer optional")->setIsHidden();
      ah.addArgument( "hidden-int-man", DEST_VAR( hiddenIntArgMan),
         "hidden integer mandatory")->setIsMandatory()->setIsHidden();
      ah.addArgument( "hidden-string-opt", DEST_VAR( hiddenStringArgOpt),
         "hidden string optional")->setIsHidden();
      ah.addArgument( "hidden-string-man", DEST_VAR( hiddenStringArgMan),
         "hidden string mandatory")->setIsMandatory()->setIsHidden();

      ah.evalArguments( argc, argv);
   } catch (const std::exception& e)
   {
   } // end try

} // printUsage



} // namespace


// ===================  END OF test_argh_hidden_output.cpp  ===================

