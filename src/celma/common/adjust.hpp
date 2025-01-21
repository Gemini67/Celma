
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2025 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template functions celma::common::adjustMin() and
/// celma::common::adjustMax().


#pragma once


namespace celma::common {


/// Adjusts \a value if it is less than \a min_value.
/// @param[in,out]  value      Value to check and adjust if necessary.
/// @param[in]      min_value  Minimum value to ensure.
/// @since  0.13.4, 24.02.2017
template< typename T> void adjustMin( T& value, const T& min_value)
{

   if (value < min_value)
      value = min_value;

} // adjustMin


/// Adjusts \a value if it is greater than \a max_value.
/// @param[in,out]  value      Value to check and adjust if necessary.
/// @param[in]      max_value  Maximum value to ensure.
/// @since  0.13.4, 24.02.2017
template< typename T> void adjustMax( T& value, const T& max_value)
{

   if (value > max_value)
      value = max_value;

} // adjustMax


} // namespace celma::common


// =====  END OF adjust.hpp  =====

