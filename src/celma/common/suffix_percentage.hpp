
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of user defined literals _pc and _pm.


#pragma once


/// 
/// @param[in]  percentage
///    .
/// @return
///    .
/// @since
///    x.y.z, 01.05.2023
inline double operator ""_pc( const long double percentage)
{
   return percentage / 100.0;
}


inline double operator ""_pc( const unsigned long long percentage)
{
   return static_cast< long double>( percentage) / 100.0;
}


inline double operator ""_pm( const long double permille)
{
   return permille / 1'000.0;
}


inline double operator ""_pm( const unsigned long long permille)
{
   return static_cast< long double>( permille) / 1'000.0;
}


// =====  END OF suffix-percentage.hpp  =====

