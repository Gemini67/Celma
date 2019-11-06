
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template functions celma::common::hasIntersection<>().


#ifndef CELMA_COMMON_HAS_INTERSECTION_HPP
#define CELMA_COMMON_HAS_INTERSECTION_HPP


namespace celma { namespace common {


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
/// @since  x.y.z, 30.10.2019
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
/// @since  x.y.z, 30.10.2019
template< typename C1, typename C2>
   bool hasIntersection( const C1& cont1, const C2& cont2)
{
   return hasIntersection( cont1.cbegin(), cont1.cend(), cont2.cbegin(),
      cont2.cend());
} // hasIntersection


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_HAS_INTERSECTION_HPP


// =====  END OF has_intersection.hpp  =====

