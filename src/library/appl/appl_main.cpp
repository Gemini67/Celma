
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::appl::@@@.


#include "celma/appl/appl_main.hpp"


#include <unistd.h>


namespace celma::appl {



bool  ApplBase::mRestart = false;
int   ApplBase::mExitCode = EXIT_SUCCESS;



bool ApplBase::restart()
{
   return mRestart;
}



int ApplBase::exitCode()
{
   return mExitCode;
}



ApplBase::ApplBase( int arg_handler_flags, prog_args::IUsageText* txt1,
   prog_args::IUsageText* txt2):
      mArgHandler( (arg_handler_flags == 0) ? prog_args::Handler::AllHelp
                   : arg_handler_flags, txt1, txt2)
{
}



void ApplBase::handleArguments( int argc, char* argv[])
{

   mArgHandler.evalArguments( argc, argv);

}



} // namespace celma::appl


// =====  END OF appl_main.cpp  =====

