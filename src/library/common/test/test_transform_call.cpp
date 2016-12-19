 
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
**    Test program for the function transformCall() using the Boost.Test module.
**
--*/


// project includes
#include "celma/common/transform_call.hpp"


// OS/C lib includes
#include <cerrno>


// C++ Standard Library includes
#include <functional>


// Boost includes
#define BOOST_TEST_MODULE TransformCallTest
#include <boost/test/unit_test.hpp>


using celma::common::transformCall;
using std::placeholders::_1;


namespace {


int error_func( int param1, std::error_code& error)
{

   if (param1 % 2 == 0)
   {
      return param1 * param1;
   }

   error = std::error_code( EINVAL, std::system_category());

   return -1;
} // error_func


} // namespace



/// Test that calling the error_func() succeeds with the transformed returned
/// value/type.
/// @since  0.10, 1.12.2016
BOOST_AUTO_TEST_CASE( test_success)
{

   auto  rc = transformCall( std::bind( error_func, 4, _1));


   BOOST_REQUIRE( static_cast< bool>( rc));
   BOOST_REQUIRE_EQUAL( rc.value(), 16);

} // test_success



/// Test that calling the error_func() works correctly when an error is
/// returned.
/// @since  0.10, 1.12.2016
BOOST_AUTO_TEST_CASE( test_failure)
{

   auto  rc = transformCall( std::bind( error_func, 5, _1));


   BOOST_REQUIRE( !rc);
   BOOST_REQUIRE_EQUAL( rc.getError().value(), EINVAL);

} // test_failure



// =====================  END OF test_transform_call.cpp  =====================
