
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
/// See documentation of class celma::prog_args::detail::FormatUppercase.


// module header file include
#include "celma/prog_args/detail/format_uppercase.hpp"


// Boost includes
#include <boost/algorithm/string.hpp>


using namespace std;


namespace celma { namespace prog_args { namespace detail {



/// Converts the text in \a val to uppercase.
/// @param[in,out]  val  The text to convert to uppercase.
/// @since  0.2, 10.04.2016
void FormatUppercase::formatValue( string& val) const
{

   boost::to_upper( val);

} // end FormatUppercase::formatValue



} // namespace detail
} // namespace prog_args
} // namespace celma


// =========================  END OF format_uppercase.cpp  =========================
