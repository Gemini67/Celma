
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
/// See documentation of function celma::log::detail::addLogStandardArgs().


#ifndef CELMA_LOG_DETAIL_ADD_LOG_STANDARD_ARGS_HPP
#define CELMA_LOG_DETAIL_ADD_LOG_STANDARD_ARGS_HPP


#include "celma/prog_args/standard_arguments_group.hpp"


namespace celma { namespace log { namespace detail {


/// Adds (standard) log arguments:
/// - '--log-stdout \<logname\>' that adds \c stdout as a log destination.
///
/// @param[in]  std_grp_name  The name of the argument group used for standard
///                           arguments.
/// @since  0.3, 19.06.2016
void addLogStandardArgs( const char* std_grp_name = prog_args::StandardArgsGroup);


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_ADD_LOG_STANDARD_ARGS_HPP


// ====================  END OF add_log_standard_args.hpp  ====================

