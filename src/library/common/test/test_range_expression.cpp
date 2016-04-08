
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
**    Test program for the functions of the module RangeExpression.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE RangeExpressionTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/range_expression.hpp"


using namespace std;
using namespace celma;



/// Range string starting with a single value.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_single_values)
{

   common::RangeExpression  re;


   re.parseString( "2");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "2"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        2);
   BOOST_REQUIRE( !re.hasRangeEnd());
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "25");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "25"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        25);
   BOOST_REQUIRE( !re.hasRangeEnd());
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "256");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "256"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        256);
   BOOST_REQUIRE( !re.hasRangeEnd());
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "256,259");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "256"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        256);
   BOOST_REQUIRE( !re.hasRangeEnd());
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( !re.hasExcludeExpr());

} // end test_single_values



/// Simple range (no increment, no exclude).
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_simple_range)
{

   common::RangeExpression  re;


   re.parseString( "2-5");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "2-5"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        2);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          5);
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "256-300");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "256-300"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        256);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          300);
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "1-99,672-28233");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "1-99"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        1);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          99);
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "11-21,102");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "11-21"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        11);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          21);
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( !re.hasExcludeExpr());

} // end test_simple_range



/// Range with increment.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_increment)
{

   common::RangeExpression  re;


   re.parseString( "1-99[2]");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "1-99[2]"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        1);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          99);
   BOOST_REQUIRE( re.hasIncrement());
   BOOST_REQUIRE_EQUAL( re.incrementValue(),    2);
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "15-255[11]");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "15-255[11]"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        15);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          255);
   BOOST_REQUIRE( re.hasIncrement());
   BOOST_REQUIRE_EQUAL( re.incrementValue(),    11);
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "1-99[2],67");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "1-99[2]"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        1);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          99);
   BOOST_REQUIRE( re.hasIncrement());
   BOOST_REQUIRE_EQUAL( re.incrementValue(),    2);
   BOOST_REQUIRE( !re.hasExcludeExpr());

   re.parseString( "1-99[2],101-201[3]");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "1-99[2]"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        1);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          99);
   BOOST_REQUIRE( re.hasIncrement());
   BOOST_REQUIRE_EQUAL( re.incrementValue(),    2);
   BOOST_REQUIRE( !re.hasExcludeExpr());

} // end test_range_increment



/// Range with exlude (but no increment).
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_exclude)
{

   common::RangeExpression  re;


   re.parseString( "256-300{280}");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "256-300{280}"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        256);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          300);
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( re.hasExcludeExpr());
   BOOST_REQUIRE_EQUAL( re.excludeExpression(), string( "280"));

   re.parseString( "1-999{400-600[2]}");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "1-999{400-600[2]}"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        1);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          999);
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( re.hasExcludeExpr());
   BOOST_REQUIRE_EQUAL( re.excludeExpression(), string( "400-600[2]"));

   re.parseString( "1-999{400-600[2]},15");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "1-999{400-600[2]}"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        1);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          999);
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( re.hasExcludeExpr());
   BOOST_REQUIRE_EQUAL( re.excludeExpression(), string( "400-600[2]"));

   re.parseString( "1-999{400-600[2]},55-66");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "1-999{400-600[2]}"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        1);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          999);
   BOOST_REQUIRE( !re.hasIncrement());
   BOOST_REQUIRE( re.hasExcludeExpr());
   BOOST_REQUIRE_EQUAL( re.excludeExpression(), string( "400-600[2]"));

} // end test_range_exclude



/// Range with increment and exclude.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( test_range_increment_exclude)
{

   common::RangeExpression  re;


   re.parseString( "256-300[3]{280}");
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "256-300[3]{280}"));
   BOOST_REQUIRE_EQUAL( re.startValue(),        256);
   BOOST_REQUIRE( re.hasRangeEnd());
   BOOST_REQUIRE_EQUAL( re.endValue(),          300);
   BOOST_REQUIRE( re.hasIncrement());
   BOOST_REQUIRE_EQUAL( re.incrementValue(),    3);
   BOOST_REQUIRE( re.hasExcludeExpr());
   BOOST_REQUIRE_EQUAL( re.excludeExpression(), string( "280"));

} // end test_range_increment_exclude



/// List of ranges.
/// @since  0.2, 07.04.2016
BOOST_AUTO_TEST_CASE( multiple_ranges)
{

   common::RangeExpression  re;
   string                   input( "22-30[2],33-39[2]{37},45");


   re.parseString( input);
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "22-30[2]"));

   string  new_input( input, re.matchedExpression().length() + 1);
   re.parseString( new_input);
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "33-39[2]{37}"));

   string  last_input( new_input, re.matchedExpression().length() + 1);
   re.parseString( last_input);
   BOOST_REQUIRE_EQUAL( re.matchedExpression(), string( "45"));

} // end multiple_ranges



// =========================  END OF test_project_path.cpp  =========================

