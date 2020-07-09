
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
/// See documentation of the operator functions.<br>
/// The names like KiB == kibibyte etc. were chosen to make clear that the unit
/// factor will be 1024, not just 1000 (like kilobytes could be).


#ifndef CELMA_UNIT_PREFIXES_HPP
#define CELMA_UNIT_PREFIXES_HPP


#include <cstddef>


/// Unit for kibibytes, 1024 bytes.
///
/// @param[in]  v  The kibibyte value to return as bytes.
/// @return  \c v kibibytes in bytes (multiplied by 1024).
/// @since  x.y.z, 07.07.2020
constexpr std::size_t operator ""_KiB( unsigned long long v)
{
  return 1024ul * v;
} // operator ""_KiB


/// Unit for mebibytes, 1024 * 1024 bytes.
///
/// @param[in]  v  The mebibyte value to return as bytes.
/// @return  \c v mebibytes in bytes (multiplied by 1024^2).
/// @since  x.y.z, 07.07.2020
constexpr std::size_t operator ""_MiB( unsigned long long v)
{
  return v * 1024_KiB;
} // operator ""_MiB


/// Unit for gibibytes, 1024^3 bytes.
///
/// @param[in]  v  The gibibyte value to return as bytes.
/// @return  \c v gibibytes in bytes (multiplied by 1024^3).
/// @since  x.y.z, 07.07.2020
constexpr std::size_t operator ""_GiB( unsigned long long v)
{
  return v * 1024_MiB;
} // operator ""_GiB


/// Unit for tebibytes, 1024^4 bytes.
///
/// @param[in]  v  The tebibyte value to return as bytes.
/// @return  \c v tebibytes in bytes (multiplied by 1024^4).
/// @since  x.y.z, 07.07.2020
constexpr std::size_t operator ""_TiB( unsigned long long v)
{
  return v * 1024_GiB;
} // operator ""_TiB


/// Unit for pebibytes, 1024^5 bytes.
///
/// @param[in]  v  The pebibyte value to return as bytes.
/// @return  \c v pebibytes in bytes (multiplied by 1024^5).
/// @since  x.y.z, 07.07.2020
constexpr std::size_t operator ""_PiB( unsigned long long v)
{
  return v * 1024_TiB;
} // operator ""_PiB


/// Unit for exbibytes, 1024^6 bytes.
///
/// @param[in]  v  The exbibyte value to return as bytes.
/// @return  \c v exbibytes in bytes (multiplied by 1024^6).
/// @since  x.y.z, 07.07.2020
constexpr std::size_t operator ""_EiB( unsigned long long v)
{
  return v * 1024_PiB;
} // operator ""_EiB


#endif   // CELMA_UNIT_PREFIXES_HPP


// =====  END OF unit_prefixes.hpp  =====

