
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
/// See documentation of class celma::log::detail::LogMsg.


#ifndef CELMA_LOG_DETAIL_LOG_MSG_HPP
#define CELMA_LOG_DETAIL_LOG_MSG_HPP


#include <sys/types.h>
#include <string>
#include "celma/common/exception_base.hpp"
#include "celma/log/detail/log_defs.hpp"


namespace celma { namespace log { namespace detail {


/// Class to store all the data of a log message.
/// @since  0.3, 19.06.2016
class LogMsg
{
public:
   /// Constructor, sets the properties where this log message was created.<br>
   /// Internally, also the process id is set.
   /// @param[in]  file_name             The name of the source file.
   /// @param[in]  pretty_function_name  The name of the function.
   /// @param[in]  line_nbr              The line number.
   /// @since  0.3, 19.06.2016
   LogMsg( const std::string& file_name, const char* const pretty_function_name,
           int line_nbr);

   /// Stores the data of an exception.<br>
   /// Note that also the line number, function name etc. are copied.
   /// @param[in]  eb  The exception to copy the data from.
   /// @since  0.3, 19.06.2016
   void assign( const common::ExceptionBase& eb);

   /// Sets the log class.
   /// @param[in]  lc  The log class of this message.
   /// @since  0.3, 19.06.2016
   void setClass( LogClass lc);

   /// Sets the log level.
   /// @param[in]  ll  The log level.
   /// @since  0.3, 19.06.2016
   void setLevel( LogLevel ll);

   /// Sets the error number, if there is any.
   /// @param[in]  error_nbr  The error number.
   /// @since  0.3, 19.06.2016
   void setErrorNumber( int error_nbr);

   /// Sets the log message text.
   /// @param[in]  text  The text to log.
   /// @since  0.3, 19.06.2016
   void setText( const std::string& text);

   /// Returns the process id.
   /// @return  The id of the process by which the log message was created.
   /// @since  0.3, 19.06.2016
   pid_t getProcessId() const;

   /// Returns the source file name.
   /// @return  The name of the source file where the log message was created.
   /// @since  0.3, 19.06.2016
   const std::string& getFileName() const;

   /// The name of the function.
   /// @return  The name of the function where the log message was created.
   /// @since  0.3, 19.06.2016
   const std::string& getFunctionName() const;

   /// The line number.
   /// @return  Returns the number of the line in the source file where the log
   /// message was created.
   /// @since  0.3, 19.06.2016
   int getLineNbr() const;

   /// The log class.
   /// @return  The log class of the message.
   /// @since  0.3, 19.06.2016
   LogClass getClass() const;

   /// The log level.
   /// @return  The log level.
   /// @since  0.3, 19.06.2016
   LogLevel getLevel() const;

   /// Returns the error number.
   /// @return  The error number set for the log message.
   /// @since  0.3, 19.06.2016
   int getErrorNbr() const;

   /// Returns the log message text.
   /// @return  The text of the log message.
   /// @since  0.3, 19.06.2016
   const std::string& getText() const;

private:
   /// Time stamp when the log message (i.e., this object) was created.
   time_t        mTimestamp;
   /// The id of the process that created the log message.
   pid_t         mProcessId;
   /// The name of the source file.
   std::string   mFileName;
   /// The name of the function.
   std::string   mFunctionName;
   /// The line number in the source file.
   int           mLineNbr;
   /// The classification of the log message.
   LogClass      mClass;
   /// The severity level of the log message.
   LogLevel      mLevel;
   /// The error number for this log message.
   int           mErrNbr;
   /// The text of the log message.
   std::string   mText;

}; // LogMsg


// inlined methods
// ===============


inline pid_t LogMsg::getProcessId() const
{
   return mProcessId;
} // end LogMsg::getProcessId


inline const std::string& LogMsg::getFileName() const
{
   return mFileName;
} // end LogMsg::getFileName


inline const std::string& LogMsg::getFunctionName() const
{
   return mFunctionName;
} // end LogMsg::getFunctionName


inline int LogMsg::getLineNbr() const
{
   return mLineNbr;
} // end LogMsg::getLineNbr


inline LogClass LogMsg::getClass() const
{
   return mClass;
} // end LogMsg::getClass


inline LogLevel LogMsg::getLevel() const
{
   return mLevel;
} // end LogMsg::getLevel


inline int LogMsg::getErrorNbr() const
{
   return mErrNbr;
} // end LogMsg::getErrorNbr


inline void LogMsg::setClass( LogClass lc)
{
   mClass = lc;
} // end LogMsg::setClass


inline void LogMsg::setLevel( LogLevel ll)
{
   mLevel = ll;
} // end LogMsg::setLevel


inline void LogMsg::setErrorNumber( int error_nbr)
{
   mErrNbr = error_nbr;
} // end LogMsg::setErrorNumber


inline void LogMsg::setText( const std::string& text)
{
   mText = text;
} // end LogMsg::setText


inline const std::string& LogMsg::getText() const
{
   return mText;
} // end LogMsg::getText


// macros
// ======


/// Use this macro as parameter for the LogMsg constructor to correctly
/// initialise a log message object.
/// @since  0.3, 19.06.2016
#define LOG_MSG_OBJECT_INIT  __FILE__, \
                             __PRETTY_FUNCTION__, \
                             __LINE__


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_MSG_HPP


// ===========================  END OF log_msg.hpp  ===========================

