
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
**    Test program for the functions of the module LogFilterClasses, using the
**    Boost.Test framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogFilterClassesTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_filter_classes.hpp"
#include "celma/log/detail/log_msg.hpp"



/// Test the filter for log classes with a single log class (name).
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( single_class)
{

   celma::log::detail::LogFilterClasses  classFilter( "Communication");
   celma::log::detail::LogMsg            msg( LOG_MSG_OBJECT_INIT);


   msg.setClass( celma::log::LogClass::sysCall);
   BOOST_REQUIRE( !classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::data);
   BOOST_REQUIRE( !classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::communication);
   BOOST_REQUIRE( classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::application);
   BOOST_REQUIRE( !classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::accounting);
   BOOST_REQUIRE( !classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::operatorAction);
   BOOST_REQUIRE( !classFilter.passFilter( msg));

} // end single_class



/// Test the filter for log classes, using every second log class (name).
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( alternating)
{

   celma::log::detail::LogFilterClasses  classFilter( "SysCall,Communication,Accounting");
   celma::log::detail::LogMsg            msg( LOG_MSG_OBJECT_INIT);


   msg.setClass( celma::log::LogClass::sysCall);
   BOOST_REQUIRE( classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::data);
   BOOST_REQUIRE( !classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::communication);
   BOOST_REQUIRE( classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::application);
   BOOST_REQUIRE( !classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::accounting);
   BOOST_REQUIRE( classFilter.passFilter( msg));

   msg.setClass( celma::log::LogClass::operatorAction);
   BOOST_REQUIRE( !classFilter.passFilter( msg));

} // end alternating



// ===================  END OF test_log_filter_classes.cpp  ===================
