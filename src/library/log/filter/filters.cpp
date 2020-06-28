
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
/// See documentation of class celma::log::filter::Filters.


// module header file include
#include "celma/log/filter/filters.hpp"


// C++ Standard Library includes
#include <stdexcept>


// // project includes
#include "celma/container/clear_container.hpp"
#include "celma/format/to_string.hpp"
#include "celma/log/detail/log_msg.hpp"
#include "celma/log/filter/detail/duplicate_policy_factory.hpp"
#include "celma/log/filter/detail/log_filter_classes.hpp"
#include "celma/log/filter/detail/log_filter_level.hpp"
#include "celma/log/filter/detail/log_filter_max_level.hpp"
#include "celma/log/filter/detail/log_filter_min_level.hpp"


namespace celma::log::filter {



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
   void Filters::checkSetFilter( detail::IFilter::FilterTypes filter_type,
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

         if (detail::IFilter::isLevelFilter( filter_type))
            mpLevelFilter = it;

         // replaced or not: no need to look further
         return;
      } // end if
   } // end for

   mFilters.push_back( new F( filter_param));

   if (detail::IFilter::isLevelFilter( filter_type))
      mpLevelFilter = mFilters.back();

} // Filters::checkSetFilter



/// static class member initialisation
boost::scoped_ptr< detail::IDuplicatePolicy>  Filters::mpDuplicatePolicy;



/// Call this method to set the policy for handling duplicates when setting a
/// filter policy. Default is to ignore duplicates, i.e. leave the existing
/// filter as is.<br>
/// This settings applies to all filter objects of all logs.
///
/// @param[in]  policy  The policy how duplicates should be handled.
/// @since  0.3, 19.06.2016
void Filters::setDuplicatePolicy( detail::DuplicatePolicy policy)
{

   if ((mpDuplicatePolicy.get() == nullptr)
       || (mpDuplicatePolicy->policy() != policy))
      mpDuplicatePolicy.reset( detail::DuplicatePolicyFactory::createPolicy( policy));

} // Filters::setDuplicatePolicy



/// Constructor.
///
/// @since  0.3, 19.06.2016
Filters::Filters():
   mFilters(),
   mpLevelFilter( nullptr)
{

   setDuplicatePolicy( detail::DuplicatePolicy::ignore);

} // Filters::Filters



/// Destructor.
///
/// @since  0.3, 19.06.2016
Filters::~Filters()
{

   container::Vector::clear( mFilters);
   mpLevelFilter = nullptr;

} // Filters::~Filters



/// Specifies a maximum log level to accept.
///
/// @param[in]  max_log_level  The maximum log level to accept.
/// @since  0.3, 19.06.2016
void Filters::maxLevel( LogLevel max_log_level)
{

   checkSetFilter< detail::LogFilterMaxLevel, LogLevel>
                 ( detail::IFilter::FilterTypes::maxLevel, max_log_level);

} // Filters::maxLevel



/// Specifies a minimum log level to accept.
///
/// @param[in]  min_log_level  The minimum log level to accept.
/// @since  0.3, 19.06.2016
void Filters::minLevel( LogLevel min_log_level)
{

   checkSetFilter< detail::LogFilterMinLevel, LogLevel>
                 ( detail::IFilter::FilterTypes::minLevel, min_log_level);

} // Filters::minLevel



/// Specifies the single log level to accept.
///
/// @param[in]  selected_log_level  The single log level to accept.
/// @since  0.3, 19.06.2016
void Filters::level( LogLevel selected_log_level)
{

   checkSetFilter< detail::LogFilterLevel, LogLevel>
                 ( detail::IFilter::FilterTypes::level, selected_log_level);

} // Filters::level



/// Specifies the list of log classes to accept.
///
/// @param[in]  class_list  List of log classes to accept.
/// @since  0.3, 19.06.2016
void Filters::classes( const std::string& class_list)
{

   checkSetFilter< detail::LogFilterClasses, std::string>
                 ( detail::IFilter::FilterTypes::classes, class_list);

} // Filters::classes



/// Returns if this message may be passed on.<br>
/// Internally checks all filters if the message passed all of them.
///
/// @param[in]  msg  The message to check.
/// @return  \c true if the message passed all checks, i.e. may be passed on.
/// @since  0.3, 19.06.2016
bool Filters::pass( const log::detail::LogMsg& msg) const
{

   for (auto & it : mFilters)
   {
      if (!it->passFilter( msg))
         return false;
   } // end for

   return true;
} // Filters::pass



/// Fast check method, if a message with a specific log level would be passed
/// on to this log or not.
///
/// @param[in]  l  The log level to check.
/// @return  \c true if messages with this log level are processed.
/// @since  0.3, 19.06.2016
bool Filters::processLevel( LogLevel l) const
{

   // no filter: yes, process
   if (mpLevelFilter == nullptr)
      return true;

   switch (mpLevelFilter->filterType())
   {
   case detail::IFilter::FilterTypes::maxLevel:
      return static_cast< detail::LogFilterMaxLevel*>( mpLevelFilter)
         ->processLevel( l);
   case detail::IFilter::FilterTypes::minLevel:
      return static_cast< detail::LogFilterMinLevel*>( mpLevelFilter)
         ->processLevel( l);
   case detail::IFilter::FilterTypes::level:
      return static_cast< detail::LogFilterLevel*>( mpLevelFilter)
         ->processLevel( l);
   default:
      throw std::invalid_argument( "wrong level filter type "
         + format::toString( static_cast< int>( mpLevelFilter->filterType())));
   } // end switch

   return true;
} // Filters::processLevel



} // namespace celma::log::filter


// =====  END OF filters.cpp  =====

