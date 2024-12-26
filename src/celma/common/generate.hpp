
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::@@@.


#pragma once


#include "celma/common/detail/generator_iterator.hpp"


namespace celma::common {


template< typename C> class GeneratorRange
{
public:
   using const_iterator = detail::GeneratorIterator< C>;

   GeneratorRange( C& generator, size_t num_values):
      mpGenerator( &generator),
      mNumValues( num_values)
   {
   }

   const_iterator begin() const
   {
      return const_iterator( mpGenerator, mNumValues);
   }

   const_iterator end() const
   {
      return const_iterator( mpGenerator);
   }

private:
   C*      mpGenerator;
   size_t  mNumValues;

};


template< typename C> auto generate( C& generator, size_t num_values)
{
   return GeneratorRange( generator, num_values);
}


} // namespace celma::common


// =====  END OF generate.hpp  =====

