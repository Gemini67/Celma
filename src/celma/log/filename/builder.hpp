
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::filename::Builder.


#ifndef CELMA_LOG_FILENAME_BUILDER_HPP
#define CELMA_LOG_FILENAME_BUILDER_HPP


#include <ctime>
#include <iosfwd>
#include <string>
#include "celma/log/filename/definition.hpp"
#include "celma/log/detail/i_format_stream.hpp"


namespace celma { namespace log {

namespace detail {
class LogMsg;
} // namespace detail

namespace filename {


/// Formats a log message for output, using the given Definition object to
/// format the fields.
/// @since  1.0.0, 16.10.2017
class Builder: private Definition
{
public:
   /// Convenience method that builds and returns a log filename without the
   /// need to explicitly create a Builder object.
   /// @param[in]  def          The object with the format definition.
   /// @param[in]  logfile_nbr  The number of the logfile. May eventually not be
   ///                          used, depending on the definiion of the log
   ///                          filename.
   /// @param[in]  timestamp    The timestamp to use for building a date part of
   ///                          the log filename. May eventually not be used,
   ///                          depending on the definition of the log filename.
   /// @return  The path and filename of the logfile built according to the
   ///          given definition.
   /// @since  1.0.0, 22.12.2017
   static std::string filename( const Definition& def, int logfile_nbr = 0,
      time_t timestamp = ::time( nullptr));

   /// Constructor.
   /// @param[in]  def  The object with the format definition.
   /// @since  1.0.0, 16.10.2017
   explicit Builder( const Definition& def);

   /// Creates a log file number according to the format definition given in the
   /// constructor.
   /// @param[out]  dest         Returns the log file path and name.
   /// @param[in]   logfile_nbr  The number of thelog file. May eventually not
   ///                           be used.
   /// @param[in]   timestamp    The timestamp to use when the log filename
   ///                           definition incluses a date part.
   /// @since  1.0.0, 16.10.2017
   void filename( std::string& dest, int logfile_nbr, time_t timestamp) const;

private:
   /// Formats a date, time or timestamp.
   /// @param[out]  dest        The stream to write into.
   /// @param[in]   part_def    The object with may contain the custom format
   ///                          string.
   /// @param[in]   format_str  The default format string, used when no custom
   ///                          format string is available.
   /// @param[in]   timestamp   The timestamp to format.
   /// @since  1.0.0, 16.10.2017
   void formatDate( std::string& dest, const Part& part_def,
                    const char* format_str, time_t timestamp) const;

   /// Formats a logfile number.
   /// @param[out]  dest         The string to append the formatted logfile
   ///                           number to.
   /// @param[in]   part_def     The object with contains the format settings
   ///                           for the logfile number
   /// @param[in]   logfile_nbr  The logfile number to format.
   /// @since  1.0.0, 16.10.2017
   void formatNumber( std::string& dest, const Part& part_def,
                      int logfile_nbr) const;

}; // Builder


} // namespace filename
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILENAME_BUILDER_HPP


// =====  END OF builder.hpp  =====

