
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
**    Test program for the module FirstPass using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE FirstPassTest
#include <boost/test/unit_test.hpp>
#include <utility>


// project includes
#include "celma/common/first_pass.hpp"


using namespace std;
using namespace celma;


/// All tests for the class FirstPass.
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( first_pass)
{

   
   {
      common::FirstPass  first;

      // first the value is true
      BOOST_REQUIRE( static_cast< bool>( first));

      // now it's false
      BOOST_REQUIRE( !static_cast< bool>( first));
      BOOST_REQUIRE( !first);
   } // end scope

   {
      common::FirstPass  first;

      // first the value is true
      BOOST_REQUIRE( !first == false);

      // now it's false
      BOOST_REQUIRE( !static_cast< bool>( first));
      BOOST_REQUIRE( !first);
   } // end scope

   {
      common::FirstPass  first;
      ostringstream      oss;

      oss << first;
      BOOST_REQUIRE_EQUAL( oss.str(), "true");

      !first;

      oss.str( "");
      oss << first;
      BOOST_REQUIRE_EQUAL( oss.str(), "false");
   } // end scope

} // end first_pass



// =========================  END OF test_first_pass.cpp  =========================

