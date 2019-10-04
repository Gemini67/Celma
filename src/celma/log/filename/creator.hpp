
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
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
using formatString = common::Manipulator< std::string, 30>;
using env_var = common::Manipulator< std::string, 31>;


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
/// If a single character is passed in by the stream operator, it defines the
/// fill character for the following log file number.<br>
/// List of manipulators and stream elements:
/// - Text constant:<br>
///   Is taken as constnat text.
/// - Integer constant:<br>
///   Specifies the width of the following log file number.
/// - Character constant:<br>
///   Specifies the fill character to use with the following log file number.
/// - \c date:<br>
///   Next field in the path/filename is a date. If no date format is specified,
///   '%F' is used.<br>
///   Although the name is just 'date', the format string can contain date
///   and/or time fields.
/// - \c env_var( name):<br>
///   Uses the value of the given environment variable as part of the
///   path/filename.
/// - \c formatString( fmt)<br>
///   Specifies the format string to use for formatting the date/time field.
/// - \c number:<br>
///   Adds a log file number field to the definition.
/// - \c path_sep:<br>
///   Makes sure that the previous and the following part are correctly
///   separated by one path separator character (a slash).
/// - \c pid:<br>
///   inserts the current pid into the path.
///
/// @since  1.26.0, 21.02.2018  (added pid)
/// @since  1.0.0, 11.10.2017
class Creator
{
public:
   /// Constructor.
   ///
   /// @param[in]  dest_def
   ///    The filename definition object to store the log filename format
   ///    definition in.
   /// @since  1.0.0, 11.10.2017
   explicit Creator( Definition& dest_def);

   // copying is not allowed, moving and deleting is default
   Creator( const Creator&) = delete;
   Creator( Creator&&) = default;
   ~Creator() = default;

   /// Adds a path/filename part with the given type. Remaining parameters must
   /// be set before and are stored in the member variables.
   ///
   /// @param[in]  part_type  The type of the part to add.
   /// @since  1.0.0, 11.10.2017
   void part( Definition::PartTypes part_type);

   /// Sets a fixed width for the next part, the log file number.
   ///
   /// @param[in]  fixed_width  The fixed width to use for log file number.
   /// @since  1.0.0, 11.10.2017
   void setFixedWidth( int fixed_width);

   /// Sets the fill-character to use when adding the log file number.
   ///
   /// @param[in]  fill_char  The fill-character to use.
   /// @since  1.0.0, 16.10.2017
   void setFillChar( char fill_char);

   /// When adding two parts of constant text (which will internally be
   /// concatenated), call this function in between if the two parts come from
   /// parameters/environment variables etc., and you need to make sure that a
   /// path separator (a slash) is in between.
   ///
   /// @since  1.0.0, 16.10.2017
   void setCheckPathSeparator();

   /// Operator to handle manipulators.
   ///
   /// @param[in]  m  The manipulator to call.
   /// @return  This object.
   /// @since  1.0.0, 11.10.2017
   Creator& operator <<( Creator&( *m)( Creator&));

   /// Operator to pass a constant string to a creator object.
   ///
   /// @param[in]  c
   ///    The object to pass the constant string to.
   /// @param[in]  const_text
   ///    The text part to add.<br>
   ///    If the previous part was a constant text too, this text will be
   ///    appended to it.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 11.10.2017
   friend Creator& operator <<( Creator& c, const std::string& const_text);

   /// Operator to pass a fixed width setting for the log file number or the pid
   /// to a creator object.
   ///
   /// @param[in]  c
   ///    The object to pass the fixed width to.
   /// @param[in]  fixed_width
   ///    The fixed width to store.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 11.10.2017
   friend Creator& operator <<( Creator& c, int fixed_width);

   /// Operator to pass the data of a 'format string' to a creator object.
   ///
   /// @param[in]  c
   ///    The object to pass the format string to.
   /// @param[in]  fs
   ///    The format string to store.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 11.10.2017
   friend Creator& operator <<( Creator& c, const formatString& fs);

   /// Operator to change the fill character to use for a fixed width log file
   /// number.
   ///
   /// @param[in]  c
   ///    The object to change the eparator string in.
   /// @param[in]  sep
   ///    The separator string to set.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 11.10.2017
   friend Creator& operator <<( Creator& c, char fill_char);

   /// Operator to store a path part that adds the value of the given
   /// environment variable.
   ///
   /// @param[in]  c
   ///    The object to pass the name of the environment variable to.
   /// @param[in]  ev
   ///    The objct with the name of the environment variable to store.
   /// @return  The same object as passed in \a c.
   /// @since  1.0.0, 19.10.2017
   friend Creator& operator <<( Creator& c, const env_var& ev);

private:
   /// Called by the operator to actually store the constant text.<br>
   /// Also adds the part to the log file format definition.
   ///
   /// @param[in]  const_text  The constant text to store.
   /// @since  1.0.0, 11.10.2017
   void addConstantText( const std::string& const_text);

   /// Stores a format string that should be used by the next date part.
   ///
   /// @param[in]  fmt  The format string to store.
   /// @since  1.0.0, 11.10.2017
   void formatString( const std::string& fmt);

   /// Called by the operator to actually store the name of an environment
   /// variable.<br>
   /// Also adds the part to the log file format definition.
   ///
   /// @param[in]  env_var_name  The name of the environment variable.
   /// @since  1.0.0, 19.10.2017
   void addEnvVar( const std::string& env_var_name);

   /// Checks if two constant text parts can be concatenated, and if
   /// #mCheckPathSep is set, checks if a path separator must be added in
   /// between. Otherwise the part is added as-is to the log filename
   /// definition.<br>
   /// And while we're at it, prepare for the next part.
   ///
   /// @param[in]  part  The part to add.
   /// @since  1.0.0, 11.10.2017
   void addPart( const Definition::Part& part);

   /// The object to store the log message format definition in.
   Definition&  mDefs;
   /// Constant text string.
   std::string  mString;
   /// Value set for the 'fixed width', will be stored in the next field.
   int          mFixedWidth = 0;
   /// The 'fill character' to use for the log file number if a fixed width is
   /// specified.
   char         mFillChar = '0';
   /// If this flag is set when a constant text part should be appended to an
   /// existing constant text part, check that either the existing part ends
   /// with a path separator, or the text to append begins with one, otherwise
   /// add one.
   bool         mCheckPathSep = false;

}; // Creator


// inlined methods
// ===============


/// Adds a 'date' field to the log filename format definition.
///
/// @param[in]  in  The object to use to add the part to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 11.10.2017
inline Creator& date( Creator& in)
{
   in.part( Definition::PartTypes::date);
   return in;
} // date


/// Adds a 'log file number' field to the log filename format definition.
///
/// @param[in]  in  The object to use to add the part to the definition.
/// @return  The object as passed in.
/// @since  1.0.0, 11.10.2017
inline Creator& number( Creator& in)
{
   in.part( Definition::PartTypes::number);
   return in;
} // number


/// Sets the flag to check that the previous constant path part and the next
/// following one are separated by exactly one slash.
///
/// @param[in]  in  The object to set the 'check path separator' flag on.
/// @return  The object as passed in.
/// @since  1.0.0, 16.10.2017
inline Creator& path_sep( Creator& in)
{
   in.setCheckPathSeparator();
   return in;
} // path_sep


/// Adds a 'pid' field to the log filename format definition.
///
/// @param[in]  in  The object to use to add the part to the definition.
/// @return  The object as passed in.
/// @since  1.26.0, 21.02.2018
inline Creator& pid( Creator& in)
{
   in.part( Definition::PartTypes::pid);
   return in;
} // pid


} // namespace filename
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILENAME_CREATOR_HPP


// =====  END OF creator.hpp  =====

