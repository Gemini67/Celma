
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/



// module to test, header file include
#include "celma/prog_args/handler_values.hpp"


// STL includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE HandlerValuesTest
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


// project includes
#include "celma/common/arg_string_2_array.hpp"


using celma::prog_args::HandlerValues;
using celma::common::ArgString2Array;


/// 
/// @since  x.y.z, 09.02.2017
BOOST_AUTO_TEST_CASE( test_simple_args)
{

   {
      HandlerValues  ah( 0);

      ah.addValueArgument< int>( "n", "Number.");

      ArgString2Array  as2a( "-n 5", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      int  result_value = -1;
      BOOST_REQUIRE_NO_THROW( ah.getValue< int>( result_value, "n"));
      BOOST_REQUIRE_EQUAL( result_value, 5);

      std::string  wrong_result_value_type;
      BOOST_REQUIRE_THROW( ah.getValue< std::string>( wrong_result_value_type, "n"),
                           std::invalid_argument);
   } // end scope

   {
      HandlerValues  ah( 0);

      ah.addValueArgument< std::string>( "n", "Name.");

      ArgString2Array  as2a( "-n Bianca", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));

      std::string  result_value;
      BOOST_REQUIRE_NO_THROW( ah.getValue< std::string>( result_value, "n"));
      BOOST_REQUIRE_EQUAL( result_value, "Bianca");

      int  wrong_result_value_type;
      BOOST_REQUIRE_THROW( ah.getValue< int>( wrong_result_value_type, "n"),
                           std::invalid_argument);
   } // end scope

} // test_simple_args



/// 
/// @since  x.y.z, 09.02.2017
BOOST_AUTO_TEST_CASE( test_free_value_arg)
{

   {
      HandlerValues  ah( 0);

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



// =====================  END OF test_handler_values.cpp  =====================

