
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
/// See documentation of function celma::common::extractFuncname().


#pragma once


#include <string>


namespace celma::common {


/// Extracts the function/method name without return type or parameters.
///
/// @param[in]  pretty_funcname
///    Function prototype as in the macro \c __PRETTY_FUNCTION__.
/// @returns
///    The name of function without parameters or return type.
/// @since  1.36.0, 12.04.2020
///    (adapted to work with clang++ too)
/// @since  0.6, 04.11.2016
///    (interface changed, simplified algorithm)
/// @since  0.2, 07.04.2016
[[nodiscard]] std::string extractFuncname( const std::string& pretty_funcname);


} // namespace celma::common


// =====  END OF extract_funcname.hpp  =====

