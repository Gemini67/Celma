
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::DynamicSingletonCreator.


#ifndef CELMA_COMMON_DETAIL_DYNAMIC_SINGLETON_CREATOR_HPP
#define CELMA_COMMON_DETAIL_DYNAMIC_SINGLETON_CREATOR_HPP


#include <memory>


namespace celma { namespace common { namespace detail {


/// Dynamically creates an object of the template type. This allows to delete
/// this object later and eventually create a new one.
/// @tparam  T  The class to create a singleton object of.
/// @since  0.2, 10.04.2016
template< class T> class DynamicSingletonCreator
{
public:
   /// Destroys the object.
   /// @since  0.2, 10.04.2016
   static void destroy()
   {
      mpInstance.reset();
   } // end DynamicSingletonCreator< T>::destroy

protected:
   /// Creates a new object.
   /// @since  0.2, 10.04.2016
   static void create()
   {
      mpInstance.reset( new T());
   } // end DynamicSingletonCreator< T>::create

   /// Returns a pointer (!) to the singleton object.
   /// @return  Pointer to the singleton object.
   /// @since  0.2, 10.04.2016
   static T* getInstance()
   {
      return mpInstance.get();
   } // end DynamicSingletonCreator< T>::getInstance

   /// Pointer to the singleton object.
   static std::unique_ptr< T>  mpInstance;

}; // DynamicSingletonCreator< T>


template< class T> std::unique_ptr< T>  DynamicSingletonCreator< T>::mpInstance;


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_DYNAMIC_SINGLETON_CREATOR_HPP


// =========================  END OF dynamic_singleton_creator.hpp  =========================

