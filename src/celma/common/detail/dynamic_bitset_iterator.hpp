
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
/// See documentation of template classes
/// celma::common::detail::DynamicBitsetIteratorBase<>,
/// celma::common::detail::DynamicBitsetIterator<> and
/// celma::common::detail::DynamicBitsetReverseIterator<>.


#ifndef CELMA_COMMON_DETAIL_DYNAMIC_BITSET_ITERATOR_HPP
#define CELMA_COMMON_DETAIL_DYNAMIC_BITSET_ITERATOR_HPP


#include <cassert>
#include "celma/common/pre_postfix.hpp"


namespace celma::common::detail {


// Template Class DynamicBitsetIteratorBase
// ========================================


/// Base class for the forward and reverse iterators.
///
/// @tparam  T
///    The type of the class for which this iterator may be used.<br>
///    Here: Always celma::common::DynamicBitset. Set as template parameter to
///    break dependency cycle.
/// @since  x.y.z, 18.06.2020
template< typename T> class DynamicBitsetIteratorBase
{
public:
   /// Equality comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if both iterators point to end(), or both iterators point to
   ///    the same position in the same dynamic bitset.
   /// @since  x.y.z, 18.06.2020
   bool operator ==( const DynamicBitsetIteratorBase& other) const
   {
      return (mpDynBitset == other.mpDynBitset) && (mCurrPos == other.mCurrPos);
   } // DynamicBitsetIteratorBase< T>::operator ==

   /// Not-equal comparison operator.
   ///
   /// @param[in]  other  The other iterator object to compare against.
   /// @return
   ///    \c true if the iterators point to different bitsets or different
   ///    positions.
   /// @since  x.y.z, 20.06.2020
   bool operator !=( const DynamicBitsetIteratorBase& other) const
   {
      return (mpDynBitset != other.mpDynBitset) || (mCurrPos != other.mCurrPos);
   } // DynamicBitsetIteratorBase< T>::operator !=

   /// De-reference operator, returns the current position of the iterator.
   ///
   /// @return
   ///    The position in the bitset that the iterator currently points to.
   /// @since  x.y.z, 20.06.2020
   size_t operator *() const
   {
      return static_cast< size_t>( mCurrPos);
   } // DynamicBitsetIteratorBase< T>::operator *

protected:
   /// Constructor.
   ///
   /// @param[in]  dbs
   ///    Pointer to the dynamic bitset to iterate over.
   /// @param[in]  startpos
   ///    The start position for the iteration.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetIteratorBase( T* dbs, ssize_t startpos):
      mpDynBitset( dbs),
      mCurrPos( startpos)
   {
      assert( mpDynBitset != nullptr);
   } // DynamicBitsetIteratorBase< T>::DynamicBitsetIteratorBase

   /// Virtual default destructore is fine.
   virtual ~DynamicBitsetIteratorBase() = default;

   /// Searches for the next bit in the dynamic bitset that is set.
   ///
   /// @since  x.y.z, 18.06.2020
   void forward()
   {
      if (static_cast< size_t>( mCurrPos) >= mpDynBitset->size())
         return;
      while ((static_cast< size_t>( ++mCurrPos) < mpDynBitset->size())
             && !mpDynBitset->test( mCurrPos))
      {
      } // end while
   } // DynamicBitsetIteratorBase< T>::forward

   /// Searches backward for the next (i.e. previous) bit that is set in the
   /// dynamic bitset.
   ///
   /// @since  x.y.z, 18.06.2020
   void reverse()
   {
      if (mCurrPos < 0)
         return;
      while ((--mCurrPos >= 0) && !mpDynBitset->test( mCurrPos))
      {
      } // end while
   } // DynamicBitsetIteratorBase< T>::reverse

   /// Pointer to the dynamic bitset object to iterate over.
   T*       mpDynBitset;
   /// Current position in the dynamic vector of a bit that is set.
   ssize_t  mCurrPos = 0;

}; // DynamicBitsetIteratorBase< T>


// Template Class DynamicBitsetIterator
// ====================================


/// Forward iterator for a dynamic bitset.
///
/// @tparam  T
///    The type of the class for which this iterator may be used.<br>
///    Here: Always celma::common::DynamicBitset. Set as template parameter to
///    break dependency cycle.
/// @since  x.y.z, 18.06.2020
template< typename T> class DynamicBitsetIterator:
   public DynamicBitsetIteratorBase< T>
{
public:
   /// Constructor for an iterator object that points to the end of the vector.
   ///
   /// @param[in]  dbs  Pointer to the dynamic bitset to iterate over.
   /// @since  x.y.z, 18.06.2020
   explicit DynamicBitsetIterator( T* dbs):
      DynamicBitsetIteratorBase< T>( dbs, dbs->size())
   {
   } // DynamicBitsetIterator< T>::DynamicBitsetIterator

   /// Constructor for an iterator object that points to a specific position in
   /// the vector.
   /// 
   /// @param[in]  dbs
   ///    Pointer to the dynamic bitset to iterate over.
   /// @param[in]  startpos
   ///    The position to start iterating from.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetIterator( T* dbs, ssize_t startpos):
      DynamicBitsetIteratorBase< T>( dbs, startpos)
   {
      if (!mpDynBitset->test( mCurrPos))
         forward();
   } // DynamicBitsetIterator< T>::DynamicBitsetIterator

   /// Default destructor is fine.
   ~DynamicBitsetIterator() override = default;

   /// Use equality comparison operator from base class.
   using DynamicBitsetIteratorBase< T>::operator ==;

   /// Use inequality comparison operator from base class.
   using DynamicBitsetIteratorBase< T>::operator !=;

   /// Use dereference operator from base class.
   using DynamicBitsetIteratorBase< T>::operator *;

   /// Pre-increment operator.
   ///
   /// @return  This object, pointing to the next bit that is set.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetIterator& operator ++( std::prefix)
   {
      forward();
      return *this;
   } // DynamicBitsetIterator::operator ++

   /// Post-increment operator.
   ///
   /// @return  A new object pointing to the previous position of this object.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetIterator operator ++( std::postfix)
   {
      auto  copy( *this);
      forward();
      return copy;
   } // DynamicBitsetIterator::operator ++

   /// Pre-decrement operator.
   ///
   /// @return  This object, pointing to the previous bit that is set.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetIterator& operator --( std::prefix)
   {
      reverse();
      if (mCurrPos < 0)
         mCurrPos = mpDynBitset->size();
      return *this;
   } // DynamicBitsetIterator::operator --


   /// Post-decrement operator.
   ///
   /// @return  A new object pointing to the previous position of this object.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetIterator operator --( std::postfix)
   {
      auto  copy( *this);
      reverse();
      if (mCurrPos < 0)
         mCurrPos = mpDynBitset->size();
      return copy;
   } // DynamicBitsetIterator::operator --

private:
   /// Use the forward function from the base class.
   using DynamicBitsetIteratorBase< T>::forward;
   /// Use the reverse function from the base class.
   using DynamicBitsetIteratorBase< T>::reverse;
   /// Use the pointer to the dynamic bitset to iterate over from the base class.
   using DynamicBitsetIteratorBase< T>::mpDynBitset;
   /// Use the current position member variable from the base class.
   using DynamicBitsetIteratorBase< T>::mCurrPos;

}; // DynamicBitsetIterator< T>


// Template Class DynamicBitsetReverseIterator
// ===========================================


/// Reverse iterator for a dynamic bitset.
///
/// @tparam  T
///    The type of the class for which this iterator may be used.<br>
///    Here: Always celma::common::DynamicBitset. Set as template parameter to
///    break dependency cycle.
/// @since  x.y.z, 18.06.2020
template< typename T> class DynamicBitsetReverseIterator:
   public DynamicBitsetIteratorBase< T>
{
public:
   /// Constructor for an iterator object that points before the start of the
   /// vector.
   ///
   /// @param[in]  dbs  Pointer to the dynamic bitset to iterate over.
   /// @since  x.y.z, 18.06.2020
   explicit DynamicBitsetReverseIterator( T* dbs):
      DynamicBitsetIteratorBase< T>( dbs, -1)
   {
   } // DynamicBitsetIterator< T>::DynamicBitsetIterator

   /// Constructor for an iterator object that points to a specific position in
   /// the vector.
   /// 
   /// @param[in]  dbs
   ///    Pointer to the dynamic bitset to iterate over.
   /// @param[in]  startpos
   ///    The position to start iterating from.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetReverseIterator( T* dbs, ssize_t startpos):
      DynamicBitsetIteratorBase< T>( dbs, startpos)
   {
      if (!mpDynBitset->test( mCurrPos))
         reverse();
   } // DynamicBitsetIterator< T>::DynamicBitsetIterator

   /// Default destructor is fine.
   ~DynamicBitsetReverseIterator() override = default;

   /// Use equality comparison operator from base class.
   using DynamicBitsetIteratorBase< T>::operator ==;

   /// Use inequality comparison operator from base class.
   using DynamicBitsetIteratorBase< T>::operator !=;

   /// Use dereference operator from base class.
   using DynamicBitsetIteratorBase< T>::operator *;

   /// Pre-increment operator.
   ///
   /// @return  This object, pointing to the previous bit that is set.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetReverseIterator& operator ++( std::prefix)
   {
      reverse();
      return *this;
   } // DynamicBitsetReverseIterator::operator ++

   /// Post-increment operator.
   ///
   /// @return  A new object pointing to the previous position of this object.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetReverseIterator operator ++( std::postfix)
   {
      auto  copy( *this);
      reverse();
      return copy;
   } // DynamicBitsetReverseIterator::operator ++

   /// Pre-decrement operator.
   ///
   /// @return  This object, pointing to the next bit that is set.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetReverseIterator& operator --( std::prefix)
   {
      forward();
      if (mCurrPos >= static_cast< ssize_t>( mpDynBitset->size()))
         mCurrPos = -1;
      return *this;
   } // DynamicBitsetReverseIterator::operator --

   /// Post-decrement operator.
   ///
   /// @return  A new object pointing to the previous position of this object.
   /// @since  x.y.z, 18.06.2020
   DynamicBitsetReverseIterator operator --( std::postfix)
   {
      auto  copy( *this);
      forward();
      if (mCurrPos >= static_cast< ssize_t>( mpDynBitset->size()))
         mCurrPos = -1;
      return copy;
   } // DynamicBitsetReverseIterator::operator --

private:
   /// Use the forward function from the base class.
   using DynamicBitsetIteratorBase< T>::forward;
   /// Use the reverse function from the base class.
   using DynamicBitsetIteratorBase< T>::reverse;
   /// Use the pointer to the dynamic bitset to iterate over from the base class.
   using DynamicBitsetIteratorBase< T>::mpDynBitset;
   /// Use the current position member variable from the base class.
   using DynamicBitsetIteratorBase< T>::mCurrPos;

}; // DynamicBitsetReverseIterator< T>


} // namespace celma::common::detail


#endif   // CELMA_COMMON_DETAIL_DYNAMIC_BITSET_ITERATOR_HPP


// =====  END OF dynamic_bitset_iterator.hpp  =====

