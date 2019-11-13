
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// project includes
#include "celma/common/managed_thread.hpp"


// Boost includes
#define BOOST_TEST_MODULE ManagedThreadTest
#include <boost/test/unit_test.hpp>


namespace {


static int  value = -1;


void func( int param)
{
   value = param;

} // func


} // namespace



/// Test with one simple thread.
/// @since  012, 19.01.2017
BOOST_AUTO_TEST_CASE( test_one)
{

   celma::common::ManagedThread  mt( func, 42);

   ::usleep( 100);

   BOOST_REQUIRE( !mt.isActive());
   BOOST_REQUIRE_EQUAL( value, 42);

} // test_one



/// Test with two threads.
/// @since  012, 21.01.2017
BOOST_AUTO_TEST_CASE( test_two)
{

   celma::common::ManagedThread  mt1( [](){ ::sleep( 3); });
   celma::common::ManagedThread  mt2( [](){ ::sleep( 1); });

   ::usleep( 100);

   BOOST_REQUIRE( mt1.isActive());
   BOOST_REQUIRE( mt2.isActive());

   ::sleep( 2);

   BOOST_REQUIRE( mt1.isActive());
   BOOST_REQUIRE( !mt2.isActive());

   ::sleep( 2);

   BOOST_REQUIRE( !mt1.isActive());
   BOOST_REQUIRE( !mt2.isActive());

} // test_two



// =====  END OF test_managed_thread_mt.cpp  =====

