
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
**    - Use the standard log argument, should succeed this time.
**    - Write two log messages, one of them should be written to stdout.
**
--*/



#include "add_log_standard_args.hpp"
#include "arg_string_2_array.hpp"
#include "argument_groups.hpp"
#include "logging.hpp"
#include "log.hpp"
#include "log_macros.hpp"


using celma::log::Logging;


// static functions prototypes
static void do_arguments_first( int argc, char* argv[]);
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

   do_arguments_first( argc, argv);

   const int  log_debug = log::Logging::instance().findCreateLog( "debug");
   const int  log_trace = log::Logging::instance().findCreateLog( "trace");

   LOG( log_debug) << "This message should not appear anywhere.";
   LOG( log_trace) << "This message too should not appear anywhere.";

   do_arguments_again( argc, argv);

   LOG( log_debug) << "This is the only message that you should see!";
   LOG( log_trace) << "Still, this message should not appear anywhere.";

   exit( EXIT_SUCCESS);
} // main



/// First test: Set up the arguments, then 'use' the standard log argument.
/// Should throw because the logs are not set up yet.
/// @param[in]  argc    Number of program arguments.
/// @param[in]  argv[]  List of program arguments.
/// @since  0.3, 19.06.2016
static void do_arguments_first( int argc, char* argv[])
{

   ArgumentGroups::SharedArgHndl  ah( new ArgumentHandler( ArgumentHandler::hfHelpShort | ArgumentHandler::hfHelpLong));

   try
   {
      ArgumentGroups::instance().addArgHandler( "Program Arguments:", ah);
      log::addLogStandardArgs();

      if (argc == 1)
      {
         const ArgString2Array  as2a( "--log-stdout debug", argv[ 0]);
         ArgumentGroups::instance().evalArguments( as2a.mArgC, as2a.mpArgV);
      } else
      {
         ArgumentGroups::instance().evalArguments( argc, argv);
      } // end if

      cerr << "*** Error: Expect exception upon first pass (log object unknown!" << endl;
      exit( EXIT_FAILURE);
   } catch (const exception& e)
   {
      // silently discard expected exception
   } // end try

} // do_arguments_first



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
         const ArgString2Array  as2a( "--log-stdout debug", argv[ 0]);
         ArgumentGroups::instance().evalArguments( as2a.mArgC, as2a.mpArgV);
      } else
      {
         ArgumentGroups::instance().evalArguments( argc, argv);
      } // end if
   } catch (const exception& e)
   {
      cerr << "Caught exception: " << e.what() << "!" << endl;
      exit( EXIT_FAILURE);
   } // end try

} // do_arguments_again



// =====  END OF test_log_standard_argument.cpp  =====

