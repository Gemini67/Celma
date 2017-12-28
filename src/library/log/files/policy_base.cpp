
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
/// See documentation of class celma::log::files::PolicyBase.


// module header file include
#include "celma/log/files/policy_base.hpp"


// C++ Standard Library includes
#include <stdexcept>
#include <string>


// project includes
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/builder.hpp"


namespace celma { namespace log { namespace files {



/// Constructor. Stores the object to use to create the log file names.
/// @param[in]  fname_def  Log filename definition.
/// @since  x.y.z, 13.12.2017
PolicyBase::PolicyBase( const filename::Definition& fname_def):
   mFilenameDefinition( fname_def),
   mCurrentLogfileName(),
   mFile()
{
} // PolicyBase::PolicyBase



/// Copy constructor. Only copies the log filename definition, not any
/// eventually open log file.
/// @param[in]  other  The other object to copy the data from.
/// @since  x.y.z, 13.12.2017
PolicyBase::PolicyBase( const PolicyBase& other):
   mFilenameDefinition( other.mFilenameDefinition),
   mCurrentLogfileName(),
   mFile()
{
} // PolicyBase::PolicyBase



/// Opens the current log file, checks if it still is okay to use the file,
/// if not closes the file again, rolls the log file generations and opens
/// a new file.<br>
/// All that is done calling the virtual function which must be implemented
/// by the derived classes, the real policies.
/// @since  x.y.z, 13.12.2017
void PolicyBase::open()
{

   const auto  filename = filename::Builder::filename( mFilenameDefinition);


   mFile.open( filename, std::ios_base::out | std::ios_base::ate);

   if (!mFile || !mFile.is_open())
      throw std::runtime_error( "could not open file '" + filename
         + "': " /* + error_reason @@@ */);

   mCurrentLogfileName = filename;

   if (!openCheck())
      reOpenFile();

} // PolicyBase::open



/// Write the next log message. Either in the currently opened file, if that
/// is still valid, or rolls the log file generations and writes into a
/// newly opened file.
/// @param[in]  msg       The log message object with the data of the log
///                       message to write into the file.<br>
///                       Provided e.g. for date checks.
/// @param[in]  msg_text  The formatted text of the log message to write.
/// @since  x.y.z, 13.12.2017
void PolicyBase::writeMessage( const detail::LogMsg& msg,
   const std::string& msg_text)
{

   if (!writeCheck( msg, msg_text))
      reOpenFile();

   mFile << msg_text;

   written( msg, msg_text);

} // PolicyBase::writeMessage



/// Closes the currently open log file, calls rollFiles() to roll the log
/// file generations, and finally opens a new log file.<br>
/// This functions is called when either the openCheck() or writeCheck()
/// function returned \c false.
/// @since  x.y.z, 13.12.2017
void PolicyBase::reOpenFile()
{

   mFile.close();

   rollFiles();

   open();

} // PolicyBase::reOpenFile



} // namespace files
} // namespace log
} // namespace celma


// =========================  END OF policy_base.cpp  =========================

