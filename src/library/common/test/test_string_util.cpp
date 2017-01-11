
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module string_util using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/common/string_util.hpp"


// Boost includes
#define BOOST_TEST_MODULE TestStringUtil
#include <boost/test/unit_test.hpp>
#include <utility>


using celma::common::ensure_last;
using std::string;



/// Test the function ensure_last().
/// @since  0.12, 11.01.2017
BOOST_AUTO_TEST_CASE( test_ensure_last)
{

   {
      string  str;

      ensure_last( str);

      BOOST_REQUIRE( str.empty());
   } // end scope

   {
      string  str( "s");

      ensure_last( str);

      BOOST_REQUIRE( !str.empty());
      BOOST_REQUIRE_EQUAL( str.length(), 2);
      BOOST_REQUIRE_EQUAL( str[ 1], '/');
   } // end scope

   {
      string  str( "/");

      ensure_last( str);

      BOOST_REQUIRE( !str.empty());
      BOOST_REQUIRE_EQUAL( str.length(), 1);
      BOOST_REQUIRE_EQUAL( str[ 0], '/');
   } // end scope

   {
      string  str( "s");

      ensure_last( str, '.');

      BOOST_REQUIRE( !str.empty());
      BOOST_REQUIRE_EQUAL( str.length(), 2);
      BOOST_REQUIRE_EQUAL( str[ 1], '.');
   } // end scope

   {
      string  str( "hello world");

      ensure_last( str, '.');

      BOOST_REQUIRE( !str.empty());
      BOOST_REQUIRE_EQUAL( str.length(), 12);
      BOOST_REQUIRE_EQUAL( str[ 11], '.');
   } // end scope

   {
      string  str( "hello world.");

      ensure_last( str, '.');

      BOOST_REQUIRE( !str.empty());
      BOOST_REQUIRE_EQUAL( str.length(), 12);
      BOOST_REQUIRE_EQUAL( str[ 11], '.');
   } // end scope

} // end test_ensure_last



// =======================  END OF test_string_util.cpp  =======================

