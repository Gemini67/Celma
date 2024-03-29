
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "value range" in the module
**    prog_args::Handler, using the Boost.Test module.
**
--*/


// module to test, headerfile include
#include "celma/prog_args.hpp"


// C++ Standard Library includes
#include <bitset>
#include <iostream>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE ArgHRangeTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/prog_args/eval_argument_string.hpp"


using celma::prog_args::Handler;



/// Test that errors are caught.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_errors)
{

   // wrong setup: value checks not allowed on ranges
   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      BOOST_REQUIRE_THROW( ah.addArgument( "v", DEST_RANGE( myVec, int, std::vector), "Integer")
                                         ->addCheck( celma::prog_args::range( 1, 100)),
                           std::logic_error);
   } // end scope

   // wrong usage: mandatory free argument not found
   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      BOOST_REQUIRE_NO_THROW( ah.addArgument( "-", DEST_RANGE( myVec, int, std::vector), "Integer")
                                            ->setIsMandatory());
      BOOST_REQUIRE_THROW( evalArgumentString( ah, ""), std::runtime_error);
   } // end scope

} // test_errors



/// Test with destination type = vector.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_vector)
{

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "v", DEST_RANGE( myVec, int, std::vector), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
      BOOST_REQUIRE( myVec.empty());
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "v", DEST_RANGE( myVec, int, std::vector), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 10,20,40"));
      BOOST_REQUIRE( !myVec.empty());
      BOOST_REQUIRE_EQUAL( myVec.size(), 3);
      BOOST_REQUIRE_EQUAL( myVec[ 0], 10);
      BOOST_REQUIRE_EQUAL( myVec[ 1], 20);
      BOOST_REQUIRE_EQUAL( myVec[ 2], 40);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "v", DEST_RANGE( myVec, int, std::vector), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 3-9"));
      BOOST_REQUIRE( !myVec.empty());
      BOOST_REQUIRE_EQUAL( myVec.size(), 7);
      BOOST_REQUIRE_EQUAL( myVec[ 0], 3);
      BOOST_REQUIRE_EQUAL( myVec[ 1], 4);
      BOOST_REQUIRE_EQUAL( myVec[ 2], 5);
      BOOST_REQUIRE_EQUAL( myVec[ 3], 6);
      BOOST_REQUIRE_EQUAL( myVec[ 4], 7);
      BOOST_REQUIRE_EQUAL( myVec[ 5], 8);
      BOOST_REQUIRE_EQUAL( myVec[ 6], 9);
   } // end scope

} // test_vector



/// Test with destination type = vector, range set as free argument.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_vector_free)
{

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "-", DEST_RANGE( myVec, int, std::vector), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
      BOOST_REQUIRE( myVec.empty());
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "-", DEST_RANGE( myVec, int, std::vector), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "10,20,40"));
      BOOST_REQUIRE( !myVec.empty());
      BOOST_REQUIRE_EQUAL( myVec.size(), 3);
      BOOST_REQUIRE_EQUAL( myVec[ 0], 10);
      BOOST_REQUIRE_EQUAL( myVec[ 1], 20);
      BOOST_REQUIRE_EQUAL( myVec[ 2], 40);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "-", DEST_RANGE( myVec, int, std::vector), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "3-9"));
      BOOST_REQUIRE( !myVec.empty());
      BOOST_REQUIRE_EQUAL( myVec.size(), 7);
      BOOST_REQUIRE_EQUAL( myVec[ 0], 3);
      BOOST_REQUIRE_EQUAL( myVec[ 1], 4);
      BOOST_REQUIRE_EQUAL( myVec[ 2], 5);
      BOOST_REQUIRE_EQUAL( myVec[ 3], 6);
      BOOST_REQUIRE_EQUAL( myVec[ 4], 7);
      BOOST_REQUIRE_EQUAL( myVec[ 5], 8);
      BOOST_REQUIRE_EQUAL( myVec[ 6], 9);
   } // end scope

} // test_vector_free



/// Test with destination type = bitset.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_bitset)
{

   {
      Handler             ah( 0);
      std::bitset< 1024>  myBitset;

      ah.addArgument( "v", DEST_RANGE_BITSET( myBitset, 1024), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
      BOOST_REQUIRE( myBitset.none());
   } // end scope

   {
      Handler             ah( 0);
      std::bitset< 1024>  myBitset;

      ah.addArgument( "v", DEST_RANGE_BITSET( myBitset, 1024), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 10,20,40"));
      BOOST_REQUIRE( !myBitset.none());
      BOOST_REQUIRE_EQUAL( myBitset.count(), 3);
      BOOST_REQUIRE( myBitset[ 10]);
      BOOST_REQUIRE( myBitset[ 20]);
      BOOST_REQUIRE( myBitset[ 40]);
   } // end scope

   {
      Handler             ah( 0);
      std::bitset< 1024>  myBitset;

      ah.addArgument( "v", DEST_RANGE_BITSET( myBitset, 1024), "Integer");

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 3-9"));
      BOOST_REQUIRE( !myBitset.none());
      BOOST_REQUIRE_EQUAL( myBitset.count(), 7);
      BOOST_REQUIRE( myBitset[ 3]);
      BOOST_REQUIRE( myBitset[ 4]);
      BOOST_REQUIRE( myBitset[ 5]);
      BOOST_REQUIRE( myBitset[ 6]);
      BOOST_REQUIRE( myBitset[ 7]);
      BOOST_REQUIRE( myBitset[ 8]);
      BOOST_REQUIRE( myBitset[ 9]);
   } // end scope

} // test_bitset



namespace {



/// Helper class to test the formatting feature.
/// @since  0.2, 10.04.2016
class WildcardRangeFormat: public celma::prog_args::detail::IFormat
{
public:
   /// Constructor, sets the formatters name in the base class.
   ///
   /// @since  1.33.0, 05.11.2019
   WildcardRangeFormat():
      IFormat( "wildcard-range")
   {
   } // WildcardRangeFormat::WildcardRangeFormat

   /// Changes the string 'all' into '0'.
   /// @param[in,out]  val  The string to check/change.
   /// @since  0.2, 10.04.2016
   virtual void formatValue( std::string& val) const
   {
      if (val == "all")
      {
         val = "0";
      } // end if
   } // end WildcardRangeFormat::formatValue
   
}; // WildcardRangeFormat



} // namespace



/// Test with destination type = vector and a formatting method.
/// @since  0.2, 10.04.2016
BOOST_AUTO_TEST_CASE( test_vector_format)
{

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "v", DEST_RANGE( myVec, int, std::vector), "Integer")
                    ->addFormat( new WildcardRangeFormat());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, ""));
      BOOST_REQUIRE( myVec.empty());
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "v", DEST_RANGE( myVec, int, std::vector), "Integer")
                    ->addFormat( new WildcardRangeFormat());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v 10,20"));
      BOOST_REQUIRE( !myVec.empty());
      BOOST_REQUIRE_EQUAL( myVec.size(), 2);
      BOOST_REQUIRE_EQUAL( myVec[ 0], 10);
      BOOST_REQUIRE_EQUAL( myVec[ 1], 20);
   } // end scope

   {
      Handler            ah( 0);
      std::vector< int>  myVec;

      ah.addArgument( "v", DEST_RANGE( myVec, int, std::vector), "Integer")
                    ->addFormat( new WildcardRangeFormat());

      BOOST_REQUIRE_NO_THROW( evalArgumentString( ah, "-v all"));
      BOOST_REQUIRE( !myVec.empty());
      BOOST_REQUIRE_EQUAL( myVec.size(), 1);
      BOOST_REQUIRE_EQUAL( myVec[ 0], 0);
   } // end scope

} // test_vector_format



// =====  END OF test_argh_range_c.cpp  =====

