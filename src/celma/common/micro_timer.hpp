
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
/// See documentation of class celma::common::MicroTimer and
/// celma::common::AverageMicroTimer.


#ifndef CELMA_COMMON_MICRO_TIMER_HPP
#define CELMA_COMMON_MICRO_TIMER_HPP


#include <stdint.h>
#include <sys/time.h>


namespace celma { namespace common {


// Class MicroTimer
// ================


/// Simple class for measuring time periods with microsecond granularity.
/// @since  0.13.5, 28.02.2017
class MicroTimer
{
public:
   /// Calculates the time difference between the two timestamps (to - from).
   /// @param[in]  from  The first, earlier timestamp.
   /// @param[in]  to    The second, later timestamp.
   /// @return  The difference between these two timestamps in microseconds.
   /// @since  0.13.5, 28.02.2017
   static uint64_t diff( const timeval& from, const timeval& to);

   /// Calculates the time difference between the two timestamps (to - from).
   /// @param[out]  diffTime  The time difference between these two timestamps
   ///                        in microseconds, but only 32 bit (maximum
   ///                        4000 seconds).
   /// @param[in]   from      The first, earlier timestamp.
   /// @param[in]   to        The second, later timestamp.
   /// @since  0.13.5, 28.02.2017
   static void diff( unsigned int& diffTime, const timeval& from,
                     const timeval& to);

   /// Constructor, initialises internal variables.
   /// @since  0.13.5, 28.02.2017
   MicroTimer();

   /// Starts the timer.
   /// @since  0.13.5, 28.02.2017
   void start();

   /// Stops the timer.
   /// @since  0.13.5, 28.02.2017
   void stop();

   /// Returns the time measured between the start() and stop() calls in
   /// microseconds.
   /// @return  The time for which the timer was running in microseconds.
   /// @see diff().
   /// @since  0.13.5, 28.02.2017
   uint64_t timed() const;

   /// Returns the time measured between the start() and stop() calls in
   /// microseconds.<br>
   /// <b>Be aware</b> that the result is only correct for a time difference up
   /// to about 4000 secs (6.5 minutes). For a better precision use the the
   /// timed() function.<br>
   /// @param[out]  diffTime  Returns the time difference in 32 bit precision.
   /// @see diff().
   /// @since  0.13.5, 28.02.2017
   void timedShort( unsigned int& diffTime) const;

   /// Returns if the timer was started and is currently able to measure a time
   /// (measuring ends when stop() is called).
   /// @return  \c true if the timer was started and is measuring time.
   /// @since  05.09.2006
   /// @since  0.13.5, 28.02.2017
   bool started() const;

   /// Returns if the timer was stopped and can provide a measured time.
   /// @return  \c true if the timer was stopped and has measured a time.
   /// @since  0.13.5, 28.02.2017
   bool stopped() const;

   /// Returns the timestamp when the timer was started.
   /// @return  The timestamp when the timer was started.
   /// @since  0.13.5, 28.02.2017
   const struct timeval& startTime() const;

   /// Returns the timestamp when the timer was stopped.
   /// @return  The timestamp when the timer was stopped.
   /// @since  0.13.5, 28.02.2017
   const struct timeval& stopTime() const;

private:
   /// The time when the timer was started.
   struct timeval  mTvStart;
   /// The time when the timer was stopped.
   struct timeval  mTvEnd;

   /// Flag, set to true when the timer is currently started.
   bool  mStarted;
   /// Flag, set to true when the timer was started and stopped and has measured
   /// a time.
   bool  mStopped;

}; // MicroTimer


// inlined methods
// ===============


inline MicroTimer::MicroTimer()
{
   mStarted = false;
   mStopped = false;
} // MicroTimer::MicroTimer


inline uint64_t MicroTimer::diff( const timeval& from, const timeval& to)
{
   return static_cast< uint64_t>( to.tv_sec) * 1000000L + to.tv_usec -
           (static_cast< uint64_t>( from.tv_sec) * 1000000L + from.tv_usec);
} // MicroTimer::diff


inline void MicroTimer::diff( unsigned int& diffTime, const timeval& from,
                              const timeval& to)
{
   diffTime = static_cast< unsigned int>( static_cast< int64_t>( to.tv_sec) * 1000000L + to.tv_usec -
                                          (static_cast< int64_t>( from.tv_sec) * 1000000L + from.tv_usec));
} // MicroTimer::diff


inline void MicroTimer::start()
{
   mStarted = true;
   mStopped = false;
   ::gettimeofday( &mTvStart, nullptr);
} // MicroTimer::start


inline void MicroTimer::stop()
{
   ::gettimeofday( &mTvEnd, nullptr);
   mStarted = false;
   mStopped = true;
} // MicroTimer::stop


inline uint64_t MicroTimer::timed() const
{
   return diff( mTvStart, mTvEnd);
} // MicroTimer::timed


inline void MicroTimer::timedShort( unsigned int& diffTime) const
{
   diff( diffTime, mTvStart, mTvEnd);
} // MicroTimer::timedShort


inline bool MicroTimer::started() const
{
   return mStarted;
} // MicroTimer::started


inline bool MicroTimer::stopped() const
{
   return mStopped;
} // MicroTimer::stopped


inline const struct timeval& MicroTimer::startTime() const
{
   return mTvStart;
} // MicroTimer::startTime


inline const struct timeval& MicroTimer::stopTime() const
{
   return mTvEnd;
} // MicroTimer::stopTime


// Class AverageMicroTimer
// =======================


/// Class for measuring time periods with microsecond granularity for multiple
/// loop passes/events/messages etc. and then calculating the average time per
/// loop/event/message etc.
/// @since  0.13.5, 28.02.2017
class AverageMicroTimer
{
public:
   /// Constructor, initialises internal variables.
   /// @since  0.13.5, 28.02.2017
   AverageMicroTimer();

   /// Resets the internal counters.
   /// @since  0.13.5, 28.02.2017
   void reset();

   /// Starts a new timer.
   /// @since  0.13.5, 28.02.2017
   void start();

   /// Stops the current timer and adds the time measured to the time sum.
   /// @since  0.13.5, 28.02.2017
   void stop();

   /// Returns the time period measured by the last timer.
   /// @return  The time measured by the last timer call in microseconds.
   /// @since  0.13.5, 28.02.2017
   uint64_t timed() const;

   /// Returns the number of timer events measured.
   /// @since  0.13.5, 28.02.2017
   unsigned int numTimers() const;

   /// Returns the sum of all time periods measured.
   /// @since  0.13.5, 28.02.2017
   uint64_t sumTime() const;

   /// Returns the average time per event (timer) in microseconds.
   /// @since  0.13.5, 28.02.2017
   uint64_t averageTime() const;

private:
   /// The timer object to measure the time.
   MicroTimer    mTimer;
   /// Number of timer events measured.
   unsigned int  mEvents;
   /// Sum of all timer periods.
   uint64_t      mTimeSum;

}; // AverageMicroTimer


// inlined methods
// ===============


inline AverageMicroTimer::AverageMicroTimer()
{
   mEvents  = 0;
   mTimeSum = 0;
} // AverageMicroTimer::AverageMicroTimer


inline void AverageMicroTimer::reset()
{
   mEvents  = 0;
   mTimeSum = 0;
} // AverageMicroTimer::reset


inline void AverageMicroTimer::start()
{
   mTimer.start();
} // AverageMicroTimer::start


inline void AverageMicroTimer::stop()
{
   mTimer.stop();
   mEvents++;
   mTimeSum += mTimer.timed();
} // AverageMicroTimer::stop


inline uint64_t AverageMicroTimer::timed() const
{
   return mTimer.timed();
} // AverageMicroTimer::timed


inline unsigned int AverageMicroTimer::numTimers() const
{
   return mEvents;
} // AverageMicroTimer::numTimers


inline uint64_t AverageMicroTimer::sumTime() const
{
   return mTimeSum;
} // AverageMicroTimer::sumTime


inline uint64_t AverageMicroTimer::averageTime() const
{
   return mTimeSum / mEvents;
} // AverageMicroTimer::averageTime


// helper functions
// ================


/// Helper function to calculate the units per second.
/// @param[in]  number  Number of units handled in the measured time.
/// @param[in]  mt      The timer used to stop the time.
/// @return  The average number of units per second.
/// @since  0.13.5, 28.02.2017
inline double avgPerSecond( int64_t number, const MicroTimer& mt)
{

   // number * 1'000'000 [ms] / time [ms] = avg/s
   return (static_cast< double>( number) * 1000000.0) /
          static_cast< double>( mt.timed());
} // avgPerSecond


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_MICRO_TIMER_HPP


// =========================  END OF micro_timer.hpp  =========================

