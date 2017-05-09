 
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module Singleton using the Boost.Test module.
**
--*/


// object to test, header file include
#include "celma/common/singleton.hpp"


// Boost includes
#define BOOST_TEST_MODULE SingletonTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/object_enumerator.hpp"


using celma::common::Singleton;


// module definitions

/// Defines a singleton.
/// @since  0.2, 10.04.2016
class TestSingleton: public Singleton< TestSingleton>,
                     public celma::common::ObjectEnumerator< TestSingleton>
{

   friend class Singleton< TestSingleton>;

public:
   /// Some dummy function.
   /// @since  0.2, 10.04.2016
   void func()
   {
   } // TestSingleton::func

   /// Returns the value stored in the singleton object.
   /// @return  The value stored internally.
   /// @since  0.12.2, 05.02.2017
   int value() const
   {
      return mValue;
   } // TestSingleton::value
   
protected:
   /// Constructor. Should be called only exactly once.
   /// @since  0.2, 10.04.2016
   TestSingleton():
      Singleton< TestSingleton>(),
      celma::common::ObjectEnumerator< TestSingleton>()
   {
   } // TestSingleton::TestSingleton

   /// Constructor. Should be called only exactly once.
   /// @since  0.2, 10.04.2016
   TestSingleton( int new_value):
      Singleton< TestSingleton>(),
      celma::common::ObjectEnumerator< TestSingleton>(),
      mValue( new_value)
   {
   } // TestSingleton::TestSingleton

   int  mValue = -1;

}; // TestSingleton



/// Test access of a Singleton object.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_singleton)
{

   BOOST_REQUIRE_NO_THROW( TestSingleton::instance().func());
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().objectNbr(), 0);
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().value(), -1);

} // test_singleton



/// Test second access of a Singleton object.
/// @since  0.10, 11.12.2016
BOOST_AUTO_TEST_CASE( test_singleton_again)
{

   BOOST_REQUIRE_NO_THROW( TestSingleton::instance().func());
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().objectNbr(), 0);
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().value(), -1);

   // test that parameters passed to instance are simply ignored now
   BOOST_REQUIRE_NO_THROW( TestSingleton::instance( 13).func());
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().objectNbr(), 0);
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().value(), -1);

} // test_singleton_again



/// Test that we get a new object after calling reset().
/// @since  0.12.2, 05.02.2017
BOOST_AUTO_TEST_CASE( test_reset)
{

   TestSingleton::reset();

   BOOST_REQUIRE_NO_THROW( TestSingleton::instance( 42).func());
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().objectNbr(), 1);
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().value(), 42);

} // test_reset



// ========================  END OF test_singleton.cpp  ========================
