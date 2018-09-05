
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


#ifndef CELMA_LOG_FILES_POLICY_BASE_HPP
#define CELMA_LOG_FILES_POLICY_BASE_HPP


#ifdef CELMA_LOG_POLICY_BASE_STUB
#include "celma/test/stubs/policy_base_stub.hpp"
#define  PolicyBase  PolicyBaseStub
#else


#include <fstream>
#include <string>
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/definition.hpp"


namespace celma { namespace log { namespace files {


/// Base class for log file handle policies. Contains the part common to all
/// policies.
/// @since  x.y.z, 27.08.2018  (renamed from PolicyBase)
/// @since  1.0.0, 13.12.2017
class PolicyBase
{
public:
   /// Constructor. Stores the object to use to create the log file names.
   /// @param[in]  fname_def  Log filename definition.
   /// @since  1.0.0, 13.12.2017
   PolicyBase( const filename::Definition& fname_def);

   /// Copy constructor. Only copies the log filename definition, not any
   /// eventually open log file.
   /// @param[in]  other  The other object to copy the data from.
   /// @since  1.0.0, 13.12.2017
   PolicyBase( const PolicyBase& other);

   /// Default, virtual destructor.
   /// @since  1.0.0, 13.12.2017
   virtual ~PolicyBase() = default;

   /// Opens the current log file, checks if it still is okay to use the file,
   /// if not closes the file again, rolls the log file generations and opens
   /// a new file.<br>
   /// All that is done calling the virtual function which must be implemented
   /// by the derived classes, the real policies.
   /// @since  1.0.0, 13.12.2017
   void open() noexcept( false);

   /// Write the next log message. Either in the currently opened file, if that
   /// is still valid, or rolls the log file generations and writes into a
   /// newly opened file.
   /// @param[in]  msg       The log message object with the data of the log
   ///                       message to write into the file.<br>
   ///                       Provided e.g. for date checks.
   /// @param[in]  msg_text  The formatted text of the log message to write.
   /// @since  1.0.0, 13.12.2017
   void writeMessage( const detail::LogMsg& msg, const std::string& msg_text);

   /// Returns the path and file name of the currently open log file.
   /// @return  The path and file name of the currently open log file.
   /// @since  1.0.0, 22.12.2017
   const std::string& logFileName() const;

protected:
   /// Check if the currently opened log file is valid for writing into.
   /// @return
   /// - \c true if it is (still) okay to write into the current log file.
   /// - \c false if a new log file should be opened.
   /// @since  1.0.0, 13.12.2017
   virtual bool openCheck() = 0;

   /// Called when openCheck() returned \c false. The current file is already
   /// closed then, all the function has to do is roll the log file generations.
   /// @since  1.0.0, 13.12.2017
   virtual void rollFiles() = 0;

   /// Called to check if the next log message can still be written into the
   /// current log file.
   /// @param[in]  msg       The log message object.
   /// @param[in]  msg_text  The formatted text of the log message.
   /// @return  \c true if the log message can be written into the current log
   ///          file, \c false if a new file should be opened for this log
   ///          message.
   /// @since  1.0.0, 13.12.2017
   virtual bool writeCheck( const detail::LogMsg& msg,
      const std::string& msg_text) = 0;

   /// Called after the log message was written into the log file. Can be used
   /// to adjust counters etc.
   /// @param[in]  msg       The log message object.
   /// @param[in]  msg_text  The formatted text of the log message that was
   ///                       written into the log file.
   /// @since  1.0.0, 13.12.2017
   virtual void written( const detail::LogMsg& msg,
      const std::string& msg_text) = 0;

   /// Closes the currently open log file, calls rollFiles() to roll the log
   /// file generations, and finally opens a new log file.<br>
   /// This functions is called when either the openCheck() or writeCheck()
   /// function returned \c false.
   /// @since  1.0.0, 13.12.2017
   virtual void reOpenFile();

   /// Returns the current size of the log file.
   ///
   /// @return  The current size of the file.
   /// @since  x.y.z, 27.08.2018
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


} // namespace files
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_POLICY_BASE_STUB
#endif   // CELMA_LOG_FILES_POLICY_BASE_HPP


// =====  END OF policy_base.hpp  =====

