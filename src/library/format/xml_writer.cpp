
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



XmlWriter::XmlWriter( std::ostream& dest, int indent_size):
   mDest( dest),
   mIndent( 0, indent_size)
{
} // XmlWriter::XmlWriter



XmlWriter& XmlWriter::operator <<( XmlWriter&( *m)( XmlWriter&))
{

   m( *this);

   return *this;
} // XmlWriter::operator <<



void XmlWriter::nextField( XmlWriter::Field type)
{

   mNextFieldType = type;

} // XmlWriter::nextField



/*
/// 
/// @param[in]  bvalue
///    .
/// @since
///    x.y.z, 05.03.2021
void XmlWriter::handle( bool bvalue)
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

} // XmlWriter::handle
*/



/// 
/// @param[in]  ivalue  .
/// @since  x.y.z, 03.03.2021
void XmlWriter::handle( int ivalue)
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

} // XmlWriter::handle



/// 
/// @param[in]  fvalue  .
/// @since  x.y.z, 04.03.2021
void XmlWriter::handle( double fvalue)
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

} // XmlWriter::handle



/// 
/// @param[in]  str  .
/// @since  x.y.z, 03.03.2021
void XmlWriter::handle( const std::string& str)
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

} // XmlWriter::handle



void XmlWriter::closeTag()
{

   mDest << "</" << mCurrentTagName << '>' << std::endl;

} // 



} // namespace celma::format


// =====  END OF xml_writer.cpp  =====

