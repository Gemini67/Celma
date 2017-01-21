
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


// module to test header file include
#include "celma/prog_args/groups.hpp"


// STL includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentGroupsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::ArgString2Array;
using celma::prog_args::Groups;
using celma::prog_args::Handler;
using std::invalid_argument;
using std::runtime_error;



/// Check that it does not crash when no argument handlers are defined yet.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( no_argument_handlers)
{

   BOOST_REQUIRE_THROW( Groups::instance().evalArguments( 1, nullptr),
                        runtime_error);
   BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( "v,verbose"));

} // end no_argument_handlers



/// Check that the same symbolic name cannot be used twice.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_name)
{

   Groups::SharedArgHndl  firstAH( new Handler( 0));
   Groups::SharedArgHndl  secondAH( new Handler( 0));


   BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
   BOOST_REQUIRE_THROW(    Groups::instance().addArgHandler( "first", secondAH),
                           runtime_error);

   {
      Groups::SharedArgHndl  unknownAH( Groups::instance().getHandler( "no-such-handler"));
      BOOST_REQUIRE( unknownAH.get() == nullptr);
   } // end scope

   {
      Groups::SharedArgHndl  findFirstAH( Groups::instance().getHandler( "first"));
      BOOST_REQUIRE( findFirstAH.get() != nullptr);
   } // end scope

   // singleton Groups: have to clean up
   Groups::instance().removeArgHandler( "first");

} // end duplicate_name



/// Check that a standard argument used by two Handler objects is
/// detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_standard_arg)
{

   {
      Groups::SharedArgHndl  firstAH( new Handler( Handler::hfHelpShort));
      Groups::SharedArgHndl  secondAH( new Handler( Handler::hfHelpShort));

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( Handler::hfHelpLong));
      Groups::SharedArgHndl  secondAH( new Handler( Handler::hfHelpLong));

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
   } // end scope


   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      std::string            firstFree;
      std::string            secondFree;

      firstAH->addArgument( DEST_VAR( firstFree), "first free argument");
      secondAH->addArgument( DEST_VAR( secondFree), "second free argument");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
   } // end scope

} // end duplicate_standard_arg



/// Check that duplicate application arguments are detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( duplicate_application_arg)
{

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   quiet;

      firstAH->addArgument(  "q", DEST_VAR( quiet), "be quiet");
      secondAH->addArgument( "q", DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool  quiet;

      firstAH->addArgument(  "quiet", DEST_VAR( quiet), "be quiet");
      secondAH->addArgument( "quiet", DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   quiet;

      firstAH->addArgument(  "q,quiet", DEST_VAR( quiet), "be quiet");
      secondAH->addArgument( "quiet",   DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
   } // end scope

} // end duplicate_application_arg



/// Check that one Handler using the standard argument, and another
/// using the same argument character/string as application argument, is
/// detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( mix_std_appl_args)
{

   // first standard argument, second application argument
   {
      Groups::SharedArgHndl  firstAH( new Handler( Handler::hfHelpShort));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   quiet;

      secondAH->addArgument( "h", DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
   } // end scope

   // first application argument, second standard argument
   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( Handler::hfHelpShort));
      bool                   quiet;

      firstAH->addArgument( "h", DEST_VAR( quiet), "be quiet");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first", firstAH));
      BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "second", secondAH),
                           runtime_error);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
   } // end scope

} // end mix_std_appl_args



/// Normal procedure: Two different arguments in two different argument handlers,
/// check handling.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( handle_arguments)
{

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      bool                   secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      // first check that it does not crash, then check if the arguments are
      // really found
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( 'f'));
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( 's'));
      BOOST_REQUIRE( Groups::instance().argumentExists( 'f'));
      BOOST_REQUIRE( Groups::instance().argumentExists( 's'));

      ArgString2Array  as2a( "-f", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( !secondFlag);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      bool                   secondFlag = false;


      firstAH->addArgument(  "first", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "second", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      // first check that it does not crash, then check if the arguments are
      // really found
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( "first"));
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( "second"));
      BOOST_REQUIRE( Groups::instance().argumentExists( "first"));
      BOOST_REQUIRE( Groups::instance().argumentExists( "second"));

      ArgString2Array  as2a( "--second", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      bool                   secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      ArgString2Array  as2a( "-f -s", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      bool                   secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      ArgString2Array  as2a( "-sf", nullptr);

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE( secondFlag);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      bool                   secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      ArgString2Array  as2a( "-a", nullptr);

      BOOST_REQUIRE_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      bool                   secondFlag = false;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      ArgString2Array  as2a( "--long_argument", nullptr);

      BOOST_REQUIRE_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

} // end handle_arguments



/// Check that missing mandatory arguments are detected.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( missing_mandatory)
{

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false; 
      int                    secondArg = -1;    


      firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory();

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      ArgString2Array  as2a( "-f", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv),
                           invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      int                    secondArg = -1;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory();

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      ArgString2Array  as2a( "-s 5", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( !firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 5);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      int                    secondArg = -1;


      firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory();

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      ArgString2Array  as2a( "-f -s 17", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 17);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
   } // end scope

   {
      Groups::SharedArgHndl  firstAH( new Handler( 0));
      Groups::SharedArgHndl  secondAH( new Handler( 0));
      bool                   firstFlag = false;
      int                    secondArg = -1;

      firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag");
      secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory();

      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
      BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

      ArgString2Array  as2a( "-fs 55", nullptr);

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 55);

      // singleton Groups: have to clean up
      Groups::instance().removeArgHandler( "first");
      Groups::instance().removeArgHandler( "second");
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

   Groups::SharedArgHndl  firstAH( new Handler( 0));
   Groups::SharedArgHndl  secondAH( new Handler( 0));
   bool                   firstFlag = false;
   bool                   secondFlag = false;
   TestControlArgs        tca;


   firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag");
   secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag");

   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( '(', std::bind( &TestControlArgs::open, &tca)));
   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( ')', std::bind( &TestControlArgs::close, &tca)));
   BOOST_REQUIRE_NO_THROW( secondAH->addControlHandler( '!', std::bind( &TestControlArgs::exclamation, &tca)));
   BOOST_REQUIRE_THROW(    secondAH->addControlHandler( '#', std::bind( &TestControlArgs::open, &tca)),
                           runtime_error);

   BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "first",  firstAH));
   BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "second", secondAH));

   ArgString2Array  as2a( "-f ( ! -s )", nullptr);

   BOOST_REQUIRE_NO_THROW( Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv));
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

   Groups::SharedArgHndl  firstAH( new Handler( 0));
   bool                   firstFlag = false;


   firstAH->addArgument( "e", DEST_VAR( firstFlag), "exists");
   BOOST_REQUIRE_NO_THROW( Groups::instance().addArgHandler( "exists_test",  firstAH));
   BOOST_REQUIRE( Groups::instance().argumentExists('f'));
   BOOST_REQUIRE( !Groups::instance().argumentExists('c'));

} // end argument_exists



/// Test if addArgHandler throws exception when nullptr is passed.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( add_arg_handler_nullptr)
{

   Groups::SharedArgHndl  argGroup;


   BOOST_REQUIRE_THROW( Groups::instance().addArgHandler( "nullptr", argGroup), std::exception);

} // end add_arg_handler_nullptr



// =====================  END OF test_argument_groups.cpp  =====================
