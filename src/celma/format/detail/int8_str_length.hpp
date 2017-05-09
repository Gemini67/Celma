
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
/// See documentation of function celma::format::detail::int8_str_length().


#ifndef CELMA_FORMAT_DETAIL_INT8_STR_LENGTH_HPP
#define CELMA_FORMAT_DETAIL_INT8_STR_LENGTH_HPP


#include <cstdint>


namespace celma { namespace format { namespace detail {


/// Determines the number of characters that the string representation of a
/// 1 byte integer value requires.
/// @param[in]  orig_value  The value to determine the string length of.
/// @return  Length of the string format of the value.
/// @since  0.9, 29.11.2016
template< typename T> uint8_t int8_str_length( T orig_value)
{

   const auto  value = static_cast< uint8_t>( orig_value);

   // 0-9                                         1
   // 10-99                                       2
   // 100-255                                     3

   return (value >= 10) ? (value >= 100) ? 3 : 2 : 1;
} // end int8_str_length


} // namespace detail
} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_DETAIL_INT8_STR_LENGTH_HPP


// =======================  END OF int8_str_length.hpp  =======================

