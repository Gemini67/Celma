
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
/// See documentation of class celma::log::files::Simple.


#ifndef CELMA_LOG_FILES_SIMPLE_HPP
#define CELMA_LOG_FILES_SIMPLE_HPP


#include <string>
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/files/policy_base.hpp"


namespace celma { namespace log { namespace files {


/// The most simple case for writing log messages into a file:<br>
/// Open the file and write. No rolling, no generations, no nothing.
/// @since  1.0.0, 13.12.2017
class Simple: public PolicyBase
{
public:
   /// Constructor.
   /// @param[in]  fname_def  The object used to create the file name.
   /// @since  1.0.0, 13.12.2017
   Simple( const filename::Definition& fname_def);

   /// Copy constructor. Copies onle the definition.
   /// @param[in]  fname_def  The object used to create the file name.
   /// @since  1.0.0, 13.12.2017
   Simple( const Simple& other);

   /// Default destructor.
   /// @since  1.0.0, 13.12.2017
   virtual ~Simple() = default;

private:
   /// Check if the currently opened file is valid for writing into.
   /// @return  Always \c true.
   /// @since  1.0.0, 13.12.2017
   virtual bool openCheck() override;

   /// Does nothing. And should actually never be called anyway.
   /// @since  1.0.0, 13.12.2017
   virtual void rollFiles() override;

   /// Checks if the next message can still be written into the current file.
   /// @param[in]  msg       The message object. Ignored.
   /// @param[in]  msg_text  The formatted text of the log message. Ignored.
   /// @return  Always \c true.
   /// @since  1.0.0, 13.12.2017
   virtual bool writeCheck( const detail::LogMsg& msg,
      const std::string& msg_text) override;

   /// Called after the log message was written into the current log file. Does
   /// nothing in this class.
   /// @param[in]  msg       The message object. Ignored.
   /// @param[in]  msg_text  The formatted text of the log message. Ignored.
   /// @since  1.0.0, 13.12.2017
   virtual void written( const detail::LogMsg& msg,
      const std::string& msg_text) override;

}; // Simple


} // namespace files
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILES_SIMPLE_HPP


// ============================  END OF simple.hpp  ============================
