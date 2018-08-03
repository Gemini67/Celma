
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module to_string using the Boost.Test module.
**
--*/


// module to test header file include
#include "celma/format/to_string.hpp"


// C++ Standard Library includes
#include <bitset>
#include <list>
#include <map>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE TestToString
#include <boost/test/unit_test.hpp>
#include <utility>


using celma::format::toString;



/// Conversion of ints, boolean values, doubles etc.
///
/// @since  1.8.0, 23.07.2018
BOOST_AUTO_TEST_CASE( test_basics)
{

   {
      bool  flag = false;
      auto  result = toString( flag);

      BOOST_REQUIRE_EQUAL( result, "false");
   } // end scope


   {
      bool  flag = true;
      auto  result = toString( flag);

      BOOST_REQUIRE_EQUAL( result, "true");
   } // end scope


   {
      int   ival = 42;
      auto  result = toString( ival);

      BOOST_REQUIRE_EQUAL( result, "42");
   } // end scope


   {
      double  d = M_PI;
      auto    result = toString( d);

      BOOST_REQUIRE_EQUAL( result, "3.141593");
   } // end scope


   {
      std::string  str( "hello world");
      auto         result = toString( str);

      BOOST_REQUIRE_EQUAL( result, "\"hello world\"");
   } // end scope

} // test_basics



/// Test storing the contents of a vector in a string.
///
/// @since  0.14.3, 20.06.2017
BOOST_AUTO_TEST_CASE( test_vector)
{

   {
      std::vector< int>  data;
      auto               result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "");
   } // end scope

   {
      std::vector< int>  data;

      data.push_back( 3);

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "3");
   } // end scope

   {
      std::vector< int>  data;

      data.push_back( 1);
      data.push_back( 2);

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "1, 2");
   } // end scope

   {
      std::vector< int>  data;

      data.push_back(  2);
      data.push_back(  3);
      data.push_back(  5);
      data.push_back(  7);
      data.push_back( 11);

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "2, 3, 5, 7, 11");
   } // end scope

} // test_vector



/// Test storing the contents of a list in a string.
///
/// @since  0.14.3, 20.06.2017
BOOST_AUTO_TEST_CASE( test_list)
{

   typedef std::pair< int, std::string>  data_t;


   {
      std::list< data_t>  data;

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "");
   } // end scope

   {
      std::list< data_t>  data;

      data.push_back( data_t( 3, std::string( "three")));

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 3, \"three\"}");
   } // end scope

   {
      std::list< data_t>  data;

      data.push_back( data_t( 1, "one"));
      data.push_back( data_t( 5, "five"));

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 1, \"one\"}, { 5, \"five\"}");
   } // end scope

   {
      std::list< data_t>  data;

      data.push_back( data_t(  2, "two"));
      data.push_back( data_t(  3, "three"));
      data.push_back( data_t(  5, "five"));
      data.push_back( data_t(  7, "seven"));
      data.push_back( data_t( 11, "eleven"));

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 2, \"two\"}, { 3, \"three\"}, { 5, \"five\"}, { 7, \"seven\"}, { 11, \"eleven\"}");
   } // end scope

} // test_list



/// Test storing the contents of a map in a string.
///
/// @since  0.14.3, 20.06.2017
BOOST_AUTO_TEST_CASE( test_map)
{

   {
      std::map< int, int>  data;
      auto                 result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "");
   } // end scope

   {
      std::map< int, int>  data;

      data[ 1] = 1;

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 1, 1}");
   } // end scope

   {
      std::map< int, int>  data;

      data[ 1] = 1;
      data[ 2] = 4;

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 1, 1}, { 2, 4}");
   } // end scope

   {
      std::map< int, int>  data;

      data[ 1] =  2;
      data[ 2] =  3;
      data[ 3] =  5;
      data[ 4] =  7;
      data[ 5] = 11;

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 1, 2}, { 2, 3}, { 3, 5}, { 4, 7}, { 5, 11}");
   } // end scope

} // test_map



/// Test storing the contents of a multi-map in a string.
///
/// @since  1.1, 17.11.2015
BOOST_AUTO_TEST_CASE( test_multimap)
{

   typedef  std::multimap< int, std::string>  cont_t;

   {
      cont_t  data;
      auto    result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "");
   } // end scope

   {
      cont_t  data;

      data.insert( cont_t::value_type( 1, "one"));

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 1, \"one\"}");
   } // end scope

   {
      cont_t  data;

      data.insert( cont_t::value_type( 1, "one"));
      data.insert( cont_t::value_type( 2, "four"));

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 1, \"one\"}, { 2, \"four\"}");
   } // end scope

   {
      cont_t  data;

      data.insert( cont_t::value_type( 1, "two"));
      data.insert( cont_t::value_type( 2, "three"));
      data.insert( cont_t::value_type( 3, "five"));
      data.insert( cont_t::value_type( 4, "seven"));
      data.insert( cont_t::value_type( 5, "eleven"));

      auto  result = toString( data.begin(), data.end());

      BOOST_REQUIRE_EQUAL( result, "{ 1, \"two\"}, { 2, \"three\"}, { 3, \"five\"}, { 4, \"seven\"}, { 5, \"eleven\"}");
   } // end scope

} // test_map



/// Test converting the contents of a bitset.
///
/// @since  1.8.0, 05.07.2018
BOOST_AUTO_TEST_CASE( bitset_to_string)
{

   // empty bitset
   {
      std::bitset< 10>  bs;
      const auto        str( toString( bs));

      BOOST_REQUIRE_EQUAL( str, "0000000000");
   } // end scope

   // two bits set
   {
      std::bitset< 12>  bs;

      bs[0] = true;
      bs[11] = true;

      const auto  str( toString( bs));

      BOOST_REQUIRE_EQUAL( str, "100000000001");
   } // end scope

   // all bits set
   {
      std::bitset< 8>  bs;

      bs.flip();

      const auto  str( toString( bs));

      BOOST_REQUIRE_EQUAL( str, "11111111");
   } // end scope

} // bitset_to_string



/// Test converting the contents of a tuple.
///
/// @since  1.8.0, 05.07.2018
BOOST_AUTO_TEST_CASE( tuple_to_string)
{

   // tuple with one value
   {
      std::tuple< int>  tpl( 10);
      const auto        str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "10");
   } // end scope

   // tuple with two values
   {
      std::tuple< int, std::string>  tpl( 10, "hello world");
      const auto                     str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "10, \"hello world\"");
   } // end scope

   // tuple with three values
   {
      std::tuple< double, int, std::string>  tpl( M_PI, 10, "hello world");
      const auto                             str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "3.141593, 10, \"hello world\"");
   } // end scope

} // tuple_to_string



// =====  END OF test_to_string.cpp  =====

