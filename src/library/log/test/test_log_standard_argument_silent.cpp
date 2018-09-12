
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the log standard arguments.
**    test procedure:
**    - Set up the arguments.
**    - Use the standard log argument: throws because the log is not set up yet.
**    - Set up two logs.
**    - Write two log messages, these should not be visible.
**
--*/



#include "celma/appl/arg_string_2_array.hpp"
#include "celma/log/detail/add_log_standard_args.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "celma/prog_args/groups.hpp"


using celma::log::Logging;


// static functions prototypes
static void do_arguments_first( int argc, char* argv[]);



/// Main function of the test program.<br>
/// For the 'normal' test, no arguments are expected. Arguments can be used
/// e.g. to check the usage.
/// @param[in]  argc    Number of arguments.
/// @param[in]  argv[]  List of arguments.
/// @return  \c EXIT_SUCCESS or \c EXIT_FAILURE.
/// @since  0.3, 19.06.2016
int main( int argc, char* argv[])
{

   do_arguments_first( argc, argv);

   const int  log_debug = Logging::instance().findCreateLog( "debug");
   const int  log_trace = Logging::instance().findCreateLog( "trace");

   LOG( log_debug) << "This message should not appear anywhere.";
   LOG( log_trace) << "This message too should not appear anywhere.";

   exit( EXIT_SUCCESS);
} // main



/// First test: Set up the arguments, then 'use' the standard log argument.
/// Should throw because the logs are not set up yet.
/// @param[in]  argc    Number of program arguments.
/// @param[in]  argv[]  List of program arguments.
/// @since  0.3, 19.06.2016
static void do_arguments_first( int argc, char* argv[])
{

   try
   {
      auto  ah = celma::prog_args::Groups::instance().getArgHandler( "Program Arguments:",
                                                                     celma::prog_args::Handler::AllHelp);
      celma::log::detail::addLogStandardArgs();

      if (argc == 1)
      {
         const celma::appl::ArgString2Array  as2a( "--log-stdout debug", argv[ 0]);
         celma::prog_args::Groups::instance().evalArguments( as2a.mArgC, as2a.mpArgV);
      } else
      {
         celma::prog_args::Groups::instance().evalArguments( argc, argv);
      } // end if

      std::cerr << "*** Error: Expect exception upon first pass (log object unknown!" << std::endl;
      exit( EXIT_FAILURE);
   } catch (const std::exception& e)
   {
      // silently discard expected exception
   } // end try

} // do_arguments_first



// =====  END OF test_log_standard_argument_silent.cpp  =====

