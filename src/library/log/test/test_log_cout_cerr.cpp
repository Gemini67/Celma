
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


#include <iostream>


#include "celma/log/log_macros.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/detail/log_dest_stream.hpp"


using celma::log::Logging;


int main()
{

   const celma::log::id_t  log_console = Logging::instance().findCreateLog( "console");
   Logging::instance().getLog( log_console)
      ->addDestination( "cerr", new celma::log::detail::LogDestStream( std::cerr))
         ->maxLevel( celma::log::llError);

   Logging::instance().getLog( log_console)
      ->addDestination( "cout", new celma::log::detail::LogDestStream( std::cout))
         ->minLevel( celma::log::llWarning);

   LOG_LEVEL( log_console, llFatal)
      << "message with level 'fatal' expected on stderr!";
   LOG_LEVEL( log_console, llError)
      << "message with level 'error' expected on stderr!";
   LOG_LEVEL( log_console, llWarning)
      << "message with level 'warning' expected on stdout!";
   LOG_LEVEL( log_console, llInfo)
      << "message with level 'info' expected on stdout!";
   LOG_LEVEL( log_console, llDebug)
      << "message with level 'debug' expected on stdout!";
   LOG_LEVEL( log_console, llFullDebug)
      << "message with level 'full debug' expected on stdout!";

   return EXIT_SUCCESS;
}


// ======================  END OF test_log_cout_cerr.cpp  ======================

