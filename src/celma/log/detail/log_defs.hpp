
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
/// See documentation of enums celma::log::detail::LogClass and celma::log::detail::LogLevel.


#ifndef CELMA_LOG_DETAIL_LOG_DEFS_HPP
#define CELMA_LOG_DETAIL_LOG_DEFS_HPP


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ostream>


namespace celma { namespace log {


/// Type of log ids.
typedef unsigned  id_t;


/// List of classes to which a log message can belong:
enum class LogClass
{
   undefined,       //!< Undefined.
   sysCall,         //!< Operating system call.
   data,            //!< Data handling.
   communication,   //!< Communication.
   application,     //!< General application.
   accounting,      //!< Accounting messages (Audit: login, logout).
   operatorAction   //!< Action caused by manual intervention of operator.
}; // LogClass


/// List of possible log levels of a message:
enum LogLevel
{
   llUndefined,   //!< Undefined.
   llFatal,       //!< Fatal error.
   llError,       //!< Recoverable error.
   llWarning,     //!< Warning.
   llInfo,        //!< Information.
   llDebug,       //!< Debug information.
   llFullDebug    //!< Extended debug information.
}; // LogLevel


namespace detail {


/// Returns the display text for the specified log message class.
/// @param[in]  lc  The log class to return the text for.
/// @return  The display text for the specified log class.
/// @since  0.3, 19.06.2016
inline const char* logClass2text( LogClass lc)
{
   switch (lc)
   {
   case LogClass::sysCall:         return "SysCall";
   case LogClass::data:            return "Data";
   case LogClass::communication:   return "Communication";
   case LogClass::application:     return "Application";
   case LogClass::accounting:      return "Accounting";
   case LogClass::operatorAction:  return "Operator Action";
   default:
   case LogClass::undefined:       return "undefined";
   } // end switch
} // end logClass2text


/// Returns the display text for the specified log message level.
/// @param[in]  ll  The log level to return the text for.
/// @return  The display text for the specified log level.
/// @since  0.3, 19.06.2016
inline const char* logLevel2text( LogLevel ll)
{
   switch (ll)
   {
   case llFatal:      return "Fatal Error";
   case llError:      return "Error";
   case llWarning:    return "Warning";
   case llInfo:       return "Info";
   case llDebug:      return "Debug";
   case llFullDebug:  return "Full Debug";
   default:
   case llUndefined:  return "undefined";
   } // end switch
} // end logLevel2text


/// Returns the log message class for the specified display class text.
/// @param[in]  lcText  The display text to return the class for.
/// @return  The log class.
/// @since  0.3, 19.06.2016
inline LogClass text2logClass( const char* lcText)
{

   for (int i = 0; i <= static_cast< int>( LogClass::operatorAction); i++)
   {
      if (::strcasecmp( logClass2text( static_cast< LogClass>( i)), lcText) == 0)
         return static_cast< LogClass>( i);
   } // end for

   return static_cast< LogClass>( -1);
} // end text2logClass


/// Returns the log message level for the specified display log text.
/// @param[in]  llText  The display text to return the level for.
/// @return  The log level.
/// @since  0.3, 19.06.2016
inline LogLevel text2logLevel( const char* llText)
{

   for (int  i = 0; i <= static_cast< int>( llFullDebug); i++)
   {
      if (::strcasecmp( logLevel2text( static_cast< LogLevel>( i)), llText) == 0)
         return static_cast< LogLevel>( i);
   } // end for

   return static_cast< LogLevel>( -1);
} // end text2logLevel


} // namespace detail


/// Insertion operator for the values of the enum log level.
/// @param[in]  os  The stream to insert into.
/// @param[in]  ll  The log level.
/// @return  The stream as passed in.
/// @since  0.3, 19.06.2016
inline std::ostream& operator <<( std::ostream& os, const LogLevel ll)
{
   return os << detail::logLevel2text( ll) << " (" << static_cast< int>( ll) << ")";
} // end operator <<


/// Insertion operator for the values of the enum log class.
/// @param[in]  os  The stream to insert into.
/// @param[in]  lc  The log class.
/// @return  The stream as passed in.
/// @since  0.3, 19.06.2016
inline std::ostream& operator <<( std::ostream& os, const LogClass lc)
{
   return os << detail::logClass2text( lc) << " (" << static_cast< int>( lc) << ")";
} // end operator <<


} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_DEFS_HPP


// ===========================  END OF log_defs.hpp  ===========================

