
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
/// See documentation of class celma::log::detail::LogFilterClasses.


#ifndef CELMA_LOG_DETAIL_LOG_FILTER_CLASSES_HPP
#define CELMA_LOG_DETAIL_LOG_FILTER_CLASSES_HPP


#include <bitset>
#include "i_log_filter.hpp"
#include "log_defs.hpp"
#include "log_msg.hpp"


namespace celma { namespace log { namespace detail {


/// Filter on log classes.
/// @since  0.3, 19.06.2016
class LogFilterClasses: public ILogFilter
{
public:
   /// Constructor, initialises the set of log classes to accept.
   /// @param[in]  class_list  The list of log class names to filter for.
   /// @since  0.3, 19.06.2016
   LogFilterClasses( const std::string& class_list);

private:
   /// Called to check if a message matches the filter criteria, i.e. if the
   /// message' log class is in the selection.
   /// @param[in]  msg  The message to check.
   /// @return  \c true if the log class of the message is selected.
   /// @since  0.3, 19.06.2016
   virtual bool pass( const LogMsg& msg) const;

   /// Set of log classes to accept.
   std::bitset< static_cast< size_t>( LogClass::operatorAction)>  mClassSelection;

}; // LogFilterClasses


// inlined methods
// ===============


inline bool LogFilterClasses::pass( const LogMsg& msg) const
{
   return mClassSelection[ static_cast< size_t>( msg.getClass())];
} // end LogFilterClasses::pass


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_FILTER_CLASSES_HPP


// ======================  END OF log_filter_classes.hpp  ======================

