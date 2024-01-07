
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of function celma::format::grouped_double2str().


#pragma once


#include <string>


namespace celma::format {


/// Converts a floating point number into string format, with grouping of the
/// digits before the deciomal point.
///
/// @param[in]  value
///    The value to format.
/// @param[in]  precision
///    Precision == numbewr of digits to use after the decimal point.
/// @param[in]  group_char
///    The character to use for the grouping.
/// @return
///    The string with the formatted double.
/// @since
///    1.13.0, 04.10.2018
[[nodiscard]] std::string grouped_double2string( double value, int precision,
   char group_char = '\'');


} // namespace celma::format


// =====  END OF grouped_double2string.hpp  =====

