
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
/// Provides fast functions to convert an integer value into string format.<br>
/// For unsigned integers or positive values, use uint8toString().<br>
/// For signed and negative values, use int8negToString().<br>
/// For signed values that may be positive or negative, use int8toString().<br>
/// For the same functions but with grouping, see grouped_int8toString() etc.


#pragma once


#include <cstdint>
#include <cstring>
#include <string>


namespace celma::format::detail {


/// Fast method to convert an integer to string:
/// - Determine the length of the resulting string.
/// - Prepare a result string, store pointer to the *end* of this string.
/// - For the pre-determined number of characters to create:
///   - Assign the character to the current position: value % 10.
///   - Move pointer to the next position (previous character in string).
///   - Divide the original value by 10.
///
/// @param[in]  value  Unsigned long integer value to convert into string format.
/// @return  The value as string.
/// @since  0.9, 04.12.2016
[[nodiscard]] std::string uint8toString( uint8_t value);


/// Fast method to convert a signed, negative integer to string:
/// - Determine the length of the resulting string.
/// - Prepare a result string, store pointer to the *end* of this string.
/// - For the pre-determined number of characters to create:
///   - Assign the character to the current position: value % 10.
///   - Move pointer to the next position (previous character in string).
///   - Divide the original value by 10.
///
/// @param[in]  value  Signed long integer value to convert into string format.
/// @return  The value as string.
/// @since  0.9, 04.12.2016
[[nodiscard]] std::string int8negToString( int8_t value);


/// Converts an integer value, signed, positive or negative, into string format.
/// @param[in]  value  Value to convert.
/// @return  The string with the value.
/// @since  0.9, 04.12.2016
[[nodiscard]] inline std::string int8toString( const int8_t value)
{
   if (value < 0)
      return int8negToString( value);
   if (value == 0)
      return std::string( "0");
   return uint8toString( value);
} // end int8toString


/// Fast unsigned integer to string conversion into a caller-supplied
/// destination buffer.
/// For long integers, the destination buffer must be at least 10 characters
/// long.
/// @param[out]  buffer  Pointer to the destination buffer to store the string
///                      form of the value in.
/// @param[in]   value   Value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 04.12.2016
int uint8toString( char* buffer, uint8_t value);


/// Fast integer to string conversion into a caller-supplied destination
/// buffer.
/// For un/signed long integers, the destination buffer must be at least
/// 11 characters long.
/// @param[out]  buffer  Pointer to the destination buffer to store the string
///                      form of the value in.
/// @param[in]   value   Value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 04.12.2016
int int8negToString( char* buffer, int8_t value);


/// Same conversion methods as above, but this time the functions take a
/// destination string/buffer pointer and return the length of the resulting
/// string.<br>
/// For un/signed long integers, the destination buffer must be at least
/// 11 characters long.
/// @param[out]  buffer  Pointer to the destination buffer to store the string
///                      form of the value in.
/// @param[in]   value   Value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 04.12.2016
inline int int8toString( char* buffer, const int8_t value)
{
   if (value < 0)
      return int8negToString( buffer, value);

   if (value == 0)
   {
      ::strcpy( buffer, "0");
      return 1;
   } // end if

   return uint8toString( buffer, value);
} // end int8toString


} // namespace celma::format::detail


// =====  END OF int8_to_string.hpp  =====

