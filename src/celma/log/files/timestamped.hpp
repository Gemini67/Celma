
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::files::@@@.


#ifndef CELMA_LOG_FILES_TIMESTAMPED_HPP
#define CELMA_LOG_FILES_TIMESTAMPED_HPP


#include <ctime>
#include <string>
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/definition.hpp"
#include "celma/log/files/policy_base.hpp"


namespace celma { namespace log { namespace files {


/// Policy to handle log file(s) by timestamp: All log messages with the same
/// timestamp are written into the same file.
/// @since  x.y.z, 13.12.2017
class Timestamped: public PolicyBase
{
public:
   /// Constructor. Checks if the given log filename definition contains a date
   /// field.
   /// @param[in]  fname_def  The definition of the log file path and namees.
   /// @since  x.y.z, 13.12.2017
   Timestamped( const filename::Definition& fname_def) noexcept( false);

   /// Copy constructor. Copies only the settings but not any eventually open
   /// log file.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  x.y.z, 13.12.2017
   Timestamped( const Timestamped& other);

   /// Default destructor.
   /// @since  x.y.z, 13.12.2017
   virtual ~Timestamped() = default;

private:
   /// Returns \c true for this policy.<br>
   /// Also calculates the maximum timestamp for log messages to be written into
   /// this file.
   /// @return  Always \c true.
   /// @since  x.y.z, 13.12.2017
   virtual bool openCheck() override;

   /// Does nothing in this policy.
   /// @since  x.y.z, 13.12.2017
   virtual void rollFiles() override;

   /// Called to check if the next log message can still be written into the
   /// current log file.<br>
   /// Here, checks if the timestamp of the log message still matches the date
   /// part of the log filename.
   /// @param[in]  msg       The object with the data of the log message.
   /// @param[in]  msg_text  Ignored.
   /// @return  \c true if the log message text can be written into the current
   ///          log file.
   /// @since  x.y.z, 13.12.2017
   virtual bool writeCheck( const detail::LogMsg& msg,
      const std::string& msg_text) override;

   /// Called after the log message was written into the log file. Here, does
   /// nothing.
   /// @param[in]  msg       Ignored.
   /// @param[in]  msg_text  
   /// @since  x.y.z, 13.12.2017
   virtual void written( const detail::LogMsg& msg,
      const std::string& msg_text) override;

   /// The maximum timestamp of log messages to write into this file.
   time_t  mTimestampLast;

}; // Timestamped


} // namespace files
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILES_TIMESTAMPED_HPP


// =========================  END OF timestamped.hpp  =========================

