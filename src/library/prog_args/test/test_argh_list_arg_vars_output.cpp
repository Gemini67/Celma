
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2021 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


// module to test headerfile include
#include "celma/prog_args.hpp"


#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include "celma/appl/arg_string_2_array.hpp"


using celma::appl::make_arg_array;
using celma::prog_args::Handler;
using std::cerr;
using std::endl;
using std::exception;
using std::string;


static void callable_function( bool);


/// 
/// @param[in]  argc    .
/// @param[in]  argv[]  .
/// @return  .
/// @since  0.2, 10.04.2016
int main( int /* argc */, char* argv[])
{

   {
      Handler       ah( 0);
      const string  args( "--list-arg-vars");
      auto const    as2a = make_arg_array( args, argv[ 0]);

      try
      {
         ah.evalArguments( as2a.mArgC, as2a.mpArgV);
         cerr << "*** ERROR: Expected exception for 'unknown argument!" << endl;
         return EXIT_FAILURE;
      } catch (const std::invalid_argument& e)
      {
         if (strcmp( e.what(), "Unknown argument 'list-arg-vars'") != 0)
         {
            cerr << "*** ERROR: Expected exception \"Unknown argument 'list-arg-vars'\", got \""
                 << e.what() << "\"!" << endl;
            return EXIT_FAILURE;
         } // end if
      } catch (const exception& e)
      {
         cerr << "*** ERROR: Expected exception type 'invalid_argument', "
              << "text \"Unknown argument 'list-arg-vars'\", got other type, text \""
              << e.what() << "\"!" << endl;
         return EXIT_FAILURE;
      } catch (...)
      {
         cerr << "*** ERROR: Exception with unknown type received!" << endl;
         return EXIT_FAILURE;
      } // end try
   } // end scope

   try
   {
      Handler       ah( Handler::hfListArgVar);
      const string  args( "--list-arg-vars --integer 42");
      auto const    as2a = make_arg_array( args, argv[ 0]);
      bool          my_flag = false;
      int           my_int;
      string        my_string;

      ah.addArgument( "f",        DEST_VAR( my_flag),    "My flag.");
      ah.addArgument( "integer",  DEST_VAR( my_int),     "My integer.")
                    ->setIsMandatory();
      ah.addArgument( "s,string", DEST_VAR( my_string),  "My string.");

      ah.evalArguments( as2a.mArgC, as2a.mpArgV);
   } catch (const exception& e)
   {
      cerr << "*** ERROR: Caught exception \"" << e.what() << "\"!" << endl;
      return EXIT_FAILURE;
   } catch (...)
   {
      cerr << "*** ERROR: Exception with unknown type received!" << endl;
      return EXIT_FAILURE;
   } // end try

   std::cout << string( 80, '-') << endl << endl;

   try
   {
      Handler  ah( 0);

      ah.addArgumentListArgVars( "V");

      const string            args( "-V --integer 42 --sl schubidu -V");
      auto const              as2a = make_arg_array( args, argv[ 0]);
      bool                    my_flag = false;
      int                     my_int;
      long                    my_long;
      uint64_t                my_ulong;
      string                  my_string;
      std::optional< string>  my_ca_string;
      std::vector< string>    my_string_list;

      ah.addArgument( "f",        DEST_VAR( my_flag),    "My flag.");
      ah.addArgument( "integer",  DEST_VAR( my_int),     "My integer.")
                    ->setIsMandatory();
      ah.addArgument( "s,string", DEST_VAR( my_string),  "My string.")
                    ->setPrintDefault( false);
      ah.addArgument( "long",     DEST_VAR( my_long),
                      "My hidden long integer.")->setIsHidden();
      ah.addArgument( "ulong",    DEST_VAR( my_ulong),
                      "My unsigned long integer.");
      ah.addArgument( "call",     DEST_FUNCTION( callable_function),
                      "My function.");
      ah.addArgument( "cas",      DEST_VAR( my_ca_string),
                      "My std::optional string");
      ah.addArgument( "sl",       DEST_VAR( my_string_list),
                      "My string list");

      ah.evalArguments( as2a.mArgC, as2a.mpArgV);
   } catch (const exception& e)
   {
      cerr << "*** ERROR: Caught exception \"" << e.what() << "\"!" << endl;
      return EXIT_FAILURE;
   } catch (...)
   {
      cerr << "*** ERROR: Exception with unknown type received!" << endl;
      return EXIT_FAILURE;
   } // end try

   return EXIT_SUCCESS;
} // main



static void callable_function( bool)
{
}


// =====  END OF test_argh_list_arg_vars_output.cpp  =====

