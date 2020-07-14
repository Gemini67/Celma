
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template functions celma::common::hasIntersection<>().


#pragma once


#include <unordered_map>


namespace celma::common {


/// Checks if two sequences intersect, i.e. if they both contain at least one
/// value.
/// This is the same as calling std::set_intersection<>() and then checking the
/// result size, only that this function is faster because it stops on the first
/// common value, and does not copy the data into another container. Only for
/// completely disjoint sequences you'd get the same runtime performance.
///
/// @tparam  I1
///    The type of the iterators for the first sequence.
/// @tparam  I2
///    The type of the iterators for the second sequence.
/// @param[in]  first1
///    Iterator pointing to the first entry of the first sequence.
/// @param[in]  last1
///    Iterator pointing behind the end of the first sequence.
/// @param[in]  first2
///    Iterator pointing to the second entry of the first sequence.
/// @param[in]  last2
///    Iterator pointing behind the end of the second sequence.
/// @return
///    \c true if the contents of the two sequences are not completely
///    disjoint, i.e. at least one (1) value exists in both sequences.
/// @since  1.33.0, 30.10.2019
template< typename I1, typename I2>
   bool hasIntersection( I1 first1, I1 last1, I2 first2, I2 last2)
{
   while ((first1 != last1) && (first2 != last2))
   {
      if (*first1 < *first2)
      {
         ++first1;
      } else
      {
         if (!(*first2 < *first1))
            return true;
         ++first2;
      } // end if
   } // end while
   return false;
} // hasIntersection


/// Helper function to check the complete contents of two containers if their
/// contents intersect.
///
/// @tparam  C1
///    The type of the first container.
/// @tparam  C2
///    The type of the second container.
/// @param[in]  cont1
///    The first container.
/// @param[in]  cont2
///    The second container.
/// @return
///    \c true if the contents of the two containers are not completely
///    disjoint, i.e. at least one (1) value exists in both containers.
/// @since  1.33.0, 30.10.2019
template< typename C1, typename C2>
   bool hasIntersection( const C1& cont1, const C2& cont2)
{
   return hasIntersection( cont1.cbegin(), cont1.cend(), cont2.cbegin(),
      cont2.cend());
} // hasIntersection


/// Checks 2 unordered maps for intersection.
///
/// @tparam  K
///    The key type of the unordered maps.
/// @tparam  V
///    The value type of the unordered maps.
/// @param[in]  cont1
///    The first container to check.
/// @param[in]  cont2
///    The second container to check.
/// @return  \c true if the values in the two containers intersect.
/// @since  1.41.0, 18.03.2020
template< typename K, typename V>
   bool hasIntersection( const std::unordered_map< K, V>& cont1,
      const std::unordered_map< K, V>& cont2)
{

   using  ct = std::unordered_map< K, V>;

   auto  check = []( const ct& c1, const ct& c2)
      {
         for (auto const& i1 : c1)
         {
            if (c2.find( i1.first) != c2.end())
               return true;
         } // end for
         return false;
      };

   if (cont1.size() < cont2.size())
      return check( cont1, cont2);

   return check( cont2, cont1);
} // hasIntersection


/// Checks 2 unordered multi-maps for intersection.
///
/// @tparam  K
///    The key type of the unordered multi-maps.
/// @tparam  V
///    The value type of the unordered multi-maps.
/// @param[in]  cont1
///    The first container to check.
/// @param[in]  cont2
///    The second container to check.
/// @return  \c true if the values in the two containers intersect.
/// @since  1.41.0, 12.07.2020
template< typename K, typename V>
   bool hasIntersection( const std::unordered_multimap< K, V>& cont1,
      const std::unordered_multimap< K, V>& cont2)
{

   using  ct = std::unordered_multimap< K, V>;

   auto  check = []( const ct& c1, const ct& c2)
      {
         for (auto const& i1 : c1)
         {
            if (c2.find( i1.first) != c2.end())
               return true;
         } // end for
         return false;
      };

   if (cont1.size() < cont2.size())
      return check( cont1, cont2);

   return check( cont2, cont1);
} // hasIntersection


} // namespace celma::common


// =====  END OF has_intersection.hpp  =====

