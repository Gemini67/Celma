
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template family
**    celma::prog_args::detail::KeyValueContainerAdapter, using the Boost.Test
**    framework.
**
--*/


// module to test headerfile include
#include "celma/prog_args/detail/key_value_container_adapter.hpp"


// C++ Standard Library includes
#include <array>
#include <bitset>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE KeyValueContainerAdapterTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/check_assign.hpp"
#include "celma/test/check_return.hpp"


using celma::prog_args::detail::KeyValueContainerAdapter;


namespace {


/// Do some checks with the key-value container adapter used with a template
/// type.
///
/// @return  \c true if all tests passed successfully.
/// @since  1.41.0, 15.02.2020
template< template< typename, typename> class C> bool checkContAdapt()
{

   using container_t = C< int, std::string>;
   using container_adapter_t = KeyValueContainerAdapter< container_t>;

   container_t          my_container;
   container_adapter_t  my_cont_adapter( my_container);


   my_cont_adapter.addValue( 42, "hello");
   my_cont_adapter.addValue( 13, "world");

   CHECK_EQUAL_RETURN( my_cont_adapter.size(), 2);

   my_cont_adapter.clear();

   CHECK_EQUAL_RETURN( my_cont_adapter.size(), 0);

   my_cont_adapter.addValue( 42, "hello");
   my_cont_adapter.addValue( 13, "world");

   CHECK_EQUAL_RETURN( my_cont_adapter.size(), 2);

   return true;
} // checkContAdapt


} // namespace



/// Verify that key-value container adapter exist only for those types that
/// should be supported.
///
/// @since  1.41.0, 15.02.2020
BOOST_AUTO_TEST_CASE( no_adapter)
{

   // std::array
   using my_array = std::array< int, 10>;
   static_assert( !KeyValueContainerAdapter< my_array>::HasAdapter);
   BOOST_REQUIRE_EQUAL( KeyValueContainerAdapter< my_array>::HasAdapter, false);

   // std::bitset
   static_assert( !KeyValueContainerAdapter< std::bitset< 10>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( KeyValueContainerAdapter< std::bitset< 10>>::HasAdapter,
      false);

   // std::optional
   static_assert( !KeyValueContainerAdapter< std::optional< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( KeyValueContainerAdapter< std::optional< int>>::HasAdapter,
      false);

   // std::string
   static_assert( !KeyValueContainerAdapter< std::string>::HasAdapter);
   BOOST_REQUIRE_EQUAL( KeyValueContainerAdapter< std::string>::HasAdapter,
      false);

   // std::tuple
   static_assert( !KeyValueContainerAdapter< std::tuple< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( KeyValueContainerAdapter< std::tuple< int>>::HasAdapter,
      false);

   // celma::common::CheckAssign
   static_assert( !KeyValueContainerAdapter<
      celma::common::CheckAssign< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL(
      KeyValueContainerAdapter< celma::common::CheckAssign< int>>::HasAdapter,
         false);

   // std::vector
   static_assert( !KeyValueContainerAdapter< std::vector< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( KeyValueContainerAdapter< std::vector< int>>::HasAdapter,
      false);

   // std::set
   static_assert( !KeyValueContainerAdapter< std::set< int>>::HasAdapter);
   BOOST_REQUIRE_EQUAL( KeyValueContainerAdapter< std::set< int>>::HasAdapter,
      false);

} // no_adapter



/// Check the features of the container adapter for maps.
/// Also test that the values are stored in the destination map.
///
/// @since  1.41.0, 15.02.2020
BOOST_AUTO_TEST_CASE( map_adapter)
{

   using my_map = std::map< int, std::string>;
   using my_adapter = KeyValueContainerAdapter< my_map>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, true);

   my_map      m;
   my_adapter  cam( m);

   BOOST_REQUIRE( cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 0);
   BOOST_REQUIRE( !cam.contains( 42));

   cam.addValue( 42, "hello");

   BOOST_REQUIRE( !cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 1);
   BOOST_REQUIRE( cam.contains( 42));

   BOOST_REQUIRE( !m.empty());
   BOOST_REQUIRE_EQUAL( m.size(), 1);

   BOOST_REQUIRE_NO_THROW( cam.clear());

   BOOST_REQUIRE( cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 0);
   BOOST_REQUIRE( !cam.contains( 42));

   BOOST_REQUIRE( m.empty());
   BOOST_REQUIRE_EQUAL( m.size(), 0);

   cam.addValue( 42, "hello");
   cam.addValue( 13, "hi");
   cam.addValue( 17, "ciao");
   cam.addValue( 9, "howdy");

   BOOST_REQUIRE_EQUAL( cam.toString(),
      R"({ 9, "howdy"}, { 13, "hi"}, { 17, "ciao"}, { 42, "hello"})");

} // map_adapter



/// Check the features of the container adapter for multi-maps.
/// Also test that the values are stored in the destination map.
///
/// @since  1.41.0, 15.03.2020
BOOST_AUTO_TEST_CASE( multi_map_adapter)
{

   using my_map = std::multimap< int, std::string>;
   using my_adapter = KeyValueContainerAdapter< my_map>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, true);

   my_map      m;
   my_adapter  cam( m);

   BOOST_REQUIRE( cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 0);
   BOOST_REQUIRE( !cam.contains( 42));

   cam.addValue( 42, "hello");

   BOOST_REQUIRE( !cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 1);
   BOOST_REQUIRE( cam.contains( 42));

   BOOST_REQUIRE( !m.empty());
   BOOST_REQUIRE_EQUAL( m.size(), 1);

   BOOST_REQUIRE_NO_THROW( cam.clear());

   BOOST_REQUIRE( cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 0);
   BOOST_REQUIRE( !cam.contains( 42));

   BOOST_REQUIRE( m.empty());
   BOOST_REQUIRE_EQUAL( m.size(), 0);

   cam.addValue( 42, "hello");
   cam.addValue( 13, "hi");
   cam.addValue( 17, "ciao");
   cam.addValue( 9, "howdy");

   BOOST_REQUIRE_EQUAL( cam.toString(),
      R"({ 9, "howdy"}, { 13, "hi"}, { 17, "ciao"}, { 42, "hello"})");

} // multi_map_adapter



/// Check the features of the container adapter for unordered maps.
/// Also test that the values are stored in the destination map.
///
/// @since  1.41.0, 18.03.2020
BOOST_AUTO_TEST_CASE( unordered_map_adapter)
{

   using my_map = std::unordered_map< int, std::string>;
   using my_adapter = KeyValueContainerAdapter< my_map>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_map      m;
   my_adapter  cam( m);

   BOOST_REQUIRE( cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 0);
   BOOST_REQUIRE( !cam.contains( 42));

   cam.addValue( 42, "hello");

   BOOST_REQUIRE( !cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 1);
   BOOST_REQUIRE( cam.contains( 42));

   BOOST_REQUIRE( !m.empty());
   BOOST_REQUIRE_EQUAL( m.size(), 1);

   BOOST_REQUIRE_NO_THROW( cam.clear());

   BOOST_REQUIRE( cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 0);
   BOOST_REQUIRE( !cam.contains( 42));

   BOOST_REQUIRE( m.empty());
   BOOST_REQUIRE_EQUAL( m.size(), 0);

   cam.addValue( 42, "hello");
   cam.addValue( 13, "hi");
   cam.addValue( 17, "ciao");
   cam.addValue( 9, "howdy");

   // since the order in the string may change ...
   auto const&  result = cam.toString();
   BOOST_REQUIRE( result.find( R"({ 9, "howdy"})") != std::string::npos);
   BOOST_REQUIRE( result.find( R"({ 13, "hi"})") != std::string::npos);
   BOOST_REQUIRE( result.find( R"({ 17, "ciao"})") != std::string::npos);
   BOOST_REQUIRE( result.find( R"({ 42, "hello"})") != std::string::npos);

} // unordered_map_adapter



/// Check the features of the container adapter for unordered multi-maps.
/// Also test that the values are stored in the destination map.
///
/// @since  1.41.0, 18.03.2020
BOOST_AUTO_TEST_CASE( unordered_multi_map_adapter)
{

   using my_map = std::unordered_multimap< int, std::string>;
   using my_adapter = KeyValueContainerAdapter< my_map>;

   static_assert( my_adapter::HasAdapter);
   BOOST_REQUIRE_EQUAL( my_adapter::HasAdapter, true);
   BOOST_REQUIRE_EQUAL( my_adapter::HasIterators, true);
   BOOST_REQUIRE_EQUAL( my_adapter::AllowsPositionFormat, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSortable, false);
   BOOST_REQUIRE_EQUAL( my_adapter::IsSorted, false);

   my_map      m;
   my_adapter  cam( m);

   BOOST_REQUIRE( cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 0);
   BOOST_REQUIRE( !cam.contains( 42));

   cam.addValue( 42, "hello");

   BOOST_REQUIRE( !cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 1);
   BOOST_REQUIRE( cam.contains( 42));

   BOOST_REQUIRE( !m.empty());
   BOOST_REQUIRE_EQUAL( m.size(), 1);

   BOOST_REQUIRE_NO_THROW( cam.clear());

   BOOST_REQUIRE( cam.empty());
   BOOST_REQUIRE_EQUAL( cam.size(), 0);
   BOOST_REQUIRE( !cam.contains( 42));

   BOOST_REQUIRE( m.empty());
   BOOST_REQUIRE_EQUAL( m.size(), 0);

   cam.addValue( 42, "hello");
   cam.addValue( 13, "hi");
   cam.addValue( 17, "ciao");
   cam.addValue( 9, "howdy");

   // since the order in the string may change ...
   auto const&  result = cam.toString();
   BOOST_REQUIRE( result.find( R"({ 9, "howdy"})") != std::string::npos);
   BOOST_REQUIRE( result.find( R"({ 13, "hi"})") != std::string::npos);
   BOOST_REQUIRE( result.find( R"({ 17, "ciao"})") != std::string::npos);
   BOOST_REQUIRE( result.find( R"({ 42, "hello"})") != std::string::npos);

} // unordered_multi_map_adapter



/// Test the key-value container adapter with a template.
///
/// @since  1.41.0, 15.02.2020
BOOST_AUTO_TEST_CASE( template_test)
{

   BOOST_REQUIRE( checkContAdapt< std::map>());
   BOOST_REQUIRE( checkContAdapt< std::multimap>());
   BOOST_REQUIRE( checkContAdapt< std::unordered_map>());
   BOOST_REQUIRE( checkContAdapt< std::unordered_multimap>());

} // template_test



// =====  END OF test_key_value_container_adapter_c.cpp  =====

