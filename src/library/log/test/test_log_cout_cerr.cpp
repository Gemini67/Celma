
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

   const auto   log_console = Logging::instance().findCreateLog( "console");
   Logging::instance().getLog( log_console)
      ->addDestination( "cerr", new celma::log::detail::LogDestStream( std::cerr))
         ->maxLevel( celma::log::LogLevel::error);

   Logging::instance().getLog( log_console)
      ->addDestination( "cout", new celma::log::detail::LogDestStream( std::cout))
         ->minLevel( celma::log::LogLevel::warning);

   LOG_LEVEL( log_console, fatal)
      << "message with level 'fatal' expected on stderr!";
   LOG_LEVEL( log_console, error)
      << "message with level 'error' expected on stderr!";
   LOG_LEVEL( log_console, warning)
      << "message with level 'warning' expected on stdout!";
   LOG_LEVEL( log_console, info)
      << "message with level 'info' expected on stdout!";
   LOG_LEVEL( log_console, debug)
      << "message with level 'debug' expected on stdout!";
   LOG_LEVEL( log_console, fullDebug)
      << "message with level 'full debug' expected on stdout!";

   return EXIT_SUCCESS;
}


// ======================  END OF test_log_cout_cerr.cpp  ======================

