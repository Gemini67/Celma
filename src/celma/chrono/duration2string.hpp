
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
/// See documentation of function celma::chrono::duration2string().


#pragma once


#include <iostream>
#include <sstream>
#include <string>


namespace celma::chrono {


/// Converts a period in seconds into minutes, hours, etc.
///
/// @param[in]  seconds
///    Number of seconds to convert into minutes, hours etc.
/// @return
///    String with the period split into minutes, hours etc.
/// @since
///    x.y.z, 27.02.2023
[[nodiscard]] inline std::string duration2string( time_t seconds)
{
   std::ostringstream  oss;
   auto const          minutes = seconds / 60;
   auto const          seconds_only = seconds % 60;

   if (minutes > 0)
   {
      auto const  minutes_only = minutes % 60;
      auto const  hours = minutes / 60;
      if (hours > 0)
      {
         auto const  hours_only = hours % 24;
         auto const  days = hours / 24;

         if (days > 0)
         {
         	auto const  days_only = days % 7;
         	auto const  weeks = days / 7;

            if (weeks > 0)
            {
               oss << weeks << "w ";
            } // end if

            oss << days_only << "d ";
         } // end if

         oss << hours_only << "h ";
      } // end if

      oss << minutes_only << "m ";
   } // end if

   oss << seconds_only << 's';

   return oss.str();
} // duration2string


} // namespace celma::chrono


// =====  END OF duration2string.hpp  =====

