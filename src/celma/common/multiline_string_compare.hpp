
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of function celma::common::multilineStringCompare()


#ifndef CELMA_COMMON_MULTILINE_STRING_COMPARE_HPP
#define CELMA_COMMON_MULTILINE_STRING_COMPARE_HPP


#include <string>


namespace celma { namespace common {


/// Compares two strings that contain a multi-line text if their contents are
/// equal.<br>
/// To simply check if the two strings are equal, std::string::compare() could
/// be used just as well. The advantage of this function is that, if the two
/// strings are not equal, it returns the information, at which position the
/// difference occurs.<br>
/// Of course the function also works for strings that contain only a single
/// line (i.e. no newline characters), the line number is always 1 in this
/// case.<br>
/// The out variables provide their values even if no difference was found,
/// e.g. the number of lines will be provided or the \a idx will return the
/// string length.
///
/// @param[out]  idx
///    Returns the index of the character in the strings that does not match.
/// @param[out]  line_nbr
///    Returns the number of the line where the difference was found, the first
///    line has number 1.
/// @param[out]  col
///    Returns the column in the line where the error was found, first position
///    has index 0.
/// @param[in]  str1
///    The first multi-line string to compare.
/// @param[in]  str2
///    The second multi-line string for the comparison.
/// @return
///    \c true if the contents of the two strings are identical.
/// @since
///    1.8.0, 24.07.2018
inline bool multilineStringCompare( std::string::size_type& idx,
   std::string::size_type& line_nbr,
   std::string::size_type& col,
   const std::string& str1,
   const std::string& str2)
{

   const auto  compare_length = std::min( str1.length(), str2.length());

   idx = 0;
   line_nbr = 1;
   col = 0;

   while ((idx < compare_length) && (str1[ idx] == str2[ idx]))
   {
      if (str1[ idx] == '\n')
      {
         ++line_nbr;
         col = 0;
      } else
      {
         ++col;
      } // end if
      ++idx;
   } // end while

   return (idx == compare_length) && (str1.length() == str2.length());
} // multilineStringCompare


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_MULTILINE_STRING_COMPARE_HPP


// =====  END OF multiline_string_compare.hpp  =====

