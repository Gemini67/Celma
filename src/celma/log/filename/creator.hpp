
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::filename::Creator.


#ifndef CELMA_LOG_FILENAME_CREATOR_HPP
#define CELMA_LOG_FILENAME_CREATOR_HPP


#include <string>
#include "celma/common/manipulator.hpp"
#include "celma/log/filename/definition.hpp"


namespace celma { namespace log { namespace filename {


// bring helper classes into the same namespace
using formatString = common::Manipulator< std::string>;


/// Creates a log filename format definition using stream-like syntax.<br>
/// As usual with streams, you set the properties first and then the value to
/// which the properties apply.<br>
/// Unlike output streams, there are no sticky properties, meaning you have to
/// set them for each field where they are required, but you don't need to
/// reset them.<br>
/// Multiple, subsequent elements of constant text are internally concatenated
/// to one constant string.<br>
/// If an integer value is passed in by the stream operator, it defines the
/// optional field width for the following log file number.<br>
/// @since  x.y.z, 11.10.2017
class Creator
{
public:
   /// Constructor.
   /// @param[in]  dest_def  The filename definition object to store the log
   ///                       filename format definition in.
   /// @since  x.y.z, 11.10.2017
   explicit Creator( Definition& dest_def);

   Creator( const Creator&) = delete;
   Creator( Creator&&) = default;
   ~Creator() = default;

   /// Adds a path/filename part with the given type. Remaining parameters must
   /// be set before and are stored in the member variables.
   /// @param[in]  part_type  The type of the part to add.
   /// @since  x.y.z, 11.10.2017
   void part( Definition::PartTypes part_type);

   /// Sets a fixed width for the next part, the log file number.
   /// @param[in]  fixed_width  The fixed width to use for log file number.
   /// @since  x.y.z, 11.10.2017
   void setFixedWidth( int fixed_width);

   /// Sets the fill-character to use when adding the log file number.
   /// @param[in]  fill_char  The fill-character to use.
   /// @since  x.y.z, 16.10.2017
   void setFillChar( char fill_char);

   /// 
   /// @since  x.y.z, 16.10.2017
   void setCheckPathSeparator();

   /// Operator to handle manipulators.
   /// @param[in]  m  The manipulator to call.
   /// @return  This object.
   /// @since  x.y.z, 11.10.2017
   Creator& operator <<( Creator&( *m)( Creator&));

   /// Operator to store a constant string in a creator object.
   /// @param[in]  c           The object to pass the constant string to.
   /// @param[in]  const_text  The text part to add.<br>
   ///                         If the previous part was a constant text too,
   ///                         this text will be appended to it.
   /// @return  The same object as passed in \a c.
   /// @since  x.y.z, 11.10.2017
   friend Creator& operator <<( Creator& c, const std::string& const_text);

   /// Operator to store a fixed width setting for the log file number in a
   /// creator object.
   /// @param[in]  c            The object to pass the fixed width to.
   /// @param[in]  fixed_width  The fixed width to store.
   /// @return  The same object as passed in \a c.
   /// @since  x.y.z, 11.10.2017
   friend Creator& operator <<( Creator& c, int fixed_width);

   /// Operator to store the data of a 'format string' in a creator object.
   /// @param[in]  c   The object to pass the format string to.
   /// @param[in]  fs  The format string to store.
   /// @return  The same object as passed in \a c.
   /// @since  x.y.z, 11.10.2017
   friend Creator& operator <<( Creator& c, const formatString& fs);

   /// Operator to change the fill character to use for a fixed width log file
   /// number.
   /// @param[in]  c    The object to change the eparator string in.
   /// @param[in]  sep  The separator string to set.
   /// @return  The same object as passed in \a c.
   /// @since  x.y.z, 11.10.2017
   friend Creator& operator <<( Creator& c, char fill_char);

private:
   /// Called by the operator to actually store the constant text.<br>
   /// Also adds the part to the log file format definition.
   /// @param[in]  const_text  The constant text to store.
   /// @since  x.y.z, 11.10.2017
   void addConstantText( const std::string& const_text);

   /// Stores a format string that should be used by the next date part.
   /// @param[in]  fmt  The format string to store.
   /// @since  x.y.z, 11.10.2017
   void formatString( const std::string& fmt);

   /// Checks if two constant text parts can be concatenated, and if
   /// #mCheckPathSep is set, checks if a path separator must be added in
   /// between. Otherwise the part is added as-is to the log filename
   /// definition.<br>
   /// And while we're at it, prepare for the next part.
   /// @param[in]  part  The part to add.
   /// @since  x.y.z, 11.10.2017
   void addPart( const Definition::Part& part);

   /// The object to store the log message format definition in.
   Definition&  mDefs;
   /// Constant text string.
   std::string  mString;
   /// Value set for the 'fixed width', will be stored in the next field.
   int          mFixedWidth;
   /// The 'fill character' to use for the log file number if a fixed width is
   /// specified.
   char         mFillChar;
   /// If this flag is set when a constant text part should be appended to an
   /// existing constant text part, check that either the existing part ends
   /// with a path separator, or the text to append begins with one, otherwise
   /// add one.
   bool         mCheckPathSep;

}; // Creator


// inlined methods
// ===============


/// Adds a 'date' field to the log filename format definition.
/// @param[in]  in  The object to use to add the part to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 11.10.2017
inline Creator& date( Creator& in)
{
   in.part( Definition::PartTypes::date);
   return in;
} // date


/// Adds a 'log file number' field to the log filename format definition.
/// @param[in]  in  The object to use to add the part to the definition.
/// @return  The object as passed in.
/// @since  x.y.z, 11.10.2017
inline Creator& number( Creator& in)
{
   in.part( Definition::PartTypes::number);
   return in;
} // number


/// Sets the flag to check that the previous constant path part and the next
/// following one are separated by exactly one slash.
/// @param[in]  in  The object to set the 'check path separator' flag on.
/// @return  The object as passed in.
/// @since  x.y.z, 16.10.2017
inline Creator& path_sep( Creator& in)
{
   in.setCheckPathSeparator();
   return in;
} // path_sep


} // namespace filename
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILENAME_CREATOR_HPP


// ===========================  END OF creator.hpp  ===========================

