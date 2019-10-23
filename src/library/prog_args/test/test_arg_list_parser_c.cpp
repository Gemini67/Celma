
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
**    Test program for the module ArgListParser using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args/detail/arg_list_parser.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgListParserTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::detail::ArgListElement;
using celma::prog_args::detail::ArgListParser;


BOOST_TEST_DONT_PRINT_LOG_VALUE( ArgListElement::ElementType)



/// Single dash as only argument leads to an error.
///
/// @since  1.14.0, 05.10.2018
BOOST_AUTO_TEST_CASE( error_single_dash_only)
{

   auto const     as2a = make_arg_array( "-", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);


   BOOST_REQUIRE_THROW( alp.cbegin(), std::runtime_error);

} // error_single_dash_only



/// Test handling of one single character as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( single_char)
{

   auto const     as2a = make_arg_array( "-v", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // single_char



/// Test handling of two single characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_single_char)
{

   auto const     as2a = make_arg_array( "-lv", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-l -v", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   ++it;
   BOOST_REQUIRE( it != alp.cend());

   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'v');

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // two_single_char_sep



/// A single dash in the argument list leads to an error.
///
/// @since  1.14.0, 05.10.2018
BOOST_AUTO_TEST_CASE( error_single_dash)
{

   auto const     as2a = make_arg_array( "-l - -v", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::singleCharArg);
   BOOST_REQUIRE_EQUAL( it->mArgChar, 'l');

   BOOST_REQUIRE_THROW( ++it, std::runtime_error);

} // error_single_dash



/// Test handling of three single characters as argument.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( three_single_char)
{

   auto const     as2a = make_arg_array( "-lva", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-l -v -a", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-lv -a", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-l -va", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "--verbose", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::stringArg);
   BOOST_REQUIRE_EQUAL( it->mArgString, "verbose");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // single_long



/// Test handling of two long arguments.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( two_long)
{

   auto const     as2a = make_arg_array( "--verbose --careful", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-v --verbose -s0l --careful -x", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-f filename", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "--inputfile filename", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "--verboselevel 8 --inputfile=filename", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "--verboselevel 8 --inputfile=filename --another=attempt", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-i input --outputfile filename --filter=everything -q always", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "my_value", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


   BOOST_REQUIRE_EQUAL( it->mElementType, ArgListElement::ElementType::value);
   BOOST_REQUIRE_EQUAL( it->mValue, "my_value");

   ++it;
   BOOST_REQUIRE( it == alp.cend());

} // single_value



/// Test handling positional value following a short argument with a value.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( short_value_value)
{

   auto const     as2a = make_arg_array( "-f value my_value", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "--longarg=value my_value", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "my_value other_value", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "42 4711 90125", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-f -- -minusfile", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "--filename -- -minusfile", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "--filename=-minusfile", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "--filter plus ( ! --filter minus )", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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

   auto const     as2a = make_arg_array( "-a --long1 -b value --long2=value -c -def value --extra value value", nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   int            numArgs = 0;


   for (auto it = alp.cbegin(); it != alp.cend(); ++it)
   {
      int  numArgs2 = numArgs;
      for (ArgListParser::const_iterator it2 = it; it2 != alp.cend(); ++it2)
      {
         ++numArgs2;
      } // end for
      BOOST_REQUIRE_EQUAL( numArgs2, 14);

      int  numArgs3 = 0;
      // cppcheck-suppress postfixOperator
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

   auto const     as2a = make_arg_array( "-ffilename -f filename -f --nofile -affilename",
      nullptr);
   ArgListParser  alp( as2a.mArgC, as2a.mpArgV);
   auto           it = alp.cbegin();


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



// =====  END OF test_arg_list_parser_c.cpp  =====

