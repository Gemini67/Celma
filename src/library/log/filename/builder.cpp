
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
/// See documentation of class celma::log::filename::Format.


// module header file include
#include "celma/log/filename/builder.hpp"


// OS/C library includes
#include <ctime>


// C++ Standard Library include
#include <iomanip>
#include <ostream>


// project includes
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace filename {



/// Constructor.
/// @param[in]  def  The object with the format definition.
/// @since  x.y.z, 16.10.2017
Builder::Builder( const Definition& def):
   Definition( def)
{
} // Builder::Builder



/// 
/// @param[in]  dest         .
/// @param[in]  logfile_nbr  .
/// @param[in]  timestamp    .
/// @since  x.y.z, 16.10.2017
void Builder::filename( std::string& dest, int logfile_nbr,
                        time_t timestamp) const
{

   for (auto const& part_def : mParts)
   {
      switch (part_def.mType)
      {
      case PartTypes::constant:
         dest.append( part_def.mConstant);
         break;
      case PartTypes::date:
         formatDate( dest, part_def, "%F", timestamp);
         break;
      case PartTypes::number:
         formatNumber( dest, part_def, logfile_nbr);
         break;
      } // end switch
   } // end for

} // Builder::filename



/// Formats a date, time or timestamp.
/// @param[out]  dest        The stream to write into.
/// @param[in]   part_def    The object with may contain the custom format
///                          string.
/// @param[in]   format_str  The default format string, used when no custom
///                          format string is available.
/// @param[in]   timestamp   The timestamp to format.
/// @since  x.y.z, 16.10.2017
void Builder::formatDate( std::string& dest, const Part& part_def,
                          const char* format_str, time_t timestamp) const
{

   // format date, time or timestamp
   auto const  use_format_str = part_def.mConstant.empty() ? format_str :
                                part_def.mConstant.c_str();
   char        timestamp_str[ 128];


   ::strftime( timestamp_str, sizeof( timestamp_str) - 1, use_format_str,
               ::localtime( &timestamp));
   dest.append( timestamp_str);

} // Builder::formatDate



/// Formats a logfile number.
/// @param[out]  dest         The string to append the formatted logfile
///                           number to.
/// @param[in]   part_def     The object with contains the format settings
///                           for the logfile number
/// @param[in]   logfile_nbr  The logfile number to format.
/// @since  x.y.z, 16.10.2017
void Builder::formatNumber( std::string& dest, const Part& part_def,
                            int logfile_nbr) const
{

   std::ostringstream  oss;


   if (part_def.mFixedWidth > 0)
      oss << std::setw( part_def.mFixedWidth);
//   if (part_def.mFillChar != '\0')
//      oss << std::setfill( part_def.mFillChar);

   oss << logfile_nbr;

   dest.append( oss.str());

} // Builder::formatNumber



} // namespace filename
} // namespace log
} // namespace celma


// ===========================  END OF builder.cpp  ===========================

