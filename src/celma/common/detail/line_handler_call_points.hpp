
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of enum  celma::common::detail::LineHandlerCallPoints.


#ifndef CELMA_COMMON_DETAIL_LINE_HANDLER_CALL_POINTS_HPP
#define CELMA_COMMON_DETAIL_LINE_HANDLER_CALL_POINTS_HPP


namespace celma { namespace common { namespace detail {


/// Symbolic names for the statistic call points used by the class TextFile.
/// @since  1.3.0, 13.04.2016
enum class LineHandlerCallPoints
{
   lineRead,       //!< Line read from the file.
   lineFiltered,   //!< Line ignored due to the filter.
   lineProcessed   //!< Line actually processed (returned by the iterator).
}; // LineHandlerCallPoints


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_LINE_HANDLER_CALL_POINTS_HPP


// =====  END OF line_handler_call_points.hpp  =====

