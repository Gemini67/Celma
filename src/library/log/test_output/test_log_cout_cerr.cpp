
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


#include "log_macros.hpp"
#include "logging.hpp"
#include "log.hpp"
#include "log_dest_stream.hpp"


using namespace celma::log::Logging;


int main()
{

   auto const log_console = Logging::instance().findCreateLog( "console");
   Logging::instance().getLog( log_console)
      ->addDestination( "cerr", new celma::log::LogDestStream( cerr, true))
         ->maxLevel( log::llError);

   Logging::instance().getLog( log_console)
      ->addDestination( "cout", new celma::log::LogDestStream( cout, true))
         ->minLevel( log::llWarning);

   LOG_LEVEL( log_console, log::llFatal)
      << "message with level 'fatal' expected on stderr!";
   LOG_LEVEL( log_console, log::llError)
      << "message with level 'error' expected on stderr!";
   LOG_LEVEL( log_console, log::llWarning)
      << "message with level 'warning' expected on stdout!";
   LOG_LEVEL( log_console, log::llInfo)
      << "message with level 'info' expected on stdout!";
   LOG_LEVEL( log_console, log::llDebug)
      << "message with level 'debug' expected on stdout!";
   LOG_LEVEL( log_console, log::llFullDebug)
      << "message with level 'full debug' expected on stdout!";

   return EXIT_SUCCESS;
}


// ======================  END OF test_log_cout_cerr.cpp  ======================

