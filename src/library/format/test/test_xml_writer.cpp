
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/



// module to test headerfile include
#include "celma/format/xml_writer.hpp"


// C++ Standard Library includes
#include <sstream>
#include <string>
#include <vector>


// Boost includes
#define BOOST_TEST_MODULE XmWriterTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/multiline_string_compare.hpp"


using celma::format::XmlWriter;
using celma::test::multilineStringCompare;


namespace {


/// Class with some basic member variables.
///
/// @since  x.y.z, 02.03.2021
class Simple
{
public:
   /// Returns the XML tag to use for data of objects from this class.
   ///
   /// @return  The tag name to use in XML for data from objects of this class.
   /// @since  x.y.z, 02.03.2021
   static const char* xmlTag()
   {
      return "simple_data";
   } // Simple::xmlTag

   /// Constructor.
   ///
   /// @param[in]  str
   ///    The value to store in the #mText member variable.
   /// @param[in]  value
   ///    The value to store in the #mValue member variable.
   /// @param[in]  ratio
   ///    The value to store in the #mRatio member variable.
   /// @since  x.y.z, 02.03.2021
   Simple( const std::string& str, int value, double ratio):
      mText( str),
      mValue( value),
      mRatio( ratio)
   {
   } // Simple::Simple

   /// Writes the data of this object in XML format.
   ///
   /// @param[in]  dest
   ///    The XML writer to stream the data into.<br>
   ///    Must be passed by value so the indent is incremented correctly etc.
   /// @since  x.y.z, 02.03.2021
   void toXml( XmlWriter dest) const
   {
      namespace xml = celma::format::xml;

      dest << xml::tag << "description"
           << xml::attr << "format" << xml::attr_val << "text"
           << xml::value << mText
           << xml::tag << "value" << xml::value << mValue
           << xml::tag << "ratio"
           << xml::attr << "unit" << xml::attr_val << "percent"
           << xml::attr << "range" << xml::attr_val << "1 week"
           << xml::value << mRatio;
   } // Simple::toXml

private:
   /// A text/string.
   std::string  mText;
   /// An integer value.
   int          mValue;
   /// A floating point value.
   double       mRatio;
}; // Simple


/// Class with member variables of type object.
///
/// @since  x.y.z, 02.03.2021
class Complex
{
public:
   /// Returns the XML tag to use for data of objects from this class.
   ///
   /// @return  The tag name to use in XML for data from objects of this class.
   /// @since  x.y.z, 02.03.2021
   static const char* xmlTag()
   {
      return "complex_data";
   } // Complex::xmlTag

   /// Constructor.
   ///
   /// @since  x.y.z, 02.03.2021
   Complex():
      mSimple1( "hello world", 42, 3.1415),
      mSimple2( "thank you for all the fish", 13, 7.25)
   {
   } // Complex::Complex

   /// Writes the data of this object in XML format.
   ///
   /// @param[in]  dest
   ///    The XML writer to stream the data into.<br>
   ///    Must be passed by value so the indent is incremented correctly etc.
   /// @since  x.y.z, 02.03.2021
   void toXml( XmlWriter dest) const
   {
      dest << mSimple1 << mSimple2;
   } // Complex::toXml

private:
   /// The first object.
   Simple  mSimple1;
   /// The second object.
   Simple  mSimple2;

}; // Complex


/// Class with a container as member variable.
///
/// @since  x.y.z, 07.03.2021
class Container
{
public:
   /// Returns the XML tag to use for data of objects from this class.
   ///
   /// @return  The tag name to use in XML for data from objects of this class.
   /// @since  x.y.z, 07.03.2021
   static const char* xmlTag()
   {
      return "container_data";
   } // Container::xmlTag

   /// Constructor.
   ///
   /// @since  x.y.z, 07.03.2021
   Container()
   {
      mSimples.emplace_back( Simple{ "hello world", 42, 3.1415 });
      mSimples.emplace_back( Simple{ "thank you for all the fish", 13, 7.25 });
   } // Container::Container

   /// Writes the data of this object in XML format.
   ///
   /// @param[in]  dest
   ///    The XML writer to stream the data into.<br>
   ///    Must be passed by value so the indent is incremented correctly etc.
   /// @since  x.y.z, 07.03.2021
   void toXml( XmlWriter dest) const
   {
      dest << mSimples;
   } // Container::toXml

private:
   /// Container == vector of objects.
   std::vector< Simple>  mSimples;

}; // Container


} // namespace



/// Test writing the data of an object of the class Simple in XML.
///
/// @since  x.y.z, 02.03.2021
BOOST_AUTO_TEST_CASE( simple)
{

   std::ostringstream  oss;
   XmlWriter           xw( oss);
   Simple              simple_obj( "juhu", 24, 9.32);

   xw << simple_obj;

   // std::cerr << oss.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( oss.str(),
      "<simple_data>\n"
      "   <description format=\"text\">juhu</description>\n"
      "   <value>24</value>\n"
      "   <ratio unit=\"percent\" range=\"1 week\">9.32</ratio>\n"
      "</simple_data>\n"
   ));
      
} // simple



/// Test writing the data of an object of the class Complex in XML.
/// 
/// @since  x.y.z, 02.03.2021
BOOST_AUTO_TEST_CASE( complex)
{

   std::ostringstream  oss;
   XmlWriter           xw( oss);
   Complex             complex_obj;

   xw << complex_obj;

   // std::cerr << oss.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( oss.str(),
      "<complex_data>\n"
      "   <simple_data>\n"
      "      <description format=\"text\">hello world</description>\n"
      "      <value>42</value>\n"
      "      <ratio unit=\"percent\" range=\"1 week\">3.1415</ratio>\n"
      "   </simple_data>\n"
      "   <simple_data>\n"
      "      <description format=\"text\">thank you for all the fish</description>\n"
      "      <value>13</value>\n"
      "      <ratio unit=\"percent\" range=\"1 week\">7.25</ratio>\n"
      "   </simple_data>\n"
      "</complex_data>\n"
   ));
      
} // complex



/// Test writing the data of an object of the class Container in XML.
/// 
/// @since  x.y.z, 07.03.2021
BOOST_AUTO_TEST_CASE( container)
{

   std::ostringstream  oss;
   XmlWriter           xw( oss);
   Container           container_obj;

   xw << container_obj;

   // std::cerr << oss.str() << std::endl;
   BOOST_REQUIRE( multilineStringCompare( oss.str(),
      "<container_data>\n"
      "   <simple_data>\n"
      "      <description format=\"text\">hello world</description>\n"
      "      <value>42</value>\n"
      "      <ratio unit=\"percent\" range=\"1 week\">3.1415</ratio>\n"
      "   </simple_data>\n"
      "   <simple_data>\n"
      "      <description format=\"text\">thank you for all the fish</description>\n"
      "      <value>13</value>\n"
      "      <ratio unit=\"percent\" range=\"1 week\">7.25</ratio>\n"
      "   </simple_data>\n"
      "</container_data>\n"
   ));
      
} // container



// =====  END OF test_xml_writer.cpp  =====

