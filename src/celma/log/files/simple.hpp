
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::files::Simple.


#pragma once


#include <string>
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/files/policy_base.hpp"


namespace celma::log::files {


/// The most simple case for writing log messages into a file:<br>
/// Open the file and write. No rolling, no generations, no nothing.
/// @since  1.0.0, 13.12.2017
class Simple final : public PolicyBase
{
public:
   /// Constructor.
   /// @param[in]  fname_def  The object used to create the file name.
   /// @since  1.0.0, 13.12.2017
   explicit Simple( const filename::Definition& fname_def);

   /// Copying and moving not needed.
   /// @since  1.19.0, 06.12.2018  (not needed)
   /// @since  1.0.0, 13.12.2017
   Simple( const Simple&) = delete;
   Simple( Simple&&) = delete;

   /// Default destructor.
   /// @since  1.0.0, 13.12.2017
   ~Simple() override = default;

   /// Copying and moving not needed.
   Simple& operator =( const Simple&) = delete;
   Simple& operator =( Simple&&) = delete;

private:
   /// Check if the currently opened file is valid for writing into.
   /// @return  Always \c true.
   /// @since  1.0.0, 13.12.2017
   bool openCheck() override;

   /// Checks if the next message can still be written into the current file.
   /// @param[in]  msg       The message object. Ignored.
   /// @param[in]  msg_text  The formatted text of the log message. Ignored.
   /// @return  Always \c true.
   /// @since  1.0.0, 13.12.2017
   bool writeCheck( const detail::LogMsg& msg, const std::string& msg_text)
      override;

   /// Called after the log message was written into the current log file. Does
   /// nothing in this class.
   /// @param[in]  msg       The message object. Ignored.
   /// @param[in]  msg_text  The formatted text of the log message. Ignored.
   /// @since  1.0.0, 13.12.2017
   void written( const detail::LogMsg& msg, const std::string& msg_text)
      override;

}; // Simple


} // namespace celma::log::files


// =====  END OF simple.hpp  =====

