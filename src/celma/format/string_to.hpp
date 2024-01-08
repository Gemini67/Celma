
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of the template function celma::format::stringTo<>().


#pragma once


#include <string>


namespace celma::format {


/// The standard library does not provide a single function to convert a value
/// from string format to short/long signed/unsigned integers, doubles etc.<br>
/// That's what this template does. Call it with the desired destination type,
/// internally the correct conversion function is chosen.
///
/// @tparam  T  Destination type to convert the value into.
/// @param[in]  str  String with the value to convert.
/// @return  Converted value from the string.
/// @since  1.17.0, 24.11.2018
template< typename T> T stringTo( const std::string& std);


#define  S2( t, c) \
   template<> [[nodiscard]] t stringTo< t>( const std::string& str) \
   { \
      return std::c( str); \
   }


S2( int8_t, stoi)
S2( uint8_t, stoi)
S2( int16_t, stoi)
S2( uint16_t, stoi)
S2( int32_t, stoi)
S2( uint32_t, stoul)
S2( int64_t, stol)
S2( uint64_t, stoul)

S2( float, stof)
S2( double, stod)
S2( long double, stold)


#undef  S2


} // namespace celma::format


// =====  END OF string_to.hpp  =====

