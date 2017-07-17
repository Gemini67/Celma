
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
/// See documentation of class celma::log::detail::StreamLog.


#ifndef CELMA_LOG_DETAIL_STREAM_LOG_HPP
#define CELMA_LOG_DETAIL_STREAM_LOG_HPP


#include <libgen.h>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/custom_property.hpp"
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace detail {


/// Helper class to create a log message using C++ streams syntax.
/// @since  0.3, 19.06.2016
class StreamLog
{
public:
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
   /// @since  0.3, 19.06.2016
   StreamLog( id_t log_ids, const std::string filename,
              const char* const function_name, int line_nbr) noexcept( false);

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
   /// @since  0.3, 19.06.2016
   StreamLog( const std::string& log_name, const std::string filename,
              const char* const function_name, int line_nbr) noexcept( false);

   /// Destructor. Pass the created log message to the log framework.
   /// @since  0.3, 19.06.2016
   ~StreamLog();

   /// Helper function to use the temporary object to create the log message.
   /// @return  This object.
   /// @since  0.3, 19.06.2016
   StreamLog& self()
   {
      return *this;
   } // end StreamLog::self

   /// Sets the log class for the current message.
   /// @param[in]  so  The object (= message) to set the log class for.
   /// @param[in]  lc  The log class to set.
   /// @return  The object passed in \a so.
   /// @since  0.3, 19.06.2016
   friend StreamLog& operator <<( StreamLog& so, LogClass lc)
   {
      // range check
      if ((lc < LogClass::undefined) || (lc > LogClass::operatorAction))
         so.mLogMsg.setClass( LogClass::undefined);
      else
         so.mLogMsg.setClass( lc);

      return so;
   } // end operator <<

   /// Sets the log level for the current message.
   /// @param[in]  so  The object (= message) to set the log level for.
   /// @param[in]  ll  The log level to set.
   /// @return  The object passed in \a so.
   /// @since  0.3, 19.06.2016
   friend StreamLog& operator <<( StreamLog& so, LogLevel ll)
   {
      if (so.mLogMsg.getLevel() == LogLevel::undefined)
      {
         // range check
         if ((ll <= LogLevel::undefined) || (ll > LogLevel::fullDebug))
            so.mLogMsg.setLevel( LogLevel::undefined);
         else
            so.mLogMsg.setLevel( ll);
      } else
      {
         // seems that user wants to write a log level into the log message
         so.mStrStream << ll;
      } // end if
      
      return so;
   } // end operator <<

   /// Logs an exception of type 'Celma runtime error'.<br>
   /// If the log level and class are not already set, they are set to
   /// \a error and \a lcSysCall, respectively. Of course they can also be set
   /// afterwards.
   /// @param[in]  so   Me.
   /// @param[in]  cre  The exception object to log.
   /// @return  Myself.
   /// @since  0.3, 19.06.2016
   friend StreamLog& operator <<( StreamLog& so,
                                  const common::CelmaRuntimeError& cre)
   {
      so.storeException( cre);
      return so;
   } // end operator <<

   /// Logs an exception of type 'Celma logic error'.<br>
   /// If the log level and class are not already set, they are set to
   /// \a error and \a lcSysCall, respectively. Of course they can also be set
   /// afterwards.
   /// @param[in]  so   Me.
   /// @param[in]  sre  The exception object to log.
   /// @return  Myself.
   /// @since  0.3, 19.06.2016
   friend StreamLog& operator <<( StreamLog& so,
                                  const common::CelmaLogicError& cle)
   {
      so.storeException( cle);
      return so;
   } // end operator <<

   /// Logs any exception.<br>
   /// The exception object needs a cast to the type \c 'const ExceptionBase&'
   /// for this operator to be called.<br>
   /// If the log level and class are not already set, they are set to
   /// \a error and \a lcSysCall, respectively. Of course they can also be set
   /// afterwards.
   /// @param[in]  so  Me.
   /// @param[in]  eb  The exception object to log.
   /// @return  The object passed in \a so.
   /// @since  0.3, 19.06.2016
   friend StreamLog& operator <<( StreamLog& so, const common::ExceptionBase& eb)
   {
      so.storeException( eb);
      return so;
   } // end operator <<

   /// 
   /// @param[in]  so  .
   /// @param[in]  cp  .
   /// @return  .
   /// @since  0.11, 12.12.2016
   friend StreamLog& operator <<( StreamLog& so, const customProperty& cp)
   {
      so.storePropertyName( cp.name());
      return so;
   } // end operator <<

   /// Input operator to add 'anything' to the internal stringstream.
   /// @tparam     T      The type of the value to add.
   /// @param[in]  so     The StreamLog to append the value.
   /// @param[in]  value  The value to append.
   /// @return  The StreamLog from the input parameter.
   /// @since  0.3, 19.06.2016
   template <typename T> friend StreamLog& operator <<( StreamLog& so,
                                                        const T& value)
   {
      if (so.mErrNbrNext)
      {
         so.mLogMsg.setErrorNumber( boost::lexical_cast< int>( value));
         so.mErrNbrNext = false;
      } else if (so.hasPropertyName())
      {
         std::ostringstream  oss;
         oss << value;
         so.storeProperty( oss.str());
      } else
      {
         so.mStrStream << value;
      } // end if
      return so;
   } // end operator <<

/*
   /// Input operator for ostream, prints the contents of the internal
   /// stringstream.
   /// @param[in]  os  The stream to write to.
   /// @param[in]  so  The StreamLog to dump the stringstream contents of.
   /// @return  The stream from the input parameter.
   /// @since  0.3, 19.06.2016
   friend std::ostream& operator <<( std::ostream& os, const StreamLog& so)
   {
      os << "file='" << so.mFile << "',line=" << so.mLineNbr << ",class="
         << so.mClass << ",level=" << so.mLevel << ",text='"
         << so.mStrStream.str() << "'";
      return os;
   } // end operator <<
*/

   /// This is the magic function to use manipulators: When a function is passed
   /// to the input operator, it is called.
   /// @param[in]  m  The function to call.
   /// @return  The object itself.
   /// @since  0.3, 19.06.2016
   StreamLog& operator <<( StreamLog&( *m)( StreamLog&))
   {
      m( *this);
      return *this;
   } // end StreamLog::operator <<

   /// Erases the contents of the internal stringstream.
   /// @since  0.3, 19.06.2016
   void clear()
   {
      mStrStream.str( "");
   } // end StreamLog::clear

   /// Stream manipulator: Specifies that the next value is the error number for
   /// the current message.
   /// @since  0.3, 19.06.2016
   void errnbr()
   {
      mErrNbrNext = true;
   } // end StreamLog::errnbr

private:
   /// Stores the data of an exception in the log message object.<br>
   /// The text of the exception is assigned to the internal stringstream in
   /// order to keep the feature that log messages without text are discarded.
   /// @param[in]  eb  The exception to log.
   /// @since  0.3, 19.06.2016
   void storeException( const common::ExceptionBase& eb);

   /// 
   /// @return  .
   /// @since  0.11, 12.12.2016
   bool hasPropertyName() const;

   /// 
   /// @param[in]  property_name  .
   /// @since  0.11, 12.12.2016
   void storePropertyName( const std::string& property_name);

   /// 
   /// @param[in]  property_value  .
   /// @since  0.11, 12.12.2016
   void storeProperty( const std::string& property_value);

   /// The set of log ids to which the log message should be sent.
   const id_t          mLogIds;
   /// The name of the log to sent the log message to (if no log ids are set).
   const std::string   mLogName;
   /// Internal processing flag: The next call of the insertion operator will
   /// give the error number.
   bool                mErrNbrNext;
   /// Internal stringstream object used to build the text of the log message.
   std::ostringstream  mStrStream;
   /// Name of a custom property, when set the next value is stored as property
   /// value.
   std::string         mPropertyName;
   /// The log message we are about to fill with data.
   LogMsg              mLogMsg;

}; // StreamLog


// inlined methods
// ===============


/// This method is normally not called directly but used as a manipulator for
/// a StreamLog:  so << clear << "New text";<br>
/// It clears the contents of the internal string stream, so it could be re-used
/// to generate a new log message.
/// @param[in]  in  The object to call the clear() method of.
/// @return  The StreamLog passed in the input parameter.
/// @since  0.3, 19.06.2016
inline StreamLog& clear( StreamLog& in)
{
   in.clear();
   return in;
} // clear


/// This method is normally not called directly but used as a manipulator for
/// a StreamLog:  so << errnbr << errno;<br>
/// Using this manipulator specifies that the next value in the stream input is
/// the error number for the current log message.
/// @param[in]  in  The object to call the errnbr() method of.
/// @return  The StreamLog passed in the input parameter.
/// @since  0.3, 19.06.2016
inline StreamLog& errnbr( StreamLog& in)
{
   in.errnbr();
   return in;
} // errnbr


} // namespace detail
} // namespace log
} // namespace celma


/// @example
/// To create a log message with an error number:
///
/// <pre>
/// LOG( log_id) << errnbr << errno << "Call to sysop() failed";
/// </pre>

#endif   // CELMA_LOG_DETAIL_STREAM_LOG_HPP


// ==========================  END OF stream_log.hpp  ==========================

