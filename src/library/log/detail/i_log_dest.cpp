
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
/// See documentation of class celma::log::detail::ILogDest.


// module header file include
#include "celma/log/detail/i_log_dest.hpp"


namespace celma { namespace log { namespace detail {



/// Call this function to pass a log message object to the message() method
/// of the derived class.
/// @param[in]  msg  The message to handle.
/// @since  0.3, 19.06.2016
void ILogDest::handleMessage( const LogMsg& msg)
{

   if (pass( msg))
      message( msg);

} // end ILogDest::handleMessage



/// Sets the new formatter to use. Does nothing in the base class.
/// @param[in]  formatter  Pointer to the new formatter object to use. If a
///                        NULL pointer is passed, the previous formatter is
///                        replaced by the default stream formatter.
/// @since  0.3, 19.06.2016
void ILogDest::setFormatter( IFormatBase*)
{
} // end ILogDest::setFormatter



} // namespace detail
} // namespace log
} // namespace celma


// ==========================  END OF i_log_dest.cpp  ==========================

