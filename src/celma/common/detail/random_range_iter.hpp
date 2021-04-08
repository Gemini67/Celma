
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
/// See documentation of class celma::common::detail::@@@.


#pragma once


#include "celma/common/pre_postfix.hpp"


namespace celma::common::detail {


template< typename R, typename T> class RandomRangeIter
{
public:
   explicit RandomRangeIter( R* random, int64_t num_values = 0);

   T operator *();

   bool operator ==( const RandomRangeIter& other) const;

   bool operator !=( const RandomRangeIter& other) const;

   RandomRangeIter& operator ++( std::prefix);

   RandomRangeIter operator ++( std::postfix);

private:
   R*       mpRandom;
   int64_t  mNumValues;
   T        mNextValue = 0;
}; // RandomRangeIter


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

