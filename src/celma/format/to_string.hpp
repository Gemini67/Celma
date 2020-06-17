
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
/// Provides several overloads of a toString() function. At the end, this allows
/// to convert the contents of any STL container into a string/list.


#ifndef CELMA_FORMAT_TO_STRING_HPP
#define CELMA_FORMAT_TO_STRING_HPP


#include <bitset>
#include <iomanip>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include "celma/common/dynamic_bitset.hpp"
#include "celma/common/tuple_at_index.hpp"
#include "celma/common/tuple_length.hpp"


namespace celma { namespace format {


/// Template to convert any value type into string format. Requires the
/// ostream << operator for the passed type.
///
/// @tparam  T
///    The type of the data to write into the string.
/// @param[in]  data
///    The data to write into the string.
/// @return
///    The string with the data.
/// @since
///    0.14.3, 20.06.2017
template< typename T> std::string toString( const T& data)
{

   std::ostringstream  oss;
   

   oss << data;

   return oss.str();
} // toString


/// Function to write a boolean value into the string.
///
/// @param[in]  flag  The boolean value to write.
/// @return  String with the value of the boolean flag.
/// @since  1.8.0, 20.07.2018
inline std::string toString( const bool flag)
{

   std::ostringstream  oss;


   oss << std::boolalpha << flag;

   return oss.str();
} // toString


/// Function to write a double value into the string.
///
/// @param[in]  val  The double value to write.
/// @return  String with the double value in fixed format.
/// @since  1.8.0, 20.07.2018
inline std::string toString( const double val)
{

   std::ostringstream  oss;


   oss << std::fixed << val;

   return oss.str();
} // toString


/// Function to write a string into the string ;-)
/// Add double quotation marks to the string, to make sure multiple-words
/// strings are interpreted correctly afterwards.
/// @param[in]  data
///    The string to write.
/// @return
///    String with the quoted input string.
/// @since
///    0.14.3, 20.06.2017
inline std::string toString( const std::string& data)
{

   std::ostringstream  oss;


   oss << '"' << data << '"';

   return oss.str();
} // toString


/// Format the contents of a vector of bool into a binary string.
///
/// @param[in]  vb  The vector of boolean values to convert the contents of.
/// @return  String with the contents of the vector as binary number.
/// @since  x.y.z, 17.06.2020
inline std::string toString( const std::vector< bool>& vb)
{
   std::string  result( vb.size(), '0');

   for (size_t idx = 0; idx < vb.size(); ++idx)
   {
      if (vb[ idx])
         result[ idx] = '1';
   } // end for
   return result;
} // toString


/// Format the contents of a dynamic bitset into a binary string.
///
/// @param[in]  dbs  The dynamic bitset to convert the contents of.
/// @return  String with the contents of the dynamic bitset as binary number.
/// @since  x.y.z, 10.06.2020
inline std::string toString( const common::DynamicBitset& dbs)
{
   return dbs.to_string();
} // toString


/// Template to handle a data pair.<br>
/// By providing this implementation, it is possible to treat containers like
/// lists, vectors and maps/multi-maps the same: Call toString() for the value
/// type of the iterator, for maps this leads to a call of toString< pair>().
///
/// @tparam  F
///    The type of the first value in the pair.
/// @tparam  S
///    The type of the second value in the pair.
/// @param[in]  data_pair
///    The pair of data to write into the string.
/// @return
///    The string with the data of the pair.
/// @since
///    0.14.3, 20.06.2017
template< typename F, typename S>
   std::string toString( const std::pair< F, S>& data_pair)
{

   std::ostringstream  oss;
   
   oss << "{ " << toString( data_pair.first) << ", "
       << toString( data_pair.second) << "}";

   return oss.str();
} // toString


/// Template to handle the contents of any STL data container.
///
/// @tparam  I
///    The type of iterator to use for iterating over the values of the
///    container.
/// @param[in]  from
///    The start value for the iteration, typically container::begin().
/// @param[in]  to
///    Iterator pointing to the end of the range, typically container::end().
/// @return
///    The string with the values from the container.
/// @since
///    0.14.3, 20.06.2017
template< typename I> std::string toString( I from, const I& to)
{

   std::ostringstream  oss;
   const I             from_copy( from);

   for (; from != to; ++from)
   {
      if (from != from_copy)
         oss << ", ";
      oss << toString( *from);
   } // end for

   return oss.str();
} // toString


/// Template to handle a std::bitset<>.
///
/// @tparam  N
///    The size of the bitset.
/// @param[in]  bs
///    The bitset to print the contents of.
/// @return
///    The string with the values from the bitset.
/// @since
///    1.8.0, 05.07.2018
template< size_t N> std::string toString( const std::bitset< N>& bs)
{
   return bs.to_string();
} // toString


/// Creates a string with a list of the values in the tuple.
///
/// @tparam  T
///    The types of the values in the tuple.
/// @param[in]  tpl
///    The tuple to format the values of.
/// @return
///    The string with the list of the values.
/// @since
///    1.8.0, 05.07.2018
template< typename... T> std::string toString( const std::tuple< T...>& tpl)
{
   const auto          tpl_length = common::tuple_length( tpl);
   std::ostringstream  oss;
   for (size_t i = 0; i < tpl_length; ++i)
   {
      if (i > 0)
         oss << ", ";

      common::tuple_at_index( i, tpl, [&oss]( auto const& value)
         {
            oss << format::toString( value);
         });
   } // end for
   return oss.str();
} // toString


/// Template to handle a std::priority_queue<>.
/// The speciality here is of course that it is not possible to iterate over the
/// values in a priority queue. This means we have to copy the priority queue
/// and then get the values from the copy.
///
/// @tparam  T  The tye of the values in the priority queue.
/// @param[in]  pq
///    The priority queue object to print the contents of. Needs to be copied so
///    we can access the values.
/// @return  The string with the values from the priority queue.
/// @since  1.34.0, 25.12.2019
template< typename T> std::string toString( std::priority_queue< T> pq)
{
   std::ostringstream  oss;

   while (!pq.empty())
   {
      if (!oss.str().empty())
         oss << ", ";
      oss << toString( pq.top());
      pq.pop();
   } // end while

   return oss.str();
} // toString


/// Template to handle a std::queue<>.
/// The speciality here is of course that it is not possible to iterate over the
/// values in a queue. This means we have to copy the queue and then get the
/// values from the copy.
///
/// @tparam  T  The tye of the values in the queue.
/// @param[in]  q
///    The queue object to print the contents of. Needs to be copied so we can
///    access the values.
/// @return  The string with the values from the queue.
/// @since  1.34.0, 29.12.2019
template< typename T> std::string toString( std::queue< T> q)
{
   std::ostringstream  oss;

   while (!q.empty())
   {
      if (!oss.str().empty())
         oss << ", ";
      oss << toString( q.front());
      q.pop();
   } // end while

   return oss.str();
} // toString


/// Template to handle a std::stack<>.
/// The speciality here is of course that it is not possible to iterate over the
/// values in a stack. This means we have to copy the stack and then get the
/// values from the copy.
///
/// @tparam  T  The tye of the values in the stack.
/// @param[in]  stck
///    The stack object to print the contents of. Needs to be copied so we can
///    access the values.
/// @return  The string with the values from the stack.
/// @since  1.34.0, 21.11.2019
template< typename T> std::string toString( std::stack< T> stck)
{
   std::ostringstream  oss;

   while (!stck.empty())
   {
      if (!oss.str().empty())
         oss << ", ";
      oss << toString( stck.top());
      stck.pop();
   } // end while

   return oss.str();
} // toString


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_TO_STRING_HPP


// =====  END OF to_string.hpp  =====

