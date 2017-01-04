
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
/// See documentation of function celma::common::string_concat.
/// Code copied from
/// http://stackoverflow.com/questions/28708497/constexpr-to-concatenate-two-or-more-char-strings
/// answer from user Yakk. Thank you very much!


#ifndef CELMA_COMMON_CONSTEXPR_STRING_CONCAT_HPP
#define CELMA_COMMON_CONSTEXPR_STRING_CONCAT_HPP


#include "celma/common/detail/constexpr_string_concat.hpp"


namespace celma { namespace common {


/// Concats 2 strings.
/// @tparam  Lhs  The type of the first string.
/// @tparam  Rhs  The type of the second string.
/// @param[in]  lhs  The first string.
/// @param[in]  rhs  The second string.
/// @return  The two strings concatenated to one string.
/// @since  0.10, 02.01.2017
template< class Lhs, class Rhs>
   constexpr const detail::combined_string< Lhs, Rhs>
      string_concat( const Lhs& lhs, const Rhs& rhs)
{
   return detail::concat_impl( lhs, rhs,
                               detail::gen_seq< detail::string_length< Lhs>{}>{},
                               detail::gen_seq< detail::string_length< Rhs>{}>{});
} // string_concat


/// Concats 3 or more strings.
/// @tparam  T0  The type of the first string.
/// @tparam  T1  The type of the second string.
/// @tparam  Ts  The types of the remaining strings.
/// @param[in]  t0  The first string.
/// @param[in]  t1  The second string.
/// @param[in]  ts  The remaining strings.
/// @return  All the strings concatenated to one string.
/// @since  0.10, 02.01.2017
template< class T0, class T1, class... Ts>
   constexpr const detail::combined_string< T0, T1, Ts...>
      string_concat( const T0& t0, const T1& t1, const Ts&... ts)
{
   return string_concat( t0, string_concat( t1, ts...));
} // string_concat


/// Concat one string.
/// @tparam  T  The type of the string.
/// @param[in]  t  The string.
/// @return  String as passed in.
/// @since  0.10, 02.01.2017
template< class T>
   constexpr const detail::combined_string< T> string_concat( const T& t)
{
   return string_concat( t, "");
} // string_concat


/// Concat nothing ;-)
/// @return  Empty string.
/// @since  0.10, 02.01.2017
constexpr const detail::combined_string<> string_concat()
{
   return string_concat( "");
} // string_concat


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CONSTEXPR_STRING_CONCAT_HPP


// ===================  END OF constexpr_string_concat.hpp  ===================

