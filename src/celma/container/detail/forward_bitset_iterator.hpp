
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
/// See documentation of class celma::container::detail::ForwardBitsetIterator.


#pragma once


#include "celma/container/detail/bitset_iterator_base.hpp"


namespace celma::container::detail {


/// Forward iterator for std::bitset's.
///
/// @tparam  N  The size of the bitset that the iterator is used for.
/// @since  1.7.0, 17.07.2018
template< size_t N> class ForwardBitsetIterator: public BitsetIteratorBase< N>
{
public:
   /// Default constructor, object must afterwards be initialised using the
   /// assignment operator, for example.
   ///
   /// @since  1.7.0, 18.07.2018
   ForwardBitsetIterator();

   /// Constructor with meaningful data.
   ///
   /// @param[in]  bs
   ///    The bitset to iterate over.
   /// @param[in]  at_end
   ///    Set this flag to true to initialise an 'end' iterator.
   /// @since
   ///    1.7.0, 17.07.2018
   explicit ForwardBitsetIterator( const std::bitset< N>& bs,
      bool at_end = false);

   /// Prefix increment operator. Searches and returns the next bit that is set
   /// in the bitset.
   ///
   /// @return
   ///    This object, pointing to the next bit that is set in the bitset,
   ///    or set to end.
   /// @since
   ///    1.7.0, 17.07.2018
   ForwardBitsetIterator& operator ++( std::prefix);

   /// Postfix increment operator. Searches and stores the next bit that is set
   /// in the bitset, returns a new iterator that points to the (previously)
   /// current position.
   ///
   /// @param  Ignored, only used to distinguish pre- and postfix operator.
   /// @return
   ///    New iterator pointing to the previously current position.
   /// @since
   ///    1.7.0, 17.07.2018
   ForwardBitsetIterator operator ++( std::postfix);

   /// Prefix decrement operator. Searches and returns the previous bit that is
   /// set in the bitset.
   ///
   /// @return
   ///    This object, pointing to the previous bit that is set in the bitset,
   ///    or set to end.
   /// @since
   ///    1.7.0, 17.07.2018
   ForwardBitsetIterator& operator --( std::prefix);

   /// Postfix decrement operator. Searches and stores the previous bit that is
   /// set in the bitset, returns a new iterator that points to the (previously)
   /// current position.
   ///
   /// @param  Ignored, only used to distinguish pre- and postfix operator.
   /// @return
   ///    New iterator pointing to the previously current position.
   /// @since
   ///    1.7.0, 17.07.2018
   ForwardBitsetIterator operator --( std::postfix);

   using BitsetIteratorBase< N>::operator ==;
   using BitsetIteratorBase< N>::operator !=;
   using BitsetIteratorBase< N>::operator *;

private:
   using BitsetIteratorBase< N>::mAtEnd;
   using BitsetIteratorBase< N>::mIndex;
   using BitsetIteratorBase< N>::mpBitset;
   using BitsetIteratorBase< N>::findPrev;
   using BitsetIteratorBase< N>::findNext;

}; // ForwardBitsetIterator< N>


// inlined methods
// ===============


template< size_t N>
   ForwardBitsetIterator< N>::ForwardBitsetIterator():
      BitsetIteratorBase< N>()
{
} // ForwardBitsetIterator< N>::ForwardBitsetIterator


template< size_t N>
   ForwardBitsetIterator< N>::ForwardBitsetIterator( const std::bitset< N>& bs,
      bool at_end):
         BitsetIteratorBase< N>( bs, at_end)
{
   if (!mAtEnd && !mpBitset->test( mIndex))
      findNext();
} // ForwardBitsetIterator< N>::ForwardBitsetIterator


template< size_t N>
   ForwardBitsetIterator< N>& ForwardBitsetIterator< N>::operator ++( std::prefix)
{
   findNext();
   return *this;
} // ForwardBitsetIterator< N>::operator ++


template< size_t N>
   ForwardBitsetIterator< N> ForwardBitsetIterator< N>::operator ++( std::postfix)
{
   auto  old( *this);
   findNext();
   return old;
} // ForwardBitsetIterator< N>::operator ++


template< size_t N>
   ForwardBitsetIterator< N>& ForwardBitsetIterator< N>::operator --( std::prefix)
{
   findPrev();
   return *this;
} // ForwardBitsetIterator< N>::operator --


template< size_t N>
   ForwardBitsetIterator< N> ForwardBitsetIterator< N>::operator --( std::postfix)
{
   auto  old( *this);
   findPrev();
   return old;
} // ForwardBitsetIterator< N>::operator --


} // namespace celma::container::detail


// =====  END OF forward_bitset_iterator.hpp  =====

