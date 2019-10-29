
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test, header file include
#include "celma/common/string_util.hpp"


// Boost includes
#define BOOST_TEST_MODULE StringUtilTest
#include <boost/test/unit_test.hpp>



/// Test the behaviour of ensure_last().
///
/// @since  1.11.0, 22.08.2018
BOOST_AUTO_TEST_CASE( check_ensure_last)
{

   using celma::common::ensure_last;

   // should not modify empty path
   {
      std::string  path;

      ensure_last( path);

      BOOST_REQUIRE( path.empty());
   } // end scope

   // append at most one slash
   {
      std::string  path( "/usr/include");

      ensure_last( path);

      BOOST_REQUIRE_EQUAL( path, "/usr/include/");

      ensure_last( path);

      BOOST_REQUIRE_EQUAL( path, "/usr/include/");
   } // end scope

   // use with other character
   {
      std::string  title( "Hallo");

      ensure_last( title, '!');

      BOOST_REQUIRE_EQUAL( title, "Hallo!");

      ensure_last( title, '!');

      BOOST_REQUIRE_EQUAL( title, "Hallo!");
   } // end scope

} // check_ensure_last



/// Verify that remove_to_if() works correctly.
///
/// @since  1.11.0, 23.08.2018
BOOST_AUTO_TEST_CASE( check_remove_to_if)
{

   using celma::common::remove_to_if;

   // should not modify empty string
   {
      std::string  path;

      remove_to_if( path, 'w');

      BOOST_REQUIRE( path.empty());
   } // end scope

   // check character not found
   {
      std::string  str( "hello world");

      remove_to_if( str, 'p');

      BOOST_REQUIRE_EQUAL( str, "hello world");
   } // end scope

   // check character not found
   {
      std::string  str( "hello world");

      remove_to_if( str, 'p', true);

      BOOST_REQUIRE_EQUAL( str, "hello world");
   } // end scope

   // character found in middle of string
   {
      std::string  str( "hello world");

      remove_to_if( str, 'o');

      BOOST_REQUIRE_EQUAL( str, "orld");
   } // end scope

   // second character found in middle of string
   {
      std::string  str( "hello world");

      remove_to_if( str, 'o', true);

      BOOST_REQUIRE_EQUAL( str, "o world");
   } // end scope

   // character found in middle of string, not including
   {
      std::string  str( "hello world");

      remove_to_if( str, 'o', false, true);

      BOOST_REQUIRE_EQUAL( str, "rld");
   } // end scope

   // check character not found
   {
      std::string  str( "hello world");

      remove_to_if( str, 'o', true, true);

      BOOST_REQUIRE_EQUAL( str, " world");
   } // end scope

} // check_remove_to_if



/// Verify that the shortcuts for remove_to_if() works correctly.
///
/// @since  1.11.0, 23.08.2018
BOOST_AUTO_TEST_CASE( check_remove_to_if_shortcuts)
{

   // character found in middle of string
   {
      std::string  str( "hello world");

      celma::common::remove_to_if_last_excl( str, 'o');

      BOOST_REQUIRE_EQUAL( str, "orld");
   } // end scope

   // second character found in middle of string
   {
      std::string  str( "hello world");

      celma::common::remove_to_if_first_excl( str, 'o');

      BOOST_REQUIRE_EQUAL( str, "o world");
   } // end scope

   // character found in middle of string, not including
   {
      std::string  str( "hello world");

      celma::common::remove_to_if_last_incl( str, 'o');

      BOOST_REQUIRE_EQUAL( str, "rld");
   } // end scope

   // check character not found
   {
      std::string  str( "hello world");

      celma::common::remove_to_if_first_incl( str, 'o');

      BOOST_REQUIRE_EQUAL( str, " world");
   } // end scope

} // check_remove_to_if_shortcuts



/// Check the results returned by celma::common::startsWith().
///
/// @since  1.32.0, 03.09.2019
BOOST_AUTO_TEST_CASE( check_starts_with)
{

   using celma::common::startsWith;


   BOOST_REQUIRE( startsWith( "", ""));
   BOOST_REQUIRE( !startsWith( "", "", false));
   BOOST_REQUIRE( !startsWith( "hello", ""));
   BOOST_REQUIRE( !startsWith( "", "world"));
   BOOST_REQUIRE( startsWith( "hello world", "hello world"));
   BOOST_REQUIRE( startsWith( "hello world", "hello worl"));
   BOOST_REQUIRE( startsWith( "hello world", "hello "));
   BOOST_REQUIRE( !startsWith( "hello", "hello "));
   BOOST_REQUIRE( startsWith( "hello world", "h"));

} // check_starts_with



// =====  END OF test_string_util.cpp  =====

