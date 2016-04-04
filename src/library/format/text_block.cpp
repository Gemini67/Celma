
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
/// See documentation of class celma::format::TextBlock.


// module header file include
#include "celma/format/text_block.hpp"


// Standard Template Library includes
#include <iostream>


// project includes
#include "celma/common/first_pass.hpp"
#include "celma/common/tokenizer.hpp"


using namespace std;


namespace celma { namespace format {


/// Constructor.
/// @param[in]  indent       Number of characters to indent the block of text.
/// @param[in]  length       Maximum line length to print.
/// @param[in]  indentFirst  Specifies if the first line of the text should
///                          be indented too (\c true), or not (\c false)
///                          e.g. because some other text was already printed.
/// @since  0.2, 04.04.2016
TextBlock::TextBlock( int indent, int length, bool indentFirst):
   mIndent( indent),
   mLength( length),
   mIndentFirst( indentFirst),
   mIndentSpaces( mIndent, ' ')
{
} // end TextBlock::TextBlock



/// Formats the text (string) as specified in the constructor.<br>
/// This function splits the text into separate lines and then takes care of
/// the indention for each (new) line.
/// @param[in]   txt  The text to format.
/// @param[out]  os   The stream to write to.
/// @since  0.2, 04.04.2016
void TextBlock::format( const string& txt, ostream& os)
{

   common::Tokenizer  tokNL( txt, '\n');
   common::FirstPass  firstLine;


   for (common::Tokenizer::iterator tiNL = tokNL.begin(); tiNL != tokNL.end(); ++tiNL)
   {
      const string  currLine( *tiNL);

      if (firstLine)
      {
         if (mIndentFirst)
            os << mIndentSpaces;
      } else
      {
         os << endl << mIndentSpaces;
      } // end if

      formatLine( os, currLine);
   } // end for

} // end TextBlock::format



/// Formats a single line of output.<br>
/// Writes words until the specified line length would be exceeded, then
/// starts a new line with indention.<br>
/// If a line starts with a dash, the text of the second, third etc. line is
/// indented two additional characters.
/// @param[out]  os    The stream to write to.
/// @param[in]   line  The line to format/print.
/// @since  0.2, 04.04.2016
void TextBlock::formatLine( ostream& os, const string& line)
{

   common::Tokenizer  tokWord( line, ' ');
   string::size_type  currLength = mIndentSpaces.length();
   bool               lineStartsWithDash = false;


   for (common::Tokenizer::iterator tiWord = tokWord.begin(); tiWord != tokWord.end(); ++tiWord)
   {
      const string  currWord( *tiWord);

      // check if the current word still fits onto the current line,
      // otherwise start a new line
      // allow output length == defined length to include the last column
      if (currWord == "nn")
      {
         os << endl << mIndentSpaces;
         currLength = mIndentSpaces.length();
         if (lineStartsWithDash)
         {
            // trick: only indent 1 additional character here
            // because afterwards a single word without dash will be written,
            // and because currLength != mIndentSpaces.length(), it will be
            // preceded by a space
            // so, instead of introducing a new flag or making the check for the
            // need of space(s) more complicated, we only add one space here
            os << " ";
            ++currLength;
         } // end if
      } else if (currLength + currWord.length() + 1 > mLength)
      {
         os << endl << mIndentSpaces;
         if (lineStartsWithDash)
            os << "  ";
         os << currWord;
         currLength = mIndentSpaces.length() + currWord.length();
         if (lineStartsWithDash)
            currLength += 2;
      } else
      {
         // if this is not the first word, add a blank
         if (currLength != mIndentSpaces.length())
         {
            os << " ";
            ++currLength;
         } else if (currWord[ 0] == '-')
         {
            lineStartsWithDash = true;
         } // end if

         os << currWord;
         currLength += currWord.length();
      } // end if
   } // end for

} // end TextBlock::formatLine



} // namespace format
} // namespace celma


// =========================  END OF text_block.cpp  =========================

