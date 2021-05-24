
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
/// See documentation of classes
/// - celma::common::detail::UnixRandom,
/// - celma::common::detail::Predefined<>
/// - celma::common::detail::Custom<>


#pragma once


#include <cstdlib>


namespace celma::common::detail {


/// Allows to use the standard C random number generator with the random range
/// class.
///
/// @since  1.45.0, 23.01.2021
class UnixRandom
{
public:
   /// Constructor, sets the seed for the random number generator.
   ///
   /// @param[in]  seed  The seed to set.
   /// @since  1.45.0, 23.01.2021
   UnixRandom( int64_t seed)
   {
      ::srand( seed);
   } // UnixRandom::UnixRandom

   /// Returns the next random number.
   ///
   /// @return  The next random number.
   /// @since  1.45.0, 23.01.2021
   uint64_t nextRand() const
   {
      return rand();
   } // UnixRandom::nextRand

}; // UnixRandom


/// Wrapper class to use one of the predefined random number generators.
///
/// @tparam  R  The type of the random number generator.
/// @since  1.45.0, 23.01.2021
template< typename R> class Predefined
{
public:
   /// Constructor, initialises the generator with the seed.
   ///
   /// @param[in]  seed
   ///    Seed for the initialisation of the random number generator.
   /// @since  1.45.0, 23.01.2021
   Predefined( int64_t seed):
      mGenerator( seed)
   {
   } // Predefined< R>::Predefined

   /// Returns the next random number.
   ///
   /// @return  The next random number.
   /// @since  1.45.0, 23.01.2021
   uint64_t nextRand() const
   {
      return mGenerator();
   } // Predefined< R>::nextRand

private:
   /// The random number generator. Mutable because creating the next random
   /// number modifies internal state of the generator.
   mutable R  mGenerator;

}; // Predefined< R>


/// Wrapper class to use a customised random number generator.
///
/// @tparam  R  The type of the random number generator.
/// @since  1.45.0, 23.01.2021
template< typename R> class Custom
{
public:
   /// Constructor, stores the generator and initialises it with the given seed.
   ///
   /// @param[in]  engine
   ///    Random number engine to use.
   /// @param[in]  seed
   ///    Seed for the initialisation of the random number generator.
   /// @since  1.45.0, 23.01.2021
   Custom( const R& engine, int64_t seed):
      mGenerator( engine)
   {
      mGenerator.seed( seed);
   } // Custom< R>::Custom

   /// Returns the next random number.
   ///
   /// @return  The next random number.
   /// @since  1.45.0, 23.01.2021
   uint64_t nextRand() const
   {
      return mGenerator();
   } // Custom< R>::nextRand

private:
   /// The random number generator. Mutable because creating the next random
   /// number modifies internal state of the generator.
   mutable R  mGenerator;

}; // Custom< R>


} // namespace celma::common::detail


// =====  END OF random.hpp  =====

