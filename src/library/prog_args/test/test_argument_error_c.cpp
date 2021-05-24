
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the class celma::prog_args::argument_error using the
**    Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/prog_args/argument_error.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgumentErrorTest
#include <boost/test/unit_test.hpp>


using celma::prog_args::argument_error;



/// Create an exception using a C string.
///
/// @since  1.45.0, 20.05.2021
BOOST_AUTO_TEST_CASE( error_c_string)
{

   argument_error  ar( "hello");


   BOOST_REQUIRE_EQUAL( ar.what(), "hello");

} // error_c_string



/// Create an exception using a std::string.
///
/// @since  1.45.0, 21.05.2021
BOOST_AUTO_TEST_CASE( error_std_string)
{

   argument_error  ar( std::string( "hello"));


   BOOST_REQUIRE_EQUAL( ar.what(), "hello");

} // error_std_string



// =====  END OF test_argument_error_c.cpp  =====
