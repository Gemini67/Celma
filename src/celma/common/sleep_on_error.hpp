
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::@@@.


#ifndef CELMA_COMMON_SLEEP_ON_ERROR_HPP
#define CELMA_COMMON_SLEEP_ON_ERROR_HPP


#include <sched.h>
#include <unistd.h>
#include <functional>
#include "celma/common/adjust.hpp"


namespace celma { namespace common {


/// If a process should slow down if an error occurs repeatedly, e.g. reading
/// from a socket fails, use this class to handle the sleep time.<br>
/// Simply create an object of this class and call sleep() every time after the
/// call that should trigger the sleep procedure, with the result of the call
/// (success/failure) as parameter.<br>
/// The first time the error occurs, \c sched_yield() is called and the sleep
/// time is set to the specified minimum.<br>
/// Afterwards, if the error occurs, the process is sent sleeping for the
/// current time in microseconds, then the specified function is called to
/// determine the next sleep time. Finally, it is ensured that the sleep time
/// does not exceed the specified maximum.<br>
/// Every time that sleep() is called and no error occurred, the (next) sleep
/// time is set to 0.
/// @tparam  T  The type of the sleep time to manage.
/// @since  0.13.4, 24.02.2017
template< typename T = int> class SleepOnError
{
public:
   /// Constructor, stores the parameters for sleeping.
   /// @param[in]  min_sleep  Minimum time (in microseconds) to sleep.
   /// @param[in]  max_sleep  Maximum time to sleep.
   /// @param[in]  f          The function to call to increase the sleep time.
   /// @since  0.13.4, 24.02.2017
   SleepOnError( T min_sleep, T max_sleep, std::function< void(T&)> f);

   /// If \a failure is set, sleep for some time as described avove, otherwise
   /// reset the (next) sleep time to 0.
   /// @param[in]  failure  Flag if an error occurred.
   /// @since  0.13.4, 24.02.2017
   void sleep( bool failure);

   /// For inspection: Return the next sleep time (in microseconds).
   /// @return  The sleep time that will be used in the call of sleep( false).
   /// @since  0.13.4, 24.02.2017
   T nextSleepTime() const;

private:
   /// Minimum time to sleep if an error occurred.
   const T                   mMinSleep;
   /// Maxiumum time to sleep if the error occurs repeatedly.
   const T                   mMaxSleep;
   /// The next sleep time.
   T                         mCurrentSleep;
   /// The function to call to increase the sleep time for the next call.
   std::function< void(T&)>  mIncFunc;

}; // SleepOnError< T>


// inlined methods
// ===============


template< typename T>
   SleepOnError< T>::SleepOnError( T min_sleep, T max_sleep,
                                   std::function< void(T&)> f):
      mMinSleep( min_sleep),
      mMaxSleep( max_sleep),
      mCurrentSleep ( 0),
      mIncFunc( f)
{
} // SleepOnError< T>::SleepOnError


template< typename T> void SleepOnError< T>::sleep( bool failure)
{

   if (failure)
   {
      if (mCurrentSleep == 0)
      {
         ::sched_yield();
         mCurrentSleep = mMinSleep;
      } else
      {
         ::usleep( mCurrentSleep);
         mIncFunc( mCurrentSleep);
         adjustMax( mCurrentSleep, mMaxSleep);
      } // end if
   } else
   {
      mCurrentSleep = 0;
   } // end if

} // SleepOnError< T>::sleep


template< typename T> T SleepOnError< T>::nextSleepTime() const
{
   return mCurrentSleep;
} // SleepOnError< T>::nextSleepTime


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_SLEEP_ON_ERROR_HPP


// ========================  END OF sleep_on_error.hpp  ========================

