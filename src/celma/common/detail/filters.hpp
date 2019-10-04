
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template classes
/// - celma::common::detail::FilterBase
/// - celma::common::detail::SingleValue
/// - celma::common::detail::ValueRange
/// - celma::common::detail::ValueList
/// - celma::common::detail::MinimumValue
/// - celma::common::detail::MaximumValue


#ifndef CELMA_COMMON_DETAIL_FILTERS_HPP
#define CELMA_COMMON_DETAIL_FILTERS_HPP


#include <stdexcept>
#include <vector>


namespace celma { namespace common { namespace detail {


// Template FilterBase
// ===================


/// Base class for all filters.<br>
/// Defines the methods that the specific filter classes must implement.<br>
/// Since all filters combined in one celma::common::Filter are filters for the
/// same type, we can define the base class as template too.
/// @tparam  T  The type of the values to create the filters for.
/// @since  x.y.z, 31.10.2017
template< typename T> class FilterBase
{
public:
   enum class Result
   {
      matches,
      no_match,
      excluded
   };

   /// Empty, virtual destructor, required for base class.
   /// @since  x.y.z, 31.10.2017
   virtual ~FilterBase() = default;

   /// Interface method that must be implemented by derived class.<br>
   /// Compares the given \a value with the defined filter %value(s) and
   /// returns if they match.
   /// @param[in]  value  The value to compare against the filter values.
   /// @return  \c true if the given \a value matches the defined filter
   ///          %value(s).
   /// @since  x.y.z, 31.10.2017
   virtual Result matches( const T& value) const = 0;

}; // FilterBase< T>


// Template SingleValue
// ====================


/// Filter for a specific, single value.
/// @since  x.y.z, 31.10.2017
template< typename T> class SingleValue: public FilterBase< T>
{
public:
   using typename FilterBase< T>::Result;

   /// Constructor.
   /// @param[in]  value     The %value to filter by.
   /// @param[in]  inverted  Set to invert the filter logic (matches if the
   ///                       test %value differs from this %value).
   /// @since  x.y.z, 31.10.2017
   SingleValue( const T& value, bool inverted = false):
      mValue( value),
      mInverted( inverted)
   {
   } // SingleValue< T>::SingleValue

   /// Empty, virtual destructor.
   /// @since  x.y.z, 31.10.2017
   virtual ~SingleValue() = default;

   /// Returns if the given %value matches the filter %value.
   /// @param[in]  value  The %value to compare against the filter %value.
   /// @return
   /// - \c Result::matches for normal logic when the given %value is equal to
   ///   the filter %value.
   /// - \c Result::excluded for inverted logic when the given %value is equal
   ///   to the filter %value.
   /// - \c Result::no_match otherwise.
   /// @since  x.y.z, 31.10.2017
   virtual Result matches( const T& value) const override
   {
      if (mInverted)
         return (value == mValue) ? Result::excluded : Result::matches;
      return (mValue == value) ? Result::matches : Result::no_match;
   } // SingleValue< T>::matches

private:
   /// The value to filter by.
   const T     mValue;
   /// \c true for inverted logic (different from filter %value).
   const bool  mInverted;

}; // SingleValue< T>


// Template ValueRange
// ===================


/// Filter for a range of values with start and end range values (inclusive).
/// @since  x.y.z, 31.10.2017
template< typename T> class ValueRange: public FilterBase< T>
{
public:
   using typename FilterBase< T>::Result;

   /// 
   /// @param[in]  min_val   .
   /// @param[in]  max_val   .
   /// @param[in]  inverted  .
   /// @since  x.y.z, 31.10.2017
   ValueRange( const T& min_val, const T& max_val, bool inverted = false):
      mMinValue( min_val),
      mMaxValue( max_val),
      mInverted( inverted)
   {
      if (mMaxValue <= mMinValue)
         throw std::range_error( "invalid range bounds");
   } // ValueRange< T>::ValueRange

   virtual ~ValueRange() = default;

   virtual Result matches( const T& value) const override
   {
      if (mInverted)
         return ((mMinValue <= value) && (value <= mMaxValue))
            ? Result::excluded : Result::matches;
      return ((mMinValue <= value) && (value <= mMaxValue))
         ? Result::matches : Result::no_match;
   } // ValueRange< T>::matches

private:
   const T     mMinValue;
   const T     mMaxValue;
   const bool  mInverted;

}; // ValueRange< T>


// Template ValueList
// ==================


template< typename T> class ValueList: public FilterBase< T>
{
public:
   using typename FilterBase< T>::Result;
   using value_cont_t = std::vector< T>;

   /// 
   /// @param[in]  values    .
   /// @param[in]  inverted  .
   /// @since  x.y.z, 01.11.2017
   ValueList( const value_cont_t& values, bool inverted = false):
      mValues( values),
      mInverted( inverted)
   {
      if (values.empty())
         throw std::runtime_error( "empty value list is not allowed");
   } // ValueList< T>::ValueList

   virtual ~ValueList() = default;

   virtual Result matches( const T& value) const override
   {
      for (auto const& list_value : mValues)
      {
         if (list_value == value)
            return mInverted ? Result::excluded : Result::matches;
      } // end for
      return mInverted ? Result::matches : Result::no_match;
   } // ValueList< T>::matches

private:
   const value_cont_t  mValues;
   const bool          mInverted;

}; // ValueList< T>


// Template MinimumValue
// =====================


template< typename T> class MinimumValue: public FilterBase< T>
{
public:
   using typename FilterBase< T>::Result;

   /// 
   /// @param[in]  min_val   .
   /// @since  x.y.z, 01.11.2017
   MinimumValue( const T& min_val):
      mMinValue( min_val)
   {
   } // MinimumValue< T>::MinimumValue

   virtual ~MinimumValue() = default;

   virtual Result matches( const T& value) const override
   {
      return (value >= mMinValue) ? Result::matches : Result::no_match;
   } // MinimumValue< T>::matches

private:
   const T  mMinValue;

}; // MinimumValue< T>


// Template MaximumValue
// =====================


template< typename T> class MaximumValue: public FilterBase< T>
{
public:
   using typename FilterBase< T>::Result;

   /// 
   /// @param[in]  max_val   .
   /// @since  x.y.z, 01.11.2017
   MaximumValue( const T& max_val):
      mMaxValue( max_val)
   {
   } // MaximumValue< T>::MaximumValue

   virtual ~MaximumValue() = default;

   virtual Result matches( const T& value) const override
   {
      return (value < mMaxValue) ? Result::matches : Result::no_match;
   } // MaximumValue< T>::matches

private:
   const T  mMaxValue;

}; // MaximumValue< T>


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_FILTERS_HPP


// =====  END OF filters.hpp  =====

