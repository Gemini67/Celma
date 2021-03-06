
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the functions of the module LogFilterClasses, using the
**    Boost.Test framework.
**
--*/


// module to test header file 
#include "celma/log/filter/detail/log_filter_classes.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogFilterClassesTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/log/detail/log_msg.hpp"
#include "celma/common/celma_exception.hpp"


using celma::log::detail::LogMsg;
using celma::log::filter::detail::LogFilterClasses;



/// Test some error cases.
///
/// @since  1.26.0, 22.05.2019
BOOST_AUTO_TEST_CASE( errors)
{

   BOOST_REQUIRE_THROW( LogFilterClasses classFilter( ""),
      celma::common::CelmaRuntimeError);
   BOOST_REQUIRE_THROW( LogFilterClasses classFilter( "noclass"),
      celma::common::CelmaRuntimeError);
   BOOST_REQUIRE_THROW( LogFilterClasses classFilter( "noclass1,noclass2"),
      celma::common::CelmaRuntimeError);

} // errors



/// Test the filter for log classes with a single log class (name).
///
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( single_class)
{

   LogFilterClasses  classFilter( "Communication");
   LogMsg            msg( LOG_MSG_OBJECT_INIT);


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

} // single_class



/// Test the filter for log classes, using every second log class (name).
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( alternating)
{

   LogFilterClasses  classFilter( "SysCall,Communication,Accounting");
   LogMsg            msg( LOG_MSG_OBJECT_INIT);


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

} // alternating



// =====  END OF test_log_filter_classes.cpp  =====

