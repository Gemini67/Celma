
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of function celma::test::multilineStringCompare().<br>
/// This file does not include the necessary Boost.Test include files, since
/// the "test module" must be defined first.<br>
/// So, define the test module, include the Boost.Test include file(s), and then
/// include this file.


#ifndef CELMA_TEST_MULTILINE_STRING_COMPARE_HPP
#define CELMA_TEST_MULTILINE_STRING_COMPARE_HPP


#include <sstream>
#include <string>
#include "celma/common/multiline_string_compare.hpp"


namespace celma { namespace test {


/// Helper function for test programs: Compare two strings and report, where the
/// difference was found (if any).
///
/// @param[in]  result
///    The result string that was e.g. created by the function to test.
/// @param[in]  expect
///    The expected result string.
/// @return
///    \c true if both strings are equal.
/// @since
///    1.8.0, 25.07.2018
inline bool multilineStringCompare( const std::string& result,
   const std::string& expect)
{

   std::string::size_type  line_nbr = 0;
   std::string::size_type  col = 0;
   std::string::size_type  idx = 0;

   if (!common::multilineStringCompare( idx, line_nbr, col, result, expect))
   {
      std::ostringstream  oss;
      oss << "expected '" << expect[ idx] << "', got '" << result[ idx]
          << "' at line " << line_nbr << ", col " << col;
      BOOST_CHECK_MESSAGE( false, oss.str());
      return false;
   } // end if

   return true;
} // multilineStringCompare


} // namespace test
} // namespace celma


#endif   // CELMA_TEST_MULTILINE_STRING_COMPARE_HPP


// =====  END OF multiline_string_compare.hpp  =====

