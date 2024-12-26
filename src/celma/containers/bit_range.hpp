
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
/// See documentation of class celma::containers::BitRange.


#ifndef CELMA_CONTAINERS_BIT_RANGE_HPP
#define CELMA_CONTAINERS_BIT_RANGE_HPP


#include <cassert>
#include <bitset>


namespace celma { namespace containers {


/// Implements a bitset on a range 'lower <= x < upper', e.g. the range '10..20'
/// allows the values/bits '10, 11, ..., 19' to be set.<br>
/// All indices that are used for accessing this bit range must of course be in
/// this range: <pre>L <= idx < U</pre>.
/// @tparam  L
///    Lower bound (inclusive) of the range.
/// @tparam  U
///    Upper bound (exclusive) of the range.
/// @since
///    x.y.z, 26.06.2018
template< size_t L, size_t U> class BitRange
{

static_assert( L < U, "lower bound must be less than the upper bound");

public:
   using reference = typename std::bitset< U - L>::reference;

   /// Default constructor and copy-constructor can be used.
   BitRange() = default;
   BitRange( const BitRange&) = default;

   /// Copy constructor that allows a source object with another range. Copies/
   /// sets only those bits that also exist in the new/destination object.
   /// @tparam  L2
   ///    The lower bound of the other object.
   /// @tparam  U2
   ///    The upper bound of the other object.
   /// @param[in]  other
   ///    The other object to copy the bits from in the intersecting range.
   /// @since
   ///    x.y.z, 28.06.2018
   template< size_t L2, size_t U2> BitRange( const BitRange< L2, U2>& other);

   // modifier
   // ========

   /// Sets the given bit.
   /// @param[in]  idx
   ///    The index of the bit to set.
   /// @since
   ///    x.y.z, 26.06.2018
   void set( size_t idx);

   /// Resets/Clears the bit at the given position.
   /// @param[in]  idx
   ///    The index of the bit to reset.
   /// @since
   ///    x.y.z, 27.06.2018
   void reset( size_t idx);

   /// Resets all bits in the range.
   /// @since
   ///    x.y.z, 27.06.2018
   void reset();

   /// Flips the bit at the given position.
   /// @param[in]  idx
   ///    The index of the bit to flip.
   /// @since
   ///    x.y.z, 27.06.2018
   void flip( size_t idx);

   /// Flips all bits in the range.
   /// @since
   ///    x.y.z, 27.06.2018
   void flip();

   /// Default assignment opertor is fine.
   BitRange& operator =( const BitRange&) = default;

   /// Assignment operator. Clears the internal bitset and then sets the bits
   /// from the intersec ting range from the other object.
   /// @tparam  L2
   ///    The lower bound of the other object.
   /// @tparam  U2
   ///    The upper bound of the other object.
   /// @param[in]  other
   ///    The other object to copy the data from.
   /// @return
   ///    This object.
   /// @since
   ///    x.y.z, 28.06.2018
   template< size_t L2, size_t U2>
      BitRange& operator =( const BitRange< L2, U2>& other);

   /// Returns a reference of the bit at the given position. Can be used to read
   /// or write the bit.
   /// @param[in]  idx
   ///    The index of the bit to return.
   /// @return
   ///    Reference object for accessing the bit.
   /// @since
   ///    x.y.z, 26.06.2018
   reference operator []( size_t idx);

   // access
   // ======

   /// Returns the value of the bit at the given position.
   /// @param[in]  idx
   ///    The index of the bit to return the value of.
   /// @return
   ///    The value of the bit at the given position.
   /// @since
   ///    x.y.z, 26.06.2018
   bool operator []( size_t idx) const;

   /// Returns the number of bits that are currently set
   /// @return
   ///    Number of bits set.
   /// @since
   ///    x.y.z, 26.06.2018
   size_t count() const;

   /// Returns the number of bits that the range can store.
   /// @return
   ///    Number of bits that the range contains.
   /// @since
   ///    x.y.z, 27.06.2018
   size_t size() const;

   /// Returns the value of the bit at the given position.
   /// @param[in]  idx
   ///    The index of the bit to return the value of.
   /// @return
   ///    The value of the bit at the given position.
   /// @since
   ///    x.y.z, 27.06.2018
   bool test( size_t idx) const;

   /// Returns if no bit is set in the range.
   /// @return
   ///    \c true if no bit is set.
   /// @since
   ///    x.y.z, 26.06.2018
   bool none() const;

   /// Returns if all bits are set in the range.
   /// @return
   ///    \c true when all bits are set.
   /// @since
   ///    x.y.z, 26.06.2018
   bool all() const;

   /// Returns if any, i.e. at least one, bit is set in the range.
   /// @return
   ///    \c true if at least one bit is set in the range.
   /// @since
   ///    x.y.z, 26.06.2018
   bool any() const;

   /// Equality comparison operator for two bit ranges.
   /// @param[in]  other
   ///    The other bit range to compare against.
   /// @return
   ///    \c true if the same bits are set in this and in the other object.
   /// @since
   ///    x.y.z, 27.06.2018
   bool operator ==( const BitRange& other) const;

   /// Inequality comparison operator for two bit ranges.
   /// @param[in]  other
   ///    The other bit range to compare against.
   /// @return
   ///    \c true if the bits that are set in this and in the other object
   ///    differ.
   /// @since
   ///    x.y.z, 27.06.2018
   bool operator !=( const BitRange& other) const;

   /// Returns a binary string representation of the value currently stored in
   /// the internal bitset.<br>
   /// The range is taken into account, i.e. if the lower bound is 10, 10 0s
   /// are added to the binary string so the resulting string displays the
   /// correct value.
   /// @return
   ///    The value of the bit range expressed as a binary string.
   /// @since
   ///    x.y.z, 27.06.2018
   std::string to_string() const;

   /// The value of the bit range converted into an integer value.
   /// @return
   ///    The value of the bit range as integer.
   /// @since
   ///    x.y.z, 27.06.2018
   uint64_t to_ulong() const;

   /// The value of the bit range converted into an integer value.
   /// @return
   ///    The value of the bit range as integer.
   /// @since
   ///    x.y.z, 27.06.2018
   unsigned long long to_ullong() const;

private:
   /// Used by the copy-constructor and assignment operator: Copy the bits
   /// from the ranges intersection.
   /// @tparam  L2
   ///    The lower bound of the range of the other object.
   /// @tparam  U2
   ///    The upper bound of the range of the other object.
   /// @param[in]  other
   ///    The other object to copy the data from.
   /// @since
   ///    x.y.z, 28.06.2018
   template< size_t L2, size_t U2>
      void copyIntersect( const BitRange< L2, U2>& other);

   /// INternally we use a bitset to store the values.
   std::bitset< U - L>  mBitset;

}; // BitRange< L, U>


// inlined methods
// ===============


template< size_t L, size_t U> 
   template< size_t L2, size_t U2>
      BitRange< L, U>::BitRange( const BitRange< L2, U2>& other):
        mBitset()
{
   copyIntersect( other);
} // BitRange< L, U>::BitRange


template< size_t L, size_t U> void BitRange< L, U>::set( size_t idx)
{
   assert( L <= idx);
   assert( idx < U);
   mBitset[ idx - L] = true;
} // BitRange< L, U>::set


template< size_t L, size_t U> void BitRange< L, U>::reset( size_t idx)
{
   assert( L <= idx);
   assert( idx < U);
   mBitset.reset( idx -L);
} // BitRange< L, U>::reset


template< size_t L, size_t U> void BitRange< L, U>::reset()
{
   mBitset.reset();
} // BitRange< L, U>::reset


template< size_t L, size_t U> void BitRange< L, U>::flip( size_t idx)
{
   assert( L <= idx);
   assert( idx < U);
   mBitset.flip( idx - L);
} // BitRange< L, U>::flip


template< size_t L, size_t U> void BitRange< L, U>::flip()
{
   mBitset.flip();
} // BitRange< L, U>::flip


template< size_t L, size_t U>
   template< size_t L2, size_t U2>
      BitRange< L, U>&
         BitRange< L, U>::operator =( const BitRange< L2, U2>& other)
{
   mBitset.reset();
   copyIntersect( other);
   return *this;
} // BitRange< L, U>::operator =


template< size_t L, size_t U>
   typename BitRange< L, U>::reference
      BitRange< L, U>::operator []( size_t idx)
{
   assert( L <= idx);
   assert( idx < U);
   return mBitset[ idx - L];
} // BitRange< L, U>::operator []


template< size_t L, size_t U>
   bool BitRange< L, U>::operator []( size_t idx) const
{
   assert( L <= idx);
   assert( idx < U);
   return mBitset[ idx - L];
} // BitRange< L, U>::operator []


template< size_t L, size_t U> size_t BitRange< L, U>::count() const
{
   return mBitset.count();
} // BitRange< L, U>::count


template< size_t L, size_t U> size_t BitRange< L, U>::size() const
{
   return mBitset.size();
} // BitRange< L, U>::size


template< size_t L, size_t U> bool BitRange< L, U>::test( size_t idx) const
{
   assert( L <= idx);
   assert( idx < U);
   return mBitset.test( idx - L);
} // BitRange< L, U>::test


template< size_t L, size_t U> bool BitRange< L, U>::none() const
{
   return mBitset.none();
} // BitRange< L, U>::none


template< size_t L, size_t U> bool BitRange< L, U>::all() const
{
   return mBitset.all();
} // BitRange< L, U>::all


template< size_t L, size_t U> bool BitRange< L, U>::any() const
{
   return mBitset.any();
} // BitRange< L, U>::any


template< size_t L, size_t U>
   bool BitRange< L, U>::operator ==( const BitRange& other) const
{
   return mBitset == other.mBitset;
} // BitRange< L, U>::operator ==


template< size_t L, size_t U>
   bool BitRange< L, U>::operator !=( const BitRange& other) const
{
   return mBitset != other.mBitset;
} // BitRange< L, U>::operator !=


template< size_t L, size_t U> std::string BitRange< L, U>::to_string() const
{
   // have to add 0es at the end to correct the length
   return mBitset.to_string().append( L, '0');
} // BitRange< L, U>::to_string


template< size_t L, size_t U> uint64_t BitRange< L, U>::to_ulong() const
{
   return mBitset.to_ulong() << L;
} // BitRange< L, U>::to_ulong


template< size_t L, size_t U>
   unsigned long long BitRange< L, U>::to_ullong() const
{
   return mBitset.to_ullong() << L;
} // BitRange< L, U>::to_ullong



template< size_t L, size_t U>
   template< size_t L2, size_t U2>
      void BitRange< L, U>::copyIntersect( const BitRange< L2, U2>& other)
{

   const size_t  interset_lower = std::max( L, L2);
   const size_t  interset_upper = std::min( U, U2);
   if (interset_lower < interset_upper)
   {
      for (size_t idx = interset_lower; idx < interset_upper; ++idx)
      {
         // only need to set bits because the destination bitset should be
         // default-constructed or cleared
         if (other[ idx])
            set( idx);
      } // end for
   } // end if

} // BitRange< L, U>::copyIntersect


} // namespace containers
} // namespace celma


#endif   // CELMA_CONTAINERS_BIT_RANGE_HPP


// =====  END OF bit_range.hpp  =====

