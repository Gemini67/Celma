
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
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


// project includes
#include "celma/prog_args/detail/arg_list_element.hpp"
#include "celma/test/check_return.hpp"


using celma::prog_args::detail::ArgListElement;



/// Element is a single character.
///
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( test_character)
{

   ArgListElement  ele;


   ele.setArgChar( 3, 1, 'n');

   BOOST_REQUIRE_EQUAL( ele.mArgIndex,    3);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos,  1);
   BOOST_REQUIRE_EQUAL( ele.mElementType, ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( ele.mArgChar,     'n');
   BOOST_REQUIRE(       ele.mArgString.empty());
   BOOST_REQUIRE(       ele.mValue.empty());

} // test_character



/// Element is a single character.
///
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( test_word)
{

   ArgListElement  ele;


   ele.setArgString( 4, "name");

   BOOST_REQUIRE_EQUAL( ele.mArgIndex,    4);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos,  -1);
   BOOST_REQUIRE_EQUAL( ele.mElementType, ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( ele.mArgChar,     '-');
   BOOST_REQUIRE_EQUAL( ele.mArgString,   "name");
   BOOST_REQUIRE(       ele.mValue.empty());

} // test_word



/// Element is a single character.
///
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( test_value)
{

   ArgListElement  ele;


   ele.setValue( 5, "my name");

   BOOST_REQUIRE_EQUAL( ele.mArgIndex,    5);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos,  -1);
   BOOST_REQUIRE_EQUAL( ele.mElementType, ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( ele.mArgChar,     '-');
   BOOST_REQUIRE(       ele.mArgString.empty());
   BOOST_REQUIRE_EQUAL( ele.mValue,       "my name");

} // test_value



/// Element is a single character.
///
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( test_control)
{

   ArgListElement  ele;


   ele.setControl( 6, 1, '!');

   BOOST_REQUIRE_EQUAL( ele.mArgIndex,    6);
   BOOST_REQUIRE_EQUAL( ele.mArgCharPos,  1);
   BOOST_REQUIRE_EQUAL( ele.mElementType, ArgListElement::etControl);
   BOOST_REQUIRE_EQUAL( ele.mArgChar,     '!');
   BOOST_REQUIRE(       ele.mArgString.empty());
   BOOST_REQUIRE(       ele.mValue.empty());

} // test_control



// =====  END OF test_arg_list_element.cpp  =====

