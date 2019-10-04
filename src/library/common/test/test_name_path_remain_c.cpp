
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the module NamePathRemain using the Boost.Test
**    framework.
**
--*/


// test module header file included first
#include "celma/common/detail/name_path_remain.hpp"


// Boost includes
#define BOOST_TEST_MODULE NamePathRemainTest
#include <boost/test/unit_test.hpp>


using celma::common::detail::NamePathRemain;



/// Check with wrong values.
///
/// @since  1.22.0, 26.03.2019
BOOST_AUTO_TEST_CASE( errors)
{

   {
      NamePathRemain  npr( "", '.');

      BOOST_REQUIRE( npr.firstName().empty());
      BOOST_REQUIRE( npr.remain().empty());
   } // end scope

   {
      NamePathRemain  npr( ".", '.');

      BOOST_REQUIRE( npr.firstName().empty());
      BOOST_REQUIRE( npr.remain().empty());
   } // end scope

   {
      NamePathRemain  npr( "..", '.');

      BOOST_REQUIRE( npr.firstName().empty());
      BOOST_REQUIRE( !npr.remain().empty());
      BOOST_REQUIRE_EQUAL( npr.remain(), ".");
   } // end scope

   {
      NamePathRemain  npr( "a.b", '-');

      BOOST_REQUIRE_EQUAL( npr.firstName(), "a.b");
      BOOST_REQUIRE( npr.remain().empty());
   } // end scope

} // errors



/// Some real split tests.
///
/// @since  1.22.0, 26.03.2019
BOOST_AUTO_TEST_CASE( split)
{

   {
      NamePathRemain  npr( "a.b", '.');

      BOOST_REQUIRE_EQUAL( npr.firstName(), "a");
      BOOST_REQUIRE_EQUAL( npr.remain(), "b");
   } // end scope

   {
      NamePathRemain  npr( "Address.Name", '.');

      BOOST_REQUIRE_EQUAL( npr.firstName(), "Address");
      BOOST_REQUIRE_EQUAL( npr.remain(), "Name");
   } // end scope

   {
      NamePathRemain  npr( "Ignore special characters.Only the separator matters!",
         '.');

      BOOST_REQUIRE_EQUAL( npr.firstName(), "Ignore special characters");
      BOOST_REQUIRE_EQUAL( npr.remain(), "Only the separator matters!");
   } // end scope

} // split



// =====  END OF test_name_path_remain_c.cpp  =====

