
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


#ifndef CELMA_COMMON_OBJECT_POOL_HPP
#define CELMA_COMMON_OBJECT_POOL_HPP


#include <deque>
#include <memory>
#include "singleton.hpp"


namespace celma { namespace common {


/// Object pool that keeps unused object instead of deleting them.<br>
/// There is one pool per object type.<br>
/// The object pool is implemented as a singleton, so no object needs to be
/// created manually.
template< typename T> class ObjectPool: public Singleton< ObjectPool< T>>
{

   friend class Singleton< ObjectPool< T>>;

public:
   /// 
   /// @return  .
   /// @since  x.y, 29.01.2017
   T* getObject();

   void putObject( T* obj);

   size_t size() const;

   void fillPool( size_t num_objects);

   void clear();
   
private:
   static std::unique_ptr< ObjectPool< T>>  mpInstance;

   ObjectPool();

   std::deque< std::unique_ptr< T>>  mObjectPool;

}; // ObjectPool< T>


template< typename T>
   std::unique_ptr< ObjectPool< T>>  ObjectPool< T>::mpInstance;


// inlined methods
// ===============


template< typename T> T* ObjectPool< T>::getObject()
{
   if (mObjectPool.empty())
   {
      return new T();
   }
   T* result = mObjectPool.back().release();
   mObjectPool.pop_back();
   return result;
} // ObjectPool< T>::getObject


template< typename T> void ObjectPool< T>::putObject( T* obj)
{
   mObjectPool.push_front( std::unique_ptr< T>( obj));
}


template< typename T> size_t ObjectPool< T>::size() const
{
   return mObjectPool.size();
}


template< typename T> void ObjectPool< T>::fillPool( size_t num_objects)
{
   for (size_t i = 0; i < num_objects; ++i)
      mObjectPool.push_back( new T());
}


template< typename T> void ObjectPool< T>::clear()
{
   mObjectPool.clear();
} // ObjectPool< T>::clear
   

template< typename T> ObjectPool< T>::ObjectPool():
   mObjectPool()
{
}


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_OBJECT_POOL_HPP


// =========================  END OF object_pool.hpp  =========================

