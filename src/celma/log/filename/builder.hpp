
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
/// See documentation of class celma::log::filename::Builder.


#ifndef CELMA_LOG_FILENAME_BUILDER_HPP
#define CELMA_LOG_FILENAME_BUILDER_HPP


#include <iosfwd>
#include <string>
#include "celma/log/filename/definition.hpp"
#include "celma/log/detail/i_format_stream.hpp"


namespace celma { namespace log {

namespace detail {
class LogMsg;
} // namespace detail

namespace filename {


/// Formats a log message for output, using the given Destination object to
/// format the fields.
/// @since  x.y.z, 16.10.2017
class Builder: private Definition
{
public:
   /// Constructor.
   /// @param[in]  def  The object with the format definition.
   /// @since  x.y.z, 16.10.2017
   Builder( const Definition& def);

   /// 
   /// @param[in]  dest         .
   /// @param[in]  logfile_nbr  .
   /// @param[in]  timestamp    .
   /// @since  x.y.z, 16.10.2017
   void filename( std::string& dest, int logfile_nbr, time_t timestamp) const;

private:
   /// Formats a date, time or timestamp.
   /// @param[out]  dest        The stream to write into.
   /// @param[in]   part_def    The object with may contain the custom format
   ///                          string.
   /// @param[in]   format_str  The default format string, used when no custom
   ///                          format string is available.
   /// @param[in]   timestamp   The timestamp to format.
   /// @since  x.y.z, 16.10.2017
   void formatDate( std::string& dest, const Part& part_def,
                    const char* format_str, time_t timestamp) const;

   /// Formats a logfile number.
   /// @param[out]  dest         The string to append the formatted logfile
   ///                           number to.
   /// @param[in]   part_def     The object with contains the format settings
   ///                           for the logfile number
   /// @param[in]   logfile_nbr  The logfile number to format.
   /// @since  x.y.z, 16.10.2017
   void formatNumber( std::string& dest, const Part& part_def,
                      int logfile_nbr) const;

}; // Builder


} // namespace filename
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILENAME_BUILDER_HPP


// ===========================  END OF builder.hpp  ===========================

