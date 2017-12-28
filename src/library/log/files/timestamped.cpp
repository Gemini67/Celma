
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


// module header file include
#include "celma/log/files/timestamped.hpp"


// C++ Standard Library includes
#include <stdexcept>


// project includes
#include "celma/log/filename/builder.hpp"


namespace celma { namespace log { namespace files {



/// Constructor. Checks if the given log filename definition contains a date
/// field.
/// @param[in]  fname_def  The definition of the log file path and namees.
/// @since  1.0.0, 13.12.2017
Timestamped::Timestamped( const filename::Definition& fname_def):
   PolicyBase( fname_def),
   mTimestampLast( 0)
{

   if (!mFilenameDefinition.hasDateField())
      throw std::runtime_error( "a log filename definition for log files "
         "limited by timestamp must include a date field");

} // Timestamped::Timestamped



/// Copy constructor. Copies only the settings but not any eventually open
/// log file.
/// @param[in]  other  The other object to copy the data from.
/// @since  1.0.0, 13.12.2017
Timestamped::Timestamped( const Timestamped& other):
   PolicyBase( other),
   mTimestampLast( 0)
{
} // Timestamped::Timestamped



/// Returns \c true for this policy.<br>
/// Also calculates the maximum timestamp for log messages to be written into
/// this file.
/// @return  Always \c true.
/// @since  1.0.0, 13.12.2017
bool Timestamped::openCheck()
{

   static const time_t  bases[] = { 60, 60 * 60, 60 * 60 * 24 };

   // have to calculate the timestamp of the last message that may be written
   // into this file
   const auto  now  = ::time( nullptr);
   const auto  current_logfile_name( logFileName());

   mTimestampLast = 0;

   for (auto const value : bases)
   {
      const auto  check_time = now - (now % value) + value;
      auto        check_filename =
         filename::Builder::filename( mFilenameDefinition, 0, check_time);

      if (current_logfile_name != check_filename)
      {
         mTimestampLast = check_time;
         break;  // for
      } // end if
   } // end for

   if (mTimestampLast == 0)
   {
   } // end if

   return true;
} // Timestamped::openCheck



/// Does nothing in this policy.
/// @since  1.0.0, 13.12.2017
void Timestamped::rollFiles()
{
} // Timestamped::rollFiles



/// Called to check if the next log message can still be written into the
/// current log file.<br>
/// Here, checks if the timestamp of the log message still matches the date
/// part of the log filename.
/// @param[in]  msg       The object with the data of the log message.
/// @param[in]  msg_text  Ignored.
/// @return  \c true if the log message text can be written into the current
///          log file.
/// @since  1.0.0, 13.12.2017
bool Timestamped::writeCheck( const detail::LogMsg& msg,
   const std::string&)
{

   return msg.getTimestamp() < mTimestampLast;
} // Timestamped::writeCheck



/// Called after the log message was written into the log file. Here, does
/// nothing.
/// @param[in]  msg       Ignored.
/// @param[in]  msg_text  
/// @since  1.0.0, 13.12.2017
void Timestamped::written( const detail::LogMsg&, const std::string&)
{
} // Timestamped::written



} // namespace files
} // namespace log
} // namespace celma


// =========================  END OF timestamped.cpp  =========================

