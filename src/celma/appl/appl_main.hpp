
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::appl::@@@.


#ifndef CELMA_APPL_APPL_MAIN_HPP
#define CELMA_APPL_APPL_MAIN_HPP


#include <iostream>
#include <memory>
#include <stdexcept>
#include "celma/prog_args/handler.hpp"


namespace celma::appl {


class ApplBase
{
public:
   static bool restart();

   static int exitCode();

   ApplBase( int arg_handler_flags = 0, prog_args::IUsageText* txt1 = nullptr,
      prog_args::IUsageText* txt2 = nullptr) noexcept( false);

   /// 
   /// @param[in]  argc
   ///    .
   /// @param[in]  argv[]
   ///    .
   /// @since
   ///    x.y.z, 13.08.2020
   virtual void handleArguments( int argc, char* argv[]);

   virtual void init() { }

   virtual void mainLoop() = 0;

   virtual void cleanUp() { }

protected:
   static bool         mRestart;
   static int          mExitCode;
   prog_args::Handler  mArgHandler;

};


template< typename A> int application( int argc, char* argv[])
{

   do
   {
      std::unique_ptr< A>  appl_obj;

      try
      {
         appl_obj = std::make_unique< A>();
      } catch (const std::exception& ex)
      {
         std::cerr << "*** ERROR: Caught exception when creating object: "
            << ex.what() << std::endl;
         return EXIT_FAILURE;
      } catch (...)
      {
         std::cerr << "*** ERROR: Caught exception with unknown type when creating object!"
            << std::endl;
         return EXIT_FAILURE;
      } // end try

      try
      {
         appl_obj->handleArguments( argc, argv);
      } catch (const std::exception& ex)
      {
      } // end try

      try
      {
         appl_obj->init();
         appl_obj->mainLoop();
         appl_obj->cleanUp();
      } catch (const std::exception& ex)
      {
      } // end try
   } while (ApplBase::restart());

   return ApplBase::exitCode();
}


} // namespace celma::appl


#define MAIN( A) \
   int main( int argc, char* argv[]) \
   { \
      return celma::appl::application< A>( argc, argv); \
   }


#endif   // CELMA_APPL_APPL_MAIN_HPP


// =====  END OF appl_main.hpp  =====

