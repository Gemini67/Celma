
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
**    Test program for the module formatting::Creator, using the Boost.Test
**    framework.
**
--*/


// include of the tested module's header file
#include "celma/log/formatting/creator.hpp"


// Boost includes
#define BOOST_TEST_MODULE LogCreatorTest
#include <boost/test/unit_test.hpp>


using celma::log::formatting::Creator;


class DefinitionAccess: public celma::log::formatting::Definition
{
public:
   size_t size() const
   {
      return mFields.size();
   } // size

   FieldTypes fieldType( int field_idx) const
   {
      return mFields[ field_idx].mType;
   } // 

   const std::string& constant( int field_idx) const
   {
      return mFields[ field_idx].mConstant;
   } // 

   int fixedWidth( int field_idx) const
   {
      return mFields[ field_idx].mFixedWidth;
   } // 

   bool alignRight( int field_idx) const
   {
      return mFields[ field_idx].mAlignRight;
   } // 

};


BOOST_TEST_DONT_PRINT_LOG_VALUE( DefinitionAccess);
BOOST_TEST_DONT_PRINT_LOG_VALUE( celma::log::formatting::Definition::FieldTypes);


/// 
/// @since  0.11, 07.12.2016
BOOST_AUTO_TEST_CASE( test_one)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);


   BOOST_REQUIRE_EQUAL( my_def.size(), 0);

   format_creator << clf::time << "|" << clf::text;

   BOOST_REQUIRE_EQUAL( my_def.size(), 3);

} // end test_one



/// 
/// @since  0.11, 07.12.2016
BOOST_AUTO_TEST_CASE( test_two)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);


   BOOST_REQUIRE_EQUAL( my_def.size(), 0);

   format_creator << 10 << clf::date << "|" << 10 << clf::time << "|"
                  << clf::text;

   BOOST_REQUIRE_EQUAL( my_def.size(), 5);

} // end test_two



/// 
/// @since  0.11, 07.12.2016
BOOST_AUTO_TEST_CASE( test_three)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);


   BOOST_REQUIRE_EQUAL( my_def.size(), 0);

   format_creator << clf::date_time << "|" << clf::right << 5 << clf::line_nbr
                  << "|" << clf::text;

   BOOST_REQUIRE_EQUAL( my_def.size(), 5);

} // end test_three



/// 
/// @since  0.11, 13.12.2016
BOOST_AUTO_TEST_CASE( test_custom_property)
{

   namespace clf = celma::log::formatting;

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);


   BOOST_REQUIRE_EQUAL( my_def.size(), 0);

   format_creator << clf::time << "|"
                  << clf::right << 13 << clf::customProperty( "color")
                  << "|" << clf::text;

   BOOST_REQUIRE_EQUAL( my_def.size(), 5);

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 2),  clf::Definition::FieldTypes::customProperty);
   BOOST_REQUIRE_EQUAL( my_def.constant( 2),   "color");
   BOOST_REQUIRE_EQUAL( my_def.fixedWidth( 2), 13);
   BOOST_REQUIRE_EQUAL( my_def.alignRight( 2), true);

} // end test_custom_property



// =======================  END OF test_log_creator.cpp  =======================
