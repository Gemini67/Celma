
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
**  Description:
**    Test program for using the log standard arguments.
**    test procedure:
**    - Set up the arguments.
**    - Set up two logs.
**    - Write two log messages, these should not be visible.
**    - Use the standard log argument, should succeed this time.
**    - Write two log messages, one of them should be written to stdout.
**
--*/


#include "celma/common/arg_string_2_array.hpp"
#include "celma/log/detail/add_log_standard_args.hpp"
#include "celma/log/detail/log.hpp"
#include "celma/log/logging.hpp"
#include "celma/log/log_macros.hpp"
#include "celma/prog_args/groups.hpp"


using celma::log::Logging;


// module definitions
static celma::prog_args::Groups::SharedArgHndl  ah;


// static functions prototypes
static void do_arguments_first();
static void do_arguments_again( int argc, char* argv[]);



/// Main function of the test program.<br>
/// For the 'normal' test, no arguments are expected. Arguments can be used
/// e.g. to check the usage.
/// @param[in]  argc    Number of arguments.
/// @param[in]  argv[]  List of arguments.
/// @return  \c EXIT_SUCCESS or \c EXIT_FAILURE.
/// @since  0.3, 19.06.2016
int main( int argc, char* argv[])
{

   do_arguments_first();

   const auto  log_debug = Logging::instance().findCreateLog( "debug");
   const auto  log_trace = Logging::instance().findCreateLog( "trace");

   LOG( log_debug) << "This message should not appear anywhere.";
   LOG( log_trace) << "This message too should not appear anywhere.";

   do_arguments_again( argc, argv);

   LOG( log_debug) << "This is the only message that you should see!";
   LOG( log_trace) << "Still, this message should not appear anywhere.";

   exit( EXIT_SUCCESS);
} // end main



/// First test: Set up the arguments, then 'use' the standard log argument.
/// Should throw because the logs are not set up yet.
/// @since  0.3, 19.06.2016
static void do_arguments_first()
{

   ah.reset( new celma::prog_args::Handler( celma::prog_args::Handler::hfHelpShort | celma::prog_args::Handler::hfHelpLong));

   try
   {
      celma::prog_args::Groups::instance().addArgHandler( "Program Arguments:", ah);
      celma::log::detail::addLogStandardArgs();
   } catch (const std::exception& e)
   {
      std::cerr << "Caught exception: " << e.what() << "!" << std::endl;
      ::exit( EXIT_FAILURE);
   } // end try

} // end do_arguments_first



/// Second test: 'Use' the standard log argument again, should succeed this time.
/// @param[in]  argc    Number of program arguments.
/// @param[in]  argv[]  List of program arguments.
/// @since  0.3, 19.06.2016
static void do_arguments_again( int argc, char* argv[])
{

   try
   {
      if (argc == 1)
      {
         celma::common::ArgString2Array  as2a( "--log-stdout debug", argv[ 0]);
         celma::prog_args::Groups::instance().evalArguments( as2a.mArgc, as2a.mpArgv);
      } else
      {
         celma::prog_args::Groups::instance().evalArguments( argc, argv);
      } // end if
   } catch (const std::exception& e)
   {
      std::cerr << "Caught exception: " << e.what() << "!" << std::endl;
      ::exit( EXIT_FAILURE);
   } // end try

} // end do_arguments_again



// ==================  END OF test_log_standard_argument.cpp  ==================

