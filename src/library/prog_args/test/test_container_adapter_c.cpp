
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
**    Test program for the template family
**    celma::prog_args::detail::ContainerAdapter, using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/prog_args/detail/container_adapter.hpp"


// C++ Standard Library includes
#include <array>
#include <bitset>
#include <optional>
#include <stack>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ValueHandlerTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/check_assign.hpp"


using celma::prog_args::detail::ContainerAdapter;



/// Verify that container adapter exist only for those types that should be
/// supported.
///
/// @since  x.y.z, 29.11.2019
BOOST_AUTO_TEST_CASE( no_adapter)
{

   // std::array
   using my_array = std::array< int, 10>;
   static_assert( !ContainerAdapter< my_array>::HasAdapter);
   BOOST_REQUIRE_EQUAL( ContainerAdapter< my_array>::HasAdapter, false);

   // std::bitset
   static_assert( !ContainerAdapter< std::bitset< 10>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( ContainerAdapter< std::bitset< 10>>::HasAdapter, false);

   // std::optional
   static_assert( !ContainerAdapter< std::optional< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( ContainerAdapter< std::optional< int>>::HasAdapter,
      false);

   // std::string
   static_assert( !ContainerAdapter< std::string>::HasAdapter);
   BOOST_REQUIRE_EQUAL( ContainerAdapter< std::string>::HasAdapter, false);

   // std::tuple
   static_assert( !ContainerAdapter< std::tuple< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( ContainerAdapter< std::tuple< int>>::HasAdapter, false);

   // celma::common::CheckAssign
   static_assert( !ContainerAdapter<
      celma::common::CheckAssign< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL(
      ContainerAdapter< celma::common::CheckAssign< int>>::HasAdapter, false);

} // no_adapter



/// Check the features of the container adapter for sets.
/// Also test that the values are stored in the destination set.
///
/// @since  x.y.z, 02.12.2019
BOOST_AUTO_TEST_CASE( set_adapter)
{

   using my_set = std::set< int>;
   using my_adapter = ContainerAdapter< my_set>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsDuplicates, false);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsClearable, true);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, true);

   my_set      s;
   my_adapter  cas( s);

   BOOST_REQUIRE( cas.empty());
   BOOST_REQUIRE_EQUAL( cas.size(), 0);
   BOOST_REQUIRE( !cas.contains( 42));

   cas.addValue( 42);

   BOOST_REQUIRE( !cas.empty());
   BOOST_REQUIRE_EQUAL( cas.size(), 1);
   BOOST_REQUIRE( cas.contains( 42));

   BOOST_REQUIRE( !s.empty());
   BOOST_REQUIRE_EQUAL( s.size(), 1);

   BOOST_REQUIRE_NO_THROW( cas.clear());

   BOOST_REQUIRE( cas.empty());
   BOOST_REQUIRE_EQUAL( cas.size(), 0);
   BOOST_REQUIRE( !cas.contains( 42));

   BOOST_REQUIRE( s.empty());
   BOOST_REQUIRE_EQUAL( s.size(), 0);

   cas.addValue( 42);
   cas.addValue( 13);

   BOOST_REQUIRE_EQUAL( cas.toString(), "13, 42");

   BOOST_REQUIRE_THROW( cas.sort(), std::logic_error);

} // set_adapter



/// Check the features of the container adapter for stacks.
/// Also test that the values are stored in the destination stack.
///
/// @since  x.y.z, 02.12.2019
BOOST_AUTO_TEST_CASE( stack_adapter)
{

   using my_stack = std::stack< int>;
   using my_adapter = ContainerAdapter< my_stack>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, false);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsDuplicates, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsClearable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_stack    s;
   my_adapter  cas( s);

   BOOST_REQUIRE( cas.empty());
   BOOST_REQUIRE_EQUAL( cas.size(), 0);

   cas.addValue( 42);

   BOOST_REQUIRE( !cas.empty());
   BOOST_REQUIRE_EQUAL( cas.size(), 1);

   BOOST_REQUIRE( !s.empty());
   BOOST_REQUIRE_EQUAL( s.size(), 1);

   cas.addValue( 13);

   BOOST_REQUIRE_EQUAL( cas.toString(), "13, 42");

   BOOST_REQUIRE_THROW( cas.clear(), std::logic_error);
   BOOST_REQUIRE_THROW( cas.contains( 42), std::logic_error);
   BOOST_REQUIRE_THROW( cas.sort(), std::logic_error);

} // stack_adapter



/// Check the features of the container adapter for vectors.
/// Also test that the values are stored in the destination vector.
///
/// @since  x.y.z, 29.11.2019
BOOST_AUTO_TEST_CASE( vector_adapter)
{

   using my_vector = std::vector< int>;
   using my_adapter = ContainerAdapter< my_vector>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsDuplicates, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, true);
   BOOST_REQUIRE_EQUAL( my_adapter::IsClearable, true);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, true);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_vector   v;
   my_adapter  cav( v);

   BOOST_REQUIRE( cav.empty());
   BOOST_REQUIRE_EQUAL( cav.size(), 0);
   BOOST_REQUIRE( !cav.contains( 42));

   cav.addValue( 42);

   BOOST_REQUIRE( !cav.empty());
   BOOST_REQUIRE_EQUAL( cav.size(), 1);
   BOOST_REQUIRE( cav.contains( 42));

   BOOST_REQUIRE( !v.empty());
   BOOST_REQUIRE_EQUAL( v.size(), 1);

   BOOST_REQUIRE_NO_THROW( cav.clear());

   BOOST_REQUIRE( cav.empty());
   BOOST_REQUIRE_EQUAL( cav.size(), 0);
   BOOST_REQUIRE( !cav.contains( 42));

   BOOST_REQUIRE( v.empty());
   BOOST_REQUIRE_EQUAL( v.size(), 0);

   cav.addValue( 42);
   cav.addValue( 13);

   BOOST_REQUIRE_EQUAL( cav.toString(), "42, 13");

   BOOST_REQUIRE_NO_THROW( cav.sort());

   BOOST_REQUIRE_EQUAL( cav.toString(), "13, 42");

} // vector_adapter



// =====  END OF test_container_adapter_c.cpp  =====

