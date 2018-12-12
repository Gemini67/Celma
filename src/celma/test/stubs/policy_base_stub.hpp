
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::files::PolicyBaseStub.


#ifndef CELMA_TEST_STUBS_POLICY_BASE_STUB_HPP
#define CELMA_TEST_STUBS_POLICY_BASE_STUB_HPP


#include <string>
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/definition.hpp"
#include "celma/log/filename/builder.hpp"


namespace celma { namespace log { namespace files {


/// Stub of the base class for log file handle policies. Provides the same
/// interface as the original class celma::log::files::PolicyBase, but contains
/// the functionality needed for unit tests.
///
/// @since  1.11.0, 27.08.2018  (copied from PolicyBase)
class PolicyBaseStub
{
public:
   /// Constructor. Stores the object to use to create the log file names.
   ///
   /// @param[in]  fname_def  Log filename definition.
   /// @since  1.11.0, 27.08.2018
   explicit PolicyBaseStub( const filename::Definition& fname_def);

   /// Copying and moving not needed.
   /// @since  x.y.z, 06.12.2018  (deleted)
   /// @since  1.11.0, 27.08.2018
   PolicyBaseStub( const PolicyBaseStub&) = delete;
   PolicyBaseStub( PolicyBaseStub&&) = delete;

   /// Default, virtual destructor.
   ///
   /// @since  1.11.0, 27.08.2018
   virtual ~PolicyBaseStub() = default;

   /// Copying and moving not needed.
   PolicyBaseStub& operator =( const PolicyBaseStub&) = delete;
   PolicyBaseStub& operator =( PolicyBaseStub&&) = delete;

   /// Opens the current log file, checks if it still is okay to use the file,
   /// if not closes the file again, rolls the log file generations and opens
   /// a new file.<br>
   /// All that is done calling the virtual function which must be implemented
   /// by the derived classes, the real policies.
   ///
   /// @since  1.11.0, 27.08.2018
   void open() noexcept( false);

   /// Write the next log message. Either in the currently opened file, if that
   /// is still valid, or rolls the log file generations and writes into a
   /// newly opened file.
   ///
   /// @param[in]  msg
   ///    The log message object with the data of the log message to write into
   ///    the file.<br>
   ///    Provided e.g. for date checks.
   /// @param[in]  msg_text
   ///    The formatted text of the log message to write.
   /// @since  1.11.0, 27.08.2018
   void writeMessage( const detail::LogMsg& msg, const std::string& msg_text);

   /// Returns the path and file name of the currently open log file.
   ///
   /// @return  The path and file name of the currently open log file.
   /// @since  1.11.0, 27.08.2018
   const std::string& logFileName() const;

   // functions of the stub

   /// Returns the current value of the #mOpenCalled flag and resets it
   /// afterwards.
   ///
   /// @return  \c true when open() was called.
   /// @since  1.11.0, 29.08.2018
   bool getResetOpenCalled();

   /// Returns the current value of the #mRollFilesCalled flag and resets it
   /// afterwards.
   ///
   /// @return  \c true when rollFiles() was called.
   /// @since  1.11.0, 29.08.2018
   bool getResetRollFilesCalled();

   /// Returns the current value of the #mReOpenCalled flag and resets it
   /// afterwards.
   ///
   /// @return  \c true when reOpenFile() was called.
   /// @since  1.11.0, 29.08.2018
   bool getResetReOpenCalled();

   /// Returns the simulated size of the logfile.
   ///
   /// @return
   ///    The simulated size of the logfile, computed by the cumulated lengths
   ///    of the log messages as specified in the log message text.
   /// @since  1.11.0, 29.08.2018
   size_t logFileSize() const;

protected:
   /// Check if the currently opened log file is valid for writing into.
   ///
   /// @return
   /// - \c true if it is (still) okay to write into the current log file.
   /// - \c false if a new log file should be opened.
   /// @since  1.11.0, 27.08.2018
   virtual bool openCheck() = 0;

   /// Called when openCheck() returned \c false. The current file is already
   /// closed then, all the function has to do is roll the log file generations.
   ///
   /// @since  1.11.0, 27.08.2018
   virtual void rollFiles();

   /// Called to check if the next log message can still be written into the
   /// current log file.
   ///
   /// @param[in]  msg
   ///    The log message object.
   /// @param[in]  msg_text
   ///    The formatted text of the log message.
   /// @return
   ///    \c true if the log message can be written into the current log file,
   ///    \c false if a new file should be opened for this log  message.
   /// @since  1.11.0, 27.08.2018
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
   /// @since  1.11.0, 27.08.2018
   virtual void written( const detail::LogMsg& msg,
      const std::string& msg_text) = 0;

   /// Closes the currently open log file, calls rollFiles() to roll the log
   /// file generations, and finally opens a new log file.<br>
   /// This functions is called when either the openCheck() or writeCheck()
   /// function returned \c false.
   ///
   /// @since  1.11.0, 27.08.2018
   virtual void reOpenFile();

   /// Returns the current size of the file.
   ///
   /// @return  The current size of the log file.
   /// @since  1.11.0, 27.08.2018
   size_t fileSize() const;

   /// The definition how to build the file name.
   const filename::Definition  mFilenameDefinition;
   /// The path and filename of the currently open log file.
   std::string                 mCurrentLogfileName;
   /// Set when open() is called.
   bool                        mOpenCalled = false;
   /// Set when rollFiles() is called.
   bool                        mRollFilesCalled = false;
   /// Set when reOpenFile() is called.
   bool                        mReOpenCalled = false;
   /// The current size of the "log file".
   size_t                      mLogFileSize = 0;
   /// Set this flag if the internal log file size should be reset to 0 when
   /// 
///   bool                        mResetFilesizeBe4openCheck = false;

}; // PolicyBaseStub


// inlined methods
// ===============


inline const std::string& PolicyBaseStub::logFileName() const
{
   return mCurrentLogfileName;
} // PolicyBaseStub::logFileName


inline bool PolicyBaseStub::getResetOpenCalled()
{
   if (mOpenCalled)
   {
      mOpenCalled = false;
      return true;
   } // end if
   return false;
} // PolicyBaseStub::getResetOpenCalled


inline bool PolicyBaseStub::getResetRollFilesCalled()
{
   if (mRollFilesCalled)
   {
      mRollFilesCalled = false;
      return true;
   } // end if
   return false;
} // PolicyBaseStub::getResetRollFilesCalled


inline bool PolicyBaseStub::getResetReOpenCalled()
{
   if (mReOpenCalled)
   {
      mReOpenCalled = false;
      return true;
   } // end if
   return false;
} // PolicyBaseStub::getResetReOpenCalled


inline size_t PolicyBaseStub::logFileSize() const
{
  return mLogFileSize;
} // PolicyBaseStub::logFileSize


inline PolicyBaseStub::PolicyBaseStub( const filename::Definition& fname_def):
   mFilenameDefinition( fname_def),
   mCurrentLogfileName()
{
} // PolicyBaseStub::PolicyBaseStub


inline void PolicyBaseStub::open()
{

   const auto  filename = filename::Builder::filename( mFilenameDefinition);


   mCurrentLogfileName = filename;

   if (!openCheck())
   {
      mReOpenCalled = true;
      reOpenFile();
   } // end if

   mOpenCalled = true;
   mLogFileSize = 0;

} // PolicyBaseStub::open


inline void PolicyBaseStub::writeMessage( const detail::LogMsg& msg,
   const std::string& msg_text)
{

   if (!writeCheck( msg, msg_text))
   {
      mReOpenCalled = true;
      reOpenFile();
   } // end if

   mLogFileSize += msg_text.length();

   written( msg, msg_text);

} // PolicyBaseStub::writeMessage


inline void PolicyBaseStub::rollFiles()
{
} // PolicyBaseStub::rollFiles


inline void PolicyBaseStub::reOpenFile()
{

   rollFiles();
   mRollFilesCalled = true;
   mLogFileSize = 0;

   open();

} // PolicyBaseStub::reOpenFile


inline size_t PolicyBaseStub::fileSize() const
{
   return mLogFileSize;
}


} // namespace files
} // namespace log
} // namespace celma


#endif   // CELMA_TEST_STUBS_POLICY_BASE_STUB_HPP


// =====  END OF policy_base_stub.hpp  =====

