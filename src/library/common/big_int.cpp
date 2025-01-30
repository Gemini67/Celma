
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2024-2025 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::BigInt.


// module headerfile include
#include "celma/common/big_int.hpp"


// C++ Standard Library includes
#include <iomanip>
#include <iostream>
#include <sstream>



namespace celma::common {



/// Dumps the contents of this object into the given stream.
/// The values of the internal vector are printed as a comma-separated list.
/// @param[out]  os  Stream to write into.
/// @since  x.y.z, 02.08.2024
void BigInt::dump( std::ostream& os) const
{

   os << "Length: " << mNumber.size() << std::endl
      << "Values: ";

   for (auto const& num : mNumber)
   {
      os << num << ", ";
   } // end for
   os << std::endl;
} // BigInt::dump



/// Converts the big integer into a decimal string representation.
/// @param[in]  grouped
///    Set this flag to format the decimal number with grouping.
/// @returns  String with the value formatted as decimal.
/// @since  x.y.z, 05.08.2024
std::string BigInt::toString( const bool grouped) const
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
} // BigInt::toString



/// Converts the big integer into a hexadecimal string representation.
/// @param[in]  grouped
///    Set this flag to format the hexadecimal number in groups of 8 digits.
/// @returns  String with the big integer value formatted as hexadecimal.
/// @since  x.y.z, 18.08.2024
[[nodiscard]] std::string BigInt::toHexString( const bool grouped) const
{

   std::string  result( "0x");


   for (size_t idx = mNumber.size(); idx-- > 0; )
   {
      std::ostringstream  oss;

      oss << std::hex;

      if (result.length() > 2)
      {
         oss << std::setw( 8) << std::setfill( '0');
         if (grouped)
            result.append( " ");
      } // end if

      oss << mNumber[ idx];
      result.append( oss.str());
   } // end for

   return result;
} // BigInt::toHexString



} // namespace celma:common


// =====  END OF big_int.cpp  =====

