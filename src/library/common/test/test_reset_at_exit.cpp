
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
**    Test program for the module ResetAtExit using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/common/reset_at_exit.hpp"


// Boost includes
#define BOOST_TEST_MODULE ResetAtExitTest
#include <boost/test/unit_test.hpp>



/// All tests for the class ResetAtExit.
/// @since  0.2, 09.04.2016
BOOST_AUTO_TEST_CASE( reset_at_exit)
{

   int  my_test_var = 42;


   {
      const celma::common::ResetAtExit< int>  rae( my_test_var, 4711);

      BOOST_REQUIRE_EQUAL( my_test_var, 42);
   } // end scope

   BOOST_REQUIRE_EQUAL( my_test_var, 4711);

} // reset_at_exit



// =====  END OF test_reset_at_exit.cpp  =====

