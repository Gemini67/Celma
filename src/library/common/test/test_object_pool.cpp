
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test header file include
#include "celma/common/make_pooled_ptr.hpp"


// Boost includes
#define BOOST_TEST_MODULE ObjectPoolTest
#include <boost/test/unit_test.hpp>
#include <utility>


using celma::common::make_pooled_ptr;
using celma::common::ObjectPool;


/// Test with a single, pooled object.
/// @since  x.y, 29.01.2017
BOOST_AUTO_TEST_CASE( test_single)
{

   {
      auto  o1 = make_pooled_ptr< std::string>();
      o1->assign( "hello world");
   } // end scope

   BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 1);

   {
      auto  o1 = make_pooled_ptr< std::string>();
      BOOST_REQUIRE_EQUAL( *o1, "hello world");
      BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 1);

   ObjectPool< std::string>::instance().clear();

   BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 0);

} // test_single



/// Test that an object that was created with parameters is afterwards returned
/// to the pool.
/// @since  x.y, 29.01.2017
BOOST_AUTO_TEST_CASE( test_parameters)
{

   {
      auto  o1 = make_pooled_ptr< std::string>( "hello again");
      BOOST_REQUIRE_EQUAL( *o1, "hello again");
      BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 1);

   {
      auto  o1 = make_pooled_ptr< std::string>();
      BOOST_REQUIRE_EQUAL( *o1, "hello again");
      BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 0);
   } // end scope

   BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 1);

   ObjectPool< std::string>::instance().clear();

   BOOST_REQUIRE_EQUAL( ObjectPool< std::string>::instance().size(), 0);

} // test_parameters



// =======================  END OF test_object_pool.cpp  =======================

