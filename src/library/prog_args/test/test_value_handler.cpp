
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/



// module to test, header file include
#include "celma/prog_args/value_handler.hpp"


// STL includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ValueHandlerTest
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args/groups.hpp"


using celma::prog_args::ValueHandler;
using celma::prog_args::Groups;
using celma::appl::ArgString2Array;
using celma::common::RangeDest;



/// Test value handling with simple types like int's, strings etc.
/// @since  0.14.0, 09.02.2017
BOOST_AUTO_TEST_CASE( test_simple_args)
{

   // test with a boolean value, not set as parameter
   {
      ValueHandler  ah( 0);

      ah.addValueArgument< bool>( "b", "Boolean.");

      ArgString2Array  as2a( "", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      celma::prog_args::detail::TypedArgBase*  arg_handler = nullptr;

      BOOST_REQUIRE_NO_THROW( arg_handler = ah.getArgHandler( "b"));
      BOOST_REQUIRE( arg_handler != nullptr);
      BOOST_REQUIRE( !arg_handler->hasValue());

      bool  result_value = false;
      BOOST_REQUIRE_NO_THROW( ah.getValue< bool>( result_value, "b"));
      BOOST_REQUIRE_EQUAL( result_value, false);
   } // end scope

   // test with a boolean value, used
   {
      ValueHandler  ah( 0);

      ah.addValueArgument< bool>( "b", "Boolean.");

      ArgString2Array  as2a( "-b", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      celma::prog_args::detail::TypedArgBase*  arg_handler = nullptr;

      BOOST_REQUIRE_NO_THROW( arg_handler = ah.getArgHandler( "b"));
      BOOST_REQUIRE( arg_handler != nullptr);
      BOOST_REQUIRE( arg_handler->hasValue());

      bool  result_value = false;
      BOOST_REQUIRE_NO_THROW( ah.getValue< bool>( result_value, "b"));
      BOOST_REQUIRE_EQUAL( result_value, true);

      std::string  wrong_result_value_type;
      BOOST_REQUIRE_THROW( ah.getValue< std::string>( wrong_result_value_type, "b"),
                           std::invalid_argument);
   } // end scope

   // test with an integer value
   {
      ValueHandler  ah( 0);

      ah.addValueArgument< int>( "n", "Number.");

      ArgString2Array  as2a( "-n 5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      celma::prog_args::detail::TypedArgBase*  arg_handler = nullptr;

      BOOST_REQUIRE_NO_THROW( arg_handler = ah.getArgHandler( "n"));
      BOOST_REQUIRE( arg_handler != nullptr);
      BOOST_REQUIRE( arg_handler->hasValue());

      int  result_value = -1;
      BOOST_REQUIRE_NO_THROW( ah.getValue< int>( result_value, "n"));
      BOOST_REQUIRE_EQUAL( result_value, 5);

      std::string  wrong_result_value_type;
      BOOST_REQUIRE_THROW( ah.getValue< std::string>( wrong_result_value_type, "n"),
                           std::invalid_argument);
   } // end scope

   // test with a string value
   {
      ValueHandler  ah( 0);

      ah.addValueArgument< std::string>( "n", "Name.");

      ArgString2Array  as2a( "-n Bianca", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      celma::prog_args::detail::TypedArgBase*  arg_handler = nullptr;

      BOOST_REQUIRE_NO_THROW( arg_handler = ah.getArgHandler( "n"));
      BOOST_REQUIRE( arg_handler != nullptr);
      BOOST_REQUIRE( arg_handler->hasValue());

      std::string  result_value;
      BOOST_REQUIRE_NO_THROW( ah.getValue< std::string>( result_value, "n"));
      BOOST_REQUIRE_EQUAL( result_value, "Bianca");

      int  wrong_result_value_type;
      BOOST_REQUIRE_THROW( ah.getValue< int>( wrong_result_value_type, "n"),
                           std::invalid_argument);
   } // end scope

} // test_simple_args



/// Test with 'complex' types like vector etc. as destination variables.
/// @since  0.14.0, 21.02.2017
BOOST_AUTO_TEST_CASE( test_complex_types)
{

   // test type vector
   {
      ValueHandler  ah( 0);

      ah.addValueArgument< std::vector< int>>( "v", "Values.");

      ArgString2Array  as2a( "-v 1,2,3,4,5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      std::vector< int>  result_value;
      BOOST_REQUIRE_NO_THROW( ah.getValue< std::vector< int>>( result_value, "v"));
      BOOST_REQUIRE_EQUAL( result_value.size(), 5);
   } // end scope

   // test type RangeDest
   {
      ValueHandler  ah( 0);

      ah.addRangeValueArgument< int, std::vector< int>>( "r", "Range.");

      ArgString2Array  as2a( "-r 1-5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      std::vector< int>  result_value;
      BOOST_REQUIRE_NO_THROW( ah.getValue< std::vector< int>>( result_value, "r"));
      BOOST_REQUIRE_EQUAL( result_value.size(), 5);
   } // end scope

   // test type tuple
   {
      using tuple_t = std::tuple< int, std::string>;

      ValueHandler  ah( 0);

      ah.addValueArgument< tuple_t>( "t", "Tuple values.");

      ArgString2Array  as2a( "-t 42,hello", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      tuple_t  result_value;
      BOOST_REQUIRE_NO_THROW( ah.getValue< tuple_t>( result_value, "t"));
      BOOST_REQUIRE_EQUAL( std::get< 0>( result_value), 42);
      BOOST_REQUIRE_EQUAL( std::get< 1>( result_value), std::string( "hello"));
   } // end scope

} // test_complex_types



/// Test storing a free value in a destination value.
/// @since  0.14.0, 09.02.2017
BOOST_AUTO_TEST_CASE( test_free_value_arg)
{

   {
      ValueHandler  ah( 0);

      ah.addValueArgument< int>( "Free number.");

      ArgString2Array  as2a( "5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      int  result_value = -1;
      BOOST_REQUIRE_NO_THROW( ah.getValue< int>( result_value));
      BOOST_REQUIRE_EQUAL( result_value, 5);

      std::string  wrong_result_value_type;
      BOOST_REQUIRE_THROW( ah.getValue< std::string>( wrong_result_value_type),
                           std::invalid_argument);
   } // end scope

} // test_free_value_arg



/// Test using handler values objects with groups.
/// @since  0.14.0, 15.03.2017
BOOST_AUTO_TEST_CASE( test_values_groups)
{

   // a plain handler cannot be used as value handler
   {
      auto  plain_handler = Groups::instance().getArgHandler( "standard handler");

      BOOST_REQUIRE( plain_handler.get() != nullptr);
      BOOST_REQUIRE( !plain_handler->isValueHandler());
      BOOST_REQUIRE_THROW( Groups::instance().getArgValueHandler( "standard handler"),
                           std::runtime_error);
      Groups::instance().removeAllArgHandler();
   } // end scope

   // a value handler should not be used as plain handler
   {
      auto  handler_value = Groups::instance().getArgValueHandler( "standard handler");

      BOOST_REQUIRE( handler_value.get() != nullptr);
      BOOST_REQUIRE( handler_value->isValueHandler());
      BOOST_REQUIRE_NO_THROW( handler_value->getValueHandlerObj());
      BOOST_REQUIRE_THROW( Groups::instance().getArgHandler( "standard handler"),
                           std::runtime_error);
      Groups::instance().removeAllArgHandler();
   } // end scope

} // test_values_groups



// =====  END OF test_handler_values.cpp  =====

