
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**
**
--*/


/// @file
/// See documentation of class celma::log::test::LogDestMsg.


#pragma once


#include "celma/log/detail/i_log_dest.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma::log::test {


/// Implementation of a log destination that copies the data of the log message
/// into another log message object.
/// @since  0.3, 19.06.2016
class LogDestMsg final : public detail::ILogDest
{
public:
   /// Constructor.
   /// @param[in]  dest  The log message object to copy the log message data into.
   /// @since  0.3, 19.06.2016
   explicit LogDestMsg( detail::LogMsg& dest):
      mDest( dest)
   {
   } // end LogDestMsg::MyLogDest

   /// Empty, virtual destructor.
   /// @since  0.3, 19.06.2016
   ~LogDestMsg() override = default;

private:
   /// Called through the base class. Stores the data of a log message in the
   /// specified object.
   /// @param[in]  msg  The message to store.
   /// @since  0.3, 19.06.2016
   void message( const detail::LogMsg& msg) override
   {
      mDest = msg;
   } // end LogDestMsg::message

   /// Used to store the log message.
   detail::LogMsg&  mDest;

}; // LogDestMsg


} // namespace celma::log::test


// =====  END OF test_log_dest_msg.hpp  =====

