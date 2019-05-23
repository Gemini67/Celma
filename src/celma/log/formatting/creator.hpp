
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
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
using attribute = common::Manipulator< std::string, 10>;
using formatString = common::Manipulator< std::string, 11>;
using separator = common::Manipulator< const char*, 12>;


/// Creates a log message format definition using stream-like syntax.<br>
/// As usual with streams, you set the properties first and then the value to
/// which the properties apply.<br>
/// Unlike output streams, there are no sticky properties, meaning you have to
/// set them for each field where they are required, but you don't need to
/// reset them.<br>
/// Constant text is added as such to the destination format.<br>
/// If an integer value is passed in by the stream operator, it defines the
/// optional field width.<br>
/// Another special feature can be used to generate separators between the
/// fields:
/// - If the same separator should be used between all fields, pass the
///   separator string to the constructor.
/// - The separator() manipulator can be used to change the separator handling
///   starting with the next field:
///   - Pass a NULL pointer to turn off the separator feature.
///   - Specify the new/other separator to use from now on.
///
/// @since  1.0.0, 13.12.2016
class Creator
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest_def
   ///    The format definition object to store the log format definition in.
   /// @param[in]  auto_sep
   ///    If set, this string is used as separator between two fields and is
   ///    added automatically.
   /// @since  1.0.0, 13.12.2016
   explicit Creator( Definition& dest_def, const char* auto_sep = nullptr);

   Creator( const Creator&) = delete;
   Creator( Creator&&) = default;
   ~Creator() = default;

   /// Sets a new auto separator string or deletes the existing one (the
   /// default).<br>
   /// The new separator will be used for the next field that is added.
   ///
   /// @param[in]  sep  The new separator to use, NULL to turn the feature off.
   /// @since  1.0.0, 29.09.2017
   void setAutoSep( const char* sep = nullptr);

   /// Adds a field with the given type. Remaining parameters must be set
   /// before and are stored in the member variables.
   ///
   /// @param[in]  field_type  The type of the field to add.
   /// @since  1.0.0, 13.12.2016
   void field( Definition::FieldTypes field_type);

   /// Sets a fixed width for the next field.
   ///
   /// @param[in]  fixed_width  The fixed width to use for the next field.
   /// @since  1.0.0, 13.12.2016
   void setFixedWidth( int fixed_width);

   /// Sets the flag that the output of the next field should be left-aligned.
   ///
   /// @since  1.0.0, 13.12.2016
   void alignLeft();

   /// Operator to handle manipulators.
   ///
   /// @param[in]  m  The manipulator to call.
   /// @return  This object.
   /// @since  1.0.0, 13.12.2016
   Creator& operator <<( Creator&( *m)( Creator&));

   /// Operator to store the data of an 'attribute' in a creator object.
   ///
   /// @param[in]  c
   ///    The object to pass the attribute to.
   /// @param[in]  attr
   ///    The attribute to store.
   /// @return  The same object as passed in \a c.
   /// @since  1.15.0, 11.10.2018
   friend Creator& operator <<( Creator& c, const attribute& attr);

   /// Operator to store a constant string in a creator object. This may later
   /// be used as constant string, or as format string e.g. for a date field.
   ///
   /// @param[in]  c
   ///    The object to pass the constant string to.
   /// @param[in]  const_text
   ///    The text to store.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 13.12.2016
   friend Creator& operator <<( Creator& c, const std::string& const_text);

   /// Operator to store a fixed width setting in a creator object.
   ///
   /// @param[in]  c
   ///    The object to pass the fixed width to.
   /// @param[in]  fixed_width
   ///    The fixed width to store.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 13.12.2016
   friend Creator& operator <<( Creator& c, int fixed_width);

   /// Operator to store the data of a 'format string' in a creator object.
   ///
   /// @param[in]  c
   ///    The object to pass the format string to.
   /// @param[in]  fs
   ///    The format string to store.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 26.09.2017
   friend Creator& operator <<( Creator& c, const formatString& fs);

   /// Operator to change the separator string to use from now on.
   ///
   /// @param[in]  c
   ///    The object to change the separator string in.
   /// @param[in]  sep
   ///    The separator string to set.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 02.10.2017
   friend Creator& operator <<( Creator& c, const separator& sep);

private:
   /// Called by the operator to actually store the constant text.<br>
   /// Also adds the field
   ///
   /// @param[in]  const_text  The constant text to store.
   /// @since  1.0.0, 13.12.2016
   void addConstantText( const std::string& const_text);

   /// Adds a field with type attribute.
   ///
   /// @param[in]  attr_name  The name of the attribute to add the value of.
   /// @since  1.15.0, 11.10.2018
   void attribute( const std::string& attr_name);

   /// Stores a format string that can be used by the next field.
   ///
   /// @param[in]  fmt  The format string to store.
   /// @since  1.0.0, 26.09.2017
   void formatString( const std::string& fmt);

   /// Checks if an auto-separator must be added first, and then adds the field
   /// to the definition.<br>
   /// And while we're at it, prepare for the next field.
   ///
   /// @param[in]  field  The field to add.
   /// @since  1.0.0, 29.09.2017
   void addField( const Definition::Field& field);

   /// The object to store the log message format definition in.
   Definition&  mDefs;
   /// THe auto separator string to use, empty if the feature is not used.
   std::string  mAutoSep;
   /// Format string for the next date, time or datetime field.
   std::string  mFormatString;
   /// Value set for the 'fixed width', will be stored in the next field.
   int          mFixedWidth = 0;
   /// Contains the value of the 'align left' flag to store in the next field.
   bool         mAlignLeft = false;

}; // Creator


// inlined methods
// ===============


/// Adds a 'date' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 13.12.2016
inline Creator& date( Creator& in)
{
   in.field( Definition::FieldTypes::date);
   return in;
} // date


/// Adds a 'date-time' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 13.12.2016
inline Creator& date_time( Creator& in)
{
   in.field( Definition::FieldTypes::dateTime);
   return in;
} // date_time


/// Adds an 'error number' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& error_nbr( Creator& in)
{
   in.field( Definition::FieldTypes::errorNbr);
   return in;
} // error_nbr


/// Adds an 'filename' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& filename( Creator& in)
{
   in.field( Definition::FieldTypes::fileName);
   return in;
} // filename


/// Adds a 'function name' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& func_name( Creator& in)
{
   in.field( Definition::FieldTypes::functionName);
   return in;
} // func_name


/// Adds a 'log level' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& level( Creator& in)
{
   in.field( Definition::FieldTypes::msgLevel);
   return in;
} // level


/// Adds a 'log class' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& log_class( Creator& in)
{
   in.field( Definition::FieldTypes::msgClass);
   return in;
} // log_class


/// Adds a 'line number' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& line_nbr( Creator& in)
{
   in.field( Definition::FieldTypes::lineNbr);
   return in;
} // line_nbr


/// Adds a 'pid (process id)' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& pid( Creator& in)
{
   in.field( Definition::FieldTypes::pid);
   return in;
} // pid


/// Adds the flag for left alignment for the following field.
///
/// @param[in]  in  The object to use to store the left-alignment flag.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& left( Creator& in)
{
   in.alignLeft();
   return in;
} // left


/// Adds a 'constant text' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& text( Creator& in)
{
   in.field( Definition::FieldTypes::text);
   return in;
} // text


/// Adds a 'thread id' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 04.10.2017
inline Creator& thread_id( Creator& in)
{
   in.field( Definition::FieldTypes::threadId);
   return in;
} // thread_id


/// Adds a 'time' field to the format definition.
///
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 20.09.2017
inline Creator& time( Creator& in)
{
   in.field( Definition::FieldTypes::time);
   return in;
} // time


/// Adds a 'milliseconds-time' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 07.03.2018
inline Creator& time_ms( Creator& in)
{
   in.field( Definition::FieldTypes::time_ms);
   return in;
} // time_ms


/// Adds a 'microseconds-time' field to the format definition.
/// @param[in]  in  The object to use to add the field to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 07.03.2018
inline Creator& time_us( Creator& in)
{
   in.field( Definition::FieldTypes::time_us);
   return in;
} // time_us


} // namespace formatting
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FORMATTING_CREATOR_HPP


// =====  END OF creator.hpp  =====

