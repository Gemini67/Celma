
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
/// See documentation of class celma::log::detail::LogMsg.


#ifndef CELMA_LOG_DETAIL_LOG_MSG_HPP
#define CELMA_LOG_DETAIL_LOG_MSG_HPP


#include <ctime>
#include <string>
#include "celma/common/exception_base.hpp"
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log_msg_property.hpp"


namespace celma { namespace log { namespace detail {


/// Class to store all the data of a log message.
/// @since x.y.z, 19.06.2016
class LogMsg
{
public:
   /// Constructor, sets the properties where this log message was created.<br>
   /// Internally, also the process id is set.
   /// @param[in]  file_name             The name of the source file.
   /// @param[in]  pretty_function_name  The name of the function.
   /// @param[in]  line_nbr              The line number.
   /// @since x.y.z, 19.06.2016
   LogMsg( const std::string& file_name, const char* const pretty_function_name,
           int line_nbr);

   /// Stores the data of an exception.<br>
   /// Note that also the line number, function name etc. are copied.
   /// @param[in]  eb  The exception to copy the data from.
   /// @since x.y.z, 19.06.2016
   void assign( const common::ExceptionBase& eb);

   /// Sets the log class.
   /// @param[in]  lc  The log class of this message.
   /// @since x.y.z, 19.06.2016
   void setClass( LogClass lc);

   /// Sets the log level.
   /// @param[in]  ll  The log level.
   /// @since x.y.z, 19.06.2016
   void setLevel( LogLevel ll);

   /// Sets the error number, if there is any.
   /// @param[in]  error_nbr  The error number.
   /// @since x.y.z, 19.06.2016
   void setErrorNumber( int error_nbr);

   /// Sets the log message text.
   /// @param[in]  text  The text to log.
   /// @since x.y.z, 19.06.2016
   void setText( const std::string& text);

   /// 
   /// @param[in]  property_name   .
   /// @param[in]  property_value  .
   /// @since x.y.z, 11.12.2016
   void setCustomProperty( const std::string& property_name,
                           const std::string& property_value);

   /// Sets the timestamp for the log message.
   /// @param[in]  ts  The timestamp to store.
   /// @since  x.y.z, 27.09.2017
   void setTimestamp( time_t ts);

   /// Returns the timestamp when the log message was created.
   /// @return  The timestamp for the log message.
   /// @since x.y.z, 11.12.2016
   time_t getTimestamp() const;

   /// Returns the process id.
   /// @return  The id of the process by which the log message was created.
   /// @since x.y.z, 19.06.2016
   pid_t getProcessId() const;

   /// Returns the source file name.
   /// @return  The name of the source file where the log message was created.
   /// @since x.y.z, 19.06.2016
   const std::string& getFileName() const;

   /// The name of the function.
   /// @return  The name of the function where the log message was created.
   /// @since x.y.z, 19.06.2016
   const std::string& getFunctionName() const;

   /// The line number.
   /// @return  Returns the number of the line in the source file where the log
   /// message was created.
   /// @since x.y.z, 19.06.2016
   int getLineNbr() const;

   /// The log class.
   /// @return  The log class of the message.
   /// @since x.y.z, 19.06.2016
   LogClass getClass() const;

   /// The log level.
   /// @return  The log level.
   /// @since x.y.z, 19.06.2016
   LogLevel getLevel() const;

   /// Returns the error number.
   /// @return  The error number set for the log message.
   /// @since x.y.z, 19.06.2016
   int getErrorNbr() const;

   /// Returns the log message text.
   /// @return  The text of the log message.
   /// @since x.y.z, 19.06.2016
   const std::string& getText() const;

   /// Returns the value of a custom property.
   /// @param[in]  property_name  The name of the property to return the value of.
   /// @return  The value of the property, empty string if the property is unknown.
   /// @since x.y.z, 12.12.2016
   const std::string getPropertyValue( const std::string& property_name) const;

private:
   /// Time stamp when the log message (i.e., this object) was created.
   time_t          mTimestamp;
   /// The id of the process that created the log message.
   pid_t           mProcessId;
   /// The name of the source file.
   std::string     mFileName;
   /// The name of the function.
   std::string     mFunctionName;
   /// The line number in the source file.
   int             mLineNbr;
   /// The classification of the log message.
   LogClass        mClass;
   /// The severity level of the log message.
   LogLevel        mLevel;
   /// The error number for this log message.
   int             mErrNbr;
   /// The text of the log message.
   std::string     mText;
   /// Stores custom-set properties of the log message.
   LogMsgProperty  mCustomProperty;

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


inline const std::string
   LogMsg::getPropertyValue( const std::string& property_name) const
{
   return mCustomProperty.getPropertyValue( property_name);
} // LogMsg::getPropertyValue


// macros
// ======


/// Use this macro as parameter for the LogMsg constructor to correctly
/// initialise a log message object.
/// @since x.y.z, 19.06.2016
#define LOG_MSG_OBJECT_INIT  __FILE__, \
                             __PRETTY_FUNCTION__, \
                             __LINE__


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_MSG_HPP


// ===========================  END OF log_msg.hpp  ===========================

