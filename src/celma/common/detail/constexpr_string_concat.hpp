
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
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


#ifndef CELMA_COMMON_DETAIL_CONSTEXPR_STRING_CONCAT_HPP
#define CELMA_COMMON_DETAIL_CONSTEXPR_STRING_CONCAT_HPP


#include <utility>
#include <array>


namespace celma { namespace common { namespace detail {


/// Template alias for the type of an element of a sequence.
template< unsigned...> struct seq { using type = seq; };


/// Helper template to separate the elements of a sequence.
/// @tparam  N   The remaining number of elements in the sequence.
/// @tparam  Is  The remaining elements of the sequence.
/// @since  0.10, 02.01.2017
template< unsigned N, unsigned... Is>
   struct gen_seq_x: gen_seq_x< N - 1, N - 1, Is...>
{
}; // gen_seq_x


/// Helper template to separate the elements of a sequence.
/// @tparam  Is  The remaining elements of the sequence.
/// @since  0.10, 02.01.2017
template< unsigned... Is> struct gen_seq_x< 0, Is...>: seq< Is...>
{
}; // gen_seq_x


/// Template alias for the type of an element of a sequence.
template< unsigned N> using gen_seq = typename gen_seq_x< N>::type;


/// Template alias for the size of a sequence.
template< size_t S> using size = std::integral_constant< size_t, S>;


/// Returns the length of a C array.
///
/// @tparam  T
///    The type of the elements in the array.
/// @tparam  N
///    The size of the array.
/// @param[in]  Unnamed array.
/// @return  The length of the array.
/// @since  0.10, 02.01.2017
template< class T, size_t N> constexpr size< N> length( const T (&)[N])
{
   return {};
} // length


/// Returns the length of an std::array.
///
/// @tparam  T
///    The type of the elements in the array.
/// @tparam  N
///    The size of the array.
/// @param[in]  Unnamed array.
/// @return  The length of the array.
/// @since  0.10, 02.01.2017
template< class T, size_t N>
   constexpr size< N> length( std::array< T, N> const&)
{
   return {};
} // length


/// Template alias for the type of the length of a string.
template< class T> using length_t = decltype( length( std::declval< T>()));


/// Returns the size of an empty string.
///
/// @return  Always 0.
/// @since  0.10, 02.01.2017
constexpr size_t string_size()
{
   return 0;
} // string_size


/// Recursively calculates the length of a "string", which is here actually a
/// parameter pack.
///
/// @tparam  Ts
///    The type of the parameter pack.
/// @param[in]  i
///    Current index.
/// @param[in]  ts
///    The remaining string to determine the length of.
/// @return  The length of the string.
/// @since  0.10, 02.01.2017
template< class... Ts> constexpr size_t string_size( size_t i, Ts... ts)
{
   return (i > 0 ? i - 1 : 0) + string_size( ts...);
} // string_size


/// Template alias for the length of a string.
template< class... Ts>
   using string_length = size< string_size( length_t< Ts>{}... )>;


/// Template alias for the resulting string type.
template< class... Ts>
   using combined_string = std::array< char, string_length< Ts...>{} + 1>;


/// This one actually concats the strings.
///
/// @tparam  Lhs
///    The type of the first string.
/// @tparam  Rhs
///    The type of the second string.
/// @tparam  I1
///    The first sequence.
/// @tparam  I2
///    The second sequence.
/// @param[in]  lhs
///    The first string.
/// @param[in]  rhs
///    The second string.
/// @param[in]
///    First unnamed sequence.
/// @param[in]
///    Second unnamed sequence.
/// @return  All the strings concatenated to one string.
/// @since  0.10, 02.01.2017
template< class Lhs, class Rhs, unsigned... I1, unsigned... I2>
   constexpr const combined_string< Lhs, Rhs>
      concat_impl( const Lhs& lhs, const Rhs& rhs, seq< I1...>, seq< I2...>)
{
   // the '\0' adds to symmetry:
   return {{ lhs[ I1]..., rhs[ I2]..., '\0' }};
} // concat_impl


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_CONSTEXPR_STRING_CONCAT_HPP


// =====  END OF constexpr_string_concat.hpp  =====

