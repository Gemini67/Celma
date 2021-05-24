
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
/// See documentation of class celma::prog_args::argument_error.


// module headerfile include
#include "celma/prog_args/argument_error.hpp"


namespace celma::prog_args {



/// Constructor with a std::string.
/// @param[in]  arg  Text for the exception.
/// @since  x.y.z, 20.05.2021
argument_error::argument_error( const std::string& arg) noexcept( true):
   std::runtime_error( arg)
{
} // argument_error::argument_error



/// Constructor with a C string.
/// @param[in]  arg  Text for the exception.
/// @since  x.y.z, 20.05.2021
argument_error::argument_error( const char* arg) noexcept( true):
   std::runtime_error( arg)
{
} // argument_error::argument_error



} // namespace celma::prog_args


// =====  END OF argument_error.cpp  =====

