
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module ArgListParser using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args/detail/arg_list_parser.hpp"


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
#include "celma/common/arg_string_2_array.hpp"


using celma::common::ArgString2Array;
using celma::prog_args::detail::ArgListElement;
using celma::prog_args::detail::ArgListParser;


BOOST_TEST_DONT_PRINT_LOG_VALUE( ArgListElement::ElementType);


// module definitions
typedef std::vector< std::string>  StringVec;



/// Test handling of one single character as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( single_char)
{

   const ArgString2Array  as2a( "-v", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // single_char



/// Test handling of two single characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_single_char)
{

   const ArgString2Array  as2a( "-lv", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // two_single_char



/// Test handling of two single, separate characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_single_char_sep)
{

   const ArgString2Array  as2a( "-l -v", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // two_single_char_sep



/// Test handling of three single characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char)
{

   const ArgString2Array  as2a( "-lva", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // three_single_char



/// Test handling of three single, separate characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char_sep)
{

   const ArgString2Array  as2a( "-l -v -a", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // three_single_char_sep



/// Test handling of three single characters (one/pair) as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char_mixed1)
{

   const ArgString2Array  as2a( "-lv -a", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // three_single_char_mixed1



/// Test handling of three single characters (one/pair) as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char_mixed2)
{

   const ArgString2Array  as2a( "-l -va", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // end three_single_char_mixed2



/// Test handling of one long argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( single_long)
{

   const ArgString2Array  as2a( "--verbose", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verbose");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // single_long



/// Test handling of two long arguments.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_long)
{

   const ArgString2Array  as2a( "--verbose --careful", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verbose");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "careful");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // two_long



/// Test handling of mixed short and long arguments.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_long)
{

   const ArgString2Array  as2a( "-v --verbose -s0l --careful -x", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verbose");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 's');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, '0');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "careful");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'x');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // two_long



/// Test handling of one single character argument with a value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_value)
{

   const ArgString2Array  as2a( "-f filename", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // short_value



/// Test handling of one long argument with a value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( long_value)
{

   const ArgString2Array  as2a( "--inputfile filename", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "inputfile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // long_value



/// Test handling of two long arguments with values.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_long_value)
{

   const ArgString2Array  as2a( "--verboselevel 8 --inputfile=filename", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verboselevel");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "8");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "inputfile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // two_long_value



/// Test handling of two long arguments with values.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_long_value)
{

   const ArgString2Array  as2a( "--verboselevel 8 --inputfile=filename --another=attempt", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verboselevel");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "8");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "inputfile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "another");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "attempt");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // three_long_value



/// Test handling of four arguments (short, long, long, short) with values.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_long_long_short)
{

   const ArgString2Array  as2a( "-i input --outputfile filename --filter=everything -q always", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'i');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "input");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "outputfile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filter");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "everything");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'q');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "always");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // short_long_long_short



/// Test handling a single, positional value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( single_value)
{

   const ArgString2Array  as2a( "my_value", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // single_value



/// Test handling positional value following a short argument with a value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_value_value)
{

   const ArgString2Array  as2a( "-f value my_value", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "value");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // short_value_value



/// Test handling positional value following a long argument with value set by
/// equal sign.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( long_eq_value_value)
{

   const ArgString2Array  as2a( "--longarg=value my_value", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "longarg");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "value");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // long_eq_value_value



/// Test handling multiple positional values.
/// @since  1.1, 06.01.2016
BOOST_AUTO_TEST_CASE( multiple_pos_values)
{

   const ArgString2Array  as2a( "my_value other_value", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "other_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // multiple_pos_values



/// Test handling multiple positional values that are numbers.
/// @since  1.1, 06.01.2016
BOOST_AUTO_TEST_CASE( multiple_pos_values_numbers)
{

   const ArgString2Array  as2a( "42 4711 90125", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "42");

   ++it;
   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "4711");

   ++it;
   BOOST_REQUIRE( it != alp.cend());
   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "90125");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // multiple_pos_values_numbers



/// Test handling of a value that starts with a dash.
/// @since  6.0, 17.06.2014
BOOST_AUTO_TEST_CASE( short_dashed_value)
{

   const ArgString2Array  as2a( "-f -- -minusfile", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "-minusfile");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // short_dashed_value



/// Test handling of a value that starts with a dash.
/// @since  6.0, 17.06.2014
BOOST_AUTO_TEST_CASE( long_dashed_value)
{

   const ArgString2Array  as2a( "--filename -- -minusfile", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "-minusfile");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // long_dashed_value



/// Just to check: Test handling of a long argument that equals a value
/// starting with a dash.
/// @since  6.0, 17.06.2014
BOOST_AUTO_TEST_CASE( long_equal_dashed_value)
{

   const ArgString2Array  as2a( "--filename=-minusfile", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "-minusfile");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // long_equal_dashed_value



/// Test if control characters are detected correctly.
/// @since  6.0, 02.07.2014
BOOST_AUTO_TEST_CASE( control)
{

   const ArgString2Array  as2a( "--filter plus ( ! --filter minus )", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filter");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "plus");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::control);
   BOOST_REQUIRE_EQUAL( it->mArgChar, '(');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::control);
   BOOST_REQUIRE_EQUAL( it->mArgChar, '!');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "filter");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "minus");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::control);
   BOOST_REQUIRE_EQUAL( it->mArgChar, ')');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // control



/// Test if multiple iterators using the same ArgListParser somehow interfere
/// with each other.
/// @since  6.0, 18.06.2014
BOOST_AUTO_TEST_CASE( multiple_iterators)
{

   const ArgString2Array  as2a( "-a --long1 -b value --long2=value -c -def value --extra value value", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   int                    numArgs = 0;


   for (auto it = alp.cbegin(); it != alp.cend(); ++it)
   {
      int  numArgs2 = numArgs;
      for (ArgListParser::const_iterator it2 = it; it2 != alp.cend(); ++it2)
      {
         ++numArgs2;
      } // end for
      BOOST_REQUIRE_EQUAL( numArgs2, 14);

      int  numArgs3 = 0;
      for (ArgListParser::const_iterator it3 = alp.cbegin(); it3 != alp.cend(); it3++)
      {
         ++numArgs3;
      } // end for
      BOOST_REQUIRE_EQUAL( numArgs3, 14);

      ++numArgs;
   } // end for

   BOOST_REQUIRE_EQUAL( numArgs, 14);

} // multiple_iterators



/// Test evaluation '-l<value>'.
/// @since  6.0, 13.02.2015
BOOST_AUTO_TEST_CASE( value_after_arg)
{

   const ArgString2Array  as2a( "-ffilename -f filename -f --nofile -affilename", nullptr);
   ArgListParser          alp( as2a.mArgc, as2a.mpArgv);
   auto                   it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   it.remArgStrAsVal();
   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   it.remArgStrAsVal();
   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   it.remArgStrAsVal();
   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "nofile");

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'a');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'f');

   it.remArgStrAsVal();
   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "filename");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // value_after_arg



// =====================  END OF test_arg_list_parser.cpp  =====================
