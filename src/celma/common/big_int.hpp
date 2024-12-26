
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


#pragma once


#include <cctype>
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
/// @since  x.y.z, 08.02.2023
class BigInt
{
public:
   static constexpr uint64_t  LowerQWordMask = 0xffffffff;
   static constexpr uint32_t  MaxEleVal = std::numeric_limits< uint32_t>::max();


   /// Default constructor, corresponds to creating an object with the value 0.
   /// @since  x.y.z, 07.02.2023
   BigInt() = default;

   /// Constructor, assigns a 32 bit value.
   /// @param[in]  value  Value to assign.
   /// @since  x.y.z, 07.02.2023
   explicit BigInt( const uint32_t value);

   /// Constructor, assigns a 64 bit value.
   /// @param[in]  value  Value to assign.
   /// @since  x.y.z, 07.02.2023
   explicit BigInt( const uint64_t value);

   /// Constructor, assigns a value from a string.
   /// @param[in]  value  String with the value to assign.
   /// @throws
   ///    celma::common::ConversionError if the string contains anything besides
   ///    digits.
   /// @since  x.y.z, 08.01.2024
   explicit BigInt( const std::string& value) noexcept( false);

   BigInt( const BigInt&) = default;
   BigInt( BigInt&&) = default;
   ~BigInt() = default;

   BigInt& assign( const uint64_t value)
   {
      mNumber.clear();
      mNumber.push_back( value & LowerQWordMask);
      if (value > MaxEleVal)
         mNumber.push_back( value >> 32);
      return *this;
   }

   BigInt& add( const uint32_t value)
   {
      if (value == 0)
         return *this;

      if (mNumber.empty())
      {
         mNumber.push_back( value);
         return *this;
      }

      if (isNull())
      {
         mNumber[ 0] = value;
         return *this;
      }

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
   }

   BigInt& add( const BigInt& other)
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
   }

   BigInt& operator +=( const uint32_t value)
   {
      return add( value);
   }

   BigInt& operator +=( const BigInt& other)
   {
      return add( other);
   }

   BigInt& multiply( const uint32_t value)
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

   BigInt& multiply( const BigInt& other)
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

   BigInt& operator *=( const uint32_t value)
   {
      return multiply( value);
   } // BigInt::operator *=

   BigInt& operator *=( const BigInt& other)
   {
      return multiply( other);
   } // BigInt::operator *=

   /// 
   /// @param[in]  value
   ///    .
   /// @return
   ///    .
   /// @throws
   ///    celma::common::CalculationError when attempting to divive by zero.
   /// @since
   ///    x.y.z, 07.01.2024
   BigInt& divide( const uint32_t value, uint32_t* remainder = nullptr) noexcept( false)
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

      //auto const  pos_first_bit = 32 - std::countl_zero( value);
      //BigInt  power2( *this);
      //power2 <<= pos_first_bit;

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

   /// 
   /// @param[in]  value
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 12.08.2024
   BigInt& operator /=( const uint32_t value)
   {
      return divide( value);
   } // BigInt::operator /=

   BigInt& operator ++( std::prefix)
   {
      return add( 1);
   }

   BigInt operator ++( std::postfix)
   {
      BigInt  copy( *this);
      add( 1);
      return copy;
   }

   BigInt& operator =( const BigInt&) = default;
   BigInt& operator =( BigInt&&) = default;

   BigInt& operator =( const uint32_t value)
   {
      mNumber.clear();
      mNumber.push_back( value);
      return *this;
   }

   BigInt& operator =( const uint64_t value)
   {
      return assign( value);
   }

   /// Assigns a value from a string.
   ///
   /// @param[in]  value  String with the value to assign.
   /// @returns  This object.
   /// @throws
   ///    celma::common::ConversionError if the string contains anything besides
   ///    digits.
   /// @since  x.y.z, 07.01.2024
   BigInt& operator =( const std::string& value) noexcept( false)
   {
      *this = BigInt( value);
      return *this;
   } // BigInt::operator =

   /// 
   /// @param[in]  shiftval
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 08.02.2023
   BigInt& operator <<=( uint32_t shiftval)
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
   }

   BigInt operator <<( const uint32_t shiftval) const
   {
      BigInt  copy( *this);
      return copy <<= shiftval;
   }

   /// 
   /// @param[in]  shiftval
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 07.01.2024
   BigInt& operator >>=( uint32_t shiftval)
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
      return *this;
   }

   /// 
   /// @param[in]  shiftval
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 05.08.2024
   BigInt operator >>( const uint32_t shiftval) const
   {
      BigInt  copy( *this);
      return copy >>= shiftval;
   }

   /// 
   /// @return
   ///    .
   /// @throws
   ///    celma::common::ConversionError if the value is too big to be converted
   ///    to a 64 bit integer.
   /// @since
   ///    x.y.z, 08.02.2023
   [[nodiscard]] operator uint64_t() const noexcept( false)
   {
      if (mNumber.size() > 2)
         throw ConversionError( "too big to convert to 64 bit integer");
      if (isNull())
         return 0;
      if (mNumber.size() == 2)
         return (static_cast< uint64_t>( mNumber[ 1]) << 32) + mNumber[ 0];
      return mNumber[ 0];
   }

   /// 
   /// @param[in]  other
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 08.02.2023
   [[nodiscard]] int8_t compare( const BigInt& other) const
   {
      if (isNull() && other.isNull())
         return 0;
      if (mNumber.size() > other.mNumber.size())
         return 1;
      if (other.mNumber.size() > mNumber.size())
         return -1;
      // when we get here, the sizes of the two vectors are equal
      for (size_t idx = mNumber.size() - 1; idx-- > 0; )
      {
         if (mNumber[ idx] > other.mNumber[ idx])
            return 1;
         if (other.mNumber[ idx] > mNumber[ idx])
            return -1;
      } // end for
      return 0;
   }

   /// 
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 08.02.2023
   [[nodiscard]] bool isNull() const
   {
      return mNumber.empty() || ((mNumber.size() == 1) && (mNumber[ 0] == 0));
   }

   /// 
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 08.02.2023
   [[nodiscard]] size_t internalLength() const
   {
      return mNumber.size();
   }

   /// 
   /// @param[in]  idx
   ///    .
   /// @return
   ///    .
   /// @throws
   ///    std::out_of_range if the given index is out of the range of existing
   ///    parts of the big integer.
   /// @since
   ///    x.y.z, 08.02.2023
   [[nodiscard]] uint32_t element( const size_t idx) const noexcept( false)
   {
      if (idx >= mNumber.size())
         throw std::out_of_range( "index is out of range");
      return mNumber[ idx];
   }

   /// 
   /// @param[in]  other
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 05.08.2024
   [[nodiscard]] auto operator <=>( const BigInt& other) const
   {
      return compare( other);
   }

   /// 
   /// @param[in]  os
   ///    .
   /// @since
   ///    x.y.z, 02.08.2024
   void dump( std::ostream& os) const
   {
      os << "Length: " << mNumber.size() << std::endl
         << "Values: ";
      for (auto const& num : mNumber)
      {
         os << num << ", ";
      } // end for
      os << std::endl;
   }

   /// 
   /// @param[in]  grouped
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 05.08.2024
   [[nodiscard]] std::string toString( const bool grouped = false) const
   {
      auto         copy( *this);
      std::string  result;
      uint8_t      inserted = 0;

      while (!copy.isNull())
      {
         if (grouped && (++inserted == 4))
         {
            result.insert( 0, 1, '\'');
            inserted = 1;
         } // end if

         uint32_t  remain = 0;
         copy.divide( 10, &remain);
         result.insert( 0, 1, remain + '0');
      } // end if
      return result;
   }

   /// 
   /// @param[in]  grouped
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 18.08.2024
   [[nodiscard]] std::string toHexString( bool grouped = false) const;

private:
   /// Calculates lhs * rhs.
   ///
   /// @param[in]  lhs
   ///    .
   /// @param[in]  rhs
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 04.01.2024
   [[nodiscard]] static BigInt mul( const BigInt& lhs, BigInt rhs)
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
   }

   /// Internal method for multiplying a big integer with a 32 bit integer.
   /// Special cases like 0, 1, etc. should be handled beforehand.
   ///
   /// @param[in]  value
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 04.01.2024
   BigInt& mulInt( const uint32_t value)
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

   std::vector< uint32_t>  mNumber;

};


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
      if ((value[ idx] == ' ') || (value[ idx] == '\''))
         continue;

      if (!std::isdigit( value[ idx]))
         throw ConversionError( "string contains non-digit");

      multiply( 10);
      add( value[ idx] - '0');
   } // end for
} // BigInt::BigInt


// functions
// =========


/// 
/// @param[in]  lhs
///    .
/// @param[in]  rhs
///    .
/// @return
///    .
/// @since
///    x.y.z, 07.01.2024
[[nodiscard]] inline BigInt operator +( BigInt lhs, const uint32_t rhs)
{
   return lhs += rhs;
}


/// 
/// @param[in]  lhs
///    .
/// @param[in]  rhs
///    .
/// @return
///    .
/// @since
///    x.y.z, 08.02.2023
[[nodiscard]] inline BigInt operator +( BigInt lhs, const BigInt& rhs)
{
   return lhs += rhs;
}


/// 
/// @param[in]  lhs
///    .
/// @param[in]  rhs
///    .
/// @return
///    .
/// @since
///    x.y.z, 07.01.2024
[[nodiscard]] inline BigInt operator *( BigInt lhs, const uint32_t rhs)
{
   return lhs *= rhs;
}


/// 
/// @param[in]  lhs
///    .
/// @param[in]  rhs
///    .
/// @return
///    .
/// @since
///    x.y.z, 07.01.2024
[[nodiscard]] inline BigInt operator *( BigInt lhs, const BigInt& rhs)
{
   return lhs *= rhs;
}


/// 
/// @param[in]  number
///    .
/// @return
///    .
/// @since
///    x.y.z, 12.08.2024
[[nodiscard]] inline BigInt factorial( const uint32_t number)
{

   BigInt  bi( 1U);

   for (uint32_t i = 1; i <= number; ++i)
   {
      bi *= i;
   } // end for

   return bi;
} // factorial


/// 
/// @param[in]  value
///    .
/// @return
///    .
/// @since
///    x.y.z, 13.08.2024
[[nodiscard]] inline BigInt square( BigInt value)
{

   value.multiply( value);
   return value;
} // square


/// 
/// @param[in]  value
///    .
/// @param[in]  exp
///    .
/// @return
///    .
/// @since
///    x.y.z, 13.08.2024
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



} // namespace celma::common


// =====  END OF big_int.hpp  =====

