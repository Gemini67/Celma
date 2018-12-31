
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
/// @param[in]  auto_sep  If set, this string is used as separator between
///                       two fields and is added automatically.
/// @since  1.0.0, 13.12.2016
Creator::Creator( Definition& dest_def, const char* auto_sep):
   mDefs( dest_def),
   mAutoSep( (auto_sep != nullptr) ? auto_sep : ""),
   mFormatString(),
   mFixedWidth( 0),
   mAlignLeft( false)
{
} // Creator::Creator



/// Sets a new auto separator string or deletes the existing one (the
/// default).<br>
/// The new separator will be used for the next field that is added.
/// @param[in]  sep  The new separator to use, NULL to turn the feature off.
/// @since  1.0.0, 29.09.2017
void Creator::setAutoSep( const char* sep)
{

   if (sep != nullptr)
      mAutoSep.assign( sep);
   else
      mAutoSep.clear();

} // Creator::setAutoSep



/// Adds a field with the given type. Remaining parameters must be set
/// before and are stored in the member variables.
/// @param[in]  field_type  The type of the field to add.
/// @since  1.0.0, 13.12.2016
void Creator::field( Definition::FieldTypes field_type)
{

   Definition::Field  field;


   field.mType       = field_type;
   field.mConstant   = mFormatString;
   field.mFixedWidth = mFixedWidth;
   field.mAlignLeft  = mAlignLeft;

   addField( field);

} // Creator::field



/// Sets a fixed width for the next field.
/// @param[in]  fixed_width  he fixed width to use for the next field.
/// @since  1.0.0, 13.12.2016
void Creator::setFixedWidth( int fixed_width)
{

   mFixedWidth = fixed_width;

} // Creator::setFixedWidth



/// Sets the flag that the output of the next field should be left-aligned.
/// @since  1.0.0, 13.12.2016
void Creator::alignLeft()
{

   mAlignLeft = true;

} // Creator::alignLeft



/// Operator to handle manipulators.
/// @param[in]  m  The manipulator to call.
/// @return  This object.
/// @since  1.0.0, 13.12.2016
Creator& Creator::operator <<( Creator&( *m)( Creator&))
{

   m( *this);

   return *this;
} // operator <<



/// Operator to store the data of a 'custom property' in a creator object.
/// @param[in]  c   The object to pass the custom property to.
/// @param[in]  cp  The custom property to store.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 13.12.2016
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
/// @since  1.0.0, 13.12.2016
Creator& operator <<( Creator& c, const std::string& const_text)
{

   c.addConstantText( const_text);

   return c;
} // operator <<



/// Operator to store a fixed width setting in a creator object.
/// @param[in]  c            The object to pass the fixed width to.
/// @param[in]  fixed_width  The fixed width to store.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 13.12.2016
Creator& operator <<( Creator& c, int fixed_width)
{

   c.setFixedWidth( fixed_width);

   return c;
} // operator <<


/// Operator to store the data of a 'format string' in a creator object.
/// @param[in]  c   The object to pass the format string to.
/// @param[in]  fs  The format string to store.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 26.09.2017
Creator& operator <<( Creator& c, const formatString& fs)
{

   c.formatString( fs.value());

   return c;
} // operator <<



/// Operator to change the separator sring to use from now on.
/// @param[in]  c    The object to change the eparator string in.
/// @param[in]  sep  The separator string to set.
/// @return  The same object as passed in \a c.
/// @since  1.0.0, 02.10..2017
Creator& operator <<( Creator& c, const separator& sep)
{

   c.setAutoSep( sep.value());

   return c;
} // operator <<



/// Called by the operator to actually store the constant text.
/// @param[in]  const_text  The constant text to store.
/// @since  1.0.0, 13.12.2016
void Creator::addConstantText( const std::string& const_text)
{

   Definition::Field  constant_field;


   constant_field.mType       = Definition::FieldTypes::constant;
   constant_field.mConstant   = const_text;
   constant_field.mFixedWidth = mFixedWidth;
   constant_field.mAlignLeft  = mAlignLeft;

   addField( constant_field);

} // Creator::addConstantText



/// Adds a field with type custom property.
/// @param[in]  property_name  The name of the property to add the value of.
/// @since  1.0.0, 13.12.2016
void Creator::customProperty( const std::string& property_name)
{

   Definition::Field  property_field;


   property_field.mType       = Definition::FieldTypes::customProperty;
   property_field.mConstant   = property_name;
   property_field.mFixedWidth = mFixedWidth;
   property_field.mAlignLeft  = mAlignLeft;

   addField( property_field);

} // Creator::customProperty



/// Stores a format string that can be used by the next field.
/// @param[in]  fmt  The format string to store.
/// @since  1.0.0, 26.09.2017
void Creator::formatString( const std::string& fmt)
{

   mFormatString = fmt;

} // Creator::formatString



/// Checks if an auto-separator must be added first, and then adds the field
/// to the definition.<br>
/// And while we're at it, prepare for the next field.
/// @param[in]  field  The field to add.
/// @since  1.0.0, 29.09.2017
void Creator::addField( const Definition::Field& field)
{

   if (!mAutoSep.empty() && !mDefs.mFields.empty())
   {
      Definition::Field  separator_field;

      separator_field.mType       = Definition::FieldTypes::constant;
      separator_field.mConstant   = mAutoSep;
      separator_field.mFixedWidth = 0;
      separator_field.mAlignLeft  = false;

      mDefs.mFields.push_back( separator_field);
   } // end if

   mDefs.mFields.push_back( field);

   mFormatString.clear();
   mFixedWidth = 0;
   mAlignLeft  = false;

} // Creator::addField



} // namespace formatting
} // namespace log
} // namespace celma


// ===========================  END OF creator.cpp  ===========================

