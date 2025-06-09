
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2025 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of type definitions
/// - celma::prog_args::detail::ArgHandlerCallable
/// - celma::prog_args::detail::ArgHandlerCallableValue.


#pragma once


#include <functional>
#include <string>


namespace celma::prog_args::detail {


/// Type of the callables (functions, methods) that can be defined as argument
/// handlers for arguments without values.
using ArgHandlerCallable = std::function< void( bool)>;


/// Type of the callables (functions, methods) that can be defined as argument
/// handlers for arguments with values.
using ArgHandlerCallableValue = std::function< void( const std::string&, bool)>;


} // namespace celma::prog_args::detail


// =====  END OF arg_handler_callable.hpp  =====

