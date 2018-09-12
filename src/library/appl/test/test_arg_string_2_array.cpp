
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


// module to test header file include
#include "celma/appl/arg_string_2_array.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgString2ArrayTest
#include <boost/test/unit_test.hpp>


using celma::appl::ArgString2Array;


/// Test argument strings without an argument.
/// @since  0.2, 05.0.4.2016
BOOST_AUTO_TEST_CASE( no_arguments)
{

   {
      const ArgString2Array  as2a( "", nullptr);
      BOOST_REQUIRE_EQUAL( as2a.mArgC, 1);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE( as2a.mpArgV[ 1] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "", "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mArgC, 1);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE( as2a.mpArgV[ 1] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mArgC, 1);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE( as2a.mpArgV[ 1] == nullptr);
   } // end scope

} // no_arguments



/// Test argument strings with a single argument.
/// @since  6.0, 23.09.2013
BOOST_AUTO_TEST_CASE( single_argument)
{

   {
      const ArgString2Array  as2a( "-v", nullptr);
      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v", "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name -v");
      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

} // single_argument



/// Test handling of an argument with multiple words (quoted).
/// @since  0.2, 05.0.4.2016
BOOST_AUTO_TEST_CASE( multi_word_value)
{

   {
      const ArgString2Array  as2a( "-v 'my multi-word value'", nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v 'my multi-word value'", "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name -v 'my multi-word value'");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v \"my multi-word value\"", nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v \"my multi-word value\"",
         "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "-v \"my multi-word value\"");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "--value='my multi-word value'", nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "--value=my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "--value='my multi-word value'",
         "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "--value=my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "--value='my multi-word value'");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "--value=my multi-word value");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "--value==\"it's my party\"", nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "--value==it's my party");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "--value==\"it's my party\"",
         "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "--value==it's my party");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "--value==\"it's my party\"");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "--value==it's my party");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "--value==\"it's my 'official' party\"");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "--value==it's my 'official' party");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "--value=='it is my \"official\" party'");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1],
         "--value==it is my \"official\" party");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "--value=='it\\'s my \"official\" party'");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1],
         "--value==it's my \"official\" party");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      // example of complex nesting and escaping:
      // - the whole argument is framed by double quotes, which will be cut away
      //   when the argument line is split
      // - inside that, the whole argument is also framed by single quotes,
      //   which should remain there
      // - there's a word in double quotes inside the argument, and we want
      //   these quotes to be passed on
      //   so, the quotes must be preceded by a backslash in the string passed
      //   to the argument splitter, and the quote itself must be preceded by
      //   a backslash for the C++ compiler, so 3 backslashes
      //   (the resulting string will contain \" which will result in ")
      // - finally, we want a single quote in the resulting string
      //   this needs to be escaped in the resulting string too (to not
      //   interfere with the quotes around the whole text), so we need 3
      //   backslashes to pass (written as 6 backslashes of course):
      //   - source code:      it\\\\\\'s
      //   - string:           it\\\'s
      //   - parsed argument:  it\'s
      const ArgString2Array  as2a( "my_own_program_name "
         "--value==\"'it\\\\\\'s my \\\"official\\\" party'\"");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1],
         "--value=='it\\'s my \"official\" party'");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

} // multi_word_value



/// Test handling of an argument with mixed quotes.
/// @since  0.2, 05.0.4.2016
BOOST_AUTO_TEST_CASE( mixed_quotes)
{

   {
      const ArgString2Array  as2a( "-v \"my child's pet\"", nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my child's pet");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v \"my child's pet\"",
         "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my child's pet");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name -v \"my child's pet\"");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my child's pet");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v 'my \"best\" idea'", nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my \"best\" idea");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v 'my \"best\" idea'",
         "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my \"best\" idea");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name -v 'my \"best\" idea'");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 3);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my \"best\" idea");
      BOOST_REQUIRE( as2a.mpArgV[ 3] == nullptr);
   } // end scope

} // mixed_quotes



/// Test handling of multiple arguments with multiple words (quoted).
/// @since  0.2, 05.0.4.2016
BOOST_AUTO_TEST_CASE( multiple_multi_word_value)
{

   {
      const ArgString2Array  as2a( "-v 'my multi-word value' -w 'two words'",
         nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v 'my multi-word value' -w 'two words'",
                                     "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "-v 'my multi-word value' -w 'two words'");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v 'my multi-word value' -w \"two words\"",
         nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v 'my multi-word value' -w \"two words\"",
                                     "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name -v 'my multi-word value' "
                                     "-w \"two words\"");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v \"my multi-word value\" -w 'two words'",
         nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v \"my multi-word value\" -w 'two words'",
                                     "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "-v \"my multi-word value\" -w 'two words'");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v \"my multi-word value\" -w \"two words\"",
         nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v \"my multi-word value\" -w \"two words\"",
                                     "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name "
         "-v \"my multi-word value\" -w \"two words\"");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 5);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "my multi-word value");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "-w");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "two words");
      BOOST_REQUIRE( as2a.mpArgV[ 5] == nullptr);
   } // end scope

} // multiple_multi_word_value



/// Test argument strings with one free argument.
/// @since  0.2, 05.0.4.2016
BOOST_AUTO_TEST_CASE( one_free)
{

   {
      const ArgString2Array  as2a( "my_name", nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "my_name");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_name", "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "my_name");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name my_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 2);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "my_name");
      BOOST_REQUIRE( as2a.mpArgV[ 2] == nullptr);
   } // end scope

} // one_free



/// Test argument strings with a multiple arguments.
/// @since  0.2, 05.0.4.2016
BOOST_AUTO_TEST_CASE( multiple_arguments)
{

   {
      const ArgString2Array  as2a( "-v -d /tmp --name=proc1 --limit 17 -- -s -5",
         nullptr);

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 10);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "programname");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "-d");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "/tmp");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "--name=proc1");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 5], "--limit");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 6], "17");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 7], "--");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 8], "-s");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 9], "-5");
      BOOST_REQUIRE( as2a.mpArgV[ 10] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "-v -d /tmp --name=proc1 --limit 17 -- -s -5",
                                     "my_own_program_name");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 10);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "-d");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "/tmp");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "--name=proc1");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 5], "--limit");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 6], "17");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 7], "--");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 8], "-s");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 9], "-5");
      BOOST_REQUIRE( as2a.mpArgV[ 10] == nullptr);
   } // end scope

   {
      const ArgString2Array  as2a( "my_own_program_name -v -d /tmp --name=proc1 "
                                     "--limit 17 -- -s -5");

      BOOST_REQUIRE_EQUAL( as2a.mArgC, 10);
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 0], "my_own_program_name");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 1], "-v");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 2], "-d");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 3], "/tmp");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 4], "--name=proc1");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 5], "--limit");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 6], "17");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 7], "--");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 8], "-s");
      BOOST_REQUIRE_EQUAL( as2a.mpArgV[ 9], "-5");
      BOOST_REQUIRE( as2a.mpArgV[ 10] == nullptr);
   } // end scope

} // multiple_arguments



// =====  END OF test_arg_string_2_array.cpp  =====

