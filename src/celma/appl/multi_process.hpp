
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
/// See documentation of class celma::app::@@@.


#pragma once


#include <sys/types.h>
#include <unistd.h>
#include <mutex>
#include <stdexcept>
#include <vector>

#include <iostream>


namespace celma::appl {


class MultiProcess
{
public:
   /// 
   /// @since  x.y.z, 17.03.2021
   MultiProcess();

   virtual ~MultiProcess();

   template< typename F> void forkChild( F fun) noexcept( false);

   void childTerminated();

   size_t numChildren() const;

protected:
   int  mReturnStatus = 0;

private:
   std::mutex           mLock;
   std::vector< pid_t>  mChildPids;

}; // MultiProcess


// inlined methods
// ===============


template< typename F> void MultiProcess::forkChild( F fun) noexcept( false)
{
   auto const  child_num = mChildPids.size();
   auto        result = ::fork();

   if (result < 0)
      throw std::runtime_error( "could not fork a new process");

   if (result == 0)
   {
      int  return_status = fun();
      ::_exit( return_status);
   } // end if

   const std::lock_guard  my_lock( mLock);
   mChildPids.push_back( result);

std::cout << "child " << result << " started" << std::endl;

} // MultiProcess::forkChild


inline size_t MultiProcess::numChildren() const
{
   return mChildPids.size();
} // MultiProcess::numChildren


} // namespace celma::appl


// =====  END OF multi_process.hpp  =====

