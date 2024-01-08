
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::Tokenizer.


#pragma once


#include <string>
#include <boost/tokenizer.hpp>
#include "celma/common/tokenizer_base.hpp"


namespace celma::common {


/// Helper class to easily set up a string tokenizer for a single character
/// separator.<br>
/// Internally, the Boost.Tokenizer is used.
/// @since  0.2, 04.04.2016
class Tokenizer: public TokenizerBase< boost::char_separator< char>>
{
public:
   /// Constructor. Empty tokens are ignored.
   /// @param[in]  s          The string to split.
   /// @param[in]  separator  The separator token.
   /// @since  0.2, 04.04.2016
   Tokenizer( const std::string& s, char separator);

   /// Constructor to set up a tokenizer that also returns empty tokens (two
   /// consecutive separators found in the string).
   /// @param[in]  s          The string to split.
   /// @param[in]  separator  The separator token.
   /// @param[in]  keepEmpty  Third parameter used to distinguish the
   ///                        constructors, the value is actually ignored.
   /// @since  0.2, 04.04.2016
   Tokenizer( const std::string& s, char separator, bool keepEmpty);

private:
   /// Helper function used to turn the single character into a string.
   /// @param[in]  c  The character.
   /// @return  Pointer to the string that contains the character.
   /// @since  0.2, 04.04.2016
   const char* convChar2String( char c);

}; // Tokenizer


// inlined methods
// ===============


inline const char* Tokenizer::convChar2String( const char c)
{
   static char  s[ 2] = { 0, 0 };
   s[ 0] = c;
   return s;
} // Tokenizer::convChar2String


inline Tokenizer::Tokenizer( const std::string& s, const char separator):
   TokenizerBase< boost::char_separator< char>>( s, boost::char_separator< char>( convChar2String( separator)))
{
} // Tokenizer::Tokenizer


inline Tokenizer::Tokenizer( const std::string& s, const char separator,
                             bool /* keepEmpty */):
   TokenizerBase< boost::char_separator< char>>( s, boost::char_separator< char>( convChar2String( separator), "", boost::keep_empty_tokens))
{
} // Tokenizer::Tokenizer


} // namespace celma::common


// =====  END OF tokenizer.hpp  =====

