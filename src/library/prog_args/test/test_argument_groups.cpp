
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
**    Test program for the module Groups using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args/groups.hpp"


// STL includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentGroupsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args/destination.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Groups;
using celma::prog_args::Handler;
using std::invalid_argument;
using std::ostringstream;
using std::runtime_error;



/// Check that it does not crash when no argument handlers are defined yet.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( no_argument_handlers)
{

   BOOST_REQUIRE_THROW( Groups::instance().evalArguments( 1, nullptr),
                        runtime_error);
   BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( "v,verbose"));

} // no_argument_handlers



/// Check that the same symbolic name cannot be used twice.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_name)
{

   Groups::SharedArgHndl  firstAH;


   BOOST_REQUIRE_NO_THROW( firstAH = Groups::instance().getArgHandler( "first"));
   BOOST_REQUIRE( firstAH.get() != nullptr);

   Groups::SharedArgHndl  secondAH;

   BOOST_REQUIRE_NO_THROW( secondAH = Groups::instance().getArgHandler( "first"));
   BOOST_REQUIRE( secondAH.get() != nullptr);
   BOOST_REQUIRE_EQUAL( firstAH, secondAH);

   // singleton Groups: have to clean up
   Groups::instance().removeAllArgHandler();

} // duplicate_name



/// Check that a standard argument used by two Handler objects is
/// detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_standard_arg)
{

   {
      auto                   firstAH = Groups::instance().getArgHandler( "first",
                                                                         Handler::hfHelpShort);
      Groups::SharedArgHndl  secondAH;

      BOOST_REQUIRE_THROW( secondAH = Groups::instance().getArgHandler( "second",
                                                                        Handler::hfHelpShort),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto                   firstAH = Groups::instance().getArgHandler( "first",
                                                                         Handler::hfHelpLong);
      Groups::SharedArgHndl  secondAH;

      BOOST_REQUIRE_THROW( secondAH = Groups::instance().getArgHandler( "second",
                                                                        Handler::hfHelpLong),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope


   {
      auto         firstAH = Groups::instance().getArgHandler( "first");
      auto         secondAH = Groups::instance().getArgHandler( "second");
      std::string  firstFree;
      std::string  secondFree;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "-", DEST_VAR( firstFree),
                                                    "first free argument"));
      BOOST_REQUIRE_THROW( secondAH->addArgument( "-", DEST_VAR( secondFree),
                                                  "second free argument"),
                                                  invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

} // duplicate_standard_arg



/// Check that duplicate application arguments are detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_application_arg)
{

   {
      auto  firstAH = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  quiet;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "q", DEST_VAR( quiet), "be quiet"));
      BOOST_REQUIRE_THROW( secondAH->addArgument( "q", DEST_VAR( quiet), "be quiet"),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  quiet;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "quiet", DEST_VAR( quiet), "be quiet"));
      BOOST_REQUIRE_THROW( secondAH->addArgument( "quiet", DEST_VAR( quiet), "be quiet"),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  quiet;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "q,quiet", DEST_VAR( quiet), "be quiet"));
      BOOST_REQUIRE_THROW( secondAH->addArgument( "quiet",   DEST_VAR( quiet), "be quiet"),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

} // duplicate_application_arg



/// Check that one Handler using the standard argument, and another
/// using the same argument character/string as application argument, is
/// detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( mix_std_appl_args)
{

   // first standard argument, second application argument
   {
      auto  firstAH  = Groups::instance().getArgHandler( "first", Handler::hfHelpShort);
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  quiet;


      BOOST_REQUIRE_THROW( secondAH->addArgument( "h", DEST_VAR( quiet), "be quiet"),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   // first application argument, second standard argument
   {
      auto  firstAH = Groups::instance().getArgHandler( "first");
      bool  quiet;


      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "h", DEST_VAR( quiet),
                                                    "be quiet"));

      Groups::SharedArgHndl  secondAH;

      BOOST_REQUIRE_THROW( secondAH = Groups::instance().getArgHandler( "second",
                                                                        Handler::hfHelpShort),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

} // mix_std_appl_args



/// Normal procedure: Two different arguments in two different argument handlers,
/// check handling.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( handle_arguments)
{

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      bool  secondFlag = false;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag"));

      // first check that it does not crash, then check if the arguments are
      // really found
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( 'f'));
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( 's'));
      BOOST_REQUIRE( Groups::instance().argumentExists( 'f'));
      BOOST_REQUIRE( Groups::instance().argumentExists( 's'));

      const ArgString2Array  as2a( "-f", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( !secondFlag);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      bool  secondFlag = false;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "first", DEST_VAR( firstFlag),  "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "second", DEST_VAR( secondFlag), "second flag"));

      // first check that it does not crash, then check if the arguments are
      // really found
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( "first"));
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( "second"));
      BOOST_REQUIRE( Groups::instance().argumentExists( "first"));
      BOOST_REQUIRE( Groups::instance().argumentExists( "second"));

      const ArgString2Array  as2a( "--second", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      bool  secondFlag = false;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag"));

      const ArgString2Array  as2a( "-f -s", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      bool  secondFlag = false;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag"));

      const ArgString2Array  as2a( "-sf", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      bool  secondFlag = false;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag"));

      const ArgString2Array  as2a( "-a", nullptr);

      BOOST_REQUIRE_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      bool  secondFlag = false;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag"));

      const ArgString2Array  as2a( "--long_argument", nullptr);

      BOOST_REQUIRE_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

} // handle_arguments



/// Check that missing mandatory arguments are detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( missing_mandatory)
{

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      int   secondArg = -1;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory());

      const ArgString2Array  as2a( "-f", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      int   secondArg = -1;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory());

      const ArgString2Array  as2a( "-s 5", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( !firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 5);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      int   secondArg = -1;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory());

      const ArgString2Array  as2a( "-f -s 17", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 17);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      int   secondArg = -1;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory());

      const ArgString2Array  as2a( "-fs 55", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 55);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

} // missing_mandatory



/// Test the special features of the argument group: Pass parameters on to each
/// handler object.
/// @since  0.13.0, 05.02.2017
BOOST_AUTO_TEST_CASE( group_features)
{

   Groups::reset();

   ostringstream  normal_out;
   ostringstream  error_out;

   Groups::instance( normal_out, error_out, Handler::hfVerboseArgs);

   auto  ah1 = Groups::instance().getArgHandler( "Handler 1");
   auto  ah2 = Groups::instance().getArgHandler( "Handler 2", Handler::AllHelp);
   bool  quiet = false;
   int   number = -1;

   ah1->addArgument( "q,quiet", DEST_VAR( quiet), "Be quiet");
   ah2->addArgument( "n,number", DEST_VAR( number), "Number")->setIsMandatory();

   const ArgString2Array  as2a( "-q -n 42", nullptr);

   BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));

   BOOST_REQUIRE_EQUAL( normal_out.str(),
                        "quiet: is set\n"
                        "number: value '42' is assigned\n");
   BOOST_REQUIRE( error_out.str().empty());

   Groups::instance().removeAllArgHandler();
   Groups::reset();

} // group_features



/// Test listing the argument groups.
/// @since  0.13.1, 07.02.2017
BOOST_AUTO_TEST_CASE( list_groups)
{

   Groups::reset();

   ostringstream  normal_out;
   ostringstream  error_out;

   Groups::instance( normal_out, error_out, Handler::hfListArgGroups);

   auto  ah1 = Groups::instance().getArgHandler( "Handler 1");
   auto  ah2 = Groups::instance().getArgHandler( "Handler 2", Handler::AllHelp);

   const ArgString2Array  as2a( "--list-arg-groups", nullptr);

   BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));

   BOOST_REQUIRE_EQUAL( normal_out.str(),
                        "list of known argument groups:\n"
                        "- Handler 1\n"
                        "- Handler 2\n");
   BOOST_REQUIRE( error_out.str().empty());

   Groups::instance().removeAllArgHandler();
   Groups::reset();

} // list_groups



class TestControlArgs
{
public:
   TestControlArgs():
      mOpen( 0),
      mClose( 0),
      mNot( 0)
   {
   } // TestControlArgs::TestControlArgs

   void open()
   {
      ++mOpen;
   }

   void close()
   {
      ++mClose;
   }

   void exclamation()
   {
      ++mNot;
   }

   int getOpen() const
   {
      return mOpen;
   }
   int getClose() const
   {
      return mClose;
   }
   int getExclamation() const
   {
      return mNot;
   }

private:
   int  mOpen;
   int  mClose;
   int  mNot;

}; // TestControlArgs



/// Test that control characters in the second group are handled correctly.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( control_characters)
{

   auto             firstAH  = Groups::instance().getArgHandler( "first");
   auto             secondAH = Groups::instance().getArgHandler( "second");
   bool             firstFlag = false;
   bool             secondFlag = false;
   TestControlArgs  tca;


   BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag"));
   BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag"));

   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( '(', std::bind( &TestControlArgs::open, &tca)));
   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( ')', std::bind( &TestControlArgs::close, &tca)));
   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( '!', std::bind( &TestControlArgs::exclamation, &tca)));
   BOOST_REQUIRE_THROW(    secondAH->addControlHandler( '#', std::bind( &TestControlArgs::open, &tca)),
                           invalid_argument);

   const ArgString2Array  as2a( "-f ( ! -s )", nullptr);

   BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV));
   BOOST_REQUIRE( firstFlag);
   BOOST_REQUIRE( secondFlag);
   BOOST_REQUIRE_EQUAL( tca.getOpen(), 1);
   BOOST_REQUIRE_EQUAL( tca.getClose(), 1);
   BOOST_REQUIRE_EQUAL( tca.getExclamation(), 1);

   // singleton Groups: have to clean up
   Groups::instance().removeAllArgHandler();

} // control_characters



/// Test if an argument exists.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( argument_exists)
{

   auto  firstAH  = Groups::instance().getArgHandler( "exists_test");
   bool  firstFlag = false;


   BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "e", DEST_VAR( firstFlag), "exists"));
   BOOST_REQUIRE( Groups::instance().argumentExists( 'e'));
   BOOST_REQUIRE( !Groups::instance().argumentExists( 'c'));

} // argument_exists



/// Test if addArgHandler throws exception when an empty name is passed.
/// @since  0.13.0, 05.02.2017  (changed from nullptr test)
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( add_group_empty_name)
{

   Groups::SharedArgHndl  argGroup;


   BOOST_REQUIRE_THROW( Groups::instance().getArgHandler( ""), std::exception);

} // add_group_empty_name



// =====  END OF test_argument_groups.cpp  =====
