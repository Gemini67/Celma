
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
/// See documentation of class celma::container::detail::ReverseBitsetIterator.


#ifndef CELMA_CONTAINER_DETAIL_REVERSE_BITSET_ITERATOR_HPP
#define CELMA_CONTAINER_DETAIL_REVERSE_BITSET_ITERATOR_HPP


#include "celma/container/detail/bitset_iterator_base.hpp"


namespace celma::container::detail {


/// Forward iterator for std::bitset's.
///
/// @tparam  N  The size of the bitset that the iterator is used for.
/// @since  1.7.0, 17.07.2018
template< size_t N> class ReverseBitsetIterator: public BitsetIteratorBase< N>
{
public:
   /// Default constructor, object must afterwards be initialised using the
   /// assignment operator, for example.
   ///
   /// @since  1.7.0, 18.07.2018
   ReverseBitsetIterator();

   /// Constructor with meaningful data.
   ///
   /// @param[in]  bs
   ///    The bitset to iterate over.
   /// @param[in]  at_end
   ///    Set this flag to true to initialise an 'end' iterator.
   /// @since
   ///    1.7.0, 17.07.2018
   explicit ReverseBitsetIterator( const std::bitset< N>& bs,
      bool at_end = false);

   /// Prefix increment operator. Searches and returns the previous bit that is
   /// set in the bitset.
   ///
   /// @return
   ///    This object, pointing to the previous bit that is set in the bitset,
   ///    or set to end.
   /// @since
   ///    1.7.0, 17.07.2018
   ReverseBitsetIterator& operator ++( std::prefix);

   /// Postfix increment operator. Searches and stores the previous bit that is
   /// set in the bitset, returns a new iterator that points to the (previously)
   /// current position.
   ///
   /// @param  Ignored, only used to distinguish pre- and postfix operator.
   /// @return
   ///    New iterator pointing to the previously current position.
   /// @since
   ///    1.7.0, 17.07.2018
   ReverseBitsetIterator operator ++( std::postfix);

   /// Prefix decrement operator. Searches and returns the next bit that is set
   /// in the bitset.
   ///
   /// @return
   ///    This object, pointing to the next bit that is set in the bitset,
   ///    or set to end.
   /// @since
   ///    1.7.0, 17.07.2018
   ReverseBitsetIterator& operator --( std::prefix);

   /// Postfix decrement operator. Searches and stores the next bit that is set
   /// in the bitset, returns a new iterator that points to the (previously)
   /// current position.
   ///
   /// @param  Ignored, only used to distinguish pre- and postfix operator.
   /// @return
   ///    New iterator pointing to the previously current position.
   /// @since
   ///    1.7.0, 17.07.2018
   ReverseBitsetIterator operator --( std::postfix);

   using BitsetIteratorBase< N>::operator ==;
   using BitsetIteratorBase< N>::operator !=;
   using BitsetIteratorBase< N>::operator *;

private:
   using BitsetIteratorBase< N>::mAtEnd;
   using BitsetIteratorBase< N>::mIndex;
   using BitsetIteratorBase< N>::mpBitset;
   using BitsetIteratorBase< N>::findPrev;
   using BitsetIteratorBase< N>::findNext;

}; // ReverseBitsetIterator< N>


// inlined methods
// ===============


template< size_t N>
   ReverseBitsetIterator< N>::ReverseBitsetIterator():
      ReverseBitsetIterator< N>()
{
} // ReverseBitsetIterator< N>::ReverseBitsetIterator


template< size_t N>
   ReverseBitsetIterator< N>::ReverseBitsetIterator( const std::bitset< N>& bs,
      bool at_end):
         BitsetIteratorBase< N>( bs, at_end)
{
   if (!mAtEnd)
   {
      mIndex = N - 1;
      if (!mpBitset->test( mIndex))
         findPrev();
   } // end if
} // ReverseBitsetIterator< N>::ReverseBitsetIterator


template< size_t N>
   ReverseBitsetIterator< N>& ReverseBitsetIterator< N>::operator ++( std::prefix)
{
   findPrev();
   return *this;
} // ReverseBitsetIterator< N>::operator ++


template< size_t N>
   ReverseBitsetIterator< N> ReverseBitsetIterator< N>::operator ++( std::postfix)
{
   auto  old( *this);
   findPrev();
   return old;
} // ReverseBitsetIterator< N>::operator ++


template< size_t N>
   ReverseBitsetIterator< N>& ReverseBitsetIterator< N>::operator --( std::prefix)
{
   findNext();
   return *this;
} // ReverseBitsetIterator< N>::operator --


template< size_t N>
   ReverseBitsetIterator< N> ReverseBitsetIterator< N>::operator --( std::postfix)
{
   auto  old( *this);
   findNext();
   return old;
} // ReverseBitsetIterator< N>::operator --


} // namespace celma::container::detail


#endif   // CELMA_CONTAINER_DETAIL_REVERSE_BITSET_ITERATOR_HPP


// =====  END OF reverse_bitset_iterator.hpp  =====

