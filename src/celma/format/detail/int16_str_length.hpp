
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
/// See documentation of function celma::format::detail::int16_str_length().


#ifndef CELMA_FORMAT_DETAIL_INT16_STR_LENGTH_HPP
#define CELMA_FORMAT_DETAIL_INT16_STR_LENGTH_HPP


#include <cstdint>


namespace celma { namespace format { namespace detail {


/// Determines the number of characters that the string representation of a
/// short integer value requires.
/// @param[in]  orig_value  The value to determine the string length of.
/// @return  Length of the string format of the value.
/// @since  0.9, 29.11.2016
template< typename T> uint8_t int16_str_length( T orig_value)
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
} // end int16_str_length


} // namespace detail
} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_DETAIL_INT16_STR_LENGTH_HPP


// =======================  END OF int16_str_length.hpp  =======================

