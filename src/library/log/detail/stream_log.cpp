
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
/// See documentation of class celma::log::detail::StreamLog.


// module header file include
#include "celma/log/detail/stream_log.hpp"


// project includes
#include "celma/log/logging.hpp"


namespace celma { namespace log { namespace detail {



/// Constructor for using log id(s).
///
/// @param[in]  log_ids
///    Set of log ids to send the resulting log message to.
/// @param[in]  filename
///    The name of the file in which the log message was created.<br>
///    Intentionally not passed by reference: We need a copy to cut the path
///    off ..
/// @param[in]  function_name
///    The name of the function in which the log message was generated.
/// @param[in]  line_nbr
///     The line number from which the log message originated.
/// @since  1.0.0, 19.06.2016
StreamLog::StreamLog( id_t log_ids, const std::string filename,
                      const char* const function_name, int line_nbr) noexcept( false):
   mLogIds( log_ids),
   mLogName(),
   mStrStream(),
   mLogMsg( filename, function_name, line_nbr)
{

   if (mLogIds == 0)
      throw CELMA_RuntimeError( "no destination log id specified");

} // StreamLog::StreamLog



/// Constructor for using the log name.
///
/// @param[in]  log_name
///    The name of the log to send the resulting log message to.
/// @param[in]  filename
///    The name of the file in which the log message was created.<br>
///    Intentionally not passed by reference: We need a copy to cut the path
///    off ..
/// @param[in]  function_name
///    The name of the function in which the log message was generated.
/// @param[in]  line_nbr
///    The line number from which the log message originated.
/// @since  1.0.0, 19.06.2016
StreamLog::StreamLog( const std::string& log_name, const std::string filename,
                      const char* const function_name, int line_nbr) noexcept( false):
   mLogName( log_name),
   mStrStream(),
   mLogMsg( filename, function_name, line_nbr)
{

   if (mLogName.empty())
      throw CELMA_RuntimeError( "no destination log name specified");

} // StreamLog::StreamLog



/// Destructor. Finally create the requested log message.
///
/// @since  1.0.0, 19.06.2016
StreamLog::~StreamLog()
{
   
   if (mStrStream.str().empty())
      // nothing to do
      return;

   mLogMsg.setText( mStrStream.str());

   if (mLogIds == 0)
      Logging::instance().log( mLogName, mLogMsg);
   else
      Logging::instance().log( mLogIds, mLogMsg);

} // StreamLog::~StreamLog



/// Stores the data of an exception in the log message object.<br>
/// The text of the exception is assigned to the internal stringstream in
/// order to keep the feature that log messages without text are discarded.
///
/// @param[in]  eb  The exception to log.
/// @since  1.0.0, 19.06.2016
void StreamLog::storeException( const common::ExceptionBase& eb)
{

   if (mLogMsg.getLevel() == LogLevel::undefined)
      mLogMsg.setLevel( LogLevel::error);
   if (mLogMsg.getClass() == LogClass::undefined)
      mLogMsg.setClass( LogClass::sysCall);

   mLogMsg.assign( eb);
   mStrStream << eb.text();

} // StreamLog::storeException



/// Adds the value of the given attribute to the log message text.
///
/// @param[in]  attr_name  The name of the attribute to add the value of.
/// @since  1.15.0, 12.10.2018
void StreamLog::addAttribute( const std::string& attr_name)
{

   auto  attr_value = mLogMsg.getAttributeValue( attr_name);


   if (attr_value.empty())
      attr_value = Logging::instance().getAttribute( attr_name);

   mStrStream << attr_value;

} // StreamLog::addAttribute



/// Stores (the pointer to) an additional attributes container in the log
/// message. The values for the attributes can be used in the log format or
/// in the log message text and take precedence over the attributes stored in
/// the global log object.
///
/// @param[in]  attr_cont  The container with the attributes.
/// @since  1.15.0, 17.10.2018
void StreamLog::setAttributes( const LogAttributes& attr_cont)
{

   mLogMsg.setAttributes( attr_cont);

} // StreamLog::setAttributes



} // namespace detail
} // namespace log
} // namespace celma


// =====  END OF stream_log.cpp  =====

