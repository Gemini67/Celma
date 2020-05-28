
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of function celma::common::extractFuncname().


#ifndef CELMA_COMMON_EXTRACT_FUNCNAME_HPP
#define CELMA_COMMON_EXTRACT_FUNCNAME_HPP


#include <string>


namespace celma { namespace common {


/// Extracts the function/method name without return type or parameters.
///
/// @param[in]  pretty_funcname
///    Function prototype as in the macro \c __PRETTY_FUNCTION__.
/// @since  x.y.z, 12.04.2020
///    (adapted to work with clang++ too)
/// @since  0.6, 04.11.2016
///    (interface changed, simplified algorithm)
/// @since  0.2, 07.04.2016
std::string extractFuncname( const std::string& pretty_funcname);


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_EXTRACT_FUNCNAME_HPP


// =====  END OF extract_funcname.hpp  =====

