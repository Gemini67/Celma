
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the module Properties using the Boost.Test
**    framework.
**
--*/


// test module header file included first
#include "celma/common/properties.hpp"


// Boost includes
#define BOOST_TEST_MODULE PropertiesTest
#include <boost/test/unit_test.hpp>


using celma::common::Properties;


/// 
/// @since  1.2, 19.10.2016
BOOST_AUTO_TEST_CASE( test_prop)
{

   Properties  myProperties;


   myProperties.addProperty( "Name", "Eng");
   myProperties.addProperty( "First Name", "Rene");
   myProperties.addProperty( "Age", 50);

   myProperties.addProperty( "Address.Street", "Erbsacker");
   myProperties.addProperty( "Address.House Number", 4);
   myProperties.addProperty( "Address.Location", "Muhen");
   myProperties.addProperty( "Address.Postal Code", 5037);
   myProperties.addProperty( "Address.Country", "Switzerland");

   myProperties.addProperty( "Address.Phone.Home", "123 45 67 89");
   myProperties.addProperty( "Address.Phone.Mobile", "079 45 67 89");

   int  age = -1;
   BOOST_REQUIRE( myProperties.getProperty( age, "Age"));
   BOOST_REQUIRE_EQUAL( age, 50);

   std::string  first_name;
   BOOST_REQUIRE( myProperties.getProperty( first_name, "First Name"));
   BOOST_REQUIRE_EQUAL( first_name, "Rene");

   std::string  street;
   BOOST_REQUIRE( myProperties.getProperty( street, "Address.Street"));
   BOOST_REQUIRE_EQUAL( street, "Erbsacker");

   std::cout << "my properties:\n" << myProperties << std::endl;

/*
   asking for a property with the wrong type crashes
   std::string  dummy;
   BOOST_REQUIRE( !myProperties.getProperty( dummy, "Age"));
*/

} // end test_prop



// =======================  END OF test_properties.cpp  =======================
