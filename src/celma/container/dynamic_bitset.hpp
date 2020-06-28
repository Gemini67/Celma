
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::container::DynamicBitset.


#ifndef CELMA_CONTAINER_DYNAMIC_BITSET_HPP
#define CELMA_CONTAINER_DYNAMIC_BITSET_HPP


#include <bitset>
#include <string>
#include <vector>
#include "celma/common/type_name.hpp"
#include "celma/container/detail/dynamic_bitset_iterator.hpp"


namespace celma { namespace container {


/// Dynamic bitset, a std::vector<bool> with the interface of a std::bitset<>.
/// If not noted otherwise, the internal vector is dynamically resized if a
/// given position is greater than the current size of the vector.<br>
/// The iterators return only the positions of the bits that are set. To check
/// each bit of the dynamic bitset, use a for loop with an index variable.
///
/// @since  1.37.0, 08.06.2020
class DynamicBitset
{
public:
   /// The type returned by the non-const index access operator.
   using reference = std::vector< bool>::reference;

   /// Iterator type.
   using iterator = detail::DynamicBitsetIterator< DynamicBitset>;
   /// Reverse iterator type.
   using reverse_iterator = detail::DynamicBitsetReverseIterator< DynamicBitset>;
   /// Const iterator type.
   using const_iterator = detail::DynamicBitsetIterator< const DynamicBitset>;
   /// Const reverse iterator type.
   using const_reverse_iterator = detail::DynamicBitsetReverseIterator< const DynamicBitset>;

   /// Constructor.
   ///
   /// @param[in]  num_bits
   ///    Number of bits that the internal vector should initially be able to
   ///    store.
   /// @since  1.37.0, 08.06.2020
   explicit DynamicBitset( size_t num_bits);

   /// Constructor that copies the values from a vector of bool.
   ///
   /// @param[in]  other  The vector to copy the data from.
   /// @since  1.37.0, 16.06.2020
   explicit DynamicBitset( const std::vector< bool>& other);

   /// Constructor that takes the values from a vector of bool.
   ///
   /// @param[in]  other  The vector to move the data from.
   /// @since  1.37.0, 16.06.2020
   explicit DynamicBitset( std::vector< bool>&& other);

   /// Constructor that copies the values from a bitset.
   ///
   /// @tparam  N  The size of the bitset to copy the data from.
   /// @param[in]  other  The bitset to copy the data from.
   /// @since  1.37.0, 16.06.2020
   template< size_t N> explicit DynamicBitset( const std::bitset< N>& other);

   /// Default copy-assignment is fine.
   DynamicBitset( const DynamicBitset&) = default;
   /// Default move-assignment is fine.
   DynamicBitset( DynamicBitset&&) = default;
   /// Default destructor is fine.
   ~DynamicBitset() = default;

   /// Returns if the flag at the given position is set.
   /// 
   /// @param[in]  pos  The index of the flag to return the value of.
   /// @return  The value of the flag at the given position.
   /// @throw
   ///    std::out_of_range if then given position is greater than the size of
   ///    the internal vector.
   /// @since  1.37.0, 08.06.2020
   bool test( size_t pos) const noexcept( false);

   /// Returns if all bits are set.
   ///
   /// @return  \c true if all bits are set.
   /// @since  1.37.0, 08.06.2020
   bool all() const noexcept( true);

   /// Returns if at least one bit is set.
   ///
   /// @return  \c true if at least one bit is set.
   /// @since  1.37.0, 08.06.2020
   bool any() const noexcept( true);

   /// Returns if no bit is set.
   ///
   /// @return  \c true if no bit is set.
   /// @since  1.37.0, 08.06.2020
   bool none() const noexcept( true);

   /// Returns the number of bits that are currently set.
   ///
   /// @return  The number of bits that are currently set.
   /// @since  1.37.0, 08.06.2020
   size_t count() const noexcept( true);

   /// Returns the size of the internal vector, the number of bits that can be
   /// stored.
   ///
   /// @return  The number of bits that are currently set.
   /// @since  1.37.0, 08.06.2020
   size_t size() const noexcept( true);

   /// Resizes the internal vector to the given size.
   ///
   /// @param[in]  count
   ///    The new size of the vector.
   /// @param[in]  init_value
   ///    The value to initialise the new elements with if the size of the
   ///    vector is increased.
   /// @since  1.37.0, 16.06.2020
   void resize( size_t count, bool init_value = false);

   /// Sets all bits.
   ///
   /// @return  This object.
   /// @since  1.37.0, 08.06.2020
   DynamicBitset& set() noexcept( true);

   /// Sets or clears the bit at the given position.
   ///
   /// @param[in]  pos
   ///    The position of the bit to change.
   /// @param[in]  value
   ///    The value to set for the bit.
   /// @return  This object.
   /// @since  1.37.0, 08.06.2020
   DynamicBitset& set( size_t pos, bool value = true);

   /// Resets/Clears all bits.
   ///
   /// @return  This object.
   /// @since  1.37.0, 08.06.2020
   DynamicBitset& reset() noexcept( true);

   /// Resets/Clears the bit at the given position.
   ///
   /// @param[in]  pos  The position of the bit to clear.
   /// @return  This object.
   /// @since  1.37.0, 08.06.2020
   DynamicBitset& reset( size_t pos);

   /// Flips/Inverts all bits.
   ///
   /// @return  This object.
   /// @since  1.37.0, 08.06.2020
   DynamicBitset& flip() noexcept( true);

   /// Flips/Inverts the bit at the given position.
   ///
   /// @param[in]  pos  The position of the bit to flip.
   /// @return  This object.
   /// @since  1.37.0, 08.06.2020
   DynamicBitset& flip( size_t pos);

   /// Returns the bits in the internal vector as a binary string.
   ///
   /// @tparam  T
   ///    The type of the characters to use to fill the string.
   /// @param[in]  zero
   ///    The character to use for the bits that are not set.
   /// @param[in]  one
   ///    The character to use for the bits that are set.
   /// @return
   ///    String with the binary representation of the bits in the vector.
   /// @since
   ///    1.37.0, 10.06.2020
   template< typename T = char>
      std::string to_string( T zero = T( '0'), T one = T( '1')) const;

   /// Returns the flags set in the internal vector as a number.
   ///
   /// @return  The number built from the bits set in the vector.
   /// @throw 
   ///    std::overflow_error if the contents of the vector cannot be converted
   ///    into an unsigned long integer.
   /// @since  1.37.0, 10.06.2020
   unsigned long to_ulong() const noexcept( false);

   /// Default assignment operator is fine.
   DynamicBitset& operator =( const DynamicBitset&) = default;
   /// Default move assignment is fine.
   DynamicBitset& operator =( DynamicBitset&&) = default;

   /// Assigns the contents of a vector of bool.
   ///
   /// @param[in]  other  The vector to copy the data from.
   /// @return  This object.
   /// @since  1.37.0, 16.06.2020
   DynamicBitset& operator =( const std::vector< bool>& other);

   /// Moves the contents of a vector of bool.
   ///
   /// @param[in]  other  The vector to take the data from.
   /// @return  This object.
   /// @since  1.37.0, 16.06.2020
   DynamicBitset& operator =( std::vector< bool>&& other);

   /// Assigns the contents of a vector of bool.
   ///
   /// @tparam  N  The size of the bitset.
   /// @param[in]  other  The bitset to copy the data from.
   /// @return  This object.
   /// @since  1.37.0, 16.06.2020
   template< size_t N> DynamicBitset& operator =( const std::bitset< N>& other);

   /// Returns if the contents of this dynamic bitset and the other are
   /// identical.
   /// The size of the internal vectors need not be identical.
   ///
   /// @param[in]  other  The other dynamic bitset to compare against.
   /// @return  \c true if the contents of the two vectors are identical.
   /// @since  1.37.0, 08.06.2020
   bool operator ==( const DynamicBitset& other) const noexcept( true);

   /// Returns the value of the flag at the given position.
   ///
   /// @param[in]  pos  The position of the flag to return the value of.
   /// @return  The value of the flag at the given position.
   /// @throw
   ///    std::out_of_range if the given position is greater than the size of
   ///    the internal vector.
   /// @since  1.37.0, 08.06.2020
   bool operator []( size_t pos) const noexcept( false);

   /// Returns the value of the flag at the given position.
   /// If the given position is greater than the current size of the vector, the
   /// vector is re-sized.
   ///
   /// @param[in]  pos  The position of the flag to return the value of.
   /// @return  The value of the flag at the given position.
   /// @since  1.37.0, 08.06.2020
   reference operator []( size_t pos) noexcept( true);

   /// Logically and's each flag of this object with that of the other object
   /// and stores the result in this object.
   ///
   /// @param[in]  other  The other dynamic bitset to "and" the flags with.
   /// @return  This object.
   /// @since  1.37.0, 09.06.2020
   DynamicBitset& operator &=( const DynamicBitset& other) noexcept( true);

   /// Logically or's each flag of this object with that of the other object
   /// and stores the result in this object.
   ///
   /// @param[in]  other  The other dynamic bitset to "or" the flags with.
   /// @return  This object.
   /// @since  1.37.0, 09.06.2020
   DynamicBitset& operator |=( const DynamicBitset& other) noexcept( true);

   /// Logically exclusive-or's each flag of this object with that of the other
   /// object and stores the result in this object.
   ///
   /// @param[in]  other
   ///    The other dynamic bitset to "exclusive or" the flags with.
   /// @return  This object.
   /// @since  1.37.0, 09.06.2020
   DynamicBitset& operator ^=( const DynamicBitset& other) noexcept( true);

   /// Invertas/Flips each flag of the internal vector.
   ///
   /// @return  This object.
   /// @since  1.37.0, 09.06.2020
   DynamicBitset operator ~() const noexcept( true);

   /// Left-shifts the internal flags by the given number of positions.
   ///
   /// @param[in]  pos  The number of positions to left-shift.
   /// @return  A new dynamic bitset with the shifted flags.
   /// @since  1.37.0, 09.06.2020
   DynamicBitset operator <<( size_t pos) const noexcept( true);

   /// Left-shifts the internal flags of this object by the given number of
   /// positions.
   ///
   /// @param[in]  pos  The number of positions to left-shift.
   /// @return  This object.
   /// @since  1.37.0, 09.06.2020
   DynamicBitset& operator <<=( size_t pos) noexcept( true);

   /// Right-shifts the internal flags by the given number of positions.
   ///
   /// @param[in]  pos  The number of positions to right-shift.
   /// @return  A new dynamic bitset with the shifted flags.
   /// @since  1.37.0, 09.06.2020
   DynamicBitset operator >>( size_t pos) const noexcept( true);

   /// Right-shifts the internal flags of this object by the given number of
   /// positions.
   ///
   /// @param[in]  pos  The number of positions to right-shift.
   /// @return  This object.
   /// @since  1.37.0, 09.06.2020
   DynamicBitset& operator >>=( size_t pos) noexcept( true);

   /// Returns an iterator that provides the position of the first bit that is
   /// set in the dynamic bitset.
   /// If not bit is set at all, begin() yields end().
   ///
   /// @return  Iterator that gives the position of the first bit that is set.
   /// @since  1.37.0, 18.06.2020
   iterator begin();

   /// Returns an iterator that points behind the end of the internal dynamic
   /// vector.
   ///
   /// @return  Iterator pointing to the end of the vector.
   /// @since  1.37.0, 18.06.2020
   iterator end();

   /// Returns a const iterator that provides the position of the first bit that
   /// is set in the dynamic bitset.
   /// If not bit is set at all, begin() yields end().
   ///
   /// @return
   ///    Const iterator that gives the position of the first bit that is set.
   /// @since  1.37.0, 21.06.2020
   const_iterator begin() const;

   /// Returns a const iterator that points behind the end of the internal
   /// dynamic vector.
   ///
   /// @return  Const iterator pointing to the end of the vector.
   /// @since  1.37.0, 21.06.2020
   const_iterator end() const;

   /// Returns a const iterator that provides the position of the first bit that
   /// is set in the dynamic bitset.
   /// If not bit is set at all, begin() yields end().
   ///
   /// @return
   ///    Const iterator that gives the position of the first bit that is set.
   /// @since  1.37.0, 21.06.2020
   const_iterator cbegin() const;

   /// Returns a const iterator that points behind the end of the internal
   /// dynamic vector.
   ///
   /// @return  Const iterator pointing to the end of the vector.
   /// @since  1.37.0, 21.06.2020
   const_iterator cend() const;

   /// Returns a reverse iterator pointing the last bit in the internal vector
   /// that is set.
   /// If no bit is set, rbegin() yields rend().
   ///
   /// @return
   ///    Iterator with the position of the last bit in the vector that is set.
   /// @since  1.37.0, 21.06.2020
   reverse_iterator rbegin();

   /// Returns a reverse iterator pointing before the start of the internal
   /// vector.
   ///
   /// @return
   ///    Iterator pointing before the start of the vector.
   /// @since  1.37.0, 21.06.2020
   reverse_iterator rend();

   /// Returns a const reverse iterator pointing the last bit in the internal
   /// vector that is set.
   /// If no bit is set, rbegin() yields rend().
   ///
   /// @return
   ///    Const iterator with the position of the last bit in the vector that is
   ///    set.
   /// @since  1.37.0, 21.06.2020
   const_reverse_iterator rbegin() const;

   /// Returns a const reverse iterator pointing before the start of the
   /// internal vector.
   ///
   /// @return
   ///    Const iterator pointing before the start of the vector.
   /// @since  1.37.0, 21.06.2020
   const_reverse_iterator rend() const;

   /// Returns a const reverse iterator pointing the last bit in the internal
   /// vector that is set.
   /// If no bit is set, rbegin() yields rend().
   ///
   /// @return
   ///    Const iterator with the position of the last bit in the vector that is
   ///    set.
   /// @since  1.37.0, 21.06.2020
   const_reverse_iterator crbegin() const;

   /// Returns a const reverse iterator pointing before the start of the
   /// internal vector.
   ///
   /// @return
   ///    Const iterator pointing before the start of the vector.
   /// @since  1.37.0, 21.06.2020
   const_reverse_iterator crend() const;

private:
   /// The vector with the flags.
   std::vector< bool>  mData;

}; // DynamicBitset


// inlined methods
// ===============


template< size_t N> DynamicBitset::DynamicBitset( const std::bitset< N>& other):
   mData( N, false)
{
   for (size_t idx = 0; idx < N; ++idx)
   {
      mData[ idx] = other[ idx];
   } // end for
} // DynamicBitset::DynamicBitset


template< typename T> std::string DynamicBitset::to_string( T zero, T one) const
{
   std::string  result( mData.size(), zero);
   for (size_t idx = 0; idx < mData.size(); ++idx)
   {
      if (mData[ idx])
         result[ idx] = one;
   } // end for
   return result;
} // DynamicBitset::to_string


template< size_t N>
   DynamicBitset& DynamicBitset::operator =( const std::bitset< N>& other)
{
   mData.resize( N);
   for (size_t idx = 0; idx < N; ++idx)
   {
      mData[ idx] = other[ idx];
   } // end for
   return *this;
} // DynamicBitset::operator =


// free functions
// ==============


/// Logically and's the flags of two dynamic bitsets and returns a new object
/// with the result.
///
/// @param[in]  lhs
///    The first dynamic bitset to use for the "and" operation.
/// @param[in]  rhs
///    The second dynamic bitset to use for the "and" operation.
/// @return
///    A new dynamic bitset with the result of the logical "and" of the flags.
/// @since
///    1.37.0, 11.06.2020
DynamicBitset operator &( const DynamicBitset& lhs, const DynamicBitset& rhs) noexcept( true);


/// Logically or's the flags of two dynamic bitsets and returns a new object
/// with the result.
///
/// @param[in]  lhs
///    The first dynamic bitset to use for the "or" operation.
/// @param[in]  rhs
///    The second dynamic bitset to use for the "or" operation.
/// @return
///    A new dynamic bitset with the result of the logical "or" of the flags.
/// @since
///    1.37.0, 11.06.2020
DynamicBitset operator |( const DynamicBitset& lhs, const DynamicBitset& rhs) noexcept( true);


/// Logically exclusive-or's the flags of two dynamic bitsets and returns a new
/// object with the result.
///
/// @param[in]  lhs
///    The first dynamic bitset to use for the "exclusive or" operation.
/// @param[in]  rhs
///    The second dynamic bitset to use for the "exclusive or" operation.
/// @return
///    A new dynamic bitset with the result of the logical "exclusive-or" of the
///    flags.
/// @since
///    1.37.0, 11.06.2020
DynamicBitset operator ^( const DynamicBitset& lhs, const DynamicBitset& rhs) noexcept( true);


} // namespace container


/// Specialisation of type<> for type 'celma::container::DynamicBitset'.
///
/// @since  1.37.0, 28.06.2020
template<> class type< container::DynamicBitset>
{
public:
   /// Returns the name of the type.
   ///
   /// @return  'celma::container::DynamicBitset>'.
   /// @since  1.37.0, 28.06.2020
   static constexpr const char* name()
   {
      return &mName[ 0];
   } // type< container::DynamicBitset>::name

   /// Used to store the name of the type persistently.
   /// Is public to build nested container names, don't access for printing.
   static constexpr auto const  mName = "celma::container::DynamicBitset";

}; // type< celma::container::DynamicBitset>


} // namespace celma


#endif   // CELMA_CONTAINER_DYNAMIC_BITSET_HPP


// =====  END OF dynamic_bitset.hpp  =====

