
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the class ArgumentKey using the Boost.Test framework.
**
--*/


// Boost includes
#define BOOST_TEST_MODULE ArgumentKeyTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/detail/argument_key.hpp"
#include "celma/test/check_return.hpp"


using namespace std;
using namespace celma;



namespace {



/// Verifies that the argument specification strings, returned by the two
/// objects, are identical.
/// @param[in]  left   The first object to use.
/// @param[in]  right  The other object to use.
/// @return  \c true if the two argument specification strings are equa.
/// @since  0.2, 06.04.2016
bool string_equal( const prog_args::detail::ArgumentKey& left,
                   const prog_args::detail::ArgumentKey& right)
{

   CHECK_EQUAL_RETURN( left.str(), right.str());

   return true;
} // end string_equal



} // end namespace



/// Verify that all possible errors are detected.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_errors)
{

   // empty string
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( ""), invalid_argument);
   } // end scope

   // comma == separator character only
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( ","), invalid_argument);
   } // end scope

   // short and comma == separator character only, no long value
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "i,"), invalid_argument);
   } // end scope

   // comma == separator character and short only, no long value
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( ",i"), invalid_argument);
   } // end scope

   // long and comma == separator character only, no long value
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "index,"), invalid_argument);
   } // end scope

   // comma == separator character and long only, no long value
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( ",index"), invalid_argument);
   } // end scope

   // two identical short argument keys
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "i,i"), invalid_argument);
   } // end scope

   // two identical long argument keys
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "name,name"), invalid_argument);
   } // end scope

   // two short argument keys
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "i,l"), invalid_argument);
   } // end scope

   // two long argument keys
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "index,name"), invalid_argument);
   } // end scope

   // three values
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "a,b,c"), invalid_argument);
   } // end scope

   // contains a space
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "a b"), invalid_argument);
   } // end scope

   // contains too many leading dashes
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "---a"), invalid_argument);
   } // end scope

   // contains too many leading dashes
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "l,---long"), invalid_argument);
   } // end scope

   // contains too many leading dashes
   {
      BOOST_REQUIRE_THROW( prog_args::detail::ArgumentKey  ak( "--long,---l"), invalid_argument);
   } // end scope

} // end test_errors



/// Test that leading dashes are correctly removed.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_remove_leading_dashes)
{

   {
      prog_args::detail::ArgumentKey  short1( "-l");
      BOOST_REQUIRE_EQUAL( short1.str(), "l");
   } // end scope

   {
      prog_args::detail::ArgumentKey  long1( "--long");
      BOOST_REQUIRE_EQUAL( long1.str(), "long");
   } // end scope

   {
      prog_args::detail::ArgumentKey  both( "-l,long");
      BOOST_REQUIRE_EQUAL( both.str(), "l,long");
   } // end scope

   {
      prog_args::detail::ArgumentKey  both( "l,--long");
      BOOST_REQUIRE_EQUAL( both.str(), "l,long");
   } // end scope

   {
      prog_args::detail::ArgumentKey  both( "-l,--long");
      BOOST_REQUIRE_EQUAL( both.str(), "l,long");
   } // end scope

} // end test_remove_leading_dashes



/// Test all successful comparisons.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_comparison)
{

   // two identical short
   {
      prog_args::detail::ArgumentKey  short1( "l");
      prog_args::detail::ArgumentKey  short2( "l");

      BOOST_REQUIRE_EQUAL( short1, short2);
      BOOST_REQUIRE( !short1.mismatch( short2));

      BOOST_REQUIRE( string_equal( short1, short2));
   } // end scope

   // two identical long
   {
      prog_args::detail::ArgumentKey  long1( "long");
      prog_args::detail::ArgumentKey  long2( "long");

      BOOST_REQUIRE_EQUAL( long1, long2);
      BOOST_REQUIRE( !long1.mismatch( long2));

      BOOST_REQUIRE( string_equal( long1, long2));
   } // end scope

   // both with short and long
   {
      prog_args::detail::ArgumentKey  both1( "l,long");
      prog_args::detail::ArgumentKey  both2( "long,l");

      BOOST_REQUIRE_EQUAL( both1, both2);
      BOOST_REQUIRE_EQUAL( both2, both1);
      BOOST_REQUIRE( !both1.mismatch( both2));
      BOOST_REQUIRE( !both2.mismatch( both1));

      BOOST_REQUIRE( string_equal( both1, both2));
   } // end scope

   // one with both short and long, the other with short only
   {
      prog_args::detail::ArgumentKey  both1( "l,long");
      prog_args::detail::ArgumentKey  short2( "l");

      BOOST_REQUIRE_EQUAL( both1, short2);
      BOOST_REQUIRE_EQUAL( short2, both1);
      BOOST_REQUIRE( !both1.mismatch( short2));
      BOOST_REQUIRE( !short2.mismatch( both1));
   } // end scope

   // one with both short and long, the other with short only
   {
      prog_args::detail::ArgumentKey  short1( "l");
      prog_args::detail::ArgumentKey  both2( "long,l");

      BOOST_REQUIRE_EQUAL( short1, both2);
      BOOST_REQUIRE_EQUAL( both2, short1);
      BOOST_REQUIRE( !short1.mismatch( both2));
      BOOST_REQUIRE( !both2.mismatch( short1));
   } // end scope

   // one with both short and long, the other with long only
   {
      prog_args::detail::ArgumentKey  both1( "l,long");
      prog_args::detail::ArgumentKey  long2( "long");

      BOOST_REQUIRE_EQUAL( both1, long2);
      BOOST_REQUIRE_EQUAL( long2, both1);
      BOOST_REQUIRE( !both1.mismatch( long2));
      BOOST_REQUIRE( !long2.mismatch( both1));
   } // end scope

   // one with both short and long, the other with short only
   {
      prog_args::detail::ArgumentKey  long1( "long");
      prog_args::detail::ArgumentKey  both2( "long,l");

      BOOST_REQUIRE_EQUAL( long1, both2);
      BOOST_REQUIRE_EQUAL( both2, long1);
      BOOST_REQUIRE( !long1.mismatch( both2));
      BOOST_REQUIRE( !both2.mismatch( long1));
   } // end scope

} // end test_comparison



/// Test all comparisons that fail.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_comparison_failed)
{

   // two different short
   {
      prog_args::detail::ArgumentKey  short1( "l");
      prog_args::detail::ArgumentKey  short2( "s");

      BOOST_REQUIRE_NE( short1, short2);
      BOOST_REQUIRE( !short1.mismatch( short2));
   } // end scope

   // two different long
   {
      prog_args::detail::ArgumentKey  long1( "long");
      prog_args::detail::ArgumentKey  long2( "short");

      BOOST_REQUIRE_NE( long1, long2);
      BOOST_REQUIRE( !long1.mismatch( long2));
   } // end scope

   // short and long
   {
      prog_args::detail::ArgumentKey  short1( "l");
      prog_args::detail::ArgumentKey  long2( "long");

      BOOST_REQUIRE_NE( short1, long2);
      BOOST_REQUIRE( !short1.mismatch( long2));
   } // end scope

   // short and long
   {
      prog_args::detail::ArgumentKey  long1( "long");
      prog_args::detail::ArgumentKey  short2( "l");

      BOOST_REQUIRE_NE( long1, short2);
      BOOST_REQUIRE( !long1.mismatch( short2));
   } // end scope

   // both short and long
   {
      prog_args::detail::ArgumentKey  both1( "s,short");
      prog_args::detail::ArgumentKey  both2( "l,long");

      BOOST_REQUIRE_NE( both1, both2);
      BOOST_REQUIRE( !both1.mismatch( both2));
   } // end scope

   // short and both
   {
      prog_args::detail::ArgumentKey  short1( "s");
      prog_args::detail::ArgumentKey  both2( "l,long");

      BOOST_REQUIRE_NE( short1, both2);
      BOOST_REQUIRE( !short1.mismatch( both2));
   } // end scope

   // long and both
   {
      prog_args::detail::ArgumentKey  long1( "short");
      prog_args::detail::ArgumentKey  both2( "l,long");

      BOOST_REQUIRE_NE( long1, both2);
      BOOST_REQUIRE( !long1.mismatch( both2));
   } // end scope

   // both and short
   {
      prog_args::detail::ArgumentKey  both1( "l,long");
      prog_args::detail::ArgumentKey  short2( "s");

      BOOST_REQUIRE_NE( both1, short2);
      BOOST_REQUIRE( !both1.mismatch( short2));
   } // end scope

   // both and long
   {
      prog_args::detail::ArgumentKey  both1( "s,short");
      prog_args::detail::ArgumentKey  long2( "long");

      BOOST_REQUIRE_NE( both1, long2);
      BOOST_REQUIRE( !both1.mismatch( long2));
   } // end scope

} // end test_comparison_failed



/// Test that mismatch is detected.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_mismatch)
{

   // two different short
   {
      prog_args::detail::ArgumentKey  both1( "s,short");
      prog_args::detail::ArgumentKey  both2( "y,short");

      BOOST_REQUIRE_NE( both1, both2);
      BOOST_REQUIRE( both1.mismatch( both2));
   } // end scope

   // two different long
   {
      prog_args::detail::ArgumentKey  both1( "s,short");
      prog_args::detail::ArgumentKey  both2( "s,symbol");

      BOOST_REQUIRE_EQUAL( both1, both2);
      BOOST_REQUIRE( both1.mismatch( both2));
   } // end scope

} // end test_mismatch



/// Test that copies contain the same values.
/// @since  0.2, 06.04.2016
BOOST_AUTO_TEST_CASE( test_copies)
{

   // copy of key with only short argument
   {
      prog_args::detail::ArgumentKey  short1( "s");
      prog_args::detail::ArgumentKey  copy1( short1);

      BOOST_REQUIRE_EQUAL( short1, copy1);
      BOOST_REQUIRE( !short1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( short1, copy1));
   } // end scope

   // copy of key with only long argument
   {
      prog_args::detail::ArgumentKey  long1( "long");
      prog_args::detail::ArgumentKey  copy1( long1);

      BOOST_REQUIRE_EQUAL( long1, copy1);
      BOOST_REQUIRE( !long1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( long1, copy1));
   } // end scope

   // copy of key with both short and long argument
   {
      prog_args::detail::ArgumentKey  both1( "s,symbol");
      prog_args::detail::ArgumentKey  copy1( both1);

      BOOST_REQUIRE_EQUAL( both1, copy1);
      BOOST_REQUIRE( !both1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( both1, copy1));
   } // end scope

   // assign/overwrite long with short
   {
      prog_args::detail::ArgumentKey  short1( "s");
      prog_args::detail::ArgumentKey  copy1( "long");

      copy1 = short1;

      BOOST_REQUIRE_EQUAL( short1, copy1);
      BOOST_REQUIRE( !short1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( short1, copy1));
   } // end scope

   // assign/overwrite short with long
   {
      prog_args::detail::ArgumentKey  long1( "long");
      prog_args::detail::ArgumentKey  copy1( "s");

      copy1 = long1;

      BOOST_REQUIRE_EQUAL( long1, copy1);
      BOOST_REQUIRE( !long1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( long1, copy1));
   } // end scope

   // assign/overwrite both with short
   {
      prog_args::detail::ArgumentKey  short1( "s");
      prog_args::detail::ArgumentKey  copy1( "l,long");

      copy1 = short1;

      BOOST_REQUIRE_EQUAL( short1, copy1);
      BOOST_REQUIRE( !short1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( short1, copy1));
   } // end scope

   // assign/overwrite both with long
   {
      prog_args::detail::ArgumentKey  long1( "long");
      prog_args::detail::ArgumentKey  copy1( "s,symbol");

      copy1 = long1;

      BOOST_REQUIRE_EQUAL( long1, copy1);
      BOOST_REQUIRE( !long1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( long1, copy1));
   } // end scope

   // assign/overwrite short with both
   {
      prog_args::detail::ArgumentKey  both1( "s,symbol");
      prog_args::detail::ArgumentKey  copy1( "l");

      copy1 = both1;

      BOOST_REQUIRE_EQUAL( both1, copy1);
      BOOST_REQUIRE( !both1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( both1, copy1));
   } // end scope

   // assign/overwrite long with both
   {
      prog_args::detail::ArgumentKey  both1( "l,long");
      prog_args::detail::ArgumentKey  copy1( "symbol");

      copy1 = both1;

      BOOST_REQUIRE_EQUAL( both1, copy1);
      BOOST_REQUIRE( !both1.mismatch( copy1));

      BOOST_REQUIRE( string_equal( both1, copy1));
   } // end scope

   // assign/overwrite long with both
   {
      prog_args::detail::ArgumentKey  both1( "l,long");
      prog_args::detail::ArgumentKey  long1( "symbol");

      both1 = prog_args::detail::ArgumentKey( "symbol");

      BOOST_REQUIRE_EQUAL( both1, long1);
      BOOST_REQUIRE( !both1.mismatch( long1));

      BOOST_REQUIRE( string_equal( both1, long1));
   } // end scope

} // end test_copies



// =========================  END OF test_argument_key.cpp  =========================

