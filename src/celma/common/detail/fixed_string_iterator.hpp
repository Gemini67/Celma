
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class
/// celma::common::detail::FixedStringIterator<>.


#pragma once


#include <iterator>
#include <limits>


namespace celma::common::detail {


/// Random access iterator for fixed strings.
/// @tparam  T  The type of the value stored in the fixed string.<br>
///             Used to distinguish between non-const and const chars.
/// @tparam  F  The type of the fixed string.<br>
///             Passed as template parameter to prevent circular dependencies.
/// @since  x.y.z, 20.01.2021
template< typename T, typename F> class FixedStringIterator final:
   public std::iterator< std::random_access_iterator_tag, void*>
{
public:
   /// The type of references that are returned by this class (const or
   /// non-const).
   using reference = T&;

   /// Default construction is allowed.
   /// @since  x.y.z, 20.01.2021
   FixedStringIterator() = default;

   /// Constructor for an iterator that points to the beginning of a string.
   /// @param[in]  obj  Pointer to the object to iterate over.
   /// @since  x.y.z, 21.01.2021
   explicit FixedStringIterator( F* obj);

   /// Constructor for an iterator that points to a specific position.
   /// @param[in]  obj  Pointer to the object to iterate over.
   /// @param[in]  pos  The position to start iterating from.
   /// @since  x.y.z, 20.01.2021
   FixedStringIterator( F* obj, size_t pos);

   /// Constructor for end iterators.
   /// @param[in]  end  Dummy parameter to distinguish the constructor.
   /// @param[in]  obj  Pointer to the object to iterate over.
   /// @since  x.y.z, 21.01.2021
   FixedStringIterator( bool end, F* obj);

   // Default copy constructor, move-constructor and destructor are fine.
   FixedStringIterator( const FixedStringIterator&) = default;
   FixedStringIterator( FixedStringIterator&&) = default;
   ~FixedStringIterator() = default;

   /// Returns the character at the current position.
   /// @return  Reference of the character at the current position.
   /// @throws  std::invalid_argument if no object was assigned to the iterator.
   /// @throws  std::range_error if the iterator points behind the end of the
   ///          string.
   /// @since  x.y.z, 20.01.2021
   reference operator *() const;

   /// Default copy- and move-assignment are fine.
   FixedStringIterator& operator =( const FixedStringIterator&) = default;
   FixedStringIterator& operator =( FixedStringIterator&&) = default;

   /// Equality comparison operator.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if both objects point to the same position in the same
   ///          string, or both objects point behind the end of their strings.
   /// @since  x.y.z, 20.01.2021
   bool operator ==( const FixedStringIterator& other) const noexcept;

   /// Difference comparison operator.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if the two objects either handle different strings, or
   ///          point to different positions.
   /// @since  x.y.z, 20.01.2021
   bool operator !=( const FixedStringIterator& other) const noexcept;

   /// Returns if this object points to a position before the other object's
   /// position.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if both objects handle the same string, and this object
   ///          points to a position before that of the other object.
   /// @since  x.y.z, 20.01.2021
   bool operator <( const FixedStringIterator& other) const noexcept;

   /// Returns if this object points to the same position, or a position before
   /// the other object's position.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if both objects handle the same string, and this object
   ///          points to a position before that of the other object, or both
   ///          point to the same position.
   /// @since  x.y.z, 20.01.2021
   bool operator <=( const FixedStringIterator& other) const noexcept;

   /// Returns if this object points to the same position, or a position behind
   /// the other object's position.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if both objects handle the same string, and this object
   ///          points to a position after that of the other object, or both
   ///          point to the same object.
   /// @since  x.y.z, 20.01.2021
   bool operator >=( const FixedStringIterator& other) const noexcept;

   /// Returns if this object points to a position behind the other object's
   /// position.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if both objects handle the same string, and this object
   ///          points to a position after that of the other object.
   /// @since  x.y.z, 20.01.2021
   bool operator >( const FixedStringIterator& other) const noexcept;

   /// Increments the current position of the iterator, unless it already points
   /// behind the string.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedStringIterator& operator ++();

   /// Increments the current position of the iterator, unless it already points
   /// behind the string.
   /// @param[in]  int  Dummy parameter to distinguish pre- and postfix
   ///                  increment operators.
   /// @return  Iterator pointing to the previous position of this iterator.
   /// @since  x.y.z, 20.01.2021
   FixedStringIterator operator ++( int);

   /// Decrements the current position of the iterator, unless it already points
   /// behind the string.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedStringIterator& operator --();

   /// Decrements the current position of the iterator, unless it already points
   /// behind the string.
   /// @param[in]  int  Dummy parameter to distinguish pre- and postfix
   ///                  increment operators.
   /// @return  Iterator pointing to the previous position of this iterator.
   /// @since  x.y.z, 20.01.2021
   FixedStringIterator operator --( int);

   /// Increments the position of the iterator by the given value.
   /// @param[in]  value  Position increment.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedStringIterator& operator +=( size_t value) noexcept;

   /// Decrements the position of the iterator by the given value.
   /// @param[in]  value  Position decrement.
   /// @return  This object.
   /// @since  x.y.z, 20.01.2021
   FixedStringIterator& operator -=( size_t value) noexcept;

   /// Index operator.
   /// @param[in]  idx  Index offset to the current position of the iterator.
   /// @return  Reference of the character at the specified position.
   /// @since  x.y.z, 20.01.2021
   reference operator[]( size_t idx) const;

   /// Helper to get the length of the string that this iterator is handling.
   /// @return  The length of the string which is referenced by this iterator,
   ///          0 if no object is assigned.
   /// @since  x.y.z, 28.01.2021
   size_t length() const;

   /// Difference between two iterators.
   /// @param[in]  lhs  The first iterator.
   /// @param[in]  rhs  The second iterator.
   /// @return  The difference of the positions of the two iterators.
   /// @throws  std::invalid_argument if one of the two iterators does not 
   ///          handle the same fixed string object, or if one of the iterators
   ///          does not have a valid position.
   /// @since  x.y.z, 21.01.2021
   friend size_t operator -( const FixedStringIterator& lhs,
      const FixedStringIterator& rhs)
   {
      if ((lhs.mpObject == nullptr) || (rhs.mpObject == nullptr)
          || (lhs.mpObject != rhs.mpObject))
         throw std::invalid_argument( "no/other object assigned to iterator");
      if ((rhs.mIndex == FixedStringIterator::EndValue)
          || (lhs.mIndex == rhs.mIndex))
         return 0;
      if (lhs.mIndex == FixedStringIterator::EndValue)
         return lhs.length() - rhs.mIndex;
      return static_cast< ssize_t>( lhs.mIndex) - static_cast< ssize_t>( rhs.mIndex);
   } // operator -

private:
   /// End value for iterators pointing behind the end of the string.
   static constexpr size_t  EndValue = std::numeric_limits< uint64_t>::max();

   /// Pointer to the fixed string object to handle.
   F*      mpObject = nullptr;
   /// The current position that the iterator points to.
   size_t  mIndex = EndValue;

}; // FixedStringIterator< T, F>


// inlined methods
// ===============


template< typename T, typename F>
   FixedStringIterator< T, F>::FixedStringIterator( F* obj):
   mpObject( obj)
{
   if ((mpObject != nullptr) && !mpObject->empty())
      mIndex = 0;
} // FixedStringIterator< T, F>::FixedStringIterator


template< typename T, typename F>
   FixedStringIterator< T, F>::FixedStringIterator( F* obj, size_t pos):
      mpObject( obj),
      mIndex( pos)
{
   if ((obj == nullptr) || (pos >= obj->length()))
      mIndex = EndValue;
} // FixedStringIterator< T, F>::FixedStringIterator


template< typename T, typename F>
   FixedStringIterator< T, F>::FixedStringIterator( bool, F* obj):
      mpObject( obj)
{
} // FixedStringIterator< T, F>::FixedStringIterator


template< typename T, typename F>
   typename FixedStringIterator< T, F>::reference
      FixedStringIterator< T, F>::operator *() const
{
   if (mpObject == nullptr)
      throw std::invalid_argument( "no object assigned to iterator");
   if (mIndex == EndValue)
      throw std::range_error( "index after end of string");
   return (*mpObject)[ mIndex];
} // FixedStringIterator< T, F>::operator *


template< typename T, typename F>
   bool FixedStringIterator< T, F>::operator ==( const FixedStringIterator& other)
      const noexcept
{
   return ((mIndex == EndValue) && (other.mIndex == EndValue))
          || ((mpObject == other.mpObject) && (mIndex == other.mIndex));
} // FixedStringIterator< T, F>::operator ==


template< typename T, typename F>
   bool FixedStringIterator< T, F>::operator !=( const FixedStringIterator& other)
      const noexcept
{
   return !(*this == other);
} // FixedStringIterator< T, F>::operator !=


template< typename T, typename F>
   bool FixedStringIterator< T, F>::operator <( const FixedStringIterator& other)
      const noexcept
{
   return (mpObject == other.mpObject) && (mIndex < other.mIndex);
} // FixedStringIterator< T, F>::operator <


template< typename T, typename F>
   bool FixedStringIterator< T, F>::operator <=( const FixedStringIterator& other)
      const noexcept
{
   return (mpObject == other.mpObject) && (mIndex <= other.mIndex);
} // FixedStringIterator< T, F>::operator <=


template< typename T, typename F>
   bool FixedStringIterator< T, F>::operator >=( const FixedStringIterator& other)
      const noexcept
{
   return (mpObject == other.mpObject) && (mIndex >= other.mIndex);
} // FixedStringIterator< T, F>::operator >=


template< typename T, typename F>
   bool FixedStringIterator< T, F>::operator >( const FixedStringIterator& other)
      const noexcept
{
   return (mpObject == other.mpObject) && (mIndex > other.mIndex);
} // FixedStringIterator< T, F>::operator >


template< typename T, typename F>
   FixedStringIterator< T, F>& FixedStringIterator< T, F>::operator ++()
{
   if (mpObject != nullptr)
   {
      if (mIndex < mpObject->length() - 1)
         ++mIndex;
      else
         mIndex = EndValue;
   } // end if
   return *this;
} // FixedStringIterator< T, F>::operator ++


template< typename T, typename F>
   FixedStringIterator< T, F> FixedStringIterator< T, F>::operator ++( int)
{
   auto  copy( *this);
   ++(*this);
   return copy;
} // FixedStringIterator< T, F>::operator ++


template< typename T, typename F>
   FixedStringIterator< T, F>& FixedStringIterator< T, F>::operator --()
{
   if (mpObject != nullptr)
   {
      if (mIndex > 0)
         --mIndex;
      else
         mIndex = EndValue;
   } // end if
   return *this;
} // FixedStringIterator< T, F>::operator --


template< typename T, typename F>
   FixedStringIterator< T, F> FixedStringIterator< T, F>::operator --( int)
{
   auto  copy( *this);
   --(*this);
   return copy;
} // FixedStringIterator< T, F>::operator --


template< typename T, typename F>
   FixedStringIterator< T, F>& FixedStringIterator< T, F>::operator +=( size_t value)
      noexcept
{
   if ((mpObject != nullptr) && (mIndex != EndValue))
   {
      if (mIndex + value < mpObject->length())
         mIndex += value;
      else
         mIndex = EndValue;
   } // end if
   return *this;
} // FixedStringIterator< T, F>::operator +=


template< typename T, typename F>
   FixedStringIterator< T, F>& FixedStringIterator< T, F>::operator -=( size_t value)
      noexcept
{
   if ((mpObject != nullptr) && (mIndex != EndValue))
   {
      if (mIndex >= value)
         mIndex -= value;
      else
         mIndex = EndValue;
   } // end if
   return *this;
} // FixedStringIterator< T, F>::operator -=


template< typename T, typename F>
   typename FixedStringIterator< T, F>::reference
      FixedStringIterator< T, F>::operator[]( size_t idx) const
{
   if (mpObject == nullptr)
      throw std::invalid_argument( "no object assigned to iterator");
   return (*mpObject)[ mIndex + idx];
} // FixedStringIterator< T, F>::operator[]


template< typename T, typename F>
   size_t FixedStringIterator< T, F>::length() const
{
   return (mpObject == nullptr) ? 0 : mpObject->length();
} // FixedStringIterator< T, F>::length


} // namespace celma::common::detail


// =====  END OF fixed_string_iterator.hpp  =====

