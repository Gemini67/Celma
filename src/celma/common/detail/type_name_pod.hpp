
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
--*/


/// @file
/// Adds partial template specialisations for the 'plain old data types'.


#ifndef CELMA_TYPE_NAME_POD_HPP
#define CELMA_TYPE_NAME_POD_HPP


#include "celma/common/constexpr_string_concat.hpp"
#include "celma/common/constexpr_string_from.hpp"
#include "celma/common/detail/provide_simple_type_name.hpp"


namespace celma {


/// Provides the name of the type 'bool'.
PROVIDE_SIMPLE_TYPE_NAME( bool);
/// Provides the name of the type 'char'.
PROVIDE_SIMPLE_TYPE_NAME( char);
/// Provides the name of the type 'unsigned char'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned char);
/// Provides the name of the type 'short'.
PROVIDE_SIMPLE_TYPE_NAME( short);
/// Provides the name of the type 'unsigned short'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned short);
/// Provides the name of the type 'int'.
PROVIDE_SIMPLE_TYPE_NAME( int);
/// Provides the name of the type 'unsigned int'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned int);
/// Provides the name of the type 'long'.
PROVIDE_SIMPLE_TYPE_NAME( long);
/// Provides the name of the type 'unsigned long'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned long);
/// Provides the name of the type 'long long'.
PROVIDE_SIMPLE_TYPE_NAME( long long);
/// Provides the name of the type 'unsigned long long'.
PROVIDE_SIMPLE_TYPE_NAME( unsigned long long);
/// Provides the name of the type 'float'.
PROVIDE_SIMPLE_TYPE_NAME( float);
/// Provides the name of the type 'double'.
PROVIDE_SIMPLE_TYPE_NAME( double);
/// Provides the name of the type 'double'.
PROVIDE_SIMPLE_TYPE_NAME( long double);

/// Provides the name of the type 'char16_t'.
PROVIDE_SIMPLE_TYPE_NAME( char16_t);
/// Provides the name of the type 'char32_t'.
PROVIDE_SIMPLE_TYPE_NAME( char32_t);
/// Provides the name of the type 'wchar_t'.
PROVIDE_SIMPLE_TYPE_NAME( wchar_t);


/// Specialisation for C arrays.
///
/// @tparam  T  The type of the data stored in the array.
/// @tparam  N  The number of values stored in the array.
/// @since  x.y.z, 29.04.2019
template< typename T, std::size_t N> class type< T[ N]>
{
public:
   /// Returns the name of the type.
   ///
   /// @return  'T[N]'.
   /// @since  x.y.z, 29.04.2019
   static constexpr const char* name()
   {
      return &mName[ 0];
   } // type< T[ N]>::name

   /// Used to store the name of the type persistently.
   /// Is public to build nested container names, don't access for printing.
   static constexpr auto const  mName =
      common::string_concat( type< T>::mName, "[",
         common::string_from< std::size_t, N>::value, "]");

}; // type< T[ N]>


} // namespace celma


#endif   // CELMA_TYPE_NAME_POD_HPP


// =====  END OF type_name_pod.hpp  =====

