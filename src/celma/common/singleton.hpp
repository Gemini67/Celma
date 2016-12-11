
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


#ifndef CELMA_COMMON_SINGLETON_HPP
#define CELMA_COMMON_SINGLETON_HPP


#include <memory>
#include <mutex>


namespace celma { namespace common {


/// Template for creating singleton classes. The template prevents creating of
/// multiple instances, copying etc.<br>
/// Usage:
/// - Derive the class from this template, with the class itself as template
///   parameter.
/// - The class must have a constructor that is protected.
/// - The template Singleton must be defined as friend.
/// .
/// The singleton template creates an object when required and stores it in a
/// std::unique_ptr<>. Creating the singleton object as a static member of a
/// member function is not supported anymore.
/// @since  0.10, 11.12.2016 (removed singleton creator policy)
/// @since  0.2, 10.04.2016
template< class T> class Singleton
{
public:
   /// Returns the singleton instance.<br>
   /// Uses the double checking locking pattern to prevent multiple threads
   /// from creating the same object multiple times.
   /// @return  The singleton object of the template class.
   /// @since  0.2, 10.04.2016
   static T& instance();

   /// Use default destructor.
   ~Singleton() = default;

protected:
   /// Empty constructor.
   /// @since  0.2, 10.04.2016
   Singleton() { }

private:
   /// Don't copy.
   /// @since  0.2, 10.04.2016
   Singleton( const Singleton&) = delete;

   /// Don't assign.
   /// @since  0.2, 10.04.2016
   Singleton& operator =( const Singleton&) = delete;

   /// The singleton object, created when instance() is called for the first time.
   static std::unique_ptr< T>  mpObject;

}; // Singleton< T>


template< class T> std::unique_ptr< T>  Singleton< T>::mpObject;


// inlined methods
// ===============


template< class T> T& Singleton< T>::instance()
{

   static std::mutex  mtx;

   if (mpObject.get() == nullptr)
   {
      const std::lock_guard< std::mutex>  lg( mtx);
      if (mpObject.get() == nullptr)
      {
         mpObject.reset( new T());
      } // end if
   } // end if

   return *mpObject;
} // end Singleton< T>::instance


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_SINGLETON_HPP


// ==========================  END OF singleton.hpp  ==========================

