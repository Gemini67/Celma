
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
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


#include <sstream>
#include <string>
#include <utility>


namespace celma { namespace format {


/// Template to convert any value type into string format. Requires the
/// ostream << operator for the passed type.
/// @tparam  T  The type of the data to write into the string.
/// @param[in]  data  The data to write into the string.
/// @return  The string with the data.
/// @since  0.14.3, 20.06.2017
template< typename T> std::string toString( const T& data)
{

   std::ostringstream  oss;
   

   oss << data;

   return oss.str();
} // toString


/// Function to write a string into the string ;-)<br>
/// Add double quotation marks to the string, to make sure multiple-words
/// strings are interpreted correctly afterwards.
/// @param[in]  data  The string to write.
/// @return  String with the quoted input string.
/// @since  0.14.3, 20.06.2017
inline std::string toString( const std::string& data)
{

   std::ostringstream  oss;


   oss << '"' << data << '"';

   return oss.str();
} // toString


/// Template to handle a data pair.<br>
/// By providing this implementation, it is possible to treat containers like
/// lists, vectors and maps/multi-maps the same: Call toString() for the value
/// type of the iterator, for maps this leads to a call of toString< pair>().
/// @tparam  F  The type of the first value in the pair.
/// @tparam  S  The type of the second value in the pair.
/// @param[in]  data_pair  The pair of data to write into the string.
/// @return  The string with the data of the pair.
/// @since  0.14.3, 20.06.2017
template< typename F, typename S>
   std::string toString( const std::pair< F, S>& data_pair)
{

   std::ostringstream  oss;
   
   oss << "{ " << toString( data_pair.first) << ", "
       << toString( data_pair.second) << "}";

   return oss.str();
} // toString


/// Template to handle the contents of any STL  container.
/// @tparam  I  The type of iterator to use for iterating over the values of the
///             container.
/// @param[in]  from  The start value for the iteration, typically
///                   container::begin()..
/// @param[in]  to    Iterator pointing to the end of the range, typically
///                   container::end().
/// @return  The string with the values from the container.
/// @since  0.14.3, 20.06.2017
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


} // namespace format
} // namespace celma


#endif   // CELMA_FORMAT_TO_STRING_HPP


// ==========================  END OF to_string.hpp  ==========================

