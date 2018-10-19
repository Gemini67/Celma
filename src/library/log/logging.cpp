
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
/// See documentation of class celma::log::Logging.


// module header file include
#include "celma/log/logging.hpp"


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log {



/// Checks if there already exists a log with the specified name. If not, a
/// new log is created.
/// @param[in]  name  The name of the log to search for.
/// @return  The id of the already existing or newly created log.
/// @since  0.3, 19.06.2016
id_t Logging::findCreateLog( const std::string& name)
{

   for (auto const& it : mLogs)
   {
      if (name == it.mName)
         return it.mLogId;
   } // end for

   // log with this name does not exist yet
   auto const  log_id = mNextLogId;

   if (mNextLogId == static_cast< id_t>( (0x1 << 31)))
      throw CELMA_RuntimeError( "maximum number of logs reached");

   mLogs.push_back( detail::LogData( log_id, name, new detail::Log));
   mNextLogId <<= 1;

   return log_id;
} // Logging::findCreateLog



/// Returns the log with the specified id.
/// @param[in]  log_id  The id of the log.
/// @return  Pointer to the internal log object, NULL if not found.
/// @throw  CelmaRuntimeError if \a log_id contains more than one log id.
/// @since  0.3, 19.06.2016
detail::Log* Logging::getLog( id_t log_id)
{

   /// @todo: find_if
   for (auto & it : mLogs)
   {
      if (log_id == it.mLogId)
      {
         if (log_id - it.mLogId != 0)
            throw CELMA_RuntimeError( "only one single log id may be specified");
         return it.mpLog;
      } // end if
   } // end for

   return nullptr;
} // Logging::getLog



/// Returns the log with the specified name.
/// @param[in]  log_name  The name of the log.
/// @return  Pointer to the internal log object, NULL if not found.
/// @since  0.3, 19.06.2016
detail::Log* Logging::getLog( const std::string& log_name)
{

   /// @todo: find_if
   for (auto const& it : mLogs)
   {
      if (log_name == it.mName)
         return it.mpLog;
   } // end for

   return nullptr;
} // Logging::getLog



/// Sends a log message to the specified log(s).
/// @param[in]  logs  The set of log id(s) to pass the message.
/// @param[in]  msg   The message to handle.
/// @since  0.3, 19.06.2016
void Logging::log( id_t logs, const detail::LogMsg& msg)
{

   for (auto & it : mLogs)
   {
      if (logs & it.mLogId)
      {
         it.mpLog->message( msg);

         // if only one log was selected, we're done
         if (logs == it.mLogId)
            break;   // for
      } // end if
   } // end for

} // Logging::log



/// Sends a log message to the specified log.
/// @param[in]  log_name  The name of the log to pass the message.
/// @param[in]  msg       The message to handle.
/// @since  0.3, 19.06.2016
void Logging::log( const std::string& log_name, const detail::LogMsg& msg)
{

   for (auto & it : mLogs)
   {
      if (log_name == it.mName)
      {
         it.mpLog->message( msg);
         break;   // for
      } // end if
   } // end for

} // Logging::log



/// Add an attribute which is later used for log messages.
///
/// @param[in]  name
///    The name of the attribute.
/// @param[in]  value
///    The value for the attribute.
/// @since
///    x.y.z, 10.10.2018
void Logging::addAttribute( const std::string& name, const std::string& value)
{

   mAttributes.addAttribute( name, value);

} // Logging::addAttribute



/// Removes an attribute.<br>
/// If multiple attributes with the same name exist, the attribute that was
/// added last is removed.
/// 
/// @param[in]  attr_name  The name of the attribute to remove.
/// @since  x.y.z, 11.10.2018
void Logging::removeAttribute( const std::string& attr_name)
{

   mAttributes.removeAttribute( attr_name);

} // Logging::removeAttribute



/// Dumps information about the logging framework.
/// @param[in]  os  The stream to write into.
/// @param[in]  lg  The object to dump.
/// @return  The stream as passed in.
/// @since  0.3, 19.06.2016
std::ostream& operator <<( std::ostream& os, const Logging& lg)
{

   os << "next log id: " << std::hex << lg.mNextLogId << std::endl;

   for (auto const& it : lg.mLogs)
   {
      os << it;
   } // end for

   return os;
} // operator <<



} // namespace log
} // namespace celma


// =====  END OF logging.cpp  =====

