
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::LogFilterMaxLevel.


#pragma once


#include "celma/log/filter/detail/i_filter.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma::log::filter::detail {


/// Filter with a maximum log level.
/// @since  0.3, 19.06.2016
class LogFilterMaxLevel final : public IFilter
{
public:
   /// Constructor.
   /// @param[in]  max_level  The maximum log level that is accepted.
   /// @since  0.3, 19.06.2016
   explicit LogFilterMaxLevel( LogLevel max_level);

   ~LogFilterMaxLevel() override = default;

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
   bool pass( const log::detail::LogMsg& msg) const override;

   /// The maximum log level.
   const LogLevel  mMaxLevel;

}; // LogFilterMaxLevel


// inlined methods
// ===============


inline LogFilterMaxLevel::LogFilterMaxLevel( LogLevel max_level):
   IFilter( FilterTypes::maxLevel),
   mMaxLevel( max_level)
{
} // LogFilterMaxLevel::LogFilterMaxLevel


bool LogFilterMaxLevel::processLevel( LogLevel l) const
{
   return l <= mMaxLevel;
} // LogFilterMaxLevel::processLevel


inline bool LogFilterMaxLevel::pass( const log::detail::LogMsg& msg) const
{
   return processLevel( msg.getLevel());
} // LogFilterMaxLevel::pass


} // namespace celma::log::filter::detail


// =====  END OF log_filter_max_level.hpp  =====

