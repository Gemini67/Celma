
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
/// See documentation of class celma::log::detail::FormatStreamDefault.


// module header file include
#include "celma/log/detail/format_stream_default.hpp"


// C++ Standard Library includes
#include <iostream>


namespace celma { namespace log { namespace detail {



/// Implementation of the interface: Generate the log entry.
/// @param[out]  out  The stream to write the log entry into.
/// @param[in]   msg  The log message object with the data to log.
/// @since  0.3, 19.06.2016
void FormatStreamDefault::format( std::ostream& out, const LogMsg& msg) const
{

   out << msg.getProcessId() << '|' << msg.getFileName() << '|'
       << msg.getFunctionName() << '|' << msg.getLineNbr() << '|'
       << msg.getClass() << '|' << msg.getLevel() << '|'
       << msg.getErrorNbr() << '|' << msg.getText() << std::endl;

} // end FormatStreamDefault::format



} // namespace detail
} // namespace log
} // namespace celma


// ====================  END OF format_stream_default.cpp  ====================

