
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


/// @file
/// See documentation of class celma::format::XmlWriter.


#pragma once


#include <iostream>
#include <string>
#include <vector>
#include "celma/format/indent_handler.hpp"


namespace celma::format {


/// Class to easily store data in XML format.
/// Main idea is that the user does not have to care about indention, correctly
/// setting begin- and end-tags, double-quotes and stuff like that.<br>
/// To store the data of a class in XML, the class must provide the method
/// "xmlTag" which returns the name of the XML tag to store the data in.<br>
/// The the class must implement the method "toXml" to store the data of an
/// object in XML format, then you can simply write:
/// <pre>
///    XmlWriter  my_writer( file);
///    my_writer << my_obj;
/// </pre>
/// The following diagram shows the possible changes of field processing:
/// \dot
/// digraph {
///    "unknown"  -> "tag" [];
///    "tag"      -> "attr" [];
///    "attr"     -> "attr_val" [];
///    "attr_val" -> "value" [];
///    "tag"      -> "value" [];
///    "value"    -> "unknown" [];
/// }
/// \enddot
/// @since  x.y.z, 02.03.2021
class XmlWriter
{
public:
   /// List of possible states of expected next fields.
   enum class Field
   {
      unknown,   //!< Used as initialisation value.
      tag,       //!< Expect the name of the tag as next input.
      attr,      //!< Expect the name of an attribute as next input.
      attr_val,  //!< Expect the value for an attribute as next input.
      value      //!< Expect a value as next input.
   };

   /// Constructor.
   ///
   /// @param[in]  dest
   ///    Destination stream to write the XML into.
   /// @param[in]  indent_size
   ///    Number of spaces to use for indention.
   /// @since  x.y.z, 02.03.2021
   explicit XmlWriter( std::ostream& dest, int indent_size = 3);

   /// Copy constructor.
   /// Used e.g. to write the data of an object within an object. Default c'tors
   /// of all members to exactly the right thing.
   ///
   /// @param[in]  other  The other object to copy the data from.
   /// @since  x.y.z, 02.03.2021
   XmlWriter( const XmlWriter& other) = default;

   /// Insertion operator to handle manipulators.
   ///
   /// @param[in]  m  The manipulator to call with this object.
   /// @return  This object.
   /// @since  x.y.z, 03.03.2021
   XmlWriter& operator <<( XmlWriter&( *m)( XmlWriter&));

   /// Insertion operator for everything.
   ///
   /// @param[in]  dest
   ///    The destination object to write into.
   /// @param[in]  obj
   ///    The object to write into the XML stream.
   /// @return  This object.
   /// @since  x.y.z, 02.03.2021
   template< typename T>
      friend XmlWriter& operator <<( XmlWriter& dest, const T& obj);

   /// Called to set the type of the next field/value.
   ///
   /// @param[in]  type  The type of the next field/value to set.
   /// @since  x.y.z, 03.03.2021
   void nextField( XmlWriter::Field type);

private:
   /// Helper class to handle the different types correctly.
   /// This class works as intended thanks to the explicit constructors.
   ///
   /// @since  x.y.z, 07.03.2021
   class Handler
   {
   public:
      /// Constructor for handling boolean values.
      ///
      /// @param[in]  dest
      ///    The XML writer object to use for writing the boolean value.
      /// @param[in]  value
      ///    The value to write.
      /// @since  x.y.z, 07.03.2021
      explicit Handler( XmlWriter& dest, bool value)
      {
         dest.handleBool( value);
      } // XmlWriter::Handler::Handler

      /// Constructor for handling integer values.
      ///
      /// @param[in]  dest
      ///    The XML writer object to use for writing the integer value.
      /// @param[in]  value
      ///    The value to write.
      /// @since  x.y.z, 07.03.2021
      explicit Handler( XmlWriter& dest, int value)
      {
         dest.handleInt( value);
      } // XmlWriter::Handler::Handler

      /// Constructor for handling C string values.
      ///
      /// @param[in]  dest
      ///    The XML writer object to use for writing the C string value.
      /// @param[in]  value
      ///    The value to write.
      /// @since  x.y.z, 07.03.2021
      explicit Handler( XmlWriter& dest, const char* value)
      {
         dest.handleString( value);
      } // XmlWriter::Handler::Handler

      /// Constructor for handling double values.
      ///
      /// @param[in]  dest
      ///    The XML writer object to use for writing the double value.
      /// @param[in]  value
      ///    The value to write.
      /// @since  x.y.z, 07.03.2021
      explicit Handler( XmlWriter& dest, double value)
      {
         dest.handleDouble( value);
      } // XmlWriter::Handler::Handler

      /// Constructor for handling std::string values.
      ///
      /// @param[in]  dest
      ///    The XML writer object to use for writing the std::string value.
      /// @param[in]  value
      ///    The value to write.
      /// @since  x.y.z, 07.03.2021
      explicit Handler( XmlWriter& dest, const std::string& value)
      {
         dest.handleString( value);
      } // XmlWriter::Handler::Handler

      /// Constructor for handling a vector of values.
      ///
      /// @param[in]  dest
      ///    The XML writer object to use for writing the values from the vector.
      /// @param[in]  value
      ///    The vector with the values to write.
      /// @since  x.y.z, 07.03.2021
      template< typename T> explicit Handler( XmlWriter& dest, const std::vector< T>& value)
      {
         dest.handleVector( value);
      } // XmlWriter::Handler::Handler

      /// Constructor for handling objects.
      ///
      /// @param[in]  dest
      ///    The XML writer object to use for writing the object.
      /// @param[in]  obj
      ///    The object to write.
      /// @since  x.y.z, 07.03.2021
      template< typename T> Handler( XmlWriter& dest, const T& obj)
      {
         dest.writeObject( obj);
      } // XmlWriter::Handler::Handler

   }; // Handler

   /// Writes the data of an object within its tag.
   ///
   /// @param[in]  obj  The object to write the data into the XML stream.
   /// @since  x.y.z, 02.03.2021
   template< typename T> void writeObject( const T& obj);

   // methods for different types
   // type names used in method names since overloading could use implicit
   // conversions and then use the wrong method, e.g. const char* --> bool

   /// Handles a boolean value.
   ///
   /// @param[in]  bvalue  The boolean value to write.
   /// @since  x.y.z, 05.03.2021
   void handleBool( bool bvalue);

   /// Handles an integer value.
   ///
   /// @param[in]  ivalue  The integer value to write.
   /// @since  x.y.z, 03.03.2021
   void handleInt( int ivalue);

   /// Handles a double value.
   ///
   /// @param[in]  fvalue  The floating point value to write.
   /// @since  x.y.z, 04.03.2021
   void handleDouble( double fvalue);

   /// Handles a string value.
   ///
   /// @param[in]  str  The string to write.
   /// @since  x.y.z, 03.03.2021
   void handleString( const std::string& str);

   /// Handles a vector with values.
   ///
   /// @param[in]  v  The vector with the values to write.
   /// @since  x.y.z, 03.03.2021
   template< typename T> void handleVector( const std::vector< T>& v);

   /// Writes the closing tag.
   ///
   /// @since  x.y.z, 03.03.2021
   void closeTag();

   /// The stream to write the XML into.
   std::ostream&  mDest;
   /// Object used to handle indention.
   IndentHandler  mIndent;
   /// The type of the next field/value.
   Field          mNextFieldType = Field::unknown;
   /// Current tag.
   std::string    mCurrentTagName;

}; // XmlWriter


// inlined methods
// ===============


template< typename T> XmlWriter& operator <<( XmlWriter& dest, const T& obj)
{
   XmlWriter::Handler  h( dest, obj);
   return dest;
} // operator <<


template< typename T> void XmlWriter::writeObject( const T& obj)
{
   mDest << mIndent << '<' << T::xmlTag() << '>' << std::endl;
   obj.toXml( *this);
   mDest << mIndent << "</" << T::xmlTag() << '>' << std::endl;
} // XmlWriter::writeObject


template< typename T> void XmlWriter::handleVector( const std::vector< T>& v)
{
   for (auto const& data : v)
   {
      XmlWriter::Handler  h( *this, data);
   } // end for
} // XmlWriter::handleVector


namespace xml {


/// Specifies that the next string is the name of the tag.
///
/// @param[in]  dest  The object to set the next field type on.
/// @return  The object as passed in.
/// @since  x.y.z, 03.03.2021
inline XmlWriter& tag( XmlWriter& dest)
{
   dest.nextField( XmlWriter::Field::tag);
   return dest;
} // tag


/// Specifies that the next string is the name of an attribute.
///
/// @param[in]  dest  The object to set the next field type on.
/// @return  The object as passed in.
/// @since  x.y.z, 03.03.2021
inline XmlWriter& attr( XmlWriter& dest)
{
   dest.nextField( XmlWriter::Field::attr);
   return dest;
} // attr


/// Specifies that the next value is the value of an attribute.
///
/// @param[in]  dest  The object to set the next field type on.
/// @return  The object as passed in.
/// @since  x.y.z, 03.03.2021
inline XmlWriter& attr_val( XmlWriter& dest)
{
   dest.nextField( XmlWriter::Field::attr_val);
   return dest;
} // attr_val


/// Specifies that the next value is a value.
///
/// @param[in]  dest  The object to set the next field type on.
/// @return  The object as passed in.
/// @since  x.y.z, 03.03.2021
inline XmlWriter& value( XmlWriter& dest)
{
   dest.nextField( XmlWriter::Field::value);
   return dest;
} // value


} // namespace xml
} // namespace celma::format


// =====  END OF xml_writer.hpp  =====

