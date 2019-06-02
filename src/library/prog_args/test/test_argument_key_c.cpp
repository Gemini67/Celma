
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the class ArgumentKey using the Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/prog_args/detail/argument_key.hpp"


// Boost includes
#define BOOST_TEST_MODULE ArgumentKeyTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/format/to_string.hpp"
#include "celma/test/check_return.hpp"


using celma::format::toString;
using celma::prog_args::detail::ArgumentKey;
using std::invalid_argument;


namespace {



/// Verifies that the argument specification strings, returned by the two
/// objects, are identical.
/// @param[in]  left   The first object to use.
/// @param[in]  right  The other object to use.
/// @return  \c true if the two argument specification strings are equa.
/// @since  0.2, 06.04.2016
bool string_equal( const ArgumentKey& left, const ArgumentKey& right)
{

   CHECK_EQUAL_RETURN( toString( left), toString( right));

   return true;
} // string_equal



} // end namespace



/// Verify that all possible errors are detected.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_errors)
{

   // empty string
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( ""), invalid_argument);
   } // end scope

   // comma == separator character only
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( ","), invalid_argument);
   } // end scope

   // short and comma == separator character only, no long value
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "i,"), invalid_argument);
   } // end scope

   // comma == separator character and short only, no long value
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( ",i"), invalid_argument);
   } // end scope

   // long and comma == separator character only, no long value
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "index,"), invalid_argument);
   } // end scope

   // comma == separator character and long only, no long value
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( ",index"), invalid_argument);
   } // end scope

   // two identical short argument keys
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "i,i"), invalid_argument);
   } // end scope

   // two identical long argument keys
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "name,name"), invalid_argument);
   } // end scope

   // two short argument keys
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "i,l"), invalid_argument);
   } // end scope

   // two long argument keys
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "index,name"), invalid_argument);
   } // end scope

   // three values
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "a,b,c"), invalid_argument);
   } // end scope

   // contains a space
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "a b"), invalid_argument);
   } // end scope

   // contains too many leading dashes
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "---a"), invalid_argument);
   } // end scope

   // contains too many leading dashes
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "l,---long"), invalid_argument);
   } // end scope

   // contains too many leading dashes
   {
      BOOST_REQUIRE_THROW( ArgumentKey  ak( "--long,---l"), invalid_argument);
   } // end scope

} // test_errors



/// Test that leading dashes are correctly removed.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_remove_leading_dashes)
{

   {
      ArgumentKey  short1( "-l");
      BOOST_REQUIRE_EQUAL( toString( short1), "-l");
   } // end scope

   {
      ArgumentKey  long1( "--long");
      BOOST_REQUIRE_EQUAL( toString( long1), "--long");
   } // end scope

   {
      ArgumentKey  both( "-l,long");
      BOOST_REQUIRE_EQUAL( toString( both), "-l,--long");
   } // end scope

   {
      ArgumentKey  both( "l,--long");
      BOOST_REQUIRE_EQUAL( toString( both), "-l,--long");
   } // end scope

   {
      ArgumentKey  both( "-l,--long");
      BOOST_REQUIRE_EQUAL( toString( both), "-l,--long");
   } // end scope

   {
      ArgumentKey  longy( "--l");
      BOOST_REQUIRE_EQUAL( toString( longy), "--l");
   } // end scope

   // positional argument
   {
      ArgumentKey  pos( "-");
      BOOST_REQUIRE_EQUAL( toString( pos), "--");
   } // end scope

} // test_remove_leading_dashes



/// Test all successful comparisons.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_comparison)
{

   // two identical short
   {
      ArgumentKey  short1( "l");
      ArgumentKey  short2( "l");

      BOOST_REQUIRE_EQUAL( short1, short2);
      BOOST_REQUIRE( !short1.mismatch( short2));

      BOOST_REQUIRE( string_equal( short1, short2));
   } // end scope

   // two identical long
   {
      ArgumentKey  long1( "long");
      ArgumentKey  long2( "long");

      BOOST_REQUIRE_EQUAL( long1, long2);
      BOOST_REQUIRE( !long1.mismatch( long2));

      BOOST_REQUIRE( string_equal( long1, long2));
   } // end scope

   // both with short and long
   {
      ArgumentKey  both1( "l,long");
      ArgumentKey  both2( "long,l");

      BOOST_REQUIRE_EQUAL( both1, both2);
      BOOST_REQUIRE_EQUAL( both2, both1);
      BOOST_REQUIRE( !both1.mismatch( both2));
      BOOST_REQUIRE( !both2.mismatch( both1));

      BOOST_REQUIRE( string_equal( both1, both2));
   } // end scope

   // one with both short and long, the other with short only
   {
      ArgumentKey  both1( "l,long");
      ArgumentKey  short2( "l");

      BOOST_REQUIRE_EQUAL( both1, short2);
      BOOST_REQUIRE_EQUAL( short2, both1);
      BOOST_REQUIRE( !both1.mismatch( short2));
      BOOST_REQUIRE( !short2.mismatch( both1));
   } // end scope

   // one with both short and long, the other with short only
   {
      ArgumentKey  short1( "l");
      ArgumentKey  both2( "long,l");

      BOOST_REQUIRE_EQUAL( short1, both2);
      BOOST_REQUIRE_EQUAL( both2, short1);
      BOOST_REQUIRE( !short1.mismatch( both2));
      BOOST_REQUIRE( !both2.mismatch( short1));
   } // end scope

   // one with both short and long, the other with long only
   {
      ArgumentKey  both1( "l,long");
      ArgumentKey  long2( "long");

      BOOST_REQUIRE_EQUAL( both1, long2);
      BOOST_REQUIRE_EQUAL( long2, both1);
      BOOST_REQUIRE( !both1.mismatch( long2));
      BOOST_REQUIRE( !long2.mismatch( both1));
   } // end scope

   // one with both short and long, the other with short only
   {
      ArgumentKey  long1( "long");
      ArgumentKey  both2( "long,l");

      BOOST_REQUIRE_EQUAL( long1, both2);
      BOOST_REQUIRE_EQUAL( both2, long1);
      BOOST_REQUIRE( !long1.mismatch( both2));
      BOOST_REQUIRE( !both2.mismatch( long1));
   } // end scope

   // compare the 'keys' of positional arguments
   {
      ArgumentKey  pos1( "-");
      ArgumentKey  pos2( "-");

      BOOST_REQUIRE_EQUAL( pos1, pos2);
      BOOST_REQUIRE( !pos1.mismatch( pos2));
   } // end scope

} // test_comparison



/// Test all comparisons that fail.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_comparison_failed)
{

   // two different short
   {
      ArgumentKey  short1( "l");
      ArgumentKey  short2( "s");

      BOOST_REQUIRE_NE( short1, short2);
      BOOST_REQUIRE( !short1.mismatch( short2));
   } // end scope

   // two different long
   {
      ArgumentKey  long1( "long");
      ArgumentKey  long2( "short");

      BOOST_REQUIRE_NE( long1, long2);
      BOOST_REQUIRE( !long1.mismatch( long2));
   } // end scope

   // short and long
   {
      ArgumentKey  short1( "l");
      ArgumentKey  long2( "long");

      BOOST_REQUIRE_NE( short1, long2);
      BOOST_REQUIRE( !short1.mismatch( long2));
   } // end scope

   // short and long
   {
      ArgumentKey  long1( "long");
      ArgumentKey  short2( "l");

      BOOST_REQUIRE_NE( long1, short2);
      BOOST_REQUIRE( !long1.mismatch( short2));
   } // end scope

   // both short and long
   {
      ArgumentKey  both1( "s,short");
      ArgumentKey  both2( "l,long");

      BOOST_REQUIRE_NE( both1, both2);
      BOOST_REQUIRE( !both1.mismatch( both2));
   } // end scope

   // short and both
   {
      ArgumentKey  short1( "s");
      ArgumentKey  both2( "l,long");

      BOOST_REQUIRE_NE( short1, both2);
      BOOST_REQUIRE( !short1.mismatch( both2));
   } // end scope

   // long and both
   {
      ArgumentKey  long1( "short");
      ArgumentKey  both2( "l,long");

      BOOST_REQUIRE_NE( long1, both2);
      BOOST_REQUIRE( !long1.mismatch( both2));
   } // end scope

   // both and short
   {
      ArgumentKey  both1( "l,long");
      ArgumentKey  short2( "s");

      BOOST_REQUIRE_NE( both1, short2);
      BOOST_REQUIRE( !both1.mismatch( short2));
   } // end scope

   // both and long
   {
      ArgumentKey  both1( "s,short");
      ArgumentKey  long2( "long");

      BOOST_REQUIRE_NE( both1, long2);
      BOOST_REQUIRE( !both1.mismatch( long2));
   } // end scope

} // test_comparison_failed



/// Test that mismatch is detected.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_mismatch)
{

   // two different short
   {
      ArgumentKey  both1( "s,short");
      ArgumentKey  both2( "y,short");

      BOOST_REQUIRE_NE( both1, both2);
      BOOST_REQUIRE( both1.mismatch( both2));
   } // end scope

   // two different long
   {
      ArgumentKey  both1( "s,short");
      ArgumentKey  both2( "s,symbol");

      BOOST_REQUIRE_EQUAL( both1, both2);
      BOOST_REQUIRE( both1.mismatch( both2));
   } // end scope

} // test_mismatch



/// Test that copies contain the same values.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_copies)
{

   // copy of key with only short argument
   {
      ArgumentKey  short1( "s");
      ArgumentKey  copy1( short1);

      BOOST_REQUIRE_EQUAL( short1, copy1);
      BOOST_REQUIRE( !short1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( short1, copy1));
   } // end scope

   // copy of key with only long argument
   {
      ArgumentKey  long1( "long");
      ArgumentKey  copy1( long1);

      BOOST_REQUIRE_EQUAL( long1, copy1);
      BOOST_REQUIRE( !long1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( long1, copy1));
   } // end scope

   // copy of key with both short and long argument
   {
      ArgumentKey  both1( "s,symbol");
      ArgumentKey  copy1( both1);

      BOOST_REQUIRE_EQUAL( both1, copy1);
      BOOST_REQUIRE( !both1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( both1, copy1));
   } // end scope

   // assign/overwrite long with short
   {
      ArgumentKey  short1( "s");
      ArgumentKey  copy1( "long");

      copy1 = short1;

      BOOST_REQUIRE_EQUAL( short1, copy1);
      BOOST_REQUIRE( !short1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( short1, copy1));
   } // end scope

   // assign/overwrite short with long
   {
      ArgumentKey  long1( "long");
      ArgumentKey  copy1( "s");

      copy1 = long1;

      BOOST_REQUIRE_EQUAL( long1, copy1);
      BOOST_REQUIRE( !long1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( long1, copy1));
   } // end scope

   // assign/overwrite both with short
   {
      ArgumentKey  short1( "s");
      ArgumentKey  copy1( "l,long");

      copy1 = short1;

      BOOST_REQUIRE_EQUAL( short1, copy1);
      BOOST_REQUIRE( !short1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( short1, copy1));
   } // end scope

   // assign/overwrite both with long
   {
      ArgumentKey  long1( "long");
      ArgumentKey  copy1( "s,symbol");

      copy1 = long1;

      BOOST_REQUIRE_EQUAL( long1, copy1);
      BOOST_REQUIRE( !long1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( long1, copy1));
   } // end scope

   // assign/overwrite short with both
   {
      ArgumentKey  both1( "s,symbol");
      ArgumentKey  copy1( "l");

      copy1 = both1;

      BOOST_REQUIRE_EQUAL( both1, copy1);
      BOOST_REQUIRE( !both1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( both1, copy1));
   } // end scope

   // assign/overwrite long with both
   {
      ArgumentKey  both1( "l,long");
      ArgumentKey  copy1( "symbol");

      copy1 = both1;

      BOOST_REQUIRE_EQUAL( both1, copy1);
      BOOST_REQUIRE( !both1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( both1, copy1));
   } // end scope

   // assign/overwrite long with both
   {
      ArgumentKey  both1( "l,long");
      ArgumentKey  long1( "symbol");

      both1 = ArgumentKey( "symbol");

      BOOST_REQUIRE_EQUAL( both1, long1);
      BOOST_REQUIRE( !both1.mismatch( long1));

      BOOST_REQUIRE( string_equal( both1, long1));
   } // end scope

} // test_copies



// =====  END OF test_argument_key_c.cpp  =====

