
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
/// See documentation of class celma::log::detail::LogFilterMinLevel.


#ifndef CELMA_LOG_DETAIL_LOG_FILTER_MIN_LEVEL_HPP
#define CELMA_LOG_DETAIL_LOG_FILTER_MIN_LEVEL_HPP


#include "i_log_filter.hpp"
#include "log_msg.hpp"


namespace celma { namespace log { namespace detail {


/// Filter with a minimum log level.
/// @since  0.3, 19.06.2016
class LogFilterMinLevel: public ILogFilter
{
public:
   /// Constructor.
   /// @param[in]  min_level  The minimum log level that is accepted.
   /// @since  0.3, 19.06.2016
   LogFilterMinLevel( LogLevel min_level);

   /// Fast check: Returns if the specified log level may be processed.
   /// @param[in]  l  The log level to check.
   /// @return  \c true if this log level is accepted.
   /// @since  0.3, 19.06.2016
   bool processLevel( LogLevel l) const;

private:
   /// Method called through the base class ILogFilter: Checks if the log level
   /// of the message is in the range.
   /// @param[in]  msg  The message to check the log level of.
   /// @return  \c true if the log level of the message is accepted.
   /// @since  0.3, 19.06.2016
   virtual bool pass( const LogMsg& msg) const override;

   /// The minimum log level.
   const LogLevel  mMinLevel;

}; // LogFilterMinLevel


// inlined methods
// ===============


inline LogFilterMinLevel::LogFilterMinLevel( LogLevel min_level):
   ILogFilter( FilterTypes::minLevel),
   mMinLevel( min_level)
{
} // end LogFilterMinLevel::LogFilterMinLevel


bool LogFilterMinLevel::processLevel( LogLevel l) const
{
   return l >= mMinLevel;
} // end LogFilterMinLevel::processLevel


inline bool LogFilterMinLevel::pass( const LogMsg& msg) const
{
   return processLevel( msg.getLevel());
} // end LogFilterMinLevel::pass


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_FILTER_MIN_LEVEL_HPP


// =====================  END OF log_filter_min_level.hpp  =====================

