
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the module PropertyIterator using the Boost.Test
**    framework.
**
--*/


// test module headerfile included first
#include "celma/container/properties.hpp"


// C++ Standard Library includes
#include <sstream>


// Boost includes
#define BOOST_TEST_MODULE PropertiesTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/multiline_string_compare.hpp"


using celma::container::Properties;



/// Test with an empty property container.
///
/// @since  1.22.0, 13.03.2019
BOOST_AUTO_TEST_CASE( no_properties)
{

   Properties  myProperties;


   BOOST_REQUIRE( myProperties.begin() == myProperties.end());

   // make sure that access after the end does not crash
   auto  dummy = myProperties.begin();
   BOOST_REQUIRE_NO_THROW( ++dummy);
   BOOST_REQUIRE_NO_THROW( dummy++);
   BOOST_REQUIRE_NO_THROW( std::ignore = dummy.name());
   BOOST_REQUIRE_EQUAL( dummy.name(), "");
   BOOST_REQUIRE_NO_THROW( dummy.pathAndName());
   BOOST_REQUIRE_EQUAL( dummy.pathAndName(), "");

   BOOST_REQUIRE_THROW( std::ignoree = dummy.value< int>(), std::runtime_error);

} // no_properties



/// Test with one top-level property.
/// 
/// @since  1.22.0, 15.03.2019
BOOST_AUTO_TEST_CASE( one_top_level)
{

   Properties  myProperties;


   myProperties.addProperty( "Name", "Hugentobler");

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Name");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Name");

   std::string  value;
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "Hugentobler");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // one_top_level



/// Test with two top-level properties.
/// 
/// @since  1.22.0, 15.03.2019
BOOST_AUTO_TEST_CASE( two_top_level)
{

   Properties  myProperties;


   myProperties.addProperty( "Name", "Hugentobler");
   myProperties.addProperty( "Age", 25);

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Age");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Age");

   int  age_value;
   BOOST_REQUIRE_NO_THROW( age_value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( age_value, 25);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Name");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Name");

   std::string  string_value;
   BOOST_REQUIRE_NO_THROW( string_value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( string_value, "Hugentobler");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // two_top_level



/// Test with one second-level property.
/// 
/// @since  1.22.0, 15.03.2019
BOOST_AUTO_TEST_CASE( one_second_level)
{

   Properties  myProperties;


   myProperties.addProperty( "Address.Street", "Hochtiefstrasse");

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Address");
   BOOST_REQUIRE_EQUAL( iter.name(), "Street");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Address.Street");

   std::string  value;
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "Hochtiefstrasse");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // one_second_level



/// Test with one second-level property.
/// 
/// @since  1.22.0, 18.03.2019
BOOST_AUTO_TEST_CASE( one_top_one_second_level)
{

   Properties  myProperties;


   myProperties.addProperty( "Name", "Hugentobler");
   myProperties.addProperty( "Address.Street", "Hochtiefstrasse");

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Address");
   BOOST_REQUIRE_EQUAL( iter.name(), "Street");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Address.Street");

   std::string  value;
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "Hochtiefstrasse");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Name");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Name");

   std::string  string_value;
   BOOST_REQUIRE_NO_THROW( string_value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( string_value, "Hugentobler");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // one_top_one_second_level



/// Test with two second-level properties.
/// 
/// @since  1.22.0, 19.03.2019
BOOST_AUTO_TEST_CASE( two_second_level)
{

   Properties  myProperties;


   myProperties.addProperty( "Address.Street", "Hochtiefstrasse");
   myProperties.addProperty( "Occupation.Company", "Tea Health Company");

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Address");
   BOOST_REQUIRE_EQUAL( iter.name(), "Street");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Address.Street");

   std::string  value;
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "Hochtiefstrasse");

   BOOST_REQUIRE_NO_THROW( iter++);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Occupation");
   BOOST_REQUIRE_EQUAL( iter.name(), "Company");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Occupation.Company");

   value.clear();
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "Tea Health Company");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // two_second_level



/// Test with properties on levels 1, 2, 1, 2 and 1.
/// 
/// @since  1.22.0, 19.03.2019
BOOST_AUTO_TEST_CASE( changing_levels)
{

   Properties  myProperties;


   myProperties.addProperty( "Aaa", 1);
   myProperties.addProperty( "Bbb.Aaa", 2);
   myProperties.addProperty( "Ccc", 3);
   myProperties.addProperty( "Ddd.Aaa", 4);
   myProperties.addProperty( "Eee", 5);

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Aaa");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Aaa");

   int  value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 1);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Bbb");
   BOOST_REQUIRE_EQUAL( iter.name(), "Aaa");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Bbb.Aaa");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 2);

   BOOST_REQUIRE_NO_THROW( iter++);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Ccc");
   BOOST_REQUIRE_EQUAL( iter.pathAndName(), "Ccc");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 3);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Ddd");
   BOOST_REQUIRE_EQUAL( iter.name(), "Aaa");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 4);

   BOOST_REQUIRE_NO_THROW( iter++);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Eee");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 5);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // changing_levels



/// Test with properties on levels 1, 2, 3, 1, 2 and 3.
/// 
/// @since  1.22.0, 19.03.2019
BOOST_AUTO_TEST_CASE( increasing_levels)
{

   Properties  myProperties;


   myProperties.addProperty( "Aaa", 1);
   myProperties.addProperty( "Bbb.Ccc", 2);
   myProperties.addProperty( "Ddd.Eee.Fff", 3);
   myProperties.addProperty( "Ggg", 4);
   myProperties.addProperty( "Hhh.Iii", 5);
   myProperties.addProperty( "Jjj.Kkk.Lll", 6);

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Aaa");

   int  value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 1);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Bbb");
   BOOST_REQUIRE_EQUAL( iter.name(), "Ccc");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 2);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Ddd.Eee");
   BOOST_REQUIRE_EQUAL( iter.name(), "Fff");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 3);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Ggg");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 4);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Hhh");
   BOOST_REQUIRE_EQUAL( iter.name(), "Iii");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 5);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Jjj.Kkk");
   BOOST_REQUIRE_EQUAL( iter.name(), "Lll");

   value = -1;
   BOOST_REQUIRE_NO_THROW( value = iter.value< int>());
   BOOST_REQUIRE_EQUAL( value, 6);

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // increasing_levels



/// One top level property with a link to it.
/// 
/// @since  1.22.0, 25.03.2019
BOOST_AUTO_TEST_CASE( top_level_link)
{

   Properties  myProperties;


   myProperties.addProperty( "Name", "Hugentobler");
   myProperties.addLink( "Name-Link", "Name");

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Name");

   std::string  value;
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "Hugentobler");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Name-Link");

   value.clear();
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "Hugentobler");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // top_level_link



/// A sub-map of properties and a link to it.
/// 
/// @since  1.22.0, 25.03.2019
BOOST_AUTO_TEST_CASE( linked_map)
{

   Properties  myProperties;


   myProperties.addProperty( "Name", "Hugentobler");
   myProperties.addProperty( "Address.Phone.Home", "123 45 67 89");
   myProperties.addProperty( "Address.Phone.Mobile", "456 12 34 56");
   myProperties.addProperty( "Address.Phone.Office", "987 65 43 21");

   myProperties.addLink( "Contacts", "Address.Phone");

   auto  iter = myProperties.begin();
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Address.Phone");
   BOOST_REQUIRE_EQUAL( iter.name(), "Home");

   std::string  value;
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "123 45 67 89");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Address.Phone");
   BOOST_REQUIRE_EQUAL( iter.name(), "Mobile");

   value.clear();
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "456 12 34 56");

   BOOST_REQUIRE_NO_THROW( iter++);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Address.Phone");
   BOOST_REQUIRE_EQUAL( iter.name(), "Office");

   value.clear();
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "987 65 43 21");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Contacts");
   BOOST_REQUIRE_EQUAL( iter.name(), "Home");

   value.clear();
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "123 45 67 89");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Contacts");
   BOOST_REQUIRE_EQUAL( iter.name(), "Mobile");

   value.clear();
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "456 12 34 56");

   BOOST_REQUIRE_NO_THROW( iter++);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "Contacts");
   BOOST_REQUIRE_EQUAL( iter.name(), "Office");

   value.clear();
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "987 65 43 21");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter != myProperties.end());

   BOOST_REQUIRE_EQUAL( iter.path(), "");
   BOOST_REQUIRE_EQUAL( iter.name(), "Name");

   value.clear();
   BOOST_REQUIRE_NO_THROW( value = iter.value< std::string>());
   BOOST_REQUIRE_EQUAL( value, "Hugentobler");

   BOOST_REQUIRE_NO_THROW( ++iter);
   BOOST_REQUIRE( iter == myProperties.end());

} // linked_map



// =====  END OF test_property_iterator_c.cpp  =====

