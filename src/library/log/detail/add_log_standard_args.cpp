
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
/// See documentation of function celma::log::detail::addLogStandardArgs().


// module header file include
#include "celma/log/detail/add_log_standard_args.hpp"


// C++ Standard Library includes
#include <iostream>
#include <string>


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/log_dest_stream.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/logging.hpp"
#include "celma/prog_args/add_standard_argument.hpp"
#include "celma/prog_args/handler.hpp"


namespace celma { namespace log { namespace detail {


namespace {


static void log2stdout( const std::string& log_name);


} // namespace



/// Adds (standard) log arguments:
/// - '--log-stdout \<logname\>' that adds \c stdout as a log destination.
///
/// @param[in]  std_grp_name  The name of the argument group used for standard
///                           arguments.
/// @since  0.3, 19.06.2016
void addLogStandardArgs( const char* std_grp_name)
{

   prog_args::addStandardArgument( "log-stdout",
                                   DEST_FUNCTION_VALUE( log2stdout),
                                   "Writes the messages of the specified "
                                   "log to stdout (too).",
                                   std_grp_name);

} // end addLogStandardArgs



namespace {



/// This function is called when the standard argument to turn on logging to
/// \c stdout is actually used. Adds the stream log destination with \c cout to
/// the specified log.
/// @param[in]  log_name  The name of the log to add the stream destination to.
/// @since  0.3, 19.06.2016
static void log2stdout( const std::string& log_name)
{

   if (auto log_obj = Logging::instance().getLog( log_name))
   {
      log_obj->addDestination( "stdout", new LogDestStream( std::cout));
   } else
   {
      throw CELMA_RuntimeError( std::string( "no log with name '").append( log_name).
                                    append( "' exists"));
   } // end if

} // log2stdout



} // namespace



} // namespace detail
} // namespace log
} // namespace celma


// ====================  END OF add_log_standard_args.cpp  ====================

