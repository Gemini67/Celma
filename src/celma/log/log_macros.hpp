
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
/// See documentation of macros GET_LOG, LOG, LOG_LEVEL and LOG_PRINTF.


#ifndef CELMA_LOG_MACROS_HPP
#define CELMA_LOG_MACROS_HPP


#include "celma/log/detail/helper_function.hpp"
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/detail/log_printf.hpp"
#include "celma/log/detail/stream_log.hpp"
#include "celma/log/logging.hpp"


/// Shortcut to get access to a log object.
/// @param  a  The name or id of a previously created log object.
#define  GET_LOG( a) \
   celma::log::Logging::instance().getLog( a)


/// Macro to prepare the build of a log message. Sets the values that are taken
/// from other macros, compiler values etc.
/// @param  a  The id(s) of the log(s) to send the message to.<br>
///            May be a single log id, a set of log ids or the symbolic name of
///            a log.
#define  LOG( a) \
   celma::log::detail::StreamLog( a, LOG_MSG_OBJECT_INIT).self()


/// Macro that checks if a log message will be processed depending on its
/// level.<br>
/// Use this macro to prevent costly creation of log messages that would be
/// discarded afterwards.<br>
/// This can only be used with a single log id/name, not with a set of log ids.
/// @param  a  The single log id or name of the log to send the message to.
/// @param  l  The log level of the message, is already set on the log message
///            too.
#define  LOG_LEVEL( a, l) \
   if (celma::log::detail::discard_by_level( a, celma::log::LogLevel::l)) \
   { } \
   else \
      celma::log::detail::StreamLog( a, LOG_MSG_OBJECT_INIT).self() \
                                                    << celma::log::LogLevel::l


/// Macro to create a log message using a printf()-like format string with the
/// additional values as parameters.
/// @param  i  The id(s) of the log(s) to send the message to.<br>
///            May be a single log id, a set of log ids or the symbolic name of
///            a log.
/// @param  l  The level of the log message.
/// @param  c  The class of the log message.
/// @param  f  The printf()-like format string.
/// @param     Optional additional parameters.
#define  LOG_PRINTF( i, l, c, f, ...) \
   celma::log::detail::printf( LOG_MSG_OBJECT_INIT, i, \
                               celma::log::LogLevel::l, \
                               celma::log::LogClass::c, f, ## __VA_ARGS__)


#endif   // CELMA_LOG_MACROS_HPP


// ==========================  END OF log_macros.hpp  ==========================

