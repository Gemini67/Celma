
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


#include <iostream>
#include <string>
#include <vector>
#include "celma/common/detail/filter.hpp"
#include "celma/common/type_name.hpp"


namespace celma { namespace common {


/// Stores multiple filters and checks values against those filters.
/// There are two ways to add a filter:
/// - Using add... methods: The filter is added as top-level filter. When
///   checking with values, at least one of the top-level filters must match the
///   value, i.e. an "or" combination.
/// - Using append... methods: The filter is appended to the last top-level
///   filter, in other words at least one filter must have been added before
///   using add...(). When checking with values, all filters of the same group
///   must match a value, i.e. the first filter that was added using add... plus
///   all filters directly afterwards added using append...(). This corresponds
///   to an "and" combination.
///
/// Any kind and numbers of filters may be combined, however you have to make
/// sure to not define combinations that are always or never true:
/// - two single value filters on the same level: always \c false
/// - two inverted single value filters at top level: always \c true.
///
/// @tparam  T  The type of the values to store the filters for.
/// @since  1.31.0, 07.10.2019
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
   /// @since  1.31.0, 07.10.2019
   void addSingleValueFilter( const T& value, bool inverted = false);

   /// Appends a single value filter to the last top-level filter.
   ///
   /// @param[in]  value
   ///    The value to check for.
   /// @param[in]  inverted
   ///    If set, the filter matches all values not equal to \a value.
   /// @throw  std::runtime_error if no top-level filter was added before.
   /// @since  1.31.0, 07.10.2019
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
   /// @since  1.31.0, 07.10.2019
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
   /// @since  1.31.0, 07.10.2019
   void appendRangeFilter( const T& min_value, const T& max_value,
      bool inverted = false) noexcept( false);

   /// Adds a minimum filter as top-level filter.
   ///
   /// @param[in]  min_val
   ///    The minimum value to check against, i.e. a value x must be greater
   ///    than or equal to \a min_val.
   /// @since  1.31.0, 07.10.2019
   void addMinimumFilter( const T& min_val);

   /// Appends a minimum filter to the last top-level filter.
   ///
   /// @param[in]  min_val
   ///    The minimum value to check against, i.e. a value x must be greater
   ///    than or equal to \a min_val.
   /// @throw  std::runtime_error if no top-level filter was added before.
   /// @since  1.31.0, 07.10.2019
   void appendMinimumFilter( const T& min_val) noexcept( false);

   /// Adds a maximum filter as top-level filter.
   ///
   /// @param[in]  max_val
   ///    The maximum value to check against, i.e. a value x must be less than
   ///    \a max_val.
   /// @since  1.31.0, 07.10.2019
   void addMaximumFilter( const T& max_val);

   /// Appends a maximum filter to the last top-level filter.
   ///
   /// @param[in]  max_val
   ///    The maximum value to check against, i.e. a value x must be less than
   ///    \a max_val.
   /// @throw  std::runtime_error if no top-level filter was added before.
   /// @since  1.31.0, 07.10.2019
   void appendMaximumFilter( const T& max_val) noexcept( false);

   /// Compares the given value against the defined filters:
   /// - From the top-level filters, at least one must match (or condition).
   /// - If a top-level filter contains multiple filters, each of them must
   ///   match (and condition).
   ///
   /// @param[in]  value  The value to check against the filters.
   /// @return  \c true if the value matched the filters as described above.
   /// @throw  std::runtime_error if filters are defined.
   /// @since  1.31.0, 07.10.2019
   bool matches( const T& value) const noexcept( false);

   /// Normal assignent is not possible.
   ValueFilter& operator =( const ValueFilter&) = delete;

   /// But move-assignment is allowed.
   ValueFilter& operator =( ValueFilter&&) = default;

   /// Clears all internally stored filters.
   ///
   /// @since  1.31.0, 17.10.2019
   void clear();

   /// Returns if the filter container is empty or not.
   ///
   /// @return  \c true if the filter container is empty.
   /// @since  1.31.0, 18.10.2019
   bool empty() const;

   /// Returns the number of top-level filters stored internally.
   ///
   /// @return   Number of top-level filters stored internally.
   /// @since  1.31.0, 18.10.2019
   size_t size() const;

   /// Returns a string with the list of filters.
   ///
   /// @return  String with the list of filters.
   /// @since  1.31.0, 18.10.2019
   std::string str() const;

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


template< typename T> void ValueFilter< T>::clear()
{
   mFilters.clear();
} // ValueFilter< T>::clear


template< typename T> bool ValueFilter< T>::empty() const
{
   return mFilters.empty();
} // ValueFilter< T>::empty


template< typename T> size_t ValueFilter< T>::size() const
{
   return mFilters.size();
} // ValueFilter< T>::size


template< typename T> std::string ValueFilter< T>::str() const
{
   std::ostringstream  oss;
   for (auto const& filter : mFilters)
   {
      if (!oss.str().empty())
         oss << ',';
      oss << filter.str();
   } // end for
   return oss.str();
} // ValueFilter< T>::str


/// Insertion operator for value filter objects.
///
/// @tparam  T  The type of the values for which the filters are defined.
/// @param[in]  os
///    The stream to write into.
/// @param[in]  vf
///    The object to print the value filters of.
/// @return
///    The stream as passed in.
/// @since  1.31.0, 18.10.2019
template< typename T>
   std::ostream& operator <<( std::ostream& os, const ValueFilter< T>& vf)
{
   return os << vf.str();
} // operator <<


} // namespace common


/// Specialisation of type<> for type 'celma::common::ValueFilter<>'.
///
/// @tparam  T  The type of the values for which filters may be stored.
/// @since  1.31.0, 17.10.2019
template< typename T> class type< common::ValueFilter< T>>
{
public:
   /// Returns the name of the type.
   ///
   /// @return  'celma::common::ValueFilter< <type-name> >' (without the spaces).
   /// @since  1.31.0, 17.10.2019
   static constexpr const char* name()
   {
      return &mName[ 0];
   } // type< common::ValueFilter< T>>::name

   /// Used to store the name of the type persistently.
   /// Is public to build nested container names, don't access for printing.
   static constexpr auto const  mName =
      common::string_concat( "celma::common::ValueFilter<", type< T>::mName, ">");

}; // type< celma::common::ValueFilter< T>>


} // namespace celma


#endif   // CELMA_COMMON_VALUE_FILTER_HPP


// =====  END OF value_filter.hpp  =====

