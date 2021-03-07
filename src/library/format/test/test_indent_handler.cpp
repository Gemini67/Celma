
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/



// module to test headerfile include
#include "celma/format/indent_handler.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE IndentHandlerTest
#include <boost/test/unit_test.hpp>


using celma::format::IndentHandler;
using celma::format::ScopedIndent;



/// Test indention.
///
/// @since  x.y.z, 02.03.2021
BOOST_AUTO_TEST_CASE( simple)
{

   {
      IndentHandler       ih( 1, 1);
      std::ostringstream  oss;

      oss << ih;
      BOOST_REQUIRE_EQUAL( oss.str(), " ");
   } // end scope

   {
      IndentHandler       ih( 1, 3);
      std::ostringstream  oss;

      oss << ih;
      BOOST_REQUIRE_EQUAL( oss.str(), "   ");
   } // end scope

   {
      IndentHandler       ih( 2, 3);
      std::ostringstream  oss;

      oss << ih;
      BOOST_REQUIRE_EQUAL( oss.str(), "      ");
   } // end scope

} // simple



/// Test indention with increasing levels.
///
/// @since  x.y.z, 02.03.2021
BOOST_AUTO_TEST_CASE( nested)
{

   IndentHandler  ih( 1, 3);

   {
      auto                ih2( ih);
      std::ostringstream  oss;

      oss << ih2;
      BOOST_REQUIRE_EQUAL( oss.str(), "      ");

      {
         auto                ih3( ih2);
         std::ostringstream  oss2;

         oss2 << ih3;
         BOOST_REQUIRE_EQUAL( oss2.str(), "         ");
      } // end scope
   } // end scope

} // nested



/// Test indention with scoped indention.
///
/// @since  x.y.z, 02.03.2021
BOOST_AUTO_TEST_CASE( scoped)
{

   IndentHandler  ih( 1, 3);

   {
      const ScopedIndent  si1( ih);
      std::ostringstream  oss;

      oss << ih;
      BOOST_REQUIRE_EQUAL( oss.str(), "      ");

      {
         const ScopedIndent  si2( ih);
         std::ostringstream  oss2;

         oss2 << ih;
         BOOST_REQUIRE_EQUAL( oss2.str(), "         ");
      } // end scope

      oss.str( "");
      oss << ih;
      BOOST_REQUIRE_EQUAL( oss.str(), "      ");
   } // end scope

   std::ostringstream  oss;

   oss << ih;
   BOOST_REQUIRE_EQUAL( oss.str(), "   ");

} // scoped



// =====  END OF test_indent_handler.cpp  =====

