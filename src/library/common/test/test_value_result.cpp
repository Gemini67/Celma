 
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
**    Test program for the module ValueResult using the Boost.Test module.
**
--*/


// project includes
#include "celma/common/value_result.hpp"


// OS/C lib includes
#include <cerrno>


// Boost includes
#define BOOST_TEST_MODULE ValueResultTest
#include <boost/test/unit_test.hpp>


using celma::common::ValueResult;


namespace {


const ValueResult< int> funcOk()
{

   return ValueResult< int>( 42);
} // funcOk


const ValueResult< int> funcError()
{

   return ValueResult< int>( std::error_code( EINVAL, std::system_category()));
} // funcError


const ValueResult< int> funcCode0()
{

   return ValueResult< int>( 0);
} // funcCode0


} // namespace



/// Test with a function that returns successfully.
/// @since  0.10, 1.12.2016
BOOST_AUTO_TEST_CASE( test_result_42)
{

   auto  cr( funcOk());


   BOOST_REQUIRE( static_cast< bool>( cr));
   BOOST_REQUIRE( !cr == false);
   BOOST_REQUIRE_EQUAL( cr.value(), 42);

} // test_result_42



/// Test with a function that returns an error.
/// @since  0.10, 1.12.2016
BOOST_AUTO_TEST_CASE( test_result_error)
{

   auto  cr( funcError());

 
   BOOST_REQUIRE( static_cast< bool>( cr) == false);
   BOOST_REQUIRE( !cr);
   BOOST_REQUIRE_EQUAL( cr.getError().value(), EINVAL);

} // test_result_error



/// Test with a function that returns 0 as success value.
/// @since  0.10, 1.12.2016
BOOST_AUTO_TEST_CASE( test_result_0)
{

   auto  cr( funcCode0());


   BOOST_REQUIRE( static_cast< bool>( cr));
   BOOST_REQUIRE( !cr == false);
   BOOST_REQUIRE_EQUAL( cr.value(), 0);

} // test_result_0



// ======================  END OF test_value_result.cpp  ======================

