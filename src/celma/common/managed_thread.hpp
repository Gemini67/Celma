
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2024 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::ManagedThread.


#pragma once


#include <atomic>
#include <thread>
#include <utility>


namespace celma::common {


/// Small helper class that provides the information if the thread is still
/// active or if it finished its work.<br>
/// When this object is destroyed, it calls \c join(), so the calling
/// application does not need to do that.
/// @since  012, 19.01.2017
class ManagedThread final: public std::thread
{
public:
   /// Constructor, creates the thread which immediately starts its work.
   /// @tparam  Function  The type of the function to be called by the thread.
   /// @tparam  Args...   The types of the parameters to be passed to the
   ///                    function.
   /// @param[in]  f     The function to execute in the thread.
   /// @param[in]  args  The parameters for the thread function.
   /// @since  012, 19.01.2017
   template< class Function, class... Args>
      explicit ManagedThread( Function&& f, Args&&... args);

   // copy-construction is not allowed
   ManagedThread( const ManagedThread&) = delete;

   // move-constructor is also not allowed
   ManagedThread( ManagedThread&&) = delete;

   /// Destructor, calls std::thread::join(), i.e. would block if the thread is
   /// still running.
   /// @since  012, 19.01.2017
   ~ManagedThread();

   /// Returns if the thread function is still active.
   /// @return  \c true if the thread function is still active.
   /// @since  012, 19.01.2017
   [[nodiscard]] bool isActive() const noexcept;

   // copy-assignment is not allowed
   ManagedThread& operator =( const ManagedThread&) = delete;

   // move-assignment is also not allowed
   ManagedThread& operator =( ManagedThread&&) = delete;

private:
   /// Flag, set by the thread before the thread function is executed, cleared
   /// when the thread function returnes, i.e. finished its work.
   std::atomic< bool>  mActive{ false};

}; // ManagedThread


// inlined methods
// ===============


template< class Function, class... Args>
   ManagedThread::ManagedThread( Function&& f, Args&&... args):
      std::thread( [ func = std::forward< Function>( f), flag = &mActive]
                   ( Args&&... lbd_args)
                     noexcept( noexcept( f( std::forward< Args>( lbd_args)...)))
                   {
                      flag->store( true, std::memory_order_release);
                      func( std::forward< Args>( lbd_args)...);
                      flag->store( false, std::memory_order_release);
                   },
                   std::forward< Args>( args)...)
{
} // ManagedThread::ManagedThread


inline ManagedThread::~ManagedThread()
{
   if (joinable())
      join();
} // ManagedThread::~ManagedThread


inline bool ManagedThread::isActive() const noexcept
{
   return mActive.load( std::memory_order_acquire);
} // ManagedThread::isActive


} // namespace celma::common


// =====  END OF managed_thread.hpp  =====

