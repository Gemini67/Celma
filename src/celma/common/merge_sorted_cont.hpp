
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::MergeSortedCont.


#ifndef CELMA_COMMON_MERGE_SORTED_CONT_HPP
#define CELMA_COMMON_MERGE_SORTED_CONT_HPP


#include <iterator>
#include <queue>


namespace celma { namespace common {


namespace detail {


/// Helper class: Comparator for two pairs, where the first value of the pair is
/// an iterator. The comparison is based on the value that the iterator points
/// to.
/// @tparam  T  The type of the objects to compare.<br>
///             Expected: std::pair< iterator, iterator>.
/// @since  0.10, 14.12.2016
template< typename T> class GreaterCompareIterators
{
public:
   /// Compares two pairs of iterators by the first value.
   /// @return  \c true if lhs \> rhs.
   /// @since  0.10, 14.12.2016
   bool operator ()( const T& lhs, const T& rhs) const
   {
      return *lhs.first > *rhs.first;
   } // GreaterCompareIterators< T>::operator ()
}; // GreaterCompareIterators< T>


} // namespace detail


/// Merges values from multiple, sorted containers into a single container.
///
/// @tparam  T  The type of the values in the containers.
/// @tparam  R  The type of the result container to return.
/// @tparam  I  The type of the input container(s).
/// @since  0.10, 14.12.2016
template< typename T, typename R, typename I> class MergeSortedCont
{
public:
   /// Constructor.
   /// @since  0.10, 14.12.2016
   MergeSortedCont();

   /// Don't want to allow copies.
   MergeSortedCont( const MergeSortedCont&) = delete;
   /// Default destructor is fine.
   ~MergeSortedCont() = default;

   /// Adds another input container to merge in.<br>
   /// Only the iterators to the container are stored, i.e. the container and
   /// its values must persist until merge() was called.
   /// @param[in]  container  The container to add for merging in later.
   /// @since  0.10, 14.12.2016
   void addCont( const I& container);

   /// Merges all the values of the previously specified containers and stores
   /// them in order in a new container.
   /// @return  The new container with all the merged values.
   /// @since  0.10, 14.12.2016
   R merge();

   /// Don't want to allow assignments.
   MergeSortedCont& operator =( const MergeSortedCont&) = delete;

private:
   /// The type of the elements to store in the priority queue.
   using elem_t = std::pair< typename I::const_iterator,
      typename I::const_iterator>;

   /// The priority queue with the iterators to the containers. Sorted by the
   /// first value in each container, in ascending order.
   using queue_t = std::priority_queue< elem_t, std::vector< elem_t>,
      detail::GreaterCompareIterators< elem_t>>;

   /// The list of containers (begin/end iterators, actually) to sort.
   queue_t  mQueue;

}; // MergeSortedCont< T, R, I>


// inlined methods
// ===============


template< typename T, typename R, typename I>
   MergeSortedCont< T, R, I>::MergeSortedCont():
      mQueue()
{
} // MergeSortedCont< T, R, I>::MergeSortedCont


template< typename T, typename R, typename I>
   void MergeSortedCont< T, R, I>::addCont( const I& container)
{
   mQueue.push( elem_t( std::begin( container), std::end( container)));
} // MergeSortedCont< T, R, I>::addCont


template< typename T, typename R, typename I>
   R MergeSortedCont< T, R, I>::merge()
{
   R  result;

   while (mQueue.size() > 1)
   {
      // remove the first element from the priority queue and store its value
      // in the result container
      auto  queue_top = mQueue.top();
      result.push_back( *queue_top.first);
      mQueue.pop();

      // get the next value (from the iterator) now on top of the queue
      auto const&  next_top_value = *mQueue.top().first;

      // if we did not yet reach the end of this input container, add it back
      // to the priority queue
      while ((++queue_top.first != queue_top.second)
             && (*queue_top.first <= next_top_value))
      {
         result.push_back( *queue_top.first);
      } // end while

      // if iterator still not reached the end of its container
      if (queue_top.first != queue_top.second)
         mQueue.push( queue_top);
   } // end while

   // queue contains at most 1 remaining input container
   if (!mQueue.empty())
   {
      auto const&  queue_top = mQueue.top();
      result.insert( result.end(), queue_top.first, queue_top.second);
      mQueue.pop();
   } // end if

   return result;
} // MergeSortedCont< T, R, I>::merge


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_MERGE_SORTED_CONT_HPP


// =====  END OF merge_sorted_cont.hpp  =====

