
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


#include "log_macros.hpp"
#include "logging.hpp"
#include "log.hpp"
#include "log_dest_stream.hpp"



int main()
{

   using namespace celma::log::Logging;

   auto const log_console = Logging::instance().findCreateLog( "console");
   Logging::instance().getLog( log_console)
      ->addDestination( "cerr", new celma::log::LogDestStream( cerr, true))
         ->maxLevel( log::error);

   Logging::instance().getLog( log_console)
      ->addDestination( "cout", new celma::log::LogDestStream( cout, true))
         ->minLevel( log::warning);

   LOG_LEVEL( log_console, log::fatal)
      << "message with level 'fatal' expected on stderr!";
   LOG_LEVEL( log_console, log::error)
      << "message with level 'error' expected on stderr!";
   LOG_LEVEL( log_console, log::warning)
      << "message with level 'warning' expected on stdout!";
   LOG_LEVEL( log_console, log::info)
      << "message with level 'info' expected on stdout!";
   LOG_LEVEL( log_console, log::debug)
      << "message with level 'debug' expected on stdout!";
   LOG_LEVEL( log_console, log::fullDebug)
      << "message with level 'full debug' expected on stdout!";

   return EXIT_SUCCESS;
}


// =====  END OF test_log_cout_cerr.cpp  =====

