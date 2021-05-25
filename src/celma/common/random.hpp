
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
/// See documentation of template class celma::common::RandomRange<>.


#pragma once


#include <random>
#include "celma/common/detail/random.hpp"
#include "celma/common/detail/random_range_iter.hpp"


namespace celma::common {


// use the following types as first template parameter to use one of the
// random number generators defined in the C++ Standard Library:
using DefaultRand  = detail::Predefined< std::default_random_engine>;
using MinStdRand0  = detail::Predefined< std::minstd_rand0>;
using MinStdRand   = detail::Predefined< std::minstd_rand>;
using Mt19937      = detail::Predefined< std::mt19937>;
using Mt19937_64   = detail::Predefined< std::mt19937_64>;
using RanLux24Base = detail::Predefined< std::ranlux24_base>;
using RanLux48Base = detail::Predefined< std::ranlux48_base>;
using RanLux24     = detail::Predefined< std::ranlux24>;
using RanLux48     = detail::Predefined< std::ranlux48>;
using KnuthB       = detail::Predefined< std::knuth_b>;
using UnixRandom   = detail::UnixRandom;

// promote the wrapper for custom random generators into this namespace:
template< typename G> using Custom = detail::Custom< G>;


/// Allows to use a random number generator in range-based for loop.
/// Features:
/// - Creates a given number of random values and then stops.
/// - Ensures that all random numbers are in a given range.
/// .
/// Either use one of the types defined above and the first constructor to
/// create an object, or use the second constructor where you pass the object of
/// your custom random number engine.<br>
/// Example:
/// <pre>
///   using my_engine = std::linear_congruential_engine< std::uint_fast32_t, 48271, 0, 2147483647>;
///   using my_generator = celma::common::Custom< my_engine>;
///   celma::common::RandomRange< my_generator>  rr( my_engine(), ::time( nullptr), -100, 100, 1000);
/// </pre>
///
/// @since  1.45.0, 23.01.2021
template< typename R = DefaultRand, typename T = int> class RandomRange
{
public:
   /// Iterator provided by this module.
   using const_iterator = detail::RandomRangeIter< const RandomRange< R, T>, T>;

   /// Constructor for using one of the predefined random number generators.
   ///
   /// @param[in]  seed
   ///    Seed to initialise the random number generator with.
   /// @param[in]  lower_bound
   ///    Lower bound for the random numbers to create.
   /// @param[in]  upper_bound
   ///    Upper bound for the random numbers to create.
   /// @param[in]  num_values
   ///    Number of random values to create.
   /// @since  1.45.0, 23.01.2021
   RandomRange( int64_t seed, T lower_bound, T upper_bound, int64_t num_values);

   /// Constructor for using a customised random number generator.
   ///
   /// @tparam  G  The type of the engine to use.
   /// @param[in]  engine
   ///    Engine to use.
   /// @param[in]  seed
   ///    Seed to initialise the random number generator with.
   /// @param[in]  lower_bound
   ///    Lower bound for the random numbers to create.
   /// @param[in]  upper_bound
   ///    Upper bound for the random numbers to create.
   /// @param[in]  num_values
   ///    Number of random values to create.
   /// @since  1.45.0, 08.04.2021
   template< typename G> RandomRange( const G& engine, int64_t seed,
      T lower_bound, T upper_bound, int64_t num_values);

   /// Returns a const iterator that provides the first random number generated.
   /// Be aware that it is possible to call this method multiple times to get
   /// multiple iterators, each providing the maximum number of random numbers,
   /// but the numbers of the iterators would not be the same.
   ///
   /// @return  Const iterator with the first random number.
   /// @since  1.45.0, 23.01.2021
   const_iterator begin() const;

   /// Returns a const iterator that provides the first random number generated.
   /// Be aware that it is possible to call this method multiple times to get
   /// multiple iterators, each providing the maximum number of random numbers,
   /// but the numbers of the iterators would not be the same.
   ///
   /// @return  Const iterator with the first random number.
   /// @since  1.45.0, 23.01.2021
   const_iterator cbegin() const;

   /// Returns a const iterator that can be used to test the range end condition.
   ///
   /// @return  Const end iterator.
   /// @since  1.45.0, 23.01.2021
   const_iterator end() const;

   /// Returns a const iterator that can be used to test the range end condition.
   ///
   /// @return  Const end iterator.
   /// @since  1.45.0, 23.01.2021
   const_iterator cend() const;

   /// Returns the next random number in the given range.
   /// Used also by the iterators.
   ///
   /// @return  The next random number.
   /// @since  1.45.0, 23.01.2021
   T nextRand() const;

private:
   /// Random number generator.
   R        mRandomGen;
   /// Lower bound for the random numbers to generate.
   T        mLowerBound;
   /// Upper bound for the random numbers to generate.
   T        mUpperBound;
   /// Maximum of random numbers to generate.
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
   template< typename G>
      RandomRange< R, T>::RandomRange( const G& engine, int64_t seed, T lower_bound,
      T upper_bound, int64_t num_values):
         mRandomGen( detail::Custom< G>( engine, seed)),
         mLowerBound( lower_bound),
         mUpperBound( upper_bound),
         mNumValues( num_values)
{
} // RandomRange< R, T>::RandomRange


template< typename R, typename T>
   typename RandomRange< R, T>::const_iterator RandomRange< R, T>::begin() const
{
   return const_iterator( this, mNumValues);
} // RandomRange< R, T>::begin


template< typename R, typename T>
   typename RandomRange< R, T>::const_iterator RandomRange< R, T>::cbegin() const
{
   return const_iterator( this, mNumValues);
} // RandomRange< R, T>::cbegin


template< typename R, typename T>
   typename RandomRange< R, T>::const_iterator RandomRange< R, T>::end() const
{
   return const_iterator( this);
} // RandomRange< R, T>::end


template< typename R, typename T>
   typename RandomRange< R, T>::const_iterator RandomRange< R, T>::cend() const
{
   return const_iterator( this);
} // RandomRange< R, T>::cend


template< typename R, typename T> T RandomRange< R, T>::nextRand() const
{
   return static_cast< T>( mRandomGen.nextRand() % (mUpperBound - mLowerBound))
      + mLowerBound;
} // RandomRange::nextRand


} // namespace celma::common


// =====  END OF random.hpp  =====

