
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// project includes
#include "celma/common/multiline_string_compare.hpp"


// Boost includes
#define BOOST_TEST_MODULE MultilineStringCompareTest
#include <boost/test/unit_test.hpp>


using celma::common::multilineStringCompare;



/// Test comparison of single-line strings.
/// @since  1.8.0, 24.07.2018
BOOST_AUTO_TEST_CASE( basic_tests)
{

   // compare two empty strings
   {
      std::string  str1;
      std::string  str2;
      std::string::size_type  idx = 0;
      std::string::size_type  line_nbr = 0;
      std::string::size_type  col = 0;

      BOOST_REQUIRE( multilineStringCompare( idx, line_nbr, col, str1, str2));
      BOOST_REQUIRE_EQUAL( idx, 0);
   } // end scope

   // compare two one-line strings that are equal
   {
      std::string  str1( "hello world");
      std::string  str2( "hello world");
      std::string::size_type  idx = 0;
      std::string::size_type  line_nbr = 0;
      std::string::size_type  col = 0;

      BOOST_REQUIRE( multilineStringCompare( idx, line_nbr, col, str1, str2));
      BOOST_REQUIRE_EQUAL( idx, 11);
   } // end scope

   // compare two one-line strings that are not equal (at the end)
   {
      std::string  str1( "hello world");
      std::string  str2( "hello world again");
      std::string::size_type  idx = 0;
      std::string::size_type  line_nbr = 0;
      std::string::size_type  col = 0;

      BOOST_REQUIRE( !multilineStringCompare( idx, line_nbr, col, str1, str2));
      BOOST_REQUIRE_EQUAL( idx, 11);
      BOOST_REQUIRE_EQUAL( line_nbr, 1);
      BOOST_REQUIRE_EQUAL( col, 11);
   } // end scope

} // basic_tests



/// Test comparison of multi-line strings.
/// @since  1.8.0, 25.07.2018
BOOST_AUTO_TEST_CASE( multi_line_strings)
{

   // compare two two-line, equal strings
   {
      std::string  str1( "The quick brown fox\njumps over the fence");
      std::string  str2( str1);
      std::string::size_type  idx = 0;
      std::string::size_type  line_nbr = 0;
      std::string::size_type  col = 0;

      BOOST_REQUIRE( multilineStringCompare( idx, line_nbr, col, str1, str2));
      BOOST_REQUIRE_EQUAL( idx, 40);
      BOOST_REQUIRE_EQUAL( line_nbr, 2);
   } // end scope

   // compare two multi-line, equal strings
   {
      std::string  str1( "I need a text\nWith multiple lines\nDidn't know one that fit\nSo I just made one up\n");
      std::string  str2( str1);
      std::string::size_type  idx = 0;
      std::string::size_type  line_nbr = 0;
      std::string::size_type  col = 0;

      BOOST_REQUIRE( multilineStringCompare( idx, line_nbr, col, str1, str2));
      BOOST_REQUIRE_EQUAL( idx, 81);
      BOOST_REQUIRE_EQUAL( line_nbr, 5);
   } // end scope

   // compare two multi-line, different strings
   {
      std::string  str1( "I need a text\nWith multiple lines\nDidn't know one that fit\nSo I just made one up\n");
      std::string  str2( "I need a text\nWith multiples lines\nDidn't know one that fit\nSo I just made one up\n");
      std::string::size_type  idx = 0;
      std::string::size_type  line_nbr = 0;
      std::string::size_type  col = 0;

      BOOST_REQUIRE( !multilineStringCompare( idx, line_nbr, col, str1, str2));
      BOOST_REQUIRE_EQUAL( idx, 27);
      BOOST_REQUIRE_EQUAL( line_nbr, 2);
      BOOST_REQUIRE_EQUAL( col, 13);
   } // end scope

   // compare two multi-line, equal strings (with empty lines)
   {
      std::string  str1( "I need a text\nWith multiple lines\n\nDidn't know one that fit\n\nSo I just made one up\n");
      std::string  str2( str1);
      std::string::size_type  idx = 0;
      std::string::size_type  line_nbr = 0;
      std::string::size_type  col = 0;

      BOOST_REQUIRE( multilineStringCompare( idx, line_nbr, col, str1, str2));
      BOOST_REQUIRE_EQUAL( idx, 83);
      BOOST_REQUIRE_EQUAL( line_nbr, 7);
   } // end scope

} // multi_line_strings



// =====  END OF test_multiline_string_compare.cpp  =====

