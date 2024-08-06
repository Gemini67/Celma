
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2024 Rene Eng
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


#pragma once


#include "celma/common/detail/constexpr_string_concat.hpp"


namespace celma::common {


/// Concats 2 strings.
/// @tparam  Lhs  Type of the first string.
/// @tparam  Rhs  Type of the second string.
/// @param[in]  lhs  First string.
/// @param[in]  rhs  Second string.
/// @returns  The two strings concatenated to one string.
/// @since  0.10, 02.01.2017
template< class Lhs, class Rhs>
   [[nodiscard]] constexpr const detail::combined_string< Lhs, Rhs>
      string_concat( const Lhs& lhs, const Rhs& rhs)
{
   return detail::concat_impl( lhs, rhs,
                               detail::gen_seq< detail::string_length< Lhs>{}>{},
                               detail::gen_seq< detail::string_length< Rhs>{}>{});
} // string_concat


/// Concats 3 or more strings.
/// @tparam  T0  Type of the first string.
/// @tparam  T1  Type of the second string.
/// @tparam  Ts  Types of the remaining strings.
/// @param[in]  t0  First string.
/// @param[in]  t1  Second string.
/// @param[in]  ts  Remaining strings.
/// @returns  All the strings concatenated to one string.
/// @since  0.10, 02.01.2017
template< class T0, class T1, class... Ts>
   constexpr const detail::combined_string< T0, T1, Ts...>
      string_concat( const T0& t0, const T1& t1, const Ts&... ts)
{
   return string_concat( t0, string_concat( t1, ts...));
} // string_concat


/// Concat one string.
/// @tparam  T  Type of the string.
/// @param[in]  t  String.
/// @returns  String as passed in.
/// @since  0.10, 02.01.2017
template< class T> [[nodiscard]] constexpr
   const detail::combined_string< T> string_concat( const T& t)
{
   return string_concat( t, "");
} // string_concat


/// Concat nothing ;-)
/// @returns  Empty string.
/// @since  0.10, 02.01.2017
[[nodiscard]] constexpr const detail::combined_string<> string_concat()
{
   return string_concat( "");
} // string_concat


} // namespace celma::common


// =====  END OF constexpr_string_concat.hpp  =====

