
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module UseOnce using the Boost.Test module.
**
--*/


// module to test header file includes
#include "celma/common/use_once.hpp"


// C++ Standard Library includes
#include <string>


// Boost includes
#define BOOST_TEST_MODULE UseOnceTest
#include <boost/test/unit_test.hpp>


using celma::common::UseOnce;


BOOST_TEST_DONT_PRINT_LOG_VALUE( nullptr_t)



/// Test with an integer value.
/// @since  x.y.z, 09.08.2017
BOOST_AUTO_TEST_CASE( value_int)
{
   
   {
      UseOnce< int>  no_value;

      BOOST_REQUIRE_EQUAL( no_value.release(), 0);
   } // end scope

   {
      UseOnce< int>  set_value;

      BOOST_REQUIRE_EQUAL( set_value.release(), 0);

      // now set a value
      set_value.set( 46);

      BOOST_REQUIRE_EQUAL( set_value.release(), 46);
      BOOST_REQUIRE_EQUAL( set_value.release(), 0);
   } // end scope

   {
      UseOnce< int>  set_value( 55);

      BOOST_REQUIRE_EQUAL( set_value.release(), 55);
      BOOST_REQUIRE_EQUAL( set_value.release(), 0);

      // now set a value
      set_value.set( 46);

      BOOST_REQUIRE_EQUAL( set_value.release(), 46);
      BOOST_REQUIRE_EQUAL( set_value.release(), 0);
   } // end scope

} // value_int



/// Test with a pointer.
/// @since  x.y.z, 09.08.2017
BOOST_AUTO_TEST_CASE( value_ptr)
{

   std::string  string_object( "init");

  
   {
      UseOnce< std::string*, nullptr>  no_value;

      BOOST_REQUIRE_EQUAL( no_value.release(), nullptr);
   } // end scope

   {
      UseOnce< std::string*, nullptr>  set_value;

      BOOST_REQUIRE_EQUAL( set_value.release(), nullptr);

      // now set a value
      set_value.set( &string_object);

      BOOST_REQUIRE_EQUAL( set_value.release(), &string_object);
      BOOST_REQUIRE_EQUAL( set_value.release(), nullptr);
   } // end scope

   {
      UseOnce< std::string*, nullptr>  set_value( &string_object);

      BOOST_REQUIRE_EQUAL( set_value.release(), &string_object);
      BOOST_REQUIRE_EQUAL( set_value.release(), nullptr);

      // now set a value
      std::string  second_str_obj( "other");
      set_value.set( &second_str_obj);

      BOOST_REQUIRE_EQUAL( set_value.release(), &second_str_obj);
      BOOST_REQUIRE_EQUAL( set_value.release(), nullptr);
   } // end scope

} // value_ptr



// ========================  END OF test_use_once.cpp  ========================

