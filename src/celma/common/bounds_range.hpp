
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
/// See documentation of classes celma::common::BoundsRangeOne and
/// celma::common::BoundsRangeTwo, as well as function
// celma::common::bounds_range.


#ifndef CELMA_COMMON_BOUND_RANGE_HPP
#define CELMA_COMMON_BOUND_RANGE_HPP


#include <utility>


namespace celma { namespace common {


/// Helper class to use a range-based for loop with the results of an
/// equal_range() search on the container.
///
/// @tparam  C
///    The type of the container to search in.
/// @tparam  T
///    The type of the (key) values in the container.
///
/// @since  1.29.0, 22.06.2019
template< typename C, typename T> class BoundsRangeOne
{
public:
   /// Constructor, stores the iterators pointing to the beginning and the
   /// after-end of the equal range for the given value.
   ///
   /// @param[in]  container
   ///    The container to search in.
   /// @param[in]  value
   ///    The value to search for.
   /// @since  1.29.0, 22.06.2019
   BoundsRangeOne( const C& container, const T& value):
      mEqualRange( container.equal_range( value))
   {
   } // BoundsRangeOne< C, T>::BoundsRangeOne

   /// Returns the iterator pointing the first entry with the given (key) value.
   ///
   /// @return  Iterator pointing to the first value or end().
   /// @since  1.29.0, 22.06.2019
   typename C::const_iterator begin() const
   {
      return mEqualRange.first;
   } // BoundsRangeOne< C, T>::begin

   /// Returns the iterator pointing the first entry after the search-value.
   ///
   /// @return
   ///    Iterator pointing to the first value after the search-value or to
   //     end().
   /// @since  1.29.0, 22.06.2019
   typename C::const_iterator end() const
   {
      return mEqualRange.second;
   } // BoundsRangeOne< C, T>::end

private:
   /// The result of searching for the given value using equal_range().
   const std::pair< typename C::const_iterator, typename C::const_iterator>  mEqualRange;

}; // BoundsRangeOne< C, T>


/// Helper class to use a range-based for loop with the results of searching for
/// a lower and upper bound in the container.
///
/// @tparam  C
///    The type of the container to search in.
/// @tparam  T
///    The type of the (key) values in the container.
///
/// @since  1.29.0, 22.06.2019
template< typename C, typename T> class BoundsRangeTwo
{
public:
   /// Constructor, stores the iterators to the first entry with the lower (key)
   /// value and to the first entry after the last entry with the upper (key)
   /// value.<br>
   /// In other words, the lower and upper bound values passed to this
   /// constructor are both included in the resulting range.
   ///
   /// @param[in]  container
   ///    The container to search in.
   /// @param[in]  lower
   ///    The lower bound of the range to search.
   /// @param[in]  upper
   ///    The upper bound of the range to search.
   /// @since  1.29.0, 23.06.2019
   BoundsRangeTwo( const C& container, const T& lower, const T& upper):
      mLower( container.lower_bound( lower)),
      mUpper( container.upper_bound( upper))
   {
   } // BoundsRangeTwo< C, T>::BoundsRangeTwo

   /// Returns the iterator pointing to the first entry of the resulting search
   /// range.
   ///
   /// @return  Iterator pointing ot the first entry.
   /// @since  1.29.0, 23.06.2019
   typename C::const_iterator begin() const
   {
      return mLower;
   } // BoundsRangeTwo< C, T>::begin

   /// Iterator pointing to the first entry after the range or end().
   ///
   /// @return
   ///    Iterator pointing to the first value after the search-range or to
   ///    end().
   /// @since  1.29.0, 23.06.2019
   typename C::const_iterator end() const
   {
      return mUpper;
   } // BoundsRangeTwo< C, T>::end

private:
   /// Iterator pointing to the first entry of the range.
   const typename C::const_iterator  mLower;
   /// Iterator pointing to the first entry after the range.
   const typename C::const_iterator  mUpper;

}; // BoundsRangeTwo< C, T>


// helper functions
// ================


/// Helper function to be used in the range-based for loop:
///    <pre>for (auto it : bounds_range( my_container, "New York"))</pre>
///
/// @tparam  C
///    The type of the container to search in.
/// @tparam  T
///    The type of the (key) values in the container.
/// @param[in]  container
///    The container to search in.
/// @param[in]  value
///    The (key) value to search for.
/// @return
///    Object that provides the begin() and end() methods needed for the range
///    based for loop.
/// @since  1.29.0, 22.06.2019
template< typename C, typename T>
   BoundsRangeOne< C, T> bounds_range( const C& container, const T& value)
{
   return {container, value};
} // bounds_range


/// Helper function to be used in the range-based for loop:
///    <pre>for (auto it : bounds_range( my_container, "Boston", "New York"))</pre>
/// 
/// @tparam  C
///    The type of the container to search in.
/// @tparam  T
///    The type of the (key) values in the container.
/// @param[in]  container
///    The container to search in.
/// @param[in]  lower
///    The lower bound value to search for.
/// @param[in]  upper
///    The upper bound value to search for.
/// @return
///    Object that provides the begin() and end() methods needed for the range
///    based for loop.
/// @since  1.29.0, 23.06.2019
template< typename C, typename T>
   BoundsRangeTwo< C, T> bounds_range( const C& container, const T& lower,
      const T& upper)
{
   return {container, lower, upper};
} // bounds_range


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_BOUND_RANGE_HPP


// =====  END OF bounds_range.hpp  =====

