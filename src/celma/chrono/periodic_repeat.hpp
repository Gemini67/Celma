
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2023 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::chrono::PeriodicRepeat.


#pragma once


#include <ctime>


namespace celma::chrono {


/// If an action should be repeated periodically, but it's not possible to sleep
/// or use another kind of timeout to achieve the desired interval, use this
/// class to determine when the next execution is due.
class PeriodicRepeat
{
public:
   /// Constructor, initialises the members.
   /// @param[in]  period  Length of the period in seconds.
   /// @param[in]  adjust  Set this flag if the start time should be adjusted to
   ///                     a multiple of the period.
   /// @since  1.48.0, 04.05.2023
   explicit PeriodicRepeat( int period, bool adjust = false);

   /// Returns if the period is over and the corresponding action should be
   /// executed.
   /// @return  \c true if the period is over and the action should be executed.
   /// @since  1.48.0, 04.05.2023
   operator bool();

private:
   /// Length of the period.
   const int  mPeriod;
   /// Last time that a period end was signalled.
   time_t     mLastTime = std::time( nullptr);

}; // PeriodicRepeat


// inlined methods
// ===============


inline PeriodicRepeat::PeriodicRepeat( const int period, const bool adjust):
   mPeriod( period)
{
   if (adjust)
      mLastTime -= (mLastTime % mPeriod);
} // PeriodicRepeat::PeriodicRepeat


inline PeriodicRepeat::operator bool()
{
   auto const  now = std::time( nullptr);
   if ((now - mLastTime) >= mPeriod)
   {
      mLastTime = now;
      return true;
   } // end if
   return false;
} // PeriodicRepeat::operator bool


} // namespace celma::chrono


// =====  END OF periodic_repeat.hpp  =====

