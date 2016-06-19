
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
/// See documentation of class celma::log::detail::LogFilterMaxLevel.


#ifndef CELMA_LOG_DETAIL_LOG_FILTER_MAX_LEVEL_HPP
#define CELMA_LOG_DETAIL_LOG_FILTER_MAX_LEVEL_HPP


#include "i_log_filter.hpp"
#include "log_msg.hpp"


namespace celma { namespace log { namespace detail {


/// Filter with a maximum log level.
/// @since  0.3, 19.06.2016
class LogFilterMaxLevel: public ILogFilter
{
public:
   /// Constructor.
   /// @param[in]  max_level  The maximum log level that is accepted.
   /// @since  0.3, 19.06.2016
   LogFilterMaxLevel( LogLevel max_level);

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
   virtual bool pass( const LogMsg& msg) const;

   /// The maximum log level.
   const LogLevel  mMaxLevel;

}; // LogFilterMaxLevel


// inlined methods
// ===============


inline LogFilterMaxLevel::LogFilterMaxLevel( LogLevel max_level):
   ILogFilter( ILogFilter::ftMaxLevel),
   mMaxLevel( max_level)
{
} // end LogFilterMaxLevel::LogFilterMaxLevel


bool LogFilterMaxLevel::processLevel( LogLevel l) const
{
   return l <= mMaxLevel;
} // end LogFilterMaxLevel::processLevel


inline bool LogFilterMaxLevel::pass( const LogMsg& msg) const
{
   return processLevel( msg.getLevel());
} // end LogFilterMaxLevel::pass


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_FILTER_MAX_LEVEL_HPP


// =====================  END OF log_filter_max_level.hpp  =====================

