
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
**    Test program for the module TokenizerBase using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/common/tokenizer_base.hpp"


// Boost includes
#define BOOST_TEST_MODULE TestTokenizerBase
#include <boost/test/unit_test.hpp>


using celma::common::TokenizerBase;


using Separator = boost::escaped_list_separator< char>;
using Tokenizer = TokenizerBase< Separator>;



/// Call tokenizer for an empty string.
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_empty)
{

   const std::string    str;
   Separator            sep( '\\', ' ', '"');
   Tokenizer            t( str, sep);
   Tokenizer::iterator  it = t.begin();


   BOOST_REQUIRE( it == t.end());

} // test_empty



/// Call tokenizer for a string that does not contain the token.
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_one)
{

   const std::string    str( "string_that_does_not_contain_the_token");
   Separator            sep( '\\', ' ', '"');
   Tokenizer            t( str, sep);
   Tokenizer::iterator  it = t.begin();


   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, str);

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_one



/// Split string with multiple tokens.
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_multi)
{

   const std::string    str( "string that does contain one token");
   Separator            sep( '\\', ' ', '"');
   Tokenizer            t( str, sep);
   Tokenizer::iterator  it = t.begin();


   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "string");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "that");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "does");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "contain");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "one");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "token");

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_multi



/// Test the handling of two tokens directly following each other, which should
/// result in an empty token returned.
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_double)
{

   const std::string    str( "two tokens  directly following");
   Separator            sep( '\\', ' ', '"');
   Tokenizer            t( str, sep);
   Tokenizer::iterator  it = t.begin();


   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "two");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "tokens");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE( it->empty());

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "directly");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "following");

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_double



/// The main feature: Test that a quoted string is not split into tokens.
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_quoted)
{

   const std::string    str( "my multi-token string with \"a string within a string\"");
   Separator            sep( '\\', ' ', '"');
   Tokenizer            t( str, sep);
   Tokenizer::iterator  it = t.begin();


   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "my");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "multi-token");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "string");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "with");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "a string within a string");

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_quoted



/// Test with multiple separators and multiple quotes.
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_multiply_quoted)
{

   const std::string    str( "my 'multi token' \\\"string\\\" with \"a string within a string\", followed by more");
   Separator            sep( "\\", " ,", "\"'");
   Tokenizer            t( str, sep);
   Tokenizer::iterator  it = t.begin();


   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "my");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "multi token");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "\"string\"");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "with");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "a string within a string");

   // comma and space: two subsequent separators
   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE( it->empty());

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "followed");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "by");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "more");

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_multiply_quoted



// =====  END OF test_tokenizer_base.cpp  =====

