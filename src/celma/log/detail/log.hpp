
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
/// See documentation of class celma::log::detail::Log.


#ifndef CELMA_LOG_DETAIL_LOG_HPP
#define CELMA_LOG_DETAIL_LOG_HPP


#include <iosfwd>
#include <string>
#include <vector>
#include "celma/log/detail/log_dest_data.hpp"
#include "celma/log/filter/filters.hpp"


namespace celma { namespace log { namespace detail {


class ILogDest;
class LogMsg;


/// Log manager. Handles settings, destinations etc. of one log (type).
/// @since  1.0.0, 19.06.2016
class Log: public filter::Filters
{
public:
   /// Constructor.
   /// @since  1.0.0, 19.06.2016
   Log();

   /// Destructor.
   /// @since  1.0.0, 19.06.2016
   ~Log();

   /// Adds a new destination to this log.
   /// @param[in]  name  The symbolic name of this log destination.
   /// @param[in]  ldo   Pointer to the object that handles this log destination.
   /// @return  Pointer to the log destination object, can be used to set filters.
   /// @since  1.0.0, 19.06.2016
   ILogDest* addDestination( const std::string& name, ILogDest* ldo);

   /// Returns a pointer to the log destination with the specified name.
   /// @param[in]  name  The name of the log destination to return.
   /// @return  Pointer to the log destination object.
   /// @throw  Runtime error if a log destination with this name was not found.
   /// @since  1.0.0, 19.06.2016
   ILogDest* getDestination( const std::string& name) noexcept( false);

   /// Removes a destination.
   /// @param[in]  name  The name of the destination to remove.
   /// @since  1.0.0, 19.06.2016
   void removeDestination( const std::string& name);

   /// Passes a log message to all current destinations.
   /// @param[in]  msg  The message to pass.
   /// @since  1.0.0, 19.06.2016
   void message( const LogMsg& msg) const;

   /// Writes information about a log.
   /// @param[in]  os  The stream to write into.
   /// @param[in]  l   The log to dump the information of.
   /// @return  The stream as passed in.
   /// @since  1.0.0, 19.06.2016
   friend std::ostream& operator <<( std::ostream& os, const Log& l);

private:
   /// Container to store all log destinations.
   using log_dest_cont_t = std::vector< LogDestData>;

   /// Current log destinations.
   log_dest_cont_t  mLoggers;

}; // Log


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_LOG_HPP


// =====  END OF log.hpp  =====

