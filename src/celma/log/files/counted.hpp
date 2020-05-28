
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::files::Counted.


#ifndef CELMA_LOG_FILES_COUNTED_HPP
#define CELMA_LOG_FILES_COUNTED_HPP


#include <string>
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filename/definition.hpp"
#include "celma/log/files/policy_base.hpp"


namespace celma { namespace log { namespace files {


/// Log file policy that rolls a log file when it contains a specified number of
/// entries.
///
/// @since  1.11.0, 05.09.2018
class Counted: public PolicyBase
{
public:
   /// Constructor. Checks that the given log filename definition contains a log
   /// generation number.
   ///
   /// @param[in]  fname_def
   ///    Log filename definition.
   /// @param[in]  max_entries
   ///    The maximum number of entries to write into a log file.
   /// @param[in]  max_gen
   ///    Maximum number of log file generations to keep.
   /// @since  1.11.0, 05.09.2018
   Counted( const filename::Definition& fname_def, size_t max_entries,
      int max_gen) noexcept( false);

   /// Copying and moving not needed.
   /// @since  1.19.0, 06.12.2018  (deleted)
   /// @since  1.11.0, 05.09.2018
   Counted( const Counted&) = delete;
   Counted( Counted&&) = delete;

   /// Default destructor.
   ///
   /// @since  1.11.0, 05.09.2018
   ~Counted() override = default;

   /// Copying and moving not needed.
   Counted& operator =( const Counted&) = delete;
   Counted& operator =( Counted&&) = delete;

private:
   /// Checks the currently open file if it can still be used, i.e. it is empty.
   ///
   /// @return
   ///    \c true if the current log file can still be used, \c false if the log
   ///    file(s) should be rolled.
   /// @since  1.11.0, 05.09.2018
   bool openCheck() override;

   /// Called when openCheck() return \c false. Rolls the existing log file
   /// generations.
   ///
   /// @since  1.11.0, 05.09.2018
   void rollFiles() override;

   /// Called to check if the next log message can still be written into the
   /// current log file.<br>
   /// Here, checks if the maximum number of entries is not yet reached.
   ///
   /// @param[in]  msg
   ///    Ignored.
   /// @param[in]  msg_text
   ///    Ignored.
   /// @return
   ///    \c true if the log message can still be written into the current log
   ///    file.
   /// @since  1.11.0, 05.09.2018
   bool writeCheck( const detail::LogMsg& msg, const std::string& msg_text)
      override;

   /// Called after the log message was written into the log file. Here, updates
   /// the #mNumberOfEntries variable.
   ///
   /// @param[in]  msg
   ///    Ignored.
   /// @param[in]  msg_text
   ///    Ignored.
   /// @since  1.11.0, 05.09.2018
   void written( const detail::LogMsg& msg, const std::string& msg_text)
      override;

   /// Maximum number of entries to write into the log file.
   size_t  mMaxEntries;
   /// Current number of entries in the log file.
   size_t  mNumberOfEntries = 0;
   /// Maximum number of generations of log files to keep.
   int     mMaxGenerations;

}; // Counted


} // namespace files
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILES_COUNTED_HPP


// =====  END OF counted.hpp  =====

