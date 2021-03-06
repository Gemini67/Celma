
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::Logging.


#pragma once


#include <iosfwd>
#include <vector>
#include "celma/common/singleton.hpp"
#include "celma/log/detail/log_attributes_container.hpp"
#include "celma/log/detail/log_data.hpp"
#include "celma/log/detail/log_defs.hpp"


namespace celma::log {


namespace detail {

class Log;
class LogMsg;

} // namespace detail


/// Logging framework.
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
/// can be specified, which messages should be passed to this destination.<br>
/// The most convenient way to create a log message is by using one of the
/// provided macros.<br>
/// For each log destination a specific output format can be specified. There
/// are predefined columns like the date, time, process id etc. that you can
/// use, plus the text of the log message of course.<br>
/// You can store values that are added to each log message, either in a
/// separate column or in the text of the log message, the log attributes.<br>
/// There are several ways to define a log attribute, related to the scope of an
/// attribute:
/// - Global:<br>
///   You can add attributes to the singleton object of this class, resulting in
///   an attribute that is visible "everywhere".
/// - Scoped:<br>
///   With the macro \c LOG_ATTRIBUTE a scoped attribute is created, that is
///   visible as long as the scope of the internally used variable exists.<br>
///   This includes functions called from within the scope etc.
/// - Variable:<br>
///   With the class celma::log::LogAttributes you can manage the scope of
///   attributes yourself. For example, use an object of this class as a member
///   variable of your class to define class-specific attributes.<br>
///   You just have to pass the log attribute object to the log message
///   afterwards. See the description of the class.
/// You can always define multiple attributes with the same name (and, most
/// likely, different values). When searching for the value of an attribute, the
/// value of the attribute that was added last is used.
///
/// @since  0.3, 19.06.2016
class Logging final : public common::Singleton< Logging>
{
public:
   friend class common::Singleton< Logging>;

   /// Empty, virtual default destructor.
   ~Logging() override = default;

   /// Checks if there already exists a log with the specified name. If not, a
   /// new log is created.
   ///
   /// @param[in]  name  The name of the log to search for.
   /// @return  The id of the already existing or newly created log.
   /// @throw
   ///    celma::common::CelmaRuntimeError if the maximum number of logs is
   ///    reached.
   /// @since  0.3, 19.06.2016
   id_t findCreateLog( const std::string& name) noexcept( false);

   /// Returns the log with the specified id.
   ///
   /// @param[in]  log_id  The id of the log.
   /// @return  Pointer to the internal log object, NULL if not found.
   /// @throw
   ///    celma::common::CelmaRuntimeError if \a log_id contains more than one
   ///    log id.
   /// @since  0.3, 19.06.2016
   detail::Log* getLog( id_t log_id) noexcept( false);

   /// Returns the log with the specified name.
   ///
   /// @param[in]  log_name  The name of the log.
   /// @return  Pointer to the internal log object, NULL if not found.
   /// @since  0.3, 19.06.2016
   detail::Log* getLog( const std::string& log_name);

   /// Sends a log message to the specified log(s).
   ///
   /// @param[in]  logs
   ///    The set of log id(s) to pass the message.
   /// @param[in]  msg
   ///    The message to handle.
   /// @since  0.3, 19.06.2016
   void log( id_t logs, const detail::LogMsg& msg);

   /// Sends a log message to the specified log.
   ///
   /// @param[in]  log_name
   ///    The name of the log to pass the message.
   /// @param[in]  msg
   ///    The message to handle.
   /// @since  0.3, 19.06.2016
   void log( const std::string& log_name, const detail::LogMsg& msg);

   /// Add an attribute which is later used for log messages.
   ///
   /// @param[in]  name
   ///    The name of the attribute.
   /// @param[in]  value
   ///    The value for the attribute.
   /// @since
   ///    1.15.0, 10.10.2018
   void addAttribute( const std::string& name, const std::string& value);

   /// Returns the value for an attribute.
   /// If multiple attributes with the same name exist, the values of the last
   /// attribute is returned (i.e. the one that was added last).
   ///
   /// @param[in]  attr_name  The name of the attribute to return the value of.
   /// @return
   ///    The (last) value of the attribute or an empty string when not found.
   /// @since
   ///    1.15.0, 11.10.2018
   std::string getAttribute( const std::string& attr_name) const;

   /// Removes an attribute.
   /// If multiple attributes with the same name exist, the attribute that was
   /// added last is removed.
   /// 
   /// @param[in]  attr_name  The name of the attribute to remove.
   /// @since  1.15.0, 11.10.2018
   void removeAttribute( const std::string& attr_name);

   /// Dumps information about the logging framework.
   ///
   /// @param[in]  os
   ///    The stream to write into.
   /// @param[in]  lg
   ///    The object to dump.
   /// @return  The stream as passed in.
   /// @since  0.3, 19.06.2016
   friend std::ostream& operator <<( std::ostream& os, const Logging& lg);

protected:
   /// Constructor.
   ///
   /// @since  0.3, 19.06.2016
   Logging() = default;

private:
   /// Container for the log object(s).
   using LogCont = std::vector< detail::LogData>;

   /// The id to give to the next log.
   id_t                            mNextLogId = 0x01;
   /// The data of the existing log(s).
   LogCont                         mLogs;
   /// Store for the current log attributes.
   detail::LogAttributesContainer  mAttributes;

}; // Logging


// inlined methods
// ===============


inline std::string Logging::getAttribute( const std::string& attr_name) const
{
   return mAttributes.getAttribute( attr_name);
} // Logging::getAtribute


} // namespace celma::log


/// @example
/// Complete example how to set up a log called 'trace' that writes to stdout.
///
/// <pre>
/// const int  trace_log = Logging::instance().findCreateLog( "trace");
/// Logging::instance().getLog( trace_log)->addDestination( "stream", new LogDestStream( cout));
/// LOG( trace_log) << "log trace message written to stdout";
/// </pre>


// =====  END OF logging.hpp  =====

