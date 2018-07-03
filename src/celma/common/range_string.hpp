
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::common::RangeString.


#ifndef CELMA_COMMON_RANGE_STRING_HPP
#define CELMA_COMMON_RANGE_STRING_HPP


#include <string>
#include "celma/common/detail/range_string_iterator.hpp"


namespace celma { namespace common {


/// Use this class to have a range-string parsed and the generated values
/// returned by the given iterator.<br>
/// Supported format of a range-string:
/// * Single values
/// * Ranges: \<start\>-\<end\>
/// * Ranges with increment: \<start\>-\<end\>[\<increment\>]
/// * Ranges with values to exclude: \<start\>-\<end\>{\<exclude-range\>}
///   The exclude-range can itself be a complex range (with start, end and skip)
/// * Increment and exclude can be combined: \<start\>-\<end\>[\<increment\>]{\<exclude-range\>}
/// * Comma-separated list of combinations thereof.
/// * Note: exclude ranges must immediately follow the range they are related
///   to. E.g. the following range string would be invalid:
///      3-20,30{10,12-15}
///   it should be:
///      3-20{10,12-15},30
///
/// @since  0.2, 07.04.2016
template< typename T = int> class RangeString
{
public:
   /// Constructor.
   /// @param[in]  str  The range string to evaluate.
   /// @since  0.2, 07.04.2016
   RangeString( const std::string& str);

   /// Type of the iterator to use for iterating over the values.
   typedef detail::RangeStringIterator< const std::string, T>  const_iterator;

   /// Returns the iterator with the first value from the range.
   /// @return  The iterator with the first value.
   /// @since  0.2, 07.04.2016
   const_iterator begin() const;

   /// Returns the end iterator.
   /// @return  The end iterator.
   /// @since  0.2, 07.04.2016
   const_iterator end() const;

   /// Returns the iterator with the first value from the range.
   /// @return  The iterator with the first value.
   /// @since  0.2, 09.04.2016
   const_iterator cbegin() const;

   /// Returns the end iterator.
   /// @return  The end iterator.
   /// @since  0.2, 09.04.2016
   const_iterator cend() const;

private:
   friend class detail::RangeStringIterator< const RangeString, T>;

   /// The range string to evaluate.
   const std::string  mRangeString;

}; // RangeString< T>


// inlined methods
// ===============


template< typename T> RangeString< T>::RangeString( const std::string& str):
   mRangeString( str)
{
} // RangeString< T>::RangeString


template< typename T>
   typename RangeString< T>::const_iterator RangeString< T>::begin() const
{
   return const_iterator( mRangeString);
} // RangeString< T>::begin


template< typename T>
   typename RangeString< T>::const_iterator RangeString< T>::end() const
{
   return const_iterator();
} // RangeString< T>::end


template< typename T>
   typename RangeString< T>::const_iterator RangeString< T>::cbegin() const
{
   return const_iterator( mRangeString);
} // RangeString< T>::cbegin


template< typename T>
   typename RangeString< T>::const_iterator RangeString< T>::cend() const
{
   return const_iterator();
} // RangeString< T>::cend


} // namespace common
} // namespace celma


#endif   // CELMA_COMMON_RANGE_STRING_HPP


// =====  END OF range_string.hpp  =====

