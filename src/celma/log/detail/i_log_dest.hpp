
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::


#ifndef CELMA_LOG_DETAIL_I_LOG_DEST_HPP
#define CELMA_LOG_DETAIL_I_LOG_DEST_HPP


#include "celma/log/detail/i_format_base.hpp"
#include "celma/log/detail/log_filter.hpp"


namespace celma { namespace log { namespace detail {


class LogMsg;


/// Interface for log destinations using the template method:<br>
/// ILogDest::handleMessage() is public and internally calls
/// ILogDest::message(), which is implemented by the derived class(es).
/// @todo  Move to detail.
/// @since  0.3, 19.06.2016
class ILogDest: public LogFilter
{
public:
   /// Empty, virtual destructor.
   /// @since  0.3, 19.06.2016
   virtual ~ILogDest() { }

   /// Call this function to pass a log message object to the message() method
   /// of the derived class.
   /// @param[in]  msg  The message to handle.
   /// @since  0.3, 19.06.2016
   void handleMessage( const LogMsg& msg);

   /// Sets the new formatter to use. Does nothing in the base class.
   /// @param[in]  formatter  Pointer to the new formatter object to use. If a
   ///                        NULL pointer is passed, the previous formatter is
   ///                        replaced by the default stream formatter.
   /// @since  0.3, 19.06.2016
   virtual void setFormatter( IFormatBase* formatter = nullptr);

private:
   /// Interface: Must be implemented by the derived class(es).
   /// @param[in]  msg  The message to process.
   /// @since  0.3, 19.06.2016
   virtual void message( const LogMsg& msg) = 0;

}; // ILogDest


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_I_LOG_DEST_HPP


// ==========================  END OF i_log_dest.hpp  ==========================

