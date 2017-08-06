
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
**    Test program for the class Storage using the Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/prog_args/detail/storage.hpp"


// C++ Standard Library includes
#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE StorageTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/detail/typed_arg_base.hpp"


using celma::prog_args::detail::Storage;
using celma::prog_args::detail::TypedArgBase;
using std::invalid_argument;
using std::runtime_error;


BOOST_TEST_DONT_PRINT_LOG_VALUE( Storage< int>::const_iterator)



/// Verify that all possible errors are detected.
/// @since  x.y.z, 22.06.2017
BOOST_AUTO_TEST_CASE( test_errors)
{

   // empty string
   {
      Storage< int>  s;
      BOOST_REQUIRE_THROW( s.addArgument( 0, ""), invalid_argument);
   } // end scope

} // test_errors



/// Verify that adding entries works correctly.
/// @since  x.y.z, 03.07.2017
BOOST_AUTO_TEST_CASE( test_simple_add)
{

   // one entry
   {
      Storage< int>  s;

      BOOST_REQUIRE( s.empty());
      BOOST_REQUIRE_EQUAL( s.size(), 0);
      BOOST_REQUIRE_EQUAL( s.begin(), s.end());

      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n"));

      BOOST_REQUIRE( !s.empty());
      BOOST_REQUIRE_EQUAL( s.size(), 1);
      BOOST_REQUIRE( s.begin() != s.end());

      auto  it = s.begin();
      BOOST_REQUIRE( it != s.end());
      ++it;
      BOOST_REQUIRE_EQUAL( it, s.end());
   } // end scope

   // two entries
   {
      Storage< int>  s;

      BOOST_REQUIRE( s.empty());
      BOOST_REQUIRE_EQUAL( s.size(), 0);
      BOOST_REQUIRE_EQUAL( s.begin(), s.end());

      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n"));
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "name"));

      BOOST_REQUIRE( !s.empty());
      BOOST_REQUIRE_EQUAL( s.size(), 2);

      auto  it = s.begin();
      BOOST_REQUIRE( it != s.end());
      ++it;
      BOOST_REQUIRE( it != s.end());
      ++it;
      BOOST_REQUIRE_EQUAL( it, s.end());
   } // end scope

} // test_simple_add



/// Check adding one argument, conflict with second argument.
/// @since  x.y.z, 22.06.2017
BOOST_AUTO_TEST_CASE( test_add_one)
{

   // add first argument/object, adding another object with same short argument
   // fails
   {
      Storage< int>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "n"), invalid_argument);
   } // end scope

   // add first argument/object, adding another object with same long argument
   // fails
   {
      Storage< int, runtime_error>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "number"), runtime_error);
   } // end scope

   // add first argument/object, adding another object with same short argument
   // fails
   {
      Storage< int>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n,number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "n"), invalid_argument);
   } // end scope

   // add first argument/object, adding another object with same long argument
   // fails
   {
      Storage< int, runtime_error>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n,number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "number"), runtime_error);
   } // end scope

   // add first argument/object, adding another object with argument mismatch
   // fails
   {
      Storage< int>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n,number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "n,name"), invalid_argument);
   } // end scope

   // add first argument/object, adding another object with argument mismatch
   // fails
   {
      Storage< int, runtime_error>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n,number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "a,number"), runtime_error);
   } // end scope

} // test_add_one



/// Check adding two arguments, conflict with third argument.
/// @since  x.y.z, 22.06.2017
BOOST_AUTO_TEST_CASE( test_add_two)
{

   // add first argument/object, adding another object with same short argument
   // fails
   {
      Storage< int>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n"));
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "n"), invalid_argument);
   } // end scope

   // add first argument/object, adding another object with same long argument
   // fails
   {
      Storage< int, runtime_error>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n"));
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "number"), runtime_error);
   } // end scope

   // add first argument/object, adding another object with same short argument
   // fails
   {
      Storage< int>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "m,maximum"));
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n,number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "m,mode"), invalid_argument);
   } // end scope

   // add first argument/object, adding another object with same long argument
   // fails
   {
      Storage< int, runtime_error>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "m,maximum"));
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n,number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "a,maximum"), runtime_error);
   } // end scope

   // add first argument/object, adding another object with argument mismatch
   // fails
   {
      Storage< int>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "m,maximum"));
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n,number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "n,name"), invalid_argument);
   } // end scope

   // add first argument/object, adding another object with argument mismatch
   // fails
   {
      Storage< int, runtime_error>  s;
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "m,maximum"));
      BOOST_REQUIRE_NO_THROW( s.addArgument( 42, "n,number"));
      BOOST_REQUIRE_THROW( s.addArgument( 42, "u,number"), runtime_error);
   } // end scope

} // test_add_two



// =========================  END OF test_storage.cpp  =========================

