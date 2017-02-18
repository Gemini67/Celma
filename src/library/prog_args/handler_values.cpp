
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::@@@.


// module header file include
#include "celma/prog_args/handler_values.hpp"


// C++ STandard Library includes
#include <iostream>


namespace celma { namespace prog_args {



HandlerValues::HandlerValues( int flagSet, IUsageText* txt1, IUsageText* txt2):
   HandlerValues( std::cout, std::cerr, flagSet, txt1, txt2)
{
} // 



HandlerValues::HandlerValues( std::ostream& os, std::ostream& error_os,
                              int flag_set, IUsageText* txt1, IUsageText* txt2):
   Handler( os, error_os, flag_set, txt1, txt2),
   mValues()
{
} // 



void HandlerValues::evalArguments( int argc, char* argv[])
{

   Handler::evalArguments( argc, argv);

} // 



void HandlerValues::evalArgumentsErrorExit( int argc, char* argv[],
                                            const std::string& prefix)
{

   Handler::evalArgumentsErrorExit( argc, argv, prefix);

} // 



} // namespace prog_args
} // namespace celma


// ========================  END OF handler_values.cpp  ========================

