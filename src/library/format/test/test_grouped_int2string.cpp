
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the functions of the module grouped_int2string.
**
--*/


// first include the module header to test
#include "celma/format/grouped_int2string.hpp"


// C++ Standard Library includes
#include <iostream>
#include <limits>


// Boost includes
#define BOOST_TEST_MODULE GroupedInt2StringTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/format/string_to.hpp"
#include "celma/test/check_return.hpp"


namespace {


/// Converts string with a grouped integer to the integer value.
///
/// @tparam  T  The type of the integer.
/// @param[in]  str  The string with the value to convert.
/// @return  The converted value from the string.
/// @since  1.17.0, 24.11.2018
template< typename T> T groupedString2int( std::string str)
{

   auto  pos = str.find( "'");


   while (pos != std::string::npos)
   {
      str.erase( pos, 1);
      pos = str.find( "'");
   } // end while

   return celma::format::stringTo< T>( str);
} // groupedString2int


/// Test function for converting unsigned integers to grouped string using the
/// grouped_int2string() function. Checks with 0 and the maximum value.
///
/// @tparam  T  The type of the integer.
/// @return  \c true if all checks succeeded.
/// @since  1.17.0, 24.11.2018
template< typename T> bool check_unsigned()
{

   using celma::format::grouped_int2string;

   T  unsigned_int = 0;


   CHECK_EQUAL_RETURN( grouped_int2string( unsigned_int), "0");

   unsigned_int = std::numeric_limits< T>::max();
   auto  int_str( grouped_int2string( unsigned_int));
   CHECK_EQUAL_RETURN( unsigned_int, groupedString2int< T>( int_str));

   return true;
} // check_unsigned


/// Test function for converting signed integers to grouped string using the
/// grouped_int2string() function. Checks with 0, the minimum and the maximum
/// value.
///
/// @tparam  T  The type of the integer.
/// @return  \c true if all checks succeeded.
/// @since  1.17.0, 24.11.2018
template< typename T> bool check_signed()
{

   using celma::format::grouped_int2string;

   T  signed_int = 0;


   CHECK_EQUAL_RETURN( grouped_int2string( signed_int), "0");

   signed_int = std::numeric_limits< T>::min();
   auto  int_str( grouped_int2string( signed_int));
   CHECK_EQUAL_RETURN( signed_int, groupedString2int< T>( int_str));

   signed_int = std::numeric_limits< T>::max();
   int_str = grouped_int2string( signed_int);
   CHECK_EQUAL_RETURN( signed_int, groupedString2int< T>( int_str));

   return true;
} // check_signed


/// Test function for converting unsigned integers to grouped string using the
/// GroupedInt<> template class. Checks with 0 and the maximum value.
///
/// @tparam  T  The type of the integer.
/// @return  \c true if all checks succeeded.
/// @since  1.17.0, 24.11.2018
template< typename T> bool check_unsigned_stream()
{

   using celma::format::GroupedInt;

   std::ostringstream  oss;
   GroupedInt< T>      gi;


   oss << gi;
   CHECK_EQUAL_RETURN( oss.str(), "0");

   gi = std::numeric_limits< T>::max();
   oss.str( "");
   oss << gi;
   CHECK_EQUAL_RETURN( static_cast< T>( gi), groupedString2int< T>( oss.str()));

   return true;
} // check_unsigned_stream


/// Test function for converting signed integers to grouped string using the
/// GroupedInt<> template class. Checks with 0, the minimum and the maximum
/// value.
///
/// @tparam  T  The type of the integer.
/// @return  \c true if all checks succeeded.
/// @since  1.17.0, 24.11.2018
template< typename T> bool check_signed_stream()
{

   using celma::format::GroupedInt;

   std::ostringstream  oss;
   GroupedInt< T>      gi;


   oss << gi;
   CHECK_EQUAL_RETURN( oss.str(), "0");

   gi = std::numeric_limits< T>::min();
   oss.str( "");
   oss << gi;
   CHECK_EQUAL_RETURN( static_cast< T>( gi), groupedString2int< T>( oss.str()));

   gi = std::numeric_limits< T>::max();
   oss.str( "");
   oss << gi;
   CHECK_EQUAL_RETURN( static_cast< T>( gi), groupedString2int< T>( oss.str()));

   return true;
} // check_signed_stream


/// Test function for converting unsigned integers to grouped string using the
/// template function that returns a GroupedInt<> object. Checks with 0 and the
/// maximum value.
///
/// @tparam  T  The type of the integer.
/// @return  \c true if all checks succeeded.
/// @since  1.17.0, 24.11.2018
template< typename T> bool check_unsigned_stream_function()
{

   using celma::format::groupedInt;

   std::ostringstream  oss;
   T                   unsigned_int = 0;


   oss << groupedInt( unsigned_int);
   CHECK_EQUAL_RETURN( oss.str(), "0");

   unsigned_int = std::numeric_limits< T>::max();
   oss.str( "");
   oss << groupedInt( unsigned_int);
   CHECK_EQUAL_RETURN( unsigned_int, groupedString2int< T>( oss.str()));

   return true;
} // check_unsigned_stream_function


/// Test function for converting unsigned integers to grouped string using the
/// template function that returns a GroupedInt<> object. Checks with 0, the
/// minimum and the maximum value.
///
/// @tparam  T  The type of the integer.
/// @return  \c true if all checks succeeded.
/// @since  1.17.0, 24.11.2018
template< typename T> bool check_signed_stream_function()
{

   using celma::format::groupedInt;

   std::ostringstream  oss;
   T                   signed_int = 0;


   oss << groupedInt( signed_int);
   CHECK_EQUAL_RETURN( oss.str(), "0");

   signed_int = std::numeric_limits< T>::min();
   oss.str( "");
   oss << groupedInt( signed_int);
   CHECK_EQUAL_RETURN( signed_int, groupedString2int< T>( oss.str()));

   signed_int = std::numeric_limits< T>::max();
   oss.str( "");
   oss << groupedInt( signed_int);
   CHECK_EQUAL_RETURN( signed_int, groupedString2int< T>( oss.str()));

   return true;
} // check_signed_stream_function


} // namespace



/// Test that the grouped_int2string conversion works for all integer types.
///
/// @since  1.17.0, 22.11.2018
BOOST_AUTO_TEST_CASE( test_types)
{

   BOOST_REQUIRE( check_unsigned< uint8_t>());
   BOOST_REQUIRE( check_signed< int8_t>());
   BOOST_REQUIRE( check_unsigned< uint16_t>());
   BOOST_REQUIRE( check_signed< int16_t>());
   BOOST_REQUIRE( check_unsigned< uint32_t>());
   BOOST_REQUIRE( check_signed< int32_t>());
   BOOST_REQUIRE( check_unsigned< uint64_t>());
   BOOST_REQUIRE( check_signed< int64_t>());

} // test_types



/// Test that the conversion using GroupedInt<> works for all integer types.
///
/// @since  1.17.0, 22.11.2018
BOOST_AUTO_TEST_CASE( test_stream)
{

   BOOST_REQUIRE( check_unsigned_stream< uint8_t>());
   BOOST_REQUIRE( check_signed_stream< int8_t>());
   BOOST_REQUIRE( check_unsigned_stream< uint16_t>());
   BOOST_REQUIRE( check_signed_stream< int16_t>());
   BOOST_REQUIRE( check_unsigned_stream< uint32_t>());
   BOOST_REQUIRE( check_signed_stream< int32_t>());
   BOOST_REQUIRE( check_unsigned_stream< uint64_t>());
   BOOST_REQUIRE( check_signed_stream< int64_t>());

} // test_stream



/// Test that the conversion using GroupedInt<> works for all integer types.
///
/// @since  1.17.0, 24.11.2018
BOOST_AUTO_TEST_CASE( test_stream_function)
{

   BOOST_REQUIRE( check_unsigned_stream_function< uint8_t>());
   BOOST_REQUIRE( check_signed_stream_function< int8_t>());
   BOOST_REQUIRE( check_unsigned_stream_function< uint16_t>());
   BOOST_REQUIRE( check_signed_stream_function< int16_t>());
   BOOST_REQUIRE( check_unsigned_stream_function< uint32_t>());
   BOOST_REQUIRE( check_signed_stream_function< int32_t>());
   BOOST_REQUIRE( check_unsigned_stream_function< uint64_t>());
   BOOST_REQUIRE( check_signed_stream_function< int64_t>());

} // test_stream_function



// =====  END OF test_grouped_int2string.cpp  =====

