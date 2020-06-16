
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
/// See documentation of class celma::common::DynamicBitset.


// module headerfile include
#include "celma/common/dynamic_bitset.hpp"


// C++ Standard Library includes
#include <algorithm>
#include <stdexcept>


namespace celma { namespace common {



/// Constructor.
///
/// @param[in]  num_bits
///    Number of bits that the internal vector should initially be able to
///    store.
/// @since  x.y.z, 08.06.2020
DynamicBitset::DynamicBitset( size_t num_bits)
{

   if (num_bits > 0)
      mData.resize( num_bits);

} // DynamicBitset::DynamicBitset



/// Constructor that copies the values from a vector of bool.
///
/// @param[in]  other  The vector to copy the data from.
/// @since  x.y.z, 16.06.2020
DynamicBitset::DynamicBitset( const std::vector< bool>& other):
   mData( other)
{
} // DynamicBitset::DynamicBitset



/// Constructor that takes the values from a vector of bool.
///
/// @param[in]  other  The vector to move the data from.
/// @since  x.y.z, 16.06.2020
DynamicBitset::DynamicBitset( std::vector< bool>&& other):
   mData( std::move( other))
{
} // DynamicBitset::DynamicBitset



/// Returns if the flag at the given position is set.
/// 
/// @param[in]  pos  The index of the flag to return the value of.
/// @return  The value of the flag at the given position.
/// @throw
///    std::out_of_range if then given position is greater than the size of
///    the internal vector.
/// @since  x.y.z, 08.06.2020
bool DynamicBitset::test( size_t pos) const noexcept( false)
{

   if (pos > mData.size())
      throw std::out_of_range( "position is behind end of vector");

   return mData[ pos];
} // DynamicBitset::test



/// Returns if all bits are set.
///
/// @return  \c true if all bits are set.
/// @since  x.y.z, 08.06.2020
bool DynamicBitset::all() const noexcept( true)
{

   return std::find( mData.begin(), mData.end(), false) == mData.end();
} // DynamicBitset::all



/// Returns if at least one bit is set.
///
/// @return  \c true if at least one bit is set.
/// @since  x.y.z, 08.06.2020
bool DynamicBitset::any() const noexcept( true)
{

   return std::find( mData.begin(), mData.end(), true) != mData.end();
} // DynamicBitset::any



/// Returns if no bit is set.
///
/// @return  \c true if no bit is set.
/// @since  x.y.z, 08.06.2020
bool DynamicBitset::none() const noexcept( true)
{

   return std::find( mData.begin(), mData.end(), true) == mData.end();
} // DynamicBitset::none



/// Returns the number of bits that are currently set.
///
/// @return  The number of bits that are currently set.
/// @since  x.y.z, 08.06.2020
size_t DynamicBitset::count() const noexcept( true)
{

   return std::count( mData.begin(), mData.end(), true);
} // DynamicBitset::count



/// Returns the size of the internal vector, the number of bits that can be
/// stored.
///
/// @return  The number of bits that are currently set.
/// @since  x.y.z, 08.06.2020
size_t DynamicBitset::size() const noexcept( true)
{

   return mData.size();
} // DynamicBitset::size



/// Resizes the internal vector to the given size.
///
/// @param[in]  count
///    The new size of the vector.
/// @param[in]  init_value
///    The value to initialise the new elements with if the size of the
///    vector is increased.
/// @since  x.y.z, 16.06.2020
void DynamicBitset::resize( size_t count, bool init_value)
{

   mData.resize( count, init_value);

} // DynamicBitset::resize



/// Sets all bits.
///
/// @return  This object.
/// @since  x.y.z, 08.06.2020
DynamicBitset& DynamicBitset::set() noexcept( true)
{

   for (auto flag : mData)
   {
      flag = true;
   } // end for

   return *this;
} // DynamicBitset::set



/// Sets or clears the bit at the given position.
///
/// @param[in]  pos
///    The position of the bit to change.
/// @param[in]  value
///    The value to set for the bit.
/// @return  This object.
/// @since  x.y.z, 08.06.2020
DynamicBitset& DynamicBitset::set( size_t pos, bool value)
{

   if (pos >= mData.size())
      mData.resize( (pos + 1) * 1.5);

   mData[ pos] = value;

   return *this;
} // DynamicBitset::set



/// Resets/Clears all bits.
///
/// @return  This object.
/// @since  x.y.z, 08.06.2020
DynamicBitset& DynamicBitset::reset() noexcept( true)
{

   mData.clear();

   return *this;
} // DynamicBitset::reset



/// Resets/Clears the bit at the given position.
///
/// @param[in]  pos  The position of the bit to clear.
/// @return  This object.
/// @since  x.y.z, 08.06.2020
DynamicBitset& DynamicBitset::reset( size_t pos)
{

   if (pos > mData.size())
      mData.resize( (pos + 1) * 1.5);

   mData[ pos] = false;

   return *this;
} // DynamicBitset::reset



/// Flips/Inverts all bits.
///
/// @return  This object.
/// @since  x.y.z, 08.06.2020
DynamicBitset& DynamicBitset::flip() noexcept( true)
{

   mData.flip();

   return *this;
} // DynamicBitset::flip



/// Flips/Inverts the bit at the given position.
///
/// @param[in]  pos  The position of the bit to flip.
/// @return  This object.
/// @since  x.y.z, 08.06.2020
DynamicBitset& DynamicBitset::flip( size_t pos)
{

   if (pos > mData.size())
      mData.resize( (pos + 1) * 1.5);

   mData[ pos] = !mData[ pos];

   return *this;
} // DynamicBitset::flip



/// Returns the flags set in the internal vector as a number.
///
/// @return  The number built from the bits set in the vector.
/// @throw 
///    std::overflow_error if the contents of the vector cannot be converted
///    into an unsigned long integer.
/// @since  x.y.z, 10.06.2020
unsigned long DynamicBitset::to_ulong() const noexcept( false)
{

   unsigned long  result = 0;


   for (size_t idx = 0; idx < mData.size(); ++idx)
   {
      if (mData[ idx])
      {
         if (idx >= 64)
            throw std::overflow_error( "value too big, cannot be converted into"
               " unsigned long integer");
         result += 1L << idx;
      } // end if
   } // end for

   return result;
} // DynamicBitset::to_ulong



/// Assigns the contents of a vector of bool.
///
/// @param[in]  other  The vector to copy the data from.
/// @return  This object.
/// @since  x.y.z, 16.06.2020
DynamicBitset& DynamicBitset::operator =( const std::vector< bool>& other)
{

   mData = other;

   return *this;
} // DynamicBitset::operator =



/// Moves the contents of a vector of bool.
///
/// @param[in]  other  The vector to take the data from.
/// @return  This object.
/// @since  x.y.z, 16.06.2020
DynamicBitset& DynamicBitset::operator =( std::vector< bool>&& other)
{

   mData = std::move( other);

   return *this;
} // DynamicBitset::operator =



/// Returns if the contents of this dynamic bitset and the other are
/// identical.
/// The size of the internal vectors need not be identical.
///
/// @param[in]  other  The other dynamic bitset to compare against.
/// @return  \c true if the contents of the two vectors are identical.
/// @since  x.y.z, 08.06.2020
bool DynamicBitset::operator ==( const DynamicBitset& other) const noexcept( true)
{

   return mData == other.mData;
} // DynamicBitset::operator ==



/// Returns the value of the flag at the given position.
///
/// @param[in]  pos  The position of the flag to return the value of.
/// @return  The value of the flag at the given position.
/// @throw
///    std::out_of_range if the given position is greater than the size of
///    the internal vector.
/// @since  x.y.z, 08.06.2020
bool DynamicBitset::operator []( size_t pos) const noexcept( false)
{

   if (pos > mData.size())
      throw std::out_of_range( "position is behind end of vector");

   return mData[ pos];
} // DynamicBitset::operator []



/// Returns the value of the flag at the given position.
/// If the given position is greater than the current size of the vector, the
/// vector is re-sized.
///
/// @param[in]  pos  The position of the flag to return the value of.
/// @return  The value of the flag at the given position.
/// @since  x.y.z, 08.06.2020
DynamicBitset::reference DynamicBitset::operator []( size_t pos) noexcept( true)
{

   if (pos > mData.size())
      mData.resize( (pos + 1) * 1.5);

   return mData[ pos];
} // DynamicBitset::operator []



/// Logically and's each flag of this object with that of the other object
/// and stores the result in this object.
///
/// @param[in]  other  The other dynamic bitset to "and" the flags with.
/// @return  This object.
/// @since  x.y.z, 09.06.2020
DynamicBitset& DynamicBitset::operator &=( const DynamicBitset& other) noexcept( true)
{

   if (mData.size() < other.mData.size())
   {
      for (size_t idx = 0; idx < mData.size(); ++idx)
      {
         mData[ idx] = mData[idx] & other.mData[ idx];
      } // end for
   } else
   {
      for (size_t idx = 0; idx < other.mData.size(); ++idx)
      {
         mData[ idx] = mData[ idx] & other.mData[ idx];
      } // end for
      for (size_t idx = other.mData.size(); idx < mData.size(); ++idx)
      {
         mData[ idx] = false;
      } // end for
   } // end if

   return *this;
} // DynamicBitset::operator &=



/// Logically or's each flag of this object with that of the other object
/// and stores the result in this object.
///
/// @param[in]  other  The other dynamic bitset to "or" the flags with.
/// @return  This object.
/// @since  x.y.z, 09.06.2020
DynamicBitset& DynamicBitset::operator |=( const DynamicBitset& other) noexcept( true)
{

   if (mData.size() < other.mData.size())
   {
      mData.resize( other.mData.size());
   } // end if

   for (size_t idx = 0; idx < std::min( mData.size(), other.mData.size()); ++idx)
   {
      mData[ idx] = mData[idx] | other.mData[ idx];
   } // end for

   return *this;
} // DynamicBitset::operator |=



/// Logically exclusive-or's each flag of this object with that of the other
/// object and stores the result in this object.
///
/// @param[in]  other
///    The other dynamic bitset to "exclusive or" the flags with.
/// @return  This object.
/// @since  x.y.z, 09.06.2020
DynamicBitset& DynamicBitset::operator ^=( const DynamicBitset& other) noexcept( true)
{

   if (mData.size() < other.mData.size())
   {
      mData.resize( other.mData.size());
   } // end if

   for (size_t idx = 0; idx < std::min( mData.size(), other.mData.size()); ++idx)
   {
      mData[ idx] = mData[idx] ^ other.mData[ idx];
   } // end for

   return *this;
} // DynamicBitset::operator ^=



/// Invertas/Flips each flag of the internal vector.
///
/// @return  This object.
/// @since  x.y.z, 09.06.2020
DynamicBitset DynamicBitset::operator ~() const noexcept( true)
{

   auto copy( *this);


   copy.flip();

   return copy;
} // DynamicBitset::operator ~



/// Left-shifts the internal flags by the given number of positions.
///
/// @param[in]  pos  The number of positions to left-shift.
/// @return  A new dynamic bitset with the shifted flags.
/// @since  x.y.z, 09.06.2020
DynamicBitset DynamicBitset::operator <<( size_t pos) const noexcept( true)
{

   if ((pos == 0) || (mData.size() == 0))
      return *this;

   DynamicBitset  dbs( mData.size() + pos);

   for (size_t idx = 0; idx < mData.size(); ++idx)
   {
      dbs.mData[ idx + pos] = mData[ idx];
   } // end for

   return dbs;
} // DynamicBitset::operator <<



/// Left-shifts the internal flags of this object by the given number of
/// positions.
///
/// @param[in]  pos  The number of positions to left-shift.
/// @return  This object.
/// @since  x.y.z, 09.06.2020
DynamicBitset& DynamicBitset::operator <<=( size_t pos) noexcept( true)
{

   if ((pos == 0) || (mData.size() == 0))
      return *this;

   mData.resize( mData.size() + pos);

   for (size_t idx = mData.size() - 1; idx >= pos; --idx)
   {
      mData[ idx] = mData[ idx - pos];
   } // end for
   for (size_t idx = 0; idx < pos; ++idx)
   {
      mData[ idx] = false;
   } // end for

   return *this;
} // DynamicBitset::operator <<=



/// Right-shifts the internal flags by the given number of positions.
///
/// @param[in]  pos  The number of positions to right-shift.
/// @return  A new dynamic bitset with the shifted flags.
/// @since  x.y.z, 09.06.2020
DynamicBitset DynamicBitset::operator >>( size_t pos) const noexcept( true)
{

   if ((pos == 0) || (mData.size() == 0))
      return *this;

   DynamicBitset  dbs( mData.size());

   for (size_t idx = 0; idx + pos < mData.size(); ++idx)
   {
      dbs.mData[ idx] = mData[ idx + pos];
   } // end for

   return dbs;
} // DynamicBitset::operator >>



/// Right-shifts the internal flags of this object by the given number of
/// positions.
///
/// @param[in]  pos  The number of positions to right-shift.
/// @return  This object.
/// @since  x.y.z, 09.06.2020
DynamicBitset& DynamicBitset::operator >>=( size_t pos) noexcept( true)
{

   if ((pos == 0) || (mData.size() == 0))
      return *this;

   for (size_t idx = 0; idx + pos < mData.size(); ++idx)
   {
      mData[ idx] = mData[ idx + pos];
   } // end for
   for (size_t idx = mData.size() - pos; idx < mData.size(); ++idx)
   {
      mData[ idx] = false;
   } // end for

   return *this;
} // DynamicBitset::operator >>=



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
///    x.y.z, 11.06.2020
DynamicBitset operator &( const DynamicBitset& lhs, const DynamicBitset& rhs) noexcept( true)
{

   auto  copy( lhs);


   copy &= rhs;
   return copy;
} // operator &



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
///    x.y.z, 11.06.2020
DynamicBitset operator |( const DynamicBitset& lhs, const DynamicBitset& rhs) noexcept( true)
{

   auto  copy( lhs);


   copy |= rhs;
   return copy;
} // operator |



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
///    x.y.z, 11.06.2020
DynamicBitset operator ^( const DynamicBitset& lhs, const DynamicBitset& rhs) noexcept( true)
{

   auto  copy( lhs);


   copy ^= rhs;
   return copy;
} // operator ^



} // namespace common
} // namespace celma


// =====  END OF dynamic_bitset.cpp  =====

