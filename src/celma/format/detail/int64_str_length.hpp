
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
/// See documentation of function celma::format::detail::int64_str_length().


#pragma once


#include <cstdint>


namespace celma::format::detail {


/// Determines the number of characters that the string representation of an
/// integer value requires.
/// @param[in]  orig_value  The value to determine the string length of.
/// @return  Length of the string format of the value.
/// @since  0.9, 28.11.2016  (renamed from int_str_length)
/// @since  0.6, 05.11.2016
template< typename T> [[nodiscard]] uint8_t int64_str_length( const T orig_value)
{

   const auto  value = static_cast< uint64_t>( orig_value);

   // 0-9                                         1
   // 10-99                                       2
   // 100-999                                     3
   // 1000-9999                                   4
   // 10000-99999                                 5
   // 100000-999999                               6
   // 1000000-9999999                             7
   // 10000000-99999999                           8
   // 100000000-999999999                         9
   // 1000000000-9999999999                      10
   // 10000000000-99999999999                    11
   // 100000000000-999999999999                  12
   // 1000000000000-9999999999999                13
   // 10000000000000-99999999999999              14
   // 100000000000000-999999999999999            15
   // 1000000000000000-9999999999999999          16
   // 10000000000000000-99999999999999999        17
   // 100000000000000000-999999999999999999      18
   // 1000000000000000000-9999999999999999999    19
   // 10000000000000000000-18446744073709551615  20

   // ullong max is 18446744073709551615ULL -> 20 char
   // binary search the length of the resulting string

   if (value >= 100000000L)
   {
      if (value >= 10000000000000000L)
      {
         if (value >= 1000000000000000000L)
         {
            return (value >= 10000000000000000000UL) ? 20 : 19;
         } else // value < 1000000000000000000L
         {
            return (value >= 100000000000000000L) ? 18 : 17;
         } // end if
      } else if (value >= 1000000000000L)
      {
         if (value >= 100000000000000L)
         {
            return (value >= 1000000000000000) ? 16 : 15;
         } else // value < 100000000000000L
         {
            return (value >= 10000000000000L) ? 14 : 13;
         } // end if
      } else // value < 1000000000000L
      {
         if (value >= 10000000000L)
         {
            return (value >= 100000000000L) ? 12 : 11;
         } else // value < 10000000000L
         {
            return (value >= 1000000000L) ? 10 : 9;
         } // end if
      } // end if
   } // end if

   // value < 100000000L
   if (value >= 10000L)
   {
      if (value >= 1000000L)
      {
         return (value >= 10000000L) ? 8 : 7;
      } else // value < 100000000L
      {
         return (value >= 100000L) ? 6 : 5;
      } // end if
   } // end if

   // value < 10000L)
   if (value >= 100L)
   {
      return (value >= 1000L) ? 4 : 3;
   } // end if

   // value < 100
   return (value >= 10) ? 2 : 1;
} // int64_str_length


} // namespace celma::format::detail


// =====  END OF int64_str_length.hpp  =====

