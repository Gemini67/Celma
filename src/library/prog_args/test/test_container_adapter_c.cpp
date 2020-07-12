
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
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
#include <stdexcept>
#include <string>
#include <tuple>


// Boost includes
#define BOOST_TEST_MODULE ValueHandlerTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/check_assign.hpp"
#include "celma/test/check_return.hpp"


using celma::prog_args::detail::ContainerAdapter;


namespace {


/// Do some checks with the container adapter used with a template type.
///
/// @return  \c true if all tests passed successfully.
/// @since  1.34.0, 13.12.2019
template< template< typename...> class C> bool checkContAdapt()
{

   using container_t = C< int>;
   using container_adapter_t = ContainerAdapter< container_t>;

   container_t          my_container;
   container_adapter_t  my_cont_adapter( my_container);


   my_cont_adapter.addValue( 42);
   my_cont_adapter.addValue( 13);

   CHECK_EQUAL_RETURN( my_cont_adapter.size(), 2);

   my_cont_adapter.clear();

   CHECK_EQUAL_RETURN( my_cont_adapter.size(), 0);

   my_cont_adapter.addValue( 42);
   my_cont_adapter.addValue( 13);

   CHECK_EQUAL_RETURN( my_cont_adapter.size(), 2);

   return true;
} // checkContAdapt


} // namespace



/// Verify that container adapter exist only for those types that should be
/// supported.
///
/// @since  1.34.0, 29.11.2019
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

   // std::vector< bool>
   static_assert( !ContainerAdapter< std::vector< bool>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( ContainerAdapter< std::vector< bool>>::HasAdapter, false);

   // celma::common::CheckAssign
   static_assert( !ContainerAdapter<
      celma::common::CheckAssign< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL(
      ContainerAdapter< celma::common::CheckAssign< int>>::HasAdapter, false);

} // no_adapter



/// Check the features of the container adapter for queues.
/// Also test that the values are stored in the destination queue.
///
/// @since  1.34.0, 04.12.2019
BOOST_AUTO_TEST_CASE( deque_adapter)
{

   using my_queue = std::deque< int>;
   using my_adapter = ContainerAdapter< my_queue>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, true);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_queue    q;
   my_adapter  caq( q);

   BOOST_REQUIRE( caq.empty());
   BOOST_REQUIRE_EQUAL( caq.size(), 0);
   BOOST_REQUIRE( !caq.contains( 42));

   caq.addValue( 42);

   BOOST_REQUIRE( !caq.empty());
   BOOST_REQUIRE_EQUAL( caq.size(), 1);
   BOOST_REQUIRE( caq.contains( 42));

   BOOST_REQUIRE( !q.empty());
   BOOST_REQUIRE_EQUAL( q.size(), 1);

   BOOST_REQUIRE_NO_THROW( caq.clear());

   BOOST_REQUIRE( caq.empty());
   BOOST_REQUIRE_EQUAL( caq.size(), 0);
   BOOST_REQUIRE( !caq.contains( 42));

   BOOST_REQUIRE( q.empty());
   BOOST_REQUIRE_EQUAL( q.size(), 0);

   caq.addValue( 42);
   caq.addValue( 13);
   caq.addValue( 17);
   caq.addValue( 9);

   BOOST_REQUIRE_EQUAL( caq.toString(), "42, 13, 17, 9");

   BOOST_REQUIRE_NO_THROW( caq.sort());

   BOOST_REQUIRE_EQUAL( caq.toString(), "9, 13, 17, 42");

   // check with duplicate value
   BOOST_REQUIRE_NO_THROW( caq.addValue( 13));
   BOOST_REQUIRE_EQUAL( caq.toString(), "9, 13, 17, 42, 13");

} // deque_adapter



/// Check the features of the container adapter for forward-lists.
/// Also test that the values are stored in the destination list.
///
/// @since  1.34.0, 30.12.2019
BOOST_AUTO_TEST_CASE( forward_list_adapter)
{

   using my_list = std::forward_list< int>;
   using my_adapter = ContainerAdapter< my_list>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, true);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_list     l;
   my_adapter  cal( l);

   BOOST_REQUIRE( cal.empty());
   BOOST_REQUIRE_EQUAL( cal.size(), 0);
   BOOST_REQUIRE( !cal.contains( 42));

   cal.addValue( 42);

   BOOST_REQUIRE( !cal.empty());
   BOOST_REQUIRE_EQUAL( cal.size(), 1);
   BOOST_REQUIRE( cal.contains( 42));

   BOOST_REQUIRE( !l.empty());

   BOOST_REQUIRE_NO_THROW( cal.clear());

   BOOST_REQUIRE( cal.empty());
   BOOST_REQUIRE_EQUAL( cal.size(), 0);
   BOOST_REQUIRE( !cal.contains( 42));

   BOOST_REQUIRE( l.empty());

   cal.addValue( 42);
   cal.addValue( 13);

   BOOST_REQUIRE_EQUAL( cal.toString(), "13, 42");

   BOOST_REQUIRE_NO_THROW( cal.sort());

   BOOST_REQUIRE_EQUAL( cal.toString(), "13, 42");

   // check with duplicate value
   BOOST_REQUIRE_NO_THROW( cal.addValue( 13));
   BOOST_REQUIRE_EQUAL( cal.toString(), "13, 13, 42");

} // forward_list_adapter



/// Check the features of the container adapter for lists.
/// Also test that the values are stored in the destination list.
///
/// @since  1.34.0, 11.12.2019
BOOST_AUTO_TEST_CASE( list_adapter)
{

   using my_list = std::list< int>;
   using my_adapter = ContainerAdapter< my_list>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, true);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_list     l;
   my_adapter  cal( l);

   BOOST_REQUIRE( cal.empty());
   BOOST_REQUIRE_EQUAL( cal.size(), 0);
   BOOST_REQUIRE( !cal.contains( 42));

   cal.addValue( 42);

   BOOST_REQUIRE( !cal.empty());
   BOOST_REQUIRE_EQUAL( cal.size(), 1);
   BOOST_REQUIRE( cal.contains( 42));

   BOOST_REQUIRE( !l.empty());
   BOOST_REQUIRE_EQUAL( l.size(), 1);

   BOOST_REQUIRE_NO_THROW( cal.clear());

   BOOST_REQUIRE( cal.empty());
   BOOST_REQUIRE_EQUAL( cal.size(), 0);
   BOOST_REQUIRE( !cal.contains( 42));

   BOOST_REQUIRE( l.empty());
   BOOST_REQUIRE_EQUAL( l.size(), 0);

   cal.addValue( 42);
   cal.addValue( 13);

   BOOST_REQUIRE_EQUAL( cal.toString(), "42, 13");

   BOOST_REQUIRE_NO_THROW( cal.sort());

   BOOST_REQUIRE_EQUAL( cal.toString(), "13, 42");

   // check with duplicate value
   BOOST_REQUIRE_NO_THROW( cal.addValue( 13));
   BOOST_REQUIRE_EQUAL( cal.toString(), "13, 42, 13");

} // list_adapter



/// Check the features of the container adapter for multisets.
/// Also test that the values are stored in the destination set.
///
/// @since  1.34.0, 13.12.2019
BOOST_AUTO_TEST_CASE( multiset_adapter)
{

   using my_multiset = std::multiset< int>;
   using my_adapter = ContainerAdapter< my_multiset>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, true);

   my_multiset  ms;
   my_adapter   cams( ms);

   BOOST_REQUIRE( cams.empty());
   BOOST_REQUIRE_EQUAL( cams.size(), 0);
   BOOST_REQUIRE( !cams.contains( 42));

   cams.addValue( 42);

   BOOST_REQUIRE( !cams.empty());
   BOOST_REQUIRE_EQUAL( cams.size(), 1);
   BOOST_REQUIRE( cams.contains( 42));

   BOOST_REQUIRE( !ms.empty());
   BOOST_REQUIRE_EQUAL( ms.size(), 1);

   BOOST_REQUIRE_NO_THROW( cams.clear());

   BOOST_REQUIRE( cams.empty());
   BOOST_REQUIRE_EQUAL( cams.size(), 0);
   BOOST_REQUIRE( !cams.contains( 42));

   BOOST_REQUIRE( ms.empty());
   BOOST_REQUIRE_EQUAL( ms.size(), 0);

   cams.addValue( 42);
   cams.addValue( 13);

   BOOST_REQUIRE_EQUAL( cams.toString(), "13, 42");

   BOOST_REQUIRE_THROW( cams.sort(), std::logic_error);

   // check with duplicate value
   cams.addValue( 42);
   BOOST_REQUIRE_EQUAL( cams.toString(), "13, 42, 42");

} // multiset_adapter



/// Check the features of the container adapter for priority queues.
/// Also test that the values are stored in the destination queue.
///
/// @since  1.34.0, 20.12.2019
BOOST_AUTO_TEST_CASE( priority_queue_adapter)
{

   using my_prio_queue = std::priority_queue< int>;
   using my_adapter = ContainerAdapter< my_prio_queue>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, false);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, true);

   my_prio_queue  pq;
   my_adapter     capq( pq);

   BOOST_REQUIRE( capq.empty());
   BOOST_REQUIRE_EQUAL( capq.size(), 0);

   capq.addValue( 42);

   BOOST_REQUIRE( !capq.empty());
   BOOST_REQUIRE_EQUAL( capq.size(), 1);

   BOOST_REQUIRE( !pq.empty());
   BOOST_REQUIRE_EQUAL( pq.size(), 1);

   capq.addValue( 42);
   capq.addValue( 13);
   capq.addValue( 17);
   capq.addValue( 9);

   BOOST_REQUIRE_EQUAL( capq.toString(), "42, 42, 17, 13, 9");

   BOOST_REQUIRE_THROW( capq.contains( 42), std::logic_error);
   BOOST_REQUIRE_THROW( capq.sort(), std::logic_error);

} // priority_queue_adapter



/// Check the features of the container adapter for queues.
/// Also test that the values are stored in the destination queue.
///
/// @since  1.34.0, 02.01.2020
BOOST_AUTO_TEST_CASE( queue_adapter)
{

   using my_queue = std::queue< int>;
   using my_adapter = ContainerAdapter< my_queue>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, false);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_queue    q;
   my_adapter  caq( q);

   BOOST_REQUIRE( caq.empty());
   BOOST_REQUIRE_EQUAL( caq.size(), 0);

   caq.addValue( 42);

   BOOST_REQUIRE( !caq.empty());
   BOOST_REQUIRE_EQUAL( caq.size(), 1);

   BOOST_REQUIRE( !q.empty());
   BOOST_REQUIRE_EQUAL( q.size(), 1);

   BOOST_REQUIRE_NO_THROW( caq.clear());

   BOOST_REQUIRE( caq.empty());
   BOOST_REQUIRE_EQUAL( caq.size(), 0);

   BOOST_REQUIRE( q.empty());
   BOOST_REQUIRE_EQUAL( q.size(), 0);

   caq.addValue( 42);
   caq.addValue( 13);
   caq.addValue( 17);
   caq.addValue( 9);

   BOOST_REQUIRE_EQUAL( caq.toString(), "42, 13, 17, 9");

   // check with duplicate value
   BOOST_REQUIRE_NO_THROW( caq.addValue( 13));
   BOOST_REQUIRE_EQUAL( caq.toString(), "42, 13, 17, 9, 13");

   BOOST_REQUIRE_THROW( caq.sort(), std::logic_error);
   BOOST_REQUIRE_THROW( caq.contains( 13), std::logic_error);

} // queue_adapter



/// Check the features of the container adapter for sets.
/// Also test that the values are stored in the destination set.
///
/// @since  1.34.0, 02.12.2019
BOOST_AUTO_TEST_CASE( set_adapter)
{

   using my_set = std::set< int>;
   using my_adapter = ContainerAdapter< my_set>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
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

   // check with duplicate value
   BOOST_REQUIRE_NO_THROW( cas.addValue( 42));
   BOOST_REQUIRE_EQUAL( cas.toString(), "13, 42");

} // set_adapter



/// Check the features of the container adapter for stacks.
/// Also test that the values are stored in the destination stack.
///
/// @since  1.34.0, 02.12.2019
BOOST_AUTO_TEST_CASE( stack_adapter)
{

   using my_stack = std::stack< int>;
   using my_adapter = ContainerAdapter< my_stack>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, false);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
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

   // check with duplicate value
   cas.addValue( 42);
   BOOST_REQUIRE_EQUAL( cas.toString(), "42, 13, 42");

   BOOST_REQUIRE_NO_THROW( cas.clear());
   BOOST_REQUIRE( cas.empty());
   BOOST_REQUIRE_EQUAL( cas.size(), 0);
   BOOST_REQUIRE( s.empty());
   BOOST_REQUIRE_EQUAL( s.size(), 0);

   BOOST_REQUIRE_THROW( cas.contains( 42), std::logic_error);
   BOOST_REQUIRE_THROW( cas.sort(), std::logic_error);

} // stack_adapter



/// Check the features of the container adapter for unordered multi-sets.
/// Also test that the values are stored in the destination unordered set.
///
/// @since  1.34.0, 17.12.2019
BOOST_AUTO_TEST_CASE( unordered_multiset_adapter)
{

   using my_set = std::unordered_multiset< int>;
   using my_adapter = ContainerAdapter< my_set>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_set      us;
   my_adapter  caus( us);

   BOOST_REQUIRE( caus.empty());
   BOOST_REQUIRE_EQUAL( caus.size(), 0);
   BOOST_REQUIRE( !caus.contains( 42));

   caus.addValue( 42);

   BOOST_REQUIRE( !caus.empty());
   BOOST_REQUIRE_EQUAL( caus.size(), 1);
   BOOST_REQUIRE( caus.contains( 42));

   BOOST_REQUIRE( !us.empty());
   BOOST_REQUIRE_EQUAL( us.size(), 1);

   BOOST_REQUIRE_NO_THROW( caus.clear());

   BOOST_REQUIRE( caus.empty());
   BOOST_REQUIRE_EQUAL( caus.size(), 0);
   BOOST_REQUIRE( !caus.contains( 42));

   BOOST_REQUIRE( us.empty());
   BOOST_REQUIRE_EQUAL( us.size(), 0);

   caus.addValue( 42);
   caus.addValue( 13);
   caus.addValue( 17);
   caus.addValue( 9);

   BOOST_REQUIRE_EQUAL( caus.toString(), "9, 17, 13, 42");

   BOOST_REQUIRE_THROW( caus.sort(), std::logic_error);

   // check with duplicate value
   BOOST_REQUIRE_NO_THROW( caus.addValue( 42));
   BOOST_REQUIRE_EQUAL( caus.toString(), "9, 17, 13, 42, 42");

} // unordered_multiset_adapter



/// Check the features of the container adapter for unordered sets.
/// Also test that the values are stored in the destination unordered set.
///
/// @since  1.34.0, 04.12.2019
BOOST_AUTO_TEST_CASE( unordered_set_adapter)
{

   using my_set = std::unordered_set< int>;
   using my_adapter = ContainerAdapter< my_set>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

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
   cas.addValue( 17);
   cas.addValue( 9);

   BOOST_REQUIRE_EQUAL( cas.toString(), "9, 17, 13, 42");

   BOOST_REQUIRE_THROW( cas.sort(), std::logic_error);

   // check with duplicate value
   BOOST_REQUIRE_NO_THROW( cas.addValue( 42));
   BOOST_REQUIRE_EQUAL( cas.toString(), "9, 17, 13, 42");

} // unordered_set_adapter



/// Check the features of the container adapter for vectors.
/// Also test that the values are stored in the destination vector.
///
/// @since  1.34.0, 29.11.2019
BOOST_AUTO_TEST_CASE( vector_adapter)
{

   using my_vector = std::vector< int>;
   using my_adapter = ContainerAdapter< my_vector>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, true);
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

   // check with duplicate value
   cav.addValue( 13);
   BOOST_REQUIRE_EQUAL( cav.toString(), "13, 42, 13");

} // vector_adapter



/// Test the container adapter with a template.
///
/// @since  1.34.0, 13.12.2019
BOOST_AUTO_TEST_CASE( template_test)
{

   BOOST_REQUIRE( checkContAdapt< std::deque>());
   BOOST_REQUIRE( checkContAdapt< std::forward_list>());
   BOOST_REQUIRE( checkContAdapt< std::list>());
   BOOST_REQUIRE( checkContAdapt< std::multiset>());
   BOOST_REQUIRE( checkContAdapt< std::priority_queue>());
   BOOST_REQUIRE( checkContAdapt< std::queue>());
   BOOST_REQUIRE( checkContAdapt< std::set>());
   BOOST_REQUIRE( checkContAdapt< std::stack>());
   BOOST_REQUIRE( checkContAdapt< std::unordered_multiset>());
   BOOST_REQUIRE( checkContAdapt< std::unordered_set>());
   BOOST_REQUIRE( checkContAdapt< std::vector>());

} // template_test



// =====  END OF test_container_adapter_c.cpp  =====

