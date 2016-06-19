
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
/// See documentation of class celma::log::detail::LogFilter.


// module header file include
#include "celma/log/detail/log_filter.hpp"


// C++ Standard Library includes
#include <stdexcept>


// // project includes
#include "celma/common/clear_container.hpp"
#include "celma/log/detail/duplicate_policy_factory.hpp"
#include "celma/log/detail/i_log_filter.hpp"
#include "celma/log/detail/log_filter_classes.hpp"
#include "celma/log/detail/log_filter_level.hpp"
#include "celma/log/detail/log_filter_max_level.hpp"
#include "celma/log/detail/log_filter_min_level.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma { namespace log { namespace detail {




/// Template method to check and set a new filter.<br>
/// If it is a filter for the log level, also set the pointer to the filter
/// object.
/// @tparam  F   The type of the filter to set (class name).
/// @tparam  FP  The type of the filter parameter to pass to the new filter
///              object.
/// @param[in]  filter_type   Filter type enum value, used to check if a
///                           filter of this type already exists.
/// @param[in]  filter_param  Value to pass to the new filter object.
/// @since  0.3, 19.06.2016
template< typename F, typename FP>
   void LogFilter::checkSetFilter( detail::ILogFilter::FilterTypes filter_type,
                                   FP filter_param)
{

   // check if we already have a filter of the same type
   for (auto & it : mFilters)
   {
      if (it->filterType() == filter_type)
      {
         // yes, this filter already exists. replace it?
         if (mpDuplicatePolicy->acceptNew())
         {
            // policy: replace
            delete it;
            it = new F( filter_param);
         } // end if

         if (detail::ILogFilter::isLevelFilter( filter_type))
            mpLevelFilter = it;

         // replaced or not: no need to look further
         return;
      } // end if
   } // end for

   mFilters.push_back( new F( filter_param));

   if (detail::ILogFilter::isLevelFilter( filter_type))
      mpLevelFilter = mFilters.back();

} // end LogFilter::checkSetFilter



/// static class member initialisation
boost::scoped_ptr< detail::IDuplicatePolicy>  LogFilter::mpDuplicatePolicy;



/// Call this method to set the policy for handling duplicates when setting a
/// filter policy. Default is to ignore duplicates, i.e. leave the existing
/// filter as is.<br>
/// This settings applies to all filter objects of all logs.
/// @param[in]  policy  The policy how duplicates should be handled.
/// @since  0.3, 19.06.2016
void LogFilter::setDuplicatePolicy( DuplicatePolicy policy)
{

   if ((mpDuplicatePolicy.get() == nullptr) ||
       (mpDuplicatePolicy->policy() != policy))
      mpDuplicatePolicy.reset( detail::DuplicatePolicyFactory::createPolicy( policy));

} // end LogFilter::setDuplicatePolicy



/// Constructor.
/// @since  0.3, 19.06.2016
LogFilter::LogFilter():
   mFilters(),
   mpLevelFilter( nullptr)
{

   setDuplicatePolicy( dpIgnore);

} // end LogFilter::LogFilter



/// Destructor.
/// @since  0.3, 19.06.2016
LogFilter::~LogFilter()
{

   common::Vector::clear( mFilters);
   mpLevelFilter = nullptr;

} // end LogFilter::~LogFilter



/// Specifies a maximum log level to accept.
/// @param[in]  max_log_level  The maximum log level to accept.
/// @since  0.3, 19.06.2016
void LogFilter::maxLevel( LogLevel max_log_level)
{

   checkSetFilter< detail::LogFilterMaxLevel, LogLevel>
                 ( detail::ILogFilter::ftMaxLevel, max_log_level);

} // end LogFilter::maxLevel



/// Specifies a minimum log level to accept.
/// @param[in]  min_log_level  The minimum log level to accept.
/// @since  0.3, 19.06.2016
void LogFilter::minLevel( LogLevel min_log_level)
{

   checkSetFilter< detail::LogFilterMinLevel, LogLevel>
                 ( detail::ILogFilter::ftMinLevel, min_log_level);

} // end LogFilter::minLevel



/// Specifies the single log level to accept.
/// @param[in]  selected_log_level  The single log level to accept.
/// @since  0.3, 19.06.2016
void LogFilter::level( LogLevel selected_log_level)
{

   checkSetFilter< detail::LogFilterLevel, LogLevel>
                 ( detail::ILogFilter::ftLevel, selected_log_level);

} // end LogFilter::level



/// Specifies the list of log classes to accept.
/// @param[in]  class_list  List of log classes to accept.
/// @since  0.3, 19.06.2016
void LogFilter::classes( const std::string& class_list)
{

   checkSetFilter< detail::LogFilterClasses, std::string>
                 ( detail::ILogFilter::ftClasses, class_list);

} // end LogFilter::classes



/// Returns if this message may be passed on.<br>
/// Internally checks all filters if the message passed all of them.
/// @param[in]  msg  The message to check.
/// @return  \c true if the message passed all checks, i.e. may be passed on.
/// @since  0.3, 19.06.2016
bool LogFilter::pass( const LogMsg& msg) const
{

   for (auto it : mFilters)
   {
      if (!it->passFilter( msg))
         return false;
   } // end for

   return true;
} // end LogFilter::pass



/// Fast check method, if a message with a specific log level would be passed
/// on to this log or not.
/// @param[in]  l  The log level to check.
/// @return  \c true if messages with this log level are processed.
/// @since  0.3, 19.06.2016
bool LogFilter::processLevel( LogLevel l) const
{

   // no filter: yes, process
   if (mpLevelFilter == nullptr)
      return true;

   if (mpLevelFilter->filterType() == detail::ILogFilter::ftMaxLevel)
      return static_cast< detail::LogFilterMaxLevel*>( mpLevelFilter)->processLevel( l);

   // only two types of level filter exist, so ...
   return static_cast< detail::LogFilterLevel*>( mpLevelFilter)->processLevel( l);
} // end LogFilter::processLevel



} // namespace detail
} // namespace log
} // namespace celma


// ==========================  END OF log_filter.cpp  ==========================

