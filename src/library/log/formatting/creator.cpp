
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::formatting::Creator.


#include "celma/log/formatting/creator.hpp"


namespace celma { namespace log { namespace formatting {



/// Constructor.
/// @param[in]  dest_def  The format definition object to store the log
///                       format definition in.
/// @since  x.y.z, 13.12.2016
Creator::Creator( Definition& dest_def):
   mDefs( dest_def),
   mFormatString(),
   mFixedWidth( 0),
   mAlignLeft( false)
{
} // Creator::Creator



/// Adds a field with the given type. Remaining parameters must be set
/// before and are stored in the member variables.
/// @param[in]  field_type  The type of the field to add.
/// @since  x.y.z, 13.12.2016
void Creator::field( Definition::FieldTypes field_type)
{

   Definition::Field  field;


   field.mType       = field_type;
   field.mConstant   = mFormatString;
   field.mFixedWidth = mFixedWidth;
   field.mAlignLeft  = mAlignLeft;

   mDefs.mFields.push_back( field);

   mFormatString.clear();
   mFixedWidth = 0;
   mAlignLeft  = false;

} // Creator::field



/// Sets a fixed width for the next field.
/// @param[in]  fixed_width  he fixed width to use for the next field.
/// @since  x.y.z, 13.12.2016
void Creator::setFixedWidth( int fixed_width)
{

   mFixedWidth = fixed_width;

} // Creator::setFixedWidth



/// Sets the flag that the output of the next field should be left-aligned.
/// @since  x.y.z, 13.12.2016
void Creator::alignLeft()
{

   mAlignLeft = true;

} // Creator::alignLeft



/// Operator to handle manipulators.
/// @param[in]  m  The manipulator to call.
/// @return  This object.
/// @since  x.y.z, 13.12.2016
Creator& Creator::operator <<( Creator&( *m)( Creator&))
{

   m( *this);

   return *this;
} // operator <<



/// Operator to store the data of a 'custom property' in a creator object.
/// @param[in]  c   The object to pass the custom property to.
/// @param[in]  cp  The custom property to store.
/// @return  The same object as passed in \a c.
/// @since  x.y.z, 13.12.2016
Creator& operator <<( Creator& c, const customProperty& cp)
{

   c.customProperty( cp.value());

   return c;
} // operator <<



/// Operator to store a constant string in a creator object. This may later
/// be used as constant string, or as format string e.g. for a date field.
/// @param[in]  c           The object to pass the constant string to.
/// @param[in]  const_text  The custom property to store.
/// @return  The same object as passed in \a c.
/// @since  x.y.z, 13.12.2016
Creator& operator <<( Creator& c, const std::string& const_text)
{

   c.addConstantText( const_text);

   return c;
} // operator <<



/// Operator to store a fixed width setting in a creator object.
/// @param[in]  c            The object to pass the fixed width to.
/// @param[in]  fixed_width  The fixed width to store.
/// @return  The same object as passed in \a c.
/// @since  x.y.z, 13.12.2016
Creator& operator <<( Creator& c, int fixed_width)
{

   c.setFixedWidth( fixed_width);

   return c;
} // operator <<


/// Operator to store the data of a 'format string' in a creator object.
/// @param[in]  c   The object to pass the format string to.
/// @param[in]  fs  The format string to store.
/// @return  The same object as passed in \a c.
/// @since  x.y.z, 26.09.2017
Creator& operator <<( Creator& c, const formatString& fs)
{

   c.formatString( fs.value());

   return c;
} // operator <<



/// Called by the operator to actually store the constant text.
/// @param[in]  const_text  The constant text to store.
/// @since  x.y.z, 13.12.2016
void Creator::addConstantText( const std::string& const_text)
{

   Definition::Field  constant_field;


   constant_field.mType       = Definition::FieldTypes::constant;
   constant_field.mConstant   = const_text;
   constant_field.mFixedWidth = mFixedWidth;
   constant_field.mAlignLeft  = mAlignLeft;

   mDefs.mFields.push_back( constant_field);

   mFormatString.clear();
   mFixedWidth = 0;
   mAlignLeft  = false;

} // Creator::addConstantText



/// Adds a field with type custom property.
/// @param[in]  property_name  The name of the property to add the value of.
/// @since  x.y.z, 13.12.2016
void Creator::customProperty( const std::string& property_name)
{

   Definition::Field  property_field;


   property_field.mType       = Definition::FieldTypes::customProperty;
   property_field.mConstant   = property_name;
   property_field.mFixedWidth = mFixedWidth;
   property_field.mAlignLeft  = mAlignLeft;

   mDefs.mFields.push_back( property_field);

   mFormatString.clear();
   mFixedWidth = 0;
   mAlignLeft  = false;

} // Creator::customProperty



/// Stores a format string that can be used by the next field.
/// @param[in]  fmt  The format string to store.
/// @since  x.y.z, 26.09.2017
void Creator::formatString( const std::string& fmt)
{

   mFormatString = fmt;

} // Creator::formatString



} // namespace formatting
} // namespace log
} // namespace celma


// ===========================  END OF creator.cpp  ===========================

