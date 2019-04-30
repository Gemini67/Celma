
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of functions celma::common::contains().


#ifndef CELMA_COMMON_CONTAINS_HPP
#define CELMA_COMMON_CONTAINS_HPP


#include <algorithm>
#include <iterator>


namespace celma { namespace common {


/// Base mplementations usable for all containers: Check if the container
/// contains the given value.<br>
/// For containers that provide their own find method, one of the following
/// overloads should be used.
///
/// @tparam  C
///    The type of the container to search the value in.
/// @param[in]  container
///    The container to search the value in.
/// @param[in]  v
///    The value to search for.
/// @return
///    \c true if the container contains the given value.
/// @since
///    1.11.0, 22.08.2018
template< typename C>
   bool contains( const C& container, const typename C::const_reference v)
{
   return std::find( std::cbegin( container), std::cend( container), v)
      != std::cend( container);
} // contains


/// Overload for containers using the value as key, e.g. std::set<>: Check if
/// the container contains the given value.
///
/// @tparam  T
///    The type of the value/key that is stored in the container.
/// @tparam  C
///    The type of the functor used for comparisons.
/// @tparam  A
///    The type of the allocator used by the container.
/// @tparam  S
///    The type of the container to search the value in.
/// @param[in]  container
///    The container to search the value in.
/// @param[in]  v
///    The value to search for.
/// @return
///    \c true if the container contains the given value.
/// @since
///    1.11.0, 22.08.2018
template< typename T, typename C, typename A,
   template< typename, typename, typename> class S>
      bool contains( const S< T, C, A>& container, const T& v)
{
   return container.find( v) != container.end();
} // contains


/// Overload for containers using the value as key, e.g. std::set<>: Check if
/// the container contains the given value.<br>
/// Also serves as an overload for containers using a hash function to store the
/// values/keys, e.g. std::unordered_set<>: Check if the container contains the
/// given value.
///
/// @tparam  K
///    The type of the used by the container.
/// @tparam  V
///    The type of the values stored in the container.
/// @tparam  C
///    The type of the functor used for comparisons.
/// @tparam  A
///    The type of the allocator used by the container.
/// @tparam  S
///    The type of the container to search the value in.
/// @param[in]  container
///    The container to search the value in.
/// @param[in]  k
///    The key to search for.
/// @return
///    \c true if the container contains the given key.
/// @since
///    1.11.0, 22.08.2018
template< typename K, typename V, typename C, typename A,
   template< typename, typename, typename, typename> class S>
      bool contains( const S< K, V, C, A>& container, const K& k)
{
   return container.find( k) != container.end();
} // contains


/// Overload for containers using a hash function to store the key/values pairs,
/// e.g. std::unordered_map<>: Check if the container contains the given value.
///
/// @tparam  K
///    The type of the used by the container.
/// @tparam  V
///    The type of the values stored in the container.
/// @tparam  H
///    The type of the hash function.
/// @tparam  E
///    The type of the functor used for equality comparisons.
/// @tparam  A
///    The type of the allocator used by the container.
/// @tparam  S
///    The type of the container to search the value in.
/// @param[in]  container
///    The container to search the value in.
/// @param[in]  k
///    The key to search for.
/// @return
///    \c true if the container contains the given key.
/// @since
///    1.11.0, 22.08.2018
template< typename K, typename V, typename H, typename E, typename A,
   template< typename, typename, typename, typename, typename> class S>
         bool contains( const S< K, V, H, E, A>& container, const K& k)
{
   return container.find( k) != container.end();
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
/// @return
///    \c true if the array contains the given value.
/// @since
///    x.y.z, 29.04.2019
template< typename T, size_t N> bool contains( const T (&arr)[ N], const T& v)
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
/// @return
///    \c true if the array contains the given value.
/// @since
///    x.y.z, 29.04.2019
template< typename T, size_t N>
   bool contains( const T (&arr)[ N], size_t n, const T& v)
{
   return std::find( arr, arr + n, v) != arr + n;
} // contains


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CONTAINS_HPP


// =====  END OF contains.hpp  =====

