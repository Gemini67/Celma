
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template function celma::test::measure.


#ifndef CELMA_TEST_MEASURE_HPP
#define CELMA_TEST_MEASURE_HPP


#include <sched.h>
#include <iostream>
#include <iomanip>
#include "celma/common/micro_timer.hpp"


namespace celma { namespace test {


/// Standard function for performance tests.
/// @tparam  F  The type of the function to execute in the test loop.
/// @param[in]  num_loops  Number of times to perform the test loop.
/// @param[in]  func_name  The name of the function to display in the result
///                        output.
/// @param[in]  fun        The function to execute.
/// @return  The time measured for this function.
/// @since  0.13.5, 28.02.2017
template< typename F> uint64_t measure( uint64_t num_loops,
                                        const char* func_name, F fun)
{

   common::MicroTimer  mt;


   ::sched_yield();

   mt.start();

   for (uint64_t i = 0; i < num_loops; ++i)
   {
      fun();
   } // end for

   mt.stop();

   std::cout << std::setw( 25) << std::left << func_name
             << " = " << mt.timed() << " [us]" << std::endl;

   return mt.timed();
} // measure


} // namespace test
} // namespace celma


#endif   // CELMA_TEST_MEASURE_HPP


// =====  END OF measure.hpp  =====

