
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::FormatLowercase.


// module headerfile include
#include "celma/prog_args/detail/format_lowercase.hpp"


// Boost includes
#include <boost/algorithm/string.hpp>


namespace celma { namespace prog_args { namespace detail {



/// Default constructor.
/// Needed to store the name of the formatter in the base class.
///
/// @since  x.y.z, 05.11.2019
FormatLowercase::FormatLowercase():
   IFormat( "lowercase")
{
} // FormatLowercase::FormatLowercase



/// Converts the text in \a val to lowercase.
///
/// @param[in,out]  val  The text to convert to lowercase.
/// @since  0.2, 10.04.2016
void FormatLowercase::formatValue( std::string& val) const
{

   boost::to_lower( val);

} // FormatLowercase::formatValue



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF format_lowercase.cpp  =====

