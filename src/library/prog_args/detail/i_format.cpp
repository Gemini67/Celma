
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
/// See documentation of class celma::prog_args::detail::IFormat.


// module headerfile include
#include "celma/prog_args/detail/i_format.hpp"


namespace celma { namespace prog_args { namespace detail {



/// Constructor, stores the name of the formatter.
///
/// @param[in]  desc  The description/name of the formatter.
/// @since  1.33.0, 05.11.2019
IFormat::IFormat( const std::string& desc):
   mDescription( desc)
{
} // IFormat::IFormat



} // namespace detail
} // namespace prog_args
} // namespace celma


// =====  END OF i_format.cpp  =====

