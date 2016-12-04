
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


// module header file include
#include "celma/format/detail/grouped_int8_to_string.hpp"


// C/OS library includes
#include <climits>


// project includes
#include "celma/format/detail/int8_str_length.hpp"


namespace celma { namespace format { namespace detail {


namespace {


/// The actual conversion function. Starts at the of the buffer, stores the last
/// digit there, divides the value and then does the same for the next (second-
/// but-last) digit.
/// @param[out]  buffer      Pointer to the last character position in the
///                          buffer.
/// @param[in]   value       The value to convert into the buffer.
/// @param[in]   result_len  Pre-determined length of the resulting string.
/// @since  0.9, 04.12.2016
inline void convert( char* buffer, uint8_t value, uint8_t result_len)
{

   // switch statement without breaks instead of a loop
   // starting with the last digit requires to know the length beforehand,
   // but then it's easy to convert digit by digit

   uint8_t  num_digits = 0;

   switch (result_len)
   {
   case 3:   *buffer-- = '0' + (value % 10);  value /= 10;
   case 2:   *buffer-- = '0' + (value % 10);  value /= 10;
   default:  *buffer-- = '0' + (value % 10);  value /= 10;
   } // end switch

} // convert


} // namespace


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
std::string groupedUint8toString( uint8_t value, char)
{

   const auto     result_len = int8_str_length( value);
   const uint8_t  grouped_result_len = result_len + (result_len - 1) / 3;
   std::string    result( grouped_result_len, '0');
   auto           buffer_end = const_cast< char*>( result.c_str()) + grouped_result_len - 1;

   convert( buffer_end, value, result_len);

   return result;
} // groupedUint8toString



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
std::string groupedInt8negToString( int8_t value, char)
{

   // convert into a positive value
   const uint8_t  abs_value = -value;

   // actually we create a string with result_len + 1
   // but then we would have to sub 1 again two times (so 1 add, 2 subs), so
   // this solution (1 add only) is a bit faster
   const auto     result_len = int8_str_length( abs_value);
   const uint8_t  grouped_result_len = result_len + (result_len - 1) / 3;

   // fill the string with dashes, so we already have the remaining 1 dash at
   // the beginning of the string when we're finished
   std::string    result( grouped_result_len + 1, '-');
   auto           buffer_end = const_cast< char*>( result.c_str()) + grouped_result_len;

   // value is positive now, can safely pass it to the function expecting
   // an unsigned value
   convert( buffer_end, abs_value, result_len);

   return result;
} // groupedInt8negToString



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
int groupedUint8toString( char* buffer, uint8_t value, char)
{

   const auto     result_len = int8_str_length( value);
   const uint8_t  grouped_result_len = result_len + (result_len - 1) / 3;
   char*          buffer_end = buffer + grouped_result_len - 1;


   ::memset( buffer, '0', grouped_result_len);
   buffer[ grouped_result_len] = '\0';

   convert( buffer_end, value, result_len);

   return grouped_result_len;
} // groupedUint8toString



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
int groupedInt8negToString( char* buffer, int8_t value, char)
{

   // convert into a positive value
   const uint8_t  abs_value = -value;

   // actually we create a string with result_len + 1
   // but then we would have to sub 1 again two times (so 1 add, 2 subs), so
   // this solution (1 add only) is a bit faster
   const auto     result_len = int8_str_length( abs_value);
   const uint8_t  grouped_result_len = result_len + (result_len - 1) / 3;
   char*          buffer_end = buffer + grouped_result_len;

   // fill the string with dashes, so we already have the remaining 1 dash at
   // the beginning of the string when we're finished
   ::memset( buffer, '-', grouped_result_len + 1);
   buffer[ grouped_result_len + 1] = '\0';

   // value is positive now, can safely pass it to the function expecting
   // an unsigned value
   convert( buffer_end, abs_value, result_len);

   return grouped_result_len + 1;
} // groupedInt8negToString



} // namespace detail
} // namespace format
} // namespace celma


// ===================  END OF grouped_int8_to_string.cpp  ====================

