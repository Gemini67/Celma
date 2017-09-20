
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// This file provides two families of grouped_int2string() functions:
/// - The first family takes the value to convert plus the separator character
///   as parameters and returns the string with the converted value.
/// - The second family takes a pointer to the destination buffer, the value to
///   convert and the separator character as parameters.
/// Implemented are two 'families' of functions, each using the feature called
/// 'tag dispatch' to call the corresponding function depending on the size and
/// the sign of the value type.<br>
/// Using the functions is simply: Just call grouped_int2string().


#ifndef CELMA_FORMAT_GROUPED_INT2STRING_HPP
#define CELMA_FORMAT_GROUPED_INT2STRING_HPP


#include <string>
#include <type_traits>
#include "celma/format/detail/grouped_int8_to_string.hpp"
#include "celma/format/detail/grouped_int16_to_string.hpp"
#include "celma/format/detail/grouped_int32_to_string.hpp"
#include "celma/format/detail/grouped_int64_to_string.hpp"


namespace celma { namespace format {


#define  TEMPLATE_ENABLE_IF( b, s, r) \
   template< typename T> \
      std::enable_if_t< std::is_integral< T>::value && (sizeof( T) == b) && \
                        std::is_signed< T>::value == s, \
                        r>

#define  FUNCTION_ENABLED( b, s, f) \
   TEMPLATE_ENABLE_IF( b, s, std::string) \
      grouped_int2string( T value, char group_char = '\'') \
   { \
      return detail::f( value, group_char); \
   }

#define  BUFFER_FUNCTION_ENABLED( b, s, f) \
   TEMPLATE_ENABLE_IF( b, s, int) \
      grouped_int2string( char* buffer, T value, char group_char = '\'') \
   { \
      return detail::f( buffer, value, group_char); \
   }

#define  SIGNED_FUNCTIONS( b, f) \
   FUNCTION_ENABLED( b, true, f) \
   BUFFER_FUNCTION_ENABLED( b, true, f)

#define  UNSIGNED_FUNCTIONS( b, f) \
   FUNCTION_ENABLED( b, false, f) \
   BUFFER_FUNCTION_ENABLED( b, false, f)


SIGNED_FUNCTIONS( 1, groupedInt8toString)
UNSIGNED_FUNCTIONS( 1, groupedUint8toString)
SIGNED_FUNCTIONS( 2, groupedInt16toString)
UNSIGNED_FUNCTIONS( 2, groupedUint16toString)
SIGNED_FUNCTIONS( 4, groupedInt32toString)
UNSIGNED_FUNCTIONS( 4, groupedUint32toString)
SIGNED_FUNCTIONS( 8, groupedInt64toString)
UNSIGNED_FUNCTIONS( 8, groupedUint64toString)


#undef  SIGNED_FUNCTIONS
#undef  UNSIGNED_FUNCTIONS
#undef  TEMPLATE_ENABLE_IF


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_GROUPED_INT2STRING_HPP


// ======================  END OF grouped_int2string.hpp  ======================

