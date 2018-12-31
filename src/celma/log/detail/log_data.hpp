
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


#ifndef CELMA_LOG_DETAIL_LOG_DATA_HPP
#define CELMA_LOG_DETAIL_LOG_DATA_HPP


#include <iosfwd>
#include <string>
#include "log_defs.hpp"


namespace celma { namespace log { namespace detail {


class Log;


/// Helper class to store all the data related to a log.
/// @since  0.3, 19.06.2016
class LogData
{
public:
   /// Constructor.
   /// @param[in]  log_id   The id of the log.
   /// @param[in]  name     The name of the log.
   /// @param[in]  log_obj  The Log object.
   /// @since  0.3, 19.06.2016
   LogData( id_t log_id, const std::string& name, Log* log_obj):
      mLogId( log_id),
      mName( name),
      mpLog( log_obj)
   {
   } // LogData::LogData

   /// Writes the information about this log to the stream.
   /// @param[in]  os  The stream to write into.
   /// @param[in]  ld  The object to dump the data of.
   /// @return  The stream as passed in.
   /// @since  0.3, 19.06.2016
   friend std::ostream& operator <<( std::ostream& os, const LogData& ld);

   /// The id of this log.
   id_t         mLogId;
   /// The name of this log.
   std::string  mName;
   /// Pointer to the log object.
   Log*         mpLog;

}; // LogData


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_DATA_HPP


// ===========================  END OF log_data.hpp  ===========================

