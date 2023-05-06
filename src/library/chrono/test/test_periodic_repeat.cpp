
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test headerfile include
#include "celma/chrono/periodic_repeat.hpp"


// OS/C lib includes
#include <ctime>


// C++ Standard Library includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE PeriodicRepeatTest
#include <boost/test/unit_test.hpp>


using celma::chrono::PeriodicRepeat;



/// Special function that allows to run the program as a normal unit test
/// program (without arguments), but also call it manually.
/// For this, the function evaluates program arguments that control the
/// behaviour:
/// - --period: Specifies the length of the period. Default value: 3 (seconds)
/// - --num-repeats: Number of times to check if the repetition is triggered at
///   the correct time. Default value: 3
/// - --adjust: Use this argument if the action should be triggered at times
///   that are a multiple of the period.
/// - --verbose: Activates the verbose output.
///
/// Test procedure:
/// Set up the periodic repeat object and also calculate the time(s) here in
/// this module, then check if the times when the execution is triggered match
/// the times calculated here.
/// @since  1.48.0, 04.05.2023
BOOST_AUTO_TEST_CASE( test_periods)
{

   auto const  argc = boost::unit_test::framework::master_test_suite().argc;

   int   period = 3;
   int   num_repeats = 3;
   bool  adjust = false;
   bool  verbose = false;

   for (int i = 1; i < argc; ++i)
   {
      if (std::strcmp( boost::unit_test::framework::master_test_suite().argv[ i], "--period") == 0)
      {
         period = std::stoi( boost::unit_test::framework::master_test_suite().argv[ ++i]);
      } else if (std::strcmp( boost::unit_test::framework::master_test_suite().argv[ i], "--num-repeats") == 0)
      {
         num_repeats = std::stoi( boost::unit_test::framework::master_test_suite().argv[ ++i]);
      } else if (std::strcmp( boost::unit_test::framework::master_test_suite().argv[ i], "--adjust") == 0)
      {
         adjust = true;
      } else if (std::strcmp( boost::unit_test::framework::master_test_suite().argv[ i], "--verbose") == 0)
      {
         verbose = true;
      } // end if
   } // end for

   auto  start = std::time( nullptr);
   int   repeated = 0;

   time_t  next = start + period;
   if (adjust)
      next -= (next % period);

   // ctime() adds a newline character to its output, so instead of using a
   // complicated formatting, simply print the timestamp at the end
   if (verbose)
   {
      auto const  now = std::time( nullptr);
      std::cout << "Starting test:   " << std::ctime( &now);
   } // end if

   // ---------- start ----------   
   PeriodicRepeat  pr( period, adjust);

   while (repeated < num_repeats)
   {
      if (pr)
      {
         if (verbose)
         {
            auto const  now = std::time( nullptr);
            std::cout << "Call " << (repeated + 1) << ", due now: " << std::ctime( &now);
         } // end if

         BOOST_REQUIRE_EQUAL( next, std::time( nullptr));
         next += period;
         ++repeated;
      } // end if

      ::usleep( 100'000);
   } // end for

   if (verbose)
   {
      auto const  now = std::time( nullptr);
      std::cout << "Test done:       " << std::ctime( &now);
   } // end if

   BOOST_REQUIRE_EQUAL( repeated, num_repeats);

} // test_periods



// =====  END OF test_periodic_repeat.cpp  =====

