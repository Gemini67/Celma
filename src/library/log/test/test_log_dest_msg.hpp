
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**
**
--*/


/// @file
/// See documentation of class celma::log::test::@@@.


#ifndef CELMA_LOG_TEST_TEST_LOG_DEST_MSG_HPP
#define CELMA_LOG_TEST_TEST_LOG_DEST_MSG_HPP


#include "celma/log/detail/i_log_dest.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace test {


/// Implementation of a log destination that copies the data of the log message
/// into another log message object.
/// @since  0.3, 19.06.2016
class LogDestMsg: public detail::ILogDest
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
   virtual ~LogDestMsg() { }

private:
   /// Called through the base class. Stores the data of a log message in the
   /// specified object.
   /// @param[in]  msg  The message to store.
   /// @since  0.3, 19.06.2016
   virtual void message( const detail::LogMsg& msg)
   {
      mDest = msg;
   } // end LogDestMsg::message

   /// Used to store the log message.
   detail::LogMsg&  mDest;

}; // LogDestMsg


} // namespace test
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_TEST_TEST_LOG_DEST_MSG_HPP


// ======================  END OF test_log_dest_msg.hpp  ======================

