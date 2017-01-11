
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module prog_args::Groups using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// STL includes
#include <string>
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE ArgumentGroupsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args/groups.hpp"


using namespace std;
using namespace celma;


// module definitions


/// Check that it does not crash when no argument handlers are defined yet.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( no_argument_handlers)
{

   BOOST_REQUIRE_THROW( prog_args::Groups::instance().evalArguments( 1, nullptr),
                        runtime_error);
   BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().argumentExists( "v,verbose"));

} // end no_argument_handlers



/// Check that the same symbolic name cannot be used twice.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_name)
{

   prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
   prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));


   BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
   BOOST_REQUIRE_THROW(    prog_args::Groups::instance().addArgHandler( "first", secondAH),
                           runtime_error);

   {
      prog_args::Groups::SharedArgHndl  unknownAH( prog_args::Groups::instance().getHandler( "no-such-handler"));
      BOOST_REQUIRE( unknownAH.get() == nullptr);
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  findFirstAH( prog_args::Groups::instance().getHandler( "first"));
      BOOST_REQUIRE( findFirstAH.get() != nullptr);
   } // end scope

   // singleton prog_args::Groups: have to clean up
   prog_args::Groups::instance().removeArgHandler( "first");

} // end duplicate_name



/// Check that a standard argument used by two prog_args::Handler objects is
/// detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_standard_arg)
{

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( prog_args::Handler::hfHelpShort));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( prog_args::Handler::hfHelpShort));

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( prog_args::Handler::hfHelpLong));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( prog_args::Handler::hfHelpLong));

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
   } // end scope


   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      string  firstFree;
      string  secondFree;

      firstAH->addArgument( DEST_VAR( firstFree), "first free argument");
      secondAH->addArgument( DEST_VAR( secondFree), "second free argument");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
   } // end scope

} // end duplicate_standard_arg



/// Check that duplicate application arguments are detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_application_arg)
{

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  quiet;

      firstAH->addArgument(  "q", DEST_VAR( quiet), "be quiet");
      secondAH->addArgument( "q", DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  quiet;

      firstAH->addArgument(  "quiet", DEST_VAR( quiet), "be quiet");
      secondAH->addArgument( "quiet", DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  quiet;

      firstAH->addArgument(  "q,quiet", DEST_VAR( quiet), "be quiet");
      secondAH->addArgument( "quiet",   DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
   } // end scope

} // end duplicate_application_arg



/// Check that one prog_args::Handler using the standard argument, and another
/// using the same argument character/string as application argument, is
/// detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( mix_std_appl_args)
{

   // first standard argument, second application argument
   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( prog_args::Handler::hfHelpShort));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  quiet;

      secondAH->addArgument( "h", DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
   } // end scope

   // first application argument, second standard argument
   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( prog_args::Handler::hfHelpShort));
      bool  quiet;

      firstAH->addArgument( "h", DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
   } // end scope

} // end mix_std_appl_args



/// Normal procedure: Two different arguments in two different argument handlers,
/// check handling.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( handle_arguments)
{

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      bool  secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      // first check that it does not crash, then check if the arguments are
      // really found
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().argumentExists( 'f'));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().argumentExists( 's'));
      BOOST_REQUIRE( prog_args::Groups::instance().argumentExists( 'f'));
      BOOST_REQUIRE( prog_args::Groups::instance().argumentExists( 's'));

      appl::ArgString2Array  as2a( "-f", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( !secondFlag);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      bool  secondFlag = false;


      firstAH->addArgument(  "first", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "second", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      // first check that it does not crash, then check if the arguments are
      // really found
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().argumentExists( "first"));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().argumentExists( "second"));
      BOOST_REQUIRE( prog_args::Groups::instance().argumentExists( "first"));
      BOOST_REQUIRE( prog_args::Groups::instance().argumentExists( "second"));

      appl::ArgString2Array  as2a( "--second", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      bool  secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      appl::ArgString2Array  as2a( "-f -s", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      bool  secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      appl::ArgString2Array  as2a( "-sf", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      bool  secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      appl::ArgString2Array  as2a( "-a", nullptr);

      BOOST_REQUIRE_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv),
                           invalid_argument);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      bool  secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      appl::ArgString2Array  as2a( "--long_argument", nullptr);

      BOOST_REQUIRE_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv),
                           invalid_argument);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

} // end handle_arguments



/// Check that missing mandatory arguments are detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( missing_mandatory)
{

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      int   secondArg = -1;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory();

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      appl::ArgString2Array  as2a( "-f", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv),
                           invalid_argument);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      int   secondArg = -1;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory();

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      appl::ArgString2Array  as2a( "-s 5", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 5);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      int   secondArg = -1;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory();

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      appl::ArgString2Array  as2a( "-f -s 17", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 17);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
      prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
      bool  firstFlag = false;
      int   secondArg = -1;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory();

      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

      appl::ArgString2Array  as2a( "-fs 55", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 55);

      // singleton prog_args::Groups: have to clean up
      prog_args::Groups::instance().removeArgHandler( "first");
      prog_args::Groups::instance().removeArgHandler( "second");
   } // end scope

} // end missing_mandatory



class TestControlArgs
{
public:
   TestControlArgs():
      mOpen( 0),
      mClose( 0),
      mNot( 0)
   {
   } // end TestControlArgs::TestControlArgs

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

   prog_args::Groups::SharedArgHndl  firstAH( new prog_args::Handler( 0));
   prog_args::Groups::SharedArgHndl  secondAH( new prog_args::Handler( 0));
   bool             firstFlag = false;
   bool             secondFlag = false;
   TestControlArgs  tca;


   firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
   secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( '(', boost::bind( &TestControlArgs::open, &tca)));
   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( ')', boost::bind( &TestControlArgs::close, &tca)));
   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( '!', boost::bind( &TestControlArgs::exclamation, &tca)));
   BOOST_REQUIRE_THROW(    secondAH->addControlHandler( '#', boost::bind( &TestControlArgs::open, &tca)),
                           runtime_error);

   BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "first",  firstAH));
   BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "second", secondAH));

   appl::ArgString2Array  as2a( "-f ( ! -s )", nullptr);

   BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
   BOOST_REQUIRE( firstFlag);
   BOOST_REQUIRE( secondFlag);
   BOOST_REQUIRE_EQUAL( tca.getOpen(), 1);
   BOOST_REQUIRE_EQUAL( tca.getClose(), 1);
   BOOST_REQUIRE_EQUAL( tca.getExclamation(), 1);

} // end control_characters



/// Test if an argument exists.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( argument_exists)
{

   prog_args::Groups::SharedArgHndl firstAH( new prog_args::Handler( 0));
   bool firstFlag = false;


   firstAH->addArgument( "e", DEST_VAR( firstFlag), "exists");
   BOOST_REQUIRE_NO_THROW( prog_args::Groups::instance().addArgHandler( "exists_test",  firstAH));
   BOOST_REQUIRE( prog_args::Groups::instance().argumentExists('f'));
   BOOST_REQUIRE( !prog_args::Groups::instance().argumentExists('c'));

} // end argument_exists



/// Test if addArgHandler throws exception when nullptr is passed.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( add_arg_handler_nullptr)
{

   prog_args::Groups::SharedArgHndl  argGroup;


   BOOST_REQUIRE_THROW( prog_args::Groups::instance().addArgHandler( "nullptr", argGroup), std::exception);

} // end add_arg_handler_nullptr



// =====================  END OF test_argument_groups.cpp  =====================
