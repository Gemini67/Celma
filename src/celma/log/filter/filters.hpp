
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
/// See documentation of class celma::log::detail::Filters.


#ifndef CELMA_LOG_FILTER_FILTERS_HPP
#define CELMA_LOG_FILTER_FILTERS_HPP


#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/filter/detail/duplicate_policy.hpp"
#include "celma/log/filter/detail/i_duplicate_policy.hpp"
#include "celma/log/filter/detail/i_filter.hpp"


namespace celma { namespace log {


namespace detail {
class LogMsg;
}


namespace filter {


/// Class to store filter settings, which log messages should be processed.
///
/// @since  0.3, 19.06.2016
class Filters
{
public:
   /// Call this method to set the policy for handling duplicates when setting a
   /// filter policy. Default is to ignore duplicates, i.e. leave the existing
   /// filter as is.<br>
   /// This setting applies to all filter objects of all logs.
   ///
   /// @param[in]  policy  The policy how filter duplicates should be handled.
   /// @since  0.3, 19.06.2016
   static void setDuplicatePolicy( detail::DuplicatePolicy policy);

   /// Constructor.
   ///
   /// @since  0.3, 19.06.2016
   Filters();

   /// Destructor.
   ///
   /// @since  0.3, 19.06.2016
   ~Filters();

   /// Specifies a maximum log level to accept.
   ///
   /// @param[in]  max_log_level  The maximum log level to accept.
   /// @since  0.3, 19.06.2016
   void maxLevel( LogLevel max_log_level);

   /// Specifies a minimum log level to accept.
   ///
   /// @param[in]  min_log_level  The minimum log level to accept.
   /// @since  0.3, 19.06.2016
   void minLevel( LogLevel min_log_level);

   /// Specifies the single log level to accept.
   ///
   /// @param[in]  selected_log_level  The single log level to accept.
   /// @since  0.3, 19.06.2016
   void level( LogLevel selected_log_level);

   /// Specifies the list of log classes to accept.
   ///
   /// @param[in]  class_list  List of log classes to accept.
   /// @since  0.3, 19.06.2016
   void classes( const std::string& class_list);

   /// Returns if this message may be passed on.<br>
   /// Internally checks all filters if the message passed all of them.
   ///
   /// @param[in]  msg  The message to check.
   /// @return  \c true if the message passed all checks, i.e. may be passed on.
   /// @since  0.3, 19.06.2016
   bool pass( const log::detail::LogMsg& msg) const;

   /// Fast check method, if a message with a specific log level would be passed
   /// on to this log or not.
   ///
   /// @param[in]  l  The log level to check.
   /// @return  \c true if messages with this log level are processed.
   /// @since  0.3, 19.06.2016
   bool processLevel( LogLevel l) const;

private:
   /// Container type to store the filters.
   using FilterCont = std::vector< detail::IFilter*>;

   /// All filters should behave the same: duplicate handling policy handler.
   static boost::scoped_ptr< detail::IDuplicatePolicy>  mpDuplicatePolicy;

   /// Template method to check and set a new filter.
   ///
   /// @tparam  F
   ///    The type of the filter to set (class name).
   /// @tparam  FP
   ///    The type of the filter parameter to pass to the new filter object.
   /// @param[in]  filter_type
   ///    Filter type enum value, used to check if a filter of this type already
   ///    exists.
   /// @param[in]  filter_param
   ///    Value to pass to the new filter object.
   /// @since  0.3, 19.06.2016
   template< typename F, typename FP>
      void checkSetFilter( detail::IFilter::FilterTypes filter_type,
                           FP filter_param);

   /// Current filters.
   FilterCont        mFilters;
   /// Pointer to the filter for log level(s), if any.
   detail::IFilter*  mpLevelFilter;

}; // Filters


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILTER_FILTERS_HPP


// =====  END OF filters.hpp  =====

