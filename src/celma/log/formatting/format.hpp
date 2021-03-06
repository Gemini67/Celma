
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::formatting::Format.


#pragma once


#include <iosfwd>
#include <string>
#include "celma/log/formatting/definition.hpp"
#include "celma/log/detail/i_format_stream.hpp"


namespace celma::log {

namespace detail {
class LogMsg;
} // namespace detail

namespace formatting {


/// Formats a log message for output, using the given Destination object to
/// format the fields.
///
/// @since  1.0.0, 07.12.2016
class Format final : public detail::IFormatStream, private Definition
{
public:
   /// Constructor.
   ///
   /// @param[in]  def  The object with the format definition.
   /// @since  1.0.0, 07.12.2016
   explicit Format( const Definition& def);

   /// Default destructor is fine.
   ///
   /// @since  1.41.1, 15.07.2020
   ~Format() override = default;

   /// Formats the data of the log messagr object according to the format
   /// definition passed into the constructor.
   ///
   /// @param[out]  dest
   ///    The destination stream to write the formatted log message data into.
   /// @param[in]   msg
   ///    The log message whose data should be formatted.
   /// @since  1.0.0, 07.12.2016
   virtual void format( std::ostream& dest,
                        const detail::LogMsg& msg) const override;

private:
   /// Formats a date, time or timestamp.
   ///
   /// @param[out]  dest
   ///    The stream to write into.
   /// @param[in]   field_def
   ///    The object with may contain the custom format string.
   /// @param[in]   format_str
   ///    The default format string, used when no custom format string is
   ///    available.
   /// @param[in]   timestamp
   ///    The timestamp to format.
   /// @since  1.0.0, 11.12.2016
   void formatDateTime( std::ostream& dest, const Field& field_def,
                        const char* format_str, time_t timestamp) const;

   /// Write a field into the output stream, including width and alignment
   /// settings.
   ///
   /// @param[out]  dest
   ///    The destination stream to write into.
   /// @param[in]   def
   ///    The object with the width and alignment settings.
   /// @param[in]   str
   ///    The string to write.
   /// @since  1.0.0, 07.12.2016
   void append( std::ostream& dest, const Field& def, const std::string& str) const;

}; // Format


} // namespace formatting
} // namespace celma::log


// =====  END OF format.hpp  =====

