
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
/// See documentation of class celma::common::@@@.


#pragma once


#include <cstdlib>
#include <random>
#include "celma/common/detail/random_range_iter.hpp"


namespace celma::common {


class UnixRandom
{
public:
   /// 
   /// @param[in]  seed
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 23.01.2021
   UnixRandom( int64_t seed)
   {
      ::srand( seed);
   } // UnixRandom::UnixRandom

   uint64_t nextRand() const
   {
      return rand();
   } // UnixRandom::nextRand

}; // UnixRandom


template< typename R> class Predefined
{
public:
   /// 
   /// @param[in]  seed
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 23.01.2021
   Predefined( int64_t seed):
      mGenerator( seed)
   {
   } // Predefined::Predefined

   uint64_t nextRand() const
   {
      return mGenerator();
   } // Predefined::Predefined

private:
   mutable R  mGenerator;

}; // Predefined< R>


using DefaultRand  = Predefined< std::default_random_engine>;
using MinStdRand0  = Predefined< std::minstd_rand0>;
using MinStdRand   = Predefined< std::minstd_rand>;
using Mt19937      = Predefined< std::mt19937>;
using Mt19937_64   = Predefined< std::mt19937_64>;
using RanLux24Base = Predefined< std::ranlux24_base>;
using RanLux48Base = Predefined< std::ranlux48_base>;
using RanLux24     = Predefined< std::ranlux24>;
using RanLux48     = Predefined< std::ranlux48>;
using KnuthB       = Predefined< std::knuth_b>;


template< typename R = DefaultRand, typename T = int> class RandomRange
{
public:
   using const_iterator = detail::RandomRangeIter< const RandomRange< R, T>, T>;

   /// 
   /// @param[in]  seed
   ///    .
   /// @param[in]  lower_bound
   ///    .
   /// @param[in]  upper_bound
   ///    .
   /// @param[in]  num_values
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 23.01.2021
   RandomRange( int64_t seed, T lower_bound, T upper_bound, int64_t num_values);

   const_iterator begin() const;
   const_iterator cbegin() const;
   const_iterator end() const;
   const_iterator cend() const;

   T nextRand() const;

private:
   R        mRandomGen;
   T        mLowerBound;
   T        mUpperBound;
   int64_t  mNumValues;
}; // RandomRange< R, T>


// inlined methods
// ===============


template< typename R, typename T>
   RandomRange< R, T>::RandomRange( int64_t seed, T lower_bound, T upper_bound,
      int64_t num_values):
         mRandomGen( seed),
         mLowerBound( lower_bound),
         mUpperBound( upper_bound),
         mNumValues( num_values)
{
} // RandomRange< R, T>::RandomRange


template< typename R, typename T>
   typename RandomRange< R, T>::const_iterator RandomRange< R, T>::begin() const
{
   return const_iterator( this, mNumValues);
}


template< typename R, typename T>
   typename RandomRange< R, T>::const_iterator RandomRange< R, T>::cbegin() const
{
   return const_iterator( this, mNumValues);
}


template< typename R, typename T>
   typename RandomRange< R, T>::const_iterator RandomRange< R, T>::end() const
{
   return const_iterator( this);
}


template< typename R, typename T>
   typename RandomRange< R, T>::const_iterator RandomRange< R, T>::cend() const
{
   return const_iterator( this);
}


template< typename R, typename T> T RandomRange< R, T>::nextRand() const
{
   return static_cast< T>( mRandomGen.nextRand() % (mUpperBound - mLowerBound))
      + mLowerBound;
} // RandomRange::nextRand


} // namespace celma::common


// =====  END OF random.hpp  =====

