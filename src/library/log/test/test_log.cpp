
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


#include <iostream>
#include <sstream>


#include "celma/log/log_macros.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/detail/log_dest_stream.hpp"


using celma::log::Logging;
using celma::log::LogLevel;
using std::cout;
using std::endl;


int main()
{

   std::ostringstream  trace_output;


   auto const  log_trace = Logging::instance().findCreateLog( "trace");
   Logging::instance().getLog( log_trace)->addDestination( "stream",
                                                           new celma::log::detail::LogDestStream( trace_output));

   LOG( log_trace) << "my first trace log message :-)";

   cout << "Trace:     " << trace_output.str() << endl;
   trace_output.str( "");

   std::ostringstream  operation_output;

   auto const log_operation = Logging::instance().findCreateLog( "operation");
   GET_LOG( log_operation)->addDestination( "stream", new celma::log::detail::LogDestStream( operation_output));

   LOG( log_operation) << "my first operation log message :-)";

   cout << "Operation: " << operation_output.str() << endl;
   operation_output.str( "");

   LOG( log_trace | log_operation) << "this important message should be written to both logs!";

   cout << "Trace:     " << trace_output.str() << endl;
   trace_output.str( "");
   cout << "Operation: " << operation_output.str() << endl;
   operation_output.str( "");

   // set a maximum log level
   Logging::instance().getLog( log_trace)->maxLevel( LogLevel::debug);
   GET_LOG( log_operation)->maxLevel( LogLevel::warning);

   // operation log message should still be written
   LOG( log_operation) << LogLevel::warning << "operation message with level '"
                       << LogLevel::warning << "' should be printed.";
   cout << "Operation: " << operation_output.str() << endl;
   operation_output.str( "");

   // trace log message should still be written
   LOG( log_trace) << LogLevel::debug << "trace message with level 'debug' should be printed.";
   cout << "Trace:     " << trace_output.str() << endl;
   trace_output.str( "");

   // operation log message should still be written with macro LOG_LEVEL
   LOG_LEVEL( log_operation, warning) << "operation message with level 'warning' should still be printed.";
   cout << "Operation: " << operation_output.str() << endl;
   operation_output.str( "");

   // trace log message should still be written with macro LOG_LEVEL
   LOG_LEVEL( log_trace, debug) << "trace message with level 'debug' should still be printed.";
   cout << "Trace:     " << trace_output.str() << endl;
   trace_output.str( "");

   // operation log message, called by name, should still be written with macro
   // LOG_LEVEL
   LOG_LEVEL( std::string( "operation"), warning) << "operation by name with level 'warning' should still be printed.";
   cout << "Operation: " << operation_output.str() << endl;
   operation_output.str( "");

   // trace log message, called by name, should still be written with macro
   // LOG_LEVEL
   LOG_LEVEL( std::string( "trace"), debug) << "trace by name with level 'debug' should still be printed.";
   cout << "Trace:     " << trace_output.str() << endl;
   trace_output.str( "");

   // operation log message should now be suppressed
   LOG( log_operation) << LogLevel::info << "operation message with level 'info' should be suppressed.";
   cout << "Operation: " << operation_output.str() << endl;
   operation_output.str( "");

   // trace log message should now be suppressed
   LOG( log_trace) << LogLevel::fullDebug << "trace message with level 'full debug' should be suppressed.";
   cout << "Trace:     " << trace_output.str() << endl;
   trace_output.str( "");

   // use LOG_LEVEL macro to prevent creating the unused operation log message
   LOG_LEVEL( log_operation, info) << "operation message with level 'info' should still be suppressed.";
   cout << "Operation: " << operation_output.str() << endl;
   operation_output.str( "");

   // use LOG_LEVEL macro to prevent creating the unused trace log message
   LOG_LEVEL( log_trace, fullDebug) << "trace message with level 'full debug' should still be suppressed.";
   cout << "Trace:     " << trace_output.str() << endl;
   trace_output.str( "");

   Logging::reset();

   return EXIT_SUCCESS;
} // main 



// =====  END OF test_log.cpp  =====

