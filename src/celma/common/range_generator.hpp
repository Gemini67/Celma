
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


/// @file
/// See documentation of template celma::common::RangeGenerator.


#ifndef CELMA_COMMON_RANGE_GENERATOR_HPP
#define CELMA_COMMON_RANGE_GENERATOR_HPP


#include <set>
#include <stdexcept>
#include "celma/common/pre_postfix.hpp"


namespace celma { namespace common {


/// Generates all numbers in a range.<br>
/// The class can also be used to handle 'ranges' with only a single value.<br>
/// The object can be used just once to create the values in the range. If the
/// same values of the same range are needed multiple times, multiple generator
/// objects must be created.
/// @tparam  T             The data type of the values to be produced by the
///                        generator.
/// @tparam  iterEndValue  Iterator end value, must be a value that is outside
///                        of the range.
/// @since  0.2, 07.04.2016
template< typename T, T iterEndValue = -1> class RangeGenerator
{
public:
   /// Constructor.
   /// @param[in]  single_value  Single value to handle.
   /// @since  0.2, 07.04.2016
   RangeGenerator( T single_value):
      mStartValue( single_value),
      mEndValue(),
      mIncrement(),
      mSingleValue( true)
   {
      if (mStartValue == iterEndValue)
         throw std::logic_error( "single value may not be iterator-end");
   } // end RangeGenerator< T, iterEndValue>::RangeGenerator

   /// Constructor for a range.
   /// @param[in]  start_value  The start value of the range.
   /// @param[in]  end_value    The last value in the range.
   /// @param[in]  increment    Increment to use.
   /// @since  0.2, 07.04.2016
   RangeGenerator( T start_value, T end_value, T increment = 1):
      mStartValue( start_value),
      mEndValue( end_value),
      mIncrement( increment),
      mSingleValue( false)
   {
      if (mEndValue < mStartValue)
         throw std::logic_error( "range-end must be greater then range start");
      if ((mStartValue <= iterEndValue) && (iterEndValue <= mEndValue))
         throw std::logic_error( "iterator-end must be outside the range");
      if (mIncrement < 0)
         throw std::logic_error( "increment value must be positive");
   } // end RangeGenerator< T, iterEndValue>::RangeGenerator

   /// Sets a value of the range that should excluded. The value must be
   /// within the range \<startvalue\> \< excl \< \<endvalue\>.
   /// @param[in]  value  The value to exclude from the range.
   /// @throw  Exception when called for a single value or when the value is not
   ///         with the range.
   /// @since  0.2, 07.04.2016
   void excludeValue( T value)
   {
      if (mSingleValue)
         throw std::logic_error( "exclude values cannot be set on single-value ranges");
      if ((value <= mStartValue) || (mEndValue <= value))
         throw std::logic_error( "exclude values outside of range");
      mExludeValues.insert( value);
   } // end RangeGenerator< T, iterEndValue>::excludeValue

   /// Allows to add multiple exclude values.
   /// @tparam  iterator  The iterator type to use.
   /// @param[in]  it_begin  Iterator pointing to the first value to add.
   /// @param[in]  it_end    End iterator.
   /// @since  0.2, 07.04.2016
   template< typename iterator>
      void excludeValues( iterator it_begin, const iterator& it_end)
   {
      for (; it_begin != it_end; ++it_begin)
      {
         excludeValue( *it_begin);
      } // end for
   } // end RangeGenerator< T, iterEndValue>::excludeValues

   /// Returns the end-of-iteration value, *not* the last value in the range.
   /// @return  The end-of-iteration value, used to check if the end of the
   ///          range is reached.
   /// @since  0.2, 07.04.2016
   T end() const
   {
      return iterEndValue;
   } // end RangeGenerator< T, iterEndValue>::end

   /// Prefix increment.
   /// @return  This object.
   /// @throw  Exception when the end of the range was already reched.
   /// @since  0.2, 07.04.2016
   RangeGenerator& operator ++( std::prefix)
   {
      if (mStartValue == iterEndValue)
         throw std::runtime_error( "attempt to increment after iterator-end");

      if (mSingleValue)
      {
         mStartValue = iterEndValue;
      } else
      {
         for (;;)
         {
            if (mStartValue > mEndValue - mIncrement)
            {
               mStartValue = iterEndValue;
               break;   // for
            } // end if

            mStartValue += mIncrement;

            if (mExludeValues.empty() ||
                (mExludeValues.find( mStartValue) == mExludeValues.end()))
               break;   // for
         } // end for
      } // end if
      return *this;
   } // end RangeGenerator< T, iterEndValue>::operator ++

   /// Postfix increment.
   /// @return  This object.
   /// @since  0.2, 07.04.2016
   RangeGenerator operator ++( std::postfix)
   {
      const RangeGenerator  copy( *this);
      ++(*this);
      return copy;
   } // end RangeGenerator< T, iterEndValue>::operator ++

   /// Returns the current value.
   /// @return  The current value, \c iterEndValue if the end of the range was
   ///          reached.
   /// @since  0.2, 07.04.2016
   operator T() const
   {
      return mStartValue;
   } // end RangeGenerator< T, iterEndValue>::operator T

private:
   /// The start and current value.
   T             mStartValue;
   /// For a range, the end value of the range.
   const T       mEndValue;
   /// The increment to use.
   const T       mIncrement;
   /// Set when the range is actually a single value.
   const bool    mSingleValue;
   /// Set of values to exclude from the generated range of values.
   std::set< T>  mExludeValues;

}; // RangeGenerator< T, iterEndValue>


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_RANGE_GENERATOR_HPP


// =======================  END OF range_generator.hpp  =======================

