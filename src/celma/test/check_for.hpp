
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Defines to enable additional test with for loops in a Boost.Test module.
**
--*/


/// @file
/// See documentation of the macros CHECK_FOR and CHECK_FOR_COUNT.<br>
/// This file does not include the necessary Boost.Test include files, since
/// the "test module" must be defined first.<br>
/// So, define the test module, include the Boost.Test include file(s), and then
/// include this file.


#ifndef CELMA_TEST_CHECK_FOR_HPP
#define CELMA_TEST_CHECK_FOR_HPP


/// Use this macro to define a for loop where the number of times that the loop
/// block is executed is counted.
/// You don't need to use curly braces afterwards, it works correctly with or
/// without them.<br>
/// After the loop block, use one of the other 3 macros to check if the number
/// of times that the loop block was entered matches the expected value.
///
/// @param  c  The clause for the for loop.
/// @since  x.y.z, 21.06.2020
#define CHECK_FOR( c) \
   { \
      size_t  counter = 0; \
      for ( c) \
      { \
         ++counter;


/// Checks that the loop block was executed exactly the given number of times.
///
/// @param  n  The expected number of times that the loop block was executed.
/// @since  x.y.z, 21.06.2020
#define  CHECK_FOR_COUNT( n) \
      } \
      BOOST_REQUIRE_EQUAL( counter, n); \
   }


/// Special case: Checks that the loop block was never executed.
///
/// @since  x.y.z, 21.06.2020
#define  CHECK_FOR_NEVER  CHECK_FOR_COUNT( 0)

/// Special case: Checks that the loop block was executed exactly once.
///
/// @since  x.y.z, 21.06.2020
#define  CHECK_FOR_ONCE   CHECK_FOR_COUNT( 1)


#endif   // CELMA_TEST_CHECK_FOR_HPP


// =====  END OF check_for.hpp  =====

