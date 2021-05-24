
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::detail::RandomRangeIter<>.


#pragma once


#include "celma/common/pre_postfix.hpp"


namespace celma::common::detail {


/// Iterator for a range of random numbers.
///
/// @tparam  R
///    Type of the random number generator.
/// @tparam  T
///    Type of the values to generate/return.
/// @since  1.45.0, 23.01.2021
template< typename R, typename T> class RandomRangeIter
{
public:
   /// Constructor.
   ///
   /// @param[in]  random
   ///    Pointer to the random number generator.
   /// @param[in]  num_values
   ///    Maximum number of random numbers to generate, 0 = end iterator.
   /// @since  1.45.0, 23.01.2021
   explicit RandomRangeIter( R* random, int64_t num_values = 0);

   /// Dereferencing this iterator returns the next random number.
   ///
   /// Returns the next random number.
   /// @since  1.45.0, 23.01.2021
   T operator *();

   /// Equality comparison operator.
   ///
   /// @param[in]  other  Other iterator object to compare against.
   /// @return
   ///    \c true if both iterators use the same generator object and are the
   ///    same position in the range.
   /// @since  1.45.0, 23.01.2021
   bool operator ==( const RandomRangeIter& other) const;

   /// Inequality comparison operator.
   ///
   /// @param[in]  other  Other iterator object to compare against.
   /// @return  \c true if the two iterators are not equal.
   /// @since  1.45.0, 23.01.2021
   bool operator !=( const RandomRangeIter& other) const;

   /// Prefix increment operator.
   ///
   /// @return  This object, moved to the next random number.
   /// @since  1.45.0, 23.01.2021
   RandomRangeIter& operator ++( std::prefix);

   /// Postfix increment operator.
   ///
   /// @return  Iterator object with the previous random number.
   /// @since  1.45.0, 23.01.2021
   RandomRangeIter operator ++( std::postfix);

private:
   /// Pointer to the random number generator.
   R*       mpRandom;
   /// Remaining number of random values to generate.
   int64_t  mNumValues;
   /// Next random value.
   T        mNextValue = 0;
}; // RandomRangeIter


// inlined methods
// ===============


template< typename R, typename T>
   RandomRangeIter< R, T>::RandomRangeIter( R* random, int64_t num_values):
      mpRandom( random),
      mNumValues( num_values)
{
   if (mNumValues > 0)
   {
      mNextValue = mpRandom->nextRand();
   } // end if
} // RandomRangeIter< R, T>::RandomRangeIter


template< typename R, typename T>
   T RandomRangeIter< R, T>::operator *()
{
   return (mNumValues > 0) ? mNextValue : -1;
} // RandomRangeIter< R, T>::operator *


template< typename R, typename T>
   bool RandomRangeIter< R, T>::operator ==( const RandomRangeIter< R, T>& other) const
{
   return (mpRandom == other.mpRandom) && (mNumValues == other.mNumValues);
} // RandomRangeIter< R, T>::operator ==


template< typename R, typename T>
   bool RandomRangeIter< R, T>::operator !=( const RandomRangeIter< R, T>& other) const
{
   return !(*this == other);
} // RandomRangeIter< R, T>::operator ==


template< typename R, typename T>
   RandomRangeIter< R, T>& RandomRangeIter< R, T>::operator ++( std::prefix)
{
   if (mNumValues > 0)
   {
      mNextValue = mpRandom->nextRand();
      --mNumValues;
   } // end if
   return *this;
} // RandomRangeIter< R, T>::operator ++


template< typename R, typename T>
   RandomRangeIter< R, T> RandomRangeIter< R, T>::operator ++( std::postfix)
{
   auto  copy( *this);
   ++(*this);
   return copy;
} // RandomRangeIter< R, T>::operator ++


} // namespace celma::common::detail


// =====  END OF random_range_iter.hpp  =====

