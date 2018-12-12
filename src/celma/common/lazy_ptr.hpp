
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::lazy_ptr.


#ifndef CELMA_COMMON_LAZY_PTR_HPP
#define CELMA_COMMON_LAZY_PTR_HPP


#include <functional>
#include <memory>
#include <utility>


namespace celma { namespace common {


/// Smart pointer that creates an object only when it is needed.<br>
/// The idea is that the parameters to create an object are passed in when the
/// lazy_ptr object is created. But only when get() or the operator ->() are
/// called, the object is actually created.<br>
/// In other words: If get() or the operator ->() are never called, no object
/// is created.<br>
/// Once the object is created, the lazy_ptr<> behaves like a unique_ptr<>
/// (which is actually used internally): Copying is not allowed, moving is.
/// And of course, the object is deleted when the lazy_ptr<> object is
/// deleted.<br>
/// It is also possible to reset() the internal object pointer, and then get a
/// new object created afterwards by calling get() again.<br>
/// The name of this class was written in this format in order to correspond to
/// the names of the smart pointers in the standard library.
///
/// @tparam  T  the type of the object to create lazily.
/// @since  1.11.0, 07.09.2018
template< typename T> class lazy_ptr
{
public:
   /// Default constructor. Will create the object by calling its default
   /// constructor.
   ///
   /// @since  1.11.0, 07.09.2018
   lazy_ptr():
      mpCreator( []() -> T*
         {
            return new T();
         }
      ),
      mpObject()
   {
   } // lazy_ptr< T>:: lazy_ptr

   /// Copying is not allowed:
   /// - We don't know if it's okay to copy the parameters for delayed creation
   ///   of the object.
   /// - The object must not be copied anyway.
   lazy_ptr( const lazy_ptr&) = delete;

   /// Move constructor.
   ///
   /// @param[in]  other
   ///    The other object to move the data from.
   /// @since  1.11.0, 07.09.2018
//   lazy_ptr( lazy_ptr&& other) = default;
   lazy_ptr( lazy_ptr&& other) = delete;

   /// Handles delayed creation of an object with exactly one parameter.
   ///
   /// @tparam  F  The type of the single parameter.
   /// @param[in]  first
   ///    The value to pass to the constructor when it is created (later,
   ///    eventually).<br>
   ///    The value is copied internally.
   /// @since  1.11.0, 07.09.2018
   template< typename F> explicit lazy_ptr( const F& first):
      mpCreator( [=]() -> T*
         {
            return new T( first);
         }
      ),
      mpObject()
   {
   } // lazy_ptr< T>::lazy_ptr

   /// Constructor for delayed creation of the object with an arbitrary number
   /// of parameters.<br>
   /// This two parameter approach was chosen in order to distinguish this
   /// constructor from e.g. the default constructor or the move constructor.<br>
   /// All parameters/values are copied internally.
   ///
   /// @tparam  F
   ///    The type of the first parameter.
   /// @tparam  Args
   ///    The types of the following parameters.
   /// @param[in]  first
   ///    The first value to pass to the object's constructor.
   /// @param[in]  args
   ///    The remaining values to pass to the object's constructor.
   /// @since  1.11.0, 07.09.2018
   template< typename F, class... Args> lazy_ptr( const F& first, Args&&... args):
      mpCreator( [=]() mutable -> T*
         {
            return new T( first, std::forward< Args>( args)...);
         }
      ),
      mpObject()
   {
   } // lazy_ptr< T>::lazy_ptr

   /// Default destructor.
   ~lazy_ptr() = default;

   /// Returns pointer to the internally stored object.<br>
   /// If no object is stored yet, one is created with the parameters specified
   /// on one of the constructors.
   ///
   /// @return  Pointer to the object, which was eventually just created now.
   /// @since  1.11.0, 07.09.2018
   T* get()
   {
      if (mpObject == nullptr)
         mpObject.reset( mpCreator());
      return mpObject.get();
   } // lazy_ptr< T>::get

   /// Returns pointer to the internally stored object.<br>
   /// If no object is stored yet, one is created with the parameters specified
   /// on one of the constructors.
   ///
   /// @return  Pointer to the object, which was eventually just created now.
   /// @since  1.11.0, 07.09.2018
   T* operator ->()
   {
      return mpObject.get();
   } // lazy_ptr< T>::operator ->

   /// Returns if this instance already contains an object.
   ///
   /// @return  \c true if a pointer to an existing object is stored internally.
   /// @since  1.11.0, 07.09.2018
   operator bool() const
   {
      return static_cast< bool>( mpObject);
   } // lazy_ptr< T>::operator bool

   /// Allows to reset the internally stored object pointer, i.e. the object is
   /// deleted if there is one.
   ///
   /// @since  1.11.0, 07.09.2018
   void reset()
   {
      mpObject.reset();
   } // lazy_ptr< T>::reset

   /// Returns the pointer to the internally stored object, which is not
   /// managed afterwards.<br>
   /// In other words: This lazy_ptr<> object does not hold a pointer to an
   /// object of type \c T anymore.
   ///
   /// @return
   ///    Pointer to the object that was stored internally. May be NULL.
   /// @since
   ///    1.11.0, 11.09.2018
   T* release()
   {
      return mpObject.release();
   } // lazy_ptr< T>::release

private:
   /// Function object used to create the destination object when required.
   std::function< T*( void)>  mpCreator;
   /// The destination object.
   std::unique_ptr< T>        mpObject;

}; // lazy_ptr< T>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_LAZY_PTR_HPP


// =====  END OF lazy_ptr.hpp  =====

