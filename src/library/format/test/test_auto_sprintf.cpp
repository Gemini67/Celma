
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
**    Test program for using the module AutoSprintf using the Boost.Test
**    framework.
**
--*/


// module to test header file include
#include "celma/format/auto_sprintf.hpp"


// C/OS library includes
#include <cstring>


// C++ Standard Library includes
#include <memory>


// Boost includes
#define BOOST_TEST_MODULE AutoSprintfTest
#include <boost/test/unit_test.hpp>


using std::unique_ptr;
using celma::format::AutoSprintf;


namespace {


unique_ptr< AutoSprintf> call_arglist( const char* formatstring, ...);


} // namespace


/// Test AutoSprintf without parameters, i.e. a constant string.
/// @since  0.2, 08.04.2016
BOOST_AUTO_TEST_CASE( test_no_param)
{

   const char* const  text = "actually mis-use AutoSprintf for a string-copy";

   {
      AutoSprintf        as( text);

      BOOST_REQUIRE( ::strcmp( as.c_str(), text) == 0);
      BOOST_REQUIRE( ::strcmp( static_cast< const char*>( as), text) == 0);

      BOOST_REQUIRE_EQUAL( ::strlen( as.c_str()), as.length());
      BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( as)),
                           static_cast< int>( as));
   } // end scope

   // same test case but using the argument-list constructor
   {
      unique_ptr< AutoSprintf>  as_with_arglist( call_arglist( text));

      BOOST_REQUIRE( ::strcmp( as_with_arglist->c_str(), text) == 0);
      BOOST_REQUIRE( ::strcmp( static_cast< const char*>( *as_with_arglist), text) == 0);

      BOOST_REQUIRE_EQUAL( ::strlen( as_with_arglist->c_str()), as_with_arglist->length());
      BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( *as_with_arglist)),
                           static_cast< int>( *as_with_arglist));
   } // end scope

} // test_no_param



/// Test AutoSprintf with all data in one string parameter (with % sign).
/// @since  0.2, 08.04.2016
BOOST_AUTO_TEST_CASE( test_one_param)
{

   const char* const  text = "this is more a test of sprintf() and %-formatting "
                             "than of AutoSprintf, but tell me, how do you test "
                             "that memory was really free'd using free()?";


   {
      AutoSprintf        as( "%s", text);

      BOOST_REQUIRE( ::strcmp( as.c_str(), text) == 0);
      BOOST_REQUIRE( ::strcmp( static_cast< const char*>( as), text) == 0);

      BOOST_REQUIRE_EQUAL( ::strlen( as.c_str()), as.length());
      BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( as)),
                           static_cast< int>( as));
   } // end scope

   // same test case but using the argument-list constructor
   {
      unique_ptr< AutoSprintf>  as_with_arglist( call_arglist( "%s", text));

      BOOST_REQUIRE( ::strcmp( as_with_arglist->c_str(), text) == 0);
      BOOST_REQUIRE( ::strcmp( static_cast< const char*>( *as_with_arglist), text) == 0);

      BOOST_REQUIRE_EQUAL( ::strlen( as_with_arglist->c_str()), as_with_arglist->length());
      BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( *as_with_arglist)),
                           static_cast< int>( *as_with_arglist));
   } // end scope

} // test_one_param



/// Test with some parameters.
/// @since  0.2, 08.04.2016
BOOST_AUTO_TEST_CASE( test_format)
{

   const char* const  format = "format int %d, float %6.4f and a string '%s'.";
   const char* const  text   = "format int 42, float 3.1415 and a string "
                               "'hello world'.";


   {
      AutoSprintf        as( format, 42, 3.1415, "hello world");

      BOOST_REQUIRE( ::strcmp( as.c_str(), text) == 0);
      BOOST_REQUIRE( ::strcmp( static_cast< const char*>( as), text) == 0);

      BOOST_REQUIRE_EQUAL( ::strlen( as.c_str()), as.length());
      BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( as)),
                           static_cast< int>( as));
   } // end scope

   // same test case but using the argument-list constructor
   {
      unique_ptr< AutoSprintf>  as_with_arglist( call_arglist( format, 42, 3.1415, "hello world"));

      BOOST_REQUIRE( ::strcmp( as_with_arglist->c_str(), text) == 0);
      BOOST_REQUIRE( ::strcmp( static_cast< const char*>( *as_with_arglist), text) == 0);

      BOOST_REQUIRE_EQUAL( ::strlen( as_with_arglist->c_str()), as_with_arglist->length());
      BOOST_REQUIRE_EQUAL( ::strlen( static_cast< const char*>( *as_with_arglist)),
                           static_cast< int>( *as_with_arglist));
   } // end scope

} // test_format



namespace {



/// Helper functions. Creates a AutoSprintf object using the argument list
/// constructor.
/// @param[in]  formatstring  The format string to pass.
/// @param[in]  ...           Additional argument for formatting.
/// @return  The newly created AutoSprintf object.
/// @since  0.7, 08.11.2016
unique_ptr< AutoSprintf> call_arglist( const char* formatstring, ...)
{

   va_list  ap;


   ::va_start( ap, formatstring);

   unique_ptr< AutoSprintf>  dest( new AutoSprintf( std::string( formatstring), ap));

   ::va_end( ap);

   return dest;
} // call_arglist



} // namespace


// ======================  END OF test_auto_sprintf.cpp  ======================

