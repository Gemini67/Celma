
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// This file provides two families of grouped_int2string() functions:
/// - The first family takes the value to convert plus the separator character
///   as parameters and returns the string with the converted value.
/// - The second family takes a pointer to the destination buffer, the value to
///   convert and the separator character as parameters.
/// Implemented are two 'families' of functions, each using the feature called
/// 'tag dispatch' to call the corresponding function depending on the size and
/// the sign of the value type.<br>
/// Using the functions is simply: Just call grouped_int2string().


#pragma once


#include <iostream>
#include <string>
#include <type_traits>
#include "celma/format/detail/grouped_int8_to_string.hpp"
#include "celma/format/detail/grouped_int16_to_string.hpp"
#include "celma/format/detail/grouped_int32_to_string.hpp"
#include "celma/format/detail/grouped_int64_to_string.hpp"


#define  TEMPLATE_ENABLE_IF( b, s, r) \
   template< typename T> \
      std::enable_if_t< std::is_integral< T>::value && (sizeof( T) == b) \
                        && std::is_signed< T>::value == s, \
                        r>

#define  FUNCTION_ENABLED( b, s, f) \
   TEMPLATE_ENABLE_IF( b, s, std::string) \
      grouped_int2string( T value, char group_char = '\'') \
   { \
      return detail::f( value, group_char); \
   }

#define  BUFFER_FUNCTION_ENABLED( b, s, f) \
   TEMPLATE_ENABLE_IF( b, s, int) \
      grouped_int2string( char* buffer, T value, char group_char = '\'') \
   { \
      return detail::f( buffer, value, group_char); \
   }

#define  SIGNED_FUNCTIONS( b, f) \
   FUNCTION_ENABLED( b, true, f) \
   BUFFER_FUNCTION_ENABLED( b, true, f)

#define  UNSIGNED_FUNCTIONS( b, f) \
   FUNCTION_ENABLED( b, false, f) \
   BUFFER_FUNCTION_ENABLED( b, false, f)


namespace celma::format {


SIGNED_FUNCTIONS( 1, groupedInt8toString)
UNSIGNED_FUNCTIONS( 1, groupedUint8toString)
SIGNED_FUNCTIONS( 2, groupedInt16toString)
UNSIGNED_FUNCTIONS( 2, groupedUint16toString)
SIGNED_FUNCTIONS( 4, groupedInt32toString)
UNSIGNED_FUNCTIONS( 4, groupedUint32toString)
SIGNED_FUNCTIONS( 8, groupedInt64toString)
UNSIGNED_FUNCTIONS( 8, groupedUint64toString)


/// Helper class that makes sure that an integer value is printed as grouped
/// integer.
///
/// @tparam  T  The type of the value.
/// @tparam  S  The separator character to use for the grouping.
/// @since  1.17.0, 22.11.2018
template< typename T = int32_t, char S = '\''> class GroupedInt
{
public:
   /// Constructor, stores the given value.
   ///
   /// @param[in]  init_val  The initial value to store.
   /// @since  1.17.0, 22.11.2018
   explicit GroupedInt( const T init_val = 0):
      mValue( init_val)
   {
   } // GroupedInt< T, S>::GroupedInt

   GroupedInt( const GroupedInt&) = default;
   ~GroupedInt() = default;

   GroupedInt& operator =( const GroupedInt& other) = default;

   /// Assigns a new value.
   /// 
   /// @param[in]  value  The new value sto store.
   /// @return  This object.
   /// @since  1.17.0, 22.11.2018
   GroupedInt& operator =( const T value)
   {
      mValue = value;
      return *this;
   } // GroupedInt< T, S>::operator =

   /// Returns the internally stored value by const reference.
   ///
   /// @return  The (const reference to the) internally stored value.
   /// @since  1.17.0, 24.11.2018
   operator const T&() const
   {
      return mValue;
   } // GroupedInt< T, S>::operator const T&

   /// Returns the internally stored value by reference.
   ///
   /// @return  The (reference to the) internally stored value.
   /// @since  1.17.0, 22.11.2018
   operator T&()
   {
      return mValue;
   } // GroupedInt< T, S>::operator T&

   /// Print the internally stored value as grouped integer.
   ///
   /// @param[in]  os
   ///    The stream to print to.
   /// @param[in]  gi
   ///    The object to print the value of.
   /// @return
   ///    The stream as passed in.
   /// @since
   ///    1.17.0, 22.11.2018
   friend inline std::ostream& operator <<( std::ostream& os, const GroupedInt& gi)
   {
      return os << grouped_int2string( gi.mValue, S);
   } // operator <<

private:
   /// The value.
   T  mValue;

}; // GroupedInt< T, S>


/// Stream manipulator function that returns a grouped int object, when then
/// prints the integer value as grouped integer.
///
/// @tparam  T  The type of the integer.
/// @param[in]  value  The value to print.
/// @return  Grouped int object that holds the integer value.
/// @since  1.17.0, 24.11.2018
template< typename T> [[nodiscard]] GroupedInt< T> groupedInt( T value)
{
  return GroupedInt< T>( value);
} // groupedInt


} // namespace celma::format


#undef  UNSIGNED_FUNCTIONS
#undef  SIGNED_FUNCTIONS
#undef  BUFFER_FUNCTION_ENABLED
#undef  FUNCTION_ENABLED
#undef  TEMPLATE_ENABLE_IF


// =====  END OF grouped_int2string.hpp  =====

