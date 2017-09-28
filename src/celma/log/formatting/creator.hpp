
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


#ifndef CELMA_LOG_FORMATTING_CREATOR_HPP
#define CELMA_LOG_FORMATTING_CREATOR_HPP


#include <string>
#include "celma/common/manipulator.hpp"
#include "celma/log/formatting/definition.hpp"


namespace celma { namespace log { namespace formatting {


// bring helper classes into the same namespace
using customProperty = common::Manipulator< std::string, 0>;
using formatString = common::Manipulator< std::string, 1>;


/// Creates a log message format definition using stream-like syntax.
/// @since  x.y.z, 13.12.2016
class Creator
{
public:
   /// Constructor.
   /// @param[in]  dest_def  The format definition object to store the log
   ///                       format definition in.
   /// @since  x.y.z, 13.12.2016
   Creator( Definition& dest_def);

   /// Adds a field with the given type. Remaining parameters must be set
   /// before and are stored in the member variables.
   /// @param[in]  field_type  The type of the field to add.
   /// @since  x.y.z, 13.12.2016
   void field( Definition::FieldTypes field_type);

   /// Sets a fixed width for the next field.
   /// @param[in]  fixed_width  he fixed width to use for the next field.
   /// @since  x.y.z, 13.12.2016
   void setFixedWidth( int fixed_width);

   /// Sets the flag that the output of the next field should be left-aligned.
   /// @since  x.y.z, 13.12.2016
   void alignLeft();

   /// Operator to handle manipulators.
   /// @param[in]  m  The manipulator to call.
   /// @return  This object.
   /// @since  x.y.z, 13.12.2016
   Creator& operator <<( Creator&( *m)( Creator&));

   /// Operator to store the data of a 'custom property' in a creator object.
   /// @param[in]  c   The object to pass the custom property to.
   /// @param[in]  cp  The custom property to store.
   /// @return  The same object as passed in \a c.
   /// @since  x.y.z, 13.12.2016
   friend Creator& operator <<( Creator& c, const customProperty& cp);

   /// Operator to store a constant string in a creator object. This may later
   /// be used as constant string, or as format string e.g. for a date field.
   /// @param[in]  c           The object to pass the constant string to.
   /// @param[in]  const_text  The custom property to store.
   /// @return  The same object as passed in \a c.
   /// @since  x.y.z, 13.12.2016
   friend Creator& operator <<( Creator& c, const std::string& const_text);

   /// Operator to store a fixed width setting in a creator object.
   /// @param[in]  c            The object to pass the fixed width to.
   /// @param[in]  fixed_width  The fixed width to store.
   /// @return  The same object as passed in \a c.
   /// @since  x.y.z, 13.12.2016
   friend Creator& operator <<( Creator& c, int fixed_width);

   /// Operator to store the data of a 'format string' in a creator object.
   /// @param[in]  c   The object to pass the format string to.
   /// @param[in]  fs  The format string to store.
   /// @return  The same object as passed in \a c.
   /// @since  x.y.z, 26.09.2017
   friend Creator& operator <<( Creator& c, const formatString& fs);

private:
   /// Called by the operator to actually store the constant text.<br>
   /// Also adds the field
   /// @param[in]  const_text  The constant text to store.
   /// @since  x.y.z, 13.12.2016
   void addConstantText( const std::string& const_text);

   /// Adds a field with type custom property.
   /// @param[in]  property_name  The name of the property to add the value of.
   /// @since  x.y.z, 13.12.2016
   void customProperty( const std::string& property_name);

   /// Stores a format string that can be used by the next field.
   /// @param[in]  fmt  The format string to store.
   /// @since  x.y.z, 26.09.2017
   void formatString( const std::string& fmt);

   /// The object to store the log message format definition in.
   Definition&  mDefs;
   /// Format string for the next date, time or datetime field.
   std::string  mFormatString;
   /// Value set for the 'fixed width', will be stored in the next field.
   int          mFixedWidth;
   /// Contains the value of the 'align left' flag to store in the next field.
   bool         mAlignLeft;

}; // Creator


// inlined methods
// ===============


/// Adds a 'date' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 13.12.2016
inline Creator& date( Creator& in)
{
   in.field( Definition::FieldTypes::date);
   return in;
} // date


/// Adds a 'date-time' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 13.12.2016
inline Creator& date_time( Creator& in)
{
   in.field( Definition::FieldTypes::dateTime);
   return in;
} // date_time


/// Adds an 'error number' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& error_nbr( Creator& in)
{
   in.field( Definition::FieldTypes::errorNbr);
   return in;
} // error_nbr


/// Adds an 'filename' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& filename( Creator& in)
{
   in.field( Definition::FieldTypes::fileName);
   return in;
} // filename


/// Adds a 'function name' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& func_name( Creator& in)
{
   in.field( Definition::FieldTypes::functionName);
   return in;
} // func_name


/// Adds a 'log level' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& level( Creator& in)
{
   in.field( Definition::FieldTypes::msgLevel);
   return in;
} // level


/// Adds a 'log class' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& log_class( Creator& in)
{
   in.field( Definition::FieldTypes::msgClass);
   return in;
} // log_class


/// Adds a 'line number' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& line_nbr( Creator& in)
{
   in.field( Definition::FieldTypes::lineNbr);
   return in;
} // line_nbr


/// Adds an 'pid (process id)' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& pid( Creator& in)
{
   in.field( Definition::FieldTypes::pid);
   return in;
} // pid


/// Adds the flag for left alignment for the following field.
/// @param[in]  in  The object to use to store the left-alignment flag.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& left( Creator& in)
{
   in.alignLeft();
   return in;
} // left


/// Adds a 'constant text' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& text( Creator& in)
{
   in.field( Definition::FieldTypes::text);
   return in;
} // text


/// Adds a 'time' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 20.09.2017
inline Creator& time( Creator& in)
{
   in.field( Definition::FieldTypes::time);
   return in;
} // time


} // namespace formatting
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FORMATTING_CREATOR_HPP


// ===========================  END OF creator.hpp  ===========================

