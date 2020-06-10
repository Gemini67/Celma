
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


namespace celma { namespace common {



/// Prints the Celma Library version information to \c stdout.
///
/// @since  1.33.1, 13.11.2019
///    (renamed from print_version_info)
/// @since  0.2, 08.04.2016
void printVersionInfo()
{

   ::printf( "Celma library version: %s.\n", VersionString);

} // print_version_info



/// Writes the Celma Library version information to the specified stream.
///
/// @param[out]  os  The stream to write into.
/// @return  The stream as passed in.
/// @since  1.33.1, 13.11.2019
///    (renamed from version_info)
/// @since  0.2, 08.04.2016
std::ostream& versionInfo( std::ostream& os)
{

   return os << "Celma library version: " << VersionString;
} // version_info



} // namespace common
} // namespace celma


// =====  END OF print_version_info.cpp  =====

