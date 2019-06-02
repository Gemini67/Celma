
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
/// See documentation of type definitions
/// - celma::prog_args::detail::ArgHandlerCallable
/// - celma::prog_args::detail::ArgHandlerCallableValue.


#ifndef CELMA_PROG_ARGS_DETAIL_ARG_HANDLER_CALLABLE_HPP
#define CELMA_PROG_ARGS_DETAIL_ARG_HANDLER_CALLABLE_HPP


#include <functional>
#include <string>


namespace celma { namespace prog_args { namespace detail {


/// Type of the callables (functions, methods) that can be defined as argument
/// handlers for arguments without values.
using ArgHandlerCallable = std::function< void( bool)>;


/// Type of the callables (functions, methods) that can be defined as argument
/// handlers for arguments with values.
using ArgHandlerCallableValue = std::function< void( const std::string&, bool)>;


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARG_HANDLER_CALLABLE_HPP


// =====  END OF arg_handler_callable.hpp  =====

