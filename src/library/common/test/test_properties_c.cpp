
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


// test module headerfile included first
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
/// @since  1.22.0, 12.03.2019
BOOST_AUTO_TEST_CASE( no_properties)
{

   Properties  myProperties;


   BOOST_REQUIRE( !myProperties.hasProperty( "Year"));
   BOOST_REQUIRE( !myProperties.hasProperty( "Address.Street"));

} // no_properties



/// Test storing and retrieving some properties.
///
/// @since  1.22.0, 19.10.2016
BOOST_AUTO_TEST_CASE( simple_properties)
{

   Properties  myProperties;


   BOOST_REQUIRE( myProperties.addProperty( "Name", "Hugentobler"));
   BOOST_REQUIRE( myProperties.addProperty( "First Name", "Klaus-Peter"));
   BOOST_REQUIRE( myProperties.addProperty( "Age", 50));

   BOOST_REQUIRE( myProperties.addProperty( "Address.Street", "Hochtiefstrasse"));
   BOOST_REQUIRE( myProperties.addProperty( "Address.House Number", 123));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Location", "Muhen"));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Postal Code", 5037));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Country", "Switzerland"));

   BOOST_REQUIRE( myProperties.addProperty( "Address.Phone.Home", "123 45 67 89"));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Phone.Mobile", "079 45 67 89"));

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

   BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
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
/// @since  1.22.0, 12.03.2019
BOOST_AUTO_TEST_CASE( overwrite_properties)
{

   Properties  myProperties;


   BOOST_REQUIRE( myProperties.addProperty( "Name", "Hugentobler"));
   BOOST_REQUIRE( myProperties.addProperty( "First Name", "Klaus-Peter"));
   BOOST_REQUIRE( myProperties.addProperty( "Age", 50));

   BOOST_REQUIRE( myProperties.addProperty( "Address.Street", "Hochtiefstrasse"));
   BOOST_REQUIRE( myProperties.addProperty( "Address.House Number", 123));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Location", "Muhen"));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Postal Code", 5037));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Country", "Switzerland"));

   BOOST_REQUIRE( myProperties.addProperty( "Age", 35));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Country", "Schweiz"));

   int  age = -1;
   BOOST_REQUIRE( myProperties.getProperty( age, "Age"));
   BOOST_REQUIRE_EQUAL( age, 35);

   std::string  country;
   BOOST_REQUIRE( myProperties.getProperty( country, "Address.Country"));
   BOOST_REQUIRE_EQUAL( country, "Schweiz");

} // overwrite_properties



/// Check that a conflict of an existing property (value) and a new property
/// path is detected.
///
/// @since  1.22.0, 19.03.2019
BOOST_AUTO_TEST_CASE( property_conflict)
{

   {
      Properties  myProperties;

      BOOST_REQUIRE( myProperties.addProperty( "Name", "Hugentobler"));
      BOOST_REQUIRE( !myProperties.addProperty( "Name.First", "Peter"));

      std::string  name;
      BOOST_REQUIRE( myProperties.getProperty( name, "Name"));
      BOOST_REQUIRE_EQUAL( name, "Hugentobler");
   } // end scope

   {
      Properties  myProperties;

      BOOST_REQUIRE( myProperties.addProperty( "Name.First", "Peter"));
      BOOST_REQUIRE( !myProperties.addProperty( "Name", "Hugentobler"));

      std::string  name;
      BOOST_REQUIRE( myProperties.getProperty( name, "Name.First"));
      BOOST_REQUIRE_EQUAL( name, "Peter");
   } // end scope

} // property_conflict



/// Create a link to an existing property.
///
/// @since  1.22.0, 21.03.2019
BOOST_AUTO_TEST_CASE( property_link)
{

   Properties  myProperties;


   BOOST_REQUIRE( myProperties.addProperty( "Name", "Hugentobler"));
   BOOST_REQUIRE( myProperties.addLink( "Family Name", "Name"));

   std::string  name;
   BOOST_REQUIRE( myProperties.getProperty( name, "Name"));
   BOOST_REQUIRE_EQUAL( name, "Hugentobler");

   name.clear();
   BOOST_REQUIRE( myProperties.getProperty( name, "Family Name"));
   BOOST_REQUIRE_EQUAL( name, "Hugentobler");

   std::ostringstream  oss;
   oss << myProperties;

   BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
      "Family Name -> Name\n"
      "Name = Hugentobler\n"
   ));

} // property_link



/// Create multiple properties and then add some links.
///
/// @since  1.22.0, 21.03.2019
BOOST_AUTO_TEST_CASE( multiple_links)
{

   Properties  myProperties;


   BOOST_REQUIRE( myProperties.addProperty( "Name", "Hugentobler"));
   BOOST_REQUIRE( myProperties.addProperty( "First Name", "Klaus-Peter"));
   BOOST_REQUIRE( myProperties.addProperty( "Age", 50));

   BOOST_REQUIRE( myProperties.addProperty( "Address.Street", "Hochtiefstrasse"));
   BOOST_REQUIRE( myProperties.addProperty( "Address.House Number", 123));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Location", "Muhen"));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Postal Code", 5037));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Country", "Switzerland"));

   BOOST_REQUIRE( myProperties.addProperty( "Address.Phone.Home", "123 45 67 89"));
   BOOST_REQUIRE( myProperties.addProperty( "Address.Phone.Mobile", "079 45 67 89"));

   BOOST_REQUIRE( myProperties.addLink( "Address.Primary Phone Number", "Address.Phone.Home"));
   BOOST_REQUIRE( myProperties.addLink( "Contacts", "Address.Phone"));

   std::string  value;
   BOOST_REQUIRE( myProperties.getProperty( value, "Address.Primary Phone Number"));
   BOOST_REQUIRE_EQUAL( value, "123 45 67 89");

   value.clear();
   BOOST_REQUIRE( myProperties.getProperty( value, "Contacts.Home"));
   BOOST_REQUIRE_EQUAL( value, "123 45 67 89");

   value.clear();
   BOOST_REQUIRE( myProperties.getProperty( value, "Contacts.Mobile"));
   BOOST_REQUIRE_EQUAL( value, "079 45 67 89");

   std::ostringstream  oss;
   oss << myProperties;

   BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
      "Address:\n"
      "   Country = Switzerland\n"
      "   House Number = 123\n"
      "   Location = Muhen\n"
      "   Phone:\n"
      "      Home = 123 45 67 89\n"
      "      Mobile = 079 45 67 89\n"
      "   Postal Code = 5037\n"
      "   Primary Phone Number -> Address.Phone.Home\n"
      "   Street = Hochtiefstrasse\n"
      "Age = 50\n"
      "Contacts -> Address.Phone\n"
      "First Name = Klaus-Peter\n"
      "Name = Hugentobler\n"
   ));

   // try to add an entry through a link
   BOOST_REQUIRE( myProperties.addProperty( "Contacts.Office", "399 33 44 55"));

   oss.str( "");
   oss << myProperties;

   BOOST_REQUIRE( celma::test::multilineStringCompare( oss,
      "Address:\n"
      "   Country = Switzerland\n"
      "   House Number = 123\n"
      "   Location = Muhen\n"
      "   Phone:\n"
      "      Home = 123 45 67 89\n"
      "      Mobile = 079 45 67 89\n"
      "      Office = 399 33 44 55\n"
      "   Postal Code = 5037\n"
      "   Primary Phone Number -> Address.Phone.Home\n"
      "   Street = Hochtiefstrasse\n"
      "Age = 50\n"
      "Contacts -> Address.Phone\n"
      "First Name = Klaus-Peter\n"
      "Name = Hugentobler\n"
   ));

} // multiple_links



/// Check that wrong access is correctly detected.
///
/// @since  x.y.z, 13.11.2019
BOOST_AUTO_TEST_CASE( errors)
{

   Properties  myProperties;


   BOOST_REQUIRE( myProperties.addProperty( "Name.Family", "Hugentobler"));
   BOOST_REQUIRE( myProperties.addProperty( "Name.First", "Peter"));

   std::string  name;
   BOOST_REQUIRE( !myProperties.getProperty( name, "Name"));
   BOOST_REQUIRE( !myProperties.getProperty( name, "Name.Name"));
   BOOST_REQUIRE( !myProperties.getProperty( name, "Identity.Name"));

   BOOST_REQUIRE( myProperties.addLink( "Identity", "Name.Family"));
   BOOST_REQUIRE( !myProperties.getProperty( name, "Identity.Name"));

   BOOST_REQUIRE( !myProperties.addProperty( "Identity.Age", 42));

   BOOST_REQUIRE( myProperties.addLink( "Shortcut", "Name"));
   BOOST_REQUIRE( !myProperties.getProperty( name, "Shortcut"));

} // errors



// =====  END OF test_properties_c.cpp  =====
