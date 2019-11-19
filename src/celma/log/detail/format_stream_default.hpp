
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
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
#include "celma/log/detail/i_format_stream.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace detail {


/// Default formatter for stream output.<br>
/// Generates a log entry with the format:
///    <pre>pid|line-nbr|log-class|log-level|error-nbr|text</pre>
/// @since  1.0.0, 19.06.2016
class FormatStreamDefault: public IFormatStream
{
public:
   // default destructor is fine
   virtual ~FormatStreamDefault() = default;

private:
   /// Implementation of the interface: Generate the log entry.
   /// @param[out]  out  The stream to write the log entry into.
   /// @param[in]   msg  The log message object with the data to log.
   /// @since  1.0.0, 19.06.2016
   void format( std::ostream& out, const LogMsg& msg) const override;

}; // FormatStreamDefault


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_FORMAT_STREAM_DEFAULT_HPP


// =====  END OF format_stream_default.hpp  =====

