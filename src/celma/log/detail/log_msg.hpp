
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
/// See documentation of class celma::log::detail::LogMsg.


#ifndef CELMA_LOG_DETAIL_LOG_MSG_HPP
#define CELMA_LOG_DETAIL_LOG_MSG_HPP


#include <pthread.h>
#include <ctime>
#include <string>
#include "celma/common/exception_base.hpp"
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/log_attributes.hpp"


namespace celma { namespace log { namespace detail {


/// Class to store all the data of a log message.
/// @since  1.15.0, 17.10.2018
///    (removed properties, added support for attributes)
/// @since  1.0.0, 19.06.2016
class LogMsg
{
public:
   /// Constructor, sets the properties where this log message was created.<br>
   /// Internally, also the process id is set.
   /// @param[in]  file_name             The name of the source file.
   /// @param[in]  pretty_function_name  The name of the function.
   /// @param[in]  line_nbr              The line number.
   /// @since  1.0.0, 19.06.2016
   LogMsg( const std::string& file_name, const char* const pretty_function_name,
           int line_nbr);

   /// Stores the data of an exception.<br>
   /// Note that also the line number, function name etc. are copied.
   /// @param[in]  eb  The exception to copy the data from.
   /// @since  1.0.0, 19.06.2016
   void assign( const common::ExceptionBase& eb);

   /// Sets the log class.
   /// @param[in]  lc  The log class of this message.
   /// @since  1.0.0, 19.06.2016
   void setClass( LogClass lc);

   /// Sets the log level.
   /// @param[in]  ll  The log level.
   /// @since  1.0.0, 19.06.2016
   void setLevel( LogLevel ll);

   /// Sets the error number, if there is any.
   /// @param[in]  error_nbr  The error number.
   /// @since  1.0.0, 19.06.2016
   void setErrorNumber( int error_nbr);

   /// Sets the log message text.
   /// @param[in]  text  The text to log.
   /// @since  1.0.0, 19.06.2016
   void setText( const std::string& text);

   /// Sets the timestamp for the log message.
   /// @param[in]  ts  The timestamp to store.
   /// @since  1.0.0, 27.09.2017
   void setTimestamp( time_t ts);

   /// Returns the timestamp when the log message was created.
   /// @return  The timestamp for the log message.
   /// @since  1.0.0, 11.12.2016
   time_t getTimestamp() const;

   /// Returns the process id.
   /// @return  The id of the process by which the log message was created.
   /// @since  1.0.0, 19.06.2016
   pid_t getProcessId() const;

   /// Returns the thread id.
   /// @return  The id of the thread by which the log message was created.
   /// @since  1.0.0, 04.10.2017
   pthread_t getThreadId() const;

   /// Returns the source file name.
   /// @return  The name of the source file where the log message was created.
   /// @since  1.0.0, 19.06.2016
   const std::string& getFileName() const;

   /// The name of the function.
   /// @return  The name of the function where the log message was created.
   /// @since  1.0.0, 19.06.2016
   const std::string& getFunctionName() const;

   /// The line number.
   /// @return  Returns the number of the line in the source file where the log
   /// message was created.
   /// @since  1.0.0, 19.06.2016
   int getLineNbr() const;

   /// The log class.
   /// @return  The log class of the message.
   /// @since  1.0.0, 19.06.2016
   LogClass getClass() const;

   /// The log level.
   /// @return  The log level.
   /// @since  1.0.0, 19.06.2016
   LogLevel getLevel() const;

   /// Returns the error number.
   /// @return  The error number set for the log message.
   /// @since  1.0.0, 19.06.2016
   int getErrorNbr() const;

   /// Returns the log message text.
   /// @return  The text of the log message.
   /// @since  1.0.0, 19.06.2016
   const std::string& getText() const;

   /// Adds (a pointer to) an attribute container.
   ///
   /// @param[in]  attr_cont  The attribute container.
   /// @since  1.15.0, 17.10.2018
   void setAttributes( const LogAttributes& attr_cont);

   /// Returns the value of the attribute with the given name.
   ///
   /// @param[in]  attr_name  The name of the attribute to return the value of.
   /// @return
   ///    The value of the attribute or an empty string when not found.
   /// @since
   ///    1.15.0, 17.10.2018
   std::string getAttributeValue( const std::string& attr_name) const;

private:
   /// Time stamp when the log message (i.e., this object) was created.
   time_t                mTimestamp;
   /// The id of the process that created the log message.
   pid_t                 mProcessId;
   /// The id the thread that created the message.
   pthread_t             mThreadId;
   /// The name of the source file.
   std::string           mFileName;
   /// The name of the function.
   std::string           mFunctionName;
   /// The line number in the source file.
   int                   mLineNbr;
   /// The classification of the log message.
   LogClass              mClass = LogClass::undefined;
   /// The severity level of the log message.
   LogLevel              mLevel = LogLevel::undefined;
   /// The error number for this log message.
   int                   mErrNbr = 0;
   /// The text of the log message.
   std::string           mText;
   /// Pointer to the optional object to get the log attributes from.
   const LogAttributes*  mpAttributes = nullptr;

}; // LogMsg


// inlined methods
// ===============


inline time_t LogMsg::getTimestamp() const
{
   return mTimestamp;
} // LogMsg::getTimestamp


inline pid_t LogMsg::getProcessId() const
{
   return mProcessId;
} // LogMsg::getProcessId


inline pthread_t LogMsg::getThreadId() const
{
   return mThreadId;
} // LogMsg::getThreadId


inline const std::string& LogMsg::getFileName() const
{
   return mFileName;
} // LogMsg::getFileName


inline const std::string& LogMsg::getFunctionName() const
{
   return mFunctionName;
} // LogMsg::getFunctionName


inline int LogMsg::getLineNbr() const
{
   return mLineNbr;
} // LogMsg::getLineNbr


inline LogClass LogMsg::getClass() const
{
   return mClass;
} // LogMsg::getClass


inline LogLevel LogMsg::getLevel() const
{
   return mLevel;
} // LogMsg::getLevel


inline int LogMsg::getErrorNbr() const
{
   return mErrNbr;
} // LogMsg::getErrorNbr


inline void LogMsg::setClass( LogClass lc)
{
   mClass = lc;
} // LogMsg::setClass


inline void LogMsg::setLevel( LogLevel ll)
{
   mLevel = ll;
} // LogMsg::setLevel


inline void LogMsg::setErrorNumber( int error_nbr)
{
   mErrNbr = error_nbr;
} // LogMsg::setErrorNumber


inline void LogMsg::setText( const std::string& text)
{
   mText = text;
} // LogMsg::setText


inline void LogMsg::setTimestamp( time_t ts)
{
   mTimestamp = ts;
} // LogMsg::setTimestamp


inline const std::string& LogMsg::getText() const
{
   return mText;
} // LogMsg::getText


inline void LogMsg::setAttributes( const LogAttributes& attr_cont)
{
  mpAttributes = &attr_cont;
} // LogMsg::setAttributes


inline std::string LogMsg::getAttributeValue( const std::string& attr_name) const
{
   return (mpAttributes == nullptr) ? std::string()
      : mpAttributes->getAttribute( attr_name);
} // LogMsg::getAttributeValue


// macros
// ======


/// Use this macro as parameter for the LogMsg constructor to correctly
/// initialise a log message object.
/// @since  1.0.0, 19.06.2016
#define LOG_MSG_OBJECT_INIT  __FILE__, \
                             __PRETTY_FUNCTION__, \
                             __LINE__


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_MSG_HPP


// =====  END OF log_msg.hpp  =====

