
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


/// @file
/// See documentation of functions celma::common::print_version_info() or
/// celma::common::version_info().


// module header file include
#include "celma/common/print_version_info.hpp"


// C/OS lib includes
#include <cstdio>


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/celma_version.hpp"


using namespace std;


namespace celma { namespace common {



/// Prints the Celma Library version information to \c stdout.
/// @since  0.2, 08.04.2016
void print_version_info()
{

   printf( "Celma library version: %s.\n",
           VersionString);

} // end print_version_info



/// Writes the Celma Library version information to the specified stream.
/// @param[out]  os  The stream to write into.
/// @return  The stream as passed in.
/// @since  0.2, 08.04.2016
ostream& version_info( ostream& os)
{

   return os << "Celma library version: " << VersionString;
} // end version_info



} // namespace common
} // namespace celma


// =========================  END OF print_version_info.cpp  =========================
