
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
/// See documentation of class celma::common::detail::StaticSingletonCreator.


#ifndef CELMA_COMMON_DETAIL_STATIC_SINGLETON_CREATOR_HPP
#define CELMA_COMMON_DETAIL_STATIC_SINGLETON_CREATOR_HPP


#include "celma/common/celma_exception.hpp"


namespace celma { namespace common { namespace detail {


/// Creates one object of the template type using a static object creating in
/// the create() method.<br>
/// This is the method to use as suggested by Alexandrescu.
/// @tparam  T  The class to create a singleton object of.
/// @since  0.2, 10.04.2016
template< class T> class StaticSingletonCreator
{
public:
   /// Always throws, static object cannot be destroyed.
   /// @throw  CelmaRuntimeError.
   /// @since  0.2, 10.04.2016
   static void destroy() noexcept( false)
   {
      throw CELMA_RuntimeError( "cannot destroy static object");
   } // end StaticSingletonCreator< T>::destroy

protected:
   /// Here we are: Create the singleton object.
   /// @since  0.2, 10.04.2016
   static void create()
   {
      static T  object;
      mpInstance = &object;
   } // end StaticSingletonCreator< T>::create

   /// Returns a pointer (!) to the singleton object.
   /// @return  Pointer to the singleton object.
   /// @since  0.2, 10.04.2016
   static T* getInstance()
   {
      return mpInstance;
   } // end StaticSingletonCreator< T>::getInstance

   /// Pointer to the singleton object.
   static T*  mpInstance;

}; // StaticSingletonCreator< T>


template< class T> T* StaticSingletonCreator< T>::mpInstance = nullptr;


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_STATIC_SINGLETON_CREATOR_HPP


// =========================  END OF static_singleton_creator.hpp  =========================

