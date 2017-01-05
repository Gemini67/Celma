
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::format::AsciiTable.


#ifndef CELMA_FORMAT_ASCIITABLE_HPP
#define CELMA_FORMAT_ASCIITABLE_HPP


#include <string>


namespace celma { namespace format {


/// Helper class to generate the title line, the line with the dashes and finally
/// the format  string used to print ASCII tables.<br>
/// The string passed to the constructor defines the table layout. The format of
/// the contents of this string:<br>
/// <pre>{['-']<title>'['['d']['-']<len>[','<formatchar>']'<sep>}</pre><br>
/// which means:
/// - Multiple repetitions of the following definition block.
/// - If the block starts with a '-', the title is left aligned, otherwise it is
///   right aligned.
/// - Then the title to print for this column.
/// - Followed by the format block for this column, may be empty, but the [] are
///   mandatory.<br>
///   If the title contains [], use a backslash to quote the [.
/// - If the first character of the format string is a 'd', then the following
///   length will only be applied to the dashes. The title and the value format
///   will not contain any length information.
/// - The first value in the format block is the width of the column, if not set
///   the length of the title is used.
/// - If the values should be left aligned, specify a negative length.
/// - Actually, the length format is used as string directly for creating the
///   format string, meaning '%05d', '%24.24s' or %8.3f' (without the % sign and
///   the last type character) can be specified here.
/// - The second value in the format block is the format character to use, if not
///   set, 's' for string is used.
/// - Finally, all characters after the closing ']' and the beginning of the
///   next title (a dash or an alphanumeric character) is used as separator.<br>
///   It is possible to specify a newline character here, after the last title,
///   to get newline characters automatically in all lines.
///
/// By default, a dash character '-' is used to create the dash lines.<br>
/// If another character should be used by default, it can be set using the
/// setDashChar() method.<br>
/// If another character should be used by one object only, it can be specified
/// in the parameter list of the constructor.
/// @todo  Enhance it so that format strings like '... (%d) ...' or
///        '... [%d] ...' are possible.
/// @since  0.7, 07.11.2016
class AsciiTable
{
public:
   /// Sets the character to use to create the dash line. Default is '-'.
   /// @param[in]  dash_char  The dash character to use from now on.
   /// @since  0.7, 07.11.2016
   static void setDashChar( char dash_char);

   /// Constructor, prepares the strings for printing the table.
   /// @param[in]  table_spec  The string that specifies the columns, widths,
   ///                         formats etc. as described in the class header.
   /// @param[in]  dash_char   The character to use to create the dash line.
   /// @since  0.7, 07.11.2016
   explicit AsciiTable( const std::string& table_spec, char dash_char = '\0');

   /// Constructor, prepares the strings for printing the table.<br>
   /// Use this version of the constructor if the table specification string
   /// should be created using a printf() like format string. This may be used
   /// e.g. when the column is set through a constant.
   /// @param[in]  dash_char          The character to use to create the dash
   ///                                line.<br>
   ///                                Pass a 0 character here if the default
   ///                                dash character should be used.
   /// @param[in]  table_spec_format  The string that specifies the columns,
   ///                                widths, formats etc. as described in the
   ///                                class header.<br>
   ///                                This string is passed to printf() to
   ///                                create the final table specification
   ///                                string using the additional parameters.
   /// @param[in]  ...                Additional parameters to create the table
   ///                                specification string.
   /// @since  0.7, 07.11.2016
   AsciiTable( char dash_char, const char* table_spec_format, ...);

   // Copying of objects may sometimes be necessary.
   AsciiTable( const AsciiTable&) = default;
   // Default destructor is just fine.
   ~AsciiTable() = default;

   /// Allows to append more columns to the table.<br>
   /// If a newline character should be appended in order to get the created
   /// lines with newline character at the end, call this funtion with just the
   /// newline character as string contents.
   /// @param[in]  table_spec  The string that specifies the additional columns,
   ///                         widths, formats etc. as described in the class
   ///                         header.
   /// @since  0.7, 07.11.2016
   void append( const std::string& table_spec);

   /// Returns the line with the titles.
   /// @return  The complete title line.
   /// @since  0.7, 07.11.2016
   const std::string& titleLine() const;

   /// Returns the line with the dashes.
   /// @return  The complete line with the dashes.
   /// @since  0.7, 07.11.2016
   const std::string& dashesLine() const;

   /// Returns the format string that can be used to print the values.
   /// @return  The complete format string.
   /// @since  0.7, 07.11.2016
   const std::string& formatString() const;

   /// Returns the format string as char* that can be used directly in a
   /// printf() call to print the values.
   /// @return  The complete format string.
   /// @since  0.10, 22.12.2016
   const char* format() const;

private:
   /// Default dash character to use.
   static char mDashChar;

   /// Process the table specification in the string pointed to by \a pnext and
   /// fill the corresponding values into #mTitleLine, #mDashesLine and
   /// #mFormatString.
   /// @param[in]  pnext  Pointer to the (position in the) string to parse.
   /// @since  0.7, 07.11.2016
   void processSpec( const char* pnext);

   /// The dash character used by this object.
   char         mCurrentDashChar;
   /// The complete title line.
   std::string  mTitleLine;
   /// The complete dashes line.
   std::string  mDashesLine;
   /// The complete format string.
   std::string  mFormatString;

}; // AsciiTable


// inlined methods
// ===============


inline const std::string& AsciiTable::titleLine() const
{
   return mTitleLine;
} // AsciiTable::titleLine


inline const std::string& AsciiTable::dashesLine() const
{
   return mDashesLine;
} // AsciiTable::dashesLine


inline const std::string& AsciiTable::formatString() const
{
   return mFormatString;
} // AsciiTable::formatString


inline const char* AsciiTable::format() const
{
   return mFormatString.c_str();
} // AsciiTable::format


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_ASCIITABLE_HPP


// =========================  END OF ascii_table.hpp  =========================

