
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
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


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE PropertiesTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/multiline_string_compare.hpp"


using celma::common::Properties;



/// Test with an empty property container.
///
/// @since  x.y.z, 12.03.2019
BOOST_AUTO_TEST_CASE( no_properties)
{

   Properties  myProperties;


   BOOST_REQUIRE( !myProperties.hasProperty( "Year"));
   BOOST_REQUIRE( !myProperties.hasProperty( "Address.Street"));

} // no_properties



/// 
/// @since  x.y.z, 19.10.2016
BOOST_AUTO_TEST_CASE( simple_properties)
{

   Properties  myProperties;


   myProperties.addProperty( "Name", "Hugentobler");
   myProperties.addProperty( "First Name", "Klaus-Peter");
   myProperties.addProperty( "Age", 50);

   myProperties.addProperty( "Address.Street", "Hochtiefstrasse");
   myProperties.addProperty( "Address.House Number", 123);
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
   BOOST_REQUIRE_EQUAL( first_name, "Klaus-Peter");

   std::string  street;
   BOOST_REQUIRE( myProperties.getProperty( street, "Address.Street"));
   BOOST_REQUIRE_EQUAL( street, "Hochtiefstrasse");

   std::ostringstream  oss;
   oss << myProperties;

   BOOST_REQUIRE( celma::test::multilineStringCompare( oss.str(),
      "Address:\n"
      "   Country = Switzerland\n"
      "   House Number = 123\n"
      "   Location = Muhen\n"
      "   Phone:\n"
      "      Home = 123 45 67 89\n"
      "      Mobile = 079 45 67 89\n"
      "   Postal Code = 5037\n"
      "   Street = Hochtiefstrasse\n"
      "Age = 50\n"
      "First Name = Klaus-Peter\n"
      "Name = Hugentobler\n"
   ));

/*
   // asking for a property with the wrong type crashes
   std::string  dummy;
   BOOST_REQUIRE( !myProperties.getProperty( dummy, "Age"));
*/

} // simple_properties



/// Store some properties and then overwrite some with new values.
///
/// @since  x.y.z, 12.03.2019
BOOST_AUTO_TEST_CASE( overwrite_properties)
{

   Properties  myProperties;


   myProperties.addProperty( "Name", "Hugentobler");
   myProperties.addProperty( "First Name", "Klaus-Peter");
   myProperties.addProperty( "Age", 50);

   myProperties.addProperty( "Address.Street", "Hochtiefstrasse");
   myProperties.addProperty( "Address.House Number", 123);
   myProperties.addProperty( "Address.Location", "Muhen");
   myProperties.addProperty( "Address.Postal Code", 5037);
   myProperties.addProperty( "Address.Country", "Switzerland");

   myProperties.addProperty( "Age", 35);
   myProperties.addProperty( "Address.Country", "Schweiz");

   int  age = -1;
   BOOST_REQUIRE( myProperties.getProperty( age, "Age"));
   BOOST_REQUIRE_EQUAL( age, 35);

   std::string  country;
   BOOST_REQUIRE( myProperties.getProperty( country, "Address.Country"));
   BOOST_REQUIRE_EQUAL( country, "Schweiz");

} // overwrite_properties



// =====  END OF test_properties.cpp  =====

