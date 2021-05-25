
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
#include "celma/common/detail/fixed_string_reverse_iterator.hpp"


// Boost includes
#define BOOST_TEST_MODULE FixedStringReverseIteratorTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/fixed_string.hpp"


using celma::common::FixedString;
using celma::common::detail::FixedStringReverseIterator;



/// Construct fixed string iterators.
///
/// @since  1.46.0, 21.01.2021
BOOST_AUTO_TEST_CASE( constructor)
{

   {
      FixedStringReverseIterator< char, FixedString< 20>>  fsri;
      auto                                                 copy( fsri);

      BOOST_REQUIRE( fsri == copy);

      BOOST_REQUIRE_THROW( *fsri, std::invalid_argument);
      BOOST_REQUIRE_THROW( fsri[ 2], std::invalid_argument);
   } // end scope

   {
      FixedStringReverseIterator< const char, FixedString< 20>>  fsri;
      auto                                                       copy( fsri);

      BOOST_REQUIRE( fsri == copy);

      BOOST_REQUIRE_THROW( *fsri, std::invalid_argument);
      BOOST_REQUIRE_THROW( fsri[ 2], std::invalid_argument);
   } // end scope

   {
      FixedString< 20>                                     fs( "hello world");
      FixedStringReverseIterator< char, FixedString< 20>>  fsri( &fs);

      BOOST_REQUIRE_EQUAL( *fsri, 'd');
   } // end scope

   {
      FixedString< 20>                                     fs( "hello world");
      FixedStringReverseIterator< char, FixedString< 20>>  fsi1( &fs);
      FixedStringReverseIterator< char, FixedString< 20>>  fsi2( &fs, fs.length() - 1);

      BOOST_REQUIRE( fsi1 == fsi2);
   } // end scope

   {
      FixedString< 20>                                     fs( "hello world");
      FixedStringReverseIterator< char, FixedString< 20>>  fsi1( &fs, 30);
      FixedStringReverseIterator< char, FixedString< 20>>  fsi2( true, &fs);

      BOOST_REQUIRE( fsi1 == fsi2);
   } // end scope

   {
      FixedString< 20>                                     fs( "hello world");
      FixedStringReverseIterator< char, FixedString< 20>>  fsi1( nullptr, 10);
      FixedStringReverseIterator< char, FixedString< 20>>  fsi2( true, &fs);

      BOOST_REQUIRE( fsi1 == fsi2);
   } // end scope

} // constructor



/// Iterate forward over the string.
///
/// @since  1.46.0, 21.01.2021
BOOST_AUTO_TEST_CASE( forward)
{


   FixedString< 20>                                     fs( "hello world");
   FixedStringReverseIterator< char, FixedString< 20>>  fsri( &fs);

   BOOST_REQUIRE_EQUAL( *fsri, 'd');
   ++fsri;
   BOOST_REQUIRE_EQUAL( *fsri, 'l');

   {
      auto  copy = ++fsri;
      BOOST_REQUIRE( fsri == copy);
      BOOST_REQUIRE_EQUAL( *fsri, 'r');
      BOOST_REQUIRE_EQUAL( *copy, 'r');

      BOOST_REQUIRE_THROW( copy[ 20], std::range_error);
      copy += 20;
      BOOST_REQUIRE_THROW( *copy, std::range_error);
   } // end scope

   ++fsri;

   {
      auto const  copy = fsri++;
      BOOST_REQUIRE( fsri != copy);
      BOOST_REQUIRE_EQUAL( *fsri, 'w');
      BOOST_REQUIRE_EQUAL( *copy, 'o');
      BOOST_REQUIRE_EQUAL( copy[ 0], 'o');
      BOOST_REQUIRE_THROW( copy[ 20], std::range_error);

      BOOST_REQUIRE( copy < fsri);
      BOOST_REQUIRE( copy <= fsri);
      BOOST_REQUIRE( fsri >= copy);
      BOOST_REQUIRE( fsri > copy);

      BOOST_REQUIRE_EQUAL( fsri - copy, 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( fsri[ 6], 'h');

   auto  copy( fsri);
   fsri += 6;
   BOOST_REQUIRE_EQUAL( *fsri, 'h');
   BOOST_REQUIRE_EQUAL( fsri - copy, 6);

   {
      FixedStringReverseIterator< char, FixedString< 20>>  invalid;

      BOOST_REQUIRE_THROW( invalid - fsri, std::invalid_argument);
      BOOST_REQUIRE_THROW( fsri - invalid, std::invalid_argument);
   } // end scope

   ++fsri;
   BOOST_REQUIRE_THROW( *fsri, std::range_error);

   auto const  copy2( fsri);
   BOOST_REQUIRE_THROW( *copy2, std::range_error);

   FixedStringReverseIterator< char, FixedString< 20>>  rend( true, &fs);
   BOOST_REQUIRE( fsri == rend);

   FixedStringReverseIterator< char, FixedString< 20>>  crend( true, &fs);
   BOOST_REQUIRE( copy2 == crend);

} // forward



/// Iterate backwards over the string.
///
/// @since  1.46.0, 21.01.2021
BOOST_AUTO_TEST_CASE( backward)
{

   FixedString< 20>                                     fs( "hello world");
   FixedStringReverseIterator< char, FixedString< 20>>  fsri( &fs, 0);

   BOOST_REQUIRE_EQUAL( *fsri, 'h');
   --fsri;
   BOOST_REQUIRE_EQUAL( *fsri, 'e');

   {
      auto  copy = --fsri;
      BOOST_REQUIRE( fsri == copy);
      BOOST_REQUIRE_EQUAL( *fsri, 'l');
      BOOST_REQUIRE_EQUAL( *copy, 'l');

      copy -= 20;
      BOOST_REQUIRE_THROW( *copy, std::range_error);
   } // end scope

   --fsri;

   {
      auto  copy = fsri--;
      BOOST_REQUIRE( fsri != copy);
      BOOST_REQUIRE_EQUAL( *fsri, 'o');
      BOOST_REQUIRE_EQUAL( *copy, 'l');
      BOOST_REQUIRE_EQUAL( copy[ 0], 'l');

      BOOST_REQUIRE( copy > fsri);
      BOOST_REQUIRE( copy >= fsri);
      BOOST_REQUIRE( fsri <= copy);
      BOOST_REQUIRE( fsri < copy);
   } // end scope

   fsri -= 6;
   BOOST_REQUIRE_EQUAL( *fsri, 'd');

   --fsri;
   BOOST_REQUIRE_THROW( *fsri, std::range_error);

} // backward



/// Check the equality comparison operator.
///
/// @since  1.46.0, 25.01.2021
BOOST_AUTO_TEST_CASE( comparisons)
{

   FixedString< 20>  fs1( "hello world");
   FixedString< 20>  fs2( "hello world");

   // same position but different strings
   {
      FixedStringReverseIterator< char, FixedString< 20>>  riter1( &fs1);
      FixedStringReverseIterator< char, FixedString< 20>>  riter2( &fs2);

      BOOST_REQUIRE( riter1 != riter2);
   } // end scope

   // same string but different positions
   {
      FixedStringReverseIterator< char, FixedString< 20>>  iter1( &fs1);
      FixedStringReverseIterator< char, FixedString< 20>>  iter2( &fs1, 1);

      BOOST_REQUIRE( iter1 != iter2);
   } // end scope

   // different strings, but both are end --> equal
   BOOST_REQUIRE( fs1.rend() == fs2.rend());

} // comparisons



// =====  END OF test_fixed_string_reverse_iterator.cpp  =====

