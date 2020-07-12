
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the module to_string using the Boost.Test module.
**
--*/


// module to test headerfile include
#include "celma/format/to_string.hpp"


// OS/C lib includes
#include <cmath>


// C++ Standard Library includes
#include <bitset>
#include <list>
#include <map>
#include <numeric>
#include <stack>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE TestToString
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/container/dynamic_bitset.hpp"
#include "celma/prog_args/detail/usage_params.hpp"


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

   {
      const auto  result = toString(
         celma::prog_args::detail::UsageParams::Contents::shortOnly);

      BOOST_REQUIRE_EQUAL( result, "short only (1)");
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

   using data_t = std::pair< int, std::string>;


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

   using cont_t = std::multimap< int, std::string>;

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

} // test_multimap



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

      bs[ 0] = true;
      bs[ 11] = true;

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

   // a large bitset
   {
      std::bitset< 1024>  bs;

      const auto         str( toString( bs));
      const std::string  result( 1024, '0');

      BOOST_REQUIRE_EQUAL( str, result);
   } // end scope

} // bitset_to_string



/// Test converting the contents of a vector of booleans.
///
/// @since  1.40.0, 04.06.2020
BOOST_AUTO_TEST_CASE( vector_bool_to_string)
{

   // empty vector
   {
      std::vector< bool>  vb;
      const auto          str( toString( vb));

      BOOST_REQUIRE_EQUAL( str, "0");
   } // end scope

   // two bits set
   {
      std::vector< bool>  vb;

      vb.resize( 20);

      vb[ 0] = true;
      vb[ 11] = true;

      const auto  str( toString( vb));

      BOOST_REQUIRE_EQUAL( str, "00000000100000000001");
   } // end scope

   // all bits set
   {
      std::vector< bool>  vb;

      vb.resize( 10);

      vb.flip();

      const auto  str( toString( vb));

      BOOST_REQUIRE_EQUAL( str, "1111111111");
   } // end scope

   // a large vector
   {
      std::vector< bool>  vb;

      vb.resize( 1024);

      const auto         str( toString( vb));
      const std::string  result( 1024, '0');

      BOOST_REQUIRE_EQUAL( str, result);
   } // end scope

} // vector_bool_to_string



/// Test converting the contents of a dynamic bitset.
///
/// @since  1.37.0, 17.06.2020
BOOST_AUTO_TEST_CASE( dynamic_bitset_to_string)
{

   using celma::container::DynamicBitset;

   // empty bitset
   {
      DynamicBitset  dbs( 10);
      const auto     str( toString( dbs));

      BOOST_REQUIRE_EQUAL( str, "0000000000");
   } // end scope

   // two bits set
   {
      DynamicBitset  dbs( 12);

      dbs[ 0] = true;
      dbs[ 11] = true;

      const auto  str( toString( dbs));

      BOOST_REQUIRE_EQUAL( str, "100000000001");
   } // end scope

   // all bits set
   {
      DynamicBitset  dbs( 8);

      dbs.flip();

      const auto  str( toString( dbs));

      BOOST_REQUIRE_EQUAL( str, "11111111");
   } // end scope

   // a large bitset
   {
      DynamicBitset  dbs( 1024);

      const auto         str( toString( dbs));
      const std::string  result( 1024, '0');

      BOOST_REQUIRE_EQUAL( str, result);
   } // end scope

} // dynamic_bitset_to_string



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

   // tuple with another single value
   {
      std::tuple< int64_t>  tpl( 10'750'382'826);
      const auto            str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "10750382826");
   } // end scope

   // tuple with another single value
   {
      std::tuple< uint64_t>  tpl( std::numeric_limits< uint64_t>::max());
      const auto             str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "18446744073709551615");
   } // end scope

   // tuple with two values
   {
      std::tuple< int, std::string>  tpl( 10, "hello world");
      const auto                     str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "10, \"hello world\"");
   } // end scope

   // tuple with other two values
   {
      std::tuple< int, int>  tpl( 13, 4711);
      const auto             str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "13, 4711");
   } // end scope

   // tuple with three values
   {
      std::tuple< double, int, std::string>  tpl( M_PI, 10, "hello world");
      const auto                             str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "3.141593, 10, \"hello world\"");
   } // end scope

   // tuple with three other values
   {
      std::tuple< int, int, int>  tpl( 13, 42, 4711);
      const auto                  str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "13, 42, 4711");
   } // end scope

   // tuple with three other values
   {
      std::tuple< int, std::string, int>  tpl( 13, "hello world", 42);
      const auto                          str( toString( tpl));

      BOOST_REQUIRE_EQUAL( str, "13, \"hello world\", 42");
   } // end scope

} // tuple_to_string



/// Test converting the contents of a stack.
///
/// @since  1.34.0, 20.11.2019
BOOST_AUTO_TEST_CASE( stack_to_string)
{

   // stack with one value
   {
      std::stack< int>  stck;

      stck.push( 13);

      const auto  str( toString( stck));

      BOOST_REQUIRE_EQUAL( str, "13");
   } // end scope

   // stack with two values
   {
      std::stack< int>  stck;

      stck.push( 42);
      stck.push( 13);

      const auto  str( toString( stck));

      BOOST_REQUIRE_EQUAL( str, "13, 42");
   } // end scope

   // hold on: stack with four values
   {
      std::stack< int>  stck;

      stck.push( 4711);
      stck.push( 42);
      stck.push( 28);
      stck.push( 13);

      const auto  str( toString( stck));

      BOOST_REQUIRE_EQUAL( str, "13, 28, 42, 4711");
   } // end scope

   // stack of strings
   {
      std::stack< std::string>  stck;

      stck.push( "show");
      stck.push( "the");
      stck.push( "for");
      stck.push( "two");
      stck.push( "money");
      stck.push( "the");
      stck.push( "for");
      stck.push( "one");

      const auto  str( toString( stck));

      BOOST_REQUIRE_EQUAL( str,
         R"raw("one", "for", "the", "money", "two", "for", "the", "show")raw");
   } // end scope

} // stack_to_string



/// Test converting the contents of a priority_queue.
///
/// @since  1.34.0, 29.12.2019
BOOST_AUTO_TEST_CASE( priority_queue_to_string)
{

   // priority queue with one value
   {
      std::priority_queue< int>  pq;

      pq.push( 13);

      const auto  str( toString( pq));

      BOOST_REQUIRE_EQUAL( str, "13");
   } // end scope

   // priority queue with two values
   {
      std::priority_queue< int>  pq;

      pq.push( 42);
      pq.push( 13);

      const auto  str( toString( pq));

      BOOST_REQUIRE_EQUAL( str, "42, 13");
   } // end scope

   // hold on: priority queue with four values
   {
      std::priority_queue< int>  pq;

      pq.push( 28);
      pq.push( 4711);
      pq.push( 13);
      pq.push( 42);

      const auto  str( toString( pq));

      BOOST_REQUIRE_EQUAL( str, "4711, 42, 28, 13");
   } // end scope

   // priority queue of strings
   {
      std::priority_queue< std::string>  pq;

      pq.push( "I");
      pq.push( "Will");
      pq.push( "Win");

      const auto  str( toString( pq));

      BOOST_REQUIRE_EQUAL( str, R"raw("Win", "Will", "I")raw");
   } // end scope

} // priority_queue_to_string



/// Test converting the contents of a queue.
///
/// @since  1.34.0, 29.12.2019
BOOST_AUTO_TEST_CASE( queue_to_string)
{

   // queue with one value
   {
      std::queue< int>  q;

      q.push( 13);

      const auto  str( toString( q));

      BOOST_REQUIRE_EQUAL( str, "13");
   } // end scope

   // queue with two values
   {
      std::queue< int>  q;

      q.push( 42);
      q.push( 13);

      const auto  str( toString( q));

      BOOST_REQUIRE_EQUAL( str, "42, 13");
   } // end scope

   // hold on: queue with four values
   {
      std::queue< int>  q;

      q.push( 28);
      q.push( 4711);
      q.push( 13);
      q.push( 42);

      const auto  str( toString( q));

      BOOST_REQUIRE_EQUAL( str, "28, 4711, 13, 42");
   } // end scope

   // queue of strings
   {
      std::queue< std::string>  q;

      q.push( "I");
      q.push( "Will");
      q.push( "Win");

      const auto  str( toString( q));

      BOOST_REQUIRE_EQUAL( str, R"raw("I", "Will", "Win")raw");
   } // end scope

} // queue_to_string



// =====  END OF test_to_string.cpp  =====

