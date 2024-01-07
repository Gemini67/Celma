
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
/// See documentation of enum celma::common::detail::LineHandlerCallPoints.


#pragma once


#include <cstdint>


namespace celma::common::detail {


/// Symbolic names for the statistic call points used by the class TextFile.
/// @since  1.3.0, 13.04.2016
enum class LineHandlerCallPoints : uint8_t
{
   lineRead,       //!< Line read from the file.
   lineFiltered,   //!< Line ignored due to the filter.
   lineProcessed   //!< Line actually processed (returned by the iterator).
}; // LineHandlerCallPoints


} // namespace celma::common::detail


// =====  END OF line_handler_call_points.hpp  =====

