
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


// Boost includes
#define BOOST_TEST_MODULE XmWriterTest
#include <boost/test/unit_test.hpp>


// project includes
#include "celma/test/multiline_string_compare.hpp"


using celma::format::XmlWriter;
using celma::test::multilineStringCompare;


namespace {


class Simple
{
public:
   static const char* xmlTag()
   {
      return "simple_data";
   }

   Simple( const std::string& str, int value, double ratio):
      mText( str),
      mValue( value),
      mRatio( ratio)
   {
   } // Simple::Simple

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
   std::string  mText;
   int          mValue;
   double       mRatio;
};


class Complex
{
public:
   static const char* xmlTag()
   {
      return "complex_data";
   }

   Complex():
      mSimple1( "hello world", 42, 3.1415),
      mSimple2( "thank you for all the fish", 13, 7.25)
   {
   } // Complex::Complex

   void toXml( XmlWriter dest) const
   {
      dest << mSimple1 << mSimple2;
   } // Complex::toXml

private:
   Simple  mSimple1;
   Simple  mSimple2;
};


} // namespace



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



// =====  END OF test_xml_writer.cpp  =====

