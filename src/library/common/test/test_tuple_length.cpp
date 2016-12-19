
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template function tuple_length using the Boost.Test
**    module.
**
--*/


// Boost includes
#define BOOST_TEST_MODULE TupleLengthBase
#include <boost/test/unit_test.hpp>
#include <utility>


// project includes
#include "celma/common/tuple_length.hpp"


using celma::common::tuple_length;


/// Verifies that the length i.e. number of elements of a tuple is returned
/// correctly.
/// @since  0.5, 27.09.2016
BOOST_AUTO_TEST_CASE( length)
{

   {
      std::tuple< int>  tup;
      BOOST_REQUIRE_EQUAL( tuple_length( tup), 1);
   } // end scope


   {
      std::tuple< int, std::string>  tup;
      BOOST_REQUIRE_EQUAL( tuple_length( tup), 2);
   } // end scope

   {
      std::tuple< int, int, std::string>  tup;
      BOOST_REQUIRE_EQUAL( tuple_length( tup), 3);
   } // end scope

} // end length



// ======================  END OF test_tuple_length.cpp  ======================

