
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template function celma::test::measure.


#pragma once


#include <sched.h>
#include <iomanip>
#include <iostream>
#include "celma/common/micro_timer.hpp"


namespace celma::test {


/// Standard function for performance tests.
/// @tparam  F  The type of the function to execute in the test loop.
/// @param[in]  num_loops  Number of times to perform the test loop.
/// @param[in]  func_name  The name of the function to display in the result
///                        output.
/// @param[in]  fun        The function to execute.
/// @return  The time measured for this function.
/// @since  0.13.5, 28.02.2017
template< typename F> [[nodiscard]]
   uint64_t measure( const uint64_t num_loops, const char* func_name, F fun)
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


} // namespace celma::test


// =====  END OF measure.hpp  =====

