
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::BitsetIteratorBase.


#ifndef CELMA_COMMON_BITSET_DETAIL_ITERATOR_BASE_HPP
#define CELMA_COMMON_BITSET_DETAIL_ITERATOR_BASE_HPP


#include <bitset>
#include <iterator>
#include "celma/common/pre_postfix.hpp"


namespace celma { namespace common { namespace detail {


/// Base class for bitset iterator classes.
///
/// @tparam  N  The size of the bitset.
/// @since  1.7.0, 17.07.2018
template< size_t N> class BitsetIteratorBase
{
public:
   typedef std::random_access_iterator_tag iterator_category;

   /// Allow default copy construction.
   BitsetIteratorBase( const BitsetIteratorBase&) = default;

   /// Equality comparison operator.
   ///
   /// @param[in]  other
   ///    The other object to compare against.
   /// @return
   ///    \c true if this and the other object refer to the same bitset and to
   ///    the same position in the bitset.
   /// @since
   ///    1.7.0, 18.07.2018
   bool operator ==( const BitsetIteratorBase& other) const;

   /// Difference comparison operator.
   ///
   /// @param[in]  other
   ///    The other object to compare against.
   /// @return
   ///    \c true if this and the other object refer to different bitsets or to
   ///    different positions in the same bitset.
   /// @since
   ///    1.7.0, 17.07.2018
   bool operator !=( const BitsetIteratorBase& other) const;

   /// Allow default assignment.
   BitsetIteratorBase& operator =( const BitsetIteratorBase&) = default;

   /// Dereference operator. Returns the current index of a bit that is set in
   /// the bitset.
   ///
   /// @return  The index of the current bit that is set.
   /// @since  1.7.0, 18.07.2018
   size_t operator *() const;

protected:
   /// Constructor with meaningful data.
   ///
   /// @param[in]  bs
   ///    The bitset to iterate over.
   /// @param[in]  at_end
   ///    Set this flag to true to initialise an 'end' iterator.
   /// @since
   ///    1.7.0, 17.07.2018
   explicit BitsetIteratorBase( const std::bitset< N>& bs, bool at_end);

   /// Tries to find the next bit that is set in the bitset, starting after the
   /// current position #mIndex.
   /// If no bit is set anymore, #mAtEnd is set.<br>
   /// Does nothing if #mAtEnd is already set when the function is entered.
   ///
   /// @since  1.7.0, 18.07.2018
   void findNext();

   /// Tries to find the previous bit that is set in the bitset, starting before
   /// the current position #mIndex.
   /// If no bit is set anymore, #mAtEnd is set.<br>
   /// Does nothing if #mAtEnd is already set when the function is entered.
   ///
   /// @since  1.7.0, 18.07.2018
   void findPrev();

   /// The bitset to iterate over.
   const std::bitset< N>*  mpBitset;
   /// The current position of a bit that is set.
   size_t                  mIndex;
   /// Set when the iterator reached the end of the bitset.
   bool                    mAtEnd;

}; // BitsetIteratorBase< N>


// inlined methods
// ===============


template< size_t N>
   bool BitsetIteratorBase< N>::operator ==( const BitsetIteratorBase& other) const
{
   return (mpBitset == other.mpBitset) && (mAtEnd == other.mAtEnd)
      && (mAtEnd || (mIndex == other.mIndex));
} // BitsetIteratorBase< N>::operator ==


template< size_t N>
   bool BitsetIteratorBase< N>::operator !=( const BitsetIteratorBase& other) const
{
   return !(*this == other);
} // BitsetIteratorBase< N>::operator !=


template< size_t N>
   size_t BitsetIteratorBase< N>::operator *() const
{
   return mIndex;
} // BitsetIteratorBase< N>::operator *


template< size_t N>
   BitsetIteratorBase< N>::BitsetIteratorBase( const std::bitset< N>& bs,
      bool at_end):
         mpBitset( &bs),
         mIndex( 0),
         mAtEnd( at_end)
{
} // BitsetIteratorBase< N>::BitsetIteratorBase


template< size_t N> void BitsetIteratorBase< N>::findNext()
{
   if (mAtEnd)
      return;
   while (mIndex < N - 1)
   {
      if (mpBitset->test( ++mIndex))
         return;
   } // end while
   mAtEnd = true;
} // BitsetIteratorBase< N>::findNext


template< size_t N> void BitsetIteratorBase< N>::findPrev()
{
   if (mAtEnd)
      return;
   for (;;)
   {
      if (mIndex == 0)
         break;   // for
      if (mpBitset->test( --mIndex))
         return;
   } // end for
   mAtEnd = true;
} // BitsetIteratorBase< N>::findPrev


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_BITSET_DETAIL_ITERATOR_BASE_HPP


// =====  END OF bitset_iterator_base.hpp  =====

