
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
/// See documentation of typedef celma::prog_args::detail::ArgHandlerCallable.


#ifndef CELMA_PROG_ARGS_DETAIL_ARG_HANDLER_CALLABLE_HPP
#define CELMA_PROG_ARGS_DETAIL_ARG_HANDLER_CALLABLE_HPP


#include <boost/function.hpp>


namespace celma { namespace prog_args { namespace detail {


/// Type of the callables (functions, methods) that can be defined as argument
/// handlers for arguments without values.
typedef boost::function< void( void)>  ArgHandlerCallable;


/// Type of the callables (functions, methods) that can be defined as argument
/// handlers for arguments with values.
typedef boost::function< void( const std::string&)>  ArgHandlerCallableValue;


} // namespace detail
} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_DETAIL_ARG_HANDLER_CALLABLE_HPP


// =========================  END OF arg_handler_callable.hpp  =========================

