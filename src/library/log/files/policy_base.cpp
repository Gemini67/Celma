
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::files::PolicyBase.


// module header file include
#include "celma/log/files/policy_base.hpp"


// OS/C lib includes
#include <cerrno>
#include <cstring>


// C++ Standard Library includes
#include <stdexcept>
#include <string>


// project includes
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/builder.hpp"


namespace celma { namespace log { namespace files {



/// Constructor. Stores the object to use to create the log file names.
/// @param[in]  fname_def  Log filename definition.
/// @since  1.0.0, 13.12.2017
PolicyBase::PolicyBase( const filename::Definition& fname_def):
   mFilenameDefinition( fname_def),
   mCurrentLogfileName(),
   mFile()
{
} // PolicyBase::PolicyBase



/// Opens the current log file, checks if it still is okay to use the file,
/// if not closes the file again, rolls the log file generations and opens
/// a new file.<br>
/// All that is done calling the virtual function which must be implemented
/// by the derived classes, the real policies.
/// @since  1.0.0, 13.12.2017
void PolicyBase::open()
{

   const auto  filename = filename::Builder::filename( mFilenameDefinition);


   mFile.open( filename, std::ios_base::out | std::ios_base::ate);

   if (!mFile || !mFile.is_open())
      throw std::runtime_error( "could not open file '" + filename
         + "': " + ::strerror( errno));

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
/// @since  1.0.0, 13.12.2017
void PolicyBase::writeMessage( const detail::LogMsg& msg,
   const std::string& msg_text)
{

   if (!writeCheck( msg, msg_text))
      reOpenFile();

   mFile << msg_text;

   written( msg, msg_text);

} // PolicyBase::writeMessage



/// Called when openCheck() returned \c false. The current file is already
/// closed then, all the function has to do is roll the log file
/// enerations.<br>
/// Empty method provided here in the base class, so it only needs to be
/// overwritten when actually used.
///
/// @since  1.11.0, 05.09.2018  (not pure virtual anymore)
/// @since  1.0.0, 13.12.2017
void PolicyBase::rollFiles()
{
} // PolicyBase::rollFiles



/// Closes the currently open log file, calls rollFiles() to roll the log
/// file generations, and finally opens a new log file.<br>
/// This functions is called when either the openCheck() or writeCheck()
/// function returned \c false.
/// @since  1.0.0, 13.12.2017
void PolicyBase::reOpenFile()
{

   mFile.close();

   rollFiles();

   open();

} // PolicyBase::reOpenFile



/// Returns the current size of the log file.
///
/// @return  The current size of the file.
/// @since  1.11.0, 27.08.2018
size_t PolicyBase::fileSize()
{

   return mFile.tellp();
} // PolicyBase::fileSize



} // namespace files
} // namespace log
} // namespace celma


// =====  END OF policy_base.cpp  =====

