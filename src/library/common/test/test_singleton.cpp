 
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

/// Defines a singleton using the default policy (static).
/// @since  0.2, 10.04.2016
class DefaultSingleton: public common::Singleton< DefaultSingleton>,
                        public common::ObjectEnumerator< DefaultSingleton>
{

   friend class common::detail::StaticSingletonCreator< DefaultSingleton>;

public:
   /// Some dummy function.
   /// @since  0.2, 10.04.2016
   void func()
   {
   } // end DefaultSingleton::func

protected:
   /// Constructor. Should be called only exactly once.
   /// @since  0.2, 10.04.2016
   DefaultSingleton():
      common::Singleton< DefaultSingleton>(),
      common::ObjectEnumerator< DefaultSingleton>()
   {
   } // end DefaultSingleton::DefaultSingleton

}; // DefaultSingleton


/// Defines a singleton explicitly using the 'static' policy.
/// @since  0.2, 10.04.2016
class StaticSingleton:
   public common::Singleton< StaticSingleton, common::detail::StaticSingletonCreator>,
   public common::ObjectEnumerator< StaticSingleton>
{

   friend class common::detail::StaticSingletonCreator< StaticSingleton>;

public:
   /// Some dummy function.
   /// @since  0.2, 10.04.2016
   void func()
   {
   } // end StaticSingleton::func

protected:
   /// Constructor. Should be called only exactly once.
   /// @since  0.2, 10.04.2016
   StaticSingleton():
      common::Singleton< StaticSingleton, common::detail::StaticSingletonCreator>(),
      ObjectEnumerator< StaticSingleton>()
   {
   } // end StaticSingleton::StaticSingleton

}; // StaticSingleton


/// Defines a singleton explicitly using the 'dynamic' policy.
/// @since  0.2, 10.04.2016
class DynamicSingleton:
   public common::Singleton< DynamicSingleton, common::detail::DynamicSingletonCreator>,
   public common::ObjectEnumerator< DynamicSingleton>
{

   friend class common::detail::DynamicSingletonCreator< DynamicSingleton>;

public:
   /// Some dummy function.
   /// @since  0.2, 10.04.2016
   void func()
   {
   } // end DynamicSingleton::func

protected:
   /// Constructor. May be called several times.
   /// @since  0.2, 10.04.2016
   DynamicSingleton():
      common::Singleton< DynamicSingleton, common::detail::DynamicSingletonCreator>(),
      ObjectEnumerator< DynamicSingleton>()
   {
   } // end DynamicSingleton::DynamicSingleton

}; // DynamicSingleton



/// Test access of a Singleton object with the default policies.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( default_policy)
{

   BOOST_REQUIRE_NO_THROW( DefaultSingleton::instance().func());
   BOOST_REQUIRE_EQUAL( DefaultSingleton::instance().objectNbr(), 0);

   BOOST_REQUIRE_THROW( DefaultSingleton::instance().destroy(), runtime_error);
   BOOST_REQUIRE_EQUAL( DefaultSingleton::instance().objectNbr(), 0);

} // end default_policy



/// Test access of a Singleton object with static creation policy.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( explicit_static_policy)
{

   BOOST_REQUIRE_NO_THROW( StaticSingleton::instance().func());
   BOOST_REQUIRE_EQUAL( StaticSingleton::instance().objectNbr(), 0);

   BOOST_REQUIRE_THROW( StaticSingleton::instance().destroy(), runtime_error);
   BOOST_REQUIRE_EQUAL( StaticSingleton::instance().objectNbr(), 0);

} // end explicit_static_policy



/// Test access of a Singleton object with dynamic creation policy.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( explicit_dynamic_policy)
{

   BOOST_REQUIRE_NO_THROW( DynamicSingleton::instance().func());
   BOOST_REQUIRE_EQUAL( DynamicSingleton::instance().objectNbr(), 0);

   BOOST_REQUIRE_NO_THROW( DynamicSingleton::instance().destroy());
   BOOST_REQUIRE_EQUAL( DynamicSingleton::instance().objectNbr(), 1);

} // end explicit_dynamic_policy



// =========================  END OF test_singleton.cpp  =========================
