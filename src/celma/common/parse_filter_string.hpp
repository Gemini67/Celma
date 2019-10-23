
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
/// See documentation of template function celma::common::parseFilterString()<>.


#ifndef CELMA_COMMON_PARSE_FILTER_STRING_HPP
#define CELMA_COMMON_PARSE_FILTER_STRING_HPP


#include <stdexcept>
#include <string>
#include "celma/common/tokenizer.hpp"
#include "celma/common/value_filter.hpp"
// the following headerfile must be included last
#include "celma/common/detail/parse_filter_combination.hpp"


namespace celma { namespace common {


/// Parses a value filter definition string.
/// The following format is expected:
/// - Multiple filters separated by commas: A value must match at least one of
///   these filters (or combination).
/// - Filters concatenated with plus signs: A value must match all of these
///   filters (and combination).
/// - Single numbers must match exactly.
/// - Single numbers preceeded by an exclamation mark: %Value must be different
///   from this value.
/// - Ranges <m>-<n>: %Value must be in this range, bounds inclusive.
/// - Range preceeded by an exclamation mark: %Value must be outside of the
///   range.
/// - A lower limit can be specified with an opening angle bracket: [<nbr>.
///   Means: %Value must be greater than or equal to this limit.
/// - Finally, an upper limit can be specified with a closing angle bracket:
///   ]<nbr>. Means: %Value must be less than this limit.
///
/// @param[in]  str
///    The string with the filter definitions to parse.
/// @return
///    The object that contains all the filters.
/// @throw
///    std::invalid_argument if the contents of the filter string are invalid.
/// @since  x.y.z, 09.10.2019
template< typename T>
   ValueFilter< T> parseFilterString( const std::string& str) noexcept( false)
{

   if (str.empty())
      throw std::invalid_argument( "filter string must not be empty");

   ValueFilter< T>  vf;
   Tokenizer        tk( str, ',');

   for (auto const& cond : tk)
   {
      detail::parseFilterCombination( vf, cond);
   } // end for

   // rely on RVO to do the right thing
   return vf;
} // parseFilterString


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_PARSE_FILTER_STRING_HPP


// =====  END OF parse_filter_string.hpp  =====

