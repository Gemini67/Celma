
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
/// See documentation of class celma::appl::@@@.


// module headerfile include
#include "celma/appl/multi_process.hpp"


#include <csignal>
#include <sys/wait.h>

#include <iostream>


namespace celma::appl {


namespace {


void child_temination_handler( int sig);


MultiProcess*  parentsObject = nullptr;


} // namespace


MultiProcess::MultiProcess():
   mLock(),
   mChildPids()
{

   struct sigaction  new_action;
   struct sigaction  old_action;


   // set up the structure to specify the new action
   new_action.sa_handler = child_temination_handler;
   ::sigemptyset( &new_action.sa_mask);
   new_action.sa_flags = SA_RESTART;

   ::sigaction( SIGCHLD, nullptr, &old_action);
   if (old_action.sa_handler != SIG_IGN)
      ::sigaction( SIGCHLD, &new_action, nullptr);


   parentsObject = this;

} // MultiProcess::MultiProcess



MultiProcess::~MultiProcess()
{

   parentsObject = nullptr;

} // MultiProcess::~MultiProcess



void MultiProcess::childTerminated()
{

   auto  result = ::waitpid( -1, nullptr, WNOHANG);


std::cout << "handle result = " << result << std::endl;
   while (result > 0)
   {
      const std::lock_guard  my_lock( mLock);

      for (auto child_iter = mChildPids.begin(); child_iter != mChildPids.end();
           ++child_iter)
      {
         if (*child_iter == result)
         {
std::cout << "child " << result << " is gone" << std::endl;
            mChildPids.erase( child_iter);
            break;
         } // end if
      } // end for

      result = ::waitpid( -1, nullptr, WNOHANG);
   } // end while

} // MultiProcess::childTerminated



namespace {



void child_temination_handler( int sig)
{

   if (parentsObject != nullptr)
      parentsObject->childTerminated();

} // child_temination_handler



} // namespace


} // namespace celma::appl


// =====  END OF multi_process.cpp  =====

