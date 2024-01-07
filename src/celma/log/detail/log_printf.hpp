
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of functions celma::log::detail::printf().


#pragma once


#include <cstdarg>
#include <string>
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/logging.hpp"


namespace celma::log::detail {


void log_vprintf( LogMsg& myMsg, LogLevel ll, LogClass lc,
                  const char* format, va_list ap) noexcept( false);


/// Template function to create a log message with a printf()-like syntax.<br>
/// Use the macro \c LOG_PRINTF to call this function more easily.
///
/// @param[in]  file_name
///    The name of the source file.
/// @param[in]  function_name
///    The name of the calling function.
/// @param[in]  line_nbr
///    The line number where the log message was created.
/// @param[in]  log_spec
///    Either the single log id or the name of the log.
/// @param[in]  ll
///    The log level.
/// @param[in]  lc
///    The log class.
/// @param[in]  format
///    The format string for the log message text.
/// @param[in]  ...
///    Additional parameters.
/// @since  0.3, 19.06.2016
template< typename T>
   void printf( const std::string& file_name, const char* const function_name,
                const int line_nbr, const T& log_spec, const LogLevel ll,
                const LogClass lc, const char* format, ...) noexcept( false)
{

   LogMsg  myMsg( file_name, function_name, line_nbr);
   va_list  ap;

   ::va_start( ap, format);
   log_vprintf( myMsg, ll, lc, format, ap);
   ::va_end( ap);

   Logging::instance().log( log_spec, myMsg);

} // printf


} // namespace celma::log::detail


// =====  END OF log_printf.hpp  =====

