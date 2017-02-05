
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


#ifndef CELMA_COMMON_SINGLETON_HPP
#define CELMA_COMMON_SINGLETON_HPP


#include <memory>
#include <mutex>
#include <utility>


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
   /// If no singleton object exists yet, a new one is created with the
   /// specified parameters. If a singletob object exists already, the
   /// parameters are ignored.<br>
   /// Uses the double checking locking pattern to prevent multiple threads
   /// from creating the same object multiple times.
   /// @tparam  Args  The types of the parameters to pass to the object's
   ///                constructor.
   /// @param[in]  args  The parameters to pass to the constructor of the
   ///                   singleton object.
   /// @return  The singleton object of the template class.
   /// @since  0.12.2, 05.02.2017  (enhanced with perfect forwarding parameters)
   /// @since  0.2, 10.04.2016
   template< class... Args> static T& instance( Args&&... args);

   /// Deletes an existing singleton object. Upon a subsequent call to
   /// instance(), a new singleton object will be created.
   /// @since  0.12.2, 05.02.2017
   static void reset();

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

   /// Mutex object used to make the creation/resetting of the singleton object
   /// thread-safe.
   static std::mutex           mMutex;
   /// The singleton object, created when instance() is called for the first
   /// time.
   static std::unique_ptr< T>  mpObject;

}; // Singleton< T>


template< class T> std::mutex           Singleton< T>::mMutex;
template< class T> std::unique_ptr< T>  Singleton< T>::mpObject;


// inlined methods
// ===============


template< class T> template< class... Args>
   T& Singleton< T>::instance( Args&&... args)
{

   if (mpObject.get() == nullptr)
   {
      const std::lock_guard< std::mutex>  lg( mMutex);
      if (mpObject.get() == nullptr)
      {
         mpObject.reset( new T( std::forward< Args>( args)...));
      } // end if
   } // end if

   return *mpObject;
} // Singleton< T>::instance


template< class T> void Singleton< T>::reset()
{

   const std::lock_guard< std::mutex>  lg( mMutex);
   mpObject.reset();
   
} // Singleton< T>::reset


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_SINGLETON_HPP


// ==========================  END OF singleton.hpp  ==========================

