
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


// module header file include
#include "celma/format/ascii_table.hpp"


// C/OS library includes
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <stdlib.h>


// project includes
#include "celma/format/auto_sprintf.hpp"


namespace celma { namespace format {


using std::string;


char AsciiTable::mDashChar = '-';


namespace
{


/// Helper class to parse the specification of one column.
/// @since  0.7, 07.11.2016
class EvalColumn
{
public:
   /// Constructor, does all the work.
   /// @param[in,out]  pnext  Pointer to the starting position of the next
   ///                        column specification.
   /// @since  0.7, 07.11.2016
   EvalColumn( const char*& pnext):
      mTitle(),
      mSeparator(),
      mLength(),
      mFormatString( "%")
   {

      if ((pnext == nullptr) || (*pnext == '\0'))
         return;

      // the title itself
      const bool title_align_left = (*pnext == '-');
      if (title_align_left)
         ++pnext;

      copyTitle( pnext);

      // require at least [] after a title
      if (*pnext != '[')
         return;

      string  length_string;
      string  format_type( "s");
      bool    length_dashes_only = false;

      ++pnext;
      if (*pnext != ']')
         readFormat( pnext, length_dashes_only, length_string, format_type);
 
      // was length set by format string?
      if (length_string.empty())
         setLengthString( length_string);
 
      if (!length_dashes_only)
      {
         // format string already contains '%', now append the length
         mFormatString.append( length_string);
      }  // end if

      // and the format type
      mFormatString.append( format_type);

      // now we have to read the separator
      ++pnext;
      copySeparator( pnext);

      // have to format the title accordingly if the length of the title itself
      // differs from the specified column width
      if ((mLength != static_cast< int>( mTitle.length())) && !length_dashes_only)
         formatTitle( title_align_left);

   } // EvalColumn::EvalColumn


   /// Returns the title of this column.
   /// @return  The formatted title.
   /// @since  0.7, 07.11.2016
   const string& title() const
   {
      return mTitle;
   } // EvalColumn::title


   /// Returns the separator string between this and the next column.
   /// @return  The separator string to append.
   /// @since  0.7, 07.11.2016
   const string& separator() const
   {
      return mSeparator;
   } // EvalColumn::separator


   /// Returns the width of the column.
   /// @return  The column width.
   /// @since  0.7, 07.11.2016
   int width() const
   {
      return mLength;
   } // EvalColumn::width


   /// Returns the format string for this column.
   /// @return  The complete format string for this column.
   /// @since  0.7, 07.11.2016
   const string& formatString() const
   {
      return mFormatString;
   } // EvalColumn::formatString

private:
   /// Copies the title from the format string into #mTitle and sets #mLength to
   /// the length of the title.<br>
   /// A backslash can be used to quote special characters (i.e. '[')
   /// @param[in,out]  pnext  Pointer to the current position.
   /// @since  0.7, 07.11.2016
   void copyTitle( const char*& pnext)
   {

      bool  quoted = false;

      while ((*pnext != '\0') && ((*pnext != '[') || quoted))
      {
        if (*pnext == '\\')
        {
          quoted = true;
        } else
        {
          mTitle.append( 1, *pnext);
          quoted = false;
        }  // end if
        ++pnext;
      }  // end while

      mLength = static_cast< int>( mTitle.length());

   } // EvalColumn::copyTitle


   /// Reads the format specification from the format string.<br>
   /// Sets #mLength to the specified length.
   /// @param[in,out]  pnext               Pointer to the current position.
   /// @param[out]     length_dashes_only  Returns \c true if the length
   ///                                     specification should be applied to
   ///                                     the dashes line only.
   /// @param[out]     length_string       Returns the length string as
   ///                                     specified in the format string.
   /// @param[out]     format_string       Returns the format specification set
   ///                                     in the format string.
   /// @since  0.7, 07.11.2016
   void readFormat( const char*& pnext, bool& length_dashes_only,
                    string& length_string, string& format_string)
   {

      if (*pnext == 'd')
      {
        length_dashes_only = true;
        ++pnext;
      }  // end if

      // have formatting options to evaluate
      mLength = ::abs( ::atoi( pnext));

      while ((*pnext != '\0') && (*pnext != ',') && (*pnext != ']'))
      {
        length_string.append( 1, *pnext);
        ++pnext;
      }  // end while

      if (*pnext == ',')
      {
        format_string.clear();
        ++pnext;
        while ((*pnext != '\0') && (*pnext != ']'))
        {
          format_string.append( 1, *pnext);
          ++pnext;
        }  // end while
      }  // end if

   } // EvalColumn::readFormat


   /// Called when no length (string) was set in the format string. Creates a
   /// length string from #mLength.
   /// @param[out]  length_string  Returns the length string.
   /// @since  0.7, 07.11.2016
   void setLengthString( string& length_string) const
   {

      char  format_len[ 64];

      ::sprintf( format_len, "%d", mLength);
      length_string = format_len;

   } // EvalColumn::setLengthString


   /// Copies the remaining characters until either the end of the string or the
   /// beginning of the next column header is found into #mSeparator.
   /// @param[in,out]  pnext  Pointer to the current position.
   /// @since  0.7, 07.11.2016
   void copySeparator( const char*& pnext)
   {

      /// @todo  there should be an easier way to do this
      ///        but (*pnext == ' ') did not work ...
      while ((*pnext != '\0') && (*pnext != '-') && !std::isalnum( *pnext) &&
             (*pnext != '#'))
      {
         mSeparator.append( 1, *pnext);
         ++pnext;
      }  // end while

   } // EvalColumn::copySeparator


   /// If the title length differs from the real length of the title, this
   /// method is called to format the title accordingly.<br>
   /// Stores the formatted column title in #mTitle.
   /// @param[in]  title_align_left  Specifies if the title should be
   ///                               left-aligned.
   /// @since  0.7, 07.11.2016
   void formatTitle( bool title_align_left)
   {

      char  title_format[ 32];
      ::strcpy( title_format, "%");

      char*  append_pos = &title_format[ 1];

      if (title_align_left)
      {
        ::strcat( title_format, "-");
        ++append_pos;
      }  // end if

      ::sprintf( append_pos, "%ds", mLength);

      char  formatted_title[ 128];
      ::sprintf( formatted_title, title_format, mTitle.c_str());

      mTitle = formatted_title;

   } // EvalColumn::formatTitle


   /// The formatted title of the column.
   string  mTitle;
   /// The separator string to append.
   string  mSeparator;
   /// The length/width of the column.
   int     mLength;
   /// The format string for values in this column.
   string  mFormatString;

}; // EvalColumn


} // namespace


/// Sets the character to use to create the dash line. Default is '-'.
/// @param[in]  dash_char  The dash character to use from now on.
/// @since  0.7, 07.11.2016
void AsciiTable::setDashChar( char dash_char)
{

   mDashChar = dash_char;

} // AsciiTable::setDashChar



/// Constructor, prepares the strings for printing the table.
/// @param[in]  table_spec  The string that specifies the columns, widths,
///                         formats etc. as described in the class header.
/// @param[in]  dash_char   The character to use to create the dash line.
/// @since  0.7, 07.11.2016
AsciiTable::AsciiTable( const string& table_spec, char dash_char):
   mCurrentDashChar( mDashChar),
   mTitleLine(),
   mDashesLine(),
   mFormatString()
{


   if (dash_char != '\0')
      mCurrentDashChar = dash_char;

   processSpec( table_spec.c_str());

} // AsciiTable::AsciiTable



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
AsciiTable::AsciiTable( char dash_char, const char* table_spec_format, ...):
   mCurrentDashChar( mDashChar),
   mTitleLine(),
   mDashesLine(),
   mFormatString()
{

   if (dash_char != '\0')
      mCurrentDashChar = dash_char;

   try
   {
      va_list  args;

      va_start( args, table_spec_format);

      const AutoSprintf  table_spec( string( table_spec_format), args);

      va_end( args);

      processSpec( table_spec.c_str());
   } catch (...)
   {
   } // end try

} // AsciiTable::AsciiTable



/// Allows to append more columns to the table.
/// @param[in]  table_spec  The string that specifies the additional columns,
///                         widths, formats etc. as described in the class
///                         header.
/// @since  0.7, 07.11.2016
void AsciiTable::append( const string& table_spec)
{

   // special handling used to e.g. append a newline character
   if (table_spec.length() == 1)
   {
      mTitleLine.append( table_spec);
      mDashesLine.append( table_spec);
      mFormatString.append( table_spec);
      return;
   }  // end if

   string       separator;
   const char*  pnext = table_spec.c_str();

   while (*pnext == ' ')
   {
     separator.append( 1, ' ');
     ++pnext;
   }  // end while

   if (!separator.empty())
   {
      mTitleLine.append( separator);
      mDashesLine.append( separator);
      mFormatString.append( separator);
   }  // end if

   processSpec( pnext);

} // AsciiTable::append



/// Process the table specification in the string pointed to by \a pnext and
/// fill the corresponding values into #mTitleLine, #mDashesLine and
/// #mFormatString.
/// @param[in]  pnext  Pointer to the (position in the) string to parse.
/// @since  0.7, 07.11.2016
void AsciiTable::processSpec( const char* pnext)
{

   while (*pnext != '\0')
   {
      const EvalColumn  next_col( pnext);

      mTitleLine.append( next_col.title()).append( next_col.separator());
      mDashesLine.append( string( next_col.width(), mCurrentDashChar)).
                  append( next_col.separator());
      mFormatString.append( next_col.formatString()).append( next_col.separator());
   }  // end while

} // AsciiTable::processSpec



} // namespace format
} // namespace celma


// =========================  END OF ascii_table.cpp  =========================

