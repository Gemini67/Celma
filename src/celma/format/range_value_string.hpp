
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2019-2020 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of functions celma::format::rangeValueString().


#ifndef CELMA_FORMAT_RANGE_VALUE_STRING_HPP
#define CELMA_FORMAT_RANGE_VALUE_STRING_HPP


#include <bitset>
#include <limits>
#include <sstream>
#include <string>


namespace celma { namespace format {


/// Creates a string with the values from the sequence, where subsequent values
/// are combined into a range, e.g. 13-21.
///
/// @tparam  I
///    The type of the iterator of the sequence.
/// @tparam  T
///    The type of the values in the sequence.
/// @param[in]  iter
///    Iterator pointing to the first element in the sequence.
/// @param[in]  end
///    Iterator pointing behind the last element in the sequence.
/// @param[in]  sep
///    The separator to use between single values.
/// @return
///    String with the values from the sequence with ranges where possible.
/// @since  1.21.0, 27.03.2019
template< typename I, typename T = int>
   std::string rangeValueString( I iter, const I& end,
      const std::string& sep = ", ")
{

   std::ostringstream  oss;
   T                   last = 0;
   T                   range_first = 0;


   for (; iter != end; ++iter)
   {
      if ((last != 0) && (*iter != last + 1))
      {
         // current value does not belong to a range
         if (range_first == last)
         {
            // had a single value
            oss << last << sep;

         // but we had a range started
         } else if (last > range_first + 1)
         {
            // real range
            oss << range_first << "-" << last << sep;
         } else
         {
            // range of two elements is not a range
            oss << range_first << sep << last << sep;
         } // end if
         range_first = 0;
      } // end if

      last = *iter;
      if (range_first == 0)
      {
         range_first = *iter;
      } // end if
   } // end for

   // now handle the last value/range
   if (last > range_first + 1)
   {
      oss << range_first << "-" << last;
   } else if (last == range_first + 1)
   {
      oss << range_first << sep << last;
   } else if (last != 0)
   {
      oss << last;
   } // end if

   return oss.str();
} // rangeValueString


/// Same as above, but creates the range string always for all elements in the
/// container.
///
/// @tparam  C  The type of the container.
/// @param[in]  cont
///    The container to iterate over to create the value string.
/// @param[in]  sep
///    The separator to use between single values.
/// @return
///    String with the values from the container with ranges where possible.
/// @since  1.11.0, 27.03.2019
template< typename C>
   std::string rangeValueString( const C& cont, const std::string& sep = ", ")
{
   return rangeValueString< typename C::const_iterator, typename C::value_type>(
      cont.begin(), cont.end(), sep);
} // rangeValueString


/// Creates a string with the values from a bitset, where subsequent values
/// are combined into a range, e.g. 13-21.
///
/// @tparam  N
///    The size of the bitset.
/// @param[in]  bs
///    The bitset to create the range value string for.
/// @param[in]  sep
///    The separator to use between single values.
/// @return
///    String with the values from the bitset with ranges where possible.
/// @since  x.y.z, 07.01.2020
template< size_t N> std::string rangeValueString( const std::bitset< N>& bs,
   const std::string& sep = ", ")
{

   std::ostringstream  oss;
   size_t              last = std::numeric_limits< size_t>::max();
   size_t              range_first = std::numeric_limits< size_t>::max();


   for (size_t idx = 0; idx < N; ++idx)
   {
      if (!bs[ idx])
         continue;

      if ((last != std::numeric_limits< size_t>::max()) && (idx != last + 1))
      {
         // current value does not belong to a range
         if (range_first == last)
         {
            // had a single value
            oss << last << sep;

         // but we had a range started
         } else if (last > range_first + 1)
         {
            // real range
            oss << range_first << "-" << last << sep;
         } else
         {
            // range of two elements is not a range
            oss << range_first << sep << last << sep;
         } // end if
         range_first = std::numeric_limits< size_t>::max();
      } // end if

      last = idx;
      if (range_first == std::numeric_limits< size_t>::max())
      {
         range_first = idx;
      } // end if
   } // end for

   // now handle the last value/range
   if (last > range_first + 1)
   {
      oss << range_first << "-" << last;
   } else if (last == range_first + 1)
   {
      oss << range_first << sep << last;
   } else if (last != std::numeric_limits< size_t>::max())
   {
      oss << last;
   } // end if

   return oss.str();
} // rangeValueString


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_RANGE_VALUE_STRING_HPP


// =====  END OF range_value_string.hpp  =====

