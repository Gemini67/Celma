
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::filename::Builder.


// module header file include
#include "celma/log/filename/builder.hpp"


// OS/C library includes
#include <ctime>


// C++ Standard Library include
#include <iomanip>
#include <ostream>
#include <stdexcept>


// project includes
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace filename {



/// Convenience method that builds and returns a log filename without the
/// need to explicitly create a Builder object.
///
/// @param[in]  def
///    The object with the format definition.
/// @param[in]  logfile_nbr
///    The number of the logfile. May eventually not be used, depending on
///    the definiion of the log filename.
/// @param[in]  timestamp
///    The timestamp to use for building a date part of the log filename. May
///    eventually not be used, depending on the definition of the log
///    filename.
/// @return
///    The path and filename of the logfile built according to the given
///    definition.
/// @since  1.0.0, 22.12.2017
std::string Builder::filename( const Definition& def, int logfile_nbr,
      time_t timestamp)
{

   Builder      my_builder( def);
   std::string  result;


   my_builder.filename( result, logfile_nbr, timestamp);

   return result;
} // Builder::filename



/// Constructor.
///
/// @param[in]  def  The object with the format definition.
/// @throws  when the definition object contains no parts.
/// @since  1.0.0, 16.10.2017
Builder::Builder( const Definition& def):
   Definition( def)
{

   if (mParts.empty())
      throw std::invalid_argument( "definition for filename is empty");

} // Builder::Builder



/// Creates a log file number according to the format definition given in the
/// constructor.
///
/// @param[out]  dest
///    Returns the log file path and name.
/// @param[in]   logfile_nbr
///    The number of thelog file. May eventually not be used.
/// @param[in]   timestamp
///    The timestamp to use when the log filename definition includes a date
///    part.
/// @since  1.0.0, 16.10.2017
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
      case PartTypes::env:
         {
            const char*  env_value = ::getenv( part_def.mConstant.c_str());
            if ((env_value != nullptr) && (env_value[ 0] != '\0'))
            {
               dest.append( env_value);
            } // end if
         } // end scope
         break;
      case PartTypes::pid:
         formatNumber( dest, part_def, ::getpid());
         break;
      } // end switch
   } // end for

} // Builder::filename



/// Formats a date, time or timestamp.
///
/// @param[out]  dest
///    The stream to write into.
/// @param[in]   part_def
///    The object with may contain the custom format string.
/// @param[in]   format_str
///    The default format string, used when no custom format string is
///    available.
/// @param[in]   timestamp   The timestamp to format.
/// @since  1.0.0, 16.10.2017
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



/// Formats a logfile number or a pid.
///
/// @param[out]  dest
///    The string to append the formatted logfile number to.
/// @param[in]   part_def
///    The object with contains the format settings for the logfile number
/// @param[in]   number
///    The number to format.
/// @since  1.0.0, 16.10.2017
void Builder::formatNumber( std::string& dest, const Part& part_def,
                            int number) const
{

   std::ostringstream  oss;


   if (part_def.mFixedWidth > 0)
      oss << std::setw( part_def.mFixedWidth);
   if (part_def.mFillChar != '\0')
      oss << std::setfill( part_def.mFillChar);

   oss << number;

   dest.append( oss.str());

} // Builder::formatNumber



} // namespace filename
} // namespace log
} // namespace celma


// =====  END OF builder.cpp  =====

