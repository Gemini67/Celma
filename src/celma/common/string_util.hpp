
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
/// See documentation of functions celma::common::ensure_last(),
/// celma::common::remove_to_if() and all its variants.


#ifndef CELMA_COMMON_STRING_UTIL_HPP
#define CELMA_COMMON_STRING_UTIL_HPP


#include <string>


namespace celma { namespace common {


/// Makes sure that the last character in a non-empty string is \a last_char.
/// @param[in,out]  str        The string to check.
/// @param[in]      last_char  The last character that should be set at the end
///                            of the string, default set to '/' (for paths).
/// @since  0.3, 19.06.2016
inline void ensure_last( std::string& str, char last_char = '/')
{

   if (str.empty())
      return;

   if (str.back() != last_char)
   {
      str.append( 1, last_char);
   } // end if

} // end ensure_last


/// Removes all leading characters from the string \a str up to and including
/// the first or last occurrence of the specified predicate \a pred.<br>
/// If the character \a pred is not found in the string, the contents remain
/// unchanged.
/// @param[in,out]  str          The string to remove the leading part
///                              eventually.
/// @param[in]      pred         The character up to which's first or last
///                              occurrence the contents should be removed.
/// @param[in]      until_first  If set then everything to the last occurrence
///                              of \a pred is removed (default), otherwise only
///                              up to the first occurrence.
/// @param[in]      including    If set removes the contents up to and including
///                              the search predicate, otherwise the predicate
///                              remains in the string.
/// @since  0.3, 19.06.2016
inline void remove_to_if( std::string& str, char pred, bool until_first = false,
                          bool including = false)
{

   if (str.empty() || (pred == '\0'))
      return;

   auto const  pos = until_first ? str.find( pred) : str.find_last_of( pred);

   if (pos != std::string::npos)
      str.erase( 0, pos + static_cast< int>( including));

} // end remove_to_if


// shortcut functions
// use different function names instead of long parameter lists


/// Shortcut (less parameters) for calling remove_to_if() to remove up to and
/// including the first occurence of the predicate.
/// @param[in,out]  str   The string to remove the leading part eventually.
/// @param[in]      pred  The character to search for.
/// @since  0.3, 19.06.2016
inline void remove_to_if_first_incl( std::string& str, char pred)
{
   remove_to_if( str, pred, true, true);
} // end remove_to_if_first_incl


/// Shortcut (less parameters) for calling remove_to_if() to remove up to
/// (excluding) the first occurence of the predicate.
/// @param[in,out]  str   The string to remove the leading part eventually.
/// @param[in]      pred  The character to search for.
/// @since  0.3, 19.06.2016
inline void remove_to_if_first_excl( std::string& str, char pred)
{
   remove_to_if( str, pred, true);
} // end remove_to_if_first_excl


/// Shortcut (less parameters) for calling remove_to_if() to remove up to and
/// including the last occurence of the predicate.
/// @param[in,out]  str   The string to remove the leading part eventually.
/// @param[in]      pred  The character to search for.
/// @since  0.3, 19.06.2016
inline void remove_to_if_last_incl( std::string& str, char pred)
{
   remove_to_if( str, pred, false, true);
} // end remove_to_if_last_incl


/// Shortcut (less parameters) for calling remove_to_if() to remove up to
/// (excluding) the last occurence of the predicate.
/// @param[in,out]  str   The string to remove the leading part eventually.
/// @param[in]      pred  The character to search for.
/// @since  0.3, 19.06.2016
inline void remove_to_if_last_excl( std::string& str, char pred)
{
   remove_to_if( str, pred);
} // end remove_to_if_last_excl


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_STRING_UTIL_HPP


// =========================  END OF string_util.hpp  =========================

