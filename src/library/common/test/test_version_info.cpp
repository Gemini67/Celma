
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
**    Test program for the functions of the module print_version_info, using the
**    Boost.Test framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE PrintVersionInfoTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/celma_version.hpp"
#include "celma/common/print_version_info.hpp"


using namespace std;
using namespace celma;



/// Test stream output.
/// @since  0.2, 08.04.2016
BOOST_AUTO_TEST_CASE( stream_output)
{


   ostringstream  oss;


   oss << common::version_info;

   BOOST_REQUIRE_EQUAL( oss.str(),
                        string( "Celma library version: ") + VersionString);

} // end stream_output



// =========================  END OF test_version_info.cpp  =========================

