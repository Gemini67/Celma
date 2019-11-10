
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for printing a usage with additional texts, using the
**    Boost.Test module.
**
--*/


// module to test header file include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <sstream>
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE ArghUsageTextsTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args/i_usage_text.hpp"
#include "celma/test/multiline_string_compare.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;


namespace {


UsageText( preUsage1, beforeArgs,
   "First pre-args usage text."
);


UsageText( preUsage2, beforeArgs,
   "Second pre-args usage text."
);


UsageText( postUsage1, afterArgs,
   "First after-args usage text."
);


UsageText( postUsage2, afterArgs,
   "Second after-args usage text."
);


} // namespace



/// Wrong setup of the usage texts should be detected.
///
/// @since  1.23.0, 04.04.2019
BOOST_AUTO_TEST_CASE( wrong_setup)
{

   BOOST_REQUIRE_THROW(
      Handler  ah( Handler::AllHelp | Handler::hfUsageCont,
         nullptr, preUsage1.get()), std::invalid_argument);

   BOOST_REQUIRE_THROW(
      Handler  ah( Handler::AllHelp | Handler::hfUsageCont,
         preUsage1.get(), preUsage2.get()), std::invalid_argument);

   BOOST_REQUIRE_THROW(
      Handler  ah( Handler::AllHelp | Handler::hfUsageCont,
         postUsage1.get(), postUsage2.get()), std::invalid_argument);

   BOOST_REQUIRE_THROW(
      Handler  ah( Handler::AllHelp | Handler::hfUsageCont,
         postUsage1.get(), preUsage1.get()), std::invalid_argument);

} // wrong_setup



/// Print the usage without, with one or with two usage texts.
///
/// @since  1.23.0, 04.04.2019
BOOST_AUTO_TEST_CASE( usage)
{

   // usage without any additional texts
   {
      std::ostringstream  oss_out;
      std::ostringstream  oss_err;
      Handler             ah( oss_out, oss_err,
         Handler::AllHelp | Handler::hfUsageCont);
      auto const          as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "\n"));
   } // end scope

   // usage with a pre-args text
   {
      std::ostringstream  oss_out;
      std::ostringstream  oss_err;
      Handler             ah( oss_out, oss_err,
         Handler::AllHelp | Handler::hfUsageCont, preUsage1.get());
      auto const          as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_out,
         "First pre-args usage text.\n"
         "\n"
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "\n"));
   } // end scope

   // usage with a post-args text
   {
      std::ostringstream  oss_out;
      std::ostringstream  oss_err;
      Handler             ah( oss_out, oss_err,
         Handler::AllHelp | Handler::hfUsageCont, postUsage1.get());
      auto const          as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_out,
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "\n"
         "First after-args usage text.\n"
         "\n"));
   } // end scope

   // usage with both a pre-args and a post-args text
   {
      std::ostringstream  oss_out;
      std::ostringstream  oss_err;
      Handler             ah( oss_out, oss_err,
         Handler::AllHelp | Handler::hfUsageCont, preUsage1.get(),
         postUsage1.get());
      auto const          as2a = make_arg_array( "-h", nullptr);

      BOOST_REQUIRE_NO_THROW( ah.evalArguments( as2a.mArgC, as2a.mpArgV));

      BOOST_REQUIRE( oss_err.str().empty());
      BOOST_REQUIRE( celma::test::multilineStringCompare( oss_out,
         "First pre-args usage text.\n"
         "\n"
         "Usage:\n"
         "Optional arguments:\n"
         "   -h,--help    Prints the program usage.\n"
         "   --help-arg   Prints the usage for the given argument.\n"
         "\n"
         "First after-args usage text.\n"
         "\n"));
   } // end scope

} // usage



// =====  END OF test_argh_usage_texts_c.cpp  =====
