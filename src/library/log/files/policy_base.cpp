
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
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
#include "celma/common/file_operations.hpp"
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/builder.hpp"


namespace celma { namespace log { namespace files {



/// Constructor. Stores the object to use to create the log file names.
///
/// @param[in]  fname_def  Log filename definition.
/// @throws  invalid argument when the filename definition contains no parts.
/// @since  1.0.0, 13.12.2017
PolicyBase::PolicyBase( const filename::Definition& fname_def):
   mFilenameDefinition( fname_def),
   mCurrentLogfileName(),
   mFile()
{

   if (mFilenameDefinition.empty())
      throw std::invalid_argument( "filename definition is empty");

} // PolicyBase::PolicyBase



/// Opens the current log file, checks if it still is okay to use the file,
/// if not closes the file again, rolls the log file generations and opens
/// a new file.<br>
/// All that is done calling the virtual function which must be implemented
/// by the derived classes, the real policies.
///
/// @param[in]  from_reopen
///    Set to \c true if the open function is called by reOpenFile() to open
///    a (new) log file after a rollover.<br>
///    This is needed to prevent an endless loop. If the open check fails on
///    the re-opened file, an exception is thrown.
/// @throws
///   runtime error if the file could not be created, or if the open check
///   fails for a re-opened file.
/// @since  1.25.0, 20.05.2019
///    (added parameter \a from_reopen)
/// @since  1.0.0, 13.12.2017
void PolicyBase::open( bool from_reopen)
{

   const auto  filename = filename::Builder::filename( mFilenameDefinition);


   mFile.open( filename, std::ios_base::out | std::ios_base::ate);

   if (!mFile || !mFile.is_open())
   {
      // check if the file should be created in a directory that does not exist
      // and if so, try to create the directory
      const auto  pos = filename.find_last_of( '/');
      if (pos != std::string::npos)
      {
         const auto  path = filename.substr( 0, pos);
         common::FileOperations::mkdir( path);

         // try again
         mFile.open( filename, std::ios_base::out | std::ios_base::ate);
      } // end if
   } // end if

   if (!mFile || !mFile.is_open())
      throw std::runtime_error( "could not open file '" + filename
         + "': " + ::strerror( errno));

   mCurrentLogfileName = filename;

   if (!openCheck())
   {
      if (from_reopen)
         throw std::runtime_error( "open check failed for re-opened file");

      reOpenFile();
   } // end if

} // PolicyBase::open



/// Write the next log message. Either in the currently opened file, if that
/// is still valid, or rolls the log file generations and writes into a
/// newly opened file.
///
/// @param[in]  msg
///    The log message object with the data of the log message to write
///    into the file.<br>
///    Provided e.g. for date checks.
/// @param[in]  msg_text
///    The formatted text of the log message to write.
/// @since  1.0.0, 13.12.2017
void PolicyBase::writeMessage( const detail::LogMsg& msg,
   const std::string& msg_text)
{

   if (!writeCheck( msg, msg_text))
      reOpenFile();

   mFile << msg_text << std::endl;

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
///
/// @since  1.0.0, 13.12.2017
void PolicyBase::reOpenFile()
{

   mFile.close();

   rollFiles();

   open( true);

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

