
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::CurrentTotal.


#ifndef CELMA_COMMON_CURRENT_TOTAL_HPP
#define CELMA_COMMON_CURRENT_TOTAL_HPP


#include <cassert>
#include <cstring>


namespace celma { namespace common {


/// Helper class to compute counters for one or multiple intervals, plus the
/// total over all intervals.<br>
/// Operations like incrementing or value access always go for the current
/// value. Call add2Total() to add the current values to the total values.
///
/// @tparam  N  The number of counters to maintain.
/// @tparam  T  The type of the counters.
/// @since  1.13.0, 07.09.2018
template< int N, typename T = int> class CurrentTotal
{
public:
   /// Default constructor, sets all values to 0.
   ///
   /// @since  1.13.0, 07.09.2018
   CurrentTotal();

   /// Increments the current value of the given counter.
   ///
   /// @param[in]  idx
   ///    The index of the counter to increment, in the range 0..N-1.
   /// @param[in]  add
   ///    The value to increment the counter by.
   /// @since  1.13.0, 07.09.2018
   void inc( int idx, T add = 1);

   /// Returns (a const reference of) the current value of the counter with the
   /// given index.
   ///
   /// @param[in]  idx
   ///    The index of the counter to return the current value of, in the range
   ///    0..N-1.
   /// @return  The current value of the counter with the given index.
   /// @since  1.13.0, 07.09.2018
   const T& operator []( int idx) const;

   /// Returns (a non-const reference of) the current value of the counter with
   /// the given index. Can be used to e.g. increment the value.
   ///
   /// @param[in]  idx
   ///    The index of the counter to return the current value of, in the range
   ///    0..N-1.
   /// @return  The current value of the counter with the given index.
   /// @since  1.13.0, 07.09.2018
   T& operator []( int idx);

   /// Returns the current value of the counter with the given index.
   ///
   /// @param[in]  idx
   ///    The index of the counter to return the current value of, in the range
   ///    0..N-1.
   /// @return  The current value of the counter with the given index.
   /// @since  1.13.0, 07.09.2018
   T currentValue( int idx) const;

   /// Returns the total value of the counter with the given index.
   ///
   /// @param[in]  idx
   ///    The index of the counter to return the total of, in the range 0..N-1.
   /// @return  The total of the counter with the given index.
   /// @since  1.13.0, 07.09.2018
   T totalValue( int idx) const;

   /// Now this is the (only) function where the current values of one or all
   /// counters are added to the total.
   ///
   /// @param[in]  reset_current
   ///    Set this flag if the current value(s) should be reset after being
   ///    added to the total.
   /// @param[in]  idx
   ///    The index of the value to add to the total in the range 0..N-1, -1 to
   ///    handle all counters.
   /// @since  1.13.0, 07.09.2018
   void add2Total( bool reset_current = true, int idx = -1);

   /// Resets the current value of one or all counters.
   ///
   /// @param[in]  idx
   ///    The index of the counter to reset the current value of in the range
   ///    0..N-1, -1 to reset all current values.
   /// @since  1.13.0, 07.09.2018
   void resetCurrent( int idx = -1);

   /// Resets the total of one or all counters.
   ///
   /// @param[in]  idx
   ///    The index of the counter to reset the total of in the range 0..N-1,
   ///    -1 to reset all totals.
   /// @since  1.13.0, 07.09.2018
   void resetTotal( int idx = -1);

   /// Resets the current value and the total of one or all counters.
   ///
   /// @param[in]  idx
   ///    The index of the counter to reset the current value and the total of
   ///    in the range 0..N-1, -1 to reset all current values and totals.
   /// @since  1.13.0, 07.09.2018
   void reset( int idx = -1);

private:
   /// The array with the current values.
   T  mValues[ N];
   /// The array with the toal values.
   T  mTotals[ N];

}; // CurrentTotal< N, T>


// inlined methods
// ===============


template< int N, typename T> CurrentTotal< N, T>::CurrentTotal()
{
   reset();
} // CurrentTotal< N, T>::CurrentTotal


template< int N, typename T> void CurrentTotal< N, T>::inc( int idx, T add)
{
   assert( idx >= 0);
   assert( idx <  N);
   mValues[ idx] += add;
} // CurrentTotal< N, T>::inc


template< int N, typename T>
   const T& CurrentTotal< N, T>::operator []( int idx) const
{
   assert( idx >= 0);
   assert( idx <  N);
   return mValues[ idx];
} // CurrentTotal< N, T>::operator []


template< int N, typename T> T& CurrentTotal< N, T>::operator []( int idx)
{
   assert( idx >= 0);
   assert( idx <  N);
   return mValues[ idx];
} // CurrentTotal< N, T>::operator []


template< int N, typename T> T CurrentTotal< N, T>::currentValue( int idx) const
{
   assert( idx >= 0);
   assert( idx <  N);
   return mValues[ idx];
} // CurrentTotal< N, T>::currentValue


template< int N, typename T> T CurrentTotal< N, T>::totalValue( int idx) const
{
   assert( idx >= 0);
   assert( idx <  N);
   return mTotals[ idx];
} // CurrentTotal< N, T>::totalValue


template< int N, typename T>
   void CurrentTotal< N, T>::add2Total( bool reset_current, int idx)
{
   assert( idx >= -1);
   assert( idx <  N);
   for (int i = 0; i < N; ++i)
   {
      if ((idx == -1) || (i == idx))
      {
         mTotals[ i] += mValues[ i];
         if (reset_current)
            mValues[ i] = 0;
      } // end if
   } // end for
} // CurrentTotal< N, T>::add2Total


template< int N, typename T> void CurrentTotal< N, T>::resetCurrent( int idx)
{
   assert( idx >= -1);
   assert( idx <  N);
   if (idx == -1)
      ::memset( mValues, '\0', sizeof( T) * N);
   else
      mValues[ idx] = 0;
} // CurrentTotal< N, T>::resetCurrent


template< int N, typename T> void CurrentTotal< N, T>::resetTotal( int idx)
{
   assert( idx >= -1);
   assert( idx <  N);
   if (idx == -1)
      ::memset( mTotals, '\0', sizeof( T) * N);
   else
      mTotals[ idx] = 0;
} // CurrentTotal< N, T>::resetTotal


template< int N, typename T> void CurrentTotal< N, T>::reset( int idx)
{
   resetCurrent( idx);
   resetTotal( idx);
} // CurrentTotal< N, T>::reset


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_CURRENT_TOTAL_HPP


// =====  END OF current_total.hpp  =====

