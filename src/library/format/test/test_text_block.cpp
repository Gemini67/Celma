
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
**    Test program for the functions of the module TextBlock.
**
--*/


// module to test header file include
#include "celma/format/text_block.hpp"


// C++ Standard Library includes
#include <sstream>
#include <string>


// Boost includes
#define BOOST_TEST_MODULE TextBlockTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/multiline_string_compare.hpp"


using celma::format::TextBlock;
using std::ostringstream;
using std::string;



/// Tests block formatting with indent 0, line length 80 and 'indent first'
/// set to \c false.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_Formatting_0_80_false)
{

   TextBlock      tb( 0, 80, false);
   string         input( "This is the string with the input to format");
   ostringstream  result;
   string         expResult( "This is the string with the input to format");


   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input += ". Append more text with an unbelievable_impossible_ridiculous long word at then end.";
   expResult = "This is the string with the input to format. Append more text with an\n"
               "unbelievable_impossible_ridiculous long word at then end.";
   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input = "New test with a string with a lot of short words which make it "
           "easier to split the string to multiple lines. Actually we make "
           "this string so long that it will use more than two lines (four, "
           "to be precise) in the resulting result string that is returned "
           "from the TextBlock formatting routine.";
   expResult = "New test with a string with a lot of short words which make it easier to split\n"
               "the string to multiple lines. Actually we make this string so long that it will\n"
               "use more than two lines (four, to be precise) in the resulting result string\n"
               "that is returned from the TextBlock formatting routine.";

   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input = "Last but not least:\n"
           "Format a string that includes:\n"
           "- line breaks\n"
           "- very long lines starting with a dash which is detected by the "
           "formatting library/method and leads to an automatic indent of "
           "the following lines.\n"
           "- new feature: nn Forced line break within a list entry.\n"
           "- and finally: test of a long line with a dash at the beginning "
           "and a forced line break somewhere (here:\n) in the text. Should "
           "result in text starting at the beginning of the line again.";
   expResult = "Last but not least:\n"
               "Format a string that includes:\n"
               "- line breaks\n"
               "- very long lines starting with a dash which is detected by the formatting\n"
               "  library/method and leads to an automatic indent of the following lines.\n"
               "- new feature:\n"
               "  Forced line break within a list entry.\n"
               "- and finally: test of a long line with a dash at the beginning and a forced\n"
               "  line break somewhere (here:\n"
               ") in the text. Should result in text starting at the beginning of the line\n"
               "again.";

   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

} // test_Formatting_0_80_false



/// Tests block formatting with indent 10, line length 80 and 'indent first'
/// set to \c true.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_Formatting_10_80_true)
{

   TextBlock      tb( 10, 80, true);
   string         input( "This is the string with the input to format");
   ostringstream  result;
   string         expResult( "          This is the string with the input to format");


   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input += ". Append more text with an unbelievable_impossible_ridiculous long word at then end.";
   expResult = "          This is the string with the input to format. Append more text with an\n"
               "          unbelievable_impossible_ridiculous long word at then end.";
   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input = "New test with a string with a lot of short words which make it "
           "easier to split the string to multiple lines. Actually we make "
           "this string so long that it will use more than two lines (four, "
           "to be precise) in the resulting result string that is returned "
           "from the TextBlock formatting routine.";
   expResult = "          New test with a string with a lot of short words which make it easier\n"
               "          to split the string to multiple lines. Actually we make this string so\n"
               "          long that it will use more than two lines (four, to be precise) in the\n"
               "          resulting result string that is returned from the TextBlock formatting\n"
               "          routine.";

   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input = "Last but not least:\n"
           "Format a string that includes:\n"
           "- line breaks\n"
           "- very long lines starting with a dash which is detected by the "
           "formatting library/method and leads to an automatic indent of "
           "the following lines.\n"
           "- new feature: nn Forced line break within a list entry.\n"
           "- and finally: test of a long line with a dash at the beginning "
           "and a forced line break somewhere (here:\n) in the text. Should "
           "result in text starting at the beginning of the line again.";
   expResult = "          Last but not least:\n"
               "          Format a string that includes:\n"
               "          - line breaks\n"
               "          - very long lines starting with a dash which is detected by the\n"
               "            formatting library/method and leads to an automatic indent of the\n"
               "            following lines.\n"
               "          - new feature:\n"
               "            Forced line break within a list entry.\n"
               "          - and finally: test of a long line with a dash at the beginning and a\n"
               "            forced line break somewhere (here:\n"
               "          ) in the text. Should result in text starting at the beginning of the\n"
               "          line again.";

   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

} // test_Formatting_10_80_true



/// Tests block formatting with indent 10, line length 70 and 'indent first'
/// set to true.
///
/// @since  0.2, 04.04.2016
BOOST_AUTO_TEST_CASE( test_Formatting_5_75_true)
{

   TextBlock      tb( 5, 75, true);
   string         input( "This is the string with the input to format");
   ostringstream  result;
   string         expResult( "     This is the string with the input to format");


   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input += ". Append more text with an unbelievable_impossible_ridiculous long word at then end.";
   expResult = "     This is the string with the input to format. Append more text with an\n"
               "     unbelievable_impossible_ridiculous long word at then end.";
   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input = "New test with a string with a lot of short words which make it "
           "easier to split the string to multiple lines. Actually we make "
           "this string so long that it will use more than two lines (four, "
           "to be precise) in the resulting result string that is returned "
           "from the TextBlock formatting routine.";
   expResult = "     New test with a string with a lot of short words which make it easier\n"
               "     to split the string to multiple lines. Actually we make this string so\n"
               "     long that it will use more than two lines (four, to be precise) in the\n"
               "     resulting result string that is returned from the TextBlock formatting\n"
               "     routine.";

   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

   input = "Last but not least:\n"
           "Format a string that includes:\n"
           "- line breaks\n"
           "- very long lines starting with a dash which is detected by the "
           "formatting library/method and leads to an automatic indent of "
           "the following lines.\n"
           "- new feature: nn Forced line break within a list entry.\n"
           "- and finally: test of a long line with a dash at the beginning "
           "and a forced line break somewhere (here:\n) in the text. Should "
           "result in text starting at the beginning of the line again.";
   expResult = "     Last but not least:\n"
               "     Format a string that includes:\n"
               "     - line breaks\n"
               "     - very long lines starting with a dash which is detected by the\n"
               "       formatting library/method and leads to an automatic indent of the\n"
               "       following lines.\n"
               "     - new feature:\n"
               "       Forced line break within a list entry.\n"
               "     - and finally: test of a long line with a dash at the beginning and a\n"
               "       forced line break somewhere (here:\n"
               "     ) in the text. Should result in text starting at the beginning of the\n"
               "     line again.";

   result.str( "");
   tb.format( result, input);
   BOOST_REQUIRE( celma::test::multilineStringCompare( result.str(), expResult));

} // test_Formatting_5_75_true



// =====  END OF test_text_block.cpp  =====

