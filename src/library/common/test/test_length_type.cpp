
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module "length type", using the Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/common/length_type.hpp"


// Boost includes
#define BOOST_TEST_MODULE LengthTypeTest
#include <boost/test/unit_test.hpp>


using celma::common::LengthType;



/// Test the sizes of the types.
/// @since  1.45.0, 23.01.2021
BOOST_AUTO_TEST_CASE( type_by_size)
{

   {
      typename LengthType< 255>::type  my_var;

      BOOST_REQUIRE_EQUAL( sizeof( my_var), 1);
   } // end scope

   {
      typename LengthType< 256>::type  my_var;

      BOOST_REQUIRE_EQUAL( sizeof( my_var), 2);
   } // end scope

   {
      typename LengthType< 65535>::type  my_var;

      BOOST_REQUIRE_EQUAL( sizeof( my_var), 2);
   } // end scope

   {
      typename LengthType< 65536>::type  my_var;

      BOOST_REQUIRE_EQUAL( sizeof( my_var), 4);
   } // end scope

   {
      typename LengthType< 4'294'967'295>::type  my_var;

      BOOST_REQUIRE_EQUAL( sizeof( my_var), 4);
   } // end scope

   {
      typename LengthType< 4'294'967'296>::type  my_var;

      BOOST_REQUIRE_EQUAL( sizeof( my_var), 8);
   } // end scope

} // type_by_size



// =====  END OF test_length_type.cpp  =====

