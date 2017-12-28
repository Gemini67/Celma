
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
/// See documentation of template celma::log::detail::discard_by_level.


#ifndef CELMA_LOG_DETAIL_HELPER_FUNCTION_HPP
#define CELMA_LOG_DETAIL_HELPER_FUNCTION_HPP


#include <string>
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/logging.hpp"


namespace celma { namespace log { namespace detail {


/// Provides a fast check for the macro \c LOG_LEVEL, if a log messages with a
/// specific level will be logged or not.
/// @param[in]  log_spec  Either a single log id or the symbolic name of a log.
/// @param[in]  ll        The log level to check.
/// @return  \c true if the log message will be discarded.
/// @since  0.3, 19.06.2016
template< typename T> bool discard_by_level( const T& log_spec, LogLevel ll)
{
   const auto  my_log = Logging::instance().getLog( log_spec);
   return (my_log == nullptr) || !my_log->processLevel( ll);
} // end discard_by_level


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_HELPER_FUNCTION_HPP


// =======================  END OF helper_function.hpp  =======================

