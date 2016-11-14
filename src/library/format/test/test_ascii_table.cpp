
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the module AsciiTable using the Boost.Test
**    framework.
**
--*/


// header file include of the module to test
#include "celma/format/ascii_table.hpp"


// Boost includes
#define BOOST_TEST_MODULE AsciiTableTest
#include <boost/test/unit_test.hpp>


using celma::format::AsciiTable;


/// Test with format string that contains only the titles.
/// @since  0.7, 07.11.2016
BOOST_AUTO_TEST_CASE( test_title_only)
{

   {
      const AsciiTable  at( "First Title[]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "-----------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s"));
   } // end scope

   {
      const AsciiTable  at( "-First Title[]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "-----------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s"));
   } // end scope

   {
      const AsciiTable  at( "First Title[]  Second Title[]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title  Second Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "-----------  ------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s  %12s"));
   } // end scope

   {
      const AsciiTable  at( "First Title[]  Second Title[]   -Third Title[]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title  Second Title   Third Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "-----------  ------------   -----------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s  %12s   %11s"));
   } // end scope

} // test_title_only



/// Tests with format strings that contain a length specification.
/// Test with format string that contains only the titles.
/// @since  0.7, 07.11.2016
BOOST_AUTO_TEST_CASE( test_title_length)
{

   {
      const AsciiTable  at( "First Title[20]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s"));
   } // end scope

   {
      const AsciiTable  at( "-First Title[20]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title         "));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s"));
   } // end scope

   {
      const AsciiTable  at( "First Title[20]  -Second Title[30]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title  Second Title                  "));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------  ------------------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s  %30s"));
   } // end scope

} // test_title_length



/// Tests with format string that should influence only the length of the dashes
/// line.
/// @since  0.7, 07.11.2016
BOOST_AUTO_TEST_CASE( test_dashes_length)
{

   {
      const AsciiTable  at( "First Title[20]  -Second Title[d30]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title  Second Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------  ------------------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s  %s"));
   } // end scope

} // end test_dashes_length



/// Test quoting special characters in the title ('[', not necessary for ']').
/// @since  1.1, 22.08.2016  (integrated into foundation)
/// @since  15.06.2016
BOOST_AUTO_TEST_CASE( test_quoting)
{

   {
      const AsciiTable  at( "Rate \\[msgs/s][13.3,f]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "Rate [msgs/s]"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "-------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%13.3f"));
   } // end scope

} // end test_quoting



/// Test titles with a hash character (#) at the beginning of a title.
/// @since  1.1, 24.08.2016
BOOST_AUTO_TEST_CASE( test_hash_char)
{

   {
      const AsciiTable  at( "-# msgs[12,lu]\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "# msgs      \n"));

      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%12lu\n"));
   } // end scope

   {
      const AsciiTable  at( "# msgs[12,lu]\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "      # msgs\n"));

      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%12lu\n"));
   } // end scope

   {
      const AsciiTable  at( "-First[10,s]  -# msgs[12,lu]\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First       # msgs      \n"));

      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "----------  ------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%10s  %12lu\n"));
   } // end scope

   {
      const AsciiTable  at( "First[10,s]  # msgs[12,lu]\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "     First        # msgs\n"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "----------  ------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%10s  %12lu\n"));
   } // end scope

} // test_hash_char



/// Format strings with length, format, left/right align ...
/// @since  0.7, 07.11.2016
BOOST_AUTO_TEST_CASE( test_formats)
{

   {
      const AsciiTable  at( "Second Title[-30]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "                  Second Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "------------------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%-30s"));
   } // end scope

   {
      const AsciiTable  at( "Third Title[11.3,f]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "Third Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "-----------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11.3f"));
   } // end scope

   {
      const AsciiTable  at( "-Last Title[20,d]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "Last Title          "));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20d"));
   } // end scope

   {
      const AsciiTable  at( "First Title[]  Second Title[-30,lu] Third Title[11.3,f]   -Last Title[20,d]");

      BOOST_REQUIRE_EQUAL( at.titleLine(),
                           std::string( "First Title                    Second Title Third Title   Last Title          "));
      BOOST_REQUIRE_EQUAL( at.dashesLine(),
                           std::string( "-----------  ------------------------------ -----------   --------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s  %-30lu %11.3f   %20d"));
   } // end scope

} // test_formats



/// Format string with end-of-line character.
/// @since  0.7, 07.11.2016
BOOST_AUTO_TEST_CASE( test_eol)
{

   {
      const AsciiTable  at( "First Title[]\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title\n"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "-----------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s\n"));
   } // end scope

   {
      const AsciiTable  at( "First Title[] Second Title[]\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title Second Title\n"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "----------- ------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s %12s\n"));
   } // end scope

   {
      const AsciiTable  at( "First Title[] Second Title[20,lu]\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title         Second Title\n"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "----------- --------------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s %20lu\n"));
   } // end scope

   {
      const AsciiTable  at( "First Title[] -Second Title[20,lu]\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "First Title Second Title        \n"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "----------- --------------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%11s %20lu\n"));
   } // end scope

} // test_eol



/// Test if the handling of the dash character works correctly.<br>
/// The dash character set by setDashChar() is used by all subsequently created
/// objects. However, it is possible to specify a different dash character when
/// an object is created, but this dash character should then only be used for
/// this object.
/// @since  0.7, 07.11.2016
BOOST_AUTO_TEST_CASE( test_dash_char)
{

   AsciiTable::setDashChar( '=');

   {
      const AsciiTable  at( "First Title[20]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "===================="));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s"));
   } // end scope

   {
      const AsciiTable  at( "First Title[20]", '-');

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s"));
   } // end scope

   {
      const AsciiTable  at( "First Title[20]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "===================="));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s"));
   } // end scope

} // test_dash_char



/// Tests appending columns to an existing table.
/// @since  0.7, 07.11.2016
BOOST_AUTO_TEST_CASE( test_append)
{

   AsciiTable::setDashChar( '-');

   {
      AsciiTable  at( "First Title[20]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s"));

      at.append( "  -Second Title[d30]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title  Second Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------  ------------------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s  %s"));

      at.append( "\n");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title  Second Title\n"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------  ------------------------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s  %s\n"));
   } // end scope

} // test_append



/// Verify that table specifications are generated correctly.
/// @since  0.7, 07.11.2016
BOOST_AUTO_TEST_CASE( test_generate_spec)
{

   // first test: no additional parameters
   {
      AsciiTable  at( '\0', "First Title[20]");

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "         First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "--------------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%20s"));
   } // end scope

   // next test: one additional parameter
   {
      AsciiTable  at( '\0', "First Title[%d]", 15);

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "    First Title"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(), std::string( "---------------"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%15s"));
   } // end scope

   // final test: many additional parameters, %-sign in table spec
   {
      AsciiTable  at( '\0', "First Title[%d]  Second Title[%d,d]   -Last Title \\[%%][d%d]\n", 15, 25, 40);

      BOOST_REQUIRE_EQUAL( at.titleLine(), std::string( "    First Title               Second Title   Last Title [%]\n"));
      BOOST_REQUIRE_EQUAL( at.dashesLine(),
                           std::string( "---------------  -------------------------   ----------------------------------------\n"));
      BOOST_REQUIRE_EQUAL( at.formatString(), std::string( "%15s  %25d   %s\n"));
   } // end scope

} // test_generate_spec



// =======================  END OF test_ascii_table.cpp  =======================
