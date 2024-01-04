
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::ILogDest.


#pragma once


#include "celma/log/filter/filters.hpp"


namespace celma::log::detail {


class IFormatBase;
class LogMsg;


/// Interface for log destinations using the template method:<br>
/// ILogDest::handleMessage() is public and internally calls
/// ILogDest::message(), which is implemented by the derived class(es).
/// @since  1.0.0, 19.06.2016
class ILogDest: public filter::Filters
{
public:
   /// Empty, virtual destructor.
   /// @since  1.0.0, 19.06.2016
   virtual ~ILogDest() = default;

   /// Call this function to pass a log message object to the message() method
   /// of the derived class.
   /// @param[in]  msg  Message to handle.
   /// @since  1.0.0, 19.06.2016
   void handleMessage( const LogMsg& msg);

   /// Sets the new formatter to use. Does nothing in the base class.
   /// @param[in]  formatter  Pointer to the new formatter object to use. If a
   ///                        NULL pointer is passed, the previous formatter is
   ///                        replaced by the default stream formatter.
   /// @since  1.0.0, 19.06.2016
   virtual void setFormatter( IFormatBase* formatter = nullptr);

private:
   /// Interface: Must be implemented by derived class(es).
   /// @param[in]  msg  Message to process.
   /// @since  1.0.0, 19.06.2016
   virtual void message( const LogMsg& msg) = 0;

}; // ILogDest


} // namespace celma::log::detail


// =====  END OF i_log_dest.hpp  =====

