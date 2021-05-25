
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
#include "celma/common/detail/fixed_string_iterator.hpp"


// Boost includes
#define BOOST_TEST_MODULE FixedStringIteratorTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/common/fixed_string.hpp"


using celma::common::FixedString;
using celma::common::detail::FixedStringIterator;



/// Construct fixed string iterators.
///
/// @since  1.46.0, 20.01.2021
BOOST_AUTO_TEST_CASE( constructor)
{

   {
      FixedStringIterator< char, FixedString< 20>>  fsi;
      auto                                          copy( fsi);

      BOOST_REQUIRE( fsi == copy);

      BOOST_REQUIRE_THROW( *fsi, std::invalid_argument);
      BOOST_REQUIRE_THROW( fsi[ 2], std::invalid_argument);
   } // end scope

   {
      const FixedStringIterator< const char, FixedString< 20>>  fsi;
      auto                                                      copy( fsi);

      BOOST_REQUIRE( fsi == copy);

      BOOST_REQUIRE_THROW( *fsi, std::invalid_argument);
      BOOST_REQUIRE_THROW( fsi[ 2], std::invalid_argument);
   } // end scope

   {
      FixedString< 20>                              fs( "hello world");
      FixedStringIterator< char, FixedString< 20>>  fsi( &fs, 0);

      BOOST_REQUIRE_EQUAL( *fsi, 'h');
   } // end scope

   {
      FixedString< 20>                              fs( "hello world");
      FixedStringIterator< char, FixedString< 20>>  fsi1( &fs);
      FixedStringIterator< char, FixedString< 20>>  fsi2( &fs, 0);

      BOOST_REQUIRE( fsi1 == fsi2);
   } // end scope

} // constructor



/// Iterate forward over the string.
///
/// @since  1.46.0, 20.01.2021
BOOST_AUTO_TEST_CASE( forward)
{


   FixedString< 20>                              fs( "hello world");
   FixedStringIterator< char, FixedString< 20>>  fsi( &fs, 0);

   BOOST_REQUIRE_EQUAL( *fsi, 'h');
   ++fsi;
   BOOST_REQUIRE_EQUAL( *fsi, 'e');

   {
      auto  copy = ++fsi;
      BOOST_REQUIRE( fsi == copy);
      BOOST_REQUIRE_EQUAL( *fsi, 'l');
      BOOST_REQUIRE_EQUAL( *copy, 'l');

      copy += 20;
      BOOST_REQUIRE_THROW( *copy, std::range_error);
   } // end scope

   ++fsi;

   {
      auto const  copy = fsi++;
      BOOST_REQUIRE( fsi != copy);
      BOOST_REQUIRE_EQUAL( *fsi, 'o');
      BOOST_REQUIRE_EQUAL( *copy, 'l');
      BOOST_REQUIRE_EQUAL( copy[ 0], 'l');

      BOOST_REQUIRE( copy < fsi);
      BOOST_REQUIRE( copy <= fsi);
      BOOST_REQUIRE( fsi >= copy);
      BOOST_REQUIRE( fsi > copy);

      BOOST_REQUIRE_EQUAL( fsi - copy, 1);
   } // end scope

   BOOST_REQUIRE_EQUAL( fsi[ 6], 'd');

   auto  copy( fsi);
   fsi += 6;
   BOOST_REQUIRE_EQUAL( *fsi, 'd');
   BOOST_REQUIRE_EQUAL( fsi - copy, 6);

   {
      FixedStringIterator< char, FixedString< 20>>  invalid;

      BOOST_REQUIRE_THROW( invalid - fsi, std::invalid_argument);
      BOOST_REQUIRE_THROW( fsi - invalid, std::invalid_argument);
   } // end scope

   ++fsi;
   BOOST_REQUIRE_THROW( *fsi, std::range_error);

   auto const  copy2( fsi);
   BOOST_REQUIRE_THROW( *copy2, std::range_error);

   FixedStringIterator< char, FixedString< 20>>  end( true, &fs);
   BOOST_REQUIRE( fsi == end);

   FixedStringIterator< char, FixedString< 20>>  cend( true, &fs);
   BOOST_REQUIRE( copy2 == cend);

} // forward



/// Iterate backwards over the string.
///
/// @since  1.46.0, 20.01.2021
BOOST_AUTO_TEST_CASE( backward)
{

   FixedString< 20>                              fs( "hello world");
   FixedStringIterator< char, FixedString< 20>>  fsi( &fs, fs.length() - 1);

   BOOST_REQUIRE_EQUAL( *fsi, 'd');
   --fsi;
   BOOST_REQUIRE_EQUAL( *fsi, 'l');

   {
      auto  copy = --fsi;
      BOOST_REQUIRE( fsi == copy);
      BOOST_REQUIRE_EQUAL( *fsi, 'r');
      BOOST_REQUIRE_EQUAL( *copy, 'r');

      copy -= 20;
      BOOST_REQUIRE_THROW( *copy, std::range_error);
   } // end scope

   --fsi;

   {
      auto const  copy = fsi--;
      BOOST_REQUIRE( fsi != copy);
      BOOST_REQUIRE_EQUAL( *fsi, 'w');
      BOOST_REQUIRE_EQUAL( *copy, 'o');
      BOOST_REQUIRE_EQUAL( copy[ 0], 'o');

      BOOST_REQUIRE( copy > fsi);
      BOOST_REQUIRE( copy >= fsi);
      BOOST_REQUIRE( fsi <= copy);
      BOOST_REQUIRE( fsi < copy);
   } // end scope

   fsi -= 6;
   BOOST_REQUIRE_EQUAL( *fsi, 'h');

   --fsi;
   BOOST_REQUIRE_THROW( *fsi, std::range_error);

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
      FixedStringIterator< char, FixedString< 20>>  iter1( &fs1);
      FixedStringIterator< char, FixedString< 20>>  iter2( &fs2);

      BOOST_REQUIRE( iter1 != iter2);
   } // end scope

   // same string but different positions
   {
      FixedStringIterator< char, FixedString< 20>>  iter1( &fs1);
      FixedStringIterator< char, FixedString< 20>>  iter2( &fs1, 1);

      BOOST_REQUIRE( iter1 != iter2);
   } // end scope

   // different strings, but both are end --> equal
   BOOST_REQUIRE( fs1.end() == fs2.end());

} // comparisons



// =====  END OF test_fixed_string_iterator.cpp  =====

