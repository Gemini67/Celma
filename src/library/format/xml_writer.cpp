
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


// module headerfile include
#include "celma/format/xml_writer.hpp"


namespace celma::format {



/// Constructor.
///
/// @param[in]  dest
///    Destination stream to write the XML into.
/// @param[in]  indent_size
///    Number of spaces to use for indention.
/// @since  1.45.0, 02.03.2021
XmlWriter::XmlWriter( std::ostream& dest, int indent_size):
   mDest( dest),
   mIndent( 0, indent_size)
{
} // XmlWriter::XmlWriter



/// Insertion operator to handle manipulators.
///
/// @param[in]  m  The manipulator to call with this object.
/// @return  This object.
/// @since  1.45.0, 03.03.2021
XmlWriter& XmlWriter::operator <<( XmlWriter&( *m)( XmlWriter&))
{

   m( *this);

   return *this;
} // XmlWriter::operator <<



/// Called to set the type of the next field/value.
///
/// @param[in]  type  The type of the next field/value to set.
/// @since  1.45.0, 03.03.2021
void XmlWriter::nextField( XmlWriter::Field type)
{

   mNextFieldType = type;

} // XmlWriter::nextField



/// Handles a boolean value.
///
/// @param[in]  bvalue  The boolean value to write.
/// @since  1.45.0, 05.03.2021
void XmlWriter::handleBool( bool bvalue)
{

   if (mNextFieldType == Field::attr_val)
   {
      mDest << std::boolalpha << bvalue << '"';
   } else if (mNextFieldType == Field::value)
   {
      mDest << '>' << std::boolalpha << bvalue;
      closeTag();
   } // end if

   mNextFieldType = Field::unknown;

} // XmlWriter::handleBool



/// Handles an integer value.
///
/// @param[in]  ivalue  The integer value to write.
/// @since  1.45.0, 03.03.2021
void XmlWriter::handleInt( int ivalue)
{

   if (mNextFieldType == Field::attr_val)
   {
      mDest << ivalue << '"';
   } else if (mNextFieldType == Field::value)
   {
      mDest << '>' << ivalue;
      closeTag();
   } // end if

   mNextFieldType = Field::unknown;

} // XmlWriter::handleInt



/// Handles a double value.
///
/// @param[in]  fvalue  The floating point value to write.
/// @since  1.45.0, 04.03.2021
void XmlWriter::handleDouble( double fvalue)
{

   if (mNextFieldType == Field::attr_val)
   {
      mDest << fvalue << '"';
   } else if (mNextFieldType == Field::value)
   {
      mDest << '>' << fvalue;
      closeTag();
   } // end if

   mNextFieldType = Field::unknown;

} // XmlWriter::handleDouble



/// Handles a string value.
///
/// @param[in]  str  The string to write.
/// @since  1.45.0, 03.03.2021
void XmlWriter::handleString( const std::string& str)
{

   switch (mNextFieldType)
   {
   case Field::tag:
      mCurrentTagName = str;
      mDest << mIndent << '<' << mCurrentTagName;
      break;
   case Field::attr:
      mDest << ' ' << str << "=\"";
      break;
   case Field::attr_val:
      mDest << str << '"';
      break;
   case Field::value:
      mDest << '>' << str;
      closeTag();
      break;
   default:
      break;
   } // end switch

   mNextFieldType = Field::unknown;

} // XmlWriter::handleString



/// Writes the closing tag.
///
/// @since  1.45.0, 03.03.2021
void XmlWriter::closeTag()
{

   mDest << "</" << mCurrentTagName << '>' << std::endl;

} // XmlWriter::closeTag



} // namespace celma::format


// =====  END OF xml_writer.cpp  =====

