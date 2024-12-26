
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::@@@.


#ifndef CELMA_COMMON_CONTAINER_TRAITS_HPP
#define CELMA_COMMON_CONTAINER_TRAITS_HPP


#include <map>
#include <set>
#include <unordered_map>


namespace celma { namespace common {


/*
template< template< typename...> class Container>
   struct is_ordered : std::false_type {};

template<> struct is_ordered< std::map>      : std::true_type {};
template<> struct is_ordered< std::set>      : std::true_type {};
template<> struct is_ordered< std::multimap> : std::true_type {};
template<> struct is_ordered< std::multiset> : std::true_type {};


template< template< typename...> class Container>
   struct has_key_value : std::false_type {};

template<> struct has_key_value< std::map>                : std::true_type {};
template<> struct has_key_value< std::multimap>           : std::true_type {};
template<> struct has_key_value< std::unordered_map>      : std::true_type {};
template<> struct has_key_value< std::unordered_multimap> : std::true_type {};
*/


template< typename T> struct is_ordered : std::false_type {};

template< typename K, typename V> struct is_ordered< std::map< K, V>>:
   std::true_type {};
template< typename T> struct is_ordered< std::set< T>>:
   std::true_type {};
template< typename K, typename V> struct is_ordered< std::multimap< K, V>>:
   std::true_type {};
template< typename T> struct is_ordered< std::multiset< T>>:
   std::true_type {};


template< typename T> struct has_key_value : std::false_type {};

template< typename K, typename V> struct has_key_value< std::map< K, V>>:
   std::true_type {};
template< typename K, typename V> struct has_key_value< std::multimap< K, V>>:
   std::true_type {};
template< typename K, typename V> struct has_key_value< std::unordered_map< K, V>>:
   std::true_type {};
template< typename K, typename V> struct has_key_value< std::unordered_multimap< K, V>>:
   std::true_type {};


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CONTAINER_TRAITS_HPP


// =====  END OF container_traits.hpp  =====

