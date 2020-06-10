
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
**    Test program for the template class celma::common::CheckAssign<>, using
**    the Boost.Test framework.
**
--*/


// module to test headerfile include
#include "celma/common/check_assign.hpp"


// C++ Standard Library includes
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE CheckAssignTest
#include <boost/test/unit_test.hpp>


using celma::common::CheckAssign;
using celma::common::CheckAssignRef;



/// Basic tests of the handling with a CheckAssignRef object.
///
/// @since  1.31.0, 16.10.2019
BOOST_AUTO_TEST_CASE( base_ref)
{

   int  x = -1;

   // try to access an unset value
   {
      int                   int_var;
      CheckAssignRef< int>  car( int_var);

      BOOST_REQUIRE( !car.hasValue());
      BOOST_REQUIRE_THROW( car.value(), std::runtime_error);
      BOOST_REQUIRE_THROW( x = static_cast< int>( car), std::runtime_error);
      BOOST_REQUIRE_THROW( x = car, std::runtime_error);
      BOOST_REQUIRE_EQUAL( x, -1); // silence!
   } // end scope

   // assign a value using the assign() method
   {
      int                   int_var;
      CheckAssignRef< int>  car( int_var);

      car.assign( 42);
      BOOST_REQUIRE( car.hasValue());
      BOOST_REQUIRE_NO_THROW( car.value());
      BOOST_REQUIRE_EQUAL( car.value(), 42);
      BOOST_REQUIRE_EQUAL( int_var, 42);
      BOOST_REQUIRE_NO_THROW( x = car);
      BOOST_REQUIRE_EQUAL( x, 42);
   } // end scope

   // assign a value using the assignment operator
   {
      int                   int_var;
      CheckAssignRef< int>  car( int_var);

      car = 42;
      x = -1;
      BOOST_REQUIRE( car.hasValue());
      BOOST_REQUIRE_NO_THROW( car.value());
      BOOST_REQUIRE_EQUAL( car.value(), 42);
      BOOST_REQUIRE_EQUAL( int_var, 42);
      BOOST_REQUIRE_NO_THROW( x = car);
      BOOST_REQUIRE_EQUAL( x, 42);
   } // end scope

} // base_ref



/// Basic tests of the handling of a CheckAssign object.
///
/// @since  1.31.0, 11.10.2019
BOOST_AUTO_TEST_CASE( base_value)
{

   int  x = -1;

   // try to access an unset value
   {
      CheckAssign< int>  ca;
      BOOST_REQUIRE( !ca.hasValue());
      BOOST_REQUIRE_THROW( ca.value(), std::runtime_error);
      BOOST_REQUIRE_THROW( x = static_cast< int>( ca), std::runtime_error);
      BOOST_REQUIRE_THROW( x = ca, std::runtime_error);
      BOOST_REQUIRE_EQUAL( x, -1); // silence!

      auto const  copy( ca);
      BOOST_REQUIRE( !copy.hasValue());
      BOOST_REQUIRE_THROW( copy.value(), std::runtime_error);
      BOOST_REQUIRE_THROW( x = static_cast< const int&>( ca), std::runtime_error);
      BOOST_REQUIRE_THROW( x = copy, std::runtime_error);
      BOOST_REQUIRE_EQUAL( x, -1); // silence!
   } // end scope

   // assign a value using the assign() method
   {
      CheckAssign< int>  ca;
      ca.assign( 42);
      BOOST_REQUIRE( ca.hasValue());
      BOOST_REQUIRE_NO_THROW( ca.value());
      BOOST_REQUIRE_EQUAL( ca.value(), 42);
      BOOST_REQUIRE_NO_THROW( x = ca);
      BOOST_REQUIRE_EQUAL( x, 42);

      CheckAssign< int>  ca2;
      ca2 = ca;
      x = -1;
      BOOST_REQUIRE( ca2.hasValue());
      BOOST_REQUIRE_NO_THROW( ca2.value());
      BOOST_REQUIRE_EQUAL( ca2.value(), 42);
      BOOST_REQUIRE_NO_THROW( x = ca2);
      BOOST_REQUIRE_EQUAL( x, 42);
   } // end scope

   // assign a value using the assignment operator
   {
      CheckAssign< int>  ca;
      ca = 42;
      x = -1;
      BOOST_REQUIRE( ca.hasValue());
      BOOST_REQUIRE_NO_THROW( ca.value());
      BOOST_REQUIRE_EQUAL( ca.value(), 42);
      BOOST_REQUIRE_NO_THROW( x = ca);
      BOOST_REQUIRE_EQUAL( x, 42);

      auto  copy( ca);
      x = -1;
      BOOST_REQUIRE( copy.hasValue());
      BOOST_REQUIRE_NO_THROW( copy.value());
      BOOST_REQUIRE_EQUAL( copy.value(), 42);
      BOOST_REQUIRE_NO_THROW( x = ca);
      BOOST_REQUIRE_EQUAL( x, 42);
   } // end scope

   // overwrite value that was set by assigning from an unset object
   {
      CheckAssign< int>  ca;
      ca = 42;

      CheckAssign< int>  ca2;
      ca = ca2;

      BOOST_REQUIRE( !ca.hasValue());
      BOOST_REQUIRE_THROW( ca.value(), std::runtime_error);
   } // end scope

} // base_value



// =====  END OF test_check_assign.cpp  =====

