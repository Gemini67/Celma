
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for arguments that will be processed by another object/tool,
**    using the Boost.Test module.
**
--*/


// module to test, header file include
#include "celma/prog_args.hpp"


// STL includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ProgAgsCommandTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Handler;


// module definitions

namespace {


/// @since  0.14.2, 12.05.2017
class TestFixtureBase
{
public:
   /// 
   /// @since  0.14.2, 12.05.2017
   TestFixtureBase():
      mArgH( 0),
      mCommand()
   {

      // some basic arguments
      mArgH.addArgument( "v", DEST_VAR( mVerbose), "verbose mode");
      mArgH.addArgument( "c", DEST_VAR( mCount), "count");

   } // TestFixtureBase::TestFixtureBase

protected:
   Handler      mArgH;
   bool         mVerbose = false;
   int          mCount = 0;
   std::string  mCommand;  

}; // TestFixtureBase


/// @since  0.14.2, 12.05.2017
class TestFixturePositional: public TestFixtureBase
{
public:
   TestFixturePositional():
      TestFixtureBase()
   {
   
      BOOST_REQUIRE_NO_THROW( mArgH.addArgument( "-", DEST_VAR( mCommand),
                                                 "command")
                                               ->setValueMode( Handler::ValueMode::command));

   } // TestFixturePositional::TestFixturePositional
   
}; // TestFixturePositional


/// @since  0.14.2, 12.05.2017
class TestFixtureCharArg: public TestFixtureBase
{
public:
   TestFixtureCharArg():
      TestFixtureBase()
   {
   
      BOOST_REQUIRE_NO_THROW( mArgH.addArgument( "x", DEST_VAR( mCommand), "command")
                                               ->setValueMode( Handler::ValueMode::command));

   } // TestFixtureCharArg::TestFixtureCharArg
   
}; // TestFixtureCharArg


} // namespace



/// Test setting up a command argument with the wrong destination types.
/// @since  0.14.2, 12.05.2017
BOOST_AUTO_TEST_CASE( test_wrong_dest_type)
{

   {
      Handler  ah( 0);
      bool     flag;
      BOOST_REQUIRE_THROW( ah.addArgument( "-", DEST_VAR( flag), "command")
                                         ->setValueMode( Handler::ValueMode::command),
                           std::invalid_argument);
   } // end scope
   
   {
      Handler  ah( 0);
      bool     flag;
      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( flag), "command")
                                         ->setValueMode( Handler::ValueMode::command),
                           std::invalid_argument);
   } // end scope
   
   {
      Handler  ah( 0);
      int      value;
      BOOST_REQUIRE_THROW( ah.addArgument( "-", DEST_VAR( value), "command")
                                         ->setValueMode( Handler::ValueMode::command),
                           std::invalid_argument);
   } // end scope
   
   {
      Handler  ah( 0);
      int      value;
      BOOST_REQUIRE_THROW( ah.addArgument( "f", DEST_VAR( value), "command")
                                         ->setValueMode( Handler::ValueMode::command),
                           std::invalid_argument);
   } // end scope
   
} // test_wrong_dest_type



/// Test when no argument is used at all.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_no_args_pos, TestFixturePositional)
{

   const ArgString2Array  as2a( "", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( !mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 0);
   BOOST_REQUIRE( mCommand.empty());

} // test_no_args_pos



/// Test when no argument is used at all.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_no_args_carg, TestFixtureCharArg)
{

   const ArgString2Array  as2a( "", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( !mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 0);
   BOOST_REQUIRE( mCommand.empty());

} // test_no_args_carg



/// Test when flag is used but not the command argument.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_only_flag_pos, TestFixturePositional)
{

   const ArgString2Array  as2a( "-v", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 0);
   BOOST_REQUIRE( mCommand.empty());

} // test_only_flag_pos



/// Test when flag is used but not the command argument.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_only_flag_carg, TestFixtureCharArg)
{

   const ArgString2Array  as2a( "-v", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 0);
   BOOST_REQUIRE( mCommand.empty());

} // test_only_flag_carg



/// Test when only command argument is used.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_only_cmd_pos, TestFixturePositional)
{

   const ArgString2Array  as2a( "command list vars", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( !mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 0);
   BOOST_REQUIRE_EQUAL( mCommand, "command list vars");

} // test_only_cmd_pos



/// Test when only command argument is used.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_only_cmd_carg, TestFixtureCharArg)
{

   const ArgString2Array  as2a( "-x list vars", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( !mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 0);
   BOOST_REQUIRE_EQUAL( mCommand, "list vars");

} // test_only_cmd_carg



/// Test when the command argument is used after the flag argument.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_cmd_after_flag_pos, TestFixturePositional)
{

   const ArgString2Array  as2a( "-v command list vars", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 0);
   BOOST_REQUIRE_EQUAL( mCommand, "command list vars");

} // test_cmd_after_flag_pos



/// Test when the command argument is used after the flag argument.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_cmd_after_flag_carg, TestFixtureCharArg)
{

   const ArgString2Array  as2a( "-v -x list vars", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 0);
   BOOST_REQUIRE_EQUAL( mCommand, "list vars");

} // test_cmd_after_flag_carg



/// Test when the command argument is used after the value argument.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_cmd_after_value_pos, TestFixturePositional)
{

   const ArgString2Array  as2a( "-c 42 command list vars", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( !mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 42);
   BOOST_REQUIRE_EQUAL( mCommand, "command list vars");

} // test_cmd_after_value_pos



/// Test when the command argument is used after the flag argument.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_cmd_after_value_carg, TestFixtureCharArg)
{

   const ArgString2Array  as2a( "-c 42 -x list vars", nullptr);

   BOOST_REQUIRE_NO_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( !mVerbose);
   BOOST_REQUIRE_EQUAL( mCount, 42);
   BOOST_REQUIRE_EQUAL( mCommand, "list vars");

} // test_cmd_after_value_carg



/// Test wrong usage when combining the argument character with another.
/// @since  0.14.2, 12.05.2017
BOOST_FIXTURE_TEST_CASE( test_wrong_usage_carg, TestFixtureCharArg)
{

   const ArgString2Array  as2a( "-vx list vars", nullptr);

   BOOST_REQUIRE_THROW( mArgH.evalArguments( as2a.mArgC, as2a.mpArgV),
                        std::runtime_error);

} // test_wrong_usage_carg



// =====  END OF test_argh_command_arg.cpp  =====

