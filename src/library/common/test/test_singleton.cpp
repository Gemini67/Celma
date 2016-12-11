 
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
**    Test program for the module Singleton using the Boost.Test module.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>


// STL includes
#include <string>
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE SingletonTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/singleton.hpp"
#include "celma/common/object_enumerator.hpp"


using namespace std;
using namespace celma;


// module definitions

/// Defines a singleton.
/// @since  0.2, 10.04.2016
class TestSingleton: public common::Singleton< TestSingleton>,
                        public common::ObjectEnumerator< TestSingleton>
{

   friend class common::Singleton< TestSingleton>;

public:
   /// Some dummy function.
   /// @since  0.2, 10.04.2016
   void func()
   {
   } // end TestSingleton::func

protected:
   /// Constructor. Should be called only exactly once.
   /// @since  0.2, 10.04.2016
   TestSingleton():
      common::Singleton< TestSingleton>(),
      common::ObjectEnumerator< TestSingleton>()
   {
   } // end TestSingleton::TestSingleton

}; // TestSingleton



/// Test access of a Singleton object.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_singleton)
{

   BOOST_REQUIRE_NO_THROW( TestSingleton::instance().func());
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().objectNbr(), 0);

} // test_singleton



/// Test second access of a Singleton object.
/// @since  0.10, 11.12.2016
BOOST_AUTO_TEST_CASE( test_singleton_again)
{

   BOOST_REQUIRE_NO_THROW( TestSingleton::instance().func());
   BOOST_REQUIRE_EQUAL( TestSingleton::instance().objectNbr(), 0);

} // test_singleton_again



// ========================  END OF test_singleton.cpp  ========================
