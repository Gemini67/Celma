
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
/// Provides fast functions to convert an integer value into string format,
/// including grouping.<br>
/// For unsigned integers or positive values, use grouped_uint2str().<br>
/// For signed and negative values, use grouped_int2str_neg().<br>
/// For signed values that may be positive or negative, use
/// grouped_int2str().<br>
/// For the same functions but without grouping, see int2str() etc.



#ifndef CELMA_FORMAT_DETAIL_GROUPED_INT2STR_HPP
#define CELMA_FORMAT_DETAIL_GROUPED_INT2STR_HPP


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
/// @param[in]  group_char  The character to use to separate a group of digits.
/// @return  The value as string.
/// @since  0.9, 23.11.2016  (renamed from grouped_uint2str)
/// @since  0.6, 05.11.2016
std::string groupedUint64toString( uint64_t value, char group_char = '\'');


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
/// @param[in]  group_char  The character to use to separate a group of digits.
/// @return  The value as string.
/// @since  0.9, 23.11.2016  (renamed from grouped_int2str_neg)
/// @since  0.6, 05.11.2016
std::string groupedInt64negToString( int64_t value, char group_char = '\'');


/// Converts an integer value, signed, positive or negative, into string format
/// with grouping.
/// @param[in]  value       The value to convert.
/// @param[in]  group_char  The character to use to separate a group of digits.
/// @return  The string with the value.
/// @since  0.9, 23.11.2016  (renamed from grouped_int2str)
/// @since  0.6, 05.11.2016
inline std::string groupedInt64toString( int64_t value, char group_char = '\'')
{
   if (value < 0L)
      return groupedInt64negToString( value, group_char);
   if (value == 0L)
      return std::string( "0");
   return groupedUint64toString( value, group_char);
} // groupedInt64toString


/// Fast unsigned integer to string conversion with grouping into a caller-
/// supplied destination buffer.<br>
/// For long integers, the destination buffer must be at least 27 characters
/// long.
/// @param[out]  buffer      Pointer to the destination buffer to store the
///                          string form of the value in.
/// @param[in]   value       The value to convert.
/// @param[in]   group_char  The character to use to separate a group of digits.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 23.11.2016  (renamed from grouped_uint2str)
/// @since  0.6, 05.11.2016
int groupedUint64toString( char* buffer, uint64_t value, char group_char = '\'');


/// Fast integer to string conversion with grouping into a caller-supplied
/// destination buffer.<br>
/// For un/signed long integers, the destination buffer must be at least
/// 27 characters long.
/// @param[out]  buffer      Pointer to the destination buffer to store the
///                          string form of the value in.
/// @param[in]   value       The value to convert.
/// @param[in]   group_char  The character to use to separate a group of digits.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 23.11.2016  (renamed from grouped_int2str_neg)
/// @since  0.6, 05.11.2016
int groupedInt64negToString( char* buffer, int64_t value, char group_char = '\'');


/// Same conversion methods as above, but this time the functions take a
/// destination string/buffer pointer and return the length of the resulting
/// string.<br>
/// For un/signed long integers, the destination buffer must be at least
/// 21 characters long.
/// @param[out]  buffer      Pointer to the destination buffer to store the
///                          string form of the value in.
/// @param[in]   value       The value to convert.
/// @param[in]   group_char  The character to use to separate a group of digits.
/// @return  Number of characters written into the destination buffer.
/// @since  0.9, 23.11.2016  (renamed from grouped_int2str)
/// @since  0.6, 05.11.2016
inline int groupedInt64toString( char* buffer, int64_t value, char group_char = '\'')
{
   if (value < 0L)
      return groupedInt64negToString( buffer, value, group_char);

   if (value == 0L)
   {
      ::strcpy( buffer, "0");
      return 1;
   } // end if

   return groupedUint64toString( buffer, value, group_char);
} // groupedInt64toString


} // namespace detail
} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_DETAIL_GROUPED_INT2STR_HPP


// ===================  END OF grouped_int64_to_string.hpp  ===================

