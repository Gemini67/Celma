
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017-2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::detail::Filter.


#ifndef CELMA_COMMON_DETAIL_FILTER_HPP
#define CELMA_COMMON_DETAIL_FILTER_HPP


#include <stdexcept>
#include <vector>
#include "celma/common/clear_container.hpp"
#include "celma/common/detail/filters.hpp"


namespace celma { namespace common { namespace detail {


/// Handles multiple filters on the same level, i.e. filters which must all
/// match a value.
///
/// @tparam  T  The type of the value to store the filters for.
/// @since  x.y.z, 31.10.2017
template< typename T> class Filter
{
public:
   /// Default constructor is fine.
   ///
   /// @since  x.y.z, 31.10.2017
   Filter() = default;

   /// Copying is not allowed.
   Filter( const Filter&) = delete;
   /// Moving is allowed.
   Filter( Filter&&) = default;

   /// Empty, virtual destrctor.
   ///
   /// @since  x.y.z, 31.10.2017
   ~Filter();

   /// Adds a single value filter.
   ///
   /// @param[in]  value
   ///    The value to compare against in the filter.
   /// @param[in]  inverted
   ///    Set when the logic should be inverted, i.e. check for values not equal
   ///    to \a value.
   /// @since  x.y.z, 31.10.2017
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
   /// @since  x.y.z, 31.10.2017
   void addRangeFilter( const T& min_value, const T& max_value,
      bool inverted = false);

   /// Adds a minimum value filter.
   ///
   /// @param[in]  min_val  The minimum value to compare against.
   /// @since  x.y.z, 02.11.2017
   void addMinimumFilter( const T& min_val);

   /// Adds a maximum value filter.
   ///
   /// @param[in]  max_val  The maximum value to compare against.
   /// @since  x.y.z, 02.11.2017
   void addMaximumFilter( const T& max_val);

   /// Checks if the given value matches all filters.
   ///
   /// @param[in]  value  The value to check against all filters.
   /// @return  \c true if the given value matched all filters.
   /// @throw  \c runtime_error if no filter is defined.
   /// @since  x.y.z, 31.10.2017
   bool matches( const T& value) const noexcept( false);

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
   Vector::clear( mFilters);
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


} // namespace detail
} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_DETAIL_FILTER_HPP


// =====  END OF filter.hpp  =====

