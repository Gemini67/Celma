
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
/// See documentation of class celma::log::Logging.


#ifndef CELMA_LOG_LOGGING_HPP
#define CELMA_LOG_LOGGING_HPP


#include <iosfwd>
#include <vector>
#include "celma/common/singleton.hpp"
#include "celma/log/detail/log_data.hpp"
#include "celma/log/detail/log_defs.hpp"


namespace celma { namespace log {


namespace detail {

class Log;
class LogMsg;

} // namespace detail


/// Logging framework.<br>
/// There is only one Logging object within a process. This singleton object is
/// the interface to use for logging.<br>
/// There can be several logs, e.g. one for operational messages, one for
/// debugging etc. The logs are created with symbolic names, for each log a
/// unique identifier is created which must be used afterwards to pass
/// messages to this log.<br>
/// The name can also be used afterwards, but using the log ids allows to
/// create log messages that are sent to multiple logs (by or-ing the
/// log-ids).<br>
/// Each of these logs can have zero or multiple destinations. This can be e.g.
/// a file writer, a communication interface etc. For each destination, filters
/// can be specified, which messages should be passed to this destination.
/// @since  0.3, 19.06.2016
class Logging: public common::Singleton< Logging>
{
public:
   friend class common::Singleton< Logging>;

   /// Checks if there already exists a log with the specified name. If not, a
   /// new log is created.
   /// @param[in]  name  The name of the log to search for.
   /// @return  The id of the already existing or newly created log.
   /// @since  0.3, 19.06.2016
   id_t findCreateLog( const std::string& name) noexcept( false);

   /// Returns the log with the specified id.
   /// @param[in]  log_id  The id of the log.
   /// @return  Pointer to the internal log object, NULL if not found.
   /// @throw  CelmaRuntimeError if \a log_id contains more than one log id.
   /// @since  0.3, 19.06.2016
   detail::Log* getLog( id_t log_id) noexcept( false);

   /// Returns the log with the specified name.
   /// @param[in]  log_name  The name of the log.
   /// @return  Pointer to the internal log object, NULL if not found.
   /// @since  0.3, 19.06.2016
   detail::Log* getLog( const std::string& log_name);

   /// Sends a log message to the specified log(s).
   /// @param[in]  logs  The set of log id(s) to pass the message.
   /// @param[in]  msg   The message to handle.
   /// @since  0.3, 19.06.2016
   void log( id_t logs, const detail::LogMsg& msg);

   /// Sends a log message to the specified log.
   /// @param[in]  log_name  The name of the log to pass the message.
   /// @param[in]  msg       The message to handle.
   /// @since  0.3, 19.06.2016
   void log( const std::string& log_name, const detail::LogMsg& msg);

   /// Dumps information about the logging framework.
   /// @param[in]  os  The stream to write into.
   /// @param[in]  lg  The object to dump.
   /// @return  The stream as passed in.
   /// @since  0.3, 19.06.2016
   friend std::ostream& operator <<( std::ostream& os, const Logging& lg);

protected:
   /// Constructor.
   /// @since  0.3, 19.06.2016
   Logging();

private:
   /// Container for the log object(s).
   typedef std::vector< detail::LogData>  LogCont;

   /// The id to give to the next log.
   id_t     mNextLogId;
   /// The data of the existing log(s).
   LogCont  mLogs;

}; // Logging


} // namespace log
} // namespace celma


/// @example
/// Complete example how to set up a log called 'trace' that writes to stdout.
///
/// <pre>
/// const int  trace_log = Logging::instance().findCreateLog( "trace");
/// Logging::instance().getLog( trace_log)->addDestination( "stream", new LogDestStream( cout));
/// LOG( trace_log) << "log trace message written to stdout";
/// </pre>


#endif   // CELMA_LOG_LOGGING_HPP


// ===========================  END OF logging.hpp  ===========================
