
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
/// See documentation of template class celma::common::OptionalPtr<>.


#include <memory>


namespace celma::common {


/// Smart pointer that manages a pointer to an object which it may own or may be
/// owned by somebody else.
/// If a raw pointer is passed, external ownership is assumed. Only when a
/// unique pointer is passed, ownership is taken from there.
/// @since  1.48.0, 03.05.2023
template< typename T> class OptionalPtr
{
public:
   /// (Default) Constructor.
   /// @param[in]  ptr  Pointer to an externally managed object, may be NULL.
   /// @since  1.48.0, 03.05.2023
   explicit OptionalPtr( T* ptr = nullptr);

   /// Constructor that takes ownership from the given unique pointer.
   /// @param[in]  ptr  Unique pointer, object (pointer) is moved from there.
   /// @since  1.48.0, 03.05.2023
   explicit OptionalPtr( std::unique_ptr< T> ptr);

   // copying objects of this class is not permitted
   OptionalPtr( const OptionalPtr&) = delete;

   /// Move constructor.
   /// @param[in]  other  Other object to move the data from.
   /// @since  1.48.0, 03.05.2023
   OptionalPtr( OptionalPtr&& other) noexcept;

   /// Destructor, deletes the object if it was owned.
   /// @since  1.48.0, 03.05.2023
   ~OptionalPtr();

   /// Returns if this object owns the object (pointer).
   /// Always returns \c false if it currently does not hold an object
   /// (pointer).
   /// @returns  \c true if this object holds and owns an object (pointer).
   /// @since  1.48.0, 03.05.2023
   [[nodiscard]] bool isOwning() const noexcept;

   /// Returns the (pointer to) the internally stored object.
   /// May be NULL.
   /// @returns  Pointer to the internally stored object.
   /// @since  1.48.0, 03.05.2023
   [[nodiscard]] T* get() const noexcept;

   /// Dereference operator.
   /// @return  Const pointer to the internally stored object.
   /// @since  1.48.0, 03.05.2023
   [[nodiscard]] const T* operator ->() const;

   /// Non-const dereference operator.
   /// @return  Pointer to the internally stored object.
   /// @since  1.48.0, 03.05.2023
   [[nodiscard]] T* operator ->();

   /// Indirection operator.
   /// @return  Const reference of the internally stored object.
   /// @since  1.48.0, 03.05.2023
   [[nodiscard]] const T& operator *() const;

   /// Non-const indirection operator.
   /// @return  Reference of the internally stored object.
   /// @since  1.48.0, 03.05.2023
   [[nodiscard]] T& operator *();

   /// Returns the (pointer to) the internally stored object.
   /// If there was an object stored, the pointer is cleared.
   /// @returns  Pointer to the internally stored object.
   /// @since  1.48.0, 03.05.2023
   [[nodiscard]] T* release() noexcept;

   /// Replaces the internally stored object (pointer) with the given new one.
   /// If the previous object was owned by this object, it is deleted.
   /// @param[in]  ptr  Pointer to the new, externally managed object to store.
   /// @since  1.48.0, 03.05.2023
   void reset( T* ptr = nullptr);

   /// Replaces the internally stored object with the given new one.
   /// This object takes ownership of the object (pointer).<br>
   /// If the previous object was owned by this object, it is deleted.
   /// @param[in]  ptr  Unique pointer to take the object (pointer) from.
   /// @since  1.48.0, 03.05.2023
   void reset( std::unique_ptr< T> ptr);

   // copy-assignment of objects of this class is not permitted
   OptionalPtr& operator =( const OptionalPtr&) = delete;

   /// Move-assignment operator.
   /// @param[in]  other  Other object to move the data from.
   /// @returns  This object.
   /// @since  1.48.0, 03.05.2023
   OptionalPtr& operator =( OptionalPtr&& other) noexcept;

   /// Boolean conversion operator, returns if this object contains an object
   /// (pointer).
   /// @returns  \c true if this object contains an object (pointer), owning or
   ///           non-owning.
   /// @since  1.48.0, 03.05.2023
   [[nodiscard]] operator bool() const noexcept;

protected:
   /// Pointer to the object to manage.
   T*    mpObject = nullptr;
   /// Flag, set to \c true if this object is the owner of the object pointed to
   /// by #mpObject.
   bool  mIsOwning = false;

}; // OptionalPtr< T>


// inlined methods
// ===============


template< typename T> OptionalPtr< T>::OptionalPtr( T* ptr):
   mpObject( ptr)
{
} // OptionalPtr< T>::OptionalPtr


template< typename T> OptionalPtr< T>::OptionalPtr( std::unique_ptr< T> ptr):
   mpObject( ptr.release()),
   mIsOwning( true)
{
} // OptionalPtr< T>::OptionalPtr


template< typename T>
   OptionalPtr< T>::OptionalPtr( OptionalPtr&& other) noexcept:
      mpObject( other.mpObject),
      mIsOwning( other.mIsOwning)
{
   other.mpObject = nullptr;
   other.mIsOwning = false;
} // OptionalPtr< T>::OptionalPtr


template< typename T> OptionalPtr< T>::~OptionalPtr()
{
   if (mIsOwning)
      delete mpObject;
} // OptionalPtr< T>::~OptionalPtr


template< typename T> bool OptionalPtr< T>::isOwning() const noexcept
{
   return mIsOwning;
} // OptionalPtr< T>::isOwning


template< typename T> T* OptionalPtr< T>::get() const noexcept
{
   return mpObject;
} // OptionalPtr< T>::get


template< typename T> const T* OptionalPtr< T>::operator ->() const
{
   return mpObject;
} // OptionalPtr< T>::operator ->


template< typename T> T* OptionalPtr< T>::operator ->()
{
   return mpObject;
} // OptionalPtr< T>::operator ->


template< typename T> const T& OptionalPtr< T>::operator *() const
{
   return *mpObject;
} // OptionalPtr< T>::operator *


template< typename T> T& OptionalPtr< T>::operator *()
{
   return *mpObject;
} // OptionalPtr< T>::operator *


template< typename T> T* OptionalPtr< T>::release() noexcept
{
   auto *  save = mpObject;
   mpObject = nullptr;
   mIsOwning = false;
   return save;
} // OptionalPtr< T>::release


template< typename T> void OptionalPtr< T>::reset( T* ptr)
{
   if (mIsOwning)
      delete mpObject;
   mpObject = ptr;
   mIsOwning = false;
} // OptionalPtr< T>::reset


template< typename T> void OptionalPtr< T>::reset( std::unique_ptr< T> ptr)
{
   if (mIsOwning)
      delete mpObject;
   mpObject = ptr.release();
   mIsOwning = true;
} // OptionalPtr< T>::reset


template< typename T>
   OptionalPtr< T>& OptionalPtr< T>::operator =( OptionalPtr&& other) noexcept
{
   if (mIsOwning)
      delete mpObject;

   mpObject = other.mpObject;
   mIsOwning = other.mIsOwning;

   // don't use other.reset() here!
   other.mpObject = nullptr;
   other.mIsOwning = false;

   return *this;
} // OptionalPtr< T>::operator =


template< typename T> OptionalPtr< T>::operator bool() const noexcept
{
   return mpObject != nullptr;
} // OptionalPtr< T>::operator bool


} // namespace celma::common


// =====  END OF optional_ptr.hpp  =====

