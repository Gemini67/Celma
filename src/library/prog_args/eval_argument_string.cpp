
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


// module headerfile include
#include "celma/prog_args/eval_argument_string.hpp"


// project includes
#include "celma/appl/arg_string_2_array.hpp"
#include "celma/prog_args/handler.hpp"


namespace celma::prog_args {



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
   const char* prog_name) noexcept( false)
{

   auto const  as2a = appl::make_arg_array( arg_string, prog_name);


   handler.evalArguments( as2a.mArgC, as2a.mpArgV);

} // evalArgumentString



} // namespace celma::prog_args


// =====  END OF eval_argument_string.cpp  =====



