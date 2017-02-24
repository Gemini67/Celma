
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::@@@.


#ifndef CELMA_COMMON_ADJUST_HPP
#define CELMA_COMMON_ADJUST_HPP


namespace celma { namespace common {


/// Adjusts \a value if it is less than \a min_value.
/// @param[in,out]  value      The value to check and adjust if necessary.
/// @param[in]      min_value  The minimum value to ensure.
/// @since  0.13.4, 24.02.2017
template< typename T> void adjustMin( T& value, const T& min_value)
{

   if (value < min_value)
      value = min_value;

} // adjustMin


/// Adjusts \a value if it is greater than \a max_value.
/// @param[in,out]  value      The value to check and adjust if necessary.
/// @param[in]      max_value  The maximum value to ensure.
/// @since  0.13.4, 24.02.2017
template< typename T> void adjustMax( T& value, const T& max_value)
{

   if (value > max_value)
      value = max_value;

} // adjustMax


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_ADJUST_HPP


// ============================  END OF adjust.hpp  ============================

