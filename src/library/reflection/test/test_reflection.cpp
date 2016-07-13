
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
**    Test program for using the reflection macros using the Boost.Test
**    framework.
**
--*/


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE ReflectionTest
#include <boost/test/unit_test.hpp>


// project includes
#include "address_record.hpp"



/// Test the reflection functions on an adress record.
/// @since  0.4, 13.07.2016
BOOST_AUTO_TEST_CASE( adress_record_test)
{

   AddressRecord           addr1;
   ReflectedAddressRecord  r_addr1( addr1);


   r_addr1.set( std::string( "Name"), std::string( "Eng"));
   r_addr1.set( std::string( "FirstName"), std::string( "Rene"));
   r_addr1.set( std::string( "PostalCode"), 5037);

   BOOST_REQUIRE_EQUAL( addr1.mName, "Eng");
   BOOST_REQUIRE_EQUAL( addr1.mFirstName, "Rene");
   BOOST_REQUIRE_EQUAL( addr1.mPostalCode, 5037);

   BOOST_REQUIRE_EQUAL( r_addr1.size(), 3);

   BOOST_REQUIRE_EQUAL( r_addr1.get< std::string>( std::string( "Name")), "Eng");
   BOOST_REQUIRE_EQUAL( r_addr1.get< std::string>( std::string( "FirstName")),
                        "Rene");
   BOOST_REQUIRE_EQUAL( r_addr1.get< int>( std::string( "PostalCode")),
                        5037);

   BOOST_REQUIRE_EQUAL( r_addr1.getFieldNameReflected( 0), "Name");
   BOOST_REQUIRE_EQUAL( r_addr1.getFieldNameReflected( 1), "FirstName");
   BOOST_REQUIRE_EQUAL( r_addr1.getFieldNameReflected( 2), "PostalCode");

   BOOST_REQUIRE_EQUAL( r_addr1.getFieldValueString( 0), "Eng");
   BOOST_REQUIRE_EQUAL( r_addr1.getFieldValueString( 1), "Rene");
   BOOST_REQUIRE_EQUAL( r_addr1.getFieldValueString( 2), "5037");

   BOOST_REQUIRE_EQUAL( r_addr1.getFieldTypeString( 0), "std::string");
   BOOST_REQUIRE_EQUAL( r_addr1.getFieldTypeString( 1), "std::string");
   BOOST_REQUIRE_EQUAL( r_addr1.getFieldTypeString( 2), "int");

   r_addr1.setName( "Fox");
   r_addr1.setFirstName( "Peter");
   r_addr1.setPostalCode( 90125);

   BOOST_REQUIRE_EQUAL( addr1.mName, "Fox");
   BOOST_REQUIRE_EQUAL( addr1.mFirstName, "Peter");
   BOOST_REQUIRE_EQUAL( addr1.mPostalCode, 90125);

   BOOST_REQUIRE_EQUAL( r_addr1.getName(), "Fox");
   BOOST_REQUIRE_EQUAL( r_addr1.getFirstName(), "Peter");
   BOOST_REQUIRE_EQUAL( r_addr1.getPostalCode(), 90125);

   std::ostringstream  oss;
   celma::reflection::detail::ReflectedBase*  bp = &r_addr1;

   oss << bp;
   BOOST_REQUIRE_EQUAL( oss.str(),
                        "field idx 0: name='Name', type='std::string', value='Fox'\n"
                        "field idx 1: name='FirstName', type='std::string', value='Peter'\n"
                        "field idx 2: name='PostalCode', type='int', value='90125'"
                        );

   oss.str( "");
   oss << addr1;
   BOOST_REQUIRE_EQUAL( oss.str(),
                        "Name = Fox\n"
                        "FirstName = Peter\n"
                        "PostalCode = 90125\n"
                        );

} // end adress_record_test



// =======================  END OF test_reflection.cpp  =======================

