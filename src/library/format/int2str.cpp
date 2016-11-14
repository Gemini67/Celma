
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


// module header file include
#include "celma/format/int2str.hpp"


// C/OS library includes
#include <climits>


// project includes
#include "celma/format/detail/int_str_length.hpp"


namespace celma { namespace format {


namespace {


/// The actual conversion function. Starts at the of the buffer, stores the last
/// digit there, divides the value and then does the same for the next (second-
/// but-last) digit.
/// @param[out]  buffer      Pointer to the last character position in the
///                          buffer.
/// @param[in]   value       The value to convert into the buffer.
/// @param[in]   result_len  Pre-determined length of the resulting string.
/// @since  0.6, 05.11.2016
inline void convert( char* buffer, uint64_t value, uint8_t result_len)
{

   // switch statement without breaks instead of a loop
   // starting with the last digit requires to know the length beforehand,
   // but then it's easy to convert digit by digit
   switch (result_len)
   {
   case 20:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 19:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 18:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 17:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 16:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 15:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 14:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 13:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 12:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 11:  *buffer-- = '0' + (value % 10);  value /= 10;
   case 10:  *buffer-- = '0' + (value % 10);  value /= 10;
   case  9:  *buffer-- = '0' + (value % 10);  value /= 10;
   case  8:  *buffer-- = '0' + (value % 10);  value /= 10;
   case  7:  *buffer-- = '0' + (value % 10);  value /= 10;
   case  6:  *buffer-- = '0' + (value % 10);  value /= 10;
   case  5:  *buffer-- = '0' + (value % 10);  value /= 10;
   case  4:  *buffer-- = '0' + (value % 10);  value /= 10;
   case  3:  *buffer-- = '0' + (value % 10);  value /= 10;
   case  2:  *buffer-- = '0' + (value % 10);  value /= 10;
   default:  *buffer   = '0' + value;
   } // end switch

} // convert


} // namespace


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
std::string uint2str( uint64_t value)
{

   const uint8_t  result_len = detail::int_str_length( value);
   std::string    result( result_len, '0');
   char*          buffer_end = const_cast< char*>( result.c_str()) + result_len - 1;


   convert( buffer_end, value, result_len);

   return result;
} // uint2str



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
std::string int2str_neg( int64_t value)
{

   // convert into a positive value
   const uint64_t  abs_value = -value;

   // actually we create a string with result_len + 1
   // but then we would have to sub 1 again two times (so 1 add, 2 subs), so
   // this solution (1 add only) is a bit faster
   const uint8_t  result_len = detail::int_str_length( abs_value);

   // fill the string with dashes, so we already have the remaining 1 dash at
   // the beginning of the string when we're finished
   std::string    result( result_len + 1, '-');
   char*          buffer_end = const_cast< char*>( result.c_str()) + result_len;

   // value is positive now, can safely pass it to the function expecting
   // an unsigned value
   convert( buffer_end, abs_value, result_len);

   return result;
} // int2str_neg



/// Fast unsigned integer to string conversion into a caller-supplied
/// destination buffer.
/// For long integers, the destination buffer must be at least 21 characters
/// long.
/// @param[in]  buffer  Pointer to the destination buffer to store the string
///                     form of the value in.
/// @param[in]  value   The value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.6, 05.11.2016
int uint2str( char* buffer, uint64_t value)
{

   const uint8_t  result_len = detail::int_str_length( value);
   char*          buffer_end = buffer + result_len - 1;


   ::memset( buffer, '0', result_len);
   buffer[ result_len] = '\0';

   convert( buffer_end, value, result_len);

   return result_len;
} // uint2str



/// Fast integer to string conversion into a caller-supplied destination
/// buffer.
/// For un/signed long integers, the destination buffer must be at least
/// 21 characters long.
/// @param[in]  buffer  Pointer to the destination buffer to store the string
///                     form of the value in.
/// @param[in]  value   The value to convert.
/// @return  Number of characters written into the destination buffer.
/// @since  0.6, 05.11.2016
int int2str_neg( char* buffer, int64_t value)
{

   // convert into a positive value
   const uint64_t  abs_value = -value;

   // actually we create a string with result_len + 1
   // but then we would have to sub 1 again two times (so 1 add, 2 subs), so
   // this solution (1 add only) is a bit faster
   const uint8_t  result_len = detail::int_str_length( abs_value);
   char*          buffer_end = buffer + result_len;

   // fill the string with dashes, so we already have the remaining 1 dash at
   // the beginning of the string when we're finished
   ::memset( buffer, '-', result_len + 1);
   buffer[ result_len + 1] = '\0';

   // value is positive now, can safely pass it to the function expecting
   // an unsigned value
   convert( buffer_end, abs_value, result_len);

   return result_len + 1;
} // int2str_neg



} // namespace format
} // namespace celma


// ===========================  END OF int2str.cpp  ===========================

