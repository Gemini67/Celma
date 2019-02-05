
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
**    Test program for the module Tokenizer using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/common/tokenizer.hpp"


// Boost includes
#define BOOST_TEST_MODULE TestTokenizer
#include <boost/test/unit_test.hpp>


using celma::common::Tokenizer;
using std::string;



/// Call tokenizer for an empty string.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_empty)
{

   const string  s;
   Tokenizer     t( s, ',');
   auto          it = t.begin();


   BOOST_REQUIRE( it == t.end());

} // test_empty



/// Call tokenizer for a string that does not contain the token.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_one)
{

   const string  s( "string that does not contain the token");
   Tokenizer     t( s, ',');
   auto          it = t.begin();


   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, s);

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_one



/// Split string with multiple tokens.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_multi)
{

   const string  s( "string that does not contain the token");
   Tokenizer     t( s, ' ');
   auto          it = t.begin();


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
   BOOST_REQUIRE_EQUAL( *it, "not");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "contain");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "the");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "token");

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_multi



/// Test the handling of two tokens directly following each other, which should
/// be ignored.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_double)
{

   const string  s( "two tokens  directly following");
   Tokenizer     t( s, ' ');
   auto          it = t.begin();


   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "two");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "tokens");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "directly");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "following");

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_double



/// Test the handling of two tokens directly following each other, which should
/// lead to one empty token.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_double_detected)
{

   const string  s( "two tokens  directly following");
   Tokenizer     t( s, ' ', true);
   auto          cit = t.begin_counting();


   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "two");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 0);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "tokens");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 1);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE( cit->empty());
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 2);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "directly");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 3);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "following");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 4);

   ++cit;
   BOOST_REQUIRE( cit == t.end());

} // test_double_detected



/// Test that multiple empty tokens are correctly ignored.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_multiple_empty_ignored)
{

   const string  s( " string with  multiple   empty tokens  ");
   Tokenizer     t( s, ' ');
   auto          it = t.begin();


   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "string");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "with");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "multiple");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "empty");

   ++it;
   BOOST_REQUIRE( it != t.end());
   BOOST_REQUIRE_EQUAL( *it, "tokens");

   ++it;
   BOOST_REQUIRE( it == t.end());

} // test_multiple_empty_ignored



/// Test the handling of multiple empty tokens due to leading/cosecutive/
/// trailing separator characters.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_multiple_empty_detected)
{

   const string  s( " string with  multiple   empty tokens  ");
   Tokenizer     t( s, ' ', true);
   auto          cit = t.begin_counting();


   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE( cit->empty());
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 0);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "string");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 1);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "with");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 2);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE( cit->empty());
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 3);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "multiple");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 4);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE( cit->empty());
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 5);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE( cit->empty());
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 6);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "empty");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 7);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE_EQUAL( *cit, "tokens");
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 8);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE( cit->empty());
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 9);

   ++cit;
   BOOST_REQUIRE( cit != t.end());
   BOOST_REQUIRE( cit->empty());
   BOOST_REQUIRE_EQUAL( cit.currentNum(), 10);

   ++cit;
   BOOST_REQUIRE( cit == t.end());

} // test_multiple_empty_detected



/// Verify that two nested tokenizers don't interfere with each other.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_nested)
{

   const string  s( "phrase one.phrase two.short phrase three.");
   Tokenizer     t( s, '.');
   int           tokenNum = 0;


   for (auto const& token : t)
   {
      if (tokenNum == 0)
         BOOST_REQUIRE_EQUAL( token, "phrase one");
      else if (tokenNum == 1)
         BOOST_REQUIRE_EQUAL( token, "phrase two");
      else if (tokenNum == 2)
         BOOST_REQUIRE_EQUAL( token, "short phrase three");
      else
         BOOST_REQUIRE( tokenNum == 0);

      Tokenizer  t2( token, ' ');
      int        tokenNum2 = 0;

      for (auto const& token2 : t2)
      {
         if (tokenNum == 0)
         {
            if (tokenNum2 == 0)
               BOOST_REQUIRE_EQUAL( token2, "phrase");
            else if (tokenNum2 == 1)
               BOOST_REQUIRE_EQUAL( token2, "one");
            else
               BOOST_REQUIRE( tokenNum2 == 0);
         } else if (tokenNum == 1)
         {
            if (tokenNum2 == 0)
               BOOST_REQUIRE_EQUAL( token2, "phrase");
            else if (tokenNum2 == 1)
               BOOST_REQUIRE_EQUAL( token2, "two");
            else
               BOOST_REQUIRE( tokenNum2 == 0);
         } else
         {
            if (tokenNum2 == 0)
               BOOST_REQUIRE_EQUAL( token2, "short");
            else if (tokenNum2 == 1)
               BOOST_REQUIRE_EQUAL( token2, "phrase");
            else if (tokenNum2 == 2)
               BOOST_REQUIRE_EQUAL( token2, "three");
            else
               BOOST_REQUIRE( tokenNum2 == 0);
         } // end if

         ++tokenNum2;
      } // end for

      if (tokenNum == 0)
         BOOST_REQUIRE_EQUAL( tokenNum2, 2);
      else if (tokenNum == 1)
         BOOST_REQUIRE_EQUAL( tokenNum2, 2);
      else if (tokenNum == 2)
         BOOST_REQUIRE_EQUAL( tokenNum2, 3);

      ++tokenNum;
   } // end for

   BOOST_REQUIRE_EQUAL( tokenNum, 3);

} // test_nested



/// Verify that two nested tokenizers don't interfere with each other.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_nested_counting)
{

   const string  s( "phrase one.phrase two.short phrase three.");
   Tokenizer     t( s, '.');


   for (auto cit = t.begin_counting(); cit != t.end_counting(); ++cit)
   {
      const string&  token( *cit);

      if (cit.currentNum() == 0)
         BOOST_REQUIRE_EQUAL( token, "phrase one");
      else if (cit.currentNum() == 1)
         BOOST_REQUIRE_EQUAL( token, "phrase two");
      else if (cit.currentNum() == 2)
         BOOST_REQUIRE_EQUAL( token, "short phrase three");
      else
         BOOST_REQUIRE( cit.currentNum() == 0);

      Tokenizer  t2( token, ' ');

      for (auto cit2 = t2.begin_counting(); cit2 != t2.end(); ++cit2)
      {
         const string&  token2( *cit2);

         if (cit.currentNum() == 0)
         {
            if (cit2.currentNum() == 0)
               BOOST_REQUIRE_EQUAL( token2, "phrase");
            else if (cit2.currentNum() == 1)
               BOOST_REQUIRE_EQUAL( token2, "one");
            else
               BOOST_REQUIRE( cit2.currentNum() == 0);
         } else if (cit.currentNum() == 1)
         {
            if (cit2.currentNum() == 0)
               BOOST_REQUIRE_EQUAL( token2, "phrase");
            else if (cit2.currentNum() == 1)
               BOOST_REQUIRE_EQUAL( token2, "two");
            else
               BOOST_REQUIRE( cit2.currentNum() == 0);
         } else
         {
            if (cit2.currentNum() == 0)
               BOOST_REQUIRE_EQUAL( token2, "short");
            else if (cit2.currentNum() == 1)
               BOOST_REQUIRE_EQUAL( token2, "phrase");
            else if (cit2.currentNum() == 2)
               BOOST_REQUIRE_EQUAL( token2, "three");
            else
               BOOST_REQUIRE( cit2.currentNum() == 0);
         } // end if
      } // end for

      if (cit.currentNum() == 0)
         BOOST_REQUIRE_EQUAL( t2.numTokens(), 2);
      else if (cit.currentNum() == 1)
         BOOST_REQUIRE_EQUAL( t2.numTokens(), 2);
      else if (cit.currentNum() == 2)
         BOOST_REQUIRE_EQUAL( t2.numTokens(), 3);
   } // end for

   BOOST_REQUIRE_EQUAL( t.numTokens(), 3);

} // test_nested_counting



// =====  END OF test_tokenizer.cpp  =====

