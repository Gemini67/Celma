
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
**    Test program for the template function tuple_length using the Boost.Test
**    module.
**
--*/


// module to test header file include
#include "celma/common/tuple_length.hpp"


// C++ Standard Library includes
#include <tuple>


// Boost includes
#define BOOST_TEST_MODULE TupleLengthBase
#include <boost/test/unit_test.hpp>


using celma::common::tuple_length;



/// Verifies that the length i.e. number of elements of a tuple is returned
/// correctly.
///
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

} // length



// =====  END OF test_tuple_length.cpp  =====

