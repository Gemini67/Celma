
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template class celma::common::RelOpsFromLess<>, using
**    the Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/common/comparable.hpp"


// Boost includes
#define BOOST_TEST_MODULE RelOpsFromLessTest
#include <boost/test/unit_test.hpp>


namespace {


/// Helper class for the test program. Implemets the less comparison operator.
/// @since  1.11.0, 24.18.2018
class Comparable: public celma::common::RelOpsFromLess< Comparable>
{
public:
   /// Constructor. Stores the value to use for the comparisons.
   /// @param[in]  val  The value to store.
   /// @since  1.11.0, 24.08.2018
   explicit Comparable( int val):
      mValue( val)
   {
   } // Comparable::Comparable

   /// Less comparison operator.
   /// @param[in]  other  The other object to compare against.
   /// @return  \c true if this is less than a other.
   /// @since  1.11.0, 24.08.2018
   bool operator <( const Comparable& other) const
   {
      return mValue < other.mValue;
   } // Comparable::opertor <

private:
   /// The value to cpmare against.
   const int  mValue;

}; // Comparable


} // namespace



/// Tries all comparison operations.
/// @since  1.11.0, 24.18.2018
BOOST_AUTO_TEST_CASE( basic)
{

   Comparable  c1( 7);
   Comparable  c2( 11);


   BOOST_REQUIRE( c1 < c2);

   BOOST_REQUIRE( c1 <= c1);
   BOOST_REQUIRE( c2 <= c2);
   BOOST_REQUIRE( c1 <= c2);
   BOOST_REQUIRE( !(c2 <= c1));

   BOOST_REQUIRE( !(c1 == c2));
   BOOST_REQUIRE( !(c2 == c1));
   BOOST_REQUIRE( c1 == c1);
   BOOST_REQUIRE( c2 == c2);

   BOOST_REQUIRE( c1 != c2);
   BOOST_REQUIRE( c2 != c1);
   BOOST_REQUIRE( !(c1 != c1));
   BOOST_REQUIRE( !(c2 != c2));

   BOOST_REQUIRE( !(c1 >= c2));
   BOOST_REQUIRE( c2 >= c1);
   BOOST_REQUIRE( c1 >= c1);
   BOOST_REQUIRE( c2 >= c2);

   BOOST_REQUIRE( !(c1 > c2));
   BOOST_REQUIRE( c2 > c1);
   BOOST_REQUIRE( !(c1 > c1));
   BOOST_REQUIRE( !(c2 > c2));

} // basic



// =====  END OF test_rel_ops_from_less.cpp  =====

