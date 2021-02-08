
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test headerfile include
#include "celma/common/fixed_string.hpp"


// C++ Standard Library includes
#include <sstream>
#include <stdexcept>
#include <string>


// Boost includes
#define BOOST_TEST_MODULE FixedStringTest
#include <boost/test/unit_test.hpp>


using celma::common::FixedString;



/// Construct fixed strings.
/// @since  x.y.z, 13.01.2021
BOOST_AUTO_TEST_CASE( constructor)
{

   // check size to prove that the string is within the object and not only the
   // pointer to the object
   {
      const FixedString< 20>  fs;

      // size = 20 characters + trailing zero + length variable
      BOOST_REQUIRE_EQUAL( sizeof( fs), 20 + 1 + sizeof( uint8_t));
   } // end scope

   // check size to prove that the string is within the object and not only the
   // pointer to the object
   {
      const FixedString< 500>  fs;

      // size = 20 characters + trailing zero + padding + length variable
      BOOST_REQUIRE_EQUAL( sizeof( fs), 500 + 1 + 1 + sizeof( uint16_t));
   } // end scope

   // empty string
   {
      const FixedString< 20>  fs;

      BOOST_REQUIRE_EQUAL( fs.length(), 0);
      BOOST_REQUIRE_EQUAL( fs.str(), "");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "");
      BOOST_REQUIRE_EQUAL( fs.data(), "");

      // try to copy
      const FixedString< 20>  fs_copy( fs);
      BOOST_REQUIRE_EQUAL( fs, fs_copy);
   } // end scope

   // short C string
   {
      const FixedString< 20>  fs( "hello world");

      BOOST_REQUIRE_EQUAL( fs.length(), 11);
      BOOST_REQUIRE_EQUAL( fs.str(), "hello world");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "hello world");
      BOOST_REQUIRE_EQUAL( fs.data(), "hello world");

      std::ostringstream  oss;
      oss << fs;
      BOOST_REQUIRE_EQUAL( oss.str(), "'hello world'");
   } // end scope

   // long C string that is truncated
   {
      const FixedString< 20>  fs( "hello world and thank you for all the fish");

      BOOST_REQUIRE_EQUAL( fs.length(), 20);
      BOOST_REQUIRE_EQUAL( fs.str(), "hello world and than");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "hello world and than");
   } // end scope

   // short std::string
   {
      const std::string       str( "Hello world");
      const FixedString< 20>  fs( str);

      BOOST_REQUIRE_EQUAL( fs.length(), 11);
      BOOST_REQUIRE_EQUAL( fs.str(), "Hello world");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "Hello world");

      // copy into object with larger buffer
      const FixedString< 100>  fs_copy( fs);
      BOOST_REQUIRE_EQUAL( fs, fs_copy);
   } // end scope

   // long std::string that is truncated
   {
      const std::string       str( "Hello world and thank you for all the fish");
      const FixedString< 20>  fs( str);

      BOOST_REQUIRE_EQUAL( fs.length(), 20);
      BOOST_REQUIRE_EQUAL( fs.str(), "Hello world and than");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "Hello world and than");

      // copy into object with smaller buffer
      const FixedString< 10>  fs_copy( fs);
      BOOST_REQUIRE_EQUAL( fs_copy.length(), 10);
      BOOST_REQUIRE_EQUAL( fs_copy.str(), "Hello worl");
      BOOST_REQUIRE( fs != fs_copy);
   } // end scope

} // constructor



/// Test assigning a string.
/// @since  x.y.z, 13.01.2021
BOOST_AUTO_TEST_CASE( assign)
{

   // assign a longer string from a C string
   {
      FixedString< 20>  fs( "hello world");

      fs.assign( "goodbye again");

      BOOST_REQUIRE_EQUAL( fs.length(), 13);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye again");

      // also test clear function
      fs.clear();
      BOOST_REQUIRE_EQUAL( fs.length(), 0);
      BOOST_REQUIRE( fs.str().empty());
   } // end scope

   // assign a longer string from a std::string
   {
      FixedString< 20>  fs( "hello world");

      fs.assign( std::string( "goodbye again"));

      BOOST_REQUIRE_EQUAL( fs.length(), 13);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye again");
   } // end scope

   // assign a longer string from another fixed string
   {
      FixedString< 20>  fs( "hello world");
      FixedString< 20>  fs_new( "goodbye again");

      fs.assign( fs_new);

      BOOST_REQUIRE_EQUAL( fs.length(), 13);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye again");
      BOOST_REQUIRE_EQUAL( fs, fs_new);
   } // end scope

   // assign a longer string from another fixed string with a different buffer
   // size
   {
      FixedString< 20>  fs( "hello world");
      FixedString< 50>  fs_new( "goodbye again");

      fs.assign( fs_new);

      BOOST_REQUIRE_EQUAL( fs.length(), 13);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye again");
      BOOST_REQUIRE_EQUAL( fs, fs_new);
   } // end scope

   // assign a shorter string from a C string
   {
      FixedString< 20>  fs( "hello world");

      fs.assign( "goodbye");

      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // assign a shorter string from a std::string
   {
      FixedString< 20>  fs( "hello world");

      fs.assign( std::string( "goodbye"));

      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // assign a shorter string from another fixed string
   {
      FixedString< 20>  fs( "hello world");
      FixedString< 20>  fs_new( "goodbye");

      fs.assign( fs_new);

      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
      BOOST_REQUIRE_EQUAL( fs, fs_new);
   } // end scope

   // assign a shorter string from another fixed string with a different buffer
   // size
   {
      FixedString< 20>  fs( "hello world");
      FixedString< 50>  fs_new( "goodbye");

      fs.assign( fs_new);

      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
      BOOST_REQUIRE_EQUAL( fs, fs_new);
   } // end scope

} // assign



/// Test assigning a string using the assignment operator.
/// @since  x.y.z, 14.01.2021
BOOST_AUTO_TEST_CASE( assign_operator)
{

   // assign a longer string from a C string
   {
      FixedString< 20>  fs( "hello world");

      fs = "goodbye again";

      BOOST_REQUIRE_EQUAL( fs.length(), 13);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye again");

      // also test clear function
      fs.clear();
      BOOST_REQUIRE_EQUAL( fs.length(), 0);
      BOOST_REQUIRE( fs.str().empty());
   } // end scope

   // assign a longer string from a std::string
   {
      FixedString< 20>  fs( "hello world");

      fs = std::string( "goodbye again");

      BOOST_REQUIRE_EQUAL( fs.length(), 13);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye again");
   } // end scope

   // assign a longer string from another fixed string
   {
      FixedString< 20>  fs( "hello world");
      FixedString< 20>  fs_new( "goodbye again");

      fs = fs_new;

      BOOST_REQUIRE_EQUAL( fs.length(), 13);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye again");
      BOOST_REQUIRE_EQUAL( fs, fs_new);
   } // end scope

   // assign a longer string from another fixed string with a different buffer
   // size
   {
      FixedString< 20>  fs( "hello world");
      FixedString< 50>  fs_new( "goodbye again");

      fs = fs_new;

      BOOST_REQUIRE_EQUAL( fs.length(), 13);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye again");
      BOOST_REQUIRE_EQUAL( fs, fs_new);
   } // end scope

   // assign a shorter string from a C string
   {
      FixedString< 20>  fs( "hello world");

      fs = "goodbye";

      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // assign a shorter string from a std::string
   {
      FixedString< 20>  fs( "hello world");

      fs = std::string( "goodbye");

      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // assign a shorter string from another fixed string
   {
      FixedString< 20>  fs( "hello world");
      FixedString< 20>  fs_new( "goodbye");

      fs = fs_new;

      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
      BOOST_REQUIRE_EQUAL( fs, fs_new);
   } // end scope

   // assign a shorter string from another fixed string with a different buffer
   // size
   {
      FixedString< 20>  fs( "hello world");
      FixedString< 50>  fs_new( "goodbye");

      fs = fs_new;

      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
      BOOST_REQUIRE_EQUAL( fs, fs_new);
   } // end scope

} // assign_operator



/// Test assigning a string using the assignment operator.
/// @since  x.y.z, 14.01.2021
BOOST_AUTO_TEST_CASE( element_access)
{

   // at with empty string
   {
      FixedString< 50>  fs;

      BOOST_REQUIRE_EQUAL( fs.at( 0), '\0');
      BOOST_REQUIRE_THROW( fs.at( 1), std::out_of_range);
   } // end scope

   // at with empty const string
   {
      const FixedString< 50>  fs;

      BOOST_REQUIRE_EQUAL( fs.at( 0), '\0');
      BOOST_REQUIRE_THROW( fs.at( 1), std::out_of_range);
   } // end scope

   // operator [] with empty string
   {
      FixedString< 50>  fs;

      BOOST_REQUIRE_EQUAL( fs[ 0], '\0');
   } // end scope

   // operator [] with empty const string
   {
      const FixedString< 50>  fs;

      BOOST_REQUIRE_EQUAL( fs[ 0], '\0');
   } // end scope

   // at with string
   {
      FixedString< 50>  fs( "Goodbye and thank you for all the fish");

      BOOST_REQUIRE_EQUAL( fs.at( 0), 'G');
      BOOST_REQUIRE_EQUAL( fs.at( 7), ' ');
      BOOST_REQUIRE_EQUAL( fs.at( fs.length() - 1), 'h');
      BOOST_REQUIRE_EQUAL( fs.at( fs.length()), '\0');

      BOOST_REQUIRE_THROW( fs.at( fs.length() + 1), std::out_of_range);
   } // end scope

   // at with const string
   {
      const FixedString< 50>  fs( "Goodbye and thank you for all the fish");

      BOOST_REQUIRE_EQUAL( fs.at( 0), 'G');
      BOOST_REQUIRE_EQUAL( fs.at( 7), ' ');
      BOOST_REQUIRE_EQUAL( fs.at( fs.length() - 1), 'h');
      BOOST_REQUIRE_EQUAL( fs.at( fs.length()), '\0');

      BOOST_REQUIRE_THROW( fs.at( fs.length() + 1), std::out_of_range);
   } // end scope

   // operator [] with string
   {
      FixedString< 50>  fs( "Goodbye and thank you for all the fish");

      BOOST_REQUIRE_EQUAL( fs[ 0], 'G');
      BOOST_REQUIRE_EQUAL( fs[ 7], ' ');
      BOOST_REQUIRE_EQUAL( fs[ fs.length() - 1], 'h');
      BOOST_REQUIRE_EQUAL( fs[ fs.length()], '\0');
   } // end scope

   // operator [] with const string
   {
      const FixedString< 50>  fs( "Goodbye and thank you for all the fish");

      BOOST_REQUIRE_EQUAL( fs[ 0], 'G');
      BOOST_REQUIRE_EQUAL( fs[ 7], ' ');
      BOOST_REQUIRE_EQUAL( fs[ fs.length() - 1], 'h');
      BOOST_REQUIRE_EQUAL( fs[ fs.length()], '\0');
   } // end scope

   // front with empty string
   {
      FixedString< 50>  fs;

      BOOST_REQUIRE_EQUAL( fs.front(), '\0');
   } // end scope

   // front with empty const string
   {
      const FixedString< 50>  fs;

      BOOST_REQUIRE_EQUAL( fs.front(), '\0');
   } // end scope

   // back with empty string
   {
      FixedString< 50>  fs;

      BOOST_REQUIRE_EQUAL( fs.back(), '\0');
   } // end scope

   // back with empty const string
   {
      const FixedString< 50>  fs;

      BOOST_REQUIRE_EQUAL( fs.back(), '\0');
   } // end scope

   // front with string
   {
      FixedString< 50>  fs( "Goodbye");

      BOOST_REQUIRE_EQUAL( fs.front(), 'G');

      fs.front() = 'g';
      BOOST_REQUIRE_EQUAL( fs.data(), "goodbye");
   } // end scope

   // front with const string
   {
      const FixedString< 50>  fs( "Goodbye");

      BOOST_REQUIRE_EQUAL( fs.front(), 'G');
   } // end scope

   // back with string
   {
      FixedString< 50>  fs( "Goodbye");

      BOOST_REQUIRE_EQUAL( fs.back(), 'e');

      fs.back() = 'E';
      BOOST_REQUIRE_EQUAL( fs.data(), "GoodbyE");
   } // end scope

   // back with const string
   {
      const FixedString< 50>  fs( "Goodbye");

      BOOST_REQUIRE_EQUAL( fs.back(), 'e');
   } // end scope

} // element_access



/// Verify that the correct iterators are returned by the begin/end methods.
/// @since  x.y.z, 22.01.2021
BOOST_AUTO_TEST_CASE( iterators)
{

   FixedString< 50>  fs( "hello world");

   {
      auto  iter = fs.begin();

      BOOST_REQUIRE_EQUAL( *iter, 'h');

      iter += 11;
      BOOST_REQUIRE( iter == fs.end());
   } // end scope

   {
      auto const  copy( fs);
      auto        iter = copy.begin();

      BOOST_REQUIRE_EQUAL( *iter, 'h');

      iter += 11;
      BOOST_REQUIRE( iter == copy.end());
   } // end scope

   {
      auto const  copy( fs);
      auto        iter = copy.cbegin();

      BOOST_REQUIRE_EQUAL( *iter, 'h');

      iter += 11;
      BOOST_REQUIRE( iter == copy.cend());
   } // end scope

   {
      auto  iter = fs.rbegin();

      BOOST_REQUIRE_EQUAL( *iter, 'd');

      iter += 11;
      BOOST_REQUIRE( iter == fs.rend());
   } // end scope

   {
      auto const  copy( fs);
      auto        iter = copy.rbegin();

      BOOST_REQUIRE_EQUAL( *iter, 'd');

      iter += 11;
      BOOST_REQUIRE( iter == copy.rend());
   } // end scope

   {
      auto const  copy( fs);
      auto        iter = copy.crbegin();

      BOOST_REQUIRE_EQUAL( *iter, 'd');

      iter += 11;
      BOOST_REQUIRE( iter == copy.crend());
   } // end scope

   {
      size_t  found = 0;

      for (auto & iter : fs)
      {
         if (iter != '\0')
            ++found;
      } // end for

      BOOST_REQUIRE_EQUAL( found, 11);
   } // end scope

   {
      auto const  copy( fs);
      size_t      found = 0;

      for (auto const& iter : copy)
      {
         if (iter != '\0')
            ++found;
      } // end for

      BOOST_REQUIRE_EQUAL( found, 11);
   } // end scope

   BOOST_REQUIRE_EQUAL( fs.end() - fs.begin(), 11);
   BOOST_REQUIRE_EQUAL( fs.cend() - fs.cbegin(), 11);

   BOOST_REQUIRE_EQUAL( fs.begin() - fs.begin(), 0);
   BOOST_REQUIRE_EQUAL( fs.cbegin() - fs.cbegin(), 0);
   BOOST_REQUIRE_EQUAL( fs.end() - fs.end(), 0);
   BOOST_REQUIRE_EQUAL( fs.cend() - fs.cend(), 0);

   BOOST_REQUIRE_EQUAL( fs.rend() - fs.rbegin(), 11);
   BOOST_REQUIRE_EQUAL( fs.crend() - fs.crbegin(), 11);

   BOOST_REQUIRE_EQUAL( fs.rbegin() - fs.rbegin(), 0);
   BOOST_REQUIRE_EQUAL( fs.rend() - fs.rend(), 0);
   BOOST_REQUIRE_EQUAL( fs.crbegin() - fs.crbegin(), 0);
   BOOST_REQUIRE_EQUAL( fs.crend() - fs.crend(), 0);

} // iterators



/// Insert a repetition of a single character into a fixed string.
/// @since  x.y.z, 14.01.2021
BOOST_AUTO_TEST_CASE( insert_char_repetition)
{

   // insert into empty string
   {
      FixedString< 50>  fs;

      fs.insert( 0, 5, 'a');

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into empty string with wrong index
   {
      FixedString< 50>  fs;

      fs.insert( 10, 5, 'a');

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into empty string with count > length
   {
      FixedString< 10>  fs;

      fs.insert( 0, 20, 'a');

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaaaaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaaaaaaa");
   } // end scope

   // insert into empty string with count > length and wrong index
   {
      FixedString< 10>  fs;

      fs.insert( 10, 20, 'a');

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaaaaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaaaaaaa");
   } // end scope

   // insert into string
   {
      FixedString< 50>  fs( "Gdbye");

      fs.insert( 1, 2, 'o');

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string would exceed length
   {
      FixedString< 5>  fs( "Gdbye");

      fs.insert( 1, 2, 'o');

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodb");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodb");
   } // end scope

   // insert into string 1 character before end
   {
      FixedString< 50>  fs( "Goodbe");

      fs.insert( 5, 1, 'y');

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string at end
   {
      FixedString< 50>  fs( "Goodby");

      fs.insert( 6, 1, 'e');

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string after end
   {
      FixedString< 50>  fs( "Goodbye");

      fs.insert( 20, 3, '!');

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye!!!");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye!!!");
   } // end scope

   // insert into full string
   {
      FixedString< 8>  fs( "Gdbye!__");

      fs.insert( 1, 2, 'o');

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye!");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye!");
   } // end scope

   // insert into full string, only 1 character possible
   {
      FixedString< 7>  fs( "Goodby_");

      fs.insert( 6, 5, 'e');

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into full string at end: nothing is inserted
   {
      FixedString< 7>  fs( "Goodbye");

      fs.insert( 7, 5, '!');

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert using an invalid iterator for the position
   {
      FixedString< 50>  fs( "goobye");

      fs.insert( fs.cend(), 'd');
      BOOST_REQUIRE_EQUAL( fs.str(), "goobye");
   } // end scope

   // insert using an iterator for the position
   {
      FixedString< 50>  fs( "goobye");
      auto              iter = fs.cbegin();

      iter += 3;
      auto result = fs.insert( iter, 'd');
      BOOST_REQUIRE_EQUAL( *iter, 'd');
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // insert using an invalid iterator for the position --> insert nothing
   {
      FixedString< 50>  fs( "goodby");

      fs.insert( fs.cend(), 1, 'e');
      BOOST_REQUIRE_EQUAL( fs.str(), "goodby");
   } // end scope

   // insert using an iterator for the position
   {
      FixedString< 50>  fs( "gdbye");
      auto              iter = fs.cbegin();

      ++iter;
      auto result = fs.insert( iter, 2, 'o');
      BOOST_REQUIRE_EQUAL( *iter, 'o');
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

} // insert_char_repetition



/// Insert a C string into a fixed string.
/// @since  x.y.z, 14.01.2021
BOOST_AUTO_TEST_CASE( insert_c_string)
{

   // insert into empty string
   {
      FixedString< 50>  fs;

      fs.insert( 0, "aaaaa");

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into empty string with wrong index
   {
      FixedString< 50>  fs;

      fs.insert( 10, "aaaaa");

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into empty string with string length > length
   {
      FixedString< 10>  fs;

      fs.insert( 0, "abcdefghijklmnopqrstuvwxyz");

      BOOST_REQUIRE_EQUAL( fs.str(), "abcdefghij");
      BOOST_REQUIRE_EQUAL( fs.data(), "abcdefghij");
   } // end scope

   // insert into empty string with string length > length and wrong index
   {
      FixedString< 10>  fs;

      fs.insert( 10, "abcdefghijklmnopqrstuvwxyz");

      BOOST_REQUIRE_EQUAL( fs.str(), "abcdefghij");
      BOOST_REQUIRE_EQUAL( fs.data(), "abcdefghij");
   } // end scope

   // insert into string
   {
      FixedString< 50>  fs( "Gdbye");

      fs.insert( 1, "oo");

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string would exceed length
   {
      FixedString< 5>  fs( "Gdbye");

      fs.insert( 1, "oo");

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodb");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodb");
   } // end scope

   // insert into string 1 character before end
   {
      FixedString< 50>  fs( "Goodbe");

      fs.insert( 5, "y");

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string at end
   {
      FixedString< 50>  fs( "Goodby");

      fs.insert( 6, "e");

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string after end
   {
      FixedString< 50>  fs( "Goodbye");

      fs.insert( 20, "!!!");

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye!!!");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye!!!");
   } // end scope

   // insert into full string
   {
      FixedString< 8>  fs( "Gdbye!__");

      fs.insert( 1, "oo");

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye!");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye!");
   } // end scope

   // insert into full string, only 1 character possible
   {
      FixedString< 7>  fs( "Goodby_");

      fs.insert( 6, "eeeee");

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into full string at end: nothing is inserted
   {
      FixedString< 7>  fs( "Goodbye");

      fs.insert( 7, "!!!!!");

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

} // insert_c_string



/// Insert a part of a C string into a fixed string.
/// @since  x.y.z, 14.01.2021
BOOST_AUTO_TEST_CASE( insert_c_string_part)
{

   // insert into empty string
   {
      FixedString< 50>  fs;

      fs.insert( 0, "aaaaabcde", 5);

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into empty string with wrong index
   {
      FixedString< 50>  fs;

      fs.insert( 10, "aaaaabcde", 5);

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into empty string with string length > length
   {
      FixedString< 10>  fs;

      fs.insert( 0, "abcdefghijklmnopqrstuvwxyz", 15);

      BOOST_REQUIRE_EQUAL( fs.str(), "abcdefghij");
      BOOST_REQUIRE_EQUAL( fs.data(), "abcdefghij");
   } // end scope

   // insert into empty string with string length > length and wrong index
   {
      FixedString< 10>  fs;

      fs.insert( 10, "abcdefghijklmnopqrstuvwxyz", 15);

      BOOST_REQUIRE_EQUAL( fs.str(), "abcdefghij");
      BOOST_REQUIRE_EQUAL( fs.data(), "abcdefghij");
   } // end scope

   // insert into string
   {
      FixedString< 50>  fs( "Gdbye");

      fs.insert( 1, "oouuu", 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string would exceed length
   {
      FixedString< 5>  fs( "Gdbye");

      fs.insert( 1, "oouuu", 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodb");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodb");
   } // end scope

   // insert into string 1 character before end
   {
      FixedString< 50>  fs( "Goodbe");

      fs.insert( 5, "y!__", 1);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string at end
   {
      FixedString< 50>  fs( "Goodby");

      fs.insert( 6, "e!__", 1);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string after end
   {
      FixedString< 50>  fs( "Goodbye");

      fs.insert( 20, "!!!1elf!!", 3);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye!!!");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye!!!");
   } // end scope

   // insert into full string
   {
      FixedString< 8>  fs( "Gdbye!__");

      fs.insert( 1, "oouuu", 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye!");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye!");
   } // end scope

   // insert into full string, only 1 character possible
   {
      FixedString< 7>  fs( "Goodby_");

      fs.insert( 6, "eeeee", 3);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into full string at end: nothing is inserted
   {
      FixedString< 7>  fs( "Goodbye");

      fs.insert( 7, "!!!!!", 3);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

} // insert_c_string_part



/// Insert a std::string into a fixed string.
/// @since  x.y.z, 14.01.2021
BOOST_AUTO_TEST_CASE( insert_std_string)
{

   // insert into empty string
   {
      FixedString< 50>  fs;

      fs.insert( 0, std::string( "aaaaa"));

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into empty string with wrong index
   {
      FixedString< 50>  fs;

      fs.insert( 10, std::string( "aaaaa"));

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into empty string with string length > length
   {
      FixedString< 10>  fs;

      fs.insert( 0, std::string( "abcdefghijklmnopqrstuvwxyz"));

      BOOST_REQUIRE_EQUAL( fs.str(), "abcdefghij");
      BOOST_REQUIRE_EQUAL( fs.data(), "abcdefghij");
   } // end scope

   // insert into empty string with string length > length and wrong index
   {
      FixedString< 10>  fs;

      fs.insert( 10, std::string( "abcdefghijklmnopqrstuvwxyz"));

      BOOST_REQUIRE_EQUAL( fs.str(), "abcdefghij");
      BOOST_REQUIRE_EQUAL( fs.data(), "abcdefghij");
   } // end scope

   // insert into string
   {
      FixedString< 50>  fs( "Gdbye");

      fs.insert( 1, std::string( "oo"));

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string would exceed length
   {
      FixedString< 5>  fs( "Gdbye");

      fs.insert( 1, std::string( "oo"));

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodb");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodb");
   } // end scope

   // insert into string 1 character before end
   {
      FixedString< 50>  fs( "Goodbe");

      fs.insert( 5, std::string( "y"));

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string at end
   {
      FixedString< 50>  fs( "Goodby");

      fs.insert( 6, std::string( "e"));

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into string after end
   {
      FixedString< 50>  fs( "Goodbye");

      fs.insert( 20, std::string( "!!!"));

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye!!!");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye!!!");
   } // end scope

   // insert into full string
   {
      FixedString< 8>  fs( "Gdbye!__");

      fs.insert( 1, std::string( "oo"));

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye!");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye!");
   } // end scope

   // insert into full string, only 1 character possible
   {
      FixedString< 7>  fs( "Goodby_");

      fs.insert( 6, std::string( "eeeee"));

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // insert into full string at end: nothing is inserted
   {
      FixedString< 7>  fs( "Goodbye");

      fs.insert( 7, std::string( "!!!!!"));

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

} // insert_std_string



/// Insert a part of a std::string into a fixed string.
/// This results in a call to insert of an std::string, so there is no need to
/// test all cases again.
/// @since  x.y.z, 15.01.2021
BOOST_AUTO_TEST_CASE( insert_std_string_part)
{

   // insert into empty string
   {
      FixedString< 50>  fs;

      fs.insert( 0, std::string( "xaaaaax"), 1, 5);

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into string 1 character before end
   {
      FixedString< 50>  fs( "Goodbe");

      fs.insert( 5, std::string( "xyx"), 1, 1);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

} // insert_std_string_part



/// Insert a fixed string into a fixed string.
/// This results in a call to insert of C string with given length, so there is
/// no need to test all cases again.
/// @since  x.y.z, 15.01.2021
BOOST_AUTO_TEST_CASE( insert_fixed_string)
{

   // insert into empty string
   {
      FixedString< 50>  fs;
      FixedString< 10>  fs_ins( "aaaaa");

      fs.insert( 0, fs_ins);

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into string would exceed length
   {
      FixedString< 5>  fs( "Gdbye");
      FixedString< 2>  fs_ins( "oo");

      fs.insert( 1, fs_ins);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodb");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodb");
   } // end scope

   // insert after end of string --> append
   {
      FixedString< 50>  fs( "Goodbye");
      FixedString< 20>  fs_ins( " and fish");

      fs.insert( 20, fs_ins);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye and fish");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye and fish");
   } // end scope

} // insert_fixed_string



/// Insert a part of a fixed string into a fixed string.
/// This results in a call to insert of a C string, so there is no need to test
/// all cases again.
/// @since  x.y.z, 15.01.2021
BOOST_AUTO_TEST_CASE( insert_fixed_string_part)
{

   // insert into empty string
   {
      FixedString< 50>  fs;
      FixedString< 10>  fs_ins( "xaaaaax");

      fs.insert( 0, fs_ins, 1, 5);

      BOOST_REQUIRE_EQUAL( fs.str(), "aaaaa");
      BOOST_REQUIRE_EQUAL( fs.data(), "aaaaa");
   } // end scope

   // insert into string 1 character before end
   {
      FixedString< 50>  fs( "Goodbe");
      FixedString< 3>   fs_ins( "xyx");

      fs.insert( 5, fs_ins, 1, 1);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

   // index of insert string after end of insert-string
   {
      FixedString< 50>  fs( "Goodbye");
      FixedString< 20>  fs_ins( " and fish");

      fs.insert( 7, fs_ins, 20);

      BOOST_REQUIRE_EQUAL( fs.str(), "Goodbye");
      BOOST_REQUIRE_EQUAL( fs.data(), "Goodbye");
   } // end scope

} // insert_fixed_string_part



/// Insert an initializer list.
/// @since  x.y.z, 25.01.2021
BOOST_AUTO_TEST_CASE( insert_std_initializer_list)
{

   // insert empty initializer list == nothing
   {
      FixedString< 50>              fs( "bye");
      std::initializer_list< char>  ilist;

      fs.insert( fs.cbegin(), ilist);

      BOOST_REQUIRE_EQUAL( fs.str(), "bye");
   } // end scope

   // insert at end == insertz nothing
   {
      FixedString< 50>              fs( "good");
      std::initializer_list< char>  ilist = { 'b', 'y', 'e' };

      fs.insert( fs.cend(), ilist);

      BOOST_REQUIRE_EQUAL( fs.str(), "good");
   } // end scope

   // insert at the beginning
   {
      FixedString< 50>              fs( "bye");
      std::initializer_list< char>  ilist = { 'g', 'o', 'o', 'd' };

      fs.insert( fs.cbegin(), ilist);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // insert only part because of limited length
   {
      FixedString< 4>               fs( "goye");
      std::initializer_list< char>  ilist = { 'o', 'd', 'b' };
      auto                          first = fs.cbegin();

      first += 2;
      fs.insert( first, ilist);

      BOOST_REQUIRE_EQUAL( fs.str(), "good");
   } // end scope

   // insert at end fails because string is already full
   {
      FixedString< 4>               fs( "good");
      std::initializer_list< char>  ilist = { 'b', 'y', 'e' };

      fs.insert( fs.cend(), ilist);

      BOOST_REQUIRE_EQUAL( fs.str(), "good");
   } // end scope

} // insert_std_initializer_list



/// Erase a part of a string.
/// @since  x.y.z, 15.01.2021
BOOST_AUTO_TEST_CASE( erase)
{

   // erase from empty string
   {
      FixedString< 50>  fs;

      fs.erase( 2, 10);
      BOOST_REQUIRE( fs.empty());
      BOOST_REQUIRE_EQUAL( fs.length(), 0);
   } // end scope

   // erase behind end of string
   {
      FixedString< 50>  fs( "goodbye and thank you for all the fish");

      fs.erase( 38, 10);
      BOOST_REQUIRE_EQUAL( fs.length(), 38);
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye and thank you for all the fish");
   } // end scope

   // erase at the beginning of the string
   {
      FixedString< 50>  fs( "goodbye and thank you for all the fish");

      fs.erase( 0, 12);
      BOOST_REQUIRE_EQUAL( fs.length(), 26);
      BOOST_REQUIRE_EQUAL( fs.c_str(), "thank you for all the fish");
   } // end scope

   // erase at the end of the string
   {
      FixedString< 50>  fs( "goodbye and thank you for all the fish");

      fs.erase( 7);
      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye");
   } // end scope

   // erase a part within the string
   {
      FixedString< 50>  fs( "goodbye and thank you for all the fish");

      fs.erase( 18, 16);
      BOOST_REQUIRE_EQUAL( fs.length(), 22);
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye and thank fish");
   } // end scope

   // erase all
   {
      FixedString< 50>  fs( "goodbye and thank you for all the fish");

      fs.erase();
      BOOST_REQUIRE( fs.empty());
      BOOST_REQUIRE_EQUAL( fs.length(), 0);
   } // end scope

   // erase last character with iterator
   {
      FixedString< 50>  fs( "g");
      auto              iter = fs.cbegin();

      auto  result = fs.erase( iter);
      BOOST_REQUIRE( fs.empty());
      BOOST_REQUIRE( result == fs.end());
   } // end scope

   // erase one character with iterator
   {
      FixedString< 50>  fs( "gooodbye");
      auto              iter = fs.cbegin();

      iter += 3;

      auto  result = fs.erase( iter);
      BOOST_REQUIRE_EQUAL( *result, *iter);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // erase last characters with iterator
   {
      FixedString< 50>  fs( "good");
      auto              first = fs.cbegin();
      auto              result = fs.erase( first, fs.cend());

      BOOST_REQUIRE( fs.empty());
      BOOST_REQUIRE( result == fs.end());
   } // end scope

   // erase characters with iterator
   {
      FixedString< 50>  fs( "goodbye");
      auto              first = fs.cbegin();
      auto              last( first);

      last += 4;

      auto  result = fs.erase( first, last);
      BOOST_REQUIRE( result == fs.begin());
      BOOST_REQUIRE_EQUAL( fs.str(), "bye");
   } // end scope

   // erase after end == nothing with iterator
   {
      FixedString< 50>  fs( "goodbye");
      auto              result = fs.erase( fs.cend());

      BOOST_REQUIRE( !fs.empty());
      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE( result == fs.end());
   } // end scope

   // erase nothing with iterators
   {
      FixedString< 50>  fs( "goodbye");

      auto  result = fs.erase( fs.cbegin(), fs.cbegin());
      BOOST_REQUIRE( !fs.empty());
      BOOST_REQUIRE_EQUAL( fs.length(), 7);
      BOOST_REQUIRE( result == fs.end());
   } // end scope

} // erase



/// Push and pop characters.
/// @since  x.y.z, 15.01.2021
BOOST_AUTO_TEST_CASE( push_and_pop)
{

   // push some more characters
   {
      FixedString< 7>  fs( "good");

      fs.push_back( 'b');
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodb");

      fs.push_back( 'y');
      fs.push_back( 'e');
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye");

      fs.push_back( 'x');
      fs.push_back( 'x');
      fs.push_back( 'x');

      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye");
   } // end scope

   // pop some characters away
   {
      FixedString< 7>  fs( "good");

      fs.pop_back();
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goo");

      fs.pop_back();
      fs.pop_back();
      BOOST_REQUIRE_EQUAL( fs.c_str(), "g");

      fs.pop_back();
      BOOST_REQUIRE( fs.empty());

      fs.pop_back();
      BOOST_REQUIRE( fs.empty());
   } // end scope

} // push_and_pop



/// Append to an existing fixed string.
/// @since  x.y.z, 15.01.2021
BOOST_AUTO_TEST_CASE( append)
{

   // append to an empty string with not enough space
   {
      FixedString< 4>  fs;

      fs.append( "goodbye");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "good");
   } // end scope

   // append to an empty string
   {
      FixedString< 20>  fs;

      fs.append( "goodbye");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye");
   } // end scope

   // append
   {
      FixedString< 4>  fs( "good");

      fs.append( "bye");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "good");
   } // end scope

   // append to string that's already at maximal length
   {
      FixedString< 10>  fs( "good");

      fs.append( "bye");
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye");
   } // end scope

   // append a part of a string
   {
      FixedString< 50>  fs( "goodbye and");

      fs.append( "farewell and thank you for all the fish in the market", 12, 27);
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye and thank you for all the fish");
   } // end scope

   // no space to append character repetition
   {
      FixedString< 7>  fs( "goodbye");

      fs.append( 3, '!');
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye");
   } // end scope

   // append character repetition
   {
      FixedString< 50>  fs( "goodbye");

      fs.append( 3, '!');
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye!!!");
   } // end scope

   // append a fixed string
   {
      FixedString< 50>        fs( "goodbye");
      const FixedString< 50>  fs_append( " and farewell");

      fs.append( fs_append);
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye and farewell");
   } // end scope

   // append a part of a fixed string
   {
      FixedString< 50>        fs( "goodbye");
      const FixedString< 50>  fs_append( "hi-ho and farewell to you");

      fs.append( fs_append, 5, 13);
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye and farewell");
   } // end scope

   // append a part of a C string
   {
      FixedString< 50>  fs( "goodbye");

      fs.append( " and farewell to you", 13);
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye and farewell");
   } // end scope

   // append a part of another fixed string using iterators
   {
      FixedString< 50>  fs( "good");
      FixedString< 50>  source( "xxxbyeyyy");
      auto              first = source.cbegin();

      first += 3;
      auto  last( first);
      last += 3;

      fs.append( first, last);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // append nothing using equal iterators
   {
      FixedString< 50>  fs( "good");
      FixedString< 50>  source( "xxxbyeyyy");

      fs.append( source.cbegin(), source.cbegin());
      BOOST_REQUIRE_EQUAL( fs.str(), "good");
   } // end scope

   // append nothing using iterators since the string is already full
   {
      FixedString< 4>   fs( "good");
      FixedString< 4>  source( "bye");

      fs.append( source.cbegin(), source.cend());
      BOOST_REQUIRE_EQUAL( fs.str(), "good");
   } // end scope

} // append



/// Append to an existing fixed string using the += operator.
/// @since  x.y.z, 18.01.2021
BOOST_AUTO_TEST_CASE( append_operator)
{

   // append to an empty string with not enough space
   {
      FixedString< 4>  fs;

      fs += "goodbye";
      BOOST_REQUIRE_EQUAL( fs.c_str(), "good");
   } // end scope

   // append one character
   {
      FixedString< 20>  fs( "goodbye");

      fs += '!';
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye!");
   } // end scope

   // append a fixed string
   {
      FixedString< 50>  fs( "goodbye");
      FixedString< 20>  fs2( " and farewell");

      fs += fs2;
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye and farewell");
   } // end scope

   // append an std::string
   {
      FixedString< 50>  fs( "goodbye");
      std::string       fs2( " and farewell");

      fs += fs2;
      BOOST_REQUIRE_EQUAL( fs.c_str(), "goodbye and farewell");
   } // end scope

} // append_operator



/// Compare a fixed string with another string.
/// @since  x.y.z, 18.01.2021
BOOST_AUTO_TEST_CASE( compare_all)
{

   // compare two equal fixed strings
   {
      FixedString< 20>  fs( "goodbye");
      FixedString< 50>  fs2( "goodbye");

      BOOST_REQUIRE( fs.compare( fs2) == 0);
      BOOST_REQUIRE( fs2.compare( fs) == 0);
   } // end scope

   // compare two fixed strings that are not equal
   {
      FixedString< 20>  fs( "goodbye");
      FixedString< 50>  fs2( "goodbye!");

      BOOST_REQUIRE( fs.compare( fs2) < 0);
      BOOST_REQUIRE( fs2.compare( fs) > 0);
   } // end scope

   // compare a fixed string against an equal std::string
   {
      FixedString< 20>  fs( "goodbye");
      std::string       str( "goodbye");

      BOOST_REQUIRE( fs.compare( str) == 0);
   } // end scope

   // compare a fixed string against a different std::string
   {
      FixedString< 20>  fs( "goodbye");
      std::string       str( "goodbya");

      BOOST_REQUIRE( fs.compare( str) > 0);
   } // end scope
   {
      FixedString< 20>  fs( "goodbya");
      std::string       str( "goodbye");

      BOOST_REQUIRE( fs.compare( str) < 0);
   } // end scope

   // compare a fixed string against a different std::string
   {
      FixedString< 20>  fs( "goodbye");
      std::string       str( "goodbye!");

      BOOST_REQUIRE( fs.compare( str) < 0);
   } // end scope
   {
      FixedString< 20>  fs( "goodbye!");
      std::string       str( "goodbye");

      BOOST_REQUIRE( fs.compare( str) > 0);
   } // end scope

   // compare a fixed string against an equal C string
   {
      FixedString< 20>  fs( "goodbye");
      char              str[ 20] = { "goodbye" };

      BOOST_REQUIRE( fs.compare( str) == 0);
   } // end scope

   // compare a fixed string against a different C string
   {
      FixedString< 20>  fs( "goodbye");
      char              str[ 20] = { "goodbye!" };

      BOOST_REQUIRE( fs.compare( str) < 0);
   } // end scope
   {
      FixedString< 20>  fs( "goodbye!");
      char              str[ 20] = { "goodbye" };

      BOOST_REQUIRE( fs.compare( str) > 0);
   } // end scope

} // compare_all



/// Compare a part of a fixed string with another string.
/// @since  x.y.z, 18.01.2021
BOOST_AUTO_TEST_CASE( compare_part)
{

   // compare a part of a fixed string against an another fixed string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      FixedString< 20>  fs2( "goodbye");

      BOOST_REQUIRE( fs.compare( 4, 7, fs2) == 0);
   } // end scope

   // compare a part of a fixed string against another fixed string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      FixedString< 20>  fs2( "goodbyx");

      BOOST_REQUIRE( fs.compare( 4, 7, fs2) < 0);
   } // end scope
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      FixedString< 20>  fs2( "goodbya");

      BOOST_REQUIRE( fs.compare( 4, 7, fs2) > 0);
   } // end scope

   // compare a part of a fixed string against another fixed string with a
   // different length
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      FixedString< 20>  fs2( "good");

      BOOST_REQUIRE( fs.compare( 4, 7, fs2) > 0);
   } // end scope

   // compare an invalid part of a fixed string against an another fixed string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      FixedString< 20>  fs2( "goodbye");

      BOOST_REQUIRE( fs.compare( 30, 7, fs2) == 1);
   } // end scope

   // compare a part of a fixed string against an equal std::string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      std::string       fs2( "goodbye");

      BOOST_REQUIRE( fs.compare( 4, 7, fs2) == 0);
   } // end scope

   // compare a part of a fixed string against a different std::string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      std::string       fs2( "goodbyx");

      BOOST_REQUIRE( fs.compare( 4, 7, fs2) < 0);
   } // end scope
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      std::string       fs2( "goodbya");

      BOOST_REQUIRE( fs.compare( 4, 7, fs2) > 0);
   } // end scope

   // compare a part of a fixed string against a std::string with a different
   // length
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      std::string       fs2( "good");

      BOOST_REQUIRE( fs.compare( 4, 7, fs2) > 0);
   } // end scope

   // compare an invalid part of a fixed string against a std::string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      std::string       fs2( "goodbye");

      BOOST_REQUIRE( fs.compare( 30, 7, fs2) == 1);
   } // end scope

   // compare a part of a fixed string against an equal C string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      char              str[ 20] = { "goodbye" };

      BOOST_REQUIRE( fs.compare( 4, 7, str) == 0);
   } // end scope

   // compare a part of a fixed string against a different C string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      char              str[ 20] = { "goodbyx" };

      BOOST_REQUIRE( fs.compare( 4, 7, str) < 0);
   } // end scope
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      char              str[ 20] = { "goodbya" };

      BOOST_REQUIRE( fs.compare( 4, 7, str) > 0);
   } // end scope

   // compare a part of a fixed string against a C string with a different
   // length
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      char              str[ 20] = { "good" };

      BOOST_REQUIRE( fs.compare( 4, 7, str) > 0);
   } // end scope

   // compare an invalid part of a fixed string against a C string
   {
      FixedString< 50>  fs( "so, goodbye and farewell");
      char              str[ 20] = { "goodbye" };

      BOOST_REQUIRE( fs.compare( 30, 7, str) == 1);
   } // end scope

} // compare_part



/// Compare a part of a fixed string with a part of another string.
/// @since  x.y.z, 18.01.2021
BOOST_AUTO_TEST_CASE( compare_part_part)
{

   // compare an invalid part of fixed string against a part of another fixed
   // string
   {
      FixedString< 50>  fs1( "xxgoodbyexx");
      FixedString< 40>  fs2;

      BOOST_REQUIRE( fs1.compare( 20, 7, fs2, 0, 0) == 0);
   } // end scope
   {
      FixedString< 50>  fs1( "xxgoodbyexx");
      FixedString< 40>  fs2;

      BOOST_REQUIRE( fs1.compare( 20, 7, fs2, 1, 2) == 0);
   } // end scope
   {
      FixedString< 50>  fs1( "xxgoodbyexx");
      FixedString< 40>  fs2( "yyyygoodbyeyyyy");

      BOOST_REQUIRE( fs1.compare( 20, 7, fs2, 4, 7) > 0);
   } // end scope
   {
      FixedString< 50>  fs1( "xxgoodbyexx");
      FixedString< 40>  fs2( "yyyygoodbyeyyyy");

      BOOST_REQUIRE( fs1.compare( 20, 7, fs2, 20, 7) == 0);
   } // end scope

   // compare a part of fixed string against an invalid part of another fixed
   // string
   {
      FixedString< 50>  fs1;
      FixedString< 40>  fs2( "yyygoodbyeyyy");

      BOOST_REQUIRE( fs1.compare( 0, 0, fs2, 20, 7) == 0);
   } // end scope
   {
      FixedString< 50>  fs1;
      FixedString< 40>  fs2( "yyygoodbyeyyy");

      BOOST_REQUIRE( fs1.compare( 1, 2, fs2, 20, 7) == 0);
   } // end scope
   {
      FixedString< 50>  fs1( "xxgoodbyexx");
      FixedString< 40>  fs2( "yyyygoodbyeyyyy");

      BOOST_REQUIRE( fs1.compare( 2, 7, fs2, 20, 7) < 0);
   } // end scope

   // compare a part of fixed string against an equal part of another fixed string
   {
      FixedString< 50>  fs1( "xxxgoodbyexxx");
      FixedString< 40>  fs2( "yyyygoodbyeyyyy");

      BOOST_REQUIRE( fs1.compare( 3, 7, fs2, 4, 7) == 0);
   } // end scope
   {
      FixedString< 50>  fs1( "goodbye");
      FixedString< 40>  fs2( "yyygoodbyeyyy");

      BOOST_REQUIRE( fs1.compare( 0, 20, fs2, 3, 7) == 0);
   } // end scope

   // compare a part of fixed string against an equal part of another fixed string
   {
      FixedString< 50>  fs1( "xxgoodbyexx");
      FixedString< 40>  fs2( "goodbye");

      BOOST_REQUIRE( fs1.compare( 2, 7, fs2, 0, 20) == 0);
   } // end scope

   // compare a part of fixed string against a different part of another fixed
   // string
   {
      FixedString< 50>  fs1( "xxxgoodbyexxx");
      FixedString< 40>  fs2( "yyyygoodbye!yyyy");

      BOOST_REQUIRE( fs1.compare( 3, 8, fs2, 4, 8) > 0);
   } // end scope
   {
      FixedString< 50>  fs1( "xxxgoodbye!xxx");
      FixedString< 40>  fs2( "yyyygoodbyeyyyy");

      BOOST_REQUIRE( fs1.compare( 3, 8, fs2, 4, 8) < 0);
   } // end scope

   // compare a part of fixed string against an equal part of a std::string
   {
      FixedString< 50>  fs1( "xxgoodbyexx");
      std::string       str( "goodbye");

      BOOST_REQUIRE( fs1.compare( 2, 7, str, 0, 20) == 0);
   } // end scope

   // compare a part of fixed string against a different part of a std::string
   {
      FixedString< 50>  fs1( "xxxgoodbyexxx");
      std::string       str( "yyyygoodbye!yyyy");

      BOOST_REQUIRE( fs1.compare( 3, 8, str, 4, 8) > 0);
   } // end scope
   {
      FixedString< 50>  fs1( "xxxgoodbye!xxx");
      std::string       str( "yyyygoodbyeyyyy");

      BOOST_REQUIRE( fs1.compare( 3, 8, str, 4, 8) < 0);
   } // end scope

   // compare a part of fixed string against an equal part of a C string
   {
      FixedString< 50>  fs1( "xxgoodbyexx");
      char              str[ 40] = { "goodbye" };

      BOOST_REQUIRE( fs1.compare( 2, 7, str, 20) == 0);
   } // end scope

   // compare a part of fixed string against a different part of a std::string
   {
      FixedString< 50>  fs1( "xxxgoodbyexxx");
      char              str[ 40] = { "yyyygoodbye!yyyy" };

      BOOST_REQUIRE( fs1.compare( 3, 8, &str[ 4], 8) > 0);
   } // end scope
   {
      FixedString< 50>  fs1( "xxxgoodbye!xxx");
      char              str[ 40] = { "yyyygoodbyeyyyy" };

      BOOST_REQUIRE( fs1.compare( 3, 8, &str[ 4], 8) < 0);
   } // end scope

} // compare_part_part



/// Check starts_with.
/// @since  x.y.z, 18.01.2021
BOOST_AUTO_TEST_CASE( starts_with)
{

   // for two empty strings, starts_with returns true
   {
      FixedString< 30>  fs;
      FixedString< 20>  fs2;

      BOOST_REQUIRE( fs.starts_with( fs2));
      BOOST_REQUIRE( fs2.starts_with( fs));
   } // end scope

   // for two strings that start with the same text, starts_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 20>  fs2( "goodbye");

      BOOST_REQUIRE( fs.starts_with( fs2));
      BOOST_REQUIRE( !fs2.starts_with( fs));
   } // end scope

   // for two different strings, starts_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 20>  fs2( "farewell");

      BOOST_REQUIRE( !fs.starts_with( fs2));
      BOOST_REQUIRE( !fs2.starts_with( fs));
   } // end scope

   // for two empty strings, starts_with returns true
   {
      FixedString< 30>  fs;
      std::string       fs2;

      BOOST_REQUIRE( fs.starts_with( fs2));
   } // end scope

   // for two strings that start with the same text, starts_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       fs2( "goodbye");

      BOOST_REQUIRE( fs.starts_with( fs2));
   } // end scope

   // for two different strings, starts_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       fs2( "farewell");

      BOOST_REQUIRE( !fs.starts_with( fs2));
   } // end scope

   // for two empty strings, starts_with returns true
   {
      FixedString< 30>  fs;
      char              fs2[ 20] = { "" };

      BOOST_REQUIRE( fs.starts_with( fs2));
   } // end scope

   // for two strings that start with the same text, starts_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              fs2[ 20] = { "goodbye" };

      BOOST_REQUIRE( fs.starts_with( fs2));
   } // end scope

   // for two different strings, starts_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              fs2[ 20] = { "farewell" };

      BOOST_REQUIRE( !fs.starts_with( fs2));
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");

      BOOST_REQUIRE( fs.starts_with( 'g'));
      BOOST_REQUIRE( !fs.starts_with( 'f'));
   } // end scope

} // starts_with



/// Check ends_with.
/// @since  x.y.z, 20.01.2021
BOOST_AUTO_TEST_CASE( ends_with)
{

   // for two empty strings, ends_with returns true
   {
      FixedString< 30>  fs;
      FixedString< 20>  fs2;

      BOOST_REQUIRE( fs.ends_with( fs2));
      BOOST_REQUIRE( fs2.ends_with( fs));
   } // end scope

   // for two strings that end with the same text, ends_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 20>  fs2( "farewell");

      BOOST_REQUIRE( fs.ends_with( fs2));
      BOOST_REQUIRE( !fs2.ends_with( fs));
   } // end scope

   // for two different strings, ends_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 20>  fs2( "goodbye");

      BOOST_REQUIRE( !fs.ends_with( fs2));
      BOOST_REQUIRE( !fs2.ends_with( fs));
   } // end scope

   // for two empty strings, ends_with returns true
   {
      FixedString< 30>  fs;
      std::string       fs2;

      BOOST_REQUIRE( fs.ends_with( fs2));
   } // end scope

   // for two strings that start with the same text, ends_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       fs2( "farewell");

      BOOST_REQUIRE( fs.ends_with( fs2));
   } // end scope

   // for two different strings, ends_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       fs2( "goodbye");

      BOOST_REQUIRE( !fs.ends_with( fs2));
   } // end scope

   // for two empty strings, ends_with returns true
   {
      FixedString< 30>  fs;
      char              fs2[ 20] = { "" };

      BOOST_REQUIRE( fs.ends_with( fs2));
   } // end scope

   // for two strings that start with the same text, ends_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              fs2[ 20] = { "farewell" };

      BOOST_REQUIRE( fs.ends_with( fs2));
   } // end scope

   // for two different strings, ends_with returns true
   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              fs2[ 20] = { "goodbye" };

      BOOST_REQUIRE( !fs.ends_with( fs2));
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");

      BOOST_REQUIRE( fs.ends_with( 'l'));
      BOOST_REQUIRE( !fs.ends_with( 'e'));
   } // end scope

} // ends_with



/// Check contains.
/// @since  x.y.z, 20.01.2021
BOOST_AUTO_TEST_CASE( contains)
{

   // always returns false for empty strings
   {
      FixedString< 30>  fs( "hello world");
      FixedString< 20>  fs2;

      BOOST_REQUIRE( !fs.contains( fs2));
      BOOST_REQUIRE( !fs2.contains( fs));
   } // end scope

   // string contains other string
   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 20>  fs2( "and");

      BOOST_REQUIRE( fs.contains( fs2));
      BOOST_REQUIRE( !fs2.contains( fs));
   } // end scope

   // string does not contain other string
   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 20>  fs2( "hello");

      BOOST_REQUIRE( !fs.contains( fs2));
      BOOST_REQUIRE( !fs2.contains( fs));
   } // end scope

   // contains other string at the beginning
   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       fs2( "goodbye");

      BOOST_REQUIRE( fs.contains( fs2));
   } // end scope

   // contains other string at the end
   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       fs2( "farewell");

      BOOST_REQUIRE( fs.contains( fs2));
   } // end scope

   // contains other string at the end
   {
      FixedString< 30>  fs( "goodbye");

      BOOST_REQUIRE( fs.contains( "e"));
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");

      BOOST_REQUIRE( fs.contains( 'a'));
      BOOST_REQUIRE( !fs.contains( 'x'));
   } // end scope

} // contains



/// Check replace.
/// @since  x.y.z, 20.01.2021
BOOST_AUTO_TEST_CASE( replace)
{

   // replace after end of string actually appends nothing
   {
      FixedString< 30>  fs( "goodbye");
      FixedString< 20>  fs2( " and farewell");

      fs.replace( 20, 10, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "goodbye");
      FixedString< 50>  fs2( " and farewell and thank you for all the fish");

      fs.replace( 20, 5, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace a string by a string with the same length
   {
      FixedString< 30>  fs( "goodbyexxxxxfarewell");
      FixedString< 20>  fs2( " and ");

      fs.replace( 7, 5, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope
   {
      FixedString< 30>  fs( "goodbye xxx farewell");
      FixedString< 20>  fs2( "and");

      fs.replace( 8, 3, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope
   {
      FixedString< 30>  fs( "goodbye and farewellx");
      FixedString< 20>  fs2( "!");

      fs.replace( 20, 1, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell!");
   } // end scope
   {
      FixedString< 30>  fs( "goodbye!");
      FixedString< 20>  fs2( "farewell");

      fs.replace( 0, 20, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "farewell");
   } // end scope

   // replace a string by a shorter string
   {
      FixedString< 30>  fs( "goodbye xxxxxx farewell");
      FixedString< 20>  fs2( "and");

      fs.replace( 8, 6, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope
   {
      FixedString< 30>  fs( "goodbyexxxxxx");
      FixedString< 20>  fs2( "!");

      fs.replace( 7, 20, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye!");
   } // end scope

   // replace a string by a longer string
   {
      FixedString< 30>  fs( "goodbye x farewell");
      FixedString< 20>  fs2( "and");

      fs.replace( 8, 1, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope
   {
      FixedString< 30>  fs( "x");
      FixedString< 20>  fs2( "goodbye and farewell");

      fs.replace( 0, 1, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope

   // replace the rest of a string
   {
      FixedString< 30>  fs( "goodbye x");
      FixedString< 20>  fs2( " and farewell");

      fs.replace( 7, 3, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope

   // replace the rest of a string with a string that is too long
   {
      FixedString< 30>  fs( "goodbye xx");
      FixedString< 50>  fs2( " and farewell and thank you for all the fish");

      fs.replace( 7, 3, fs2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell and thank");
   } // end scope

   // replace with a std::string
   {
      FixedString< 30>  fs( "goodbye");
      std::string       str( " and farewell");

      fs.replace( 20, 10, str);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "goodbyexxxxxfarewell");
      std::string       str( " and ");

      fs.replace( 7, 5, str);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope
   {
      FixedString< 30>  fs( "goodbyexxxxxx");
      std::string       str( "!");

      fs.replace( 7, 20, str);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye!");
   } // end scope
   {
      FixedString< 30>  fs( "x");
      std::string       str( "goodbye and farewell");

      fs.replace( 0, 1, str);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope
   // replace the rest of a string
   {
      FixedString< 30>  fs( "goodbye x");
      std::string       str( " and farewell");

      fs.replace( 7, 3, str);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye and farewell");
   } // end scope

} // replace



/// Replace a part of a string with a part of another string.
/// @since  x.y.z, 20.01.2021
BOOST_AUTO_TEST_CASE( replace_part)
{

   // replace parts of same length
   {
      FixedString< 30>  fs( "gooxxye");
      FixedString< 20>  fs2( "xxdbxx");

      fs.replace( 3, 2, fs2, 2, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace with a longer part
   {
      FixedString< 30>  fs( "gxe");
      FixedString< 20>  fs2( "xxoodbyxx");

      fs.replace( 1, 1, fs2, 2, 5);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gxe");
      FixedString< 20>  fs2( "xxoodby");

      fs.replace( 1, 1, fs2, 2, 20);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gxe");
      FixedString< 20>  fs2( "xxoodby");

      fs.replace( 1, 1, fs2, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace with a shorter part
   {
      FixedString< 30>  fs( "gooxxxxxye");
      FixedString< 20>  fs2( "yyyyydbyyy");

      fs.replace( 3, 5, fs2, 5, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxxye");
      FixedString< 20>  fs2( "yyyyydb");

      fs.replace( 3, 5, fs2, 5, 20);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // invalid start position does not replace anything
   {
      FixedString< 30>  fs( "gooxxxxxye");
      FixedString< 20>  fs2( "yyyyydb");

      fs.replace( 3, 5, fs2, 20, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxxye");
   } // end scope

   // replace parts of same length
   {
      FixedString< 30>  fs( "gooxxye");
      std::string       str( "xxdbxx");

      fs.replace( 3, 2, str, 2, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace with a longer part
   {
      FixedString< 30>  fs( "gxe");
      std::string       str( "xxoodby");

      fs.replace( 1, 1, str, 2, 20);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace with a shorter part
   {
      FixedString< 30>  fs( "gooxxxxxye");
      std::string       str( "yyyyydbyyy");

      fs.replace( 3, 5, str, 5, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // invalid start position does not replace anything
   {
      FixedString< 30>  fs( "gooxxxxxye");
      std::string       str( "yyyyydb");

      fs.replace( 3, 5, str, 20, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxxye");
   } // end scope

   // replace parts of same length
   {
      FixedString< 30>  fs( "gooxxye");
      char              str[ 20] = { "dbxx" };

      fs.replace( 3, 2, str, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace with a longer part
   {
      FixedString< 30>  fs( "gxe");
      char              str[ 20] = { "oodby" };

      fs.replace( 1, 1, str);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace with a shorter part
   {
      FixedString< 30>  fs( "gooxxxxxye");
      char              str[ 20] = { "dbyyy" };

      fs.replace( 3, 5, str, 2);

      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace a part using invalid iterators --> replaces nothing
   {
      FixedString< 30>  fs( "gooxxxxxye");
      FixedString< 30>  src( "xxxdbyyy");

      fs.replace( fs.cbegin(), fs.cbegin(), src.begin(), src.end());
      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxxye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxxye");
      FixedString< 30>  src( "xxxdbyyy");

      fs.replace( fs.cend(), fs.cbegin(), src.begin(), src.end());
      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxxye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxxye");
      FixedString< 30>  src( "xxxdbyyy");
      auto              rep_last = src.cbegin();

      rep_last += 4;
      fs.replace( fs.cbegin(), rep_last, src.begin(), src.begin());
      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxxye");
   } // end scope

   // replace a part using iterators
   {
      FixedString< 30>  fs( "gooxxxxxye");
      FixedString< 30>  src( "db");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();

      rep_first += 3;
      rep_last += 8;

      fs.replace( rep_first, rep_last, src.begin(), src.end());
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "goodx");
      FixedString< 30>  src( "bye");
      auto              rep_first = fs.cbegin();

      rep_first += 4;

      fs.replace( rep_first, fs.cend(), src.begin(), src.end());
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxxye");
      FixedString< 30>  src( "xxxdbyyy");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();
      auto              src_first = src.begin();
      auto              src_last = src.begin();

      rep_first += 3;
      rep_last += 8;
      src_first += 3;
      src_last += 5;

      fs.replace( rep_first, rep_last, src_first, src_last);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace a part by a part of a std::string using iterators
   {
      FixedString< 30>  fs( "gooxxxxxye");
      std::string       src( "db");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();

      rep_first += 3;
      rep_last += 8;

      fs.replace( rep_first, rep_last, src.begin(), src.begin());
      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxxye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxxye");
      std::string       src( "db");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();

      rep_first += 3;
      rep_last += 8;

      fs.replace( rep_first, rep_last, src.begin(), src.end());
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "goodx");
      std::string       src( "bye");
      auto              rep_first = fs.cbegin();

      rep_first += 4;

      fs.replace( rep_first, fs.cend(), src.begin(), src.end());
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxxye");
      std::string       src( "xxxdbyyy");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();
      auto              src_first = src.begin();
      auto              src_last = src.begin();

      rep_first += 3;
      rep_last += 8;
      src_first += 3;
      src_last += 5;

      fs.replace( rep_first, rep_last, src_first, src_last);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope

   // replace a part using iterators and a C string
   {
      FixedString< 30>  fs( "gooxxxxxye");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();

      rep_first += 3;
      rep_last += 8;
      fs.replace( rep_first, rep_last, "db");
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxxye");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();

      rep_first += 3;
      rep_last += 8;
      fs.replace( rep_first, rep_last, "dbxxxx", 2);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxx");
      auto              rep_first = fs.cbegin();

      rep_first += 3;
      fs.replace( rep_first, fs.cend(), "dbye");
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxx");

      fs.replace( fs.cend(), fs.cend(), "dbye");
      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxx");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxx");
      auto              rep_first = fs.cbegin();

      rep_first += 3;
      fs.replace( rep_first, fs.cend(), nullptr);
      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxx");
   } // end scope
   {
      FixedString< 30>  fs( "gooxxxxx");
      auto              rep_first = fs.cbegin();

      rep_first += 3;
      fs.replace( rep_first, fs.cend(), "");
      BOOST_REQUIRE_EQUAL( fs.str(), "gooxxxxx");
   } // end scope

   // replace a part of a string by a repetition of a character
   {
      FixedString< 30>  fs( "gxdbye");

      fs.replace( 1, 1, 2, 'o');
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gxdbye");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();

      rep_first += 1;
      rep_last += 2;

      fs.replace( rep_first, rep_last, 2, 'o');
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>  fs( "gxdbye");

      fs.replace( fs.cbegin(), fs.cbegin(), 2, 'o');
      BOOST_REQUIRE_EQUAL( fs.str(), "gxdbye");
   } // end scope
   {
      FixedString< 30>  fs( "gxdbye");
      auto              rep_first = fs.cbegin();
      auto              rep_last = fs.cbegin();

      rep_first += 1;
      rep_last += 2;

      fs.replace( rep_first, rep_last, 0, 'o');
      BOOST_REQUIRE_EQUAL( fs.str(), "gxdbye");
   } // end scope

   // replace a part of a string with an initializer list
   {
      FixedString< 30>              fs( "gxdbye");
      std::initializer_list< char>  ilist = { 'o', 'o' };
      auto                          rep_first = fs.cbegin();
      auto                          rep_last = fs.cbegin();

      rep_first += 1;
      rep_last += 2;

      fs.replace( rep_first, rep_last, ilist);
      BOOST_REQUIRE_EQUAL( fs.str(), "goodbye");
   } // end scope
   {
      FixedString< 30>              fs( "gxdbye");
      std::initializer_list< char>  ilist;
      auto                          rep_first = fs.cbegin();
      auto                          rep_last = fs.cbegin();

      rep_first += 1;
      rep_last += 2;

      fs.replace( rep_first, rep_last, ilist);
      BOOST_REQUIRE_EQUAL( fs.str(), "gxdbye");
   } // end scope
   {
      FixedString< 30>              fs( "gxdbye");
      std::initializer_list< char>  ilist = { 'o', 'o' };

      fs.replace( fs.cbegin(), fs.cbegin(), ilist);
      BOOST_REQUIRE_EQUAL( fs.str(), "gxdbye");
   } // end scope

} // replace_part



/// Check that the correct substring is returned.
/// @since  x.y.z, 25.01.2021
BOOST_AUTO_TEST_CASE( sub_str)
{

   FixedString< 30>  fs( "goodbye and farewell");

   {
      auto  sub = fs.substr( 0);
      BOOST_REQUIRE_EQUAL( sub, "goodbye and farewell");
   } // end scope

   {
      auto  sub = fs.substr( 8, 3);
      BOOST_REQUIRE_EQUAL( sub, "and");
   } // end scope

   {
      auto  sub = fs.substr( 12);
      BOOST_REQUIRE_EQUAL( sub, "farewell");
   } // end scope

   {
      auto  sub = fs.substr( 30);
      BOOST_REQUIRE( sub.empty());
   } // end scope

   {
      auto  sub = fs.substr( 12, 0);
      BOOST_REQUIRE( sub.empty());
   } // end scope

} // sub_str



/// Checks the copy() function.
/// @since  x.y.z, 25.01.2021
BOOST_AUTO_TEST_CASE( copy_str)
{

   FixedString< 30>  fs( "goodbye and farewell");

   {
      char  dest[ 30 ] = { "goodbye xxx farewell" };
      BOOST_REQUIRE( fs.copy( &dest[ 8], 3, 8) == 3);
      BOOST_REQUIRE( ::strcmp( fs.c_str(), dest) == 0);
   } // end scope

   {
      char  dest[ 30 ] = { "goodbye xx" };
      BOOST_REQUIRE( fs.copy( &dest[ 8], 40, 8) == 12);
      dest[ fs.length()] = '\0';
      BOOST_REQUIRE( ::strcmp( fs.c_str(), dest) == 0);
   } // end scope

   {
      char  dest[ 30 ] = { "goodbye xxx farewell" };
      BOOST_REQUIRE( fs.copy( &dest[ 8], 3, 38) == 0);
   } // end scope

   {
      char  dest[ 30 ] = { "goodbye xxx farewell" };
      BOOST_REQUIRE( fs.copy( &dest[ 8], 0, 38) == 0);
   } // end scope

   BOOST_REQUIRE( fs.copy( nullptr, 3, 8) == 0);

} // copy_str



/// Checks the swap() function.
/// @since  x.y.z, 25.01.2021
BOOST_AUTO_TEST_CASE( swap)
{

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  fs2;

      fs1.swap( fs2);
      BOOST_REQUIRE( fs1.empty());
      BOOST_REQUIRE_EQUAL( fs2.str(), "goodbye and farewell");
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  fs2;

      fs2.swap( fs1);
      BOOST_REQUIRE( fs1.empty());
      BOOST_REQUIRE_EQUAL( fs2.str(), "goodbye and farewell");
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  fs2( "hello world");

      fs1.swap( fs2);
      BOOST_REQUIRE_EQUAL( fs1.str(), "hello world");
      BOOST_REQUIRE_EQUAL( fs2.str(), "goodbye and farewell");
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  fs2( "hello world");

      fs2.swap( fs1);
      BOOST_REQUIRE_EQUAL( fs1.str(), "hello world");
      BOOST_REQUIRE_EQUAL( fs2.str(), "goodbye and farewell");
   } // end scope

} // swap



/// Checks the find() function.
/// @since  x.y.z, 26.01.2021
BOOST_AUTO_TEST_CASE( find)
{

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search;

      BOOST_REQUIRE( fs1.find( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1;
      FixedString< 30>  search( "or");

      BOOST_REQUIRE( fs1.find( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "and farewell forever");

      BOOST_REQUIRE( fs1.find( search, 8) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "or");

      BOOST_REQUIRE( fs1.find( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "good");

      BOOST_REQUIRE( fs1.find( search, 1) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "good");

      BOOST_REQUIRE( fs1.find( search) == 0);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "well");

      BOOST_REQUIRE( fs1.find( search) == 16);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search;

      BOOST_REQUIRE( fs1.find( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1;
      std::string       search( "or");

      BOOST_REQUIRE( fs1.find( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "and farewell forever");

      BOOST_REQUIRE( fs1.find( search, 8) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "or");

      BOOST_REQUIRE( fs1.find( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "good");

      BOOST_REQUIRE( fs1.find( search, 1) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "good");

      BOOST_REQUIRE( fs1.find( search) == 0);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "well");

      BOOST_REQUIRE( fs1.find( search) == 16);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");

      BOOST_REQUIRE( fs1.find( nullptr, 0, 5) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1;
      char              search[ 20] = { "or" };

      BOOST_REQUIRE( fs1.find( search, 0, 2) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 30] = { "and farewell forever" };

      BOOST_REQUIRE( fs1.find( search, 8, ::strlen( search)) == std::string::npos);
      BOOST_REQUIRE( fs1.find( search, 8) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 20] = { "or" };

      BOOST_REQUIRE( fs1.find( search, 0, 2) == std::string::npos);
      BOOST_REQUIRE( fs1.find( search, 0) == std::string::npos);
      BOOST_REQUIRE( fs1.find( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 20] = { "good" };

      BOOST_REQUIRE( fs1.find( search, 1, 4) == std::string::npos);
      BOOST_REQUIRE( fs1.find( search, 1) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 20] = { "good" };

      BOOST_REQUIRE( fs1.find( search, 0, 4) == 0);
      BOOST_REQUIRE( fs1.find( search, 0) == 0);
      BOOST_REQUIRE( fs1.find( search) == 0);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 20] = { "well" };

      BOOST_REQUIRE( fs1.find( search, 0, 4) == 16);
      BOOST_REQUIRE( fs1.find( search, 0) == 16);
      BOOST_REQUIRE( fs1.find( search) == 16);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");

      BOOST_REQUIRE( fs1.find( 'x') == std::string::npos);
      BOOST_REQUIRE( fs1.find( 'o') == 1);
      BOOST_REQUIRE( fs1.find( 'o', 2) == 2);
      BOOST_REQUIRE( fs1.find( 'o', 5) == std::string::npos);
      BOOST_REQUIRE( fs1.find( 'l', 18) == 18);
      BOOST_REQUIRE( fs1.find( 'l', 19) == 19);
      BOOST_REQUIRE( fs1.find( 'l', 20) == std::string::npos);
   } // end scope

} // find



/// Checks the rfind() function.
/// @since  x.y.z, 26.01.2021
BOOST_AUTO_TEST_CASE( rfind)
{

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search;

      BOOST_REQUIRE( fs1.rfind( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1;
      FixedString< 30>  search( "or");

      BOOST_REQUIRE( fs1.rfind( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "and farewell forever");

      BOOST_REQUIRE( fs1.rfind( search, 8) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "or");

      BOOST_REQUIRE( fs1.rfind( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "well");

      BOOST_REQUIRE( fs1.rfind( search, 15) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "good");

      BOOST_REQUIRE( fs1.rfind( search) == 0);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      FixedString< 30>  search( "well");

      BOOST_REQUIRE( fs1.rfind( search) == 16);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search;

      BOOST_REQUIRE( fs1.rfind( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1;
      std::string       search( "or");

      BOOST_REQUIRE( fs1.rfind( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "and farewell forever");

      BOOST_REQUIRE( fs1.rfind( search, 8) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "or");

      BOOST_REQUIRE( fs1.rfind( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "well");

      BOOST_REQUIRE( fs1.rfind( search, 15) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "good");

      BOOST_REQUIRE( fs1.rfind( search) == 0);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      std::string       search( "well");

      BOOST_REQUIRE( fs1.rfind( search) == 16);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");

      BOOST_REQUIRE( fs1.rfind( nullptr, 0, 5) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( "", 0, 5) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1;
      char              search[ 20] = { "or" };

      BOOST_REQUIRE( fs1.rfind( search, 0, 2) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 30] = { "and farewell forever" };

      BOOST_REQUIRE( fs1.rfind( search, 8, ::strlen( search)) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( search, 8) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 50] = { "and farewell forever my friend" };

      BOOST_REQUIRE( fs1.rfind( search, 8, 100) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( search, 8) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 20] = { "or" };

      BOOST_REQUIRE( fs1.rfind( search, 0, 2) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( search, 0) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( search) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 20] = { "well" };

      BOOST_REQUIRE( fs1.rfind( search, 15, 4) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( search, 15, 22) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( search, 15) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");
      char              search[ 20] = { "good" };

      BOOST_REQUIRE( fs1.rfind( search, 0, 4) == 0);
      BOOST_REQUIRE( fs1.rfind( search, 19, 4) == 0);
      BOOST_REQUIRE( fs1.rfind( search, 19) == 0);
      BOOST_REQUIRE( fs1.rfind( search) == 0);
   } // end scope

   {
      FixedString< 30>  fs1( "goodbye and farewell");

      BOOST_REQUIRE( fs1.rfind( 'x') == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( 'o') == 2);
      BOOST_REQUIRE( fs1.rfind( 'o', 1) == 1);
      BOOST_REQUIRE( fs1.rfind( 'o', 0) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( 'l', 20) == std::string::npos);
      BOOST_REQUIRE( fs1.rfind( 'l', 19) == 19);
      BOOST_REQUIRE( fs1.rfind( 'l', 18) == 18);
      BOOST_REQUIRE( fs1.rfind( 'l', 17) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs;

      BOOST_REQUIRE( fs.rfind( 'x') == std::string::npos);
   } // end scope

} // rfind


   
/// Checks the find_first_of() function.
/// @since  x.y.z, 26.01.2021
BOOST_AUTO_TEST_CASE( find_first_of)
{

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch;

      BOOST_REQUIRE( fs.find_first_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch( "uvxz");

      BOOST_REQUIRE( fs.find_first_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch( "aeiou");

      BOOST_REQUIRE( fs.find_first_of( srch) == 1);
      BOOST_REQUIRE( fs.find_first_of( srch, 3) == 6);
      BOOST_REQUIRE( fs.find_first_of( srch, 6) == 6);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch;

      BOOST_REQUIRE( fs.find_first_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch( "uvxz");

      BOOST_REQUIRE( fs.find_first_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch( "aeiou");

      BOOST_REQUIRE( fs.find_first_of( srch) == 1);
      BOOST_REQUIRE( fs.find_first_of( srch, 3) == 6);
      BOOST_REQUIRE( fs.find_first_of( srch, 6) == 6);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "aeiou" };

      BOOST_REQUIRE( fs.find_first_of( srch, 0, ::strlen( srch)) == 1);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "ae\0iou" };

      BOOST_REQUIRE( fs.find_first_of( srch, 0, 6) == 1);
      BOOST_REQUIRE( fs.find_first_of( srch, 1, 6) == 1);
      BOOST_REQUIRE( fs.find_first_of( srch, 3, 6) == 6);
      BOOST_REQUIRE( fs.find_first_of( srch, 25, 6) == std::string::npos);
      BOOST_REQUIRE( fs.find_first_of( srch, 25, 0) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "uvxz" };

      BOOST_REQUIRE( fs.find_first_of( srch, 0, 4) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "aeiou" };

      BOOST_REQUIRE( fs.find_first_of( srch) == 1);
      BOOST_REQUIRE( fs.find_first_of( srch, 0) == 1);
      BOOST_REQUIRE( fs.find_first_of( srch, 1) == 1);
      BOOST_REQUIRE( fs.find_first_of( srch, 3) == 6);
      BOOST_REQUIRE( fs.find_first_of( srch, 25) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");

      BOOST_REQUIRE( fs.find_first_of( 'a') == 8);
      BOOST_REQUIRE( fs.find_first_of( 'o') == 1);
      BOOST_REQUIRE( fs.find_first_of( 'o', 2) == 2);
      BOOST_REQUIRE( fs.find_first_of( 'x') == std::string::npos);
      BOOST_REQUIRE( fs.find_first_of( 'e', 26) == std::string::npos);
   } // end scope

} // find_first_of



/// Checks the find_first_not_of() function.
/// @since  x.y.z, 27.01.2021
BOOST_AUTO_TEST_CASE( find_first_not_of)
{

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch;

      BOOST_REQUIRE( fs.find_first_not_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch( " abdefglnorwy");

      BOOST_REQUIRE( fs.find_first_not_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch( " abdfglnorwy");

      BOOST_REQUIRE( fs.find_first_not_of( srch) == 6);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 7) == 15);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 16) == 17);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 18) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch;

      BOOST_REQUIRE( fs.find_first_not_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch( " abdefglnorwy");

      BOOST_REQUIRE( fs.find_first_not_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch( " abdfglnorwy");

      BOOST_REQUIRE( fs.find_first_not_of( srch) == 6);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 7) == 15);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 16) == 17);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 18) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "aeiou" };

      BOOST_REQUIRE( fs.find_first_of( srch, 0, ::strlen( srch)) == 1);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { " abdfgl\0norwy" };

      BOOST_REQUIRE( fs.find_first_not_of( srch, 0, 14) == 6);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 7, 14) == 15);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 0, 0) == std::string::npos);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 25, 14) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { " abdefglnorwy" };

      BOOST_REQUIRE( fs.find_first_not_of( srch, 0, 15) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { " abdfglnorwy" };

      BOOST_REQUIRE( fs.find_first_not_of( srch) == 6);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 0) == 6);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 6) == 6);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 7) == 15);
      BOOST_REQUIRE( fs.find_first_not_of( srch, 25) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");

      BOOST_REQUIRE( fs.find_first_not_of( 'a') == 0);
      BOOST_REQUIRE( fs.find_first_not_of( 'g') == 1);
      BOOST_REQUIRE( fs.find_first_not_of( 'c', 4) == 4);
      BOOST_REQUIRE( fs.find_first_not_of( 'e', 26) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "oo");

      BOOST_REQUIRE( fs.find_first_not_of( 'o') == std::string::npos);
   } // end scope

} // find_first_not_of



/// Checks the find_last_of() function.
/// @since  x.y.z, 27.01.2021
BOOST_AUTO_TEST_CASE( find_last_of)
{

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch;

      BOOST_REQUIRE( fs.find_last_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch( "uvxz");

      BOOST_REQUIRE( fs.find_last_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch( "aeiou");

      BOOST_REQUIRE( fs.find_last_of( srch) == 17);
      BOOST_REQUIRE( fs.find_last_of( srch, 16) == 15);
      BOOST_REQUIRE( fs.find_last_of( srch, 14) == 13);
      BOOST_REQUIRE( fs.find_last_of( srch, 13) == 13);
      BOOST_REQUIRE( fs.find_last_of( srch, 0) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch;

      BOOST_REQUIRE( fs.find_last_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch( "uvxz");

      BOOST_REQUIRE( fs.find_last_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch( "aeiou");

      BOOST_REQUIRE( fs.find_last_of( srch) == 17);
      BOOST_REQUIRE( fs.find_last_of( srch, 14) == 13);
      BOOST_REQUIRE( fs.find_last_of( srch, 0) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "aeiou" };

      BOOST_REQUIRE( fs.find_last_of( srch, 19, ::strlen( srch)) == 17);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "ae\0iou" };

      BOOST_REQUIRE( fs.find_last_of( srch, 19, 6) == 17);
      BOOST_REQUIRE( fs.find_last_of( srch, 7, 6) == 6);
      BOOST_REQUIRE( fs.find_last_of( srch, 1, 6) == 1);
      BOOST_REQUIRE( fs.find_last_of( srch, 25, 6) == std::string::npos);
      BOOST_REQUIRE( fs.find_last_of( srch, 25, 0) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "uvxz" };

      BOOST_REQUIRE( fs.find_last_of( srch, 19, 4) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "aeiou" };

      BOOST_REQUIRE( fs.find_last_of( srch) == 17);
      BOOST_REQUIRE( fs.find_last_of( srch, 16) == 15);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");

      BOOST_REQUIRE( fs.find_last_of( 'a') == 13);
      BOOST_REQUIRE( fs.find_last_of( 'o') == 2);
      BOOST_REQUIRE( fs.find_last_of( 'o', 1) == 1);
      BOOST_REQUIRE( fs.find_last_of( 'x') == std::string::npos);
      BOOST_REQUIRE( fs.find_last_of( 'e', 26) == std::string::npos);
   } // end scope

} // find_last_of



/// Checks the find_last_not_of() function.
/// @since  x.y.z, 28.01.2021
BOOST_AUTO_TEST_CASE( find_last_not_of)
{

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch;

      BOOST_REQUIRE( fs.find_last_not_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch( " abdefglnorwy");

      BOOST_REQUIRE( fs.find_last_not_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      FixedString< 30>  srch( " abdfglnorwy");

      BOOST_REQUIRE( fs.find_last_not_of( srch) == 17);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 16) == 15);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 14) == 6);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 6) == 6);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 5) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch;

      BOOST_REQUIRE( fs.find_last_not_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch( " abdefglnorwy");

      BOOST_REQUIRE( fs.find_last_not_of( srch) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      std::string       srch( " abdfglnorwy");

      BOOST_REQUIRE( fs.find_last_not_of( srch) == 17);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 16) == 15);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 14) == 6);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 6) == 6);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 5) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { "aeiou" };

      BOOST_REQUIRE( fs.find_first_of( srch, 0, ::strlen( srch)) == 1);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { " abdfgl\0norwy" };

      BOOST_REQUIRE( fs.find_last_not_of( srch, 19, 14) == 17);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 16, 14) == 15);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 5, 14) == std::string::npos);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 0, 0) == std::string::npos);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 25, 14) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { " abdefglnorwy" };

      BOOST_REQUIRE( fs.find_last_not_of( srch, 19, 15) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");
      char              srch[ 20] = { " abdfglnorwy" };

      BOOST_REQUIRE( fs.find_last_not_of( srch) == 17);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 16) == 15);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 6) == 6);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 5) == std::string::npos);
      BOOST_REQUIRE( fs.find_last_not_of( srch, 25) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "goodbye and farewell");

      BOOST_REQUIRE( fs.find_last_not_of( 'a') == 19);
      BOOST_REQUIRE( fs.find_last_not_of( 'l') == 17);
      BOOST_REQUIRE( fs.find_last_not_of( 'c', 4) == 4);
      BOOST_REQUIRE( fs.find_last_not_of( 'e', 26) == std::string::npos);
   } // end scope

   {
      FixedString< 30>  fs( "oo");

      BOOST_REQUIRE( fs.find_last_not_of( 'o') == std::string::npos);
   } // end scope

} // find_last_not_of



// =====  END OF test_fixed_string.hpp  =====

