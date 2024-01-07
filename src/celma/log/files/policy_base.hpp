
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::files::PolicyBase.


#pragma once


#ifdef CELMA_LOG_POLICY_BASE_STUB
#include "celma/test/stubs/policy_base_stub.hpp"
#define  PolicyBase  PolicyBaseStub
#else


#include <fstream>
#include <string>
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/definition.hpp"


namespace celma::log::files {


/// Base class for log file handle policies. Contains the part common to all
/// policies.
///
/// @since  1.11.0, 27.08.2018
///    (renamed from PolicyBase)
/// @since  1.0.0, 13.12.2017
class PolicyBase
{
public:
   /// Constructor. Stores the object to use to create the log file names.
   ///
   /// @param[in]  fname_def  Log filename definition.
   /// @throw
   ///    std::invalid argument when the filename definition contains no parts.
   /// @since  1.0.0, 13.12.2017
   explicit PolicyBase( const filename::Definition& fname_def) noexcept( false);

   /// Copying and moving not allowed/needed.
   ///
   /// @since  1.19.0, 06.12.2018
   ///    (deleted)
   /// @since  1.0.0, 13.12.2017
   PolicyBase( const PolicyBase&) = delete;
   PolicyBase( PolicyBase&&) = delete;

   /// Default, virtual destructor.
   ///
   /// @since  1.0.0, 13.12.2017
   virtual ~PolicyBase() = default;

   /// Copying and moving not allowed/needed.
   ///
   /// @since  1.19.0, 06.12.2018
   PolicyBase& operator =( const PolicyBase&) = delete;
   PolicyBase& operator =( PolicyBase&&) = delete;

   /// Opens the current log file, checks if it still is okay to use the file,
   /// if not closes the file again, rolls the log file generations and opens
   /// a new file.
   /// All that is done calling the virtual function which must be implemented
   /// by the derived classes, the real policies.
   ///
   /// @param[in]  from_reopen
   ///    Set to \c true if the open function is called by reOpenFile() to open
   ///    a (new) log file after a rollover.<br>
   ///    This is needed to prevent an endless loop. If the open check fails on
   ///    the re-opened file, an exception is thrown.
   /// @throw
   ///    std::runtime error if the file could not be created, or if the open
   ///    check fails for a re-opened file.
   /// @since  1.25.0, 20.05.2019
   ///    (added parameter \a from_reopen)
   /// @since  1.0.0, 13.12.2017
   void open( bool from_reopen = false) noexcept( false);

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
   void writeMessage( const detail::LogMsg& msg, const std::string& msg_text);

   /// Returns the path and file name of the currently open log file.
   ///
   /// @return  The path and file name of the currently open log file.
   /// @since  1.0.0, 22.12.2017
   [[nodiscard]] const std::string& logFileName() const;

protected:
   /// Check if the currently opened log file is valid for writing into.
   ///
   /// @return
   /// - \c true if it is (still) okay to write into the current log file.
   /// - \c false if a new log file should be opened.
   /// @since  1.0.0, 13.12.2017
   virtual bool openCheck() = 0;

   /// Called when openCheck() returned \c false. The current file is already
   /// closed then, all the function has to do is roll the log file
   /// enerations.<br>
   /// Empty method provided here in the base class, so it only needs to be
   /// overwritten when actually used.
   ///
   /// @since  1.11.0, 05.09.2018  (not pure virtual anymore)
   /// @since  1.0.0, 13.12.2017
   virtual void rollFiles();

   /// Called to check if the next log message can still be written into the
   /// current log file.
   ///
   /// @param[in]  msg
   ///    The log message object.
   /// @param[in]  msg_text
   ///    The formatted text of the log message.
   /// @return
   ///    - \c true if the log message can be written into the current log file.
   ///    - \c false if a new file should be opened for this log message.
   /// @since  1.0.0, 13.12.2017
   virtual bool writeCheck( const detail::LogMsg& msg,
      const std::string& msg_text) = 0;

   /// Called after the log message was written into the log file. Can be used
   /// to adjust counters etc.
   ///
   /// @param[in]  msg
   ///    The log message object.
   /// @param[in]  msg_text
   ///    The formatted text of the log message that was written into the log
   ///    file.
   /// @since  1.0.0, 13.12.2017
   virtual void written( const detail::LogMsg& msg,
      const std::string& msg_text) = 0;

   /// Closes the currently open log file, calls rollFiles() to roll the log
   /// file generations, and finally opens a new log file.<br>
   /// This functions is called when either the openCheck() or writeCheck()
   /// function returned \c false.
   ///
   /// @since  1.0.0, 13.12.2017
   virtual void reOpenFile();

   /// Returns the current size of the log file.
   ///
   /// @return  The current size of the file.
   /// @since  1.11.0, 27.08.2018
   size_t fileSize();

   /// The definition how to build the file name.
   const filename::Definition  mFilenameDefinition;
   /// The path and filename of the currently open log file.
   std::string                 mCurrentLogfileName;
   /// The current log file.
   std::ofstream               mFile;

}; // PolicyBase


// inlined methods
// ===============


inline const std::string& PolicyBase::logFileName() const
{
   return mCurrentLogfileName;
} // PolicyBase::logFileName


} // namespace celma::log::files


#endif   // CELMA_LOG_POLICY_BASE_STUB


// =====  END OF policy_base.hpp  =====

