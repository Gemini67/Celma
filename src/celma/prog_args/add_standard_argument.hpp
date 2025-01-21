
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
/// See documentation of function celma::prog_args::addStandardArgument.


#pragma once


#include "celma/prog_args/groups.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma::prog_args {


/// Adds a standard argument to the standard argument handler.
/// @param[in]  argString     The argument string (short and/or long argument).
/// @param[in]  dest          Pointer to the object that handles this parameter.
/// @param[in]  desc          The description of the argument to print in the
///                           usage.
/// @param[in]  std_grp_name  The name of the argument group used for standard
///                           arguments.
/// @since  1.0.0, 28.12.2017
/// @since  0.3, 19.06.2016
inline void addStandardArgument( const std::string& argString,
                                 detail::TypedArgBase* dest,
                                 const std::string& desc,
                                 const char* std_grp_name = StandardArgsGroup)
{

   auto  ah = Groups::instance().getArgHandler( std_grp_name);


   ah->addArgument( argString, dest, desc);

} // addStandardArgument


} // namespace celma::prog_args


// =====  END OF add_standard_argument.hpp  =====

