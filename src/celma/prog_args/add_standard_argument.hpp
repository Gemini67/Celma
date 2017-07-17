
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
/// See documentation of template functions
/// celma::prog_args::addStandardArgument and
/// celma::prog_args::addStandardArgumentValue.


#ifndef CELMA_PROG_ARGS_ADD_STANDARD_ARGUMENT_HPP
#define CELMA_PROG_ARGS_ADD_STANDARD_ARGUMENT_HPP


#include "celma/prog_args/groups.hpp"


namespace celma { namespace prog_args {


/// Adds a standard argument to the standard argument handler.
/// @tparam  F  The type of the method/function to call when the standard
///             argument is used.
/// @param[in]  argString     The argument string (short and/or long argument).
/// @param[in]  fun           The function to call for this argument.
/// @param[in]  func_name     The name of the function to call.
/// @param[in]  desc          The description of the argument to print in the
///                           usage.
/// @param[in]  std_grp_name  The name of the argument group used for standard
///                           arguments.
/// @since  0.3, 19.06.2016
template< typename F> void addStandardArgument( const std::string& argString,
                                                F fun,
                                                const std::string& func_name,
                                                const std::string& desc,
                                                const char* std_grp_name = StandardArgsGroup)
{

   auto  ah = Groups::instance().getArgHandler( std_grp_name);


   ah->addArgument( argString, fun, func_name, desc);

} // addStandardArgument


/// Adds a standard argument to the standard argument handler.
/// @tparam  F  The type of the function to call when the standard argument is
///             used.
/// @param[in]  argString     The argument string (short and/or long argument).
/// @param[in]  fun           The function to call for this argument.
/// @param[in]  func_name     The name of the function to call.
/// @param                    Dummy parameter used to distinguish from the
///                           non-value variant.
/// @param[in]  desc          The description of the argument to print in the
///                           usage.
/// @param[in]  std_grp_name  The name of the argument group used for standard
///                           arguments.
/// @since  0.3, 19.06.2016
template< typename F> void addStandardArgument( const std::string& argString,
                                                F fun,
                                                const std::string& func_name,
                                                bool /* takes_value */,
                                                const std::string& desc,
                                                const char* std_grp_name = StandardArgsGroup)
{

   auto  ah = Groups::instance().getArgHandler( std_grp_name);


   ah->addArgument( argString, fun, func_name, true, desc);

} // addStandardArgument


} // namespace prog_args
} // namespace celma


#endif   // CELMA_PROG_ARGS_ADD_STANDARD_ARGUMENT_HPP


// ====================  END OF add_standard_argument.hpp  ====================

