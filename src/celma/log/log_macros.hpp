
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of macros GET_LOG, LOG, LOG_LEVEL, LOG_PRINTF,
/// LOG_LEVEL_ONCE, LOG_LEVEL_MAX, LOG_LEVEL_AFTER, LOG_LEVEL_EVERY and
/// LOG_ATTRIBUTE.


#ifndef CELMA_LOG_MACROS_HPP
#define CELMA_LOG_MACROS_HPP


#include "boost/preprocessor/cat.hpp"
#include "celma/log/detail/helper_function.hpp"
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/detail/log_printf.hpp"
#include "celma/log/detail/log_scoped_attribute.hpp"
#include "celma/log/detail/stream_log.hpp"
#include "celma/log/log_attributes.hpp"
#include "celma/log/logging.hpp"


/// Shortcut to get access to a log object.
///
/// @param  a  The name or id of a previously created log object.
#define  GET_LOG( a) \
   celma::log::Logging::instance().getLog( a)


/// Macro to prepare the build of a log message. Sets the values that are taken
/// from other macros, compiler values etc.
///
/// @param  a  The id(s) of the log(s) to send the message to.<br>
///            May be a single log id, a set of log ids or the symbolic name of
///            a log.
#define  LOG( a) \
   celma::log::detail::StreamLog( a, LOG_MSG_OBJECT_INIT).self()


/// Macro to prepare the build of a log message with additional log attributes.
/// Sets the values that are taken from other macros, compiler values etc.
///
/// @param  ids
///    The id(s) of the log(s) to send the message to.<br>
///    May be a single log id, a set of log ids or the symbolic name of a log.
/// @param  attr
///    The log attributes object to use for gettings the values of additional
///    log attributes.
#define  LOG_ATTR( ids, attr) \
   celma::log::detail::StreamLog( ids, LOG_MSG_OBJECT_INIT).self() << attr


/// Macro that checks if a log message will be processed depending on its
/// level.<br>
/// Use this macro to prevent costly creation of log messages that would be
/// discarded afterwards.<br>
/// This can only be used with a single log id/name, not with a set of log ids.
///
/// @param  a  The single log id or name of the log to send the message to.
/// @param  l  The log level of the message, is already set on the log message
///            too.
#define  LOG_LEVEL( a, l) \
   if (celma::log::detail::discard_by_level( a, celma::log::LogLevel::l)) \
   { } \
   else \
      celma::log::detail::StreamLog( a, LOG_MSG_OBJECT_INIT).self() \
         << celma::log::LogLevel::l


/// Macro that checks if a log message will be processed depending on its
/// level.<br>
/// Use this macro to prevent costly creation of log messages that would be
/// discarded afterwards.<br>
/// This can only be used with a single log id/name, not with a set of log
/// ids.<br>
/// This macro also allows to specify a log attribute object that will be used
/// to get the values for log attributes.
///
/// @param  ids
///    The single log id or name of the log to send the message to.
/// @param  lvl
///    The log level of the message, is already set on the log message too.
/// @param  attr
///    The log attributes object to use for gettings the values of additional
///    log attributes.
#define  LOG_LEVEL_ATTR( ids, lvl, attr) \
   if (celma::log::detail::discard_by_level( ids, celma::log::LogLevel::lvl)) \
   { } \
   else \
      celma::log::detail::StreamLog( ids, LOG_MSG_OBJECT_INIT).self() \
         << celma::log::LogLevel::lvl << attr


/// Macro to create a log message using a printf()-like format string with the
/// additional values as parameters.
///
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



/// Macro that creates a specific log message at most once.<br>
/// It also checks if a log message will be processed depending on its
/// level.<br>
/// Use this macro to prevent costly creation of log messages that would be
/// discarded afterwards.<br>
/// This can only be used with a single log id/name, not with a set of log ids.
///
/// @param  a  The single log id or name of the log to send the message to.
/// @param  l  The log level of the message, is already set on the log message
///            too.
#define  LOG_LEVEL_ONCE( a, l) \
   static bool  BOOST_PP_CAT( logged, __LINE__)= false; \
   if (BOOST_PP_CAT( logged, __LINE__)) \
   { } \
   else if (celma::log::detail::discard_by_level( a, celma::log::LogLevel::l)) \
   { } \
   else \
      BOOST_PP_CAT( logged, __LINE__) = true, \
      celma::log::detail::StreamLog( a, LOG_MSG_OBJECT_INIT).self() \
         << celma::log::LogLevel::l


/// Macro that creates a specific log message at most once.<br>
/// It also checks if a log message will be processed depending on its
/// level.<br>
/// Use this macro to prevent costly creation of log messages that would be
/// discarded afterwards.<br>
/// This can only be used with a single log id/name, not with a set of log ids.
///
/// @param  a  The single log id or name of the log to send the message to.
/// @param  l  The log level of the message, is already set on the log message
///            too.
/// @param  m  The maximum number of times to write this message.
#define  LOG_LEVEL_MAX( a, l, m) \
   static int  BOOST_PP_CAT( log_counter, __LINE__) = 0; \
   if (BOOST_PP_CAT( log_counter, __LINE__)++ >= m) \
   { \
      --BOOST_PP_CAT( log_counter, __LINE__); \
   } else if (celma::log::detail::discard_by_level( a, celma::log::LogLevel::l)) \
   { } \
   else \
      celma::log::detail::StreamLog( a, LOG_MSG_OBJECT_INIT).self() \
         << celma::log::LogLevel::l


/// Macro that creates a specific log message only when the call point has been
/// past at least a given minimum number of times.<br>
/// It also checks if a log message will be processed depending on its
/// level.<br>
/// Use this macro to prevent costly creation of log messages that would be
/// discarded afterwards.<br>
/// This can only be used with a single log id/name, not with a set of log ids.
///
/// @param  a  The single log id or name of the log to send the message to.
/// @param  l  The log level of the message, is already set on the log message
///            too.
/// @param  m  The minimum number of times that the call point must have been
///            passed until the log message is actually created.
#define  LOG_LEVEL_AFTER( a, l, m) \
   static int  BOOST_PP_CAT( log_counter, __LINE__) = 0; \
   if (BOOST_PP_CAT( log_counter, __LINE__)++ < m) \
   { } \
   else if (celma::log::detail::discard_by_level( a, celma::log::LogLevel::l)) \
   { } \
   else \
      --BOOST_PP_CAT( log_counter, __LINE__), \
      celma::log::detail::StreamLog( a, LOG_MSG_OBJECT_INIT).self() \
         << celma::log::LogLevel::l


/// Macro that creates a specific log message only every nth time when the call
/// point has been past.<br>
/// It also checks if a log message will be processed depending on its
/// level.<br>
/// Use this macro to prevent costly creation of log messages that would be
/// discarded afterwards.<br>
/// This can only be used with a single log id/name, not with a set of log ids.
///
/// @param  a  The single log id or name of the log to send the message to.
/// @param  l  The log level of the message, is already set on the log message
///            too.
/// @param  n  The nth number of times that the call point must have been
///            passed for the log message to be actually created.
#define  LOG_LEVEL_EVERY( a, l, n) \
   static int  BOOST_PP_CAT( log_counter, __LINE__) = 0; \
   if ((++BOOST_PP_CAT( log_counter, __LINE__)) % n != 0) \
   { } \
   else if (celma::log::detail::discard_by_level( a, celma::log::LogLevel::l)) \
   { } \
   else \
      BOOST_PP_CAT( log_counter, __LINE__) = 0, \
      celma::log::detail::StreamLog( a, LOG_MSG_OBJECT_INIT).self() \
         << celma::log::LogLevel::l


/// Macro to create a scoped log attribute with a unique name.<br>
/// The log attribute is accessible while the object exists.
///
/// @param  n  The name of the attribute.
/// @param  v  The value to use for the attribute.
#define  LOG_ATTRIBUTE( n, v) \
   celma::log::detail::ScopedAttribute  BOOST_PP_CAT( sa, __LINE__) ( n, v)


#endif   // CELMA_LOG_MACROS_HPP


// =====  END OF log_macros.hpp  =====

