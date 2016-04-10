
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


#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include "celma/common/arg_string_2_array.hpp"
#include "celma/prog_args.hpp"


using namespace std;
using namespace celma;


static void callable_function();


/// 
/// @param[in]  argc    .
/// @param[in]  argv[]  .
/// @return  .
/// @since  0.2, 10.04.2016
int main( int /* argc */, char* argv[])
{

   {
      prog_args::Handler       ah( 0);
      const string             args( "--list-arg-vars");
      common::ArgString2Array  as2a( args, argv[ 0]);

      try
      {
         ah.evalArguments( as2a.mArgc, as2a.mpArgv);
         cerr << "*** ERROR: Expected exception for 'unknown argument!" << endl;
         return EXIT_FAILURE;
      } catch (const invalid_argument& e)
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

   {
      prog_args::Handler       ah( prog_args::Handler::hfListArgVar);
      const string             args( "--list-arg-vars --integer 42");
      common::ArgString2Array  as2a( args, argv[ 0]);
      bool                     my_flag = false;
      int                      my_int;
      string                   my_string;

      try
      {
         ah.addArgument( "f",        DEST_VAR( my_flag),    "My flag.");
         ah.addArgument( "integer",  DEST_VAR( my_int),     "My integer.")->setIsMandatory();
         ah.addArgument( "s,string", DEST_VAR( my_string),  "My string.");

         ah.evalArguments( as2a.mArgc, as2a.mpArgv);
      } catch (const exception& e)
      {
         cerr << "*** ERROR: Caught exception \"" << e.what() << "\"!" << endl;
         return EXIT_FAILURE;
      } catch (...)
      {
         cerr << "*** ERROR: Exception with unknown type received!" << endl;
         return EXIT_FAILURE;
      } // end try
   } // end scope

   cout << string( 80, '-') << endl << endl;

   {
      prog_args::Handler  ah( 0);
      ah.addArgumentListArgVars( "V");

      const string                  args( "-V --integer 42 --sl schubidu -V");
      common::ArgString2Array       as2a( args, argv[ 0]);
      bool                          my_flag = false;
      int                           my_int;
      long                          my_long;
      uint64_t                      my_ulong;
      string                        my_string;
      common::CheckAssign< string>  my_ca_string;
      vector< string>               my_string_list;

      try
      {
         ah.addArgument( "f",        DEST_VAR( my_flag),    "My flag.");
         ah.addArgument( "integer",  DEST_VAR( my_int),     "My integer.")->setIsMandatory();
         ah.addArgument( "s,string", DEST_VAR( my_string),  "My string.")->setPrintDefault( false);
         ah.addArgument( "long",     DEST_VAR( my_long),    "My hidden long integer.")->setIsHidden();
         ah.addArgument( "ulong",    DEST_VAR( my_ulong),   "My unsigned long integer.")
                       ->setValueMode( prog_args::detail::TypedArgBase::vmOptional);
         ah.addArgument( "call",     DEST_FUNCTION( callable_function),
                         "My function.");
         ah.addArgument( "cas",      DEST_VAR( my_ca_string), "My CheckAssign string");
         ah.addArgument( "sl",       DEST_VAR( my_string_list), "My string list");

         ah.evalArguments( as2a.mArgc, as2a.mpArgv);
      } catch (const exception& e)
      {
         cerr << "*** ERROR: Caught exception \"" << e.what() << "\"!" << endl;
         return EXIT_FAILURE;
      } catch (...)
      {
         cerr << "*** ERROR: Exception with unknown type received!" << endl;
         return EXIT_FAILURE;
      } // end try
   } // end scope

   return EXIT_SUCCESS;
} // end main



static void callable_function()
{
}


// =========================  END OF test_argh_list_arg_vars_output.cpp  =========================
