
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of template class celma::common::ValueFilter<>.


#ifndef CELMA_COMMON_VALUE_FILTER_HPP
#define CELMA_COMMON_VALUE_FILTER_HPP


#include <vector>
#include "celma/common/detail/filter.hpp"


namespace celma { namespace common {


/// Stores multiple filters and checks values against those filters.<br>
/// There are two way to add a filter:
/// - Using add... methods: The filter is added as top-level filters. When
///   checking with values, at least one of the top-level filters must match the
///   value, i.e. an or combination.
/// - Using append... methods: The filter is appended to the last top-level
///   filter, in other words at least one filter must have been added before
///   using add...(). When checking with values, all filters of the same group
///   must match a value, i.e. the first filter that was added using add... plus
///   all filters directly afterwards added using append...(). This corresponds
///   to an and combination.
///
/// Any kind and numbers of filters may be combined, however you have to make
/// sure to not define combinations that are always or never true:
/// - two single value filters on the same level: always \c false
/// - two inverted single value filters at top level: always \c true.
///
/// @tparam  T  The type of the values to store the filters for.
/// @since  x.y.z, 07.10.2019
template< typename T> class ValueFilter
{
public:
   /// Default constructor is fine.
   ValueFilter() = default;
   /// Copying is not allowed.
   ValueFilter( const ValueFilter&) = delete;
   /// Moving however is possible.
   ValueFilter( ValueFilter&&) = default;
   /// Default destructor is fine.
   ~ValueFilter() = default;

   /// Adds a single value filter as top-level filter.
   ///
   /// @param[in]  value
   ///    The value to check for.
   /// @param[in]  inverted
   ///    If set, the filter matches all values not equal to \a value.
   /// @since  x.y.z, 07.10.2019
   void addSingleValueFilter( const T& value, bool inverted = false);

   /// Appends a single value filter to the last top-level filter.
   ///
   /// @param[in]  value
   ///    The value to check for.
   /// @param[in]  inverted
   ///    If set, the filter matches all values not equal to \a value.
   /// @throw  \c runtime_error if no top-level filter was added before.
   /// @since  x.y.z, 07.10.2019
   void appendSingleValueFilter( const T& value, bool inverted = false)
      noexcept( false);

   /// Adds a range filter as top-level filter.
   ///
   /// @param[in]  min_value
   ///    The lower bound of the range to check for.
   /// @param[in]  max_value
   ///    The upper bound of the range to check for.
   /// @param[in]  inverted
   ///    If set, the filter matches all values not within the range.
   /// @since  x.y.z, 07.10.2019
   void addRangeFilter( const T& min_value, const T& max_value,
      bool inverted = false);

   /// Appends a range filter to the last top-level filter.
   ///
   /// @param[in]  min_value
   ///    The lower bound of the range to check for.
   /// @param[in]  max_value
   ///    The upper bound of the range to check for.
   /// @param[in]  inverted
   ///    If set, the filter matches all values not within the range.
   /// @throw  \c runtime_error if no top-level filter was added before.
   /// @since  x.y.z, 07.10.2019
   void appendRangeFilter( const T& min_value, const T& max_value,
      bool inverted = false) noexcept( false);

   /// Adds a minimum filter as top-level filter.
   ///
   /// @param[in]  min_val
   ///    The minimum value to check against, i.e. a value x must be greater
   ///    than or equal to \a min_val.
   /// @since  x.y.z, 07.10.2019
   void addMinimumFilter( const T& min_val);

   /// Appends a minimum filter to the last top-level filter.
   ///
   /// @param[in]  min_val
   ///    The minimum value to check against, i.e. a value x must be greater
   ///    than or equal to \a min_val.
   /// @throw  \c runtime_error if no top-level filter was added before.
   /// @since  x.y.z, 07.10.2019
   void appendMinimumFilter( const T& min_val) noexcept( false);

   /// Adds a maximum filter as top-level filter.
   ///
   /// @param[in]  max_val
   ///    The maximum value to check against, i.e. a value x must be less than
   ///    \a max_val.
   /// @since  x.y.z, 07.10.2019
   void addMaximumFilter( const T& max_val);

   /// Appends a maximum filter to the last top-level filter.
   ///
   /// @param[in]  max_val
   ///    The maximum value to check against, i.e. a value x must be less than
   ///    \a max_val.
   /// @throw  \c runtime_error if no top-level filter was added before.
   /// @since  x.y.z, 07.10.2019
   void appendMaximumFilter( const T& max_val) noexcept( false);

   /// Compares the given value against the defined filters:
   /// - From the top-level filters, at least one must match (or condition).
   /// - If a top-level filter contains multiple filters, each of them must
   ///   match (and condition).
   ///
   /// @param[in]  value  The value to check against the filters.
   /// @return  \c true if the value matched the filters as described above.
   /// @throw  \c runtime_error if filters are defined.
   /// @since  x.y.z, 07.10.2019
   bool matches( const T& value) const noexcept( false);

private:
   /// The type of the top-level filter container.
   using filter_group = detail::Filter< T>;

   /// The (top level) filters.
   std::vector< filter_group>  mFilters;

}; // ValueFilter< T>


// inlined methods
// ===============


template< typename T>
   void ValueFilter< T>::addSingleValueFilter( const T& value, bool inverted)
{
   detail::Filter< T>  f;
   f.addSingleValueFilter( value, inverted);
   mFilters.emplace_back( std::move( f));
} // ValueFilter< T>::addSingleValueFilter


template< typename T>
   void ValueFilter< T>::appendSingleValueFilter( const T& value, bool inverted)
{
   if (mFilters.empty())
      throw std::runtime_error( "cannot append filter to empty list");

   mFilters.back().addSingleValueFilter( value, inverted);
} // ValueFilter< T>::appendSingleValueFilter


template< typename T>
   void ValueFilter< T>::addRangeFilter( const T& min_value, const T& max_value,
      bool inverted)
{
   detail::Filter< T>  f;
   f.addRangeFilter( min_value, max_value, inverted);
   mFilters.emplace_back( std::move( f));
} // ValueFilter< T>::addRangeFilter


template< typename T>
   void ValueFilter< T>::appendRangeFilter( const T& min_value,
      const T& max_value, bool inverted)
{
   if (mFilters.empty())
      throw std::runtime_error( "cannot append filter to empty list");

   mFilters.back().addRangeFilter( min_value, max_value, inverted);
} // ValueFilter< T>::appendRangeFilter


template< typename T> void ValueFilter< T>::addMinimumFilter( const T& min_val)
{
   detail::Filter< T>  f;
   f.addMinimumFilter( min_val);
   mFilters.emplace_back( std::move( f));
} // ValueFilter< T>::addMinimumFilter


template< typename T>
   void ValueFilter< T>::appendMinimumFilter( const T& min_val)
{
   if (mFilters.empty())
      throw std::runtime_error( "cannot append filter to empty list");

   mFilters.back().addMinimumFilter( min_val);
} // ValueFilter< T>::appendMinimumFilter


template< typename T> void ValueFilter< T>::addMaximumFilter( const T& max_val)
{
   detail::Filter< T>  f;
   f.addMaximumFilter( max_val);
   mFilters.emplace_back( std::move( f));
} // ValueFilter< T>::addMaximumFilter


template< typename T>
   void ValueFilter< T>::appendMaximumFilter( const T& max_val)
{
   if (mFilters.empty())
      throw std::runtime_error( "cannot append filter to empty list");

   mFilters.back().addMaximumFilter( max_val);
} // ValueFilter< T>::appendMaximumFilter


template< typename T> bool ValueFilter< T>::matches( const T& value) const
{
   if (mFilters.empty())
      throw std::runtime_error( "no filter specified");

   for (auto const& next_filter : mFilters)
   {
      if (next_filter.matches( value))
         return true;
   } // end for
   return false;
} // ValueFilter< T>::matches


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_VALUE_FILTER_HPP


// =====  END OF value_filter.hpp  =====

