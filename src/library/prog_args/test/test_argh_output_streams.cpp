
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
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;
using std::string;



/// Simple case: Empty usage except for help arguments.
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( help_usage)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);


   ArgString2Array  as2a( "-h", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( std_out.str(), "Usage:\nOptional arguments:\n   -h,--help   Prints the program usage.\n\n");
   BOOST_REQUIRE( err_out.str().empty());

} // help_usage



/// Empty usage except for custom help arguments.
/// @since  0.10, 22.12.2016
BOOST_AUTO_TEST_CASE( custom_help_usage)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::hfUsageCont);


   ah.addHelpArgument( "u,usage", "Custom arguments for help");

   ArgString2Array  as2a( "-u", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( std_out.str(), "Usage:\nOptional arguments:\n   -u,--usage   Custom arguments for help\n\n");
   BOOST_REQUIRE( err_out.str().empty());

} // custom_help_usage



/// Two arguments, one optional, one mandatory.
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( argument_output)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   string               string_arg;
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
                        "   -h,--help    Prints the program usage.\n"
                        "   -i,--index   Integer argument\n"
                        "                Default value: 42\n"
                        "\n");
   BOOST_REQUIRE( err_out.str().empty());

} // argument_output



/// Special arguments: one optional, one mandatory, one hidden, one deprecated
/// and one "replaced by".
/// @since
///    1.6.0, 30.04.2018
BOOST_AUTO_TEST_CASE( usage_with_special_arguments)
{

   /// Helper class used to provide a fresh set of the Handler object and the
   /// test variables.
   /// @since
   ///    1.6.0, 30.04.2018
   class TestData
   {
   public:
      /// Constructor, initialises the Handler.
      /// @param[in]  argstring
      ///    The argument string to pass to \c ArgString2Array.
      /// @since
      ///    1.6.0, 30.04.2018
      TestData( int flag_set, const string& argstring):
         mStdOut(),
         mErrOut(),
         mHandler( mStdOut, mErrOut, Handler::AllHelp | Handler::hfUsageCont | flag_set),
         mStringArg(),
         mReplacedBy(),
         mAs2a( argstring, nullptr)
      {
         mHandler.addArgument( "s", DEST_VAR( mStringArg), "String argument")
            ->setIsMandatory();
         mHandler.addArgument( "i,index", DEST_VAR( mOptIntArg),
            "Integer argument");
         mHandler.addArgument( "hidden", DEST_VAR( mHidden),
            "Hidden boolean argument")->setIsHidden();
         mHandler.addArgument( "deprecated", DEST_VAR( mDummy),
            "Deprecated argument, don't use anymore")->setIsDeprecated();
         mHandler.addArgument( "n,name", DEST_VAR( mReplacedBy),
            "Argument replaced by '-i', don't use anymore")
            ->setPrintDefault( false)->setReplacedBy( "-i");
      } // end TestData::TestData

      /// Captures the output to \c stdout.
      std::ostringstream   mStdOut;
      /// Captures the output to \c stderr.
      std::ostringstream   mErrOut;
      /// The argument handler object used for the test.
      Handler              mHandler;
      /// Mandatory string argument.
      string               mStringArg;
      /// Optional integer argument.
      int                  mOptIntArg = 42;
      /// Deprecated argument variable.
      bool                 mDummy = false;
      /// Argument "replaced by".
      string               mReplacedBy;
      /// Hidden variable.
      bool                 mHidden = false;
      /// Argument string split to argc, argv.
      ArgString2Array      mAs2a;
   }; // TestData

   {
      TestData  td( 0, "-h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgc,
         td.mAs2a.mpArgv));
      BOOST_REQUIRE_EQUAL( td.mStdOut.str(),
                           "Usage:\nMandatory arguments:\n"
                           "   -s           String argument\n"
                           "\n"
                           "Optional arguments:\n"
                           "   -h,--help    Prints the program usage.\n"
                           "   -i,--index   Integer argument\n"
                           "                Default value: 42\n"
                           "\n");
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfUsageHidden, "-h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgc,
         td.mAs2a.mpArgv));
      BOOST_REQUIRE_EQUAL( td.mStdOut.str(),
                           "Usage:\nMandatory arguments:\n"
                           "   -s           String argument\n"
                           "\n"
                           "Optional arguments:\n"
                           "   -h,--help    Prints the program usage.\n"
                           "   -i,--index   Integer argument\n"
                           "                Default value: 42\n"
                           "   --hidden     Hidden boolean argument\n"
                           "                [hidden]\n"
                           "\n");
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfUsageDeprecated, "-h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgc,
         td.mAs2a.mpArgv));
      BOOST_REQUIRE_EQUAL( td.mStdOut.str(),
                           "Usage:\nMandatory arguments:\n"
                           "   -s             String argument\n"
                           "\n"
                           "Optional arguments:\n"
                           "   -h,--help      Prints the program usage.\n"
                           "   -i,--index     Integer argument\n"
                           "                  Default value: 42\n"
                           "   --deprecated   Deprecated argument, don't use anymore\n"
                           "                  [deprecated]\n"
                           "   -n,--name      Argument replaced by '-i', don't use anymore\n"
                           "                  [replaced by '-i']\n"
                           "\n");
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfUsageHidden | Handler::hfUsageDeprecated, "-h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgc,
         td.mAs2a.mpArgv));
      BOOST_REQUIRE_EQUAL( td.mStdOut.str(),
                           "Usage:\nMandatory arguments:\n"
                           "   -s             String argument\n"
                           "\n"
                           "Optional arguments:\n"
                           "   -h,--help      Prints the program usage.\n"
                           "   -i,--index     Integer argument\n"
                           "                  Default value: 42\n"
                           "   --hidden       Hidden boolean argument\n"
                           "                  [hidden]\n"
                           "   --deprecated   Deprecated argument, don't use anymore\n"
                           "                  [deprecated]\n"
                           "   -n,--name      Argument replaced by '-i', don't use anymore\n"
                           "                  [replaced by '-i']\n"
                           "\n");
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfArgHidden, "--print-hidden -h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgc,
         td.mAs2a.mpArgv));
      BOOST_REQUIRE_EQUAL( td.mStdOut.str(),
                           "Usage:\nMandatory arguments:\n"
                           "   -s               String argument\n"
                           "\n"
                           "Optional arguments:\n"
                           "   -h,--help        Prints the program usage.\n"
                           "   --print-hidden   Also print hidden arguments in the usage.\n"
                           "   -i,--index       Integer argument\n"
                           "                    Default value: 42\n"
                           "   --hidden         Hidden boolean argument\n"
                           "                    [hidden]\n"
                           "\n");
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfArgDeprecated, "--print-deprecated -h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgc,
         td.mAs2a.mpArgv));
      BOOST_REQUIRE_EQUAL( td.mStdOut.str(),
                           "Usage:\nMandatory arguments:\n"
                           "   -s                   String argument\n"
                           "\n"
                           "Optional arguments:\n"
                           "   -h,--help            Prints the program usage.\n"
                           "   --print-deprecated   Also print deprecated and replaced arguments in the\n"
                           "                        usage.\n"
                           "   -i,--index           Integer argument\n"
                           "                        Default value: 42\n"
                           "   --deprecated         Deprecated argument, don't use anymore\n"
                           "                        [deprecated]\n"
                           "   -n,--name            Argument replaced by '-i', don't use anymore\n"
                           "                        [replaced by '-i']\n"
                           "\n");
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfArgHidden | Handler::hfArgDeprecated,
         "--print-hidden --print-deprecated -h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgc,
         td.mAs2a.mpArgv));
      BOOST_REQUIRE_EQUAL( td.mStdOut.str(),
                           "Usage:\nMandatory arguments:\n"
                           "   -s                   String argument\n"
                           "\n"
                           "Optional arguments:\n"
                           "   -h,--help            Prints the program usage.\n"
                           "   --print-hidden       Also print hidden arguments in the usage.\n"
                           "   --print-deprecated   Also print deprecated and replaced arguments in the\n"
                           "                        usage.\n"
                           "   -i,--index           Integer argument\n"
                           "                        Default value: 42\n"
                           "   --hidden             Hidden boolean argument\n"
                           "                        [hidden]\n"
                           "   --deprecated         Deprecated argument, don't use anymore\n"
                           "                        [deprecated]\n"
                           "   -n,--name            Argument replaced by '-i', don't use anymore\n"
                           "                        [replaced by '-i']\n"
                           "\n");
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

} // usage_with_special_arguments



/// Two arguments, one optional, one mandatory, plus custom help arguments.
/// @since  0.10, 22.12.2016
BOOST_AUTO_TEST_CASE( argument_output_custom_help)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   string               string_arg;
   int                  opt_int_arg = 42;


   ah.addHelpArgument( "u,usage", "Custom arguments for help");

   ah.addArgument( "s",       DEST_VAR( string_arg),  "String argument")->setIsMandatory();
   ah.addArgument( "i,index", DEST_VAR( opt_int_arg), "Integer argument");

   ArgString2Array  as2a( "--usage", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( std_out.str(),
                        "Usage:\nMandatory arguments:\n"
                        "   -s           String argument\n"
                        "\n"
                        "Optional arguments:\n"
                        "   -h,--help    Prints the program usage.\n"
                        "   -u,--usage   Custom arguments for help\n"
                        "   -i,--index   Integer argument\n"
                        "                Default value: 42\n"
                        "\n");
   BOOST_REQUIRE( err_out.str().empty());

} // argument_output_custom_help



/// Test if checks are printed correctly in the usage.
/// @since  0.16.0, 14.08.2017
BOOST_AUTO_TEST_CASE( test_usage_output_checks)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   string               string_arg;
   int                  opt_int_arg1 = 42;
   int                  opt_int_arg2 = 42;
   int                  opt_int_arg3 = 42;


   ah.addArgument( "s",       DEST_VAR( string_arg),  "String argument")
                 ->setIsMandatory()
                 ->addCheck( celma::prog_args::values( "tiger,dragon"));
   ah.addArgument( "index1", DEST_VAR( opt_int_arg1), "Integer argument one")
                 ->addCheck( celma::prog_args::lower( 20));
   ah.addArgument( "index2", DEST_VAR( opt_int_arg2), "Integer argument two")
                 ->addCheck( celma::prog_args::upper( 100))
                 ->addConstraint( celma::prog_args::requires( "index3"));
   ah.addArgument( "index3", DEST_VAR( opt_int_arg3), "Integer argument three")
                 ->addCheck( celma::prog_args::range( 20, 100));

   ArgString2Array  as2a( "-h", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( std_out.str(),
                        "Usage:\nMandatory arguments:\n"
                              "   -s          String argument\n"
                              "               Check: Value in ( \"dragon\", \"tiger\")\n"
                              "\n"
                              "Optional arguments:\n"
                              "   -h,--help   Prints the program usage.\n"
                              "   --index1    Integer argument one\n"
                              "               Default value: 42\n"
                              "               Check: Value >= 20\n"
                              "   --index2    Integer argument two\n"
                              "               Default value: 42\n"
                              "               Check: Value < 100\n"
                              "               Constraint: Requires index3\n"
                              "   --index3    Integer argument three\n"
                              "               Default value: 42\n"
                              "               Check: 20 <= value < 100\n"
                              "\n");
   BOOST_REQUIRE( err_out.str().empty());

} // test_usage_output_checks



/// Two arguments, values assigned.
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( argument_verbose_assignment)
{

   std::ostringstream   std_out;
   std::ostringstream   err_out;
   Handler              ah( std_out, err_out,
                            Handler::AllHelp | Handler::hfUsageCont |
                            Handler::hfListArgVar | Handler::hfVerboseArgs);
   string               string_arg;
   int                  opt_int_arg = 42;


   ah.addArgument( "s",       DEST_VAR( string_arg),  "String argument")->setIsMandatory();
   ah.addArgument( "i,index", DEST_VAR( opt_int_arg), "Integer argument");

   const ArgString2Array  as2a( "-s text --list-arg-vars --index 4711", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE_EQUAL( std_out.str(),
                        "string_arg: value 'text' is assigned\n"
                        "Handler::listArgVars: is set\n"
                        "Arguments:\n"
                        "'-h,--help' calls function/method 'Handler::usage'.\n"
                        "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
                        "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
                        "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats\n"
                        "'-s' value type 'std::string', destination 'string_arg', value = text.\n"
                        "   value 'required' (2), mandatory, does not take multiple&separate values, print dflt, no checks, no formats\n"
                        "'-i,--index' value type 'int', destination 'opt_int_arg', value not set.\n"
                        "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, no formats\n"
                        "\n"
                        "opt_int_arg: value '4711' is assigned\n");
   BOOST_REQUIRE( err_out.str().empty());

} // argument_verbose_assignment



/// Usage with only short arguments.
/// @since  1.1.0, 17.11.2017
BOOST_AUTO_TEST_CASE( test_usage_short)
{

   {
      std::ostringstream   std_out;
      std::ostringstream   err_out;
      Handler              ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort);
      int                  intArg1 = 0;
      int                  intArg2 = 0;
      int                  intArg3 = 0;


      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      ArgString2Array  as2a( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( std_out.str(),
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help      Prints the program usage.\n"
         "   --help-short   Only print arguments with their short key in the usage.\n"
         "   -f             The first argument.\n"
         "                  Default value: 0\n"
         "   -s,--second    The second argument.\n"
         "                  Default value: 0\n"
         "   --third        The third argument.\n"
         "                  Default value: 0\n"
         "\n");
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   {
      std::ostringstream   std_out;
      std::ostringstream   err_out;
      Handler              ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort);
      int                  intArg1 = 0;
      int                  intArg2 = 0;
      int                  intArg3 = 0;


      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      ArgString2Array  as2a( "--help-short -h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( std_out.str(),
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -f   The first argument.\n"
         "        Default value: 0\n"
         "   -s   The second argument.\n"
         "        Default value: 0\n"
         "\n");
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

} // test_usage_short



/// Usage with only long arguments.
/// @since  1.1.0, 20.11.2017
BOOST_AUTO_TEST_CASE( test_usage_long)
{

   {
      std::ostringstream   std_out;
      std::ostringstream   err_out;
      Handler              ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageLong);
      int                  intArg1 = 0;
      int                  intArg2 = 0;
      int                  intArg3 = 0;


      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      ArgString2Array  as2a( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( std_out.str(),
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help     Prints the program usage.\n"
         "   --help-long   Only print arguments with their long key in the usage.\n"
         "   -f            The first argument.\n"
         "                 Default value: 0\n"
         "   -s,--second   The second argument.\n"
         "                 Default value: 0\n"
         "   --third       The third argument.\n"
         "                 Default value: 0\n"
         "\n");
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   {
      std::ostringstream   std_out;
      std::ostringstream   err_out;
      Handler              ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageLong);
      int                  intArg1 = 0;
      int                  intArg2 = 0;
      int                  intArg3 = 0;


      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      ArgString2Array  as2a( "--help-long -h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( std_out.str(),
         "Usage:\n"
         "Optional arguments:\n"
         "   --help        Prints the program usage.\n"
         "   --help-long   Only print arguments with their long key in the usage.\n"
         "   --second      The second argument.\n"
         "                 Default value: 0\n"
         "   --third       The third argument.\n"
         "                 Default value: 0\n"
         "\n");
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

} // test_usage_long



/// Usage with only short arguments.
/// @since  1.1.0, 04.12..2017
BOOST_AUTO_TEST_CASE( test_usage_subgroup_short)
{

   {
      std::ostringstream   std_out;
      std::ostringstream   err_out;
      Handler              masterAH( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort);

      Handler              subInput( 0);
      string               inputName;
      int                  inputType = 0;

      Handler              subOutput( 0);
      string               outputName;
      int                  outputType = 0;

      subInput.addArgument( "c", DEST_PAIR( inputName, inputType, 1),
         "cache name")->setPrintDefault( false);
      subInput.addArgument( "f,file", DEST_PAIR( inputName, inputType, 2),
         "file name")->setPrintDefault( false);
      subInput.addArgument( "queue", DEST_PAIR( inputName, inputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "i", &subInput, "input arguments");

      subOutput.addArgument( "cache", DEST_PAIR( outputName, outputType, 1),
         "cache name")->setPrintDefault( false);
      subOutput.addArgument( "f", DEST_PAIR( outputName, outputType, 2),
         "file name")->setPrintDefault( false);
      subOutput.addArgument( "q,queue", DEST_PAIR( outputName, outputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "o", &subOutput, "output arguments");

      ArgString2Array  as2a( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( std_out.str(),
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help      Prints the program usage.\n"
         "   --help-short   Only print arguments with their short key in the usage.\n"
         "   -i             input arguments\n"
         "   -o             output arguments\n"
         "\n");
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   {
      std::ostringstream   std_out;
      std::ostringstream   err_out;
      Handler              masterAH( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort
         | Handler::hfUsageLong);

      Handler              subInput( masterAH, Handler::AllHelp);
      string               inputName;
      int                  inputType = 0;

      Handler              subOutput( masterAH, Handler::AllHelp);
      string               outputName;
      int                  outputType = 0;

      subInput.addArgument( "c", DEST_PAIR( inputName, inputType, 1),
         "cache name")->setPrintDefault( false);
      subInput.addArgument( "f,file", DEST_PAIR( inputName, inputType, 2),
         "file name")->setPrintDefault( false);
      subInput.addArgument( "queue", DEST_PAIR( inputName, inputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "i", &subInput, "input arguments");

      subOutput.addArgument( "cache", DEST_PAIR( outputName, outputType, 1),
         "cache name")->setPrintDefault( false);
      subOutput.addArgument( "f", DEST_PAIR( outputName, outputType, 2),
         "file name")->setPrintDefault( false);
      subOutput.addArgument( "q,queue", DEST_PAIR( outputName, outputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "o", &subOutput, "output arguments");

      ArgString2Array  as2a( "-ih", nullptr);

      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( std_out.str(),
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help   Prints the program usage.\n"
         "   -c          cache name\n"
         "   -f,--file   file name\n"
         "   --queue     queue name\n"
         "\n");
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   {
      std::ostringstream   std_out;
      std::ostringstream   err_out;
      Handler              masterAH( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort
         | Handler::hfUsageLong);

      Handler              subInput( masterAH, Handler::AllHelp);
      string               inputName;
      int                  inputType = 0;

      Handler              subOutput( masterAH, Handler::AllHelp);
      string               outputName;
      int                  outputType = 0;

      subInput.addArgument( "c", DEST_PAIR( inputName, inputType, 1),
         "cache name")->setPrintDefault( false);
      subInput.addArgument( "f,file", DEST_PAIR( inputName, inputType, 2),
         "file name")->setPrintDefault( false);
      subInput.addArgument( "queue", DEST_PAIR( inputName, inputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "i", &subInput, "input arguments");

      subOutput.addArgument( "cache", DEST_PAIR( outputName, outputType, 1),
         "cache name")->setPrintDefault( false);
      subOutput.addArgument( "f", DEST_PAIR( outputName, outputType, 2),
         "file name")->setPrintDefault( false);
      subOutput.addArgument( "q,queue", DEST_PAIR( outputName, outputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "o", &subOutput, "output arguments");

      ArgString2Array  as2a( "--help-short -ih", nullptr);

      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE_EQUAL( std_out.str(),
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -c   cache name\n"
         "   -f   file name\n"
         "\n");
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

} // test_usage_subgroup_short



// =====  END OF test_argh_output_streams.cpp  =====
