
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
/// See documentation of class celma::prog_args::detail::FormatUppercase.


// module header file include
#include "celma/prog_args/detail/format_uppercase.hpp"


// Boost includes
#include <boost/algorithm/string.hpp>


namespace celma { namespace prog_args { namespace detail {



/// Default constructor.
/// Needed to store the name of the formatter in the base class.
///
/// @since  1.33.0, 05.11.2019
FormatUppercase::FormatUppercase():
   IFormat( "uppercase")
{
} // FormatUppercase::FormatUppercase



/// Converts the text in \a val to uppercase.
///
/// @param[in,out]  val  The text to convert to uppercase.
/// @since  0.2, 10.04.2016
void FormatUppercase::formatValue( std::string& val) const
{

   boost::to_upper( val);

} // FormatUppercase::formatValue



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF format_uppercase.cpp  =====

