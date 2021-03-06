
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::LogDestStream.


// module header file include
#include "celma/log/detail/log_dest_stream.hpp"


// C++ Standard Library incldudes
#include <iostream>


// project includes
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/detail/format_stream_default.hpp"


namespace celma { namespace log { namespace detail {



/// Constructor.<br>
/// A default stream formatter (FormatStreamDefault) is created for
/// formatting the log messages. Use setFormatter() to specify another
/// formatter if necessary.
///
/// @param[in]  dest  The stream to write into.
/// @since  1.24.1, 22.04.2019  (removed unused parameter add_newline)
/// @since  1.0.0, 19.06.2016
LogDestStream::LogDestStream( std::ostream& dest):
   mDest( dest),
   mpFormatter( new FormatStreamDefault())
{
} // LogDestStream::LogDestStream



/// Sets the new formatter to use.<br>
/// Although the pointer type is \a IFormatBase only, objects passed here
/// must be derived from the \a IFormatStream class.
/// @param[in]  formatter  Pointer to the new formatter object to use. If a
///                        NULL pointer is passed, the previous formatter is
///                        replaced by the default stream formatter.
/// @since  1.0.0, 19.06.2016
void LogDestStream::setFormatter( IFormatBase* formatter)
{

   mpFormatter.reset(
      (formatter == nullptr) ? new FormatStreamDefault() :
                               static_cast< IFormatStream*>( formatter));

} // LogDestStream::setFormatter



/// Called through the base class. Writes a log message to the specified
/// stream.
/// @param[in]  msg  The message to write.
/// @since  1.0.0, 19.06.2016
void LogDestStream::message( const LogMsg& msg)
{

   mpFormatter->formatMsg( mDest, msg);

} // LogDestStream::message



} // namespace detail
} // namespace log
} // namespace celma


// =====  END OF log_dest_stream.cpp  =====

