
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
**    Test program for the module "container traits", using the Boost.Test
**    framework.
**
--*/


// module to test headerfile include
#include "celma/common/container_traits.hpp"


// C++ Standard Library includes
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ContainerTraitsTest
#include <boost/test/unit_test.hpp>



/// Verify trait "container is sorted".
/// @since  x.y.z, 21.03.2020
BOOST_AUTO_TEST_CASE( trait_sorted)
{

   using celma::common::is_ordered;


   using map_t = std::map< int, std::string>;
   static_assert( is_ordered< std::map< int, std::string>>::value, "error");
   BOOST_REQUIRE( is_ordered< map_t>::value);

   using multimap_t = std::multimap< int, std::string>;
   static_assert( is_ordered< std::multimap< int, std::string>>::value, "error");
   BOOST_REQUIRE( is_ordered< multimap_t>::value);

   static_assert( is_ordered< std::set< int>>::value, "error");
   BOOST_REQUIRE( is_ordered< std::set< int>>::value);

   static_assert( is_ordered< std::multiset< int>>::value, "error");
   BOOST_REQUIRE( is_ordered< std::multiset< int>>::value);

   // unordered container(s)
   using unordered_map_t = std::unordered_map< int, std::string>;
   static_assert( !is_ordered< std::unordered_map< int, std::string>>::value, "error");
   BOOST_REQUIRE( !is_ordered< unordered_map_t>::value);

   static_assert( !is_ordered< std::vector< int>>::value, "error");
   BOOST_REQUIRE( !is_ordered< std::vector< int>>::value);

} // trait_sorted



/// Verify trait "has key/value".
/// @since  x.y.z, 21.03.2020
BOOST_AUTO_TEST_CASE( trait_has_key_value)
{

   using celma::common::has_key_value;


   using map_t = std::map< int, std::string>;
   static_assert( has_key_value< std::map< int, std::string>>::value, "error");
   BOOST_REQUIRE( has_key_value< map_t>::value);

   using multimap_t = std::multimap< int, std::string>;
   static_assert( has_key_value< std::multimap< int, std::string>>::value, "error");
   BOOST_REQUIRE( has_key_value< multimap_t>::value);

   using unordered_map_t = std::unordered_map<int, std::string>;
   static_assert( has_key_value< std::unordered_map<int, std::string>>::value, "error");
   BOOST_REQUIRE( has_key_value< unordered_map_t>::value);

   using unordered_multimap_t = std::unordered_multimap< int, std::string>;
   static_assert( has_key_value< std::unordered_multimap< int, std::string>>::value, "error");
   BOOST_REQUIRE( has_key_value< unordered_multimap_t>::value);

   // container without keys
   static_assert( !has_key_value< std::set< int>>::value, "error");
   BOOST_REQUIRE( !has_key_value< std::set< int>>::value);

   static_assert( !has_key_value< std::multiset< int>>::value, "error");
   BOOST_REQUIRE( !has_key_value< std::multiset< int>>::value);

   static_assert( !has_key_value< std::vector< int>>::value, "error");
   BOOST_REQUIRE( !has_key_value< std::vector< int>>::value);

} // trait_has_key_value



// =====  END OF test_container_traits.cpp  =====

