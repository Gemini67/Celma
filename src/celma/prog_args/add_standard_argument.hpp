
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of function celma::prog_args::addStandardArgument.


#ifndef CELMA_PROG_ARGS_ADD_STANDARD_ARGUMENT_HPP
#define CELMA_PROG_ARGS_ADD_STANDARD_ARGUMENT_HPP


#include "celma/prog_args/groups.hpp"
#include "celma/prog_args/detail/typed_arg_base.hpp"


namespace celma { namespace prog_args {


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


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_ADD_STANDARD_ARGUMENT_HPP


// ====================  END OF add_standard_argument.hpp  ====================

