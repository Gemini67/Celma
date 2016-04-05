
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


#ifndef CELMA_FORMAT_TEXT_BLOCK_HPP
#define CELMA_FORMAT_TEXT_BLOCK_HPP


#include <iosfwd>
#include <string>


namespace celma { namespace format {


/// Helper class to format a text (string) into a block.<br>
/// The following special features are supported:
/// - Maximum line length.
/// - Indention (applied to all lines).
/// - Forced line-breaks:
///   The string can contain newline characters (\n) in order to enforce a line
///   break.
/// - Lists:
///   If a line starts with a dash, when the text is broken onto multiple
///   lines, the second, third etc. line is indented to form a list like this
///   one.
/// - Forced line-break in list:
///   To force a line break in list (like thise line here), use the token ' nn '
///   in the text.
/// @since  0.2, 04.04.2016
class TextBlock
{
public:
   /// Constructor.
   /// @param[in]  indent       Number of characters to indent the block of text.
   /// @param[in]  length       Maximum line length to print.
   /// @param[in]  indentFirst  Specifies if the first line of the text should
   ///                          be indented too (\c true), or not (\c false)
   ///                          e.g. because some other text was already printed.
   /// @since  0.2, 04.04.2016
   TextBlock( int indent, int length, bool indentFirst);

   /// Formats the text (string) as specified in the constructor.
   /// @param[out]  os   The stream to write to.
   /// @param[in]   txt  The text to format.
   /// @since  0.2, 04.04.2016
   void format( std::ostream& os, const std::string& txt);

private:
   /// Do not copy.
   /// @since  0.2, 05.04.2016
   TextBlock( const TextBlock&) = delete;

   /// Do not assign.
   /// @since  0.2, 05.04.2016
   TextBlock& operator =( const TextBlock&) = delete;

   /// Formats a single line of output.<br>
   /// Writes words until the specified line length would be exceeded, then
   /// starts a new line with indention.<br>
   /// If a line starts with a dash, the text of the second, third etc. line is
   /// indented two additional characters.
   /// @param[out]  os    The stream to write to.
   /// @param[in]   line  The line to format/print.
   /// @since  0.2, 04.04.2016
   void formatLine( std::ostream& os, const std::string& line);

   /// The number of characters to indent the text.
   const int                     mIndent;
   /// Maximum line length to print.
   const std::string::size_type  mLength;
   /// Specifies if the first line should be indented (\c true) or not (\c false).
   const bool                    mIndentFirst;
   /// The prepared block of spaces to print as indent.
   const std::string             mIndentSpaces;

}; // TextBlock


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_TEXT_BLOCK_HPP


// =========================  END OF text_block.hpp  =========================

