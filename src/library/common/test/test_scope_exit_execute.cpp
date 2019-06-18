
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test header file include
#include "celma/common/scope_exit_execute.hpp"


#include <stdexcept>


// Boost includes
#define BOOST_TEST_MODULE ScopeExitExecuteTest
#include <boost/test/unit_test.hpp>


using celma::common::ScopeExitExecute;


namespace {


/// Function that creates a ScopeExitExecute object with a lambda that throws an
/// exception.
///
/// @since  1.28.0, 18.06.2019
void throwing()
{

   const ScopeExitExecute  see( []() { throw std::runtime_error( "die!"); });

} // throwing


} // namespace



/// Test that the code is executed only when the object's scope is left.
///
/// @since  1.28.0, 18.06.2019
BOOST_AUTO_TEST_CASE( execute_when_scope_is_left)
{

   bool  flag = false;

   {
      const ScopeExitExecute  see( [&flag]() { flag = true; });
      BOOST_REQUIRE( !flag);
   } // end scope

   BOOST_REQUIRE( flag);

} // execute_when_scope_is_left



/// Check that an exception, thrown by the function to execute, is caught by the
/// ScopeExitExecute destructor.
///
/// @since  1.28.0, 18.06.2019
BOOST_AUTO_TEST_CASE( catch_exception)
{

   BOOST_REQUIRE_NO_THROW( throwing());

} // catch_exception



// =====  END OF test_scope_exit_execute.cpp  =====

