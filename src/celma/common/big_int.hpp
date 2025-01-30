
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023-2025 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


#pragma once


#include <cctype>
#include <cmath>
#include <cstdint>
#include <bit>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
#include "celma/common/pre_postfix.hpp"


namespace celma::common {


/// Exception thrown when a calculation error occurs, like division by zero.
/// This class was implemented because the existing classes somehow all did not
/// fit.
/// @since  x.y.z, 07.01.2024
class CalculationError : public std::runtime_error
{
public:
   /// Constructor, assigns the description of the error that occurred.
   ///
   /// @param[in]  what_arg  Text to store with the exception.
   /// @since  x.y.z, 07.01.2024
   CalculationError( const char* what_arg):
      std::runtime_error( what_arg)
   {
   } // CalculationError::CalculationError

   /// Constructor, assigns the description of the error that occurred.
   ///
   /// @param[in]  what_arg  Text to store with the exception.
   /// @since  x.y.z, 07.01.2024
   CalculationError( const std::string& what_arg):
      std::runtime_error( what_arg)
   {
   } // CalculationError::CalculationError

}; // CalculationError


/// Exception thrown when a conversion error occurs.
/// This class was implemented because the existing classes somehow all did not
/// fit.
/// @since  x.y.z, 07.01.2024
class ConversionError : public std::runtime_error
{
public:
   /// Constructor, assigns the description of the error that occurred.
   ///
   /// @param[in]  what_arg  Text to store with the exception.
   /// @since  x.y.z, 07.01.2024
   ConversionError( const char* what_arg):
      std::runtime_error( what_arg)
   {
   } // ConversionError::ConversionError

   /// Constructor, assigns the description of the error that occurred.
   ///
   /// @param[in]  what_arg  Text to store with the exception.
   /// @since  x.y.z, 07.01.2024
   ConversionError( const std::string& what_arg):
      std::runtime_error( what_arg)
   {
   } // ConversionError::ConversionError

}; // ConversionError


/// Stores integers with an arbitrary number of digits.
/// Internally the value is stored in a vector of unsigned 32 bit integers. This
/// way, operations can be executed with 64 bit integers and the result then
/// adapted and stored.<br>
/// Lowest bytes of the value are always in index 0.
/// @since  x.y.z, 07.02.2023
class BigInt
{
public:
   /// Bit mask used to get the lower 4 bytes of a 64 bit integer.
   static constexpr uint64_t  LowerQWordMask = 0xffffffff;
   /// Maximum value of one of the elements in the vector.
   static constexpr uint32_t  MaxEleVal = std::numeric_limits< uint32_t>::max();


   /// Default constructor, corresponds to creating an object with the value 0.
   /// @since  x.y.z, 07.02.2023
   BigInt() = default;

   /// Constructor, assigns a 32 bit value.
   /// @param[in]  value  Value to assign.
   /// @since  x.y.z, 07.02.2023
   explicit BigInt( uint32_t value);

   /// Constructor, assigns a 64 bit value.
   /// @param[in]  value  Value to assign.
   /// @since  x.y.z, 07.02.2023
   explicit BigInt( uint64_t value);

   /// Constructor, assigns a value from a string.
   /// The number may be written grouped with single quotes or spaces.<br>
   /// Also supports hex values starting with 0x.
   ///
   /// @param[in]  value  String with the value to assign.
   /// @throws
   ///    celma::common::ConversionError if the string contains anything besides
   ///    digits.
   /// @since  x.y.z, 08.01.2024
   explicit BigInt( const std::string& value) noexcept( false);

   BigInt( const BigInt&) = default;
   BigInt( BigInt&&) = default;
   ~BigInt() = default;

   /// Comparison function for two big integers.
   /// Must be defined early to be available for the following functions.
   ///
   /// @param[in]  other
   ///    Other big integer to compare against.
   /// @returns
   ///    - std::strong_ordering:less if this is less than \a other.
   ///    - std::strong_ordering:equal if this is equal to \a other.
   ///    - std::strong_ordering:greater if this is greater than \a other.
   /// @since
   ///    x.y.z, 08.02.2023
   [[nodiscard]] auto compare( const BigInt& other) const;

   /// Returns the relation between this and the other big integer.
   ///
   /// @param[in]  other
   ///    Other big integer to compare against.
   /// @returns
   ///    Result of compare().
   /// @since
   ///    x.y.z, 05.08.2024
   [[nodiscard]] auto operator <=>( const BigInt& other) const;

   /// Assigns a long integer value.
   /// @param[in]  value  Value to assign.
   /// @returns  This object.
   /// @since  x.y.z, 07.02.2023
   BigInt& assign( uint64_t value);

   /// Adds a 4 byte integer value.
   /// @param[in]  value  Value to add.
   /// @returns  This object.
   /// @since  x.y.z, 07.02.2023
   BigInt& add( uint32_t value);

   /// Adds the value from another big integer.
   /// @param[in]  other  Other big integer to add the value from.
   /// @returns  This object.
   /// @since  x.y.z, 07.02.2023
   BigInt& add( const BigInt& other);

   /// Adds a 4 byte integer.
   /// @param[in]  value  Value to add.
   /// @returns  This object.
   /// @since  x.y.z, 07.02.2023
   BigInt& operator +=( uint32_t value);

   /// Adds the value from another big integer.
   /// @param[in]  other  Other big integer to add the value from.
   /// @returns  This object.
   /// @since  x.y.z, 07.02.2023
   BigInt& operator +=( const BigInt& other);

   /// Subtracts a 4 byte integer.
   /// @param[in]  value  4 byte integer to subtract.
   /// @returns  This object.
   /// @since  x.y.z, 29.12.2024
   BigInt& sub( uint32_t value);

   /// Subtracts the value from another big integer.
   /// @param[in]  other  Other big integer object to subtract its value from
   ///                    this.
   /// @returns  This object.
   /// @since  x.y.z, 29.12.2024
   BigInt& sub( const BigInt& other);

   /// Subtracts a 4 byte integer.
   /// @param[in]  value  4 byte integer to subtract.
   /// @returns  This object.
   /// @since  x.y.z, 29.12.2024
   BigInt& operator -=( uint32_t value);

   /// Subtracts the value from another big integer.
   /// @param[in]  other  Other big integer object to subtract its value from
   ///                    this.
   /// @returns  This object.
   /// @since  x.y.z, 29.12.2024
   BigInt& operator -=( const BigInt& other);

   /// Multiplies with a 4 byte integer.
   /// @param[in]  value  4 byte integer to multiply with.
   /// @returns  This object.
   /// @since  x.y.z, 04.01.2024
   BigInt& multiply( uint32_t value);

   /// Multiplies with another big integer.
   /// @param[in]  other  Other big integer object to multiply with.
   /// @returns  This object.
   /// @since  x.y.z, 10.06.2024
   BigInt& multiply( const BigInt& other);
   
   /// Multiplies with a 4 byte integer.
   /// @param[in]  value  4 byte integer to multiply with.
   /// @returns  This object.
   /// @since  x.y.z, 04.01.2024
   BigInt& operator *=( uint32_t value);

   /// Multiplies with another big integer.
   /// @param[in]  other  Other big integer object to multiply with.
   /// @returns  This object.
   /// @since  x.y.z, 10.06.2024
   BigInt& operator *=( const BigInt& other);

   /// Divides by a 4 byte integer.
   /// @param[in]   value
   ///    4 byte value to divide by.
   /// @param[out]  remainder
   ///    When set, the remainder of the divistion is returned here.
   /// @returns  This object.
   /// @throws celma::common::CalculationError when attempting to divide by zero.
   /// @since  x.y.z, 07.01.2024
   BigInt& divide( uint32_t value, uint32_t* remainder = nullptr) noexcept( false);

   /// Divides a big integer by another big integer.
   /// @param[in]   value
   ///    The big integer value to divide by.
   /// @param[out]  remainder
   ///    When set, the remainder of the divistion is returned here.
   /// @returns  This object.
   /// @since  x.y.z, 26.12.2024
   BigInt& divide( const BigInt& value, BigInt* remainder = nullptr)
      noexcept( false);

   /// Divides by a 4 byte integer.
   /// @param[in]  value  4 byte value to divide by.
   /// @returns  This object.
   /// @since  x.y.z, 12.08.2024
   BigInt& operator /=( uint32_t value);

   /// Divides a big integer by another big integer.
   /// @param[in]  value  The big integer value to divide by.
   /// @returns  This object.
   /// @since  x.y.z, 26.12.2024
   BigInt& operator /=( const BigInt& value);

   /// Prefix increment operator.
   /// @returns  This object.
   /// @since  x.y.z, 07.02.2023
   BigInt& operator ++( std::prefix);

   /// Postfix increment operator.
   /// @returns  Big integer object with the previous value of this.
   /// @since  x.y.z, 07.02.2023
   BigInt operator ++( std::postfix);

   /// Prefix decrement operator.
   /// @returns  This object.
   /// @since  x.y.z, 29.12.2024
   BigInt& operator --( std::prefix);

   /// Postfix decrement operator.
   /// @returns  Big integer object with the previous value of this.
   /// @since  x.y.z, 29.12.2024
   BigInt operator --( std::postfix);

   BigInt& operator =( const BigInt&) = default;
   BigInt& operator =( BigInt&&) = default;

   /// Assigns a 4 byte integer value.
   /// @param[in]  value  Value to assign.
   /// @returns  This object.
   /// @since  x.y.z, 07.02.2023
   BigInt& operator =( uint32_t value);

   /// Assigns a long integer value.
   /// @param[in]  value  Value to assign.
   /// @returns  This object.
   /// @since  x.y.z, 07.02.2023
   BigInt& operator =( uint64_t value);

   /// Assigns a value from a string.
   ///
   /// @param[in]  value  String with the value to assign.
   /// @returns  This object.
   /// @throws
   ///    celma::common::ConversionError if the string contains anything besides
   ///    digits.
   /// @since  x.y.z, 07.01.2024
   BigInt& operator =( const std::string& value) noexcept( false);

   /// Left-shifts the value.
   /// @param[in]  shiftval  Number of bits to shift the value by.
   /// @returns  This object.
   /// @since  x.y.z, 08.02.2023
   BigInt& operator <<=( uint32_t shiftval);

   /// Returns a big integer where the value was left-shifted.
   /// @param[in]  shiftval  Number of bits to shift the value by.
   /// @returns  New big integer object with the shifted value.
   /// @since  x.y.z, 08.02.2023
   [[nodiscard]] BigInt operator <<( uint32_t shiftval) const;

   /// Right-shifts the value.
   /// @param[in]  shiftval  Number of bits to shift the value by.
   /// @returns  This object.
   /// @since  x.y.z, 07.01.2024
   BigInt& operator >>=( uint32_t shiftval);

   /// Returns a big integer where the value was right-shifted.
   /// @param[in]  shiftval  Number of bits to shift the value by.
   /// @returns  New big integer object with the shifted value.
   /// @since  x.y.z, 05.08.2024
   [[nodiscard]] BigInt operator >>( uint32_t shiftval) const;

   /// Returns the internally stored value as a long integer, if possible.
   /// @returns  Internal value, if it fits into a 4 byte integer.
   /// @throws
   ///    celma::common::ConversionError if the value is too big to be converted
   ///    to a 64 bit integer.
   /// @since  x.y.z, 08.02.2023
   [[nodiscard]] operator uint64_t() const noexcept( false);

   /// Returns if this object currently has the value 0.
   /// Empty internal vector after construction equals the value 0.
   /// @returns  \c true if this objecz currently has the value 0.
   /// @since  x.y.z, 08.02.2023
   [[nodiscard]] bool isNull() const;

   /// Returns the length of the internal vector.
   /// @returns  Length of the internal vector.
   /// @since  x.y.z, 08.02.2023
   [[nodiscard]] size_t internalLength() const;

   /// Returns the number of bits used by the big integer number currently stored
   /// in this object.
   /// @returns  Number of bits of the value.
   /// @since  x.y.z, 21.01.2025
   [[nodiscard]] size_t bitLength() const;

   /// Returns the value of the element at the given position.
   /// @param[in]  idx  Index of the element to return the value of.
   /// @returns  Value of the element at the given position.
   /// @throws
   ///    std::out_of_range if the given index is out of the range of existing
   ///    parts of the big integer.
   /// @since  x.y.z, 08.02.2023
   [[nodiscard]] uint32_t element( size_t idx) const noexcept( false);

   /// Dumps the contents of this object into the given stream.
   /// The values of the internal vector are printed as a comma-separated list.
   /// @param[out]  os  Stream to write into.
   /// @since  x.y.z, 02.08.2024
   void dump( std::ostream& os) const;

   /// Converts the big integer into a decimal string representation.
   /// @param[in]  grouped
   ///    Set this flag to format the decimal number with grouping.
   /// @returns  String with the value formatted as decimal.
   /// @since  x.y.z, 05.08.2024
   [[nodiscard]] std::string toString( bool grouped = false) const;

   /// Converts the big integer into a hexadecimal string representation.
   /// @param[in]  grouped
   ///    Set this flag to format the hexadecimal number in groups of 8 digits.
   /// @returns  String with the big integer value formatted as hexadecimal.
   /// @since  x.y.z, 18.08.2024
   [[nodiscard]] std::string toHexString( bool grouped = false) const;

   /// Returns if the bit at the given position is set.
   /// Alwys returns \c false if the given position is greater than the current
   /// size of the big integer.
   /// @param[in]  pos  Position of he bit to test.
   /// @returns  \c true if the bit at the given posiion is set.
   /// @since  x.y.z, 22.01.2025
   [[nodiscard]] bool testBit( uint64_t pos) const;

   /// Sets the bit at the given position.
   /// If necessary, additional elements are added to the internal vector, until
   /// the bit can be set.
   /// @param[in]  pos  Position of the bit to set.
   /// @since  x.y.z, 22.01.2025
   void setBit( uint64_t pos);

private:
   /// Multiplies two big integers.
   /// Both values must be greater than 1.
   /// @param[in]  lhs  First value for the multiplication.
   /// @param[in]  rhs  Second value for the multiplication.
   /// @returns  Big integer object with the result of the multiplication.
   /// @since  x.y.z, 04.01.2024
   [[nodiscard]] static BigInt mul( const BigInt& lhs, BigInt rhs);

   /// Internal method for multiplying a big integer with a 32 bit integer.
   /// Special cases like 0, 1, etc. should be handled beforehand.
   /// @param[in]  value  4 byte integer to multiply by.
   /// @returns  This object.
   /// @since  x.y.z, 04.01.2024
   BigInt& mulInt( uint32_t value);

   /// Stores the big integer.
   /// Position 0 is the lowest value.
   std::vector< uint32_t>  mNumber;

}; // BigInt


// inlined methods
// ===============


inline BigInt::BigInt( const uint32_t value)
{
   mNumber.push_back( value);
} // BigInt::BigInt


inline BigInt::BigInt( const uint64_t value)
{
   mNumber.push_back( value & LowerQWordMask);
   if (value > MaxEleVal)
      mNumber.push_back( value >> 32);
} // BigInt::BigInt


inline BigInt::BigInt( const std::string& value) noexcept( false)
{
   if (value.empty() || (value == "0"))
      return;

   if (value.substr( 0, 2) == "0x")
   {
      auto  convertHexChar = []( char hex_char)
         {
            if ((hex_char >= '0') && (hex_char <= '9'))
               return hex_char - '0';
            if ((hex_char >= 'a') && (hex_char <= 'f'))
               return hex_char - 'a' + 10;
            throw ConversionError( "string contains non-digit");
         };

      mNumber.push_back( convertHexChar( value[ 2]));
      for (size_t idx = 3; idx < value.length(); ++idx)
      {
         if (value[ idx] == ' ')
            continue;

         *this <<= 4;
         add( convertHexChar( value[ idx]));
      } // end for
      return;
   } // end if

   if (!std::isdigit( value[ 0]))
      throw ConversionError( "string contains non-digit");

   mNumber.push_back( value[ 0] - '0');
   for (size_t idx = 1; idx < value.length(); ++idx)
   {
      // allow grouping in the string, simply ignore them
      if ((value[ idx] == ' ') || (value[ idx] == '\''))
         continue;

      if (!std::isdigit( value[ idx]))
         throw ConversionError( "string contains non-digit");

      multiply( 10);
      add( value[ idx] - '0');
   } // end for
} // BigInt::BigInt


inline auto BigInt::compare( const BigInt& other) const
{
   // special cases
   if (isNull() && other.isNull())
      return std::strong_ordering::equal;
   if (mNumber.size() > other.mNumber.size())
      return std::strong_ordering::greater;
   if (other.mNumber.size() > mNumber.size())
      return std::strong_ordering::less;
   // when we get here, the sizes of the two vectors are equal
   if (mNumber.size() == 1)
      return mNumber[ 0] <=> other.mNumber[ 0];

   // compare elements starting at the highest
   for (size_t idx = mNumber.size() - 1; idx > 0; --idx)
   {
      if (mNumber[ idx] > other.mNumber[ idx])
         return std::strong_ordering::greater;
      if (other.mNumber[ idx] > mNumber[ idx])
         return std::strong_ordering::less;
   } // end for

   // no difference found until element 1
   return mNumber[ 0] <=> other.mNumber[ 0];
} // BigInt::compare


inline auto BigInt::operator <=>( const BigInt& other) const
{
   return compare( other);
} // BigInt::operator <=>


inline BigInt& BigInt::assign( const uint64_t value)
{
   mNumber.clear();
   mNumber.push_back( value & LowerQWordMask);
   if (value > MaxEleVal)
      mNumber.push_back( value >> 32);
   return *this;
} // BigInt::assign


inline BigInt& BigInt::add( const uint32_t value)
{
   if (value == 0)
      return *this;

   if (mNumber.empty())
   {
      mNumber.push_back( value);
      return *this;
   } // end if

   if (isNull())
   {
      mNumber[ 0] = value;
      return *this;
   } // end if

   uint64_t  result = static_cast< uint64_t>( mNumber[ 0]) + value;
   size_t    index = 0;
   while (result >= MaxEleVal)
   {
      mNumber[ index] = result & LowerQWordMask;
      result >>= 32;
      if (++index >= mNumber.size())
      {
         mNumber.push_back( result);
         return *this;
      } // end if
      result += mNumber[ index];
   } // end while

   if (result != 0)
   {
      if (index < mNumber.size())
         mNumber[ index] = result;
      else
         mNumber.push_back( result);
   } // end if
   return *this;
} // BigInt::add


inline BigInt& BigInt::add( const BigInt& other)
{
   if (other.isNull())
      return *this;

   if (isNull())
      return *this = other;

   auto const  both = std::min( mNumber.size(), other.mNumber.size());
   uint64_t    take_over = 0;

   for (size_t idx = 0; idx < both; ++idx)
   {
      take_over += static_cast< uint64_t>( mNumber[ idx]) + static_cast< uint64_t>( other.mNumber[ idx]);
      mNumber[ idx] = (take_over & LowerQWordMask);
      take_over >>= 32;
   } // end for

   auto  index = both;

   if (mNumber.size() > both)
   {
      while (index < mNumber.size())
      {
         take_over += static_cast< uint64_t>( mNumber[ index]);
         mNumber[ index] = (take_over & LowerQWordMask);
         take_over >>= 32;
         ++index;
      }
   } else if (other.mNumber.size() > both)
   {
      while (index < other.mNumber.size())
      {
         take_over += static_cast< uint64_t>( other.mNumber[ index]);
         mNumber.push_back( take_over & LowerQWordMask);
         take_over >>= 32;
         ++index;
      }
   } // end if

   if (take_over > 0)
   {
      mNumber.push_back( take_over);
   } // end if

   return *this;
} // BigInt::add


inline BigInt& BigInt::operator +=( const uint32_t value)
{
   return add( value);
} // BigInt::operator +=


inline BigInt& BigInt::operator +=( const BigInt& other)
{
   return add( other);
} // BigInt::operator +=


inline BigInt& BigInt::sub( const uint32_t value)
{
   if (value == 0)
      return *this;
   if (mNumber.size() == 1)
   {
      if (value >= mNumber[ 0])
      {
         mNumber[ 0] = 0;
         return *this;
      } // end if
      mNumber[ 0] -= value;
      return *this;
   } // end if

   if (value <= mNumber[ 0])
   {
      mNumber[ 0] -= value;
      return *this;
   } // end if

   uint32_t  take_over = 1;
   uint64_t  index = 1;

   uint64_t  calc = static_cast<uint64_t>( mNumber[ 0]) + 0x100000000;
   calc -= value;
   mNumber[ 0] = calc;

   do
   {
      if (take_over <= mNumber[ index])
      {
         mNumber[ index] -= take_over;
         take_over = 0;
      } else
      {
         calc = static_cast<uint64_t>( mNumber[ index]) + 0x100000000;
         calc -= take_over;
         mNumber[ index] = calc;
      } // end if
      ++index;
   } while ((index < mNumber.size()) && (take_over > 0));

   if (mNumber.back() == 0)
      mNumber.pop_back();

   return *this;
} // BigInt::sub


inline BigInt& BigInt::sub( const BigInt& other)
{
   if (isNull() || other.isNull())
      return *this;
   // if (other > *this)
   if (other >= *this)
   {
      mNumber.clear();
      mNumber.push_back( 0);
      return *this;
   } // end if

   uint64_t    take_over = 0;
   auto const  both = std::min( mNumber.size(), other.mNumber.size());

   for (uint64_t index = 0; index < both; ++index)
   {
      if ((static_cast< uint64_t>( other.mNumber[ index]) + take_over) <= mNumber[ index])
      {
         mNumber[ index] -= (other.mNumber[ index] + take_over);
         take_over = 0;
      } else
      {
         uint64_t  calc = static_cast<uint64_t>( mNumber[ index]) + 0x100000000;
         calc -= (other.mNumber[ index] + take_over);
         mNumber[ index] = calc;
         take_over = 1;
      } // end if 
   } // end for

   if ((both < mNumber.size()) && (take_over > 0))
   {
      for (uint64_t index = both; both < mNumber.size(); ++index)
      {
         if (mNumber[ index] >= take_over)
         {
            mNumber[ index] -= take_over;
            break;
         } else
         {
            uint64_t  calc = static_cast<uint64_t>( mNumber[ index]) + 0x100000000;
            calc -= take_over;
            mNumber[ index] = calc;
            take_over = 1;
         } // end if
      } // end for
   } // end if

   while (mNumber.back() == 0)
      mNumber.pop_back();

   return *this;
} // BigInt::sub


inline BigInt& BigInt::operator -=( const uint32_t value)
{
   return sub( value);
} // BigInt::operator -=


inline BigInt& BigInt::operator -=( const BigInt& other)
{
   return sub( other);
} // BigInt::operator -=


inline BigInt& BigInt::multiply( const uint32_t value)
{
   if (value == 0)
   {
      mNumber.clear();
      return *this;
   } // end if
   if (value == 1)
      return *this;
   if (isNull())
      return *this;
   if ((mNumber.size() == 1) && (mNumber[ 0] == 1))
   {
      mNumber[ 0] = value;
      return *this;
   } // end if
   return mulInt( value);
} // BigInt::multiply


inline BigInt& BigInt::multiply( const BigInt& other)
{
   if (other.isNull())
   {
      mNumber.clear();
      return *this;
   } // end if
   if (isNull())
      return *this;
   if ((other.mNumber.size() == 1) && (other.mNumber[ 0] == 1))
      return *this;
   if ((mNumber.size() == 1) && (mNumber[ 0] == 1))
   {
      mNumber = other.mNumber;
      return *this;
   } // end if

   if (mNumber.size() > other.mNumber.size())
      *this = mul( other, *this);
   else
      *this = mul( *this, other);
   return *this;
} // BigInt::multiply


inline BigInt& BigInt::operator *=( const uint32_t value)
{
   return multiply( value);
} // BigInt::operator *=


inline BigInt& BigInt::operator *=( const BigInt& other)
{
   return multiply( other);
} // BigInt::operator *=


BigInt& BigInt::divide( const uint32_t value, uint32_t* remainder) noexcept( false)
{
   if (value == 0)
      throw CalculationError( "division by zero is invalid");
   if (remainder != nullptr)
      *remainder = 0;

   if (value == 1)
      return *this;
   if (isNull())
      return *this;

   if (mNumber.size() == 1)
   {
      if (mNumber[ 0] == value)
      {
         mNumber[ 0] = 1;
         return *this;
      } // end if

      if (remainder != nullptr)
         *remainder = (mNumber[ 0] % value);
      mNumber[ 0] /= value;
      return *this;
   } // end if

   uint64_t  take_over = 0;

   for (size_t idx = mNumber.size(); idx-- > 0; )
   {
      const uint64_t  element = static_cast< uint64_t>( mNumber[ idx])
         + (take_over << 32);
      const uint32_t  result = element / value;
      const uint32_t  remain = element % value;

      if ((result == 0) && (idx + 1 == mNumber.size()))
      {
         if (idx == 0)
         {
            mNumber[ 0] = 0;
            if (remainder != nullptr)
               *remainder = remain;
            return *this;
         } // end i
         mNumber.pop_back();
      } else
      {
         mNumber[ idx] = result;
      } // end if

      take_over = remain;
   } // end for

   if (remainder != nullptr)
      *remainder = take_over;

   return *this;
} // BigInt::divide


inline BigInt& BigInt::divide( const BigInt& value, BigInt* remainder)
   noexcept( false)
{
   if (value.isNull())
      throw CalculationError( "division by zero is invalid");

   if (value.mNumber.size() == 1)
   {
      if (remainder != nullptr)
      {
         *remainder = 0U;
         return divide( value.mNumber[ 0], &remainder->mNumber[ 0]);
      } // end if
      return divide( value.mNumber[ 0]);
   }// end if

   if (remainder != nullptr)
      remainder->mNumber.clear();
   if (isNull())
      return *this;

   auto const  cmp_result = compare( value);
   if (cmp_result == std::strong_ordering::less)
   {
      if (remainder != nullptr)
         *remainder = value;
      *this = 0U;
      return *this;
   } // end if

   if (cmp_result == std::strong_ordering::equal)
   {
      *this = 1U;
      return *this;
   } // end if

   auto const  my_bitlength = bitLength();
   auto const  value_bitlength = value.bitLength();
   auto        diff_length = my_bitlength - value_bitlength;

   BigInt  cmp_value( value);
   cmp_value <<= diff_length;

   BigInt  result;

   while (diff_length > 0)
   {
      if (*this >= cmp_value)
      {
         result.setBit( diff_length);
         if (sub( cmp_value).isNull())
            break;  // while
      } // end if

      cmp_value >>= 1;
      --diff_length;
   } // end while

   if (*this >= cmp_value)
   {
      result.setBit( diff_length);
      sub( cmp_value);
   } // end if

   if (remainder != nullptr)
      *remainder = *this;
   *this = result;

   return *this;
} // BigInt::divide


inline BigInt& BigInt::operator /=( const uint32_t value)
{
   return divide( value);
} // BigInt::operator /=


inline BigInt& BigInt::operator /=( const BigInt& value)
{
   return divide( value);
} // BigInt::operator /=


inline BigInt& BigInt::operator ++( std::prefix)
{
   return add( 1);
} // BigInt::operator ++


inline BigInt BigInt::operator ++( std::postfix)
{
   BigInt  copy( *this);
   add( 1);
   return copy;
} // BigInt::operator ++


inline BigInt& BigInt::operator --( std::prefix)
{
   return sub( 1);
} // BigInt::operator --


inline BigInt BigInt::operator --( std::postfix)
{
   BigInt  copy( *this);
   sub( 1);
   return copy;
} // BigInt::operator --


inline BigInt& BigInt::operator =( const uint32_t value)
{
   mNumber.clear();
   mNumber.push_back( value);
   return *this;
} // BigInt::operator =


inline BigInt& BigInt::operator =( const uint64_t value)
{
   return assign( value);
} // BigInt::operator =


inline BigInt& BigInt::operator =( const std::string& value) noexcept( false)
{
   *this = BigInt( value);
   return *this;
} // BigInt::operator =


inline BigInt& BigInt::operator <<=( uint32_t shiftval)
{
   if (isNull())
      return *this;

   size_t  index = 0;

   if (auto const shift_bytes = (shiftval / 32))
   {
      mNumber.insert( mNumber.begin(), shift_bytes, 0);
      shiftval %= 32;
      index = shift_bytes;
   } // end if

   uint64_t  take_over = 0;

   for (; index < mNumber.size(); ++index)
   {
      take_over = (static_cast< uint64_t>( mNumber[ index]) << shiftval) + take_over;
      mNumber[ index] = (take_over & 0xffffffff);
      take_over >>= 32;
   } // end for

   if (take_over > 0)
   {
      mNumber.push_back( take_over);
   } // end if

   return *this;
} // BigInt::operator <<=


inline BigInt BigInt::operator <<( const uint32_t shiftval) const
{
   BigInt  copy( *this);
   return copy <<= shiftval;
} // BigInt::operator <<


inline BigInt& BigInt::operator >>=( uint32_t shiftval)
{
   if (isNull() || (shiftval == 0))
      return *this;
   if (auto const  num_elements = (shiftval / 32))
   {
      if (num_elements >= mNumber.size())
         return assign( 0);
      mNumber.erase( mNumber.begin(), mNumber.begin() + num_elements);
      shiftval -= (32 * num_elements);
   } // end if

   const uint32_t  shift_mask = (1UL << (static_cast< uint64_t>( shiftval) + 1UL)) - 1UL;
   uint32_t        push_down = 0;
   for (size_t idx = mNumber.size(); idx-- > 0; )
   {
      auto &      element = mNumber[ idx];
      auto const  next_push_down = element & shift_mask;
      element >>= shiftval;
      if (push_down > 0)
         element |= (push_down << (32 - shiftval));
      push_down = next_push_down;
   } // end for
   if (mNumber.back() == 0)
      mNumber.pop_back();
   return *this;
} // BigInt::operator >>=


inline BigInt BigInt::operator >>( const uint32_t shiftval) const
{
   BigInt  copy( *this);
   return copy >>= shiftval;
} // BigInt::operator >>


inline BigInt::operator uint64_t() const noexcept( false)
{
   if (mNumber.size() > 2)
      throw ConversionError( "too big to convert to 64 bit integer");
   if (isNull())
      return 0;
   if (mNumber.size() == 2)
      return (static_cast< uint64_t>( mNumber[ 1]) << 32) + mNumber[ 0];
   return mNumber[ 0];
} // BigInt::operator uint64_t


inline bool BigInt::isNull() const
{
   return mNumber.empty() || ((mNumber.size() == 1) && (mNumber[ 0] == 0));
} // BigInt::isNull


inline size_t BigInt::internalLength() const
{
   return mNumber.size();
} // BigInt::internalLength


inline size_t BigInt::bitLength() const
{
   return (mNumber.size() - 1) * 32 + (32 - __builtin_clz( mNumber.back()));
} // BigInt::bitLength


inline uint32_t BigInt::element( const size_t idx) const noexcept( false)
{
   if (idx >= mNumber.size())
      throw std::out_of_range( "index is out of range");
   return mNumber[ idx];
} // BigInt::element


inline bool BigInt::testBit( const uint64_t pos) const
{
   const size_t  elem = pos / 32;
   const size_t  bit  = pos % 32;
   if (elem >= mNumber.size())
      return false;
   return (mNumber[ elem] & (1U << bit)) != 0;
} // BigInt::testBit


inline void BigInt::setBit( const uint64_t pos)
{
   const size_t  elem = pos / 32;
   const size_t  bit  = pos % 32;
   while (elem >= mNumber.size())
      mNumber.push_back( 0);
   mNumber[ elem] |= (1U << bit);
} // BigInt::setBit


inline BigInt BigInt::mul( const BigInt& lhs, BigInt rhs)
{
   BigInt  result;
   for (auto factor : lhs.mNumber)
   {
      if (factor > 0)
      {
         if (factor == 1)
         {
            result += rhs;
         } else
         {
            BigInt  copy( rhs);
            copy.mulInt( factor);
            result += copy;
         } // end if
      } // end if
      rhs <<= 32;
   } // end for
   return result;
} // BigInt::mul


inline BigInt& BigInt::mulInt( const uint32_t value)
{
   uint64_t  result = 0;
   for (auto & element : mNumber)
   {
      result += static_cast< uint64_t>( element) * static_cast< uint64_t>( value);
      element = result & LowerQWordMask;
      result >>= 32;
   } // end for
   if (result > 0)
      mNumber.push_back( result);
   return *this;
} // BigInt::mulInt


// functions
// =========


/// Adds a 4 byte integer to a big integer.
/// @param[in]  lhs  Big integer to add \a rhs to.
/// @param[in]  rhs  4 byte integer to add to \a lhs.
/// @returns  Result of adding \a rhs to \a lhs.
/// @since  x.y.z, 07.01.2024
[[nodiscard]] inline BigInt operator +( BigInt lhs, const uint32_t rhs)
{
   return lhs += rhs;
} // operator +


/// Adds two big integers.
/// @param[in]  lhs  First big integer for the addition.
/// @param[in]  rhs  Big integer to add to \a lhs.
/// @returns  Result of adding \a lhs and \a rhs.
/// @since  x.y.z, 08.02.2023
[[nodiscard]] inline BigInt operator +( BigInt lhs, const BigInt& rhs)
{
   return lhs += rhs;
} // operator +


/// Subtracts a 4 byte integer from a big integer.
/// @param[in]  lhs  Big integer to subtract \a rhs from.
/// @param[in]  rhs  4 byte integer to subtract from the big integer.
/// @returns  Result of \a lhs - \a rhs.
/// @since  x.y.z, 29.12.2024
[[nodiscard]] inline BigInt operator -( BigInt lhs, const uint32_t rhs)
{
   return lhs -= rhs;
} // operator -


/// Subtracts two big integers.
/// @param[in]  lhs  Big integer to subtract from.
/// @param[in]  rhs  Big integer to subtract from \a lhs.
/// @returns  Result of \a lhs - \a rhs.
/// @since  x.y.z, 29.12.2024
[[nodiscard]] inline BigInt operator -( BigInt lhs, const BigInt& rhs)
{
   return lhs -= rhs;
} // operator -


/// Multiplies a big integer with a 4 byte integer.
/// @param[in]  lhs  Big integer to use for the multiplication.
/// @param[in]  rhs  4 byte integer to multiply with.
/// @returns  Result of the multiplication \a lhs * \a rhs.
/// @since  x.y.z, 07.01.2024
[[nodiscard]] inline BigInt operator *( BigInt lhs, const uint32_t rhs)
{
   return lhs *= rhs;
} // operator *


/// Multiplies two big integers.
/// @param[in]  lhs  First value for the multiplication.
/// @param[in]  rhs  Second value for the multiplication.
/// @returns  Result of the multiplication \a lhs * \a rhs.
/// @since  x.y.z, 07.01.2024
[[nodiscard]] inline BigInt operator *( BigInt lhs, const BigInt& rhs)
{
   return lhs *= rhs;
} // operator *


/// Division of a big integer by a 4 byte integer.
/// @param[in]  lhs  Big integer to use for the division.
/// @param[in]  rhs  4 byte integer to divide by.
/// @returns  Result of the division \a lhs / \a rhs.
/// @since  x.y.z, 26.12.2024
[[nodiscard]] inline BigInt operator /( BigInt lhs, const uint32_t rhs)
{
   return lhs /= rhs;
} // operator /


/// Returns the result of the division.
/// @param[in]  lhs  Dividend to use.
/// @param[in]  rhs  Divisor to divide by.
/// @returns  Result of the division \a lhs / \a rhs.
/// @since  x.y.z, 26.12.2024
[[nodiscard]] inline BigInt operator /( BigInt lhs, const BigInt& rhs)
{
   return lhs /= rhs;
} // operator /


/// Calculates the factorial of a number.
/// @param[in]  number  Value to calculate the factorial of.
/// @returns  Factorial of \a number, i.e. \a number!
/// @since  x.y.z, 12.08.2024
[[nodiscard]] inline BigInt factorial( const uint32_t number)
{

   BigInt  bi( 1U);

   for (uint32_t i = 1; i <= number; ++i)
   {
      bi *= i;
   } // end for

   return bi;
} // factorial


/// Simple square calculation.
/// @param[in]  value  Value to calculae the square of.
/// @returns  Square of \a value, i.e. \a value ^ 2 == \a value * \a value.
/// @since  x.y.z, 13.08.2024
[[nodiscard]] inline BigInt square( BigInt value)
{

   value.multiply( value);
   return value;
} // square


/// Calculate exponential values.
/// @param[in]  value  Base value of the exponent.
/// @param[in]  exp    Exponent.
/// @returns  \a value ^ \a exp.
/// @since  x.y.z, 13.08.2024
[[nodiscard]] inline BigInt power( BigInt value, uint64_t exp)
{

   BigInt  result( 1U);


   for (;;)
   {
      if (exp & 1)
         result *= value;
      exp >>= 1;
      if (exp == 0)
         break; // for
      value *= value;
   } // end for

   return result;
} // power


/// Calculate the square root using Newton's method.
/// @param[in]  value  Value to calculate the square root of.
/// @returns  The nearest integer value to the square root of \a value.
/// @since  x.y.z, 13.08.2024
[[nodiscard]] inline BigInt sqrt( const BigInt& value)
{

   if (value.isNull())
      return BigInt( 0U);

   if (value.internalLength() == 1)
      return BigInt( static_cast< uint64_t>( std::sqrt( value.element( 0))));

   if (value.internalLength() == 2)
   {
      const uint64_t  ival = (static_cast< uint64_t>( value.element( 1)) << 32UL)
                             + value.element( 0);
      return BigInt( static_cast< uint64_t>( std::sqrt( ival)));
   } // end if

   // used for the comparisons below
   static const BigInt  one( 1U);

   BigInt  result( value);
   BigInt  root;

   for (;;)
   {
      root = result + (value / result);
      root >>= 1;

      if (root > result)
      {
         if ((root - result).compare( one) <= 0)
            break;
      } else if ((result - root).compare( one) <= 0)
      {
         break;
      } // end if

      result = root;
   } // end for

   return root;
} // sqrt


} // namespace celma::common


// =====  END OF big_int.hpp  =====

