
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of functions celma::common::contains().


#pragma once


#include <algorithm>
#include <iterator>


namespace celma::common {


/// Base mplementations usable for containers like vector or array: Check if the
/// container contains the given value.
///
/// @tparam  C
///    The type of the container to search the value in.
/// @param[in]  container
///    The container to search the value in.
/// @param[in]  v
///    The value to search for.
/// @returns
///    \c true if the container contains the given value.
/// @since
///    1.11.0, 22.08.2018
template< typename C> [[nodiscard]]
   bool contains( const C& container, const typename C::const_reference v)
{
   return std::find( std::cbegin( container), std::cend( container), v)
      != std::cend( container);
} // contains


/// Overload for C arrays.
///
/// @tparam  T
///    The type of the values stored in the array.
/// @tparam  N
///    Number of elements in the array.
/// @param[in]  arr
///    The array to search the value in.
/// @param[in]  v
///    The value to search for.
/// @returns
///    \c true if the array contains the given value.
/// @since
///    1.26.0, 29.04.2019
template< typename T, size_t N> [[nodiscard]]
   bool contains( const T (&arr)[ N], const T& v)
{
   return std::find( arr, arr + N, v) != arr + N;
} // contains


/// Overload for partially filled C arrays.
///
/// @tparam  T
///    The type of the values stored in the array.
/// @tparam  N
///    Number of elements in the array.
/// @param[in]  arr
///    The array to search the value in.
/// @param[in]  n
///    Number of elements in the array to check.
/// @param[in]  v
///    The value to search for.
/// @returns
///    \c true if the array contains the given value.
/// @since
///    1.26.0, 29.04.2019
template< typename T, size_t N> [[nodiscard]]
   bool contains( const T (&arr)[ N], size_t n, const T& v)
{
   return std::find( arr, arr + n, v) != arr + n;
} // contains


} // namespace celma::common


// =====  END OF contains.hpp  =====

