
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
**    Test program for the handling of duplicate filters in the module
**    LogFilter, using the Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/log/filter/filters.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogFilterDuplicatePolicyTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/log_msg.hpp"


using celma::log::detail::LogMsg;
using celma::log::filter::detail::DuplicatePolicy;
using celma::log::filter::Filters;
using celma::log::LogLevel;



/// Test some errors conditions.
///
/// @since  1.26.0, 22.05.2019
BOOST_AUTO_TEST_CASE( errors)
{

   BOOST_REQUIRE_THROW( Filters::setDuplicatePolicy(
      static_cast< DuplicatePolicy>( 10)), celma::common::CelmaRuntimeError);

} // errors



/// Default policy 'ignore' should simply ignore the new filter with the same
/// type.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( policy_ignore)
{

   Filters  lf;
   LogMsg   msg( LOG_MSG_OBJECT_INIT);


   lf.maxLevel( LogLevel::error);

   msg.setLevel( LogLevel::error);
   BOOST_REQUIRE( lf.pass( msg));

   msg.setLevel( LogLevel::debug);
   BOOST_REQUIRE( !lf.pass( msg));

   // now we try to set another max level that should be ignored
   BOOST_REQUIRE_NO_THROW( lf.maxLevel( LogLevel::debug));

   // tests with a message with different levels should yield the same results
   // as before
   msg.setLevel( LogLevel::error);
   BOOST_REQUIRE( lf.pass( msg));

   msg.setLevel( LogLevel::debug);
   BOOST_REQUIRE( !lf.pass( msg));

} // policy_ignore



/// Policy 'throw' must throw when another filter with the same type is set.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( policy_throw)
{

   Filters  lf;


   lf.maxLevel( LogLevel::error);

   Filters::setDuplicatePolicy( DuplicatePolicy::exception);

   // now we try to set another max level which should result in an exception
   // being thrown
   BOOST_REQUIRE_THROW( lf.maxLevel( LogLevel::debug),
      celma::common::CelmaRuntimeError);

} // policy_ignore



/// Policy 'replace' should replace the existing policy with the same type.
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( policy_replace)
{

   Filters  lf;
   LogMsg   msg( LOG_MSG_OBJECT_INIT);


   lf.maxLevel( LogLevel::error);

   msg.setLevel( LogLevel::error);
   BOOST_REQUIRE( lf.pass( msg));

   msg.setLevel( LogLevel::debug);
   BOOST_REQUIRE( !lf.pass( msg));

   Filters::setDuplicatePolicy( DuplicatePolicy::replace);

   // now we try to set another max level that should be used afterwards
   BOOST_REQUIRE_NO_THROW( lf.maxLevel( LogLevel::debug));

   // now the mesage with level debug should also pass
   msg.setLevel( LogLevel::error);
   BOOST_REQUIRE( lf.pass( msg));

   msg.setLevel( LogLevel::debug);
   BOOST_REQUIRE( lf.pass( msg));

} // policy_ignore



// =====  END OF test_log_filter_duplicate_policy.cpp  =====

