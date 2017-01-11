
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of function celma::common::ensure_last().


#ifndef CELMA_COMMON_STRING_UTIL_HPP
#define CELMA_COMMON_STRING_UTIL_HPP


#include <string>


namespace celma { namespace common {


/// Makes sure that the last character in a non-empty string is \a last_char.
/// @param[in,out]  str        The string to check.
/// @param[in]      last_char  The last character that should be set at the end
///                            of the string, default set to '/' (for paths).
/// @since  0.12, 11.01.2017
inline void ensure_last( std::string& str, char last_char = '/')
{
   if (str.empty())
      return;

   if (str.back() != last_char)
   {
      str.append( 1, last_char);
   } // end if

} // ensure_last


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_STRING_UTIL_HPP


// =========================  END OF string_util.hpp  =========================

