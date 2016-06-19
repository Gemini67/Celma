
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
/// See documentation of class celma::log::detail::Log.


// module header file include
#include "celma/log/detail/log.hpp"


// C++ Standard Library includes
#include <iostream>


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/i_log_dest.hpp"


namespace celma { namespace log { namespace detail {



/// Constructor.
/// @since  0.3, 19.06.2016
Log::Log():
   LogFilter(),
   mLoggers()
{
} // end Log::Log



/// Destructor.
/// @since  0.3, 19.06.2016
Log::~Log()
{

   mLoggers.clear();

} // end Log::~Log



/// Adds a new destination to this log.
/// @param[in]  name  The symbolic name of this log destination.
/// @param[in]  ldo   Pointer to the object that handles this log destination.
/// @return  Pointer to the log destination object, can be used to set filters.
/// @since  0.3, 19.06.2016
ILogDest* Log::addDestination( const std::string& name, ILogDest* ldo)
{

   mLoggers.push_back( LogDestData( name, ldo));

   return mLoggers.back().mpLogger.get();
} // end Log::addDestination




/// Returns a pointer to the log destination with the specified name.
/// @param[in]  name  The name of the log destination to return.
/// @return  Pointer to the log destination object.
/// @throw  Runtime error if a log destination with this name was not found.
/// @since  0.3, 19.06.2016
ILogDest* Log::getDestination( const std::string& name)
{

   /// @todo  find_if
   for (auto it : mLoggers)
   {
      if (it.mName == name)
      {
         return it.mpLogger.get();
      } // end if
   } // end for

   throw CELMA_RuntimeError( "Log destination with name '" + name + "' does not exist");

} // end Log::getDestination



/// Removes a destination.
/// @param[in]  name  The name of the destination to remove.
/// @since  0.3, 19.06.2016
void Log::removeDestination( const std::string& name)
{

   for (auto it = mLoggers.begin(); it != mLoggers.end(); ++it)
   {
      if (it->mName == name)
      {
         mLoggers.erase( it);
         break;   // for
      } // end if
   } // end for

} // end Log::removeDestination



/// Passes a log message to all current destinations.
/// @param[in]  msg  The message to pass.
/// @since  0.3, 19.06.2016
void Log::message( const LogMsg& msg) const
{

   if (pass( msg))
   {
      for (auto it : mLoggers)
      {
         it.mpLogger->handleMessage( msg);
      } // end for
   } // end if

} // end Log::message



/// Writes information about a log.
/// @param[in]  os  The stream to write into.
/// @param[in]  l   The log to dump the information of.
/// @return  The stream as passed in.
/// @since  0.3, 19.06.2016
std::ostream& operator <<( std::ostream& os, const Log& l)
{

   for (auto it : l.mLoggers)
   {
      os << it << std::endl;
   } // end for

   return os;
} // end operator <<



} // namespace detail
} // namespace log
} // namespace celma


// =============================  END OF log.cpp  =============================

