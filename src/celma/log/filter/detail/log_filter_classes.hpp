
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
/// See documentation of class celma::log::detail::LogFilterClasses.


#pragma once


#include <bitset>
#include <string>
#include "celma/log/filter/detail/i_filter.hpp"
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log_msg.hpp"


namespace celma::log::filter::detail {


/// Filter on log classes.
/// @since  0.3, 19.06.2016
class LogFilterClasses final : public IFilter
{
public:
   /// Constructor, initialises the set of log classes to accept.
   /// @param[in]  class_list  The list of log class names to filter for.
   /// @since  0.3, 19.06.2016
   explicit LogFilterClasses( const std::string& class_list) noexcept( false);

   ~LogFilterClasses() override = default;

private:
   /// Called to check if a message matches the filter criteria, i.e. if the
   /// message' log class is in the selection.
   /// @param[in]  msg  The message to check.
   /// @return  \c true if the log class of the message is selected.
   /// @since  0.3, 19.06.2016
   bool pass( const log::detail::LogMsg& msg) const override;

   /// Set of log classes to accept.
   std::bitset< static_cast< size_t>( LogClass::operatorAction)>  mClassSelection;

}; // LogFilterClasses


// inlined methods
// ===============


inline bool LogFilterClasses::pass( const log::detail::LogMsg& msg) const
{
   return mClassSelection[ static_cast< size_t>( msg.getClass())];
} // LogFilterClasses::pass


} // namespace celma::log::filter::detail


// =====  END OF log_filter_classes.hpp  =====

