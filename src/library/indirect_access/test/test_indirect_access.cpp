
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
**    Test program for using the 'indirect access' macros using the Boost.Test
**    framework.
**
--*/


// (indirect) module to test headerfile include
#include "address_record.hpp"


// OS/C lib includes
#include <unistd.h>
#include <cstdlib>


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE IndirectAccessTest
#include <boost/test/unit_test.hpp>



/// Test that errors are caught correctly.
///
/// @since  1.33.1, 13.11.2019
BOOST_AUTO_TEST_CASE( errors)
{

   AddressRecord                 addr1;
   IndirectAccess_AddressRecord  ia_addr1( addr1);


   // unknown field name
   BOOST_REQUIRE_THROW(
      ia_addr1.set( std::string( "Age"), 42), std::runtime_error);

   // wrong type for this field
   BOOST_REQUIRE_THROW(
      ia_addr1.set( std::string( "Name"), 42), std::runtime_error);

   // unknown field name
   BOOST_REQUIRE_THROW(
      ia_addr1.get< int>( std::string( "Age")), std::runtime_error);

   // wrong type for this field
   BOOST_REQUIRE_THROW(
      ia_addr1.get< int>( std::string( "Name")), std::runtime_error);

   // same with ids

   // unknown id
   BOOST_REQUIRE_THROW( ia_addr1.set( 14, 42), std::runtime_error);

   // wrong type
   BOOST_REQUIRE_THROW( ia_addr1.set( 0, 42), std::runtime_error);

   // unknown id
   BOOST_REQUIRE_THROW( ia_addr1.get< int>( 14), std::runtime_error);

   // wrong type
   BOOST_REQUIRE_THROW( ia_addr1.get< int>( 0), std::runtime_error);

   // field index too high
   BOOST_REQUIRE_THROW( ia_addr1.getFieldName( 14), std::runtime_error);
   BOOST_REQUIRE_THROW( ia_addr1.getFieldValueString( 14), std::runtime_error);
   BOOST_REQUIRE_THROW( ia_addr1.getFieldTypeString( 14), std::runtime_error);

} // errors



/// Test the indirect access functions on an address record.
///
/// @since  0.4, 13.07.2016
BOOST_AUTO_TEST_CASE( adress_record_test)
{

   AddressRecord                 addr1;
   IndirectAccess_AddressRecord  ia_addr1( addr1);


   BOOST_REQUIRE_NO_THROW(
      ia_addr1.set( std::string( "Name"), std::string( "Eng")));
   BOOST_REQUIRE_NO_THROW(
      ia_addr1.set( std::string( "FirstName"), std::string( "Rene")));
   BOOST_REQUIRE_NO_THROW( ia_addr1.set( std::string( "PostalCode"), 5037));

   BOOST_REQUIRE_EQUAL( addr1.mName, "Eng");
   BOOST_REQUIRE_EQUAL( addr1.mFirstName, "Rene");
   BOOST_REQUIRE_EQUAL( addr1.mPostalCode, 5037);

   BOOST_REQUIRE_EQUAL( ia_addr1.size(), 3);

   BOOST_REQUIRE_EQUAL( ia_addr1.get< std::string>( std::string( "Name")), "Eng");
   BOOST_REQUIRE_EQUAL( ia_addr1.get< std::string>( std::string( "FirstName")),
                        "Rene");
   BOOST_REQUIRE_EQUAL( ia_addr1.get< int>( std::string( "PostalCode")),
                        5037);

   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldName( 0), "Name");
   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldName( 1), "FirstName");
   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldName( 2), "PostalCode");

   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldValueString( 0), "Eng");
   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldValueString( 1), "Rene");
   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldValueString( 2), "5037");

   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldTypeString( 0), "std::string");
   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldTypeString( 1), "std::string");
   BOOST_REQUIRE_EQUAL( ia_addr1.getFieldTypeString( 2), "int");

   ia_addr1.setName( "Fox");
   ia_addr1.setFirstName( "Peter");
   ia_addr1.setPostalCode( 90125);

   BOOST_REQUIRE_EQUAL( addr1.mName, "Fox");
   BOOST_REQUIRE_EQUAL( addr1.mFirstName, "Peter");
   BOOST_REQUIRE_EQUAL( addr1.mPostalCode, 90125);

   BOOST_REQUIRE_EQUAL( ia_addr1.getName(), "Fox");
   BOOST_REQUIRE_EQUAL( ia_addr1.getFirstName(), "Peter");
   BOOST_REQUIRE_EQUAL( ia_addr1.getPostalCode(), 90125);

   std::ostringstream  oss;
   celma::indirect_access::detail::Base*  bp = &ia_addr1;

   // the following output is generated through the insertion operator of the
   // base class
   // oss << &ia_addr1;   would also work
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

} // adress_record_test



/// Test the indirect access functions on an address record using the field ids.
///
/// @since  1.33.1, 13.11.2019
BOOST_AUTO_TEST_CASE( adress_record_id_test)
{

   AddressRecord                 addr1;
   IndirectAccess_AddressRecord  ia_addr1( addr1);


   BOOST_REQUIRE_NO_THROW( ia_addr1.set( 0, std::string( "Eng")));
   BOOST_REQUIRE_NO_THROW( ia_addr1.set( 1, std::string( "Rene")));
   BOOST_REQUIRE_NO_THROW( ia_addr1.set( 2, 5037));

   BOOST_REQUIRE_EQUAL( addr1.mName, "Eng");
   BOOST_REQUIRE_EQUAL( addr1.mFirstName, "Rene");
   BOOST_REQUIRE_EQUAL( addr1.mPostalCode, 5037);

   BOOST_REQUIRE_EQUAL( ia_addr1.size(), 3);

   BOOST_REQUIRE_EQUAL( ia_addr1.get< std::string>( 0), "Eng");
   BOOST_REQUIRE_EQUAL( ia_addr1.get< std::string>( 1), "Rene");
   BOOST_REQUIRE_EQUAL( ia_addr1.get< int>( 2), 5037);

} // adress_record_id_test



// =====  END OF test_indirect_access.cpp  =====

