
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for the feature "evaluate arguments and exit on error" in the
**    module celma::prog_args::Handler.
**    Most arguments of the test program cause it to exit with an error.
**
--*/



#include <stdexcept>
#include "celma/prog_args.hpp"


using celma::prog_args::Handler;


namespace {


/// Throws an integer value.
///
/// @since  x.y.z, 03.04.2019
void throw_integer_error()
{

   throw 42;
} // throw_integer_error


/// Throws a standard exception.
///
/// @since  x.y.z, 03.04.2019
void throw_exception()
{

   throw std::exception();
} // throw_exception


/// Throws an invalid argument exception.
///
/// @since  x.y.z, 03.04.2019
void throw_invalid_argument()
{

   throw std::invalid_argument( "invalid argument");
} // throw_invalid_argument


/// Throws a logic error exception.
///
/// @since  x.y.z, 03.04.2019
void throw_logic_error()
{

   throw std::logic_error( "logic");
} // throw_logic_error


/// Throws an out-of-range exception.
///
/// @since  x.y.z, 03.04.2019
void throw_out_of_range()
{

   throw std::out_of_range( "out of range");
} // throw_out_of_range


/// Throws an overflow error exception.
///
/// @since  x.y.z, 03.04.2019
void throw_overflow_error()
{

   throw std::overflow_error( "overflow");
} // throw_overflow_error


/// Throws a runtime error exception.
///
/// @since  x.y.z, 03.04.2019
void throw_runtime_error()
{

   throw std::runtime_error( "runtime");
} // throw_runtime_error


/// Throws an underflow error exception.
///
/// @since  x.y.z, 03.04.2019
void throw_underflow_error()
{

   throw std::underflow_error( "underflow");
} // throw_underflow_error


} // namespace


/// The main function of the test progrema.<br>
/// Defines various arguments that throw when used. The point is to test the
/// error handling in the function
/// celma::prog_args::Handler::evalArgumentsErrorExit().
///
/// @param[in]  argc
///    Number of arguments passed.
/// @param[in]  argv[]
///    List of argument strings.
/// @return  \c EXIT_FAILURE on error, \c EXIT_SUCCESS otherwise.
/// @since  x.y.z, 03.04.2019
int main( int argc, char* argv[])
{

   Handler  ah( 0);
   bool     flag = false;


   ah.addArgument( "e", DEST_FUNCTION( throw_exception),
      "Throws an exception.");
   ah.addArgument( "f", DEST_VAR( flag), "Sets a flag.");
   ah.addArgument( "i", DEST_FUNCTION( throw_integer_error),
      "Throws an integer.");
   ah.addArgument( "l", DEST_FUNCTION( throw_logic_error),
      "Throws a logic error exception.");
   ah.addArgument( "o", DEST_FUNCTION( throw_out_of_range),
      "Throws an out of range exception.");
   ah.addArgument( "r", DEST_FUNCTION( throw_runtime_error),
      "Throws a runtime error exception.");
   ah.addArgument( "v", DEST_FUNCTION( throw_invalid_argument),
      "Throws an invalid argument exception.");
   ah.addArgument( "O", DEST_FUNCTION( throw_overflow_error),
      "Throws an overflow error exception.");
   ah.addArgument( "U", DEST_FUNCTION( throw_underflow_error),
      "Throws an underflow error exception.");

   ah.evalArgumentsErrorExit( argc, argv, "*** ERROR: ");

   return EXIT_SUCCESS;
} // main



// =====  END OF test_arg_eval_error_exit.cpp  =====

