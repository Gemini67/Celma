
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature 'log destination file with no generations',
**    using the Boost.Test framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogDestFileNoGenerationsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_defs.hpp"
#include "celma/log/detail/log_dest_file_generations.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "test_log_dest_msg.hpp"


using celma::log::Logging;


/// @todo  Should use test classes to set up/tear down the log destination.
///        a) To remove code duplicates.
///        b) To make sure that the cleanup also happens when a test case fails
///           (now it leaves the invalid log destination which causes the next
///           test case to fail).



/// 
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( log_dest_file)
{

   const auto  my_log = Logging::instance().findCreateLog( "mine");


   Logging::instance().getLog( my_log)
      ->addDestination( "file", new celma::log::detail::LogDestFileGenerations<>( "/tmp", "logfile.txt"));

   LOG_PRINTF( my_log, info, communication,
               "log message created by %s-like function call with %d parameters",
               "printf()", 2);

   // have to remove this log destination again
   Logging::instance().getLog( my_log)->removeDestination( "file");

} // end log_printf_id



// =======================  END OF test_log_printf.cpp  =======================
