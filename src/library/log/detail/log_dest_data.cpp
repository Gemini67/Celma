
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
/// See documentation of class celma::log::detail::LogDestData.


// module header file include
#include "celma/log/detail/log_dest_data.hpp"


// C++ Standard Library includs
#include <iostream>


namespace celma { namespace log { namespace detail {



/// Writes information about a log destination.
///
/// @param[in]  os
///    The stream to write into.
/// @param[in]  l
///    The log destination to dump the information of.
/// @return  The stream as passed in.
/// @since  1.0.0, 19.06.2016
std::ostream& operator <<( std::ostream& os, const LogDestData& l)
{

   return os << "log dest name: " << l.mName << std::endl;
} // operator <<



} // namespace detail
} // namespace log
} // namespace celma


// =====  END OF log_dest_data.cpp  =====

