
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
/// See documentation of class celma::log::files::MaxSize.


#ifndef CELMA_LOG_FILES_MAX_SIZE_HPP
#define CELMA_LOG_FILES_MAX_SIZE_HPP


#include <string>
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/definition.hpp"
#include "celma/log/files/policy_base.hpp"


namespace celma { namespace log { namespace files {


/// Log file policy that ensures a maximum log file size.
///
/// @since  1.0.0, 13.12.2017
class MaxSize: public PolicyBase
{
public:
   /// Constructor. Checks that the given log filename definition contains a log
   /// generation number.
   ///
   /// @param[in]  fname_def
   ///    Log filename definition.
   /// @param[in]  max_file_size
   ///    The maximum size of a log file.
   /// @param[in]  max_gen
   ///    Maximum number of log file generations to keep.
   /// @since  1.0.0, 13.12.2017
   MaxSize( const filename::Definition& fname_def, size_t max_file_size,
      int max_gen) noexcept( false);

   /// Copying and moving not needed.
   /// @since  1.19.0, 06.12.2018  (deleted)
   /// @since  1.0.0, 13.12.2017
   MaxSize( const MaxSize&) = delete;
   MaxSize( MaxSize&&) = delete;

   /// Default destructor.
   /// @since  1.0.0, 13.12.2017
   virtual ~MaxSize() = default;

   /// Copying and moving not needed.
   MaxSize& operator =( const MaxSize&) = delete;
   MaxSize& operator =( MaxSize&&) = delete;

private:
   /// Checks the currently open file if the file limit is reached.
   ///
   /// @return
   ///    \c true if the current log file can still be used, \c false if the log
   ///    file(s) should be rolled.
   /// @since  1.0.0, 13.12.2017
   virtual bool openCheck() override;

   /// Called when openCheck() return \c false. Rolls the existing log file
   /// generations.
   ///
   /// @since  1.0.0, 13.12.2017
   virtual void rollFiles() override;

   /// Called to check if the next log message can still be written into the
   /// current log file.<br>
   /// Here, checks if the log file size still allows to write the given log
   /// message into the file.
   ///
   /// @param[in]  msg
   ///    Ignored.
   /// @param[in]  msg_text
   ///    The formatted text of the log message.
   /// @return
   ///    \c true if the log message text can be written into the current log
   ///    file.
   /// @since  1.0.0, 13.12.2017
   virtual bool writeCheck( const detail::LogMsg& msg,
      const std::string& msg_text) override;

   /// Called after the log message was written into the log file. Here, updates
   /// the #mCurrentFilesize variable.
   ///
   /// @param[in]  msg
   ///    Ignored.
   /// @param[in]  msg_text
   ///    The formatted text of the log message that was written into the log
   ///    file.
   /// @since  1.0.0, 13.12.2017
   virtual void written( const detail::LogMsg& msg,
      const std::string& msg_text) override;

   /// Maximum size of one logfile.
   size_t  mMaxFileSize;
   /// Size of the current file.
   size_t  mCurrentFilesize = 0;
   /// Maximum number of generations of log files to keep.
   int     mMaxGenerations;

}; // MaxSize


} // namespace files
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILES_MAX_SIZE_HPP


// =====  END OF max_size.hpp  =====

