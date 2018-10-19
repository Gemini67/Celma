
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
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


// OS/C lib includes
#include <iostream>


// Boost includes
#define BOOST_TEST_MODULE LogFormatCreatorTest
#include <boost/test/unit_test.hpp>


namespace clf = celma::log::formatting;
using celma::log::formatting::Creator;


/// Helper class used to check the contents of the created format.
/// @since  1.0.0, 07.12.2016
class DefinitionAccess: public clf::Definition
{
public:
   /// Returns the stored size, i.e. number of format entries.
   /// @return  The number of format entries stored.
   /// @since  1.0.0, 07.12.2016
   size_t size() const
   {
      return mFields.size();
   } // DefinitionAccess::size

   /// Returns the type of the field at the given position.
   /// @param[in]  field_idx  The number of the field to return the type of.
   /// @return  The type of the field at the given position.
   /// @since  1.0.0, 07.12.2016
   FieldTypes fieldType( int field_idx) const
   {
      return mFields[ field_idx].mType;
   } // DefinitionAccess::fieldType

   /// Returns the constant value of the field at the given position.
   /// @param[in]  field_idx  The number of the field to return the constant
   ///                        value of.
   /// @return  The constant value of the field at the given position.
   /// @since  1.0.0, 07.12.2016
   const std::string& constant( int field_idx) const
   {
      return mFields[ field_idx].mConstant;
   } // DefinitionAccess::constant

   /// Returns the fixed width of the field at the given position.
   /// @param[in]  field_idx  The number of the field to return the fixed width
   ///                        of.
   /// @return  The fixed width of the field at the given position.
   /// @since  1.0.0, 07.12.2016
   int fixedWidth( int field_idx) const
   {
      return mFields[ field_idx].mFixedWidth;
   } // DefinitionAccess::fixedWidth

   /// Returns if left alignment should be used for the field at the given
   /// position.
   /// @param[in]  field_idx  The number of the field to return the alignment
   ///                        mode of.
   /// @return  \c true if left alignment should be used for the field at the
   ///          given position.
   /// @since  1.0.0, 07.12.2016
   bool alignLeft( int field_idx) const
   {
      return mFields[ field_idx].mAlignLeft;
   } // DefinitionAccess::alignLeft

}; // DefinitionAccess


BOOST_TEST_DONT_PRINT_LOG_VALUE( DefinitionAccess)
BOOST_TEST_DONT_PRINT_LOG_VALUE( celma::log::formatting::Definition::FieldTypes)



/// First simple tests.
/// @since  1.0.0, 07.12.2016
BOOST_AUTO_TEST_CASE( test_one)
{

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << clf::time;

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def, "|");

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << clf::time;

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << clf::time << "|" << clf::text;

      BOOST_REQUIRE_EQUAL( my_def.size(), 3);
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def, "|");

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << clf::time << clf::text;

      BOOST_REQUIRE_EQUAL( my_def.size(), 3);
   } // end scope

} // test_one



/// Test with more fields.
/// @since  1.0.0, 07.12.2016
BOOST_AUTO_TEST_CASE( test_two)
{

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << 10 << clf::date << "|" << 10 << clf::time << "|"
                     << clf::text;

      BOOST_REQUIRE_EQUAL( my_def.size(), 5);
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def, " | ");

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << 10 << clf::date << 10 << clf::time << clf::text;

      BOOST_REQUIRE_EQUAL( my_def.size(), 5);
   } // end scope

} // test_two



/// Test with 3 columns.
/// @since  1.0.0, 07.12.2016
BOOST_AUTO_TEST_CASE( test_three)
{

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def);

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << clf::date_time << "|" << clf::left << 5 << clf::line_nbr
                     << "|" << clf::text;

      BOOST_REQUIRE_EQUAL( my_def.size(), 5);
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator           format_creator( my_def, "|");

      BOOST_REQUIRE_EQUAL( my_def.size(), 0);

      format_creator << clf::date_time << clf::left << 5 << clf::line_nbr
                     << clf::text;

      BOOST_REQUIRE_EQUAL( my_def.size(), 5);
   } // end scope

} // test_three



/// Test all format entries.
/// @since  1.0.0, 20.09.2017
BOOST_AUTO_TEST_CASE( test_all_fields)
{

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);


   BOOST_REQUIRE_EQUAL( my_def.size(), 0);

   format_creator << clf::filename << "|"
                  << clf::func_name << "["
                  << clf::left << 6 << clf::line_nbr << "]"
                  << clf::left << 5 << clf::pid << "|"
                  << clf::date << " " << clf::time << "|"
                  << clf::level << "|"
                  << clf::log_class << "|"
                  << clf::error_nbr << "|"
                  << clf::text;

   BOOST_REQUIRE_EQUAL( my_def.size(), 19);

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 0),
                        DefinitionAccess::FieldTypes::fileName);
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 1),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 1), "|");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 2),
                        DefinitionAccess::FieldTypes::functionName);
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 3),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 3), "[");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 4),
                        DefinitionAccess::FieldTypes::lineNbr);
   BOOST_REQUIRE_EQUAL( my_def.fixedWidth( 4), 6);
   BOOST_REQUIRE( my_def.alignLeft( 4));
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 5),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 5), "]");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 6),
                        DefinitionAccess::FieldTypes::pid);
   BOOST_REQUIRE_EQUAL( my_def.fixedWidth( 6), 5);
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 7),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 7), "|");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 8),
                        DefinitionAccess::FieldTypes::date);
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 9),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 9), " ");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 10),
                        DefinitionAccess::FieldTypes::time);
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 11),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 11), "|");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 12),
                        DefinitionAccess::FieldTypes::msgLevel);
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 13),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 13), "|");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 14),
                        DefinitionAccess::FieldTypes::msgClass);
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 15),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 15), "|");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 16),
                        DefinitionAccess::FieldTypes::errorNbr);
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 17),
                        DefinitionAccess::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 17), "|");
   BOOST_REQUIRE_EQUAL( my_def.fieldType( 18),
                        DefinitionAccess::FieldTypes::text);

} // test_all_fields



/// Test using attributes.
///
/// @since  x.y.z, 12.10.2018
BOOST_AUTO_TEST_CASE( format_with_attributes)
{

   DefinitionAccess  my_def;
   Creator           format_creator( my_def);


   BOOST_REQUIRE_EQUAL( my_def.size(), 0);

   format_creator << clf::time << "|"
                  << clf::left << 13 << clf::attribute( "attr1")
                  << "|" << clf::attribute( "attr2")
                  << "|" << clf::text;

   BOOST_REQUIRE_EQUAL( my_def.size(), 7);

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 2),
                        clf::Definition::FieldTypes::attribute);
   BOOST_REQUIRE_EQUAL( my_def.constant( 2),   "attr1");
   BOOST_REQUIRE_EQUAL( my_def.fixedWidth( 2), 13);
   BOOST_REQUIRE_EQUAL( my_def.alignLeft( 2), true);

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 4),
                        clf::Definition::FieldTypes::attribute);
   BOOST_REQUIRE_EQUAL( my_def.constant( 4),   "attr2");
   BOOST_REQUIRE_EQUAL( my_def.fixedWidth( 4), 0);
   BOOST_REQUIRE_EQUAL( my_def.alignLeft( 4), false);

} // format_with_attributes



/// Test date, time and timestamp format string handling.
/// @since  1.0.0, 26.09.2017
BOOST_AUTO_TEST_CASE( test_format_string)
{

   {
      DefinitionAccess  my_def;
      Creator  format_creator( my_def);

      format_creator << clf::time;

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
      BOOST_REQUIRE_EQUAL( my_def.fieldType( 0),
                           clf::Definition::FieldTypes::time);
      BOOST_REQUIRE( my_def.constant( 0).empty());
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator  format_creator( my_def);

      format_creator << clf::formatString( "%T") << clf::time;

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
      BOOST_REQUIRE_EQUAL( my_def.fieldType( 0),
                           clf::Definition::FieldTypes::time);
      BOOST_REQUIRE_EQUAL( my_def.constant( 0), "%T");
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator  format_creator( my_def);

      format_creator << clf::formatString( "%Y-%M") << clf::date;

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
      BOOST_REQUIRE_EQUAL( my_def.fieldType( 0),
                           clf::Definition::FieldTypes::date);
      BOOST_REQUIRE_EQUAL( my_def.constant( 0), "%Y-%M");
   } // end scope

   {
      DefinitionAccess  my_def;
      Creator  format_creator( my_def);

      format_creator << clf::formatString( "%d-%h") << clf::date_time;

      BOOST_REQUIRE_EQUAL( my_def.size(), 1);
      BOOST_REQUIRE_EQUAL( my_def.fieldType( 0),
                           clf::Definition::FieldTypes::dateTime);
      BOOST_REQUIRE_EQUAL( my_def.constant( 0), "%d-%h");
   } // end scope

} // test_format_string



/// Test that changing the separator works correctly.
/// @since  1.0.0, 02.10.2017
BOOST_AUTO_TEST_CASE( test_change_sep)
{

   DefinitionAccess  my_def;
   Creator  format_creator( my_def, "|");

   format_creator << "one" << "two" << "three"
                  << clf::separator( ":")
                  << "four" << "five";

   BOOST_REQUIRE_EQUAL( my_def.size(), 9);

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 0),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 0), "one");

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 1),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 1), "|");

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 2),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 2), "two");

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 3),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 3), "|");

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 4),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 4), "three");

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 5),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 5), ":");

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 6),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 6), "four");

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 7),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 7), ":");

   BOOST_REQUIRE_EQUAL( my_def.fieldType( 8),
                        clf::Definition::FieldTypes::constant);
   BOOST_REQUIRE_EQUAL( my_def.constant( 8), "five");

} // test_change_sep



// =====  END OF test_log_format_creator.cpp  =====

