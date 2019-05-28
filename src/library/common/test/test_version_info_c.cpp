
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
**    Test program for the functions of the module print_version_info, using the
**    Boost.Test framework.
**
--*/


// C++ Standard Library includes
#include <sstream>
#include <string>


// Boost includes
#define BOOST_TEST_MODULE PrintVersionInfoTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/celma_version.hpp"
#include "celma/common/print_version_info.hpp"



/// Test stream output.
///
/// @since  0.2, 08.04.2016
BOOST_AUTO_TEST_CASE( stream_output)
{


   std::ostringstream  oss;


   oss << celma::common::version_info;

   BOOST_REQUIRE_EQUAL( oss.str(), std::string( "Celma library version: ")
      + celma::VersionString);

} // stream_output



// =====  END OF test_version_info_c.cpp  =====

