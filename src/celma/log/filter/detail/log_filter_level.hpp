
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
/// See documentation of class celma::log::detail::LogFilterLevel.


#pragma once


#include "celma/log/filter/detail/i_filter.hpp"
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma::log::filter::detail {


/// Filter for a specific log level.
/// @since  0.3, 19.06.2016
class LogFilterLevel final : public IFilter
{
public:
   /// Constructor.
   /// @param[in]  ll  The log level to filter for.
   /// @since  0.3, 19.06.2016
   explicit LogFilterLevel( LogLevel ll);

   ~LogFilterLevel() override = default;

   /// Fast check: Returns if the specified log level may be processed.
   /// @param[in]  l  The log level to check.
   /// @return  \c true if this log level is accepted.
   /// @since  0.3, 19.06.2016
   bool processLevel( LogLevel l) const;

private:
   /// Method called through the base class ILogFilter: Checks if the log level
   /// of the message matches the specified log level to filter for.
   /// @param[in]  msg  The message to check the log level of.
   /// @return  \c true if the log level of the message is accepted.
   /// @since  0.3, 19.06.2016
   bool pass( const log::detail::LogMsg& msg) const override;

   /// The log level to filter.
   const LogLevel  mLevel;

}; // LogFilterLevel


// inlined methods
// ===============


inline LogFilterLevel::LogFilterLevel( LogLevel ll):
   IFilter( FilterTypes::level),
   mLevel( ll)
{
} // LogFilterLevel::LogFilterLevel


inline bool LogFilterLevel::processLevel( LogLevel l) const
{
   return l == mLevel;
} // LogFilterLevel::processLevel


inline bool LogFilterLevel::pass( const log::detail::LogMsg& msg) const
{
   return msg.getLevel() == mLevel;
} // LogFilterLevel::pass


} // namespace celma::log::filter::detail


// =====  END OF log_filter_level.hpp  =====

