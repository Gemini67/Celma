
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test headerfile include
#include "celma/appl/multi_process.hpp"


// Boost includes
#define BOOST_TEST_MODULE MultiProcessTest
#include <boost/test/unit_test.hpp>

#include <functional>
#include <iostream>


namespace {


int child_func( int child_num)
{
   std::cout << ::getpid() << ": child process number " << child_num << " started" << std::endl;
   ::sleep( 1);
   std::cout << ::getpid() << ": child process number " << child_num << " stopping" << std::endl;
   return 0;
}


}


/// Test 
///
/// @since  x.y.z, 17.03.2021
BOOST_AUTO_TEST_CASE( no_arguments)
{

   celma::appl::MultiProcess  mp;


   mp.forkChild( []()
   {
      std::cout << "child process started" << std::endl;
      ::sleep( 1);
      std::cout << "child process stopping" << std::endl;
      return 0;
   });

   while (mp.numChildren() > 0)
   {
      ::sleep( 1);
   } // end while

   mp.forkChild( std::bind( child_func, 2));

   while (mp.numChildren() > 0)
   {
      ::sleep( 1);
   } // end while

   mp.forkChild( std::bind( child_func, 3));
   mp.forkChild( std::bind( child_func, 4));
   mp.forkChild( std::bind( child_func, 5));
   mp.forkChild( std::bind( child_func, 6));

   while (mp.numChildren() > 0)
   {
      ::sleep( 1);
   } // end while


} // multiple_arguments



// =====  END OF test_arg_string_2_array.cpp  =====

