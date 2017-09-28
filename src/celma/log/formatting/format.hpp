
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::formatting::Format.


#ifndef CELMA_LOG_FORMATTING_FORMAT_HPP
#define CELMA_LOG_FORMATTING_FORMAT_HPP


#include <iosfwd>
#include <string>
#include "celma/log/formatting/definition.hpp"
#include "celma/log/detail/i_format_stream.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace formatting {


/// Formats a log message for output.
/// @since  x.y.z, 07.12.2016
class Format: public detail::IFormatStream, private Definition
{
public:
   /// Constructor.
   /// @param[in]  def  The object with the format definition.
   /// @since  x.y.z, 07.12.2016
   Format( const Definition& def);

   /// Formats the data of the log messagr object according to the format
   /// definition passed into the constructor.
   /// @param[in]  dest  The destination stream to write the formatted log
   ///                   message data into.
   /// @param[in]  msg   The log message whose data should be formatted.
   /// @since  x.y.z, 07.12.2016
   virtual void format( std::ostream& dest,
                        const detail::LogMsg& msg) const override;

private:
   /// Formats a date, time or timestamp.
   /// @param[in]  dest        The stream to write into.
   /// @param[in]  field_def   The object with may contain the custom format
   ///                         string.
   /// @param[in]  format_str  The default format string, used when no custom
   ///                         format string is available.
   /// @param[in]  timestamp   The timestamp to format.
   /// @since  x.y.z, 11.12.2016
   void formatDateTime( std::ostream& dest, const Field& field_def,
                        const char* format_str, time_t timestamp) const;

   /// Write a field into the output stream, including width and alignment
   /// settings.
   /// @param[in]  dest  The destination stream to write into.
   /// @param[in]  def   The object with the width and alignment settings.
   /// @param[in]  str   The string to write.
   /// @since  x.y.z, 07.12.2016
   void append( std::ostream& dest, const Field& def, const std::string& str) const;

}; // Format


} // namespace formatting
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FORMATTING_FORMAT_HPP


// ============================  END OF format.hpp  ============================

