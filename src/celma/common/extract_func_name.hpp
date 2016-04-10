
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
/// See documentation of function celma::common::extractFuncName().


#ifndef CELMA_COMMON_EXTRACT_FUNC_NAME_HPP
#define CELMA_COMMON_EXTRACT_FUNC_NAME_HPP


#include <string>


namespace celma { namespace common {


/// Extracts the function name without return type and parameters.
/// @param[out]  funcNameStripped  Returns the pure function name.
/// @param[in]   prettyFuncName    Function prototype as in the macro
///                                __PRETTY_function__.
/// @since  0.2, 07.04.2016
extern void extractFuncName( std::string& funcNameStripped,
                             const std::string& prettyFuncName);


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_EXTRACT_FUNC_NAME_HPP


// =========================  END OF extract_func_name.hpp  =========================

