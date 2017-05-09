
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
/// This file provides two families of int2string() functions:
/// - The first family takes only the value to convert as parameter and returns
///   a string with the converted value.
/// - The second family takes a pointer to the destination buffer and the value
///   to convert as parameters.
/// Implemented are two 'families' of functions, each using the feature called
/// 'tag dispatch' to call the corresponding function depending on the size and
/// the sign of the value type.<br>
/// Using the functions is simple: Just call int2string().


#ifndef CELMA_FORMAT_INT2STRING_HPP
#define CELMA_FORMAT_INT2STRING_HPP


#include <string>
#include <type_traits>
#include "celma/format/detail/int8_to_string.hpp"
#include "celma/format/detail/int16_to_string.hpp"
#include "celma/format/detail/int32_to_string.hpp"
#include "celma/format/detail/int64_to_string.hpp"


namespace celma { namespace format {


#define  TEMPLATE_ENABLE_IF( b, s, r) \
   template< typename T> \
      std::enable_if_t< std::is_integral< T>::value && (sizeof( T) == b) && \
                        std::is_signed< T>::value == s, \
                        r>

#define  FUNCTION_ENABLED( b, s, f) \
   TEMPLATE_ENABLE_IF( b, s, std::string) \
      int2string( T value) \
   { \
      return detail::f( value); \
   }

#define  BUFFER_FUNCTION_ENABLED( b, s, f) \
   TEMPLATE_ENABLE_IF( b, s, int) \
      int2string( char* buffer, T value) \
   { \
      return detail::f( buffer, value); \
   }

#define  SIGNED_FUNCTIONS( b, f) \
   FUNCTION_ENABLED( b, true, f); \
   BUFFER_FUNCTION_ENABLED( b, true, f)

#define  UNSIGNED_FUNCTIONS( b, f) \
   FUNCTION_ENABLED( b, false, f); \
   BUFFER_FUNCTION_ENABLED( b, false, f)


SIGNED_FUNCTIONS( 1, int8toString);
UNSIGNED_FUNCTIONS( 1, uint8toString);
SIGNED_FUNCTIONS( 2, int16toString);
UNSIGNED_FUNCTIONS( 2, uint16toString);
SIGNED_FUNCTIONS( 4, int32toString);
UNSIGNED_FUNCTIONS( 4, uint32toString);
SIGNED_FUNCTIONS( 8, int64toString);
UNSIGNED_FUNCTIONS( 8, uint64toString);


#undef  SIGNED_FUNCTIONS
#undef  UNSIGNED_FUNCTIONS
#undef  TEMPLATE_ENABLE_IF


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_INT2STRING_HPP


// ==========================  END OF int2string.hpp  ==========================

