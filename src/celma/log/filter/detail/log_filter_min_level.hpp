
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
/// See documentation of class celma::log::detail::LogFilterMinLevel.


#pragma once


#include "celma/log/filter/detail/i_filter.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma::log::filter::detail {


/// Filter with a minimum log level.
/// @since  0.3, 19.06.2016
class LogFilterMinLevel final : public IFilter
{
public:
   /// Constructor.
   /// @param[in]  min_level  The minimum log level that is accepted.
   /// @since  0.3, 19.06.2016
   explicit LogFilterMinLevel( LogLevel min_level);

   // default destructor is fine
   ~LogFilterMinLevel() override = default;

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

   /// The minimum log level.
   const LogLevel  mMinLevel;

}; // LogFilterMinLevel


// inlined methods
// ===============


inline LogFilterMinLevel::LogFilterMinLevel( LogLevel min_level):
   IFilter( FilterTypes::minLevel),
   mMinLevel( min_level)
{
} // LogFilterMinLevel::LogFilterMinLevel


bool LogFilterMinLevel::processLevel( LogLevel l) const
{
   return l >= mMinLevel;
} // LogFilterMinLevel::processLevel


inline bool LogFilterMinLevel::pass( const log::detail::LogMsg& msg) const
{
   return processLevel( msg.getLevel());
} // LogFilterMinLevel::pass


} // namespace celma::log::filter::detail


// =====  END OF log_filter_min_level.hpp  =====

