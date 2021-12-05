
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module Groups using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/prog_args/groups.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE ArgumentGroupsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/destination.hpp"
#include "celma/prog_args/eval_argument_string.hpp"
#include "celma/prog_args/i_usage_text.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::prog_args::evalArgumentString;
using celma::prog_args::Groups;
using celma::prog_args::Handler;


namespace {


UsageText( preUsage, beforeArgs,
   "Very interesting and meaningful text that will be printed before the list of\n"
   "arguments."
);


UsageText( postUsage, afterArgs,
   "And now this even more interesting and meaningful text that will be printed\n"
   "after the list of arguments."
);


class GroupsCleanupFixture
{
public:
   /// 
   /// @return
   ///    .
   /// @since
   ///    1.33.0, 08.11.2019
   GroupsCleanupFixture()
   {
      // remove the argument handlers from the group
      Groups::instance().removeAllArgHandler();
      // remove the group object so we can set (new) parameters on the group
      Groups::reset();
   } // GroupsCleanupFixture::GroupsCleanupFixture

   ~GroupsCleanupFixture()
   {
      // remove the argument handlers from the group
      Groups::instance().removeAllArgHandler();
      // remove the group object so we can set (new) parameters on the group
      Groups::reset();
   } // GroupsCleanupFixture::~GroupsCleanupFixture

}; // GroupsCleanupFixture


} // namespace



/// Check that it does not crash when no argument handlers are defined yet.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( no_argument_handlers)
{

   BOOST_REQUIRE_THROW( evalArgumentString( ""), std::runtime_error);
   BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( "v,verbose"));

} // no_argument_handlers



/// Should not crash if the name is empty.
///
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( no_name)
{

   BOOST_REQUIRE_THROW( Groups::instance().getArgHandler( ""),
      std::runtime_error);
   BOOST_REQUIRE_THROW( Groups::instance().getArgValueHandler( ""),
      std::runtime_error);

} // no_name



/// Add an argument handler, remove it and add it again.
/// Verify that a new argument handler was created. This cannot be done by
/// comparing the object handler pointers, because it may happen that the new
/// object is created at exactly the same address.
///
/// @since  1.32.0, 29.10.2019
BOOST_FIXTURE_TEST_CASE( remove_arg_handler, GroupsCleanupFixture)
{

   {
      Groups::SharedArgHndl  firstAH;

      BOOST_REQUIRE_NO_THROW( firstAH = Groups::instance().getArgHandler( "first"));
      BOOST_REQUIRE( firstAH.get() != nullptr);

      BOOST_REQUIRE_THROW( Groups::instance().getArgValueHandler( "first"),
         std::runtime_error);

      bool  dummy;
      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "d", DEST_VAR( dummy), "dummy"));
   } // end if

   Groups::instance().removeArgHandler( "first");

   Groups::SharedArgHndl  secondAH;

   BOOST_REQUIRE_NO_THROW( secondAH = Groups::instance().getArgHandler( "first"));
   BOOST_REQUIRE( secondAH.get() != nullptr);

   // try to add the same argument again
   // would fail if we would have got the same object as first
   bool  dummy;
   BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "d", DEST_VAR( dummy), "dummy"));

} // remove_arg_handler



/// Check that the same symbolic name cannot be used twice.
///
/// @since  0.2, 10.04.2016
BOOST_FIXTURE_TEST_CASE( duplicate_name, GroupsCleanupFixture)
{

   Groups::SharedArgHndl  firstAH;


   BOOST_REQUIRE_NO_THROW( firstAH = Groups::instance().getArgHandler( "first"));
   BOOST_REQUIRE( firstAH.get() != nullptr);

   Groups::SharedArgHndl  secondAH;

   BOOST_REQUIRE_NO_THROW( secondAH = Groups::instance().getArgHandler( "first"));
   BOOST_REQUIRE( secondAH.get() != nullptr);
   BOOST_REQUIRE_EQUAL( firstAH, secondAH);

} // duplicate_name



/// Check that a standard argument used by two Handler objects is
/// detected.
///
/// @since  0.2, 10.04.2016
BOOST_FIXTURE_TEST_CASE( duplicate_standard_arg, GroupsCleanupFixture)
{

   {
      auto                   firstAH = Groups::instance().getArgHandler( "first",
                                                                         Handler::hfHelpShort);
      Groups::SharedArgHndl  secondAH;

      BOOST_REQUIRE_THROW( secondAH = Groups::instance().getArgHandler( "second",
                                                                        Handler::hfHelpShort),
                           std::invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto                   firstAH = Groups::instance().getArgHandler( "first",
                                                                         Handler::hfHelpLong);
      Groups::SharedArgHndl  secondAH;

      BOOST_REQUIRE_THROW( secondAH = Groups::instance().getArgHandler( "second",
                                                                        Handler::hfHelpLong),
                           std::invalid_argument);

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
         "second free argument"), std::invalid_argument);
   } // end scope

} // duplicate_standard_arg



/// Check that duplicate application arguments are detected.
///
/// @since  0.2, 10.04.2016
BOOST_FIXTURE_TEST_CASE( duplicate_application_arg, GroupsCleanupFixture)
{

   {
      auto  firstAH = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  quiet;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "q", DEST_VAR( quiet), "be quiet"));
      BOOST_REQUIRE_THROW( secondAH->addArgument( "q", DEST_VAR( quiet), "be quiet"),
         std::invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  quiet;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "quiet", DEST_VAR( quiet), "be quiet"));
      BOOST_REQUIRE_THROW( secondAH->addArgument( "quiet", DEST_VAR( quiet), "be quiet"),
         std::invalid_argument);

      // singleton Groups: have to clean up
      Groups::instance().removeAllArgHandler();
   } // end scope

   {
      auto  firstAH = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  quiet;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "q,quiet", DEST_VAR( quiet), "be quiet"));
      BOOST_REQUIRE_THROW( secondAH->addArgument( "quiet",   DEST_VAR( quiet), "be quiet"),
         std::invalid_argument);
   } // end scope

} // duplicate_application_arg



/// Check that one Handler using the standard argument, and another
/// using the same argument character/string as application argument, is
/// detected.
///
/// @since  0.2, 10.04.2016
BOOST_FIXTURE_TEST_CASE( mix_std_appl_args, GroupsCleanupFixture)
{

   // first standard argument, second application argument
   {
      auto  firstAH  = Groups::instance().getArgHandler( "first", Handler::hfHelpShort);
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  quiet;


      BOOST_REQUIRE_THROW( secondAH->addArgument( "h", DEST_VAR( quiet), "be quiet"),
         std::invalid_argument);

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
         Handler::hfHelpShort), std::invalid_argument);
   } // end scope

} // mix_std_appl_args



/// Normal procedure: Two different arguments in two different argument handlers,
/// check handling.
///
/// @since  0.2, 10.04.2016
BOOST_FIXTURE_TEST_CASE( handle_arguments, GroupsCleanupFixture)
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

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( ""));
      BOOST_REQUIRE( !firstFlag);
      BOOST_REQUIRE( !secondFlag);

      std::ostringstream  oss;
      Groups::instance().printSummary( celma::prog_args::sumoptset_t(), oss);

      BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
         "Argument summary:\n"
         "   No arguments used/values set.\n"));

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

      // first check that it does not crash, then check if the arguments are
      // really found
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( 'f'));
      BOOST_REQUIRE_NO_THROW( Groups::instance().argumentExists( 's'));
      BOOST_REQUIRE( Groups::instance().argumentExists( 'f'));
      BOOST_REQUIRE( Groups::instance().argumentExists( 's'));

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-f"));
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

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( "--second"));
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

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-f -s"));
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

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-sf"));
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
      BOOST_REQUIRE_THROW( evalArgumentString( "-a"), std::runtime_error);

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

      firstFlag  = false;
      secondFlag = false;
      BOOST_REQUIRE_THROW( evalArgumentString( "hello"), std::runtime_error);

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
      BOOST_REQUIRE_THROW( evalArgumentString( "--long_argument"),
         std::runtime_error);
   } // end scope

} // handle_arguments



/// Test printing the usage with pre- and/or post-argument texts.
///
/// @since  1.33.0, 07.11.2019
BOOST_FIXTURE_TEST_CASE( usage, GroupsCleanupFixture)
{

   // usage without any pre- or post argument list texts
   {
      std::ostringstream  oss_std;
      std::ostringstream  oss_err;
      auto                firstAH  = Groups::instance( oss_std, oss_err,
         Handler::hfUsageCont).getArgHandler( "first", Handler::AllHelp);
      auto                secondAH = Groups::instance().getArgHandler( "second");
      bool                firstFlag = false;
      int                 firstValue;
      bool                secondFlag = false;
      int                 secondValue;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "f", DEST_VAR( firstFlag),
         "first flag"));
      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "v", DEST_VAR( firstValue),
         "first value")->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag),
         "second flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "w", DEST_VAR( secondValue),
         "second value")->setIsMandatory());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-h"));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( !oss_std.str().empty());

      // std::cerr << oss_std.str();
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Usage:\n"
         "\n"
         "first\n"
         "Mandatory:\n"
         "   -v           first value\n"
         "\n"
         "Optional:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -f           first flag\n"
         "\n"
         "\n"
         "second\n"
         "Mandatory:\n"
         "   -w   second value\n"
         "\n"
         "Optional:\n"
         "   -s   second flag\n"
         "\n"
         "\n"));

      // singleton Groups: have to clean up
      Groups::reset();
   } // end scope

   // usage with a pre-argument list text
   {
      std::ostringstream  oss_std;
      std::ostringstream  oss_err;
      auto                firstAH  = Groups::instance( oss_std, oss_err,
         Handler::hfUsageCont).getArgHandler( "first", Handler::AllHelp,
         preUsage.get());
      auto                secondAH = Groups::instance().getArgHandler( "second");
      bool                firstFlag = false;
      int                 firstValue;
      bool                secondFlag = false;
      int                 secondValue;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "f", DEST_VAR( firstFlag),
         "first flag"));
      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "v", DEST_VAR( firstValue),
         "first value")->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag),
         "second flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "w", DEST_VAR( secondValue),
         "second value")->setIsMandatory());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-h"));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( !oss_std.str().empty());

      // std::cerr << oss_std.str();
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Very interesting and meaningful text that will be printed before the list of\n"
         "arguments.\n"
         "\n"
         "Usage:\n"
         "\n"
         "first\n"
         "Mandatory:\n"
         "   -v           first value\n"
         "\n"
         "Optional:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -f           first flag\n"
         "\n"
         "\n"
         "second\n"
         "Mandatory:\n"
         "   -w   second value\n"
         "\n"
         "Optional:\n"
         "   -s   second flag\n"
         "\n"
         "\n"));

      // singleton Groups: have to clean up
      Groups::reset();
   } // end scope

   // usage with a post-argument list text
   {
      std::ostringstream  oss_std;
      std::ostringstream  oss_err;
      auto                firstAH  = Groups::instance( oss_std, oss_err,
         Handler::hfUsageCont).getArgHandler( "first", Handler::AllHelp,
         postUsage.get());
      auto                secondAH = Groups::instance().getArgHandler( "second");
      bool                firstFlag = false;
      int                 firstValue;
      bool                secondFlag = false;
      int                 secondValue;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "f", DEST_VAR( firstFlag),
         "first flag"));
      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "v", DEST_VAR( firstValue),
         "first value")->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag),
         "second flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "w", DEST_VAR( secondValue),
         "second value")->setIsMandatory());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-h"));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( !oss_std.str().empty());

      // std::cerr << oss_std.str();
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Usage:\n"
         "\n"
         "first\n"
         "Mandatory:\n"
         "   -v           first value\n"
         "\n"
         "Optional:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -f           first flag\n"
         "\n"
         "\n"
         "second\n"
         "Mandatory:\n"
         "   -w   second value\n"
         "\n"
         "Optional:\n"
         "   -s   second flag\n"
         "\n"
         "\n"
         "And now this even more interesting and meaningful text that will be printed\n"
         "after the list of arguments.\n"
         "\n"));

      // singleton Groups: have to clean up
      Groups::reset();
   } // end scope

   // and finally a usage with a pre- and post-argument list text
   {
      std::ostringstream  oss_std;
      std::ostringstream  oss_err;
      auto                firstAH  = Groups::instance( oss_std, oss_err,
         Handler::hfUsageCont).getArgHandler( "first", Handler::AllHelp,
         preUsage.get(), postUsage.get());
      auto                secondAH = Groups::instance().getArgHandler( "second");
      bool                firstFlag = false;
      int                 firstValue;
      bool                secondFlag = false;
      int                 secondValue;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "f", DEST_VAR( firstFlag),
         "first flag"));
      BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "v", DEST_VAR( firstValue),
         "first value")->setIsMandatory());
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag),
         "second flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "w", DEST_VAR( secondValue),
         "second value")->setIsMandatory());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-h"));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( !oss_std.str().empty());

      // std::cerr << oss_std.str();
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_std.str(),
         "Very interesting and meaningful text that will be printed before the list of\n"
         "arguments.\n"
         "\n"
         "Usage:\n"
         "\n"
         "first\n"
         "Mandatory:\n"
         "   -v           first value\n"
         "\n"
         "Optional:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "   -f           first flag\n"
         "\n"
         "\n"
         "second\n"
         "Mandatory:\n"
         "   -w   second value\n"
         "\n"
         "Optional:\n"
         "   -s   second flag\n"
         "\n"
         "\n"
         "And now this even more interesting and meaningful text that will be printed\n"
         "after the list of arguments.\n"
         "\n"));

      // singleton Groups: have to clean up
      Groups::reset();
   } // end scope

} // usage


/// Check that missing mandatory arguments are detected.
///
/// @since  0.2, 10.04.2016
BOOST_FIXTURE_TEST_CASE( missing_mandatory, GroupsCleanupFixture)
{

   {
      auto  firstAH  = Groups::instance().getArgHandler( "first");
      auto  secondAH = Groups::instance().getArgHandler( "second");
      bool  firstFlag = false;
      int   secondArg = -1;

      BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag), "first flag"));
      BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondArg), "second arg")->setIsMandatory());

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_THROW( evalArgumentString( "-f"), std::runtime_error);

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

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-s 5"));
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

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-f -s 17"));
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

      firstFlag = false;
      secondArg = -1;
      BOOST_REQUIRE_NO_THROW( evalArgumentString( "-fs 55"));
      BOOST_REQUIRE( firstFlag);
      BOOST_REQUIRE_EQUAL( secondArg, 55);
   } // end scope

} // missing_mandatory



/// Test the special features of the argument group: Pass parameters on to each
/// handler object.
///
/// @since  0.13.0, 05.02.2017
BOOST_FIXTURE_TEST_CASE( group_features, GroupsCleanupFixture)
{

   std::ostringstream  normal_out;
   std::ostringstream  error_out;

   Groups::instance( normal_out, error_out, Handler::hfVerboseArgs);

   auto  ah1 = Groups::instance().getArgHandler( "Handler 1");
   auto  ah2 = Groups::instance().getArgHandler( "Handler 2", Handler::AllHelp);
   bool  quiet = false;
   int   number = -1;

   ah1->addArgument( "q,quiet", DEST_VAR( quiet), "Be quiet");
   ah2->addArgument( "n,number", DEST_VAR( number), "Number")->setIsMandatory();

   BOOST_REQUIRE_NO_THROW( evalArgumentString( "-q -n 42"));

   BOOST_REQUIRE_EQUAL( normal_out.str(),
                        "quiet: is set\n"
                        "number: value '42' is assigned\n");
   BOOST_REQUIRE( error_out.str().empty());

} // group_features



/// Test listing the argument groups.
///
/// @since  0.13.1, 07.02.2017
BOOST_FIXTURE_TEST_CASE( list_groups, GroupsCleanupFixture)
{

   {
      Groups::reset();

      std::ostringstream  normal_out;
      std::ostringstream  error_out;

      Groups::instance( normal_out, error_out, Handler::hfListArgGroups);

      auto  ah1 = Groups::instance().getArgHandler( "Handler 1");
      auto  ah2 = Groups::instance().getArgHandler( "Handler 2", Handler::AllHelp);

      BOOST_REQUIRE_NO_THROW( evalArgumentString( "--list-arg-groups"));

      BOOST_REQUIRE_EQUAL( normal_out.str(),
                           "list of known argument groups:\n"
                           "- Handler 1\n"
                           "- Handler 2\n");
      BOOST_REQUIRE( error_out.str().empty());

      Groups::instance().removeAllArgHandler();
      Groups::reset();
   } // end scope

   {
      Groups::reset();

      std::ostringstream  normal_out;
      std::ostringstream  error_out;

      Groups::instance( normal_out, error_out);

      auto  ah1 = Groups::instance().getArgHandler( "Handler 1");
      auto  ah2 = Groups::instance().getArgHandler( "Handler 2", Handler::AllHelp);

      BOOST_REQUIRE_THROW( ah1->addArgumentListArgGroups( ""),
         std::invalid_argument);

      Groups::instance().removeAllArgHandler();
      Groups::reset();
   } // end scope

   {
      Groups::reset();

      std::ostringstream  normal_out;
      std::ostringstream  error_out;

      Groups::instance( normal_out, error_out);

      auto  ah1 = Groups::instance().getArgHandler( "Handler 1");
      auto  ah2 = Groups::instance().getArgHandler( "Handler 2", Handler::AllHelp);

      BOOST_REQUIRE_NO_THROW( ah1->addArgumentListArgGroups( "lag"));
      BOOST_REQUIRE_NO_THROW( evalArgumentString( "--lag"));

      BOOST_REQUIRE_EQUAL( normal_out.str(),
                           "list of known argument groups:\n"
                           "- Handler 1\n"
                           "- Handler 2\n");
      BOOST_REQUIRE( error_out.str().empty());
   } // end scope

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
///
/// @since  0.2, 10.04.2016
BOOST_FIXTURE_TEST_CASE( control_characters, GroupsCleanupFixture)
{

   auto             firstAH  = Groups::instance().getArgHandler( "first");
   auto             secondAH = Groups::instance().getArgHandler( "second");
   bool             firstFlag = false;
   bool             secondFlag = false;
   TestControlArgs  tca;


   BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag"));
   BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag"));

   BOOST_REQUIRE_NO_THROW( secondAH->addBracketHandler( 
      std::bind( &TestControlArgs::open, &tca),
      std::bind( &TestControlArgs::close, &tca)));

   BOOST_REQUIRE_NO_THROW( evalArgumentString( "-f ( ! -s )"));
   BOOST_REQUIRE( firstFlag);
   BOOST_REQUIRE( secondFlag);
   BOOST_REQUIRE_EQUAL( tca.getOpen(), 1);
   BOOST_REQUIRE_EQUAL( tca.getClose(), 1);

} // control_characters



/// Test that conflicting control characters handlers are detected.
///
/// @since  1.33.0, 06.11.2019
BOOST_FIXTURE_TEST_CASE( control_characters_conflict, GroupsCleanupFixture)
{

   auto             firstAH  = Groups::instance().getArgHandler( "first");
   auto             secondAH = Groups::instance().getArgHandler( "second");
   bool             firstFlag = false;
   bool             secondFlag = false;
   TestControlArgs  tca;


   BOOST_REQUIRE_NO_THROW( firstAH->addArgument(  "f", DEST_VAR( firstFlag),  "first flag"));
   BOOST_REQUIRE_NO_THROW( secondAH->addArgument( "s", DEST_VAR( secondFlag), "second flag"));

   BOOST_REQUIRE_NO_THROW( secondAH->addBracketHandler( 
      std::bind( &TestControlArgs::open, &tca),
      std::bind( &TestControlArgs::close, &tca)));

   BOOST_REQUIRE_THROW( firstAH->addBracketHandler( 
      std::bind( &TestControlArgs::open, &tca),
      std::bind( &TestControlArgs::close, &tca)), std::invalid_argument);

} // control_characters_conflict



/// Test if an argument exists.
///
/// @since  0.2, 10.04.2016
BOOST_FIXTURE_TEST_CASE( argument_exists, GroupsCleanupFixture)
{

   auto  firstAH  = Groups::instance().getArgHandler( "exists_test");
   bool  firstFlag = false;


   BOOST_REQUIRE_NO_THROW( firstAH->addArgument( "e", DEST_VAR( firstFlag), "exists"));
   BOOST_REQUIRE( Groups::instance().argumentExists( 'e'));
   BOOST_REQUIRE( !Groups::instance().argumentExists( 'c'));

} // argument_exists



// =====  END OF test_argument_groups_c.cpp  =====

