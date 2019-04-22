
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test header file include
#include "celma/format/size_handling.hpp"


// OS/C lib includes
#include <cstring>


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE SizeHandlingTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/check_return.hpp"


namespace {


/// Helper function to test the size formatting with streams and with the
/// printf()-like function.
///
/// @tparam  T  The type of the value to format.
/// @param[in]  value
///    The value to format.
/// @param[in]  exp_result
///    The expected result of the formatting.
/// @return
///    \c false if the result of the formatting does not equal the given
///    expected result.
/// @since  1.24.0, 17.04.2019
template< typename T>
   bool checkFormatSize( const T& value, const std::string exp_result)
{

   using celma::format::formatSize;

   // check with stream
   std::ostringstream  oss;
   formatSize( oss, value);
   CHECK_EQUAL_RETURN( exp_result, oss.str());

   // check with printf format
   char  buffer[ 30];
   formatSize( buffer, value);
   CHECK_EQUAL_RETURN( exp_result, buffer);

   return true;
} // checkFormatSize


} // namespace



/// Test if div2unit() returns correct values.
///
/// @since  1.24.0, 17.04.2019
BOOST_AUTO_TEST_CASE( test_div2unit)
{

   using celma::format::div2unit;


   double  testval = 0.0;
   BOOST_REQUIRE_EQUAL( div2unit( testval), 0);
   BOOST_REQUIRE_EQUAL( testval, 0.0);

   testval = 1.0;
   BOOST_REQUIRE_EQUAL( div2unit( testval), 0);
   BOOST_REQUIRE_EQUAL( testval, 1.0);

   testval = 1023.0;
   BOOST_REQUIRE_EQUAL( div2unit( testval), 0);
   BOOST_REQUIRE_EQUAL( testval, 1023.0);

   testval = 1024.0;
   BOOST_REQUIRE_EQUAL( div2unit( testval), 1);
   BOOST_REQUIRE_EQUAL( testval, 1.0);

   testval = 1025.0;
   BOOST_REQUIRE_EQUAL( div2unit( testval), 1);
   BOOST_REQUIRE_EQUAL( testval, 1025.0 / 1024.0);

   testval = 1024.0 * 1024.0 - 1;
   BOOST_REQUIRE_EQUAL( div2unit( testval), 1);
   BOOST_REQUIRE_EQUAL( testval, (1024.0 * 1024.0 - 1) / 1024.0);

   testval = 1024.0 * 1024.0;
   BOOST_REQUIRE_EQUAL( div2unit( testval), 2);
   BOOST_REQUIRE_EQUAL( testval, 1.0);

   testval = 1024.0 * 1024.0 + 1;
   BOOST_REQUIRE_EQUAL( div2unit( testval), 2);
   BOOST_REQUIRE_EQUAL( testval, (1024.0 * 1024.0 + 1) / 1024.0 / 1024.0);

} // test_div2unit



/// Test if numDivs2Name return correct values.
///
/// @since  1.24.0, 17.04.2019
BOOST_AUTO_TEST_CASE( test_numDivs2Name)
{

   using celma::format::numDivs2Name;


   BOOST_REQUIRE( ::strcmp( numDivs2Name( 0), "bytes") == 0);
   BOOST_REQUIRE( ::strcmp( numDivs2Name( 1), "kbytes") == 0);
   BOOST_REQUIRE( ::strcmp( numDivs2Name( 2), "Mbytes") == 0);
   BOOST_REQUIRE( ::strcmp( numDivs2Name( 3), "Gbytes") == 0);
   BOOST_REQUIRE( ::strcmp( numDivs2Name( 4), "Tbytes") == 0);
   BOOST_REQUIRE( ::strcmp( numDivs2Name( 5), "Pbytes") == 0);
   BOOST_REQUIRE( ::strcmp( numDivs2Name( 6), "Ebytes") == 0);

   BOOST_REQUIRE( ::strcmp( numDivs2Name( -1), "out of range") == 0);
   BOOST_REQUIRE( ::strcmp( numDivs2Name(  7), "out of range") == 0);

} // test_numDivs2Name



/// Function formatSize() does the whole formatting.
///
/// @since  1.24.0, 17.04.2019
BOOST_AUTO_TEST_CASE( format_size)
{

   BOOST_REQUIRE( checkFormatSize( 1000, "1000.0 bytes"));
   BOOST_REQUIRE( checkFormatSize( 10000, "   9.8 kbytes"));
   BOOST_REQUIRE( checkFormatSize( 100000, "  97.7 kbytes"));
   BOOST_REQUIRE( checkFormatSize( 1000000, " 976.6 kbytes"));
   BOOST_REQUIRE( checkFormatSize( 1024000, "1000.0 kbytes"));
   BOOST_REQUIRE( checkFormatSize( 10000000, "   9.5 Mbytes"));
   BOOST_REQUIRE( checkFormatSize( 100000000, "  95.4 Mbytes"));
   BOOST_REQUIRE( checkFormatSize( 1000000000, " 953.7 Mbytes"));
   BOOST_REQUIRE( checkFormatSize( 1048576000, "1000.0 Mbytes"));
   BOOST_REQUIRE( checkFormatSize( 10000000000L, "   9.3 Gbytes"));
   BOOST_REQUIRE( checkFormatSize( 100000000000L, "  93.1 Gbytes"));
   BOOST_REQUIRE( checkFormatSize( 1000000000000L, " 931.3 Gbytes"));
   BOOST_REQUIRE( checkFormatSize( 1073741824000L, "1000.0 Gbytes"));
   BOOST_REQUIRE( checkFormatSize( 10000000000000L, "   9.1 Tbytes"));

} // format_size



// =====  END OF test_size_handling.cpp  =====

