
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::FormatAnycase.


#ifndef CELMA_PROG_ARGS_DETAIL_FORMAT_ANYCASE_HPP
#define CELMA_PROG_ARGS_DETAIL_FORMAT_ANYCASE_HPP


#include <string>
#include "celma/prog_args/detail/i_format.hpp"


namespace celma { namespace prog_args { namespace detail {


/// Formats the characters in a string according to the given pattern.
///
/// @since  1.23.0, 11.04.2019
class FormatAnycase: public IFormat
{
public:
   /// Constructor, stores the pattern to use to format the value in
   /// formatValue().<br>
   /// The following characters are supported in the format pattern:
   /// - U: Formats the character to an uppercase character.
   /// - l (small l): Formats the character to a lowercase character.
   /// - anything else: character remains unchanged.
   ///
   /// @param[in]  pattern  The format pattern to use.
   /// @since  1.23.0, 11.04.2019
   explicit FormatAnycase( const std::string& pattern) noexcept( false);

   /// Virtual, empty destructor.
   ///
   /// @since  1.23.0, 11.04.2019
   virtual ~FormatAnycase() = default;

   /// Converts the text in \a val according to the pattern given in the 
   /// constructor.<br>
   /// If the text in \a val is longer than the format string, only the first
   /// characters as defined by the format string are adapted.<br>
   /// If the text in \a val is shorter than the format string, just the first
   /// characters will be formatted.
   ///
   /// @param[in,out]  val  The text to convert, returns the adapted satring.
   /// @since  1.23.0, 11.04.2019
   virtual void formatValue( std::string& val) const override;

private:
   /// The pattern that specifies how to format the string contents.
   const std::string  mPattern;

}; // FormatAnycase


} // namespace detail


// helper function
// ===============


/// Helper function to create an anycase formatter more easily.<br>
/// Usage: addArgument( ...)->addFormat( anycase( "Ulll"));
///
/// @return  The newly created FormatAnycase object.
/// @since  1.23.0, 11.04.2016
inline detail::IFormat* anycase( const std::string& pattern)
{
   return new detail::FormatAnycase( pattern);
} // anycase


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_FORMAT_ANYCASE_HPP


// =====  END OF format_anycase.hpp  =====

