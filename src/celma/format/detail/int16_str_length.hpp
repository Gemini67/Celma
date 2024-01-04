
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
/// See documentation of function celma::format::detail::int16_str_length().


#pragma once


#include <cstdint>


namespace celma::format::detail {


/// Determines the number of characters that the string representation of a
/// short integer value requires.
/// @param[in]  orig_value  The value to determine the string length of.
/// @return  Length of the string format of the value.
/// @since  0.9, 29.11.2016
template< typename T> [[nodiscard]] uint8_t int16_str_length( const T orig_value)
{

   const auto  value = static_cast< uint16_t>( orig_value);

   // 0-9                                         1
   // 10-99                                       2
   // 100-999                                     3
   // 1000-9999                                   4
   // 10000-65535                                 5

   if (value >= 100)
   {
      if (value >= 1000)
      {
         return (value >= 10000) ? 5 : 4;
      } // end if
      return 3;
   } // end if

   // value < 100
   return (value >= 10) ? 2 : 1;
} // int16_str_length


} // namespace celma::format::detail


// =====  END OF int16_str_length.hpp  =====

