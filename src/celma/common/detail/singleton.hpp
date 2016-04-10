
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// See documentation of class celma::common::detail::Singleton.


#ifndef CELMA_COMMON_DETAIL_SINGLETON_HPP
#define CELMA_COMMON_DETAIL_SINGLETON_HPP


#include <mutex>
#include "celma/common/detail/static_singleton_creator.hpp"
#include "celma/common/detail/dynamic_singleton_creator.hpp"


namespace celma { namespace common { namespace detail {


/// Template for creating singleton classes. The template prevents creating of
/// multiple instances, copying etc.<br>
/// Usage:
/// - Derive the class from this template, with the class itself as template
///   parameter.
/// - The class must have a constructor that is protected.
/// - The template Singleton must be defined as friend.
///
/// @todo: Use atomic operations to make the instance pointer thread safe.
///
/// @since  0.2, 10.04.2016
template< class T, template< typename> class C = StaticSingletonCreator>
   class Singleton: private C< T>
{
public:
   // would like to do the following, but that needs C++14 or so
   //   typedef C< T>::Creator;

   /// Returns the singleton instance.<br>
   /// Uses the double checking locking pattern to prevent multiple threads
   /// from creating the same object multiple times.
   /// @return  The singleton object of the template class.
   /// @since  0.2, 10.04.2016
   static T& instance();

   // method to destroy the object is taken from the policy
   using C< T>::destroy;

protected:
   /// Empty constructor.
   /// @since  0.2, 10.04.2016
   Singleton() { };

private:
   /// Don't copy.
   /// @since  0.2, 10.04.2016
   Singleton( const Singleton&) = delete;

   /// Don't assign.
   /// @since  0.2, 10.04.2016
   Singleton& operator =( const Singleton&) = delete;

   // method to create the object is taken from the policy
   using C< T>::create;
   // method to access the object is taken from the policy
   using C< T>::getInstance;

}; // Singleton< T>


// inlined methods
// ===============


template< class T, template< typename> class C> T& Singleton< T, C>::instance()
{

   static std::mutex  mtx;

   // actually this is not completely thread safe
   // the instance pointer should be handled by atomic operations to be really
   // thread safe
   if (getInstance() == nullptr)
   {
      std::lock_guard< std::mutex>  lg( mtx);
      if (getInstance() == nullptr)
      {
         create();
      } // end if
   } // end if

   return *getInstance();
} // end Singleton<T>::instance


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_SINGLETON_HPP


// =========================  END OF singleton.hpp  =========================

