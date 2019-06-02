
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


// module header file include
#include "celma/prog_args/detail/format_anycase.hpp"


// OS/C lib includes
#include <cctype>


// C++ Standard Library includes
#include <stdexcept>


namespace celma { namespace prog_args { namespace detail {



/// Constructor, stores the pattern to use to format the value in
/// formatValue().<br>
/// The following characters are supported in the format pattern:
/// - U: Formats the character to an uppercase character.
/// - l (small l): Formats the character to a lowercase character.
/// - anything else: character remains unchanged.
///
/// @param[in]  pattern  The format pattern to use.
/// @since  1.23.0, 11.04.2019
FormatAnycase::FormatAnycase( const std::string& pattern):
   mPattern( pattern)
{

   if (mPattern.empty())
      throw std::invalid_argument( "format pattern may not be empty");

} // FormatAnycase::FormatAnycase



/// Converts the text in \a val according to the pattern given in the 
/// constructor.
///
/// @param[in,out]  val  The text to convert, returns the adapted satring.
/// @since  1.23.0, 11.04.2019
void FormatAnycase::formatValue( std::string& val) const
{

   std::string::size_type  len = std::min( mPattern.length(), val.length());

   for (std::string::size_type idx = 0; idx < len; ++idx)
   {
      if (mPattern[ idx] == 'U')
         val[ idx] = ::toupper( val[ idx]);
      else if (mPattern[ idx] == 'l')
         val[ idx] = ::tolower( val[ idx]);
   } // end for

} // FormatAnycase::formatValue



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF format_anycase.cpp  =====

