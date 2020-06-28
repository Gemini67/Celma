
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
/// See documentation of class celma::common::detail::Filter.


#ifndef CELMA_COMMON_DETAIL_FILTER_HPP
#define CELMA_COMMON_DETAIL_FILTER_HPP


#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "celma/common/detail/filters.hpp"
#include "celma/container/clear_container.hpp"


namespace celma::common::detail {


/// Handles multiple filters on the same level.
/// A value must match all these filters, i.e. like an "and" condition.
///
/// @tparam  T  The type of the value to store the filters for.
/// @since  1.31.0, 31.10.2017
template< typename T> class Filter
{
public:
   /// Default constructor is fine.
   ///
   /// @since  1.31.0, 31.10.2017
   Filter() = default;

   /// Copying is not allowed.
   Filter( const Filter&) = delete;
   /// Moving is allowed.
   Filter( Filter&&) = default;

   /// Destructor.
   ///
   /// @since  1.31.0, 31.10.2017
   ~Filter();

   /// Adds a single value filter.
   ///
   /// @param[in]  value
   ///    The value to compare against in the filter.
   /// @param[in]  inverted
   ///    Set when the logic should be inverted, i.e. check for values not equal
   ///    to \a value.
   /// @since  1.31.0, 31.10.2017
   void addSingleValueFilter( const T& value, bool inverted = false);

   /// Adds a range filter.
   ///
   /// @param[in]  min_value
   ///    The lower bound of the range.
   /// @param[in]  max_value
   ///    The upper bound of the range.
   /// @param[in]  inverted
   ///    Set when the logic should be inverted, i.e. check for values outside
   ///    of the range.
   /// @since  1.31.0, 31.10.2017
   void addRangeFilter( const T& min_value, const T& max_value,
      bool inverted = false);

   /// Adds a minimum value filter.
   ///
   /// @param[in]  min_val  The minimum value to compare against.
   /// @since  1.31.0, 02.11.2017
   void addMinimumFilter( const T& min_val);

   /// Adds a maximum value filter.
   ///
   /// @param[in]  max_val  The maximum value to compare against.
   /// @since  1.31.0, 02.11.2017
   void addMaximumFilter( const T& max_val);

   /// Checks if the given value matches all filters.
   ///
   /// @param[in]  value  The value to check against all filters.
   /// @return  \c true if the given value matched all filters.
   /// @throw  \c runtime_error if no filter is defined.
   /// @since  1.31.0, 31.10.2017
   bool matches( const T& value) const noexcept( false);

   /// Returns the string representation of the filter.
   /// 
   /// @return  A string with the list of filters.
   /// @since  1.31.0, 18.10.2019
   std::string str() const;

private:
   /// The type used to store the filter objects: Base class pointer.
   using filter_base_t = FilterBase< T>;
   /// The type of the container in which the filter objects are stored.
   using filter_cont_t = std::vector< filter_base_t*>;

   /// The filters.
   filter_cont_t  mFilters;

}; // Filter< T>


// inlined methods
// ===============


template< typename T> Filter< T>::~Filter()
{
   container::Vector::clear( mFilters);
} // Filter< T>::~Filter


template< typename T>
   void Filter< T>::addSingleValueFilter( const T& value, bool inverted)
{
   mFilters.push_back( new SingleValue< T>( value, inverted));
} // Filter< T>::addSingleValueFilter


template< typename T>
   void Filter< T>::addRangeFilter( const T& min_value, const T& max_value,
                                    bool inverted)
{
   mFilters.push_back( new ValueRange< T>( min_value, max_value, inverted));
} // Filter< T>::addRangeFilter


template< typename T> void Filter< T>::addMinimumFilter( const T& min_val)
{
   mFilters.push_back( new MinimumValue< T>( min_val));
} // Filter< T>::addMinimumFilter


template< typename T> void Filter< T>::addMaximumFilter( const T& max_val)
{
   mFilters.push_back( new MaximumValue< T>( max_val));
} // Filter< T>::addMaximumFilter


template< typename T> bool Filter< T>::matches( const T& value) const
{
   if (mFilters.empty())
      throw std::runtime_error( "no filter specified");

   for (auto const& next_filter : mFilters)
   {
      if (!next_filter->matches( value))
         return false;
   } // end for
   return true;
} // Filter< T>::matches


template< typename T> std::string Filter< T>::str() const
{
   std::ostringstream  oss;
   for (auto const& filter : mFilters)
   {
      if (!oss.str().empty())
         oss << '+';
      oss << filter->str();
   } // end for
   return oss.str();
} // Filter< T>::str


} // namespace celma::common::detail


#endif   // CELMA_COMMON_DETAIL_FILTER_HPP


// =====  END OF filter.hpp  =====

