
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
**    Test program for the class ArgListElement using the Boost.Test framework.
**
--*/


// Boost includes
#define BOOST_TEST_MODULE ArgListElementTest
#include <boost/test/unit_test.hpp>


// C++ Standard Library includes
#include <iostream>
#include <sstream>


// project includes
#include "celma/prog_args/detail/arg_list_element.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::detail::ArgListElement;
using celma::test::multilineStringCompare;



/// Default initialisation.
///
/// @since  x.y.z, 16.04.2019
BOOST_AUTO_TEST_CASE( default_ctor)
{

   ArgListElement  ele;


   BOOST_REQUIRE_EQUAL( ele.mArgIndex, -1);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos, -1);
   BOOST_REQUIRE( ele.mElementType == ArgListElement::ElementType::invalid);
   BOOST_REQUIRE_EQUAL( ele.mArgChar, '-');
   BOOST_REQUIRE( ele.mArgString.empty());
   BOOST_REQUIRE( ele.mValue.empty());

   std::ostringstream  oss;

   oss << ele;
   // std::cerr << '\n' << oss.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( oss.str(),
      "invalid argument list element"));

} // default_ctor



/// Printing the element types.
///
/// @since  x.y.z, 16.04.2019
BOOST_AUTO_TEST_CASE( element_types)
{

   std::ostringstream  oss;


   oss << ArgListElement::ElementType::singleCharArg;
   BOOST_REQUIRE_EQUAL( oss.str(), "single character argument (0)");

   oss.str( "");
   oss << ArgListElement::ElementType::stringArg;
   BOOST_REQUIRE_EQUAL( oss.str(), "string/long argument (1)");

   oss.str( "");
   oss << ArgListElement::ElementType::value;
   BOOST_REQUIRE_EQUAL( oss.str(), "value (2)");

   oss.str( "");
   oss << ArgListElement::ElementType::control;
   BOOST_REQUIRE_EQUAL( oss.str(), "control character (3)");

   oss.str( "");
   oss << ArgListElement::ElementType::invalid;
   BOOST_REQUIRE_EQUAL( oss.str(), "invalid (4)");

} // element_types



/// Element is a single character.
///
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( test_character)
{

   ArgListElement  ele;


   ele.setArgChar( 3, 1, 'n');

   BOOST_REQUIRE_EQUAL( ele.mArgIndex, 3);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos, 1);
   BOOST_REQUIRE( ele.mElementType == ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( ele.mArgChar, 'n');
   BOOST_REQUIRE( ele.mArgString.empty());
   BOOST_REQUIRE( ele.mValue.empty());

   std::ostringstream  oss;

   oss << ele;
   // std::cerr << '\n' << oss.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( oss.str(),
      "element type       = single character argument (0)\n"
      "argument index     = 3\n"
      "character position = 1\n"
      "argument character = n\n"));

} // test_character



/// Element is a single character.
///
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( test_word)
{

   ArgListElement  ele;


   ele.setArgString( 4, "name");

   BOOST_REQUIRE_EQUAL( ele.mArgIndex, 4);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos, -1);
   BOOST_REQUIRE( ele.mElementType == ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( ele.mArgChar, '-');
   BOOST_REQUIRE_EQUAL( ele.mArgString, "name");
   BOOST_REQUIRE( ele.mValue.empty());

   std::ostringstream  oss;

   oss << ele;
   // std::cerr << '\n' << oss.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( oss.str(),
      "element type       = string/long argument (1)\n"
      "argument index     = 4\n"
      "argument string    = name\n"));

} // test_word



/// Element is a single character.
///
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( test_value)
{

   ArgListElement  ele;


   ele.setValue( 5, "my name");

   BOOST_REQUIRE_EQUAL( ele.mArgIndex, 5);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos, -1);
   BOOST_REQUIRE( ele.mElementType == ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( ele.mArgChar,  '-');
   BOOST_REQUIRE( ele.mArgString.empty());
   BOOST_REQUIRE_EQUAL( ele.mValue, "my name");

   std::ostringstream  oss;

   oss << ele;
   // std::cerr << '\n' << oss.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( oss.str(),
      "element type       = value (2)\n"
      "argument index     = 5\n"
      "value              = my name\n"));

} // test_value



/// Element is a single character.
///
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( test_control)
{

   ArgListElement  ele;


   ele.setControl( 6, 1, '!');

   BOOST_REQUIRE_EQUAL( ele.mArgIndex, 6);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos, 1);
   BOOST_REQUIRE( ele.mElementType == ArgListElement::ElementType::control);
   BOOST_REQUIRE_EQUAL( ele.mArgChar, '!');
   BOOST_REQUIRE( ele.mArgString.empty());
   BOOST_REQUIRE( ele.mValue.empty());

   std::ostringstream  oss;

   oss << ele;
   // std::cerr << '\n' << oss.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( oss.str(),
      "element type       = control character (3)\n"
      "argument index     = 6\n"
      "ctrl char position = 1\n"
      "control character  = !\n"));

} // test_control



// =====  END OF test_arg_list_element.cpp  =====

