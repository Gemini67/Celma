
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
/// See documentation of class celma::log::detail::LogData.


// module header file include
#include "celma/log/detail/log_data.hpp"


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/log/detail/log.hpp"


namespace celma { namespace log { namespace detail {



/// Writes the information about this log to the stream.
/// @param[in]  os  The stream to write into.
/// @param[in]  ld  The object to dump the data of.
/// @return  The stream as passed in.
/// @since  0.3, 19.06.2016
std::ostream& operator <<( std::ostream& os, const LogData& ld)
{

   os << "   log id = " << std::hex << ld.mLogId << ", name = '" << ld.mName
      << ":" << std::endl
      << *ld.mpLog << std::endl;

   return os;
} // end operator <<



} // namespace detail
} // namespace log
} // namespace celma


// ===========================  END OF log_data.cpp  ===========================

