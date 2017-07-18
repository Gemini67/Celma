
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::@@@.


#ifndef CELMA_COMMON_MAKE_POOLED_PTR_HPP
#define CELMA_COMMON_MAKE_POOLED_PTR_HPP


#include <utility>
#include "object_pool.hpp"


namespace celma { namespace common {


namespace {


class PoolDeleter
{
public:
   template< typename T> void operator ()( T* ptr)
   {
      if (ptr != nullptr)
         ObjectPool< T>::instance().putObject( ptr);
   }

};


} // namespace


/// Returns an object from the pool. If the pool is empty, a new object is
/// created.
template< typename T> std::unique_ptr< T, PoolDeleter> make_pooled_ptr()
{
   return std::unique_ptr< T, PoolDeleter>( ObjectPool< T>::instance().getObject());
}


/// Creates a new object with the specified parameters. When the object is
/// deleted, it will be added to the pool.
template< typename T, typename A1, typename... Args>
   std::unique_ptr< T, PoolDeleter> make_pooled_ptr( A1&& a1, Args&&... args)
{
   return std::unique_ptr< T, PoolDeleter>( new T( std::forward< A1>( a1),
                                                   std::forward< Args>( args)...));
}


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_MAKE_POOLED_PTR_HPP


// =======================  END OF make_pooled_ptr.hpp  =======================

