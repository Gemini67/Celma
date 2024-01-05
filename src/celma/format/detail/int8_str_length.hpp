
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
/// See documentation of function celma::format::detail::int8_str_length().


#pragma once


#include <cstdint>


namespace celma::format::detail {


/// Determines the number of characters that the string representation of a
/// 1 byte integer value requires.
/// @param[in]  orig_value  Value to determine the string length of.
/// @return  Length of the string format of the value.
/// @since  0.9, 29.11.2016
template< typename T> [[nodiscard]] uint8_t int8_str_length( const T orig_value)
{

   const auto  value = static_cast< uint8_t>( orig_value);

   // 0-9                                         1
   // 10-99                                       2
   // 100-255                                     3

   return (value >= 10) ? (value >= 100) ? 3 : 2 : 1;
} // int8_str_length


} // namespace celma::format::detail


// =====  END OF int8_str_length.hpp  =====

