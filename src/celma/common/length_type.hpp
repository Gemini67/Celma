
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::LengthType<>.


#pragma once


#include <cstdint>


namespace celma::common {


/// Namespace used for helper functions and classes.
namespace detail {


/// Returns the number of bytes needed to be able to manage the given length.
/// @param[in]  length  The length value for which the required number of bytes
///                     is determined.
/// @return
/// - 1 [byte] for values up to 255.
/// - 2 [bytes] for values up to 64 k
/// - 4 [bytes] for values up to 4 G
/// - 8 [bytes] otherwise.
/// @since  x.y.z, 23.01.2021
constexpr int bytesNeeded( uint64_t length)
{
   return (length < 256) ? 1 : (length < 65'536) ? 2
          : (length < 4'294'967'296) ? 4 : 8;
} // bytesNeeded


/// Template that will give the type.
template< uint64_t L> class type4length;


/// Template that provides the type needed to store a one byte value.
/// @since  x.y.z, 23.01.2021
template<> class type4length< 1>
{
public:
   /// Type for 1 byte values: unsigned 1 byte integer.
   using type = uint8_t;
}; // type4length


/// Template that provides the type needed to store a two byte value.
/// @since  x.y.z, 23.01.2021
template<> class type4length< 2>
{
public:
   /// Type for 2 byte values: unsigned short integer.
   using type = uint16_t;
}; // type4length


/// Template that provides the type needed to store a four byte value.
/// @since  x.y.z, 23.01.2021
template<> class type4length< 4>
{
public:
   /// Type for 4 byte values: unsigned integer.
   using type = uint32_t;
}; // type4length


/// Template that provides the type needed to store an eight byte value.
/// @since  x.y.z, 23.01.2021
template<> class type4length< 8>
{
public:
   /// Type for 4 byte values: unsigned long integer.
   using type = uint64_t;
}; // type4length


} // namespace detail


/// Provides the minimum type needed for a variable to store the given value.
/// Usage:  <pre> typename six::foundation::LengthType< 200>::type  my_var; </pre>
/// @tparam  L  The maximum value to store in the variable.
/// @since  x.y.z, 23.01.2021
template< uint64_t L> class LengthType
{
public:
   /// The type needed to store the given value, always an unsigned int with
   /// different lengths (1, 2, 4 or 8 bytes).
   using type = typename detail::type4length< detail::bytesNeeded( L)>::type;
}; // LengthType


} // namespace celma::common


// =====  END OF type_length.hpp  =====

