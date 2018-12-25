
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module under test header file include
#include "celma/common/find_sequence.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE FindSequenceTest
#include <boost/test/unit_test.hpp>


using celma::common::find_sequence_end;
using celma::common::find_sequence_start;
using std::string;



/// Find the end of a simple sequence.
/// @since  0.5, 05.11.2016
BOOST_AUTO_TEST_CASE( test_simple_sequence)
{

   // sequence in middle of string
   {
      const string  seq( "y = x + (x * 3) + 11");
      auto          seq_start = std::begin( seq) + seq.find( '(');
      auto          seq_end = find_sequence_end( seq_start, std::end( seq), ')');

      BOOST_REQUIRE_EQUAL( seq_end - begin( seq), seq.find( ')'));
   } // end scope

   // sequence at end of string
   {
      const string  seq( "y = x + (x * 3)");
      auto          seq_start = std::begin( seq) + seq.find( '(');
      auto          seq_end = find_sequence_end( seq_start, std::end( seq), ')');

      BOOST_REQUIRE_EQUAL( seq_end - begin( seq), seq.find( ')'));
   } // end scope

   // string == sequence
   {
      const string  seq( "(x + y + z)");
      auto          seq_start = std::begin( seq) + seq.find( '(');
      auto          seq_end = find_sequence_end( seq_start, std::end( seq), ')');

      BOOST_REQUIRE_EQUAL( seq_end - begin( seq), seq.find( ')'));
   } // end scope

   // another sequence at end of string, should be ignored
   {
      const string  seq( "(x + y + z) - (x * y)");
      auto          seq_start = std::begin( seq) + seq.find( '(');
      auto          seq_end = find_sequence_end( seq_start, std::end( seq), ')');

      BOOST_REQUIRE_EQUAL( seq_end - begin( seq), seq.find( ')'));
   } // end scope

} // test_simple_sequence



/// Handle nested sequences correctly.
/// @since  0.5, 05.11.2016
BOOST_AUTO_TEST_CASE( test_nested_sequences)
{

   // nested sequence in middle of string
   {
      const string  seq( "x + (x * (x - 4) / 7) + 11");
      auto          seq_start = std::begin( seq) + seq.find( '(');
      auto          seq_end = find_sequence_end( seq_start, std::end( seq), ')');

      BOOST_REQUIRE_EQUAL( seq_end - begin( seq), seq.find_last_of( ')'));
   } // end scope

   // sequence with two nested sequences
   {
      const string  seq( "(x * (x - 4) / (x + 9) - 7) + 11");
      auto          seq_start = std::begin( seq) + seq.find( '(');
      auto          seq_end = find_sequence_end( seq_start, std::end( seq), ')');

      BOOST_REQUIRE_EQUAL( seq_end - begin( seq), seq.find_last_of( ')'));
   } // end scope

   // nested sequence at beginning of string
   {
      const string  seq( "((x + y) * z)");
      auto          seq_start = std::begin( seq) + seq.find( '(');
      auto          seq_end = find_sequence_end( seq_start, std::end( seq), ')');

      BOOST_REQUIRE_EQUAL( seq_end - begin( seq), seq.find_last_of( ')'));
   } // end scope

   // nested sequence at beginning and end of string
   {
      const string  seq( "((x + y) * (x + z))");
      auto          seq_start = std::begin( seq) + seq.find( '(');
      auto          seq_end = find_sequence_end( seq_start, std::end( seq), ')');

      BOOST_REQUIRE_EQUAL( seq_end - begin( seq), seq.find_last_of( ')'));

      auto  seq2( seq);
      seq2.append( " * (x + y)");

      auto  seq2_start = std::begin( seq2) + seq2.find( '(');
      auto  seq2_end = find_sequence_end( seq2_start, std::end( seq2), ')');

      // still use seq (! 2) to find the end of the sequence (returns pos)
      BOOST_REQUIRE_EQUAL( seq2_end - begin( seq2), seq.find_last_of( ')'));
   } // end scope

} // test_nested_sequences



/// Find the end of a simple sequence, searching backwards.
/// @since  0.5, 05.11.2016
BOOST_AUTO_TEST_CASE( test_simple_sequence_backward)
{

   // sequence in middle of string
   {
      const string  seq( "y = x + (x * 3) + 11");
      auto          seq_end = std::begin( seq) + seq.find_last_of( ')');
      auto          seq_start = find_sequence_start( seq_end, std::begin( seq), '(');

      BOOST_REQUIRE_EQUAL( seq_start - begin( seq), seq.find( '('));
   } // end scope

   // sequence at end of string
   {
      const string  seq( "y = x + (x * 3)");
      auto          seq_end = std::begin( seq) + seq.find_last_of( ')');
      auto          seq_start = find_sequence_start( seq_end, std::begin( seq), '(');

      BOOST_REQUIRE_EQUAL( seq_start - begin( seq), seq.find( '('));
   } // end scope

   // string == sequence
   {
      const string  seq( "(x + y + z)");
      auto          seq_end = std::begin( seq) + seq.find_last_of( ')');
      auto          seq_start = find_sequence_start( seq_end, std::begin( seq), '(');

      BOOST_REQUIRE_EQUAL( seq_start - begin( seq), seq.find( '('));
   } // end scope

   // another sequence at beginning of string, should be ignored
   {
      const string  seq( "(x * y) - (x + y + z)");
      auto          seq_end = std::begin( seq) + seq.find_last_of( ')');
      auto          seq_start = find_sequence_start( seq_end, std::begin( seq), '(');

      BOOST_REQUIRE_EQUAL( seq_start - begin( seq), 10L);
   } // end scope

} // test_simple_sequence_backward



/// Handle nested sequences correctly, searching backward.
/// @since  0.5, 05.11.2016
BOOST_AUTO_TEST_CASE( test_nested_sequences_backward)
{

   // nested sequence in middle of string
   {
      const string  seq( "x + (x * (x - 4) / 7) + 11");
      auto          seq_end = std::begin( seq) + seq.find_last_of( ')');
      auto          seq_start = find_sequence_start( seq_end, std::begin( seq), '(');

      BOOST_REQUIRE_EQUAL( seq_start - begin( seq), seq.find( '('));
   } // end scope

   // sequence with two nested sequences
   {
      const string  seq( "(x * (x - 4) / (x + 9) - 7) + 11");
      auto          seq_end = std::begin( seq) + seq.find_last_of( ')');
      auto          seq_start = find_sequence_start( seq_end, std::begin( seq), '(');

      BOOST_REQUIRE_EQUAL( seq_start - begin( seq), seq.find( '('));
   } // end scope

   // nested sequence at beginning of string
   {
      const string  seq( "((x + y) * z)");
      auto          seq_end = std::begin( seq) + seq.find_last_of( ')');
      auto          seq_start = find_sequence_start( seq_end, std::begin( seq), '(');

      BOOST_REQUIRE_EQUAL( seq_start - begin( seq), seq.find( '('));
   } // end scope

   // nested sequence at beginning and end of string
   {
      const string  seq( "((x + y) * (x + z))");
      auto          seq_end = std::begin( seq) + seq.find_last_of( ')');
      auto          seq_start = find_sequence_start( seq_end, std::begin( seq), '(');

      BOOST_REQUIRE_EQUAL( seq_start - begin( seq), seq.find( '('));

      string  seq2( "(x + y) * ");
      seq2.append( seq);

      auto  seq2_end = std::begin( seq2) + seq2.find_last_of( ')');
      auto  seq2_start = find_sequence_start( seq2_end, std::begin( seq2), '(');

      BOOST_REQUIRE_EQUAL( seq2_start - begin( seq2), 10L);
   } // end scope

} // test_nested_sequences_backward



// =====  END OF test_find_sequence.cpp  =====

