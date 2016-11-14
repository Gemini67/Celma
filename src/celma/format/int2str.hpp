
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
/// For unsigned integers or positive values, use uint2str().<br>
/// For signed and negative values, use int2str_neg().<br>
/// For signed values that may be positive or negative, use int2str().<br>
/// For the same functions but with grouping, see grouped_int2str() etc.


#ifndef CELMA_FORMAT_INT2STR_HPP
#define CELMA_FORMAT_INT2STR_HPP


#include <cstdint>
#include <cstring>
#include <string>


namespace celma { namespace format {


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
/// @since  0.6, 05.11.2016
std::string uint2str( uint64_t value);


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
/// @since  0.6, 05.11.2016
std::string int2str_neg( int64_t value);


/// Converts an integer value, signed, positive or negative, into string format.
/// @param[in]  value  The value to convert.
/// @return  The string with the value.
/// @since  0.6, 05.11.2016
inline std::string int2str( int64_t value)
{
   if (value < 0L)
      return int2str_neg( value);
   if (value == 0L)
      return std::string( "0");
   return uint2str( value);
} // end int2str


/// Fast unsigned integer to string conversion into a caller-supplied
/// destination buffer.
/// For long integers, the destination buffer must be at least 21 characters
/// long.
/// @param[in]  buffer  Pointer to the destination buffer to store the string
///                     form of the value in.
/// @param[in]  value   The value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.6, 05.11.2016
int uint2str( char* buffer, uint64_t value);


/// Fast integer to string conversion into a caller-supplied destination
/// buffer.
/// For un/signed long integers, the destination buffer must be at least
/// 21 characters long.
/// @param[in]  buffer  Pointer to the destination buffer to store the string
///                     form of the value in.
/// @param[in]  value   The value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.6, 05.11.2016
int int2str_neg( char* buffer, int64_t value);


/// Same conversion methods as above, but this time the functions take a
/// destination string/buffer pointer and return the length of the resulting
/// string.<br>
/// For un/signed long integers, the destination buffer must be at least
/// 21 characters long.
/// @param[in]  buffer  Pointer to the destination buffer to store the string
///                     form of the value in.
/// @param[in]  value   The value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.6, 05.11.2016
inline int int2str( char* buffer, int64_t value)
{
   if (value < 0L)
      return int2str_neg( buffer, value);

   if (value == 0L)
   {
      ::strcpy( buffer, "0");
      return 1;
   } // end if

   return uint2str( buffer, value);
} // end int2str


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_INT2STR_HPP


// ===========================  END OF int2str.hpp  ===========================

