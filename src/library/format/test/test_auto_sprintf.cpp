
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
**    Test program for using the module AutoSprintf using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/format/auto_sprintf.hpp"


// C/OS library includes
#include <cstring>


// Boost includes
#define BOOST_TEST_MODULE AutoSprintfTest
#include <boost/test/unit_test.hpp>


using celma::format::AutoSprintf;



/// Test AutoSprintf without parameters, i.e. a constant string.
/// @since  0.2, 08.04.2016
BOOST_AUTO_TEST_CASE( test_no_param)
{

   const char* const  text = "actually mis-use AutoSprintf for a string-copy";
   AutoSprintf        as( text);


   BOOST_REQUIRE( ::strcmp( as.c_str(), text) == 0);
   BOOST_REQUIRE( ::strcmp( static_cast< const char*>( as), text) == 0);

   BOOST_REQUIRE_EQUAL( ::strlen( as.c_str()), as.length());
   BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( as)),
                        static_cast< int>( as));

} // end test_no_param



/// Test AutoSprintf with all data in one string parameter (with % sign).
/// @since  0.2, 08.04.2016
BOOST_AUTO_TEST_CASE( test_one_param)
{

   const char* const  text = "this is more a test of sprintf() and %-formatting "
                             "than of AutoSprintf, but tell me, how do you test "
                             "that memory was really free'd using free()?";
   AutoSprintf        as( "%s", text);


   BOOST_REQUIRE( ::strcmp( as.c_str(), text) == 0);
   BOOST_REQUIRE( ::strcmp( static_cast< const char*>( as), text) == 0);

   BOOST_REQUIRE_EQUAL( ::strlen( as.c_str()), as.length());
   BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( as)),
                        static_cast< int>( as));

} // end test_one_param



/// Test with some parameters.
/// @since  0.2, 08.04.2016
BOOST_AUTO_TEST_CASE( test_format)
{

   const char* const  format = "format int %d, float %6.4f and a string '%s'.";
   const char* const  text   = "format int 42, float 3.1415 and a string "
                               "'hello world'.";
   AutoSprintf        as( format, 42, 3.1415, "hello world");


   BOOST_REQUIRE( ::strcmp( as.c_str(), text) == 0);
   BOOST_REQUIRE( ::strcmp( static_cast< const char*>( as), text) == 0);

   BOOST_REQUIRE_EQUAL( ::strlen( as.c_str()), as.length());
   BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( as)),
                        static_cast< int>( as));

} // end test_format



// ======================  END OF test_auto_sprintf.cpp  ======================

