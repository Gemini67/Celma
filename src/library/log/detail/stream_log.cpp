
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
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
/// @param[in]  log_ids        Set of log ids to send the resulting log
///                            message to.
/// @param[in]  filename       The name of the file in which the log message
///                            was created.<br>
///                            Intentionally not passed by reference: We need
///                            a copy to cut the path off ..
/// @param[in]  function_name  The name of the function in which the log
///                            message was generated.
/// @param[in]  line_nbr       The line number from which the log message
///                            originated.
/// @since  x.y.z, 19.06.2016
StreamLog::StreamLog( id_t log_ids, const std::string filename,
                      const char* const function_name, int line_nbr) noexcept( false):
   mLogIds( log_ids),
   mLogName(),
   mErrNbrNext( false),
   mStrStream(),
   mPropertyName(),
   mLogMsg( filename, function_name, line_nbr)
{

   if (mLogIds == 0)
      throw CELMA_RuntimeError( "no destination log id specified");

} // StreamLog::StreamLog



/// Constructor for using the log name.
/// @param[in]  log_name       The name of the log to send the resulting log
///                            message to.
/// @param[in]  filename       The name of the file in which the log message
///                            was created.<br>
///                            Intentionally not passed by reference: We need
///                            a copy to cut the path off ..
/// @param[in]  function_name  The name of the function in which the log
///                            message was generated.
/// @param[in]  line_nbr       The line number from which the log message
///                            originated.
/// @since  x.y.z, 19.06.2016
StreamLog::StreamLog( const std::string& log_name, const std::string filename,
                      const char* const function_name, int line_nbr) noexcept( false):
   mLogIds( 0),
   mLogName( log_name),
   mErrNbrNext( false),
   mStrStream(),
   mLogMsg( filename, function_name, line_nbr)
{

   if (mLogName.empty())
      throw CELMA_RuntimeError( "no destination log name specified");

} // StreamLog::StreamLog



/// Destructor. Finally create the requested log message.
/// @since  x.y.z, 19.06.2016
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
/// @param[in]  eb  The exception to log.
/// @since  x.y.z, 19.06.2016
void StreamLog::storeException( const common::ExceptionBase& eb)
{

   if (mLogMsg.getLevel() == LogLevel::undefined)
      mLogMsg.setLevel( LogLevel::error);
   if (mLogMsg.getClass() == LogClass::undefined)
      mLogMsg.setClass( LogClass::sysCall);

   mLogMsg.assign( eb);
   mStrStream << eb.text();

} // StreamLog::storeException



bool StreamLog::hasPropertyName() const
{

   return !mPropertyName.empty();
} // StreamLog::hasPropertyName



void StreamLog::storePropertyName( const std::string& property_name)
{

   mPropertyName = property_name;

} // StreamLog::storePropertyName



void StreamLog::storeProperty( const std::string& property_value)
{

   mLogMsg.setCustomProperty( mPropertyName, property_value);

   mPropertyName.clear();

} // StreamLog::storeProperty



} // namespace detail
} // namespace log
} // namespace celma


// ==========================  END OF stream_log.cpp  ==========================

