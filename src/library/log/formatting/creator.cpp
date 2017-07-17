
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::formatting::Creator.


#include "celma/log/formatting/creator.hpp"


namespace celma { namespace log { namespace formatting {



Creator::Creator( Definition& dest_def):
   mDefs( dest_def),
   mFixedWidth( 0),
   mAlignRight( false)
{
} // Creator::Creator



void Creator::field( Definition::FieldTypes field_type)
{

   Definition::Field  field;


   field.mType       = field_type;
   field.mFixedWidth = mFixedWidth;
   field.mAlignRight = mAlignRight;

   mDefs.mFields.push_back( field);

   mFixedWidth = 0;
   mAlignRight = false;

} // Creator::field



void Creator::setFixedWidth( int fixed_width)
{

   mFixedWidth = fixed_width;

} // end if



void Creator::alignRight()
{

   mAlignRight = true;

} // Creator::alignRight



Creator& operator <<( Creator& c, const std::string& const_text)
{

   c.addConstantText( const_text);

   return c;
} // Creator::operator <<



Creator& operator <<( Creator& c, int fixed_width)
{

   c.setFixedWidth( fixed_width);

   return c;
} // Creator::operator <<



void Creator::addConstantText( const std::string& const_text)
{

   Definition::Field  constant_field;


   constant_field.mType       = Definition::FieldTypes::constant;
   constant_field.mConstant   = const_text;
   constant_field.mFixedWidth = mFixedWidth;
   constant_field.mAlignRight = mAlignRight;

   mDefs.mFields.push_back( constant_field);

   mFixedWidth = 0;
   mAlignRight = false;

} // Creator::addConstantText



void Creator::customProperty( const std::string& property_name)
{

   Definition::Field  constant_field;


   constant_field.mType       = Definition::FieldTypes::customProperty;
   constant_field.mConstant   = property_name;
   constant_field.mFixedWidth = mFixedWidth;
   constant_field.mAlignRight = mAlignRight;

   mDefs.mFields.push_back( constant_field);

   mFixedWidth = 0;
   mAlignRight = false;

} // Creator::customProperty



} // namespace formatting
} // namespace log
} // namespace celma


// ===========================  END OF creator.cpp  ===========================

