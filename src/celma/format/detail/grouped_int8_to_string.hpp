
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
/// Provides fast functions to convert a 1 byte integer value into string format,
/// including grouping.<br>
/// Of course, grouping does never really happen for such values, the functions
/// are just provided for completeness.<br>
/// For unsigned 1 byte integers or positive values, use grouped_uint2str().<br>
/// For signed and negative values, use grouped_int2str_neg().<br>
/// For signed values that may be positive or negative, use
/// grouped_int2str().<br>
/// For the same functions but without grouping, see int2str() etc.



#ifndef CELMA_FORMAT_DETAIL_GROUPED_INT8_TO_STRING_HPP
#define CELMA_FORMAT_DETAIL_GROUPED_INT8_TO_STRING_HPP


#include <cstdint>
#include <cstring>
#include <string>


namespace celma { namespace format { namespace detail {


/// Fast method to convert an integer to string format with grouping:
/// - Determine the length of the resulting string.
/// - Prepare a result string, store pointer to the *end* of this string.
/// - For the pre-determined number of characters to create:
///   - Assign the character to the current position: value % 10.
///   - Move pointer to the next position (previous character in string).
///   - Divide the original value by 10.
///
/// @param[in]  value       The unsigned long integer value to convert into
///                         string format.
/// @param[in]  group_char  Unused here.
/// @return  The value as string.
/// @since  0.9, 04.12.2016
std::string groupedUint8toString( uint8_t value, char group_char = '\'');


/// Fast method to convert a signed, negative integer to string format with
/// grouping:
/// - Determine the length of the resulting string.
/// - Prepare a result string, store pointer to the *end* of this string.
/// - For the pre-determined number of characters to create:
///   - Assign the character to the current position: value % 10.
///   - Move pointer to the next position (previous character in string).
///   - Divide the original value by 10.
///
/// @param[in]  value       The signed long integer value to convert into string
///                         format.
/// @param[in]  group_char  Unused here.
/// @return  The value as string.
/// @since  0.9, 04.12.2016
std::string groupedInt8negToString( int8_t value, char group_char = '\'');


/// Converts an integer value, signed, positive or negative, into string format
/// with grouping.
/// @param[in]  value       The value to convert.
/// @param[in]  group_char  Unused here.
/// @return  The string with the value.
/// @since  0.9, 04.12.2016
inline std::string groupedInt8toString( int8_t value, char group_char = '\'')
{
   if (value < 0)
      return groupedInt8negToString( value, group_char);
   if (value == 0)
      return std::string( "0");
   return groupedUint8toString( value, group_char);
} // groupedInt8toString


/// Fast unsigned integer to string conversion with grouping into a caller-
/// supplied destination buffer.<br>
/// For long integers, the destination buffer must be at least 27 characters
/// long.
/// @param[out]  buffer      Pointer to the destination buffer to store the
///                          string form of the value in.
/// @param[in]   value       The value to convert.
/// @param[in]   group_char  Unused here.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 04.12.2016
int groupedUint8toString( char* buffer, uint8_t value, char group_char = '\'');


/// Fast integer to string conversion with grouping into a caller-supplied
/// destination buffer.<br>
/// For un/signed long integers, the destination buffer must be at least
/// 27 characters long.
/// @param[out]  buffer      Pointer to the destination buffer to store the
///                          string form of the value in.
/// @param[in]   value       The value to convert.
/// @param[in]   group_char  Unused here.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 04.12.2016
int groupedInt8negToString( char* buffer, int8_t value, char group_char = '\'');


/// Same conversion methods as above, but this time the functions take a
/// destination string/buffer pointer and return the length of the resulting
/// string.<br>
/// For un/signed long integers, the destination buffer must be at least
/// 21 characters long.
/// @param[out]  buffer      Pointer to the destination buffer to store the
///                          string form of the value in.
/// @param[in]   value       The value to convert.
/// @param[in]   group_char  Unused here.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 04.12.2016
inline int groupedInt8toString( char* buffer, int8_t value, char group_char = '\'')
{
   if (value < 0)
      return groupedInt8negToString( buffer, value, group_char);

   if (value == 0)
   {
      ::strcpy( buffer, "0");
      return 1;
   } // end if

   return groupedUint8toString( buffer, value, group_char);
} // groupedInt8toString


} // namespace detail
} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_DETAIL_GROUPED_INT8_TO_STRING_HPP


// ====================  END OF grouped_int8_to_string.hpp  ====================
