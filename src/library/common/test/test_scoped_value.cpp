
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
**    Test program for the module "scoped value", using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/common/scoped_value.hpp"


// Boost includes
#define BOOST_TEST_MODULE ScopedValueTest
#include <boost/test/unit_test.hpp>



/// Value should be set immediately and the old value restored afterwards.
///
/// @since  1.22.0, 02.04.2019
BOOST_AUTO_TEST_CASE( scoped_value)
{

   int  my_test_var = 42;


   {
      const celma::common::ScopedValue< int>  sv( my_test_var, 4711);

      BOOST_REQUIRE_EQUAL( my_test_var, 4711);
   } // end scope

   BOOST_REQUIRE_EQUAL( my_test_var, 42);

} // scoped_value



/// A specific bit should be set and restored to its previous value afterwards.
///
/// @since  1.22.0, 02.04.2019
BOOST_AUTO_TEST_CASE( scoped_flag)
{

   // set the flag and clear it again
   {
      int  my_test_var = 0x0a;   // 0000 1010

      {
         const celma::common::ScopedFlag< int>  sv( my_test_var, 0x04);

         BOOST_REQUIRE_EQUAL( my_test_var, 0x0e);
      } // end scope

      BOOST_REQUIRE_EQUAL( my_test_var, 0x0a);
   } // end scope

   // set the flag but it's already cleared
   {
      int  my_test_var = 0x0a;   // 0000 1010

      {
         const celma::common::ScopedFlag< int>  sv( my_test_var, 0x04);

         BOOST_REQUIRE_EQUAL( my_test_var, 0x0e);

         my_test_var = 0x0a;
      } // end scope

      BOOST_REQUIRE_EQUAL( my_test_var, 0x0a);
   } // end scope

   // fag is already set
   {
      int  my_test_var = 0x0e;   // 0000 1010

      {
         const celma::common::ScopedFlag< int>  sv( my_test_var, 0x04);

         BOOST_REQUIRE_EQUAL( my_test_var, 0x0e);
      } // end scope

      BOOST_REQUIRE_EQUAL( my_test_var, 0x0e);
   } // end scope

   // flag is already set but then cleared
   {
      int  my_test_var = 0x0e;   // 0000 1010

      {
         const celma::common::ScopedFlag< int>  sv( my_test_var, 0x04);

         BOOST_REQUIRE_EQUAL( my_test_var, 0x0e);
         my_test_var = 0x0a;
      } // end scope

      BOOST_REQUIRE_EQUAL( my_test_var, 0x0e);
   } // end scope

} // scoped_flag



// =====  END OF test_scoped_value.cpp  =====

