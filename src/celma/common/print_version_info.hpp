
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
/// celma::common:version_info().


#ifndef CELMA_COMMON_PRINT_VERSION_INFO_HPP
#define CELMA_COMMON_PRINT_VERSION_INFO_HPP


#include <iosfwd>


namespace celma { namespace common {


/// Prints the Celma Library version information to \c stdout.
///
/// @since  0.2, 08.04.2016
extern void print_version_info();


/// Writes the Celma Library version information to the specified stream.
///
/// @param[out]  os  The stream to write into.
/// @return  The stream as passed in.
/// @since  0.2, 08.04.2016
extern std::ostream& version_info( std::ostream& os);


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_PRINT_VERSION_INFO_HPP


// =====  END OF print_version_info.hpp  =====

