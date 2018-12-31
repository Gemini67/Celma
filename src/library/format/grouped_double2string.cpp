
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
/// See documentation of function celma::format::grouped_double2string().


// module header file include
#include "celma/format/grouped_double2string.hpp"


// OS/C lib includes
#include <cmath>


// C++ Standard Library includes
#include <iomanip>
#include <sstream>


// project includes
#include "celma/format/grouped_int2string.hpp"


namespace celma { namespace format {



/// Converts a floating point number into string format, with grouping of the
/// digits before the deciomal point.
///
/// @param[in]  value
///    The value to format.
/// @param[in]  precision
///    Precision == numbewr of digits to use after the decimal point.
/// @param[in]  group_char
///    The character to use for the grouping.
/// @return
///    The string with the formatted double.
/// @since
///    1.13.0, 04.10.2018
std::string grouped_double2string( double value, int precision, char group_char)
{
 
   const int64_t       integer_part = static_cast< int64_t>( value);
   const double        fractions = ::fabs( value - integer_part);
   std::string         int_str( grouped_int2string( integer_part, group_char));
   std::ostringstream  oss;
 
 
   oss << std::fixed << std::setprecision( precision) << fractions;
   int_str.append( oss.str().substr( 1));
 
   return int_str;
} // grouped_double2string



} // namespace format
} // namespace celma


// =====  END OF grouped_double_to_string.cpp  =====

