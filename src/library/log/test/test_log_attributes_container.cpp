
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
**    Test program for the class celma::log::detail::LogAttributesContainer,
**    using the Boost.Test framework.
**
--*/


// module to test header file include
#include "celma/log/detail/log_attributes_container.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogAttributesContainerTest
#include <boost/test/unit_test.hpp>


// project includes


using celma::log::detail::LogAttributesContainer;



/// Test with an empty container.
///
/// @since  x.y.z, 11.10.2018
BOOST_AUTO_TEST_CASE( empty_container)
{

   LogAttributesContainer  lac;


   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( "anything"));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));

   BOOST_REQUIRE_NO_THROW( lac.removeAttribute());

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));

} // empty_container



/// Test with one attribute in the container.
///
/// @since  x.y.z, 11.10.2018
BOOST_AUTO_TEST_CASE( one_attribute)
{

   LogAttributesContainer  lac;
   const std::string       attr_name( "first_attr_name");
   const std::string       attr_value( "first attribute value");


   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr_name, attr_value));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), attr_value);

   // try to delete an attribute that does not exist
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( "anything"));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), attr_value);

   // delete by name
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( attr_name));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), "");

} // one_attribute



/// Test with one attribute in the container, delete it by usin the "delete
/// last" function.
///
/// @since  x.y.z, 11.10.2018
BOOST_AUTO_TEST_CASE( one_attribute_delete_last)
{

   LogAttributesContainer  lac;
   const std::string       attr_name( "first_attr_name");
   const std::string       attr_value( "first attribute value");


   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr_name, attr_value));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), attr_value);

   // try to delete an attribute that does not exist
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( "anything"));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), attr_value);

   // delete last (and only, in this case)
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute());

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), "");

} // one_attribute_delete_last



/// Add one attribute, delete it, add it again.
///
/// @since  x.y.z, 12.10.2018
BOOST_AUTO_TEST_CASE( one_attribute_readded)
{

   LogAttributesContainer  lac;
   const std::string       attr_name( "first_attr_name");
   const std::string       attr_value( "first attribute value");


   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr_name, attr_value));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), attr_value);

   // try to delete an attribute that does not exist
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( "anything"));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), attr_value);

   // delete by name
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( attr_name));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), "");

   // add the attribute (again)
   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr_name, attr_value));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), attr_value);

   // delete last
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute());

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr_name), "");

} // one_attribute_readded



/// Test with two different attributes in the container.
///
/// @since  x.y.z, 12.10.2018
BOOST_AUTO_TEST_CASE( two_attributes)
{

   LogAttributesContainer  lac;
   const std::string       attr1_name( "first_attr_name");
   const std::string       attr1_value( "first attribute value");
   const std::string       attr2_name( "second_attr_name");
   const std::string       attr2_value( "second attribute value");


   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr1_name, attr1_value));
   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr2_name, attr2_value));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), attr1_value);

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), attr2_value);

   // try to delete an attribute that does not exist
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( "anything"));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), attr1_value);

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), attr2_value);

   // delete the first attribute by name
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( attr1_name));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), attr2_value);

   // delete the second attribute as last
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute());

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), "");

} // two_attributes



/// Test with two different attributes in the container, delete the second
/// attribute first using the "delete last" function.
///
/// @since  x.y.z, 12.10.2018
BOOST_AUTO_TEST_CASE( two_attributes_delete_last)
{

   LogAttributesContainer  lac;
   const std::string       attr1_name( "first_attr_name");
   const std::string       attr1_value( "first attribute value");
   const std::string       attr2_name( "second_attr_name");
   const std::string       attr2_value( "second attribute value");


   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr1_name, attr1_value));
   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr2_name, attr2_value));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), attr1_value);

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), attr2_value);

   // delete the second attribute as last
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute());

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), attr1_value);

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), "");

   // delete the second argument as last too
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( attr1_name));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), "");

} // two_attributes_delete_last



/// Add three attributes, whereof the first and last are the same attribute with
/// different values.
///
/// @since  x.y.z, 12.10.2018
BOOST_AUTO_TEST_CASE( three_attributes_two_same)
{

   LogAttributesContainer  lac;
   const std::string       attr1_name( "first_attr_name");
   const std::string       attr1_value( "first attribute value");
   const std::string       attr1_value2( "first attribute, second value");
   const std::string       attr2_name( "second_attr_name");
   const std::string       attr2_value( "second attribute value");


   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr1_name, attr1_value));
   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr2_name, attr2_value));
   BOOST_REQUIRE_NO_THROW( lac.addAttribute( attr1_name, attr1_value2));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), attr1_value2);

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), attr2_value);

   // try to delete an attribute that does not exist
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( "anything"));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), attr1_value2);

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), attr2_value);

   // delete the second instance of the first attribute by name
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( attr1_name));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), attr1_value);

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), attr2_value);

   // delete the second attribute as last
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute());

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), attr1_value);

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), "");

   // delete the remaining first attribute by name
   BOOST_REQUIRE_NO_THROW( lac.removeAttribute( attr1_name));

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( "anything"));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( "anything"), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr1_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr1_name), "");

   BOOST_REQUIRE_NO_THROW( lac.getAttribute( attr2_name));
   BOOST_REQUIRE_EQUAL( lac.getAttribute( attr2_name), "");

} // three_attributes_two_same



// =====  END OF test_log_attributes_container.cpp  =====

