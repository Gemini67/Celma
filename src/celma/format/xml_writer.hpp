
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
#include "celma/format/indent_handler.hpp"


namespace celma::format {


/// Class to easily store data in XML format.
/// Main idea is that the user does not have to care about indention, correctly
/// setting begin- and end-tags, double-quotes and stuff like that.<br>
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

   /// 
   /// @param[in]  dest         .
   /// @param[in]  indent_size  .
   /// @since  x.y.z, 02.03.2021
   explicit XmlWriter( std::ostream& dest, int indent_size = 3);

   /// 
   /// @param[in]  other  .
   /// @return  .
   /// @since  x.y.z, 02.03.2021
   XmlWriter( const XmlWriter& other) = default;

   /// 
   /// @param[in]  dest
   ///    .
   /// @param[in]  bvalue
   ///    .
   /// @return
   ///    .
   /// @since
   ///    x.y.z, 05.03.2021
//   friend XmlWriter& operator <<( XmlWriter& dest, bool bvalue);

   /// 
   /// @param[in]  dest    .
   /// @param[in]  ivalue  .
   /// @return  .
   /// @since  x.y.z, 03.03.2021
   friend XmlWriter& operator <<( XmlWriter& dest, int ivalue);

   /// 
   /// @param[in]  dest    .
   /// @param[in]  fvalue  .
   /// @return  .
   /// @since  x.y.z, 04.03.2021
   friend XmlWriter& operator <<( XmlWriter& dest, double fvalue);

   /// 
   /// @param[in]  dest  .
   /// @param[in]  str   .
   /// @return  .
   /// @since  x.y.z, 03.03.2021
   friend XmlWriter& operator <<( XmlWriter& dest, const char* str);

   /// 
   /// @param[in]  dest  .
   /// @param[in]  str   .
   /// @return  .
   /// @since  x.y.z, 03.03.2021
   friend XmlWriter& operator <<( XmlWriter& dest, const std::string& str);

   /// 
   /// @param[in]  *m  .
   /// @return  .
   /// @since  x.y.z, 03.03.2021
   XmlWriter& operator <<( XmlWriter&( *m)( XmlWriter&));

   /// 
   /// @param[in]  dest  .
   /// @param[in]  obj   .
   /// @return  .
   /// @since  x.y.z, 02.03.2021
   template< typename T> friend
      XmlWriter& operator <<( XmlWriter& dest, const T& obj);

   /// 
   /// @param[in]  type  .
   /// @since  x.y.z, 03.03.2021
   void nextField( XmlWriter::Field type);

private:
   /// 
   /// @param[in]  obj  .
   /// @return  .
   /// @since  x.y.z, 02.03.2021
   template< typename T> void writeObject( const T& obj);

/*
   /// 
   /// @param[in]  bvalue
   ///    .
   /// @since
   ///    x.y.z, 05.03.2021
   void handle( bool bvalue);
*/

   /// 
   /// @param[in]  ivalue  .
   /// @since  x.y.z, 03.03.2021
   void handle( int ivalue);

   /// 
   /// @param[in]  fvalue  .
   /// @since  x.y.z, 04.03.2021
   void handle( double fvalue);

   /// 
   /// @param[in]  str  .
   /// @since  x.y.z, 03.03.2021
   void handle( const std::string& str);

   /// 
   /// @since  x.y.z, 03.03.2021
   void closeTag();

   std::ostream&  mDest;
   IndentHandler  mIndent;
   Field          mNextFieldType = Field::unknown;
   std::string    mCurrentTagName;

};

// inlined methods
// ===============

/*

/// 
/// @param[in]  dest
///    .
/// @param[in]  ivalue
///    .
/// @return
///    .
/// @since
///    x.y.z, 05.03.2021
inline XmlWriter& operator <<( XmlWriter& dest, bool bvalue)
{
   dest.handle( bvalue);
   return dest;
} // operator <<

*/

inline XmlWriter& operator <<( XmlWriter& dest, int ivalue)
{
   dest.handle( ivalue);
   return dest;
} // operator <<


/// 
/// @param[in]  dest    .
/// @param[in]  fvalue  .
/// @return  .
/// @since  x.y.z, 04.03.2021
inline XmlWriter& operator <<( XmlWriter& dest, double fvalue)
{
   dest.handle( fvalue);
   return dest;
} // operator <<


inline XmlWriter& operator <<( XmlWriter& dest, const char* str)
{
   dest.handle( str);
   return dest;
}


inline XmlWriter& operator <<( XmlWriter& dest, const std::string& str)
{
   dest.handle( str);
   return dest;
}


template< typename T> XmlWriter& operator <<( XmlWriter& dest, const T& obj)
{
   dest.writeObject( obj);
   return dest;
} // operator <<


template< typename T> void XmlWriter::writeObject( const T& obj)
{
   mDest << mIndent << '<' << T::xmlTag() << '>' << std::endl;
   obj.toXml( *this);
   mDest << mIndent << "</" << T::xmlTag() << '>' << std::endl;
} // XmlWriter::writeObject


namespace xml {


/// 
/// @param[in]  dest  .
/// @return  .
/// @since  x.y.z, 03.03.2021
inline XmlWriter& tag( XmlWriter& dest)
{
   dest.nextField( XmlWriter::Field::tag);
   return dest;
}


/// 
/// @param[in]  dest  .
/// @return  .
/// @since  x.y.z, 03.03.2021
inline XmlWriter& attr( XmlWriter& dest)
{
   dest.nextField( XmlWriter::Field::attr);
   return dest;
}


/// 
/// @param[in]  dest  .
/// @return  .
/// @since  x.y.z, 03.03.2021
inline XmlWriter& attr_val( XmlWriter& dest)
{
   dest.nextField( XmlWriter::Field::attr_val);
   return dest;
}


/// 
/// @param[in]  dest  .
/// @return  .
/// @since  x.y.z, 03.03.2021
inline XmlWriter& value( XmlWriter& dest)
{
   dest.nextField( XmlWriter::Field::value);
   return dest;
}


} // namespace xml
} // namespace celma::format


// =====  END OF xml_writer.hpp  =====

