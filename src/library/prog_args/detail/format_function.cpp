
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::prog_args::detail::FormatFunction.


// module headerfile include
#include "celma/prog_args/detail/format_function.hpp"


namespace celma::prog_args::detail {



/// Constructor, stores the function to call to format the value.
///
/// @param[in]  fun   The function to call to format a value.
/// @param[in]  desc  Description of the function.
/// @since  x.y.z, 21.11.2021
FormatFunction::FormatFunction( format_func_t fun, const std::string& desc)
   noexcept:
      IFormat( desc),
      mFormatFunc( fun)
{
} // FormatFunction::FormatFunction



/// Calls the format function.
///
/// @param[in,out]  val  The value string to format.
/// @since  x.y.z, 21.11.2021
void FormatFunction::formatValue( std::string& val) const
{

   mFormatFunc( val);

} // FormatFunction::formatValue



} // namespace celma::prog_args::detail


// =====  END OF format_function.cpp  =====

