
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
/// See documentation of class celma::prog_args::detail::FormatLowercase.


// module header file include
#include "celma/prog_args/detail/format_lowercase.hpp"


// Boost includes
#include <boost/algorithm/string.hpp>


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Converts the text in \a val to lowercase.
/// @param[in,out]  val  The text to convert to lowercase.
/// @since  0.2, 10.04.2016
void FormatLowercase::formatValue( string& val) const
{

   boost::to_lower( val);

} // end FormatLowercase::formatValue



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF format_lowercase.cpp  =========================
