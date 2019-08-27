
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
**    Test program for the feature "output streams parameters" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ArgHOutputStreams
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::ArgString2Array;
using celma::appl::make_arg_array;
using celma::prog_args::Handler;
using celma::test::multilineStringCompare;
using std::ostringstream;
using std::string;



/// Simple case: Empty usage except for help arguments.
///
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( help_usage)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);


   auto const  as2a = make_arg_array( "-h", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( celma::test::multilineStringCompare( std_out,
      "Usage:\n"
      "Optional arguments:\n"
      "   -h,--help    Prints the program usage.\n"
      "   --help-arg   Prints the usage for the given argument.\n"
      "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // help_usage



/// Empty usage except for custom help arguments.
///
/// @since  0.10, 22.12.2016
BOOST_AUTO_TEST_CASE( custom_help_usage)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::hfUsageCont);


   ah.addHelpArgument( "u,usage", "Custom arguments for help");

   auto const  as2a = make_arg_array( "-u", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( multilineStringCompare( std_out,
      "Usage:\n"
      "Optional arguments:\n"
      "   -u,--usage   Custom arguments for help\n"
      "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // custom_help_usage



/// Two arguments, one optional, one mandatory.
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( argument_output)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   string          string_arg;
   int             opt_int_arg = 42;


   ah.addArgument( "s",       DEST_VAR( string_arg),  "String argument")->setIsMandatory();
   ah.addArgument( "i,index", DEST_VAR( opt_int_arg), "Integer argument");

   auto const  as2a = make_arg_array( "-h", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( multilineStringCompare( std_out,
                        "Usage:\nMandatory arguments:\n"
                        "   -s           String argument\n"
                        "\n"
                        "Optional arguments:\n"
                        "   -h,--help    Prints the program usage.\n"
                        "   --help-arg   Prints the usage for the given argument.\n"
                        "   -i,--index   Integer argument\n"
                        "                Default value: 42\n"
                        "\n"));
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
      ostringstream          mStdOut;
      /// Captures the output to \c stderr.
      ostringstream          mErrOut;
      /// The argument handler object used for the test.
      Handler                mHandler;
      /// Mandatory string argument.
      string                 mStringArg;
      /// Optional integer argument.
      int                    mOptIntArg = 42;
      /// Deprecated argument variable.
      bool                   mDummy = false;
      /// Argument "replaced by".
      string                 mReplacedBy;
      /// Hidden variable.
      bool                   mHidden = false;
      /// Argument string split to argc, argv.
      const ArgString2Array  mAs2a;
   }; // TestData

   {
      TestData  td( 0, "-h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s           String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -i,--index   Integer argument\n"
         "                Default value: 42\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfUsageHidden, "-h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s           String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -i,--index   Integer argument\n"
         "                Default value: 42\n"
         "   --hidden     Hidden boolean argument\n"
         "                [hidden]\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfUsageDeprecated, "-h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s             String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help      Prints the program usage.\n"
         "   --help-arg     Prints the usage for the given argument.\n"
         "   -i,--index     Integer argument\n"
         "                  Default value: 42\n"
         "   --deprecated   Deprecated argument, don't use anymore\n"
         "                  [deprecated]\n"
         "   -n,--name      Argument replaced by '-i', don't use anymore\n"
         "                  [replaced by '-i']\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfUsageHidden | Handler::hfUsageDeprecated, "-h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s             String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help      Prints the program usage.\n"
         "   --help-arg     Prints the usage for the given argument.\n"
         "   -i,--index     Integer argument\n"
         "                  Default value: 42\n"
         "   --hidden       Hidden boolean argument\n"
         "                  [hidden]\n"
         "   --deprecated   Deprecated argument, don't use anymore\n"
         "                  [deprecated]\n"
         "   -n,--name      Argument replaced by '-i', don't use anymore\n"
         "                  [replaced by '-i']\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   // set a custom argument to activate "print hidden", but don't use it
   {
      TestData  td( 0, "-h");

      td.mHandler.addArgumentPrintHidden( "-H");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s           String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -i,--index   Integer argument\n"
         "                Default value: 42\n"
         "   -H           Also print hidden arguments in the usage.\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   // use a custom argument to activate "print hidden"
   {
      TestData  td( 0, "-H -h");

      td.mHandler.addArgumentPrintHidden( "-H", "Print hidden arguments too.");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s           String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -i,--index   Integer argument\n"
         "                Default value: 42\n"
         "   --hidden     Hidden boolean argument\n"
         "                [hidden]\n"
         "   -H           Print hidden arguments too.\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfArgHidden, "--print-hidden -h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s               String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help        Prints the program usage.\n"
         "   --help-arg       Prints the usage for the given argument.\n"
         "   --print-hidden   Also print hidden arguments in the usage.\n"
         "   -i,--index       Integer argument\n"
         "                    Default value: 42\n"
         "   --hidden         Hidden boolean argument\n"
         "                    [hidden]\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfArgDeprecated, "--print-deprecated -h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s                   String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help            Prints the program usage.\n"
         "   --help-arg           Prints the usage for the given argument.\n"
         "   --print-deprecated   Also print deprecated and replaced arguments in the\n"
         "                        usage.\n"
         "   -i,--index           Integer argument\n"
         "                        Default value: 42\n"
         "   --deprecated         Deprecated argument, don't use anymore\n"
         "                        [deprecated]\n"
         "   -n,--name            Argument replaced by '-i', don't use anymore\n"
         "                        [replaced by '-i']\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

   {
      TestData  td( Handler::hfArgHidden | Handler::hfArgDeprecated,
         "--print-hidden --print-deprecated -h");

      BOOST_REQUIRE_NO_THROW( td.mHandler.evalArguments( td.mAs2a.mArgC,
         td.mAs2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( td.mStdOut,
         "Usage:\nMandatory arguments:\n"
         "   -s                   String argument\n"
         "\n"
         "Optional arguments:\n"
         "   -h,--help            Prints the program usage.\n"
         "   --help-arg           Prints the usage for the given argument.\n"
         "   --print-deprecated   Also print deprecated and replaced arguments in the\n"
         "                        usage.\n"
         "   --print-hidden       Also print hidden arguments in the usage.\n"
         "   -i,--index           Integer argument\n"
         "                        Default value: 42\n"
         "   --hidden             Hidden boolean argument\n"
         "                        [hidden]\n"
         "   --deprecated         Deprecated argument, don't use anymore\n"
         "                        [deprecated]\n"
         "   -n,--name            Argument replaced by '-i', don't use anymore\n"
         "                        [replaced by '-i']\n"
         "\n"));
      BOOST_REQUIRE( td.mErrOut.str().empty());
   } // end scope

} // usage_with_special_arguments



/// Two arguments, one optional, one mandatory, plus custom help arguments.
/// @since  0.10, 22.12.2016
BOOST_AUTO_TEST_CASE( argument_output_custom_help)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   string          string_arg;
   int             opt_int_arg = 42;


   ah.addHelpArgument( "u,usage", "Custom arguments for help");

   ah.addArgument( "s",       DEST_VAR( string_arg),  "String argument")->setIsMandatory();
   ah.addArgument( "i,index", DEST_VAR( opt_int_arg), "Integer argument");

   auto const  as2a = make_arg_array( "--usage", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( multilineStringCompare( std_out,
      "Usage:\nMandatory arguments:\n"
      "   -s           String argument\n"
      "\n"
      "Optional arguments:\n"
      "   -h,--help    Prints the program usage.\n"
      "   --help-arg   Prints the usage for the given argument.\n"
      "   -u,--usage   Custom arguments for help\n"
      "   -i,--index   Integer argument\n"
      "                Default value: 42\n"
      "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // argument_output_custom_help



/// Test if checks are printed correctly in the usage.
/// @since  0.16.0, 14.08.2017
BOOST_AUTO_TEST_CASE( test_usage_output_checks)
{

   ostringstream   std_out;
   ostringstream   err_out;
   Handler         ah( std_out, err_out, Handler::AllHelp | Handler::hfUsageCont);
   string          string_arg;
   int             opt_int_arg1 = 42;
   int             opt_int_arg2 = 42;
   int             opt_int_arg3 = 42;
   std::string     file;
   std::string     dir;
   std::string     existing_parent_dir;
   std::string     absolute_path;
   std::string     name;


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
   ah.addArgument( "f,file", DEST_VAR( file), "Existing file")
                 ->addCheck( celma::prog_args::isFile())
                 ->setPrintDefault( false);
   ah.addArgument( "d,dir", DEST_VAR( dir), "Existing directory")
                 ->addCheck( celma::prog_args::isDirectory())
                 ->setPrintDefault( false);
   ah.addArgument( "p", DEST_VAR( existing_parent_dir), "Existing parent directory")
                 ->addCheck( celma::prog_args::parentDirectoryExists())
                 ->setPrintDefault( false);
   ah.addArgument( "absolute", DEST_VAR( absolute_path), "Absolute path required")
                 ->addCheck( celma::prog_args::isAbsolutePath())
                 ->setPrintDefault( false);
   ah.addArgument( "n", DEST_VAR( name), "A name")
                 ->addCheck( celma::prog_args::pattern( "^[A-Z][a-z]+"))
                 ->setPrintDefault( false);

   auto const  as2a = make_arg_array( "-h", nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( multilineStringCompare( std_out,
      "Usage:\nMandatory arguments:\n"
            "   -s           String argument\n"
            "                Check: Value in ( \"dragon\", \"tiger\")\n"
            "\n"
            "Optional arguments:\n"
            "   -h,--help    Prints the program usage.\n"
            "   --help-arg   Prints the usage for the given argument.\n"
            "   --index1     Integer argument one\n"
            "                Default value: 42\n"
            "                Check: Value >= 20\n"
            "   --index2     Integer argument two\n"
            "                Default value: 42\n"
            "                Check: Value < 100\n"
            "                Constraint: Requires index3\n"
            "   --index3     Integer argument three\n"
            "                Default value: 42\n"
            "                Check: 20 <= value < 100\n"
            "   -f,--file    Existing file\n"
            "                Check: is a file\n"
            "   -d,--dir     Existing directory\n"
            "                Check: is a directory\n"
            "   -p           Existing parent directory\n"
            "                Check: parent directory exists\n"
            "   --absolute   Absolute path required\n"
            "                Check: is an absolute path\n"
            "   -n           A name\n"
            "                Check: Value matches '^[A-Z][a-z]+'\n"
            "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // test_usage_output_checks



/// Multiple arguments, values assigned.
///
/// @since  0.3, 04.06.2016
BOOST_AUTO_TEST_CASE( argument_verbose_assignment)
{

   using celma::common::CheckAssign;
   using celma::prog_args::LevelCounter;

   ostringstream       std_out;
   ostringstream       err_out;
   Handler             ah( std_out, err_out,
                           Handler::AllHelp | Handler::hfUsageCont |
                           Handler::hfListArgVar | Handler::hfVerboseArgs);
   string              string_arg;
   int                 opt_int_arg = 42;
   CheckAssign< int>   optional_int;
   CheckAssign< bool>  optional_bool;
   LevelCounter        verbose_level;


   ah.addArgument( "s",          DEST_VAR( string_arg),    "String argument")
      ->setIsMandatory();
   ah.addArgument( "i,index",    DEST_VAR( opt_int_arg),   "Integer argument");
   ah.addArgument( "o,opt-int",  DEST_VAR( optional_int),  "Optional integer argument");
   ah.addArgument( "opt-bool",   DEST_VAR( optional_bool), "Optional boolean argument");
   ah.addArgument( "v,verbose",  DEST_VAR( verbose_level), "Verbose level counter");

   auto const  as2a = make_arg_array( "-s text --list-arg-vars --index 4711 -o 13 --opt-bool -vv --list-arg-vars",
      nullptr);

   BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
   // std::cerr << std::endl << std_out.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( std_out,
      "string_arg: value 'text' is assigned\n"
      "Handler::listArgVars: is set\n"
      "Arguments:\n"
      "'-h,--help' calls function/method 'Handler::usage'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--help-arg' calls function/method 'Prints the usage for the given argument.'.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::string', destination 'string_arg', value = \"text\".\n"
      "   value 'required' (2), mandatory, does not take multiple&separate values, print dflt, no checks, no formats.\n"
      "'-i,--index' value type 'int', destination 'opt_int_arg', value not set.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, no formats.\n"
      "'-o,--opt-int' value type 'int', destination 'CheckAssign< optional_int>', value not set.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--opt-bool' sets boolean flag on 'CheckAssign< optional_bool>'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-v,--verbose' value type 'LevelCounter', destination variable 'verbose_level', current value 0.\n"
      "   value 'optional' (1), optional, does not take multiple&separate values, print dflt, no checks, no formats.\n"
      "\n"
      "opt_int_arg: value '4711' is assigned\n"
      "optional_int: value '13' is assigned\n"
      "optional_bool: is set\n"
      "verbose_level: is set\n"
      "verbose_level: is set\n"
      "Handler::listArgVars: is set\n"
      "Arguments:\n"
      "'-h,--help' calls function/method 'Handler::usage'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--help-arg' calls function/method 'Prints the usage for the given argument.'.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--list-arg-vars' calls function/method 'Handler::listArgVars'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-s' value type 'std::string', destination 'string_arg', value = \"text\".\n"
      "   value 'required' (2), mandatory, does not take multiple&separate values, print dflt, no checks, no formats.\n"
      "'-i,--index' value type 'int', destination 'opt_int_arg', value = 4711.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, print dflt, no checks, no formats.\n"
      "'-o,--opt-int' value type 'int', destination 'CheckAssign< optional_int>', value = 13.\n"
      "   value 'required' (2), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'--opt-bool' sets boolean flag on 'CheckAssign< optional_bool>'.\n"
      "   value 'none' (0), optional, does not take multiple&separate values, don't print dflt, no checks, no formats.\n"
      "'-v,--verbose' value type 'LevelCounter', destination variable 'verbose_level', current value 2.\n"
      "   value 'optional' (1), optional, does not take multiple&separate values, print dflt, no checks, no formats.\n"
      "\n"));
   BOOST_REQUIRE( err_out.str().empty());

} // argument_verbose_assignment



/// Usage with only short arguments.
/// @since  1.1.0, 17.11.2017
BOOST_AUTO_TEST_CASE( test_usage_short)
{

   // activate argument for short usage only, but don't use it
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort);
      int             intArg1 = 0;
      int             intArg2 = 0;
      int             intArg3 = 0;

      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help      Prints the program usage.\n"
         "   --help-arg     Prints the usage for the given argument.\n"
         "   --help-short   Only print arguments with their short key in the usage.\n"
         "   -f             The first argument.\n"
         "                  Default value: 0\n"
         "   -s,--second    The second argument.\n"
         "                  Default value: 0\n"
         "   --third        The third argument.\n"
         "                  Default value: 0\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // use the flag and standard argument for short usage
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort);
      int             intArg1 = 0;
      int             intArg2 = 0;
      int             intArg3 = 0;

      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      auto const  as2a = make_arg_array( "--help-short -h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -f   The first argument.\n"
         "        Default value: 0\n"
         "   -s   The second argument.\n"
         "        Default value: 0\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // set a custom argument for short usage only, but don't use it
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont);
      int             intArg1 = 0;
      int             intArg2 = 0;
      int             intArg3 = 0;

      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      ah.addArgumentUsageShort( "S");

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help     Prints the program usage.\n"
         "   --help-arg    Prints the usage for the given argument.\n"
         "   -f            The first argument.\n"
         "                 Default value: 0\n"
         "   -s,--second   The second argument.\n"
         "                 Default value: 0\n"
         "   --third       The third argument.\n"
         "                 Default value: 0\n"
         "   -S            Only print arguments with their short key in the usage.\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // set and use a custom argument for short usage
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont);
      int             intArg1 = 0;
      int             intArg2 = 0;
      int             intArg3 = 0;

      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      ah.addArgumentUsageShort( "S", "Short usage only.");

      auto const  as2a = make_arg_array( "-S -h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -f   The first argument.\n"
         "        Default value: 0\n"
         "   -s   The second argument.\n"
         "        Default value: 0\n"
         "   -S   Short usage only.\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

} // test_usage_short



/// Usage with only long arguments.
/// @since  1.1.0, 20.11.2017
BOOST_AUTO_TEST_CASE( test_usage_long)
{

   // activate argument for long usage only, but don't use it
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageLong);
      int             intArg1 = 0;
      int             intArg2 = 0;
      int             intArg3 = 0;

      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help     Prints the program usage.\n"
         "   --help-arg    Prints the usage for the given argument.\n"
         "   --help-long   Only print arguments with their long key in the usage.\n"
         "   -f            The first argument.\n"
         "                 Default value: 0\n"
         "   -s,--second   The second argument.\n"
         "                 Default value: 0\n"
         "   --third       The third argument.\n"
         "                 Default value: 0\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // use the flag and standard argument for long usage
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageLong);
      int             intArg1 = 0;
      int             intArg2 = 0;
      int             intArg3 = 0;

      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      auto const  as2a = make_arg_array( "--help-long -h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   --help        Prints the program usage.\n"
         "   --help-arg    Prints the usage for the given argument.\n"
         "   --help-long   Only print arguments with their long key in the usage.\n"
         "   --second      The second argument.\n"
         "                 Default value: 0\n"
         "   --third       The third argument.\n"
         "                 Default value: 0\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // set a custom argument for long usage only, but don't use it
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont);
      int             intArg1 = 0;
      int             intArg2 = 0;
      int             intArg3 = 0;

      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      ah.addArgumentUsageLong( "L");

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help     Prints the program usage.\n"
         "   --help-arg    Prints the usage for the given argument.\n"
         "   -f            The first argument.\n"
         "                 Default value: 0\n"
         "   -s,--second   The second argument.\n"
         "                 Default value: 0\n"
         "   --third       The third argument.\n"
         "                 Default value: 0\n"
         "   -L            Only print arguments with their long key in the usage.\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   // set and use a custom argument for short usage
   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         ah( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont);
      int             intArg1 = 0;
      int             intArg2 = 0;
      int             intArg3 = 0;

      ah.addArgument( "f", DEST_VAR( intArg1), "The first argument.");
      ah.addArgument( "s,second", DEST_VAR( intArg2), "The second argument.");
      ah.addArgument( "third", DEST_VAR( intArg3), "The third argument.");

      ah.addArgumentUsageLong( "L", "Long arguments only.");

      auto const  as2a = make_arg_array( "-L -h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   --help       Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   --second     The second argument.\n"
         "                Default value: 0\n"
         "   --third      The third argument.\n"
         "                Default value: 0\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

} // test_usage_long



/// Usage with only short arguments.
/// @since  1.1.0, 04.12..2017
BOOST_AUTO_TEST_CASE( test_usage_subgroup_short)
{

   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         masterAH( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort);

      Handler         subInput( 0);
      string          inputName;
      int             inputType = 0;

      Handler         subOutput( 0);
      string          outputName;
      int             outputType = 0;

      subInput.addArgument( "c", DEST_PAIR( inputName, inputType, 1),
         "cache name")->setPrintDefault( false);
      subInput.addArgument( "f,file", DEST_PAIR( inputName, inputType, 2),
         "file name")->setPrintDefault( false);
      subInput.addArgument( "queue", DEST_PAIR( inputName, inputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "i", subInput, "input arguments");

      subOutput.addArgument( "cache", DEST_PAIR( outputName, outputType, 1),
         "cache name")->setPrintDefault( false);
      subOutput.addArgument( "f", DEST_PAIR( outputName, outputType, 2),
         "file name")->setPrintDefault( false);
      subOutput.addArgument( "q,queue", DEST_PAIR( outputName, outputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "o", subOutput, "output arguments");

      auto const  as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help      Prints the program usage.\n"
         "   --help-arg     Prints the usage for the given argument.\n"
         "   --help-short   Only print arguments with their short key in the usage.\n"
         "   -i             input arguments\n"
         "   -o             output arguments\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         masterAH( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort
         | Handler::hfUsageLong);

      Handler         subInput( masterAH, Handler::AllHelp);
      string          inputName;
      int             inputType = 0;

      Handler         subOutput( masterAH, Handler::AllHelp);
      string          outputName;
      int             outputType = 0;

      subInput.addArgument( "c", DEST_PAIR( inputName, inputType, 1),
         "cache name")->setPrintDefault( false);
      subInput.addArgument( "f,file", DEST_PAIR( inputName, inputType, 2),
         "file name")->setPrintDefault( false);
      subInput.addArgument( "queue", DEST_PAIR( inputName, inputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "i", subInput, "input arguments");

      subOutput.addArgument( "cache", DEST_PAIR( outputName, outputType, 1),
         "cache name")->setPrintDefault( false);
      subOutput.addArgument( "f", DEST_PAIR( outputName, outputType, 2),
         "file name")->setPrintDefault( false);
      subOutput.addArgument( "q,queue", DEST_PAIR( outputName, outputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "o", subOutput, "output arguments");

      auto const  as2a = make_arg_array( "-ih", nullptr);

      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -c           cache name\n"
         "   -f,--file    file name\n"
         "   --queue      queue name\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

   {
      ostringstream   std_out;
      ostringstream   err_out;
      Handler         masterAH( std_out, err_out,
         Handler::AllHelp | Handler::hfUsageCont | Handler::hfUsageShort
         | Handler::hfUsageLong);

      Handler         subInput( masterAH, Handler::AllHelp);
      string          inputName;
      int             inputType = 0;

      Handler         subOutput( masterAH, Handler::AllHelp);
      string          outputName;
      int             outputType = 0;

      subInput.addArgument( "c", DEST_PAIR( inputName, inputType, 1),
         "cache name")->setPrintDefault( false);
      subInput.addArgument( "f,file", DEST_PAIR( inputName, inputType, 2),
         "file name")->setPrintDefault( false);
      subInput.addArgument( "queue", DEST_PAIR( inputName, inputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "i", subInput, "input arguments");

      subOutput.addArgument( "cache", DEST_PAIR( outputName, outputType, 1),
         "cache name")->setPrintDefault( false);
      subOutput.addArgument( "f", DEST_PAIR( outputName, outputType, 2),
         "file name")->setPrintDefault( false);
      subOutput.addArgument( "q,queue", DEST_PAIR( outputName, outputType, 3),
         "queue name")->setPrintDefault( false);
      masterAH.addArgument( "o", subOutput, "output arguments");

      auto const  as2a = make_arg_array( "--help-short -ih", nullptr);

      BOOST_REQUIRE_NO_THROW( masterAH.evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( multilineStringCompare( std_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h   Prints the program usage.\n"
         "   -c   cache name\n"
         "   -f   file name\n"
         "\n"));
      BOOST_REQUIRE( err_out.str().empty());
   } // end scope

} // test_usage_subgroup_short



// =====  END OF test_argh_output_streams_c.cpp  =====
