
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::@@@.


// module headerfile include
#include "celma/common/big_int.hpp"


// C++ Standard Library includes
#include <iomanip>
#include <iostream>
#include <sstream>



namespace celma::common {



/// 
/// @return
///    .
/// @since
///    x.y.z, 18.08.2024
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
}



} // namespace celma:common


// =====  END OF big_int.cpp  =====

