
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
**    Test program for the module ArgListParser using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// STL includes
#include <string>
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE ArgumentHandlerTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/detail/arg_list_parser.hpp"
#include "celma/common/arg_string_2_array.hpp"


using namespace std;
using namespace celma;


// module definitions
typedef std::vector< std::string>  StringVec;



/// Test handling of one single character as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( single_char)
{

   common::ArgString2Array           as2a( "-v", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end single_char



/// Test handling of two single characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_single_char)
{

   common::ArgString2Array           as2a( "-lv", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end two_single_char



/// Test handling of two single, separate characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_single_char_sep)
{

   common::ArgString2Array           as2a( "-l -v", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end two_single_char_sep



/// Test handling of three single characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char)
{

   common::ArgString2Array           as2a( "-lva", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end three_single_char



/// Test handling of three single, separate characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char_sep)
{

   common::ArgString2Array           as2a( "-l -v -a", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end three_single_char_sep



/// Test handling of three single characters (one/pair) as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char_mixed1)
{

   common::ArgString2Array           as2a( "-lv -a", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end three_single_char_mixed1



/// Test handling of three single characters (one/pair) as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char_mixed2)
{

   common::ArgString2Array           as2a( "-l -va", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end three_single_char_mixed2



/// Test handling of one long argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( single_long)
{

   common::ArgString2Array           as2a( "--verbose", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verbose");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end single_long



/// Test handling of two long arguments.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_long)
{

   common::ArgString2Array           as2a( "--verbose --careful", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verbose");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "careful");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end two_long



/// Test handling of mixed short and long arguments.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_long)
{

   common::ArgString2Array           as2a( "-v --verbose -s0l --careful -x", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verbose");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 's');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, '0');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "careful");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'x');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end two_long



/// Test handling of one single character argument with a value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_value)
{

   common::ArgString2Array           as2a( "-f filename", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end short_value



/// Test handling of one long argument with a value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( long_value)
{

   common::ArgString2Array           as2a( "--inputfile filename", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "inputfile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end long_value



/// Test handling of two long arguments with values.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_long_value)
{

   common::ArgString2Array           as2a( "--verboselevel 8 --inputfile=filename", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verboselevel");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "8");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "inputfile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end two_long_value



/// Test handling of two long arguments with values.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_long_value)
{

   common::ArgString2Array           as2a( "--verboselevel 8 --inputfile=filename --another=attempt", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verboselevel");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "8");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "inputfile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "another");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "attempt");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end three_long_value



/// Test handling of four arguments (short, long, long, short) with values.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_long_long_short)
{

   common::ArgString2Array           as2a( "-i input --outputfile filename --filter=everything -q always", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'i');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "input");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "outputfile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filter");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "everything");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'q');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "always");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end short_long_long_short



/// Test handling a single, positional value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( single_value)
{

   common::ArgString2Array           as2a( "my_value", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end single_value



/// Test handling positional value following a short argument with a value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_value_value)
{

   common::ArgString2Array           as2a( "-f value my_value", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "value");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end short_value_value



/// Test handling positional value following a long argument with value set by
/// equal sign.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( long_eq_value_value)
{

   common::ArgString2Array           as2a( "--longarg=value my_value", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "longarg");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "value");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end long_eq_value_value



/// Test handling multiple positional values.
/// @since  1.1, 06.01.2016
BOOST_AUTO_TEST_CASE( multiple_pos_values)
{

   common::ArgString2Array           as2a( "my_value other_value", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "other_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end multiple_pos_values



/// Test handling multiple positional values that are numbers.
/// @since  1.1, 06.01.2016
BOOST_AUTO_TEST_CASE( multiple_pos_values_numbers)
{

   common::ArgString2Array           as2a( "42 4711 90125", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "42");

   ++it;
   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "4711");

   ++it;
   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "90125");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end multiple_pos_values_numbers



/// Test handling of a value that starts with a dash.
/// @since  6.0, 17.06.2014
BOOST_AUTO_TEST_CASE( short_dashed_value)
{

   common::ArgString2Array           as2a( "-f -- -minusfile", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "-minusfile");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end short_dashed_value



/// Test handling of a value that starts with a dash.
/// @since  6.0, 17.06.2014
BOOST_AUTO_TEST_CASE( long_dashed_value)
{

   common::ArgString2Array           as2a( "--filename -- -minusfile", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "-minusfile");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end long_dashed_value



/// Just to check: Test handling of a long argument that equals a value
/// starting with a dash.
/// @since  6.0, 17.06.2014
BOOST_AUTO_TEST_CASE( long_equal_dashed_value)
{

   common::ArgString2Array           as2a( "--filename=-minusfile", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "-minusfile");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end long_equal_dashed_value



/// Test if control characters are detected correctly.
/// @since  6.0, 02.07.2014
BOOST_AUTO_TEST_CASE( control)
{

   common::ArgString2Array           as2a( "--filter plus ( ! --filter minus )", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filter");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "plus");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etControl);
   BOOST_REQUIRE_EQUAL( it->mArgChar, '(');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etControl);
   BOOST_REQUIRE_EQUAL( it->mArgChar, '!');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filter");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "minus");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etControl);
   BOOST_REQUIRE_EQUAL( it->mArgChar, ')');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end control



/// Test if multiple iterators using the same ArgListParser somehow interfere
/// with each other.
/// @since  6.0, 18.06.2014
BOOST_AUTO_TEST_CASE( multiple_iterators)
{

   common::ArgString2Array           as2a( "-a --long1 -b value --long2=value -c -def value --extra value value", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   int                               numArgs = 0;


   for (auto it = alp.cbegin(); it != alp.cend(); ++it)
   {
      int  numArgs2 = numArgs;
      for (prog_args::detail::ArgListParser::const_iterator it2 = it; it2 != alp.cend(); ++it2)
      {
         ++numArgs2;
      } // end for
      BOOST_REQUIRE_EQUAL( numArgs2, 14);

      int  numArgs3 = 0;
      for (prog_args::detail::ArgListParser::const_iterator it3 = alp.cbegin(); it3 != alp.cend(); it3++)
      {
         ++numArgs3;
      } // end for
      BOOST_REQUIRE_EQUAL( numArgs3, 14);

      ++numArgs;
   } // end for

   BOOST_REQUIRE_EQUAL( numArgs, 14);

} // end multiple_iterators



/// Test evaluation '-l<value>'.
/// @since  6.0, 13.02.2015
BOOST_AUTO_TEST_CASE( value_after_arg)
{

   common::ArgString2Array           as2a( "-ffilename -f filename -f --nofile -affilename", nullptr);
   prog_args::detail::ArgListParser  alp( as2a.mArgc, as2a.mpArgv);
   auto                              it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   it.remArgStrAsVal();
   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   it.remArgStrAsVal();
   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   it.remArgStrAsVal();
   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etStringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "nofile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etSingleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   it.remArgStrAsVal();
   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, prog_args::detail::ArgListElement::etValue);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end value_after_arg



// =========================  END OF test_arg_list_parser.cpp  =========================
