
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
**    Test program for the feature "output streams parameters" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHOutputStreams
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using celma::common::ArgString2Array;
using celma::prog_args::Handler;



/// Simple case: Empty usage except for help arguments.
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( help_usage)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);


   ArgString2Array  as2a( "-h", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( std_out.str(), "Usage:\nOptional arguments:\n   -h,--help   Prints the program usage\n\n");
   BOOST_REQUIRE( err_out.str().empty());

} // end help_usage



/// Two arguments, one optional, one mandatory.
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( argument_output)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   std::string          string_arg;
   int                  opt_int_arg = 42;


   ah.addArgument( "s",       DEST_VAR( string_arg),  "String argument")->setIsMandatory();
   ah.addArgument( "i,index", DEST_VAR( opt_int_arg), "Integer argument");

   ArgString2Array  as2a( "-h", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( std_out.str(),
                        "Usage:\nMandatory arguments:\n"
                        "   -s           String argument\n"
                        "\n"
                        "Optional arguments:\n"
                        "   -h,--help    Prints the program usage\n"
                        "   -i,--index   Integer argument\n"
                        "                Default value: 42\n"
                        "\n");
   BOOST_REQUIRE( err_out.str().empty());

} // end argument_output



/// Two arguments, values assigned.
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( argument_verbose_assignment)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out,
                            Handler::AllHelp | Handler::hfUsageCont |
                            Handler::hfListArgVar | Handler::hfVerboseArgs);
   std::string          string_arg;
   int                  opt_int_arg = 42;


   ah.addArgument( "s",       DEST_VAR( string_arg),  "String argument")->setIsMandatory();
   ah.addArgument( "i,index", DEST_VAR( opt_int_arg), "Integer argument");

   ArgString2Array  as2a( "-s text --list-arg-vars --index 4711", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( std_out.str(),
                        "string_arg: value 'text' is assigned\n"
                        "Handler::listArgVars: is set\n"
                        "Short (character) arguments:\n"
                        "'-h' calls function/method 'Handler::usage'.\n"
                        "   value 'no value' (0), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
                        "'-i' value type 'int', destination 'opt_int_arg', value not set.\n"
                        "   value 'required' (2), optional, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
                        "'-s' value type 'std::string', destination 'string_arg', value = text.\n"
                        "   value 'required' (2), mandatory, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
                        "\n"
                        "Long (string) arguments:\n"
                        "'--help' calls function/method 'Handler::usage'.\n"
                        "   value 'no value' (0), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
                        "'--index' value type 'int', destination 'opt_int_arg', value not set.\n"
                        "   value 'required' (2), optional, does not take multiple&separate values, print dflt, visible, no checks, no formats\n"
                        "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
                        "   value 'no value' (0), optional, does not take multiple&separate values, don't print dflt, visible, no checks, no formats\n"
                        "\n"
                        "opt_int_arg: value '4711' is assigned\n");
   BOOST_REQUIRE( err_out.str().empty());

} // end argument_verbose_assignment



// ===================  END OF test_argh_output_streams.cpp  ===================
