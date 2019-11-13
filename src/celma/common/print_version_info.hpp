
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of functions celma::common::printVersionInfo() or
/// celma::common:versionInfo().


#ifndef CELMA_COMMON_PRINT_VERSION_INFO_HPP
#define CELMA_COMMON_PRINT_VERSION_INFO_HPP


#include <iosfwd>


namespace celma { namespace common {


/// Prints the Celma Library version information to \c stdout.
///
/// @since  1.33.1, 13.11.2019
///    (renamed from print_version_info)
/// @since  0.2, 08.04.2016
extern void printVersionInfo();


/// Writes the Celma Library version information to the specified stream.
///
/// @param[out]  os  The stream to write into.
/// @return  The stream as passed in.
/// @since  1.33.1, 13.11.2019
///    (renamed from version_info)
/// @since  0.2, 08.04.2016
extern std::ostream& versionInfo( std::ostream& os);


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_PRINT_VERSION_INFO_HPP


// =====  END OF print_version_info.hpp  =====

