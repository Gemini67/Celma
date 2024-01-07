
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of functions celma::common::printVersionInfo() or
/// celma::common:versionInfo().


#pragma once


#include <iosfwd>


namespace celma::common {


/// Prints the Celma Library version information to \c stdout.
///
/// @since  1.33.1, 13.11.2019
///    (renamed from print_version_info)
/// @since  0.2, 08.04.2016
void printVersionInfo();


/// Writes the Celma Library version information to the specified stream.
///
/// @param[out]  os  The stream to write into.
/// @return  The stream as passed in.
/// @since  1.33.1, 13.11.2019
///    (renamed from version_info)
/// @since  0.2, 08.04.2016
std::ostream& versionInfo( std::ostream& os);


} // namespace celma::common


// =====  END OF print_version_info.hpp  =====

