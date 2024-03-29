
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "argument help" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHArgHelp
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args.hpp"
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::Handler;
using celma::test::multilineStringCompare;
using std::ostringstream;
using std::string;



/// Request help for a non-existing argument.
///
/// @since  1.14.0, 03.10.2018
BOOST_AUTO_TEST_CASE( unknown_argument)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   bool            bool_arg;


   ah.addArgument( "f", DEST_VAR( bool_arg), "A boolean flag");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg=-x"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( std_out.str().empty());
   BOOST_REQUIRE( !err_out.str().empty());

} // unknown_argument



/// Request help for a non-existing sub-group.
///
/// @since  1.23.0, 05.04.2019
BOOST_AUTO_TEST_CASE( unknown_subgroup)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   bool            bool_arg;


   ah.addArgument( "f", DEST_VAR( bool_arg), "A boolean flag");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg=-g/x"));
   // std::cerr << "\n" << err_out.str() << std::endl;
   BOOST_REQUIRE( std_out.str().empty());
   BOOST_REQUIRE( multilineStringCompare( err_out,
      "*** ERROR: Sub-group argument '-g/x' is unknown!\n"));

} // unknown_argument



/// Help for a boolean argument.
///
/// @since  1.14.0, 02.10.2016
BOOST_AUTO_TEST_CASE( flag_usage)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   bool            bool_arg;


   ah.addArgument( "f", DEST_VAR( bool_arg), "A boolean flag with a very long, "
      "but meaningless description, just used to check text formatting in this "
      "context.\n"
      "Not that it is already tested thoroughly through the usage formatting.");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg=-f"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '-f', usage:\n"
                        "   A boolean flag with a very long, but meaningless description, just used to\n"
                        "   check text formatting in this context.\n"
                        "   Not that it is already tested thoroughly through the usage formatting.\n"));
   // std::cerr << "\n" << err_out.str() << std::endl;
   BOOST_REQUIRE( err_out.str().empty());

} // flag_usage



/// Full help for a boolean argument.
///
/// @since  1.14.0, 01.10.2016
BOOST_AUTO_TEST_CASE( flag_full)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::hfHelpArgFull | Handler::hfUsageCont);
   bool            bool_arg;


   ah.addArgument( "f", DEST_VAR( bool_arg), "A boolean flag with a very long, "
      "but meaningless description, just used to check text formatting in this "
      "context.\n"
      "Not that it is already tested thoroughly through the usage formatting.");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg f"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '-f', usage:\n"
                        "   A boolean flag with a very long, but meaningless description, just used to\n"
                        "   check text formatting in this context.\n"
                        "   Not that it is already tested thoroughly through the usage formatting.\n"
                        "Properties:\n"
                        "   destination variable name:  bool_arg\n"
                        "   destination variable type:  bool\n"
                        "   is mandatory:               false\n"
                        "   value mode:                 'none' (0)\n"
                        "   cardinality:                at most 1\n"
                        "   checks:                     -\n"
                        "   check original value:       false\n"
                        "   formats:                    -\n"
                        "   constraints:                -\n"
                        "   is hidden:                  false\n"
                        "   takes multiple values:      false\n"
                        "   allows inverting:           false\n"
                        "   is deprecated:              false\n"
                        "   is replaced:                false\n"
                        "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // flag_full



/// Help for a mandatory string argument.
///
/// @since  1.14.0, 01.10.2016
BOOST_AUTO_TEST_CASE( mandatory_usage)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   string          string_arg;


   ah.addArgument( "s", DEST_VAR( string_arg), "Some funny string argument.")
      ->setIsMandatory();

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg=s"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '-s', usage:\n"
                        "   Some funny string argument.\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // mandatory_usage



/// Full help for a mandatory string argument.
///
/// @since  1.14.0, 01.10.2016
BOOST_AUTO_TEST_CASE( mandatory_full)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::hfHelpArgFull | Handler::hfUsageCont);
   string          string_arg;


   ah.addArgument( "s", DEST_VAR( string_arg), "Some funny string argument.")
      ->setIsMandatory();

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg=-s"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '-s', usage:\n"
                        "   Some funny string argument.\n"
                        "Properties:\n"
                        "   destination variable name:  string_arg\n"
                        "   destination variable type:  std::string\n"
                        "   is mandatory:               true\n"
                        "   value mode:                 'required' (2)\n"
                        "   cardinality:                at most 1\n"
                        "   checks:                     -\n"
                        "   check original value:       false\n"
                        "   formats:                    -\n"
                        "   constraints:                -\n"
                        "   is hidden:                  false\n"
                        "   takes multiple values:      false\n"
                        "   allows inverting:           false\n"
                        "   is deprecated:              false\n"
                        "   is replaced:                false\n"
                        "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // mandatory_full



/// Full help for a pair argument.
///
/// @since  1.14.0, 04.10.2018
BOOST_AUTO_TEST_CASE( pair_full)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::hfHelpArgFull | Handler::hfUsageCont);
   int             int_arg = -1;
   std::string     string_arg;


   ah.addArgument( "p,pair", DEST_PAIR( string_arg, int_arg, 42),
      "A pair of a string and an integer argument.");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg pair"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '--pair', usage:\n"
                        "   A pair of a string and an integer argument.\n"
                        "Properties:\n"
                        "   destination variable name:  string_arg\n"
                        "   destination variable type:  std::string\n"
                        "   is mandatory:               false\n"
                        "   value mode:                 'required' (2)\n"
                        "   cardinality:                at most 1\n"
                        "   checks:                     -\n"
                        "   check original value:       false\n"
                        "   formats:                    -\n"
                        "   constraints:                -\n"
                        "   is hidden:                  false\n"
                        "   takes multiple values:      false\n"
                        "   allows inverting:           false\n"
                        "   is deprecated:              false\n"
                        "   is replaced:                false\n"
                        "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // pair_full



/// Full help for a sub-group handler.
///
/// @since  1.14.0, 04.10.2018
BOOST_AUTO_TEST_CASE( subgroup_full)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         masterAH( std_out, err_out,
      Handler::hfHelpArgFull | Handler::hfUsageCont);
   string          paramL;

   Handler  subInput( masterAH, 0);
   string   inputName;
   int      inputType = 0;

   Handler  subOutput( masterAH, 0);
   string   outputName;
   int      outputType = 0;

   masterAH.addArgument( "l", DEST_VAR( paramL), "top-level argument l");

   subInput.addArgument( "f", DEST_PAIR( inputName, inputType, 2), "file name");
   subInput.addArgument( "q", DEST_PAIR( inputName, inputType, 3), "queue name");
   masterAH.addArgument( "i", subInput, "input arguments");

   subOutput.addArgument( "f", DEST_PAIR( outputName, outputType, 2), "file name");
   subOutput.addArgument( "q", DEST_PAIR( outputName, outputType, 3), "queue name");
   masterAH.addArgument( "o", subOutput, "output arguments");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( masterAH, "--help-arg o"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '-o', usage:\n"
                        "   output arguments\n"
                        "Properties:\n"
                        "   destination variable name:  sub-group\n"
                        "   destination variable type:  subgroup\n"
                        "   is mandatory:               false\n"
                        "   value mode:                 'none' (0)\n"
                        "   cardinality:                none\n"
                        "   checks:                     -\n"
                        "   check original value:       false\n"
                        "   formats:                    -\n"
                        "   constraints:                -\n"
                        "   is hidden:                  false\n"
                        "   takes multiple values:      false\n"
                        "   allows inverting:           false\n"
                        "   is deprecated:              false\n"
                        "   is replaced:                false\n"
                        "\n"));
   // std::cerr << "\n" << err_out.str() << std::endl;
   BOOST_REQUIRE( err_out.str().empty());

} // subgroup_full



/// Full help for an argument in a sub-group.
///
/// @since  1.14.0, 05.10.2018
BOOST_AUTO_TEST_CASE( subgroup_arg_full)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         masterAH( std_out, err_out,
      Handler::hfHelpArgFull | Handler::hfUsageCont);
   string          paramL;

   Handler  subInput( masterAH, 0);
   string   inputName;
   int      inputType = 0;

   Handler  subOutput( masterAH, 0);
   string   outputName;
   int      outputType = 0;

   masterAH.addArgument( "l", DEST_VAR( paramL), "top-level argument l");

   subInput.addArgument( "f", DEST_PAIR( inputName, inputType, 2), "file name");
   subInput.addArgument( "q", DEST_PAIR( inputName, inputType, 3), "queue name");
   masterAH.addArgument( "i", subInput, "input arguments");

   subOutput.addArgument( "f", DEST_PAIR( outputName, outputType, 2), "file name");
   subOutput.addArgument( "q", DEST_PAIR( outputName, outputType, 3), "queue name");
   masterAH.addArgument( "o", subOutput, "output arguments");

   BOOST_REQUIRE_NO_THROW( evalArgumentString( masterAH, "--help-arg i/f"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '-f', usage:\n"
                        "   file name\n"
                        "Properties:\n"
                        "   destination variable name:  inputName\n"
                        "   destination variable type:  std::string\n"
                        "   is mandatory:               false\n"
                        "   value mode:                 'required' (2)\n"
                        "   cardinality:                at most 1\n"
                        "   checks:                     -\n"
                        "   check original value:       false\n"
                        "   formats:                    -\n"
                        "   constraints:                -\n"
                        "   is hidden:                  false\n"
                        "   takes multiple values:      false\n"
                        "   allows inverting:           false\n"
                        "   is deprecated:              false\n"
                        "   is replaced:                false\n"
                        "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // subgroup_arg_full



/// Help for an optional vector of integers.
///
/// @since  1.14.0, 03.10.2018
BOOST_AUTO_TEST_CASE( vector_max_values_usage)
{

   ostringstream      std_out;
   ostringstream      err_out;
   Handler            ah( std_out, err_out, Handler::hfHelpArg | Handler::hfUsageCont);
   std::vector< int>  int_vec;


   ah.addArgument( "values", DEST_VAR( int_vec), "3 values in the range 1..10.")
      ->setCardinality( celma::prog_args::cardinality_exact( 3))
      ->setTakesMultiValue()
      ->addConstraint( celma::prog_args::excludes( "names"))
      ->addCheck( celma::prog_args::range( 1, 100));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg=--values"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '--values', usage:\n"
                        "   3 values in the range 1..10.\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // vector_max_values_usage



/// Full help for an optional vector of integers.
///
/// @since  1.14.0, 02.10.2018
BOOST_AUTO_TEST_CASE( vector_max_values_full)
{

   ostringstream      std_out;
   ostringstream      err_out;
   Handler            ah( std_out, err_out, Handler::hfHelpArgFull | Handler::hfUsageCont);
   std::vector< int>  int_vec;


   ah.addArgument( "values", DEST_VAR( int_vec), "3 values in the range 1..10.")
      ->setCardinality( celma::prog_args::cardinality_exact( 3))
      ->setTakesMultiValue()
      ->addConstraint( celma::prog_args::excludes( "names"))
      ->addCheck( celma::prog_args::range( 1, 100));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "--help-arg values"));
   // std::cerr << "\n" << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Argument '--values', usage:\n"
                        "   3 values in the range 1..10.\n"
                        "Properties:\n"
                        "   destination variable name:  int_vec\n"
                        "   destination variable type:  std::vector<int>\n"
                        "   is mandatory:               false\n"
                        "   value mode:                 'required' (2)\n"
                        "   cardinality:                exactly 3\n"
                        "   checks:                     1 <= value < 100\n"
                        "   check original value:       false\n"
                        "   formats:                    -\n"
                        "   constraints:                excludes (names)\n"
                        "   is hidden:                  false\n"
                        "   takes multiple values:      true\n"
                        "   allows inverting:           false\n"
                        "   is deprecated:              false\n"
                        "   is replaced:                false\n"
                        "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // vector_max_values_full



// =====  END OF test_argh_arg_help_c.cpp  =====

