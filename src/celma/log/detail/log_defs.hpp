
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
/// See documentation of enums celma::log::detail::LogClass and
/// celma::log::detail::LogLevel.


#pragma once


// OS/C lib includes
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ostream>


namespace celma::log {


/// Type of log ids.
using id_t = unsigned int;


/// List of classes to which a log message can belong:
enum class LogClass : uint8_t
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
enum class LogLevel : uint8_t
{
   undefined,   //!< Undefined.
   fatal,       //!< Fatal error.
   error,       //!< Recoverable error.
   warning,     //!< Warning.
   info,        //!< Information.
   debug,       //!< Debug information.
   fullDebug    //!< Extended debug information.
}; // LogLevel


namespace detail {


/// Returns the display text for the specified log message class.
/// @param[in]  lc  The log class to return the text for.
/// @return  The display text for the specified log class.
/// @since  1.0.0, 19.06.2016
[[nodiscard]] inline const char* logClass2text( const LogClass lc)
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
} // logClass2text


/// Returns the display text for the specified log message level.
/// @param[in]  ll  The log level to return the text for.
/// @return  The display text for the specified log level.
/// @since  1.0.0, 19.06.2016
[[nodiscard]] inline const char* logLevel2text( const LogLevel ll)
{
   switch (ll)
   {
   case LogLevel::fatal:      return "Fatal Error";
   case LogLevel::error:      return "Error";
   case LogLevel::warning:    return "Warning";
   case LogLevel::info:       return "Info";
   case LogLevel::debug:      return "Debug";
   case LogLevel::fullDebug:  return "Full Debug";
   default:
   case LogLevel::undefined:  return "undefined";
   } // end switch
} // logLevel2text


/// Returns the log message class for the specified display class text.
/// @param[in]  lcText  The display text to return the class for.
/// @return  The log class.
/// @since  1.0.0, 19.06.2016
[[nodiscard]] inline LogClass text2logClass( const char* lcText)
{

   for (int i = 0; i <= static_cast< int>( LogClass::operatorAction); i++)
   {
      if (::strcasecmp( logClass2text( static_cast< LogClass>( i)), lcText) == 0)
         return static_cast< LogClass>( i);
   } // end for

   return LogClass::undefined;
} // text2logClass


/// Returns the log message level for the specified display log text.
/// @param[in]  llText  The display text to return the level for.
/// @return  The log level.
/// @since  1.0.0, 19.06.2016
[[nodiscard]] inline LogLevel text2logLevel( const char* llText)
{

   for (int  i = 0; i <= static_cast< int>( LogLevel::fullDebug); i++)
   {
      if (::strcasecmp( logLevel2text( static_cast< LogLevel>( i)), llText) == 0)
         return static_cast< LogLevel>( i);
   } // end for

   return LogLevel::undefined;
} // text2logLevel


} // namespace detail


/// Insertion operator for the values of the enum log level.
/// @param[in]  os  The stream to insert into.
/// @param[in]  ll  The log level.
/// @return  The stream as passed in.
/// @since  1.0.0, 19.06.2016
inline std::ostream& operator <<( std::ostream& os, const LogLevel ll)
{
   return os << detail::logLevel2text( ll) << " (" << static_cast< int>( ll)
             << ")";
} // operator <<


/// Insertion operator for the values of the enum log class.
/// @param[in]  os  The stream to insert into.
/// @param[in]  lc  The log class.
/// @return  The stream as passed in.
/// @since  1.0.0, 19.06.2016
inline std::ostream& operator <<( std::ostream& os, const LogClass lc)
{
   return os << detail::logClass2text( lc) << " (" << static_cast< int>( lc)
             << ")";
} // operator <<


} // namespace celma::log


// =====  END OF log_defs.hpp  =====

