
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template functions
/// - celma::format::div2unit()
/// - celma::format::numDivs2Name()
/// - celma::format::formatSize()


#pragma once


#include <cstdio>
#include <iomanip>
#include <iostream>


namespace celma::format {


/// Divides the given value by 1024 (1 kibibyte) until it is less than 1024, and
/// returns the number of divisions that were required.
///
/// @param[in,out]  value  The value to normalise, returns the remaining value.
/// @return  Number of divisions required to normalise the value.
/// @since  1.24.0, 17.04.2019
template< typename T> int div2unit( T& value)
{

   static constexpr T  divisor = static_cast< T>( 1024);
   int  num_divs = 0;

   while (value >= divisor)
   {
      value /= divisor;
      ++num_divs;
   } // end while

   return num_divs;
} // div2unit


/// Returns the name of the unit that corresponds to the number of divisions
/// required to normalise the value.
///
/// @param[in]  num_divs  Number of divisions that were required.
/// @return  Pointer to the char string with the name of the unit.
/// @since  1.24.0, 17.04.2019
[[nodiscard]] inline const char* numDivs2Name( const int num_divs)
{

   switch (num_divs)
   {
   case 0:   return "bytes";
   case 1:   return "kbytes";
   case 2:   return "Mbytes";
   case 3:   return "Gbytes";
   case 4:   return "Tbytes";
   case 5:   return "Pbytes";
   case 6:   return "Ebytes";
   default:  return "out of range";
   } // end switch
} // numDivs2Name


/// Completely formats the given size as "nnnn.n <units>".
///
/// @tparam  T  Type of the value to format.
/// @param[out]  os
///    Stream to write the formatted value to.
/// @param[in]  value
///    Value to format.
/// @since  1.24.0, 17.04.2019
template< typename T> void formatSize( std::ostream& os, const T& value)
{

   double     d_value = static_cast< double>( value);
   const int  num_divs = div2unit( d_value);

   os << std::fixed << std::setw( 6) << std::setprecision( 1) << d_value
      << " " << numDivs2Name( num_divs);

} // formatSize


/// Completely formats the given value as defined by the given format string
/// (using sprintf).
/// The format string must contain the format definition for a floating point
/// value and a string, in that order.
///
/// @tparam  T  Type of the value to format.
/// @param[out]  buff
///    Pointer to the buffer to write into.
/// @param[in]   format
///    Format string to use.
/// @param[in]   value
///    Value to format.
/// @since  1.24.0, 17.04.2019
template< typename T> void formatSize( char* buff, const char* format,
   const T value)
{

   double     d_value = static_cast< double>( value);
   const int  num_divs = div2unit( d_value);

   ::sprintf( buff, format, d_value, numDivs2Name( num_divs));

} // formatSize


/// Helper function to format a value with a default format string:
/// Completely formats the given size as "nnnn.n <units>".
///
/// @tparam  T  The type of the value to format.
/// @param[in]  buff
///    Pointer to the buffer to print the formatted value into.
/// @param[in]  value
///    The value to format.
/// @since  1.24.0, 17.04.2019
template< typename T> void formatSize( char* buff, const T value)
{

   formatSize( buff, "%6.1f %s", value);

} // formatSize


} // namespace celma::format


// =====  END OF size_handling.hpp  =====

