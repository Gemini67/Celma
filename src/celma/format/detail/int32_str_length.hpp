
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
/// See documentation of function celma::format::detail::int32_str_length().


#ifndef CELMA_FORMAT_DETAIL_INT32_STR_LENGTH_HPP
#define CELMA_FORMAT_DETAIL_INT32_STR_LENGTH_HPP


#include <cstdint>


namespace celma { namespace format { namespace detail {


/// Determines the number of characters that the string representation of an
/// integer value requires.
/// @param[in]  orig_value  The value to determine the string length of.
/// @return  Length of the string format of the value.
/// @since  0.9, 28.11.2016
template< typename T> uint8_t int32_str_length( T orig_value)
{

   const auto  value = static_cast< uint32_t>( orig_value);

   // 0-9                                         1
   // 10-99                                       2
   // 100-999                                     3
   // 1000-9999                                   4
   // 10000-99999                                 5
   // 100000-999999                               6
   // 1000000-9999999                             7
   // 10000000-99999999                           8
   // 100000000-999999999                         9
   // 1000000000-4294967295                      10

   // uint max is 4294967295 -> 10 char
   // binary search the length of the resulting string

   if (value >= 100000)
   {
      if (value >= 10000000)
      {
         if (value >= 100000000)
         {
            return (value >= 1000000000) ? 10 : 9;
         } else // value < 100000000
         {
            return 8;
         } // end if
      } else
      {
         return (value >= 1000000) ? 7 : 6;
      } // end if
   } // end if

   // value < 100000
   if (value >= 100)
   {
      if (value >= 1000)
      {
         return (value >= 10000) ? 5 : 4;
      } else // value < 1000
      {
         return 3;
      } // end if
   } // end if

   // value < 100
   return (value >= 10) ? 2 : 1;
} // end int32_str_length


} // namespace detail
} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_DETAIL_INT32_STR_LENGTH_HPP


// =======================  END OF int32_str_length.hpp  =======================

