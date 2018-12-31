
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the template function tuple_at_index using the Boost.Test
**    module.
**
--*/


// module to test header file include
#include "celma/common/tuple_at_index.hpp"


// C++ Standard Library includes
#include <stdexcept>
#include <type_traits>


// Boost includes
#define BOOST_TEST_MODULE TupleLengthBase
#include <boost/test/unit_test.hpp>


using celma::common::tuple_at_index;


namespace {


template< typename T> class ResultCheck
{
public:
   explicit ResultCheck( const T& exp_value):
      mExpectedValue( exp_value),
      mWasCalled( false)
   {
   }

   void operator()( T& value)
   {
      if (value != mExpectedValue)
         throw std::runtime_error( "not expected value");
      mWasCalled = true;
   }

   bool wasCalled() const
   {
      return mWasCalled;
   }
   
private:
   const T  mExpectedValue;
   bool     mWasCalled;

}; // ResultCheck< T>


template< typename T> class MixedTypeResultCheck
{
public:
   MixedTypeResultCheck():
      mWasCalled( false)
   {
   }

   template< typename U> void operator()( U&)
   {
      if (!std::is_same< T, U>::value)
         throw std::invalid_argument( "wrong value type");

      mWasCalled = true;
   }

   bool wasCalled() const
   {
      return mWasCalled;
   }
   
private:
   bool  mWasCalled;

}; // MixedTypeResultCheck< T>


} // namespace



/// Test with a tuple with one single element.
///
/// @since  0.5, 27.09.2016
BOOST_AUTO_TEST_CASE( single_element)
{

   // correct access of first/single element in the tuple
   {
      std::tuple< int>   tup( 42);
      int                idx = 0;
      ResultCheck< int>  rc( 42);
      BOOST_REQUIRE_NO_THROW( tuple_at_index( idx, tup, std::ref( rc)));
      BOOST_REQUIRE( rc.wasCalled());
   } // end scope

   // wrong index
   {
      std::tuple< int>  tup( 42);
      int               idx = 1;
      BOOST_REQUIRE_THROW( tuple_at_index( idx, tup, ResultCheck< int>( 42)), std::out_of_range);
   } // end scope

   // totally wrong index
   {
      std::tuple< int>  tup( 42);
      int               idx = 2;
      BOOST_REQUIRE_THROW( tuple_at_index( idx, tup, ResultCheck< int>( 42)), std::out_of_range);
   } // end scope

} // single_element



/// Test with a tuple with 3 elements.
///
/// @since  0.5, 29.09.2016
BOOST_AUTO_TEST_CASE( three_elements)
{

   // correct access of first element in the tuple
   {
      std::tuple< int, int, int>  tup( 13, 42, 4711);
      int                         idx = 0;
      ResultCheck< int>           rc( 13);
      BOOST_REQUIRE_NO_THROW( tuple_at_index( idx, tup, std::ref( rc)));
      BOOST_REQUIRE( rc.wasCalled());
   } // end scope

   // second element
   {
      std::tuple< int, int, int>  tup( 13, 42, 4711);
      int                         idx = 1;
      ResultCheck< int>           rc( 42);
      BOOST_REQUIRE_NO_THROW( tuple_at_index( idx, tup, std::ref( rc)));
      BOOST_REQUIRE( rc.wasCalled());
   } // end scope

   // third/last element
   {
      std::tuple< int, int, int>  tup( 13, 42, 4711);
      int                         idx = 2;
      ResultCheck< int>           rc( 4711);
      BOOST_REQUIRE_NO_THROW( tuple_at_index( idx, tup, std::ref( rc)));
      BOOST_REQUIRE( rc.wasCalled());
   } // end scope

   // third/last element
   {
      std::tuple< int, int, int>  tup( 13, 42, 4711);
      int                         idx = 2;
      ResultCheck< int>           rc( 4711);
      BOOST_REQUIRE_NO_THROW( tuple_at_index( idx, tup, std::ref( rc)));
      BOOST_REQUIRE( rc.wasCalled());
   } // end scope

   // invalid index
   {
      std::tuple< int, int, int>  tup( 13, 42, 4711);
      int                         idx = 3;
      BOOST_REQUIRE_THROW( tuple_at_index( idx, tup, ResultCheck< int>( -1)), std::out_of_range);
   } // end scope

   // loop access
   std::tuple< int, int, int>  tup( 13, 42, 4711);

   for (int index = 0; index < 3; ++index)
   {
      if (index == 0)
      {
         ResultCheck< int>  rc( 13);
         BOOST_REQUIRE_NO_THROW( tuple_at_index( index, tup, std::ref( rc)));
         BOOST_REQUIRE( rc.wasCalled());
      } else if (index == 1)
      {
         ResultCheck< int>  rc( 42);
         BOOST_REQUIRE_NO_THROW( tuple_at_index( index, tup, std::ref( rc)));
         BOOST_REQUIRE( rc.wasCalled());
      } else
      {
         ResultCheck< int>  rc( 4711);
         BOOST_REQUIRE_NO_THROW( tuple_at_index( index, tup, std::ref( rc)));
         BOOST_REQUIRE( rc.wasCalled());
      } // end if
   } // end for

} // three_elements



/// Test access of a tuple with mixed types.
///
/// @since  0.5, 29.09.2016
BOOST_AUTO_TEST_CASE( mixed_types)
{

   // correct access of first element in the tuple
   {
      std::tuple< int, std::string, double>  tup( 42, "hello world", 3.1415);
      int                                    idx = 0;
      MixedTypeResultCheck< int>             rc;
      BOOST_REQUIRE_NO_THROW( tuple_at_index( idx, tup, std::ref( rc)));
      BOOST_REQUIRE( rc.wasCalled());
   } // end scope

   // wrong access of second element in the tuple
   {
      std::tuple< int, std::string, double>  tup( 42, "hello world", 3.1415);
      int                                    idx = 1;
      MixedTypeResultCheck< int>             rc;
      BOOST_REQUIRE_THROW( tuple_at_index( idx, tup, std::ref( rc)), std::invalid_argument);
   } // end scope

   // correct access of second element in the tuple
   {
      std::tuple< int, std::string, double>  tup( 42, "hello world", 3.1415);
      int                                    idx = 1;
      MixedTypeResultCheck< std::string>     rc;
      BOOST_REQUIRE_NO_THROW( tuple_at_index( idx, tup, std::ref( rc)));
      BOOST_REQUIRE( rc.wasCalled());
   } // end scope

   // correct access for second element, but wrong index
   {
      std::tuple< int, std::string, double>  tup( 42, "hello world", 3.1415);
      int                                    idx = 0;
      MixedTypeResultCheck< std::string>     rc;
      BOOST_REQUIRE_THROW( tuple_at_index( idx, tup, std::ref( rc)), std::invalid_argument);
   } // end scope

} // mixed_types



// =====  END OF test_tuple_at_index.cpp  =====

