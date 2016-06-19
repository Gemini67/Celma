
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
**    Test program for the handling of duplicate filters in the module
**    LogFilter, using the Boost.Test framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// Boost includes
#define BOOST_TEST_MODULE LogFilterDuplicatePolicyTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/celma_exception.hpp"
#include "celma/log/detail/log_filter.hpp"


using celma::log::detail::LogFilter;
using celma::log::LogLevel;



/// 
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( policy_ignore)
{

   LogFilter  lf;


   lf.maxLevel( LogLevel::error);

   // now we try to set another max level that should be ignored
   BOOST_REQUIRE_NO_THROW( lf.maxLevel( LogLevel::debug));

} // end policy_ignore



/// 
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( policy_throw)
{

   LogFilter  lf;


   lf.maxLevel( LogLevel::error);

   LogFilter::setDuplicatePolicy( celma::log::detail::dpThrow);

   // now we try to set another max level which should result in an exception
   // being thrown
   BOOST_REQUIRE_THROW( lf.maxLevel( LogLevel::debug), celma::common::CelmaRuntimeError);

} // end policy_ignore



/// 
/// @since  0.3, 19.06.2016
BOOST_AUTO_TEST_CASE( policy_replace)
{

   LogFilter  lf;


   lf.maxLevel( LogLevel::error);

   LogFilter::setDuplicatePolicy( celma::log::detail::dpReplace);

   // now we try to set another max level that should be used afterwards
   BOOST_REQUIRE_NO_THROW( lf.maxLevel( LogLevel::debug));

} // end policy_ignore



// ===============  END OF test_log_filter_duplicate_policy.cpp  ===============
