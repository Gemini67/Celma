
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
/// Provides fast functions to convert an integer value into string format.<br>
/// For unsigned integers or positive values, use uint32toString().<br>
/// For signed and negative values, use int32negToString().<br>
/// For signed values that may be positive or negative, use int32toString().<br>
/// For the same functions but with grouping, see grouped_int32toString() etc.


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
/// @param[in]  value  The unsigned long integer value to convert into string
///                    format.
/// @return  The value as string.
/// @since  0.9, 28.11.2016
[[nodiscard]] std::string uint32toString( uint32_t value);


/// Fast method to convert a signed, negative integer to string:
/// - Determine the length of the resulting string.
/// - Prepare a result string, store pointer to the *end* of this string.
/// - For the pre-determined number of characters to create:
///   - Assign the character to the current position: value % 10.
///   - Move pointer to the next position (previous character in string).
///   - Divide the original value by 10.
///
/// @param[in]  value  The signed long integer value to convert into string
///                    format.
/// @return  The value as string.
/// @since  0.9, 28.11.2016
[[nodiscard]] std::string int32negToString( int32_t value);


/// Converts an integer value, signed, positive or negative, into string format.
/// @param[in]  value  The value to convert.
/// @return  The string with the value.
/// @since  0.9, 28.11.2016
[[nodiscard]] inline std::string int32toString( const int32_t value)
{
   if (value < 0L)
      return int32negToString( value);
   if (value == 0L)
      return std::string( "0");
   return uint32toString( value);
} // int32toString


/// Fast unsigned integer to string conversion into a caller-supplied
/// destination buffer.
/// For long integers, the destination buffer must be at least 10 characters
/// long.
/// @param[in]  buffer  Pointer to the destination buffer to store the string
///                     form of the value in.
/// @param[in]  value   The value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 28.11.2016
int uint32toString( char* buffer, uint32_t value);


/// Fast integer to string conversion into a caller-supplied destination
/// buffer.
/// For un/signed long integers, the destination buffer must be at least
/// 11 characters long.
/// @param[in]  buffer  Pointer to the destination buffer to store the string
///                     form of the value in.
/// @param[in]  value   The value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 28.11.2016
int int32negToString( char* buffer, int32_t value);


/// Same conversion methods as above, but this time the functions take a
/// destination string/buffer pointer and return the length of the resulting
/// string.<br>
/// For un/signed long integers, the destination buffer must be at least
/// 11 characters long.
/// @param[in]  buffer  Pointer to the destination buffer to store the string
///                     form of the value in.
/// @param[in]  value   The value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 28.11.2016
inline int int32toString( char* buffer, const int32_t value)
{
   if (value < 0L)
      return int32negToString( buffer, value);

   if (value == 0L)
   {
      ::strcpy( buffer, "0");
      return 1;
   } // end if

   return uint32toString( buffer, value);
} // int32toString


} // namespace celma::format::detail


// =====  END OF int32_to_string.hpp  =====

