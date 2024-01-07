
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
/// See documentation of template celma::log::detail::discard_by_level.


#pragma once


#include <string>
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/logging.hpp"


namespace celma::log::detail {


/// Provides a fast check for the macro \c LOG_LEVEL, if a log messages with a
/// specific level will be logged or not.
/// @param[in]  log_spec  Either a single log id or the symbolic name of a log.
/// @param[in]  ll        The log level to check.
/// @return  \c true if the log message will be discarded.
/// @since  0.3, 19.06.2016
template< typename T> [[nodiscard]]
   bool discard_by_level( const T& log_spec, const LogLevel ll)
{
   const auto  my_log = Logging::instance().getLog( log_spec);
   return (my_log == nullptr) || !my_log->processLevel( ll);
} // discard_by_level


} // namespace celma:log::detail


// =====  END OF helper_function.hpp  =====

