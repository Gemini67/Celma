
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
/// See documentation of class celma::celma::prog_args::@@@.


#pragma once


#include <string>


namespace celma::prog_args {


class Handler;


/// Evaluates a complete argument string.
/// This can be used e.g. if an argument string is passed to a function and
/// should be evaluated like main function arguments, or in test
/// programs.
///
/// @param[in]  handler     Handler object to evaluate the arguments with.
/// @param[in]  arg_string  Complete argument and values string.
/// @param[in]  prog_name   Optional program name to be set.
/// @since  1.46.1, 19.08.2021
void evalArgumentString( Handler& handler, const std::string& arg_string,
   const char* prog_name = nullptr) noexcept( false);


} // namespace celma::prog_args


// =====  END OF eval_argument_string.hpp  =====

