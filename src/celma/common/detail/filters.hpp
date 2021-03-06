
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template classes
/// - celma::common::detail::FilterBase<>
/// - celma::common::detail::SingleValue<>
/// - celma::common::detail::ValueRange<>
/// - celma::common::detail::MinimumValue<>
/// - celma::common::detail::MaximumValue<>


#pragma once


#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace celma::common::detail {


// Template FilterBase
// ===================


/// Base class for all filters.
/// Defines the methods that the specific filter classes must implement.<br>
/// Since all filters combined in one celma::common::Filter are filters for the
/// same type, we can define the base class as template too.
///
/// @tparam  T  The type of the values to create the filters for.
/// @since  1.31.0, 31.10.2017
template< typename T> class FilterBase
{
public:
   /// Empty, virtual destructor, required for base class.
   /// @since  1.31.0, 31.10.2017
   virtual ~FilterBase() = default;

   /// Interface method that must be implemented by derived class.
   /// Compares the given \a value with the defined filter value(s) and returns
   /// if they match.
   ///
   /// @param[in]  value  The value to compare against the filter values.
   /// @return
   ///    \c true if the given \a value matches the defined filter value(s).
   /// @since  1.31.0, 31.10.2017
   virtual bool matches( const T& value) const = 0;

   /// In derived classes, should return a string representation of the filter.
   ///
   /// @return
   ///    String with a representation of the filter that corresponds to the
   ///    format that the filter string parser supports.
   /// @since  1.31.0, 18.10.2019
   virtual std::string str() const = 0;

protected:
   /// Default constructor is fine.
   FilterBase() = default;

}; // FilterBase< T>


// Template SingleValue
// ====================


/// %Filter for a specific, single value.
///
/// @tparam  T  The type of the values to check.
/// @since  1.31.0, 31.10.2017
template< typename T> class SingleValue final : public FilterBase< T>
{
public:
   /// Constructor.
   ///
   /// @param[in]  value
   ///    The value to filter by.
   /// @param[in]  inverted
   ///    Set to invert the filter logic (matches if the test value differs from
   ///    this value).
   /// @since  1.31.0, 31.10.2017
   explicit SingleValue( const T& value, bool inverted = false):
      mValue( value),
      mInverted( inverted)
   {
   } // SingleValue< T>::SingleValue

   /// Empty, virtual destructor.
   /// @since  1.31.0, 31.10.2017
   ~SingleValue() override = default;

   /// Returns if the given value matches the filter value.
   ///
   /// @param[in]  value  The value to compare against the filter value.
   /// @return
   ///    \c true if the given value is equal to the filter value, or, when the
   ///    filter logic is inverted, when the value is different.
   /// @since  1.31.0, 31.10.2017
   bool matches( const T& value) const override
   {
      return mInverted ? (value != mValue) : (value == mValue);
   } // SingleValue< T>::matches

   /// Returns the string representation of the filter.
   ///
   /// @return  The string with the single value filter.
   /// @since  1.31.0, 18.10.2019
   std::string str() const override
   {
      std::ostringstream  oss;
      if (mInverted)
         oss << '!';
      oss << mValue;
      return oss.str();
   } // SingleValue< T>::str

private:
   /// The value to compare against.
   const T     mValue;
   /// \c true for inverted logic (different from filter value).
   const bool  mInverted;

}; // SingleValue< T>


// Template ValueRange
// ===================


/// %Filter for a range of values with start and end range values (inclusive).
///
/// @tparam  T  The type of the values to check.
/// @since  1.31.0, 31.10.2017
template< typename T> class ValueRange final : public FilterBase< T>
{
public:
   /// Constructor, checks and stores the values of the range.
   ///
   /// @param[in]  min_val
   ///    The lower bound of the range.
   /// @param[in]  max_val
   ///    The upper bound of the range.
   /// @param[in]  inverted
   ///    If set, the check will be succesful for values outside of the range.
   /// @throw  std::range_error if the parameters for the range are invalid.
   /// @since  1.31.0, 31.10.2017
   ValueRange( const T& min_val, const T& max_val, bool inverted = false):
      mMinValue( min_val),
      mMaxValue( max_val),
      mInverted( inverted)
   {
      if (mMaxValue <= mMinValue)
         throw std::range_error( "invalid range bounds");
   } // ValueRange< T>::ValueRange

   /// Empty, virtual destructor.
   /// @since  1.31.0, 31.10.2017
   ~ValueRange() override = default;

   /// Checks if the given value is inside or outside of the range.
   ///
   /// @param[in]  value  The value to check against the range.
   /// @return
   ///    \c true if the value is inside of the range, or if the flag
   ///    \c inverted was set in the constructor and the value is outside of the
   ///    range.
   /// @since  1.31.0, 31.10.2017
   bool matches( const T& value) const override
   {
      const bool  result = (mMinValue <= value) && (value <= mMaxValue);
      return mInverted ? !result : result;
   } // ValueRange< T>::matches

   /// Returns the string representation of the filter.
   /// 
   /// @return  A string with the range filter.
   /// @since  1.31.0, 18.10.2019
   std::string str() const override
   {
      std::ostringstream  oss;
      if (mInverted)
         oss << '!';
      oss << mMinValue << '-' << mMaxValue;
      return oss.str();
   } // ValueRange< T>::str

private:
   /// The lower bound of the range.
   const T     mMinValue;
   /// The upper bound of the range.
   const T     mMaxValue;
   /// If set, checks if the value is outside of the loop.
   const bool  mInverted;

}; // ValueRange< T>


// Template MinimumValue
// =====================


/// Minimum value filter.
///
/// @tparam  T  The type of the values to check.
/// @since  1.31.0, 01.11.2017
template< typename T> class MinimumValue final : public FilterBase< T>
{
public:
   /// Constructor, stores the minimum value to check against.
   ///
   /// @param[in]  min_val   The minimum value to check against.
   /// @since  1.31.0, 01.11.2017
   explicit MinimumValue( const T& min_val):
      mMinValue( min_val)
   {
   } // MinimumValue< T>::MinimumValue

   /// Empty, virtual destructor.
   /// @since  1.31.0, 01.11.2017
   ~MinimumValue() override = default;

   /// Checks if the given \a value is greater than or equal to the minimum
   /// value.
   ///
   /// @param[in]  value  The value to check.
   /// @return
   ///    \c true if the given value is greater than or equal to the defined
   ///    minimum value.
   /// @since  1.31.0, 01.11.2017
   bool matches( const T& value) const override
   {
      return value >= mMinValue;
   } // MinimumValue< T>::matches

   /// Returns the string representation of the filter.
   /// 
   /// @return  A string with the minimum value filter.
   /// @since  1.31.0, 18.10.2019
   std::string str() const override
   {
      std::ostringstream  oss;
      oss << '[' << mMinValue;
      return oss.str();
   } // MinimumValue< T>::str

private:
   /// The minimum value to compare against.
   const T  mMinValue;

}; // MinimumValue< T>


// Template MaximumValue
// =====================


/// Maximum value filter.
///
/// @tparam  T  The type of the values to check.
/// @since  1.31.0, 01.11.2017
template< typename T> class MaximumValue final : public FilterBase< T>
{
public:
   /// Constructor, stores the maximum value to check against.
   /// 
   /// @param[in]  max_val   The maximum value to check against.
   /// @since  1.31.0, 01.11.2017
   explicit MaximumValue( const T& max_val):
      mMaxValue( max_val)
   {
   } // MaximumValue< T>::MaximumValue

   /// Empty, virtual destructor.
   /// @since  1.31.0, 01.11.2017
   ~MaximumValue() override = default;

   /// Checks if the given \a value is less than the maximum value.
   ///
   /// @param[in]  value  The value to check.
   /// @return
   ///    \c true if the given value is less than the defined maximum value.
   /// @since  1.31.0, 01.11.2017
   bool matches( const T& value) const override
   {
      return value < mMaxValue;
   } // MaximumValue< T>::matches

   /// Returns the string representation of the filter.
   /// 
   /// @return  A string with the maximum value filter.
   /// @since  1.31.0, 18.10.2019
   std::string str() const override
   {
      std::ostringstream  oss;
      oss << ']' << mMaxValue;
      return oss.str();
   } // MaximumValue< T>::str

private:
   /// The maximum value to compare against.
   const T  mMaxValue;

}; // MaximumValue< T>


} // namespace celma::common::detail


// =====  END OF filters.hpp  =====

