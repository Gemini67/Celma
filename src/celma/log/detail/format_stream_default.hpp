
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::FormatStreamDefault.


#ifndef CELMA_LOG_DETAIL_FORMAT_STREAM_DEFAULT_HPP
#define CELMA_LOG_DETAIL_FORMAT_STREAM_DEFAULT_HPP


#include <iosfwd>
#include "i_format_stream.hpp"
#include "log_msg.hpp"


namespace celma { namespace log { namespace detail {


/// Default formatter for stream output.<br>
/// Generates a log entry with the format:
///    <pre>pid|line-nbr|log-class|log-level|error-nbr|text</pre>
/// @since  0.3, 19.06.2016
class FormatStreamDefault: public IFormatStream
{
private:
   /// Implementation of the interface: Generate the log entry.
   /// @param[out]  out  The stream to write the log entry into.
   /// @param[in]   msg  The log message object with the data to log.
   /// @since  0.3, 19.06.2016
   virtual void format( std::ostream& out, const LogMsg& msg) const;

}; // FormatStreamDefault


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_FORMAT_STREAM_DEFAULT_HPP


// ====================  END OF format_stream_default.hpp  ====================

